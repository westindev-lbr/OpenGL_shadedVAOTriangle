/*!\file window.c
 *
 * \brief GL4Dummies, exemple 3D simple avec dessin de triangle coloré
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date February 11 2018
 */

#include <GL4D/gl4du.h>
#include <GL4D/gl4duw_SDL2.h>

/* Prototypes des fonctions statiques contenues dans ce fichier C */
static void init(void);
static void draw(void);
static void quit(void);

/*!\brief largeur et hauteur de la fenêtre */
static int _wW = 800, _wH = 600;
/*!\brief identifiant du (futur) Vertex Array Object */
static GLuint _vao = 0;
/*!\brief identifiant du (futur) buffer de data - VBO ou Vertex Buffer Object */
static GLuint _buffer = 0;
/*!\brief identifiant du (futur) GLSL program */
static GLuint _pId = 0;

/*!\brief créé la fenêtre d'affichage, initialise GL et les données,
 * affecte les fonctions d'événements et lance la boucle principale
 * d'affichage.
 */
int main(int argc, char **argv)
{
  if (!gl4duwCreateWindow(argc, argv, "GL4Dummies", 20, 20,
                          _wW, _wH, GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwDisplayFunc(draw);
  gl4duwMainLoop();
  return 0;
}
/*!\brief initialise les paramètres OpenGL et les données.
 *
 * Exercice (corrigé en 1.1) : modifier data, les lignes
 * glVertexAttribPointer et glDrawArrays (dans draw) afin de dessiner
 * un quadrilatère recouvrant l'ensemble de l'écran ; mettre une
 * couleur jaune pour le point ajouté.
 */
static void init(void)
{
  /* données envoyées par tranches (différent du mode interleaved
   * array) dans le VBO */
  GLfloat data[] = {
      /* 3 coordonnées de sommets en 2D */
      -1.0f, -1.0f,
      1.0f, -1.0f,
      -1.0f, 1.0f,
      1.0f, 1.0f,

      /* 3 couleurs */
      1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 0.0f};
  /* Création du programme shader (voir le dossier shader) */
  _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/basic.fs", NULL);
  /* Set de la couleur (RGBA) d'effacement OpenGL */
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  /* dans quelle partie de l'écran on effectue le rendu */
  glViewport(0, 0, _wW, _wH);
  /* VBO  == Le conteneur des vertex des sommets
    VAO == Tableau de VBO, il y a au moins un VBO et un description
  */
  /* Génération d'un identifiant de VAO */
  glGenVertexArrays(1, &_vao);
  /* Lier le VAO-machine-GL à l'identifiant VAO généré */
  glBindVertexArray(_vao);
  /* Activation des 2 premiers indices d'attribut de sommet
  J'ouvre 2 cannaux le 0 et le 1 corrspondant aux attributs du sommet : coord 2D(x,y) et Couleur 3D(r,g,b)
  */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  /*
    methode 2 :
      glEnableVertexAttribArray(glGetAttribLocation(_pId, "vsiPosition"));
      glEnableVertexAttribArray(glGetAttribLocation(_pId, "vsiColor"));
  */

  /* Génération d'un identifiant de VBO
  je génères un id pour le VBO*/
  glGenBuffers(1, &_buffer);
  /* Lier le VBO-machine-GL à l'identifiant VBO généré
  GL_ARRAY_BUFFER == type de buffer dites Brute */
  glBindBuffer(GL_ARRAY_BUFFER, _buffer);
  /* Transfert des données VBO
  Envoi des données via le bus du CPU vers GPU */
  glBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);
  /* Paramétrage 2 premiers indices d'attribut de sommet
  @param 1 == indice du canal (voir l76,77)
  @param 2 == 2 -> coord 2D, 3 -> 3D
  @param 3 == le Type (ici flottant)
  @param 4 == Normaliser une donnée (revenir à l'échelle 1)  ex : || u || = racine(x^2 + y^2)  du coup la norme ==  u / ||u||
  @param 5 == stride 0 -> le pas en octet qu'il y a entre 1 donnée et la suivante
  @param 6 == pointeur sur le 1er élément ex : 1er cooord et pour le 2eme 1ere couleur
  */
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void *)(4 * 2 * sizeof *data));
  /* dé-lier le VAO et VBO
    Fermeture VAO
    Fermeture VBO
  */
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
/*!\brief Cette fonction dessine dans le contexte OpenGL actif. */
static void draw(void)
{
  /* effacement du buffer de couleur */
  glClear(GL_COLOR_BUFFER_BIT);
  /* activation du programme _pId */
  glUseProgram(_pId);
  /* Lier le VAO-machine-GL à l'identifiant VAO _vao */
  glBindVertexArray(_vao);
  /* Dessiner le VAO comme une bande de triangles à 3 sommets commençant à 0 */
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  /* dé-lier le VAO */
  glBindVertexArray(0);
  /* désactiver le programme shader */
  glUseProgram(0);
}
/*!\brief appelée au moment de sortir du programme (atexit), elle
 *  libère les éléments OpenGL utilisés.*/
static void quit(void)
{
  /* suppression du VAO _vao en GPU */
  if (_vao)
    glDeleteVertexArrays(1, &_vao);
  /* suppression du VBO _buffer en GPU */
  if (_buffer)
    glDeleteBuffers(1, &_buffer);
  /* nettoyage des éléments utilisés par la bibliothèque GL4Dummies */
  gl4duClean(GL4DU_ALL);
}

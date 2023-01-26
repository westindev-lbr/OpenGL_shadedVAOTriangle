# Introduction to OpenGL

## VAO

### Exo 1.1

- [x] Exercice :

- modifier data, les lignes glVertexAttribPointer et glDrawArrays (dans draw) afin de dessiner un quadrilatère recouvrant l'ensemble de l'écran
- mettre une couleur jaune pour le point ajouté

### Exo 1.2

- [ ] Exercice:

- entrelacer les données de sommet dans data afin d'avoir la 1ere coordonnée spaciale suivie de sa couleur,suivi de la 2ème coordonnée ... modifier les appels à glVertexAttribPointer en corrigeant le 5ème et 6ème argument (voir
doc de glVertexAttribPointer sur https://www.khronos.org/registry/OpenGL-Refpages/gl4) puis ajouter une variable d'angle (en radians) qui s'incrémente dans draw, envoyer cette variable à GLSL (le vertex shader) comme variable "uniform float angle;" en utilisant les fonctions glGetUniformLocation et glUniform1f (voir les doc sur https://www.khronos.org/registry/OpenGL-Refpages/gl4).
Enfin utiliser cet angle côté vertex shader pour construire une matrice de rotation 4x4 autour de l'axe y et l'utiliser sur le sommet.

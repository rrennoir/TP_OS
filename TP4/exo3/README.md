# Exo3

## 1) Qu'observez-vous des comportement de ces deux processus ?

* Ils affichent deux fois les 5 premiers caractères.

## 2) Comment peut-on réssoudre le problème observé ?
 
* Créer les strings a affichier avant le fork puis simplement le print dans chaque processus, au lieu de lire le fichier et d'affiche le string dans un processus différent.

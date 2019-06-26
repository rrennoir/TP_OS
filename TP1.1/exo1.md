# TP 1.1 os exerciece 3

## 1) Créez dans votre répertoire de connexion (home directory) un répertoire nommé"exo"

* mkdir exo
* cd ./exo
* pwd
pwd affiche **/home/exo**

## 2) Dans le répertoire"exo", créez un fichier texte nommé "es1", puis un sous-répertoire nommé"essai2"

* cd ./exo
* touch ./es1.txt
* mkdir ./essai2

## 3) Copiez le fichier "es1" dans le répertoire "essai2" (commandecp). Changez le nomde cette copie en "es1-copie"

* cp ./es1 ./essai2
* mv ./essai2/es1 ./essai2/es1-copy

## 4) Que fait la commandels * ? Comment peut-on voir les fichiers dont le nomcommence par "es"

* la commande ls * affiche :
    `es1 essai2 es1-copy`

* pour afficher tout les fichier commencent par es il faut uriliser ls es*

## 5) Tapezman rmpour afficher l’aide la commanderm. Lisez rapidement la descrip-tion et la liste des options. Comment peut-on supprimer un fichier avec demandede confirmation ? Comment supprimer un répertoire et ses sous-répertoires

* on peut supprimer un fichier avec une demande de confirmation avec la commande rm [file name] -i
* on peut supprimer un ficher et tout ces sous fichiers avec la commande rm -r [file name]

## 6) On a un fichier texte de 100 lignes, comment faire pour n’afficher que la ligne 51

on peut utiliser la commande sed -n 51p [file name] pour extraire la 51ieme ligne du fichier

## 7) Qu’observez-vous si on exécute la commande grep passwd /etc/*?Comment faire pour supprimer tous ces messages d’erreurs

* il y a de nombreux message car je n ai pas les droit root
* rajouter sudo devant la commande

## 8) En utilisant la commandefindtrouvez tous les fichiers dont les noms commençant par a ou A

on peut utiliser find a* pour afficher tout les ficher commenceant par a

## 9) En utilisant la commande find trouvez quels sont les fichiers qui ont été modifiés plus récemment qu’un autre fichier spécifié

find /chemin/ -type f - file-mtime -print

## 10) En utilisant la commande find trouvez tous les fichiers qui se terminent par .o et supprimez-les

il faut se servir de la commande rm -i $(find . -name *.o)

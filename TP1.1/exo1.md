# TP 1.1 os exerciece 3

## 1)

* mkdir exo
* cd ./exo
* pwd
pwd affiche **/home/cg/root/exo**


## 2)

* cd ./exo
* touch ./es1
* mkdir ./essai2


## 3)

* cp ./es1 ./essai2
* mv ./essai2/es1 ./essai2/es1-copy


## 4)

* la commande ls * affiche :
* es1
* essai2:
* es1-copy

pour afficher tout les fichier commencent par es il faut uriliser ls es* 


## 5)

* on peut supprimer un fichier avec une demande de confirmation avec la commande rm [file name] -i
* on peut supprimer un ficher et tout ces sous fichiers avec la commande rm -r [file name] 


## 6)

on peut utiliser la commande sed -n 51p [file name] pour extraire la 51ieme ligne du fichier


## 7)

* il y a de nombreux message car je n ai pas les droit root
* rajouter sudo devant la commande


## 8)

on peut utiliser find a* pour afficher tout les ficher commenceant par a


## 9)

find /chemin/ -type f - file-mtime -print


## 10)

il faut se servirr de la commande rm -i $(find . -name *.o)

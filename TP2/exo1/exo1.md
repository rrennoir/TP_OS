# TP 2: Exo1

## 1) Que fait ce programme

* il enregistre des nombres positif ou négative entré par l'utilisateur dans une list.

## 2) En utilisant le gdb, mettez en évidence le passage par référence de chaque élément du tableau

* Dans `for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++);`
* `&array[n]` est un passage en référence de l'élement n du tableau.

## 3)Essayez de comprendre les rapports de la commande strace

* Strace permet de voir tous les appels systeme que le programe execute.

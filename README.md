Rendu du projet LIIFLC Version 2017-2018
================================

PERRIN   Thibaud  #123456  
KACED    Jayson   #1710753

Voir http://liris.cnrs.fr/sylvain.brandel/wiki/doku.php?id=ens:liflf:projet

Contenu de l'archive
--------------------

README.txt      ce fichier
Makefile          cibles 
                    all (par défaut) : exécutable principal
                    parser : flex et bison pour le parser d'expression rationnelles
                    clean et cleanparser : pour le nettoyage
exemples/         exemples d'automates :
                    D = Déterministe,
                    ND = Non Déterministe,
                    NDE = Non Déterministe avec transitions spontanées
src/              fichiers sources C++

Utilisation du programme ./ndet :
--------------------------
-acc ou -accept Input Word :  
	 détermine si le mot Word est accepté par l'automate Input  
-det ou -determinize Input Output [-g] :  
	 déterminise l'automate Input, écrit le résultat dans Output  
-aut2expr ou automate2expressionrationnelle Input :  
	 calcule l'expression rationnelle correspondant à l'automate Input et l'affiche sur la sortie standard
-min ou -minimisation Input Output [-g] :  
	 construit l'automate standard correspondant à Input, écrit le résultat dans Output  
-pequ ou -pseudo_equivalent Input1 Intput2 size :  
	 détermine si les deux automates Input1 et Input2 sont pseudo-équivalents par comparaison mot par mot de longueur < à size  
-equ ou -equivalent Input1 Intput2 :  
	 détermine si les deux automates Input1 et Input2 sont équivalents par minimisation et comparaison des tables de transition  
-nop ou -no_operation Input Output [-g] :  
	 ne fait rien, recopie juste l'entrée dans Output  
-g :  
	 paramètre optionnel pour avoir une sortie au format Graphviz dans Output  


Documentation de référence
--------------------------

http://www.cplusplus.com/reference/

Commentaires
------------

Cet exemple d'archive est fournie aux étudiants comme projet de départ pde l'UE LIFLC 2017-2018

Pour utiliser la sortie graphique, utilisez le package graphviz https://doc.ubuntu-fr.org/graphviz


Mettre ici les commentaires éventuels des étudiants.
Tous les warnings, info résiduels doivent être justifiés ici.

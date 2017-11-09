Rendu du projet LIIFLC Version 1.0 2017-2018
================================

PERRIN   Thibaud  #1707841  
KACED    Jayson   #1710753

__Université Claube Bernard Lyon 1__

Sujet du projet :  
--------------------
L'objectif de ce TP est de réaliser un programme qui prend en entrée un automate à états finis non déterministe dont la description est lue dans un fichier, qui teste si un mot donné est accepté par cet automate, et qui déterminise cet automate.  

Voir http://liris.cnrs.fr/sylvain.brandel/wiki/doku.php?id=ens:liflf:projet

Contenu de l'archive
--------------------

* __README.md__ ce fichier
* __Makefile__          cibles 
	* all (par défaut) : exécutable principal
	* parser : flex et bison pour le parser d'expression rationnelles
	* clean et cleanparser : pour le nettoyage
* __exemples/__ exemples d'automates :
	* D = Déterministe,
	* ND = Non Déterministe,
	* NDE = Non Déterministe avec transitions spontanées
* __src/__ fichiers sources C++

Utilisation du programme ./ndet :
--------------------------
__-acc ou -accept Input Word :__  
	 détermine si le mot Word est accepté par l'automate Input  
__-det ou -determinize Input Output [-g] :__  
	 déterminise l'automate Input, écrit le résultat dans Output  
__-aut2expr ou automate2expressionrationnelle Input :__  
	 calcule l'expression rationnelle correspondant à l'automate Input et l'affiche sur la sortie standard
__-min ou -minimisation Input Output [-g] :__  
	 construit l'automate standard correspondant à Input, écrit le résultat dans Output  
__-pequ ou -pseudo_equivalent Input1 Intput2 size :__  
	 détermine si les deux automates Input1 et Input2 sont pseudo-équivalents par comparaison mot par mot de longueur < à size  
__-equ ou -equivalent Input1 Intput2 :__  
	 détermine si les deux automates Input1 et Input2 sont équivalents par minimisation et comparaison des tables de transition  
__-nop ou -no_operation Input Output [-g] :__  
	 ne fait rien, recopie juste l'entrée dans Output  
__-g :__  
	 paramètre optionnel pour avoir une sortie au format Graphviz dans Output 

Utilisation du programme ./ndet :
--------------------------
__-acc ou -accept Input Word :__  
	 détermine si le mot Word est accepté par l'automate Input  
__-det ou -determinize Input Output [-g] :__  
	 déterminise l'automate Input, écrit le résultat dans Output  
__-aut2expr ou automate2expressionrationnelle Input :__  
	 calcule l'expression rationnelle correspondant à l'automate Input et l'affiche sur la sortie standard
__-min ou -minimisation Input Output [-g] :__  
	 construit l'automate standard correspondant à Input, écrit le résultat dans Output  
__-pequ ou -pseudo_equivalent Input1 Intput2 size :__  
	 détermine si les deux automates Input1 et Input2 sont pseudo-équivalents par comparaison mot par mot de longueur < à size  
__-equ ou -equivalent Input1 Intput2 :__  
	 détermine si les deux automates Input1 et Input2 sont équivalents par minimisation et comparaison des tables de transition  
__-nop ou -no_operation Input Output [-g] :__  
	 ne fait rien, recopie juste l'entrée dans Output  
__-g :__  
	 paramètre optionnel pour avoir une sortie au format Graphviz dans Output  


Documentation de référence
--------------------------

http://www.cplusplus.com/reference/

Commentaires
------------

Cet archive hérite d'une archive fournie aux étudiants comme projet de départ pde l'UE LIFLC 2017-2018

Pour utiliser la sortie graphique, utilisez le package graphviz https://doc.ubuntu-fr.org/graphviz

Mettre ici les commentaires éventuels des étudiants.
Tous les warnings, info résiduels doivent être justifiés ici.

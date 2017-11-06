//******************************************************************************

#include <iostream>
#include <algorithm>

#include "Accept.h"
#include "FA_tools.h"

////////////////////////////////////////////////////////////////////////////////

bool EstDeterministe(const sAutoNDE& at){
  //TODO définir cette fonction

  return true;
}

////////////////////////////////////////////////////////////////////////////////

void Fermeture(const sAutoNDE& at, etatset_t& e){
  //TODO définir cette fonction
    etatset_t::iterator itEt, itEps;
    etatset_t tmp1 = e; // liste d'état temporaire, à chaque fois qu'on trouve un état

    do{
        etatset_t tmp2; // liste d'état, à chaque fois qu'on trouve un état par une e-transition
        for(size_t i=0; i < at.epsilon.size(); i++){
            itEt = tmp1.find(i);
            if(itEt != tmp1.end() && !at.epsilon[i].empty()){
                for(itEps = at.epsilon[i].begin(); itEps != at.epsilon[i].end(); itEps++){
                    if(e.insert(*itEps).second){
                        // si l'état inséré n'est pas déjà dans la liste d'états
                        tmp2.insert(*itEps);
                    }
                }
            }
        }
        // On se déplace sur les nouveaux état
        tmp1 = tmp2;
    }while(!tmp1.empty());
}

////////////////////////////////////////////////////////////////////////////////
/* renvoie l'ensemble des états accessibles depuis au moins un des états du paramètre e; */
etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c){
  //TODO définir cette fonction
  etatset_t r;

  //STEP 1 : c est-il dans l'alphabet de l'automate d'étude ?
  int numC = c - ASCII_A; //On récupère la valeur de c pour la comparer à l'alphabet
  if(numC > at.nb_etats) { return r; } // C n'est pas dans l'alphabet

  //STEP 2 : Où je peux aller avec C si je suis dans les état e
  for(int i = 0; i < at.trans.size(); i++) {
    if(e.find(i) != e.end()) { //On cherche si l'état i est demandé ou non
      if(!at.trans[i][numC].empty()) { //La transition de l'état i avec le symbole c existe
        std::set<etat_t>::iterator itTrans;
        for(itTrans = at.trans[i][numC].begin(); itTrans != at.trans[i][numC].end(); itTrans++){
          r.insert(*itTrans);
        }
      }
    }
  }

  // /\ Ne pas oublier de faire la fermture de E car sinon on oublie les transitions spontanées !!
  return r;
}

////////////////////////////////////////////////////////////////////////////////

bool Accept(const sAutoNDE& at, std::string str){
  //TODO définir cette fonction

  for (int i = 0; i < (int)str.size(); ++i) {
    std::cout << str[i] << std::endl;
  }

  std::cout << at.trans.front().front() << std::endl;

  return false;
}

//******************************************************************************

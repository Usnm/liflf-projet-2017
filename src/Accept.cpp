/**
 * \file Accept.cpp
 * \brief Programme de tests.
 * \author Thibaud PERRIN & Jayson KACED
 * \version 1
 *
 * Ensemble de fonctions pour vérifier le déterminisme d'un automate,
 * la fermeture d'un automate, le delta suivant un symbole donnée ainsi que
 * l'acceptation par l'automate d'un mot donné w
 *
 */

#include <iostream>
#include <algorithm>

#include "Accept.h"
#include "FA_tools.h"

using namespace std;

/*!
 * \brief Verification de déterminisme
 *
 * Fonction d'indication sur la détermination d'un automate.
 *
 * \param at Automate d'étude
 * \return VRAI si l'automate at est déterministe, FALSE sinon.
 */
bool EstDeterministe(const sAutoNDE& at){
    bool estDeter = true;

    for(int nbe = 0; nbe < at.nb_etats; nbe++){

        if(at.epsilon.size() != 0){
           if(at.epsilon[nbe].size() != 0 ){
               estDeter = false;
            } 
        }
        

    }

    for (int i=0; i<at.trans.size(); i++ )
    {

        for (int j=0; j<at.trans[i].size(); j++ )
        {

            if(at.trans[i][j].size() != 1){//On verifie que le nombre de liaisons par etats est egale 1 sinon non deterministe
                
                estDeter = false;
            }

        }
    }
    std::cout << "est Deterministe ? " << estDeter << std::endl;
    return estDeter;
}

/*!
 * \brief Fermeture d'un ensemble
 *
 * Fonction qui ajoute à l'ensemble d'états e
 * tous ceux qui sont accessibles via des transitions spontanées
 *
 * \param at Automate d'étude
 * \param e ensemble d'états
 */
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

/*!
 * \brief Delta d'un ensemble
 *
 * Fonction qui renvoie l'ensemble des états accessibles
 * depuis au moins un des états du paramètre e;
 *
 * \param at Automate d'étude
 * \param e ensemble d'états
 * \param c symbole donné
 *
 * \return r ensemble des états accessibles
 */
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
///bin\Debug\liflf-projet-2017.exe -acc exemples/AD1.txt ab//////

/*!
 * \brief Acceptation d'un mot
 *
 * Fonction qui indique l'acceptation d'un mot donné
 * pour l'automate courant - mode récursif
 *
 * \param at Automate d'étude
 * \param str mot donné
 * \param position_courante
 *
 * \return VRAI si le mot est accepté, FAUX sinon
 */
bool Accept_rec(const sAutoNDE& at, string str, int position_courante){

    bool accepter = false;
    int i=0;

    if(str.compare("") != 0){
        while(i<at.trans[position_courante].size() && accepter == false){
            //etat_t deplacements_possibles = i;
            string deplacement(1,(char)(i%(122-97+1)+97));//Transformation ASCII
            if(deplacement.compare(0,1, str, 0,1) == 0){//compare les char de 0 à 1 pour deplacement et de 0 à 1 pour str
                
                set<etat_t>::iterator k = at.trans[position_courante][i].begin();
                while(k != at.trans[position_courante][i].end() && !accepter) {
                    etat_t element = *k;
                    accepter = Accept_rec(at, str.erase(0,1),element);
                    k++;
                }

            }

            set<etat_t>::iterator epk = at.epsilon[position_courante].begin();
            while(epk != at.epsilon[position_courante].end() && !accepter) {
                etat_t ep_element = *epk;
                accepter = Accept_rec(at, str,ep_element);
                epk++;
            }

            i++;
        }

    }else{
       for (set<etat_t>::iterator f = at.finaux.begin(); f != at.finaux.end(); f++) {
            etat_t element_final = *f;

            if(position_courante == element_final){
                accepter = true;
            }
        }
    }
    return accepter;
}

/*!
 * \brief Acceptation d'un mot
 *
 * Fonction qui indique l'acceptation d'un mot donné
 * pour l'automate courant - fonction appel pour la commande -acc
 *
 * \param at Automate d'étude
 * \param str mot donné
 *
 * \return VRAI si le mot est accepté, FAUX sinon
 */
bool Accept(const sAutoNDE& at, string str){
    EstDeterministe(at);
    return Accept_rec(at, str, at.initial);
}


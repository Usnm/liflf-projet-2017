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

}

////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c){
  //TODO définir cette fonction

  etatset_t r;

  return r;
}

////////////////////////////////////////////////////////////////////////////////
///bin\Debug\liflf-projet-2017.exe -acc exemples/AD1.txt ab//////
bool Accept_rec(const sAutoNDE& at, std::string str, int position_courante){
    bool accepter = false;
    if(str.compare("") != 0){
        //std::cout << "trans : " << at << std::endl;
         //std::cout << "trans[] : " << at.trans << std::endl;
       // std::cout << "initial : " << position_courante << std::endl;
        //std::cout << "initial {} : " << at.trans[position_courante] << std::endl;
        for (int i=0; i<at.trans[position_courante].size(); i++ )
        {
            //etat_t deplacements_possibles = i;
            std::string deplacement(1,(char)(i%(122-97+1)+97));//Transformation ASCII
            //std::cout << "test test  : " << deplacement << " dplcmt : str " << str[0] << std::endl;
            if(deplacement.compare(0,1, str, 0,1) == 0){//compare les char de 0 à 1 pour deplacement et de 0 à 1 pour str
                //std::cout << "--- : " << deplacement << " dplcmt : str " << str[0] << std::endl;
                for (std::set<etat_t>::iterator k = at.trans[position_courante][i].begin(); k != at.trans[position_courante][i].end(); k++) {
                   etat_t element = *k;
                   accepter = Accept_rec(at, str.erase(0,1),element);
                }
            }
            //std::cout << "deplacements_possibles : " << deplacement << " => " << i << std::endl;
        }
    }else{
       for (std::set<etat_t>::iterator f = at.finaux.begin(); f != at.finaux.end(); f++) {
            etat_t element = *f;
            if(position_courante == element){
                accepter = true;
            }
        }
    }
    return accepter;
}
bool Accept(const sAutoNDE& at, std::string str){
    return Accept_rec(at, str, at.initial);
}

//******************************************************************************

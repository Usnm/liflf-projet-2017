//******************************************************************************

#include <iostream>
#include <algorithm>

#include "Accept.h"
#include "FA_tools.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////////

bool EstDeterministe(const sAutoNDE& at){
    bool estDeter = true;


    for(int nbe = 0; nbe < at.nb_etats; nbe++){

        if(at.epsilon[nbe].size() != 0 ){

           estDeter = false;
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

bool Accept(const sAutoNDE& at, string str){
    EstDeterministe(at);
    return Accept_rec(at, str, at.initial);
}


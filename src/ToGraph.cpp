//******************************************************************************

#include "ToGraph.h"
#include <iostream>
#include <fstream>

using namespace std;



////////////////////////////////////////////////////////////////////////////////

bool ToGraph(sAutoNDE& at, std::string path){
  //TODO définir cette fonction
        ofstream fichier(path.c_str(), ios::out | ios::trunc);
            if(fichier){

        fichier <<"digraph finite_state_machine {"<< endl;
        fichier <<" rankdir=LR;"<< endl;
        fichier <<" size=\"10,10\"" <<endl<<endl;

        fichier <<" node[shape = doublecircle];";
        for(etatset_t::iterator it=at.finaux.begin();it!=at.finaux.end();it++)
        {
            fichier << (*it) << " " ;
        }
        fichier << endl;

        fichier <<" node[shape = point]; q;" <<endl;
        fichier <<" node[shape = circle];" <<endl <<endl;
        fichier <<" q -> "<< at.initial<<";" <<endl;

        for(size_t i=0 ; i<at.trans.size();i++){
            for(size_t j=0 ; j<at.trans[i].size();j++){
                for(etatset_t::iterator iti=at.trans[i][j].begin(); iti!=at.trans[i][j].end();iti++){
                    fichier<<"  "<< i << " -> " << *iti <<" " << "[label=\"" << (char)(j+ASCII_A)<< "\"];" <<endl;
                }
            }
        }

        for(size_t i=0;i<at.epsilon.size(); i++){
            for(etatset_t::iterator iti=at.epsilon[i].begin(); iti !=at.epsilon[i].end(); iti++){
                fichier<< " \t" << i << "->" << *iti<<" " << "[label = \"ε\"];" <<endl;
            }
        }

        fichier << "}";
        fichier.close();

        }

        else {
            cerr <<"Erreur à l'ouverture ! " <<endl;
        }

        return false;

        }

//******************************************************************************
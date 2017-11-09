//******************************************************************************

#include "ToGraph.h"

#include <iostream>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

bool ToGraph(sAutoNDE& at, string path){

    //TODO définir cette fonction
    ofstream file(path, ios::out | ios::trunc);
    if(file) {
        file << "digraph finite_state_machine {" << endl;
        file << "\trankdir=LR;" << endl;
        file << "\tsize=\"10,10\"" << endl << endl;

        file << "\tnode [shape = doublecircle];";
        for(etatset_t::iterator it=at.finaux.begin(); it != at.finaux.end(); it++){
            file << *it << " ";
        }
        file << "\tnode [shape = point ]; q;" << endl;
        file << "\tnode [shape = circle];" << endl << endl;

        file << "\tq -> " << at.initial << endl;

        for(size_t i = 0; i <= at.trans.size(); i++){
            for(size_t j = 0; j <= at.trans[i].size(); j++){
                for(etatset_t::iterator it = at.trans[i][j].begin(); it != at.trans[i][j].end(); it++)
                    file << "\t" << i << " -> " << *it << " [label = \"" << (j+ASCII_A) << "\"];" << endl;
            }
        }
        file << endl;

        for(size_t i = 0; i <= at.epsilon.size(); i++) {
            for(etatset_t::iterator it = at.epsilon[i].begin(); it != at.epsilon[i].end(); it++)
                file << "\t" << i << " -> " << *it << " [label = \"ε\"];" << endl;
        }
        file << endl;

        file << "}";
        file.close();

        return true;
    }
    else {
        cout << "Impossible d'ouvrir le fichier" << endl;
        return false;
    }
}

//******************************************************************************

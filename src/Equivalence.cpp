//******************************************************************************

#include <iostream>
#include <cassert>

#include "Equivalence.h"
#include "FA_tools.h"

////////////////////////////////////////////////////////////////////////////////

std::string Automate2ExpressionRationnelle(sAutoNDE at){
	//TODO définir cette fonction

	std::string sr;
	sAutoNDE r = ArrangementAutomate(at);

	std::vector<std::vector<std::set<std::string>> > r1;
	std::vector<std::set<std::string>> t;
	t.push_back({"a|b"});
	r1.push_back(t);
	std::cout << r.trans << std::endl;
	std::set<std::string>::iterator i = r1[0][0].begin();
	std::string s =  *i;
	sr = s;
	return sr;
}

sAutoNDE ArrangementAutomate(sAutoNDE at){
	//TODO définir cette fonction
	sAutoNDE r;
	r = at;

	//ajout noeud de départ
	std::vector<etatset_t> noeudInit_Fin;
	etatset_t vide = {};
	noeudInit_Fin.push_back(vide);
	noeudInit_Fin.push_back(vide);
	r.trans.insert(r.trans.begin(),noeudInit_Fin);

	//ajout noeud de fin
	r.trans.push_back(noeudInit_Fin);

	//modification epsilon et noeud de depart et de fin
	r.epsilon.insert(r.epsilon.begin(), {r.initial+1});
	r.epsilon.push_back({});
	r.nb_etats += 2;
	r.finaux = {r.nb_etats-1};//init finaux

  	for (std::set<etat_t>::iterator f = at.finaux.begin(); f != at.finaux.end(); f++) {
	    etat_t element_final = *f;
	    r.epsilon[element_final+1].insert(r.nb_etats-1);
	}

	return r;
}


////////////////////////////////////////////////////////////////////////////////

bool PseudoEquivalent(const sAutoNDE& a1, const sAutoNDE& a2, unsigned int word_size_max) {
  //TODO définir cette fonction

  return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Equivalent(const sAutoNDE& a1, const sAutoNDE& a2) {
  //TODO définir cette fonction

  return true;
}

//******************************************************************************

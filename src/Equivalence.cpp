//******************************************************************************

#include <iostream>
#include <cassert>
#include <regex>
#include <math.h>

#include "Equivalence.h"
#include "Accept.h"
#include "FA_tools.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//pour eviter de la calculer a chaque boucle 
std::regex reg ("[(]([^ ]*)[)]");//selection de tous ce qu'il y à entre ()

std::string Automate2ExpressionRationnelle(sAutoNDE at){
	//TODO définir cette fonction

	sAutoNDE r = ArrangementAutomate(at);

	std::vector<std::set<std::string>> r1;
	r1 = createTable3D(r);

	// std::cout << at.trans << std::endl;
	// std::cout << "r1 : " << r1 << std::endl;
	//std::set<std::string>::iterator i = r1[1][0].begin();
	//std::string s =  *i;
	//std::cout << s << std::endl;
	// std::cout << r.epsilon << std::endl;
	// std::vector<std::set<std::string>> rijk = Rijk(r1, 1);
	// std::cout << rijk << std::endl;
	// calculeExpressions(r1, rijk, 1);
	// std::cout << r1 << std::endl;

	while(r1.size()>2){
		std::vector<std::set<std::string>> rijk = Rijk(r1, 1);
		calculeExpressions(r1, rijk, 1);
		//std::cout << r1 << std::endl;

	}
	std::set<std::string>::iterator i = r1[0].begin();
	std::string s =  *i;
	// std::cout  << std::endl;
	// std::cout  << std::endl;
	std::cout << "Expression rationnelle résultante     :" << s.substr(1) << std::endl;

	return s.substr(1);
}


std::vector<std::set<std::string>> Rijk(std::vector<std::set<std::string>> & v, unsigned int pointSuppr){
	std::vector<std::set<std::string>> r;

	std::set<std::string> prec, suiv, ptSuppr;

	for(unsigned int i = 0; i < v.size(); i++) {
	std::vector<std::set<std::string>> t;
        for(std::set<std::string>::iterator k = v[i].begin(); k != v[i].end(); k++) {
            std::string element = *k;
        	if(i == pointSuppr && element.compare(0,1,std::to_string(pointSuppr),0,1) != 0){
				suiv.insert({element});
			}else if(i == pointSuppr && element.compare(0,1,std::to_string(pointSuppr),0,1) == 0){
				ptSuppr.insert({element});
			}else if(i != pointSuppr && element.compare(0,1,std::to_string(pointSuppr),0,1) == 0){
				prec.insert({std::to_string(i)+element.substr (1,element.size()-1)});
			}
        }

	}

	r.push_back(prec);
	r.push_back(suiv);
	r.push_back(ptSuppr);
	return r;
}

void calculeExpressions(std::vector<std::set<std::string>> & v, std::vector<std::set<std::string>> & rijk, unsigned int pointSuppr){
	//parcours prec
		std::set<std::string> expr;

	for(std::set<std::string>::iterator i = rijk[0].begin(); i != rijk[0].end(); i++) {
		std::string element_i = *i;
		std::string stPrec = "";
		std::string stPt = "";
		std::string stSuiv = "";
		//unsigned int prec = std::stoi(element_i.substr(0,1));

		stPrec = verifExpr(rijk, element_i, "prec");
		

		//ptSuppr
		for(std::set<std::string>::iterator k = rijk[2].begin(); k != rijk[2].end(); k++) {
			std::string element_k = *k;
			stPt = verifExpr(rijk, element_k, "pt");
			//suiv

			for(std::set<std::string>::iterator j = rijk[1].begin(); j != rijk[1].end(); j++) {
				std::string element_j = *j;
				stSuiv = verifExpr(rijk, element_j, "suiv");
				//unsigned int suiv = std::stoi(element_j.substr(0,1));
				expr.insert(stPrec+stPt+stSuiv+element_j.substr(0,1));
			}

		}
		
	}
	//std::cout << expr << std::endl;
	insertTable3D(v, expr, pointSuppr);
}
void insertTable3D(std::vector<std::set<std::string>> & v, std::set<std::string> expr, unsigned int pointSuppr)
{
	for(std::set<std::string>::iterator i = expr.begin(); i != expr.end(); i++) {
		std::string element_i = *i;
		unsigned int prec = std::stoi(element_i.substr(0,1));
		std::string suiv = element_i.substr(element_i.size()-1,1);

		for(std::set<std::string>::iterator j = v[prec].begin(); j != v[prec].end(); j++){
			std::string element_j = *j;
			unsigned int prec_j = std::stoi(element_j.substr(0,1));
			unsigned int suiv_j = std::stoi(suiv);
			if(prec_j == pointSuppr ){//on supprime les liaisons vers le noeud qu'on supprime
				v[prec].erase(element_j);
			}
			if(prec_j == suiv_j){
				element_i = std::to_string(prec) + element_j.substr(1) + "|" + element_i.substr(1);
				v[prec].erase(element_j);
			}

		}

		v[prec].insert(suiv+element_i.substr(1, element_i.size()-2));
	}

	//update des noeuds
	for(unsigned int ni = 0; ni < v.size(); ni++) {
		for(std::set<std::string>::iterator nj = v[ni].begin(); nj != v[ni].end(); nj++){
			std::string element_nj = *nj;
			v[ni].erase(element_nj);
			unsigned int new_prec = std::stoi(element_nj.substr(0,1));
			element_nj = std::to_string(new_prec-1) + element_nj.substr(1);
			v[ni].insert(element_nj);
		}
	}

	v.erase(v.begin()+pointSuppr);

}

std::string verifExpr(std::vector<std::set<std::string>> & rijk, std::string element, std::string condition)
{
	std::string s = element;
	s = std::regex_replace (s,reg,"");
	if(condition.compare("prec") == 0){
		//si l'eleement precedent n'est pas e et qu'il y a un suivant ou une boucle
		if((rijk[1].empty() && rijk[2].empty()) || element.substr(1).compare("e") != 0){
			//si on a un 'ou'
			//std::cout << s << std::endl;
			if (s.find('|') != std::string::npos){

			    return "("+element + ").";
			}
			else{
			    return element + ".";
			}
		}else{
			return element.substr(0,1);
		}

	}else if(condition.compare("pt") == 0){
		if (s.find('|') != std::string::npos){

		    return "("+element.substr(1) + ")*";
		}
		else{
		    return element.substr(1) + "*";
		}

	}else if(condition.compare("suiv") == 0){
		if (s.find('|') != std::string::npos){

		    return "("+element.substr(1) + ")";
		}
		else{
		    return "." + element.substr(1);
		}
		
	}
	return "erreur";
}
//permet de mettre dans un tableau 3D de string
std::vector<std::set<std::string>> createTable3D(const sAutoNDE & at)
{
	std::vector<std::set<std::string>> r;

  	for(unsigned int i = 0; i < at.trans.size(); i++) {
	std::set<std::string> t;
  		for(unsigned int j = 0; j < at.trans[i].size(); j++) {
			
        	std::string symbole(1,(char)(j%(122-97+1)+97));//Transformation ASCII

	        std::set<etat_t>::iterator k = at.trans[i][j].begin();
	        while(k != at.trans[i][j].end()) {
	            etat_t element = *k;
				t.insert(std::to_string(element)+symbole);
	            k++;
	        }
	        
	    }

	    r.push_back(t);
    }

//ajout des epsilon
    for(unsigned int e = 0; e < at.epsilon.size(); e++) {
		std::set<etat_t>::iterator epk = at.epsilon[e].begin();
	    while(epk !=  at.epsilon[e].end()) {
	        etat_t ep_element = *epk;
	        r[e].insert(std::to_string(ep_element)+"e");
	        epk++;
	    }
	}

	return r;
}

sAutoNDE ArrangementAutomate(const sAutoNDE & at)
{
	//TODO définir cette fonction
	sAutoNDE r;
	r = at;

	for(unsigned int i = 0; i < r.trans.size(); i++) {
	std::vector<std::set<std::string>> t;
  		for(unsigned int j = 0; j < r.trans[i].size(); j++) {

	        std::set<etat_t>::iterator k = r.trans[i][j].begin();
	        while(k != r.trans[i][j].end()) {
	            etat_t element = *k;
	            r.trans[i][j].erase(element);
	            r.trans[i][j].insert(element+1);
	            k++;
	        }
	        
	    }
    }

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

	std::set<std::string> sigmaEtoile;

	unsigned int nb_symbs = 0;
	unsigned int nb_lettre_max = word_size_max;

	if(a1.nb_symbs > a2.nb_symbs) { nb_symbs = a1.nb_symbs; }
	else { nb_symbs = a2.nb_symbs; }

	for(unsigned int nb_lettre = 1 ; nb_lettre <= nb_lettre_max ; ++nb_lettre) {
		std::string str(nb_lettre,0);
		unsigned int nb_poss = pow(nb_symbs , nb_lettre);

		for (unsigned int iem_poss = 0; iem_poss < nb_poss; iem_poss++) {
			int tmp = iem_poss;
			for (unsigned int i = 0; i < nb_lettre; i ++) {
				str[i] = (char)tmp%nb_symbs + ASCII_A;
				tmp = tmp / nb_symbs ;
			}
			sigmaEtoile.insert(str);
		}
	}

	for (std::set < std::string >::iterator it = sigmaEtoile.begin(); it != sigmaEtoile.end() ; ++it) {
		std::cout << "mot d'étude : " << *it << std::endl;
		if( !Accept(a1, *it) ==  Accept(a2, *it))
			return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Equivalent(const sAutoNDE& a1, const sAutoNDE& a2) {
    if(!EstDeterministe(a1) || !EstDeterministe(a2)){
        cout << "Equivalence : Attention, les automates doivent etre deterministes." << endl;
        return false;
    }

    if(a1.nb_symbs != a2.nb_symbs){
        cout << "Le nombre de symboles est different" << endl;
        return false;
    }
    if(a1.nb_etats != a2.nb_etats){
        cout << "Le nombre d'etats est different" << endl;
        return false;
    }
    if(a1.nb_finaux != a2.nb_finaux){
        cout << "Le nombre d'etats finaux est different" << endl;
        return false;
    }
    map<etat_t, etat_t> correspA1, correspA2;

    etatset_t tmpLsEtat; // liste temporaire contenant tous les états à traiter
    etatset_t tmpLsEtat2;
    tmpLsEtat.insert(a1.initial);
    correspA1.insert(pair<etat_t, etat_t>(a1.initial, a2.initial)); // correspondance entre les noms de l'automate 1 à 2
    correspA2.insert(pair<etat_t, etat_t>(a2.initial, a1.initial)); // correspondance entre les noms de l'automate 2 à 1
    cout << "Renommage des etats :" << endl;
    cout << " - etat " << a1.initial << " (initial) --> " << a2.initial << endl;
    do{
        tmpLsEtat2.clear();
        for(etatset_t::iterator it = tmpLsEtat.begin(); it != tmpLsEtat.end(); it++){
            for(unsigned int sym=0; sym < a1.nb_symbs; sym++){
                etat_t tmpEtatArrA1 = *(a1.trans[*it][sym].begin());
                etat_t tmpEtatArrA2 = *(a2.trans[correspA1.find(*it)->second][sym].begin());
                map<etat_t, etat_t>::iterator res = correspA1.find(tmpEtatArrA1);
                if(res == correspA1.end()){ // si on est jamais allé dans cet état
                    // si l'état actuel est déjà connu dans l'automate 2 alors qu'il ne l'ai pas dans l'automate 1
                    if(correspA2.insert(pair<etat_t, etat_t>(tmpEtatArrA2, tmpEtatArrA1)).second == false){
                        cout << "Automate 1 : De l'etat " << res->second << " par '" << (char)(ASCII_A+sym) << "' ne correspond pas a l'automate 2." << endl;
                        return false;
                    }
                    cout << " - etat " << tmpEtatArrA1 << " --> " << tmpEtatArrA2 << endl;
                    correspA1.insert(pair<etat_t, etat_t>(tmpEtatArrA1, tmpEtatArrA2)); // Insert les nouveau états connus
                    tmpLsEtat2.insert(tmpEtatArrA1);
                }
                else{
                    if(res->second != tmpEtatArrA2){ // si les états ne correspondent pas
                        cout << "Automate 1 : De l'etat " << res->second << " par '" << (char)(ASCII_A+sym) << "' ne correspond pas a l'automate 2." << endl;
                        return false;
                    }
                }
            }
            // compare les états finaux
            if((a1.finaux.find(*it) != a1.finaux.end()) != (a2.finaux.find(correspA1.find(*it)->second) != a2.finaux.end())){
                cout << "Les etats finaux de l'automate 1 et l'automate 2 ne sont pas les memes : " << *it << endl;
                return false;
            }
        }
        tmpLsEtat = tmpLsEtat2;
    }while(!tmpLsEtat.empty()); // tant qu'on à pas fait tous les états
    cout << " - Les etats finaux sont les memes" << endl;
    cout << "\t ==> Les automates sont egaux" << endl;
    return true;
}

//******************************************************************************

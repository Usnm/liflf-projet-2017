//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at){
	
	sAutoNDE r;
	
	if(!EstDeterministe(at)){
		etatset_t etat_init = {at.initial};
		Fermeture(at,etat_init);

		std::string sCourant;
		symb_t symb;
		std::set<std::string> noeuds;
		unsigned int i=0;

		sCourant = etatsString(creation_nouveau_point(at, etat_init, '\0'));
		noeuds.insert(sCourant);
		
		std::set<std::string>::iterator itNoeuds = noeuds.begin();
		do{
			
			//parcours des symbols
			for(unsigned int j = 0; j < at.nb_symbs; ++j){

				/*
				*creation du nouveau noeuds et ajout dans le set de tous les nouveaux noeuds
				*/
			 	symb = (char)(j%(122-97+1)+97);

				sCourant = etatsString(creation_nouveau_point(at, to_etatset_t(*itNoeuds), symb));
				
				if(sCourant.compare("") == 0){//creation de l'etat "sortie"
					sCourant = std::to_string(at.nb_etats +1);
				}

				noeuds.insert(sCourant);//creation du nouveau noeuds du nouveau
			
				/*
				*recherche de l'indice du noeud pointé par la liaison
				*/
				int k = 0;
				std::set<std::string>::iterator itRecherche = noeuds.begin();

		   		while(itRecherche != noeuds.end()){

		   			std::string noeudsRecherche = *itRecherche;
		   			if(noeudsRecherche.compare(sCourant) == 0){
		   				etatset_t monK = {(long unsigned int )k};

		   				if(i >= r.trans.size()){
		   					r.trans.resize(i+1);
		   				}

	  					r.trans[i].insert(r.trans[i].end(),monK);

		   			}
	    			k++;
	    			itRecherche++;
	    		}
			}

			i++;
		    itNoeuds++;

		}while(itNoeuds != noeuds.end() );
		
		calculEtatFinaux(at, r, noeuds);

		/*r.nb_etats = r.trans.size();
		r.nb_symbs = at.nb_symbs;*/
		r.initial = at.initial;
		r.nb_etats = r.trans.size();
		r.nb_symbs = at.nb_symbs;
        	r.nb_finaux = r.finaux.size();
	}

  return r;
}

/*
* Fonction qui rajoute les etats finaux de r
*/
void calculEtatFinaux(const sAutoNDE& at, sAutoNDE& r, const std::set<std::string>& noeuds)
{
	int i = 0;
	for (std::set<std::string>::iterator itFinaux = noeuds.begin(); itFinaux != noeuds.end(); ++itFinaux)
	{
		etatset_t itF = to_etatset_t(*itFinaux);
		if(isFinal(at, itF)){
			r.finaux.insert(i);
			//r.nb_finaux +=1;
		}
		i++;
	}

}

/*
* Fonction qui verifie qu'un etat est final
*/
bool isFinal(const sAutoNDE& at, const etatset_t& e)
{
	bool isF = false;
	for (std::set<etat_t>::iterator itFinaux = e.begin(); itFinaux != e.end(); ++itFinaux)
	{
		if(at.finaux.find(*itFinaux ) != at.finaux.end()){
			isF = true;
		}
	}
	return isF;
}
/*
* on donne un etatset_t et cette fonction le converti 
* en string avec comme séparateur le character '-'
*/
std::string etatsString(const etatset_t& e)
{
	std::string etats_string = "";
	for (std::set<etat_t>::iterator itE = e.begin(); itE != e.end(); ++itE)
	{
		if(etats_string.compare("") == 0){
			etats_string = std::to_string(*itE);
		}else{
			etats_string = etats_string+"-"+std::to_string(*itE);
		}
	}

	return etats_string;
}

/*
* on donne un string et cette fonction le converti 
* en etatset_t apres avoir supprimé le séparateurs '-'
*/
etatset_t to_etatset_t(std::string s)
{
	std::string::size_type sz;   // alias de size_t
	etatset_t result;
	std::string delimiter = "-";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    result.insert(std::stol (token,&sz));
	    s.erase(0, pos + delimiter.length());
	}
	result.insert(std::stol (s,&sz));
	return result;
}


/*
* va creer des etats grace a la fonction parcours
*/
etatset_t creation_nouveau_point(const sAutoNDE& at, const etatset_t& e, symb_t c1){
	etatset_t result = {};
	
	for (std::set<etat_t>::iterator itE = e.begin(); itE != e.end(); ++itE)
	{
		etat_t oneByOne_e = *itE;
		if(c1 == '\0'){//si avec le mot vide
			result.insert(oneByOne_e);
		}
		
		 etatset_t parcours2 = parcours(at, result, oneByOne_e, c1);
		 result.insert(parcours2.begin(), parcours2.end());

		
	}
	return result;
	
}


/*
* va parcourir l'etatset_t qu'on lui fourni et le determiniser
* ptsC = noeud courant
* cC = symbole courant
* position = etatset_t que l'on va determiniser
*/
etatset_t parcours(const sAutoNDE& at, const etatset_t& position, const etat_t& ptsC, symb_t cC)
{
	etatset_t result;
	/**************************************************************************
	* ici on parcour tous les epsilons
	*/
	if(cC != '\0'){
		result = {ptsC};
		Fermeture(at,result);
		result = verifLiaisons(at, result, cC);//on retire tous les point qui n'ont pas de delta avec le symbole courant

		/*******************************************************************************************************************
		* ici a partir des epsilon on parcours tous les delta et on range uniquement ceux qui on eu une lisaison symbol
		*/
		etatset_t deplacement_char;// etatset_t des noeuds ayant eu une liaison symbole après x epsilon
		for (std::set<etat_t>::iterator iteratorChar = result.begin(); iteratorChar != result.end(); ++iteratorChar)
		{	
			etatset_t dpl_ch = Delta(at, {*iteratorChar}, cC);
			deplacement_char.insert(dpl_ch.begin(), dpl_ch.end());
		}
		Fermeture(at,deplacement_char);//on ajoute les points qui on un epsilon apres avoir eu un symbole
		result.insert(deplacement_char.begin(), deplacement_char.end());


	}else{
		result = position;
	}
	result = verifEpsilon(at, result, ptsC);//on verifie si le premier est atteignable par un epsilon
	return result;
}

/*
* va parcourir l'etatset_t qu'on lui fourni et le verifier s'il dispose d'une liaison du symbole cC
* sinon on le retire
* cC = symbole courant
* all_Pts = noeuds que le va tester
*/
etatset_t verifLiaisons(const sAutoNDE& at, const etatset_t& all_Pts, symb_t& cC){
	etatset_t result = all_Pts;
	for(std::set<etat_t>::iterator it = all_Pts.begin(); it != all_Pts.end(); it++){
		etatset_t delta = Delta(at, {*it}, cC);
		if(delta.empty()){
			result.erase(*it);
		}
	}
	return result;
}

/*
* on verifie si le premier est atteignable par un epsilon
* puisque fermeture donne tout les point accessible de un points fourni
* y compris lui meme
*/
etatset_t verifEpsilon(const sAutoNDE& at, const etatset_t& all_Pts, const etat_t& pts_C)
{
	etatset_t result = all_Pts;
	bool isOnEpsilon = false;

	
    for(std::set<etat_t>::iterator epk = all_Pts.begin(); epk != all_Pts.end(); epk++){//parcours des points fournis
    	for (unsigned int i = 0; i < at.epsilon.size(); ++i)//parcours des epsilons
    	{
    		if(at.epsilon[*epk].find(pts_C ) != at.epsilon[*epk].end()){ //si le points courant est dans le tableau epsilon on le garde
    			isOnEpsilon = true;
    		}
    	}
    }
    if(!isOnEpsilon){//sinon on le supprime
    	result.erase(pts_C);
    }
	return result;
}

//******************************************************************************

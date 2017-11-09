//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at){
  //TODO définir cette fonction

if(!EstDeterministe(at)){
	etatset_t e;
	std::cout << "epsilon : " << at.epsilon << std::endl;
	std::cout << "at.initial : " << at.initial << std::endl;
	std::cout << "init : " <<  creation_nouveau_point(at, {at.initial}, '\0') << std::endl;
	std::cout << "test" << std::endl;
	std::cout << "b : " <<  creation_nouveau_point(at, {1}, 'b') << std::endl;
	for (int i = 0; i < at.trans.size(); ++i)
	{
		for (int j = 0; j < at.trans[i].size(); ++j)
		{
			e = {i};

			std::cout << "(" << e << ","<<(char)(j%(122-97+1)+97)<<") : " <<  creation_nouveau_point(at, {i}, (char)(j%(122-97+1)+97)) << std::endl;


			//std::cout << "Delta (at," << e << ","<<(char)(j%(122-97+1)+97)<<") : " << Delta(at, e, (char)(j%(122-97+1)+97)) << std::endl;
			//creation_nouveau_point(at, e, (char)(j%(122-97+1)+97));
		}
		
	}
	
	
	std::cout << "at.trans : " << at.trans << std::endl;

}
  sAutoNDE r;

  return r;
}

etatset_t creation_nouveau_point(const sAutoNDE& at, const etatset_t& e, symb_t c1){
	etatset_t result = {};
	//etatset_t delta = Delta(at, e, c);
	

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



etatset_t parcours(const sAutoNDE& at, const etatset_t& position, const etat_t& e, symb_t cC){
	etatset_t result = position;
	/**************************************************************************
	* ici on parcour tous les epsilons
	*/
	etatset_t deplacement_epsilons = parcours_epsilon(at, e);


	result.insert(deplacement_epsilons.begin(), deplacement_epsilons.end());
	if(cC != '\0'){


		/*******************************************************************************************************************
		* ici a partir des epsilon on parcours tous les delta
		*/
		etatset_t deplacement_char;
		for (std::set<etat_t>::iterator iteratorChar = result.begin(); iteratorChar != result.end(); ++iteratorChar)
		{
			deplacement_char = Delta(at, {*iteratorChar}, cC);
			result.insert(deplacement_char.begin(), deplacement_char.end());
		}
		/******************************************************************************************************************
		* enfin apres avoir parcouru tous les epsilon possible puis tous les delta on reparcour une fois epsilon
		*/
		etatset_t deplacement_epsilons2;
		for (std::set<etat_t>::iterator iteratorChar = result.begin(); iteratorChar != result.end(); ++iteratorChar)
		{

			deplacement_epsilons2 = parcours_epsilon(at, *iteratorChar);
			result.insert(deplacement_epsilons2.begin(), deplacement_epsilons2.end());
		}

	}
	return result;

}


etatset_t parcours_epsilon(const sAutoNDE& at, const etat_t& e){
	etatset_t result1 = {};
	etat_t next_etat = e;
	
	if(at.epsilon[next_etat].size() != 0){

		std::set<etat_t>::iterator res = result1.begin();
		do{
			std::set<etat_t>::iterator epk = at.epsilon[next_etat].begin();
		    while(epk != at.epsilon[next_etat].end()) {
	    		result1.insert(*epk);

		    	epk++;
		    }
			next_etat = *res;
		    res++;

		}while(res != result1.end() );
	}
    return result1;

}

//******************************************************************************

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

bool Accept(const sAutoNDE& at, std::string str){
	sAutoNDE at2 = at;
	bool isFinal = false;
  	//TODO définir cette fonction
	//debug
	std::cout << str << std::endl;
	std::cout << "trans 0 : " << at.trans << std::endl;
	std::cout << "finaux : " << at.finaux << std::endl;
	std::cout << "initial : " << at.initial << std::endl;

	if(str.compare("") == 0){
		//std::set<etat_t>::iterator it;
		for (auto f : at.finaux)
		{
			if(at.initial == f){
				isFinal = true;
			}
			//std::cout << "finaux2 : " << f << std::endl;
		}

		if(isFinal){
			return true;
		}else{
			return false;
		}
		//verifier que at est un etat final
		//si oui alors return true
		//sino return false
	}else{
		//parcour des elements
		//algo null a changer
		if(str[0] != 'a'){
			if(at2.initial == 0){
				at2.initial = 1;	
			}else{
				at2.initial = 0;
			}
			
		}
		
		return Accept(at2, str.erase(0,1));
	}
}

//******************************************************************************

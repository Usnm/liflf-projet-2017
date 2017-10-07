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
bool Accept(const sAutoNDE& at, std::string str){
    int position_courante = at.initial;
    while(str.compare("") != 0){
        str[0];
        std::cout << "trans : " << at << std::endl;
        std::cout << "initial : " << position_courante << std::endl;
        std::cout << "initial {} : " << at.trans[position_courante] << std::endl;

        for (int i=0; i<at.trans[position_courante].size(); i++ )
        {
            etat_t deplacements_possibles = *at.trans[position_courante][i].begin();
            //if(str[0].compare(""+(char)(deplacements_possibles%(122-97+1)+97)) == 0){

            //}
            std::cout << "deplacements_possibles : " << (char) (deplacements_possibles%(122-97+1)+97) << " => " << deplacements_possibles << std::endl;
        }
        str = str.erase(0,1);
    }


	//sAutoNDE at2 = at;
	//bool isFinal = false;
  	//TODO définir cette fonction
	//debug
	//std::cout << str << std::endl;
	//std::cout << "trans 0 : " << at.trans << std::endl;
	etat_t kkk = *at.trans[0][0].begin();
	std::cout << "trans 0000 : " << (char) (kkk%(122-97+1)+97) << std::endl;
	for (int i=0; i<at.trans.size(); i++ )
    {
        for (int j=0; j<at.trans[i].size(); j++ )
        {

            for (std::set<etat_t>::iterator k = at.trans[i][j].begin(); k != at.trans[i][j].end(); k++) {
               etat_t element = *k;
               std::cout << "trans 0 : " << element << std::endl;
            }
        }
    }
	//std::cout << "finaux : " << at.finaux << std::endl;
	//std::cout << "initial : " << at.initial << std::endl;

	//if(str.compare("") == 0){
		//std::set<etat_t>::iterator it;
		//for (auto f : at.finaux)
		//{
			//if(at.initial == f){
				//isFinal = true;
			//}
			//std::cout << "finaux2 : " << f << std::endl;
		//}

		//if(isFinal){
		//	return true;
		//}else{
		//	return false;
		//}
		//verifier que at est un etat final
		//si oui alors return true
		//sino return false
	//}else{
		//parcour des elements
		//algo null a changer
		//if(str[0] != 'a'){
			//if(at2.initial == 0){
			//	at2.initial = 1;
			//}else{
			//	at2.initial = 0;
			//}

		//}
		return false;
		//return Accept(at2, str.erase(0,1));
	//}
}

//******************************************************************************

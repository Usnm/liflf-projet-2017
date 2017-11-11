//******************************************************************************
#ifndef DETERMINIZE_H
#define DETERMINIZE_H
//******************************************************************************

#include "FA_types.h"

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at);
void calculEtatFinaux(const sAutoNDE& at, sAutoNDE& r, const std::set<std::string>& noeuds);
bool isFinal(const sAutoNDE& at, const etatset_t& e);
std::string etatsString(const etatset_t& e);
etatset_t to_etatset_t(std::string s);
etatset_t creation_nouveau_point(const sAutoNDE& at, const etatset_t& e, symb_t c);
etatset_t parcours(const sAutoNDE& at, const etatset_t& position, const etat_t& e, symb_t cC);
etatset_t verifLiaisons(const sAutoNDE& at, const etatset_t& result, symb_t& cC);
etatset_t verifEpsilon(const sAutoNDE& at, const etatset_t& all_Pts, const etat_t& pts_C);
//******************************************************************************
#endif // DETERMINIZE_H
//******************************************************************************

//******************************************************************************
#ifndef ACCEPT_H
#define ACCEPT_H
//******************************************************************************

#include "FA_types.h"

////////////////////////////////////////////////////////////////////////////////

bool EstDeterministe(const sAutoNDE& at);

////////////////////////////////////////////////////////////////////////////////

void Fermeture(const sAutoNDE& at, etatset_t& e);

////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c);

////////////////////////////////////////////////////////////////////////////////
bool Accept_rec(const sAutoNDE& at, std::string str, int position_courante);

bool Accept(const sAutoNDE& at, std::string str);

//******************************************************************************
#endif // ACCEPT_H
//******************************************************************************

//******************************************************************************
#ifndef EQUIVALENCE_H
#define EQUIVALENCE_H
//******************************************************************************

#include "FA_types.h"

////////////////////////////////////////////////////////////////////////////////

std::string Automate2ExpressionRationnelle(sAutoNDE at);

////////////////////////////////////////////////////////////////////////////////
std::vector<std::set<std::string>>  createTable3D(const sAutoNDE & at);

std::vector<std::set<std::string>> Rijk(std::vector<std::set<std::string>> & v, unsigned int pointSuppr);

void calculeExpressions(std::vector<std::set<std::string>> & v, std::vector<std::set<std::string>> & rijk, unsigned int pointSuppr);

void insertTable3D(std::vector<std::set<std::string>> & v, std::set<std::string> expr, unsigned int pointSuppr);

std::string verifExpr(std::vector<std::set<std::string>> & rijk, std::string element, std::string condition);

sAutoNDE ArrangementAutomate(const sAutoNDE & at);

////////////////////////////////////////////////////////////////////////////////

// détermine la pseudo équivalence par comparaison de tous les mots de Sigma* de longueur < à word_size_max
bool PseudoEquivalent(const sAutoNDE& a1, const sAutoNDE& a2, unsigned int word_size_max);

////////////////////////////////////////////////////////////////////////////////

// détermine l'équivalence par "égalité" des automates :
//   - même nombre d'états
//   - même état initial
//   - mêmes états finaux
//   - même table de transition
// à un renommage des états près
bool Equivalent(const sAutoNDE& a1, const sAutoNDE& a2);

//******************************************************************************
#endif // EQUIVALENCE_H
//******************************************************************************

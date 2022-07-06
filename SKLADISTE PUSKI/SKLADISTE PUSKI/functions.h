#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataType.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajPusku(const char* const);
void* ucitajPuske(const char* const);
void ispisiSve(const PUSKA*);
void ispisiSortirano(const PUSKA*);
void* pretraziPuske(PUSKA* const);
void azurirajPusku(PUSKA*, const char* const);
void brisanjePuske(PUSKA* const, const char* const);

#endif
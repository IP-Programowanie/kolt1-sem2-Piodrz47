#pragma once
#include "PK1_kolA.h"
namespace maski {
	enum maski {
		LICZBA =	0x0001fffe,
		ESTYMOWANA= 0x00020000,
		SYMBOL    = 0x03fc0000,
		WCZYTANA  = 0x04000000,
		OBLICZONA=  0x20000000,
		AKTYWNA  =  0x80000000

	};
}
uint32_t kompresuj(const Dane& d);
Dane dekompresuj(uint32_t);
void niski(uint32_t& inst);
bool odczytaj(uint32_t inst);
uint32_t** alokuj(uint32_t rozmiar);
void dealokuj(uint32_t**& tab);
uint32_t odczytajrozmiar(const uint32_t** tab);
void modyfikacja(uint32_t** tab, uint32_t indeks, uint32_t wartosc);
void modyfikacja(uint32_t** tab, uint32_t indeks, const Dane& wartosc);
void zapisbin(uint32_t** tab, const char* nazwa);
uint32_t** odczytbin(const char* nazwa);


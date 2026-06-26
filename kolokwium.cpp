#define _CRT_SECURE_NO_WARNINGS
#include "kolokwium.h"
uint32_t kompresuj(const Dane& d) {
	uint32_t wynik;
	uint32_t pl = ((uint32_t)(d.liczba) << 1) & maski::LICZBA;
	uint32_t pe = ((!!d.estymowana) << 17) & maski::ESTYMOWANA;
	uint32_t ps= ((uint32_t)(d.symbol) << 18) & maski::SYMBOL;
	uint32_t pw = ((!!d.wczytana) << 26) & maski::WCZYTANA;
	uint32_t po = ((!!d.obliczona) << 29) & maski::OBLICZONA;
	uint32_t pa = ((!!d.aktywna) << 31) & maski::AKTYWNA;
	wynik = pl | pe | ps | pw | po | pa;
	return wynik;
}
Dane dekompresuj(uint32_t d) {
	Dane wynik;
	wynik.liczba = (short)((d & maski::LICZBA)>>1);
	wynik.estymowana = (!!(d & maski::ESTYMOWANA));
	wynik.symbol = (char)((d & maski::SYMBOL) >> 18);
	wynik.wczytana = (!!(d & maski::WCZYTANA));
	wynik.obliczona = (!!(d & maski::OBLICZONA));
	wynik.aktywna = (!!(d & maski::AKTYWNA));
	return wynik;

}
void niski(uint32_t& inst){
	inst &= ~maski::OBLICZONA;
}
bool odczytaj(uint32_t inst){
	return !!(inst & maski::OBLICZONA);
}
uint32_t** alokuj(uint32_t rozmiar) {
	uint32_t** tablica_wsk = new uint32_t * [2];
	uint32_t* tablica = new uint32_t[rozmiar + 1]();
	tablica[0] = rozmiar;
	tablica_wsk[0] = &tablica[1];
	tablica_wsk[1] = &tablica[0];
	return tablica_wsk;
}
void dealokuj(uint32_t**& tab) {
	if (tab != nullptr) {
		delete[]tab[1];
		delete[]tab;
		tab = nullptr;
	}
}
uint32_t odczytajrozmiar( uint32_t** tab) {
	
	return *(tab[1]);
}
void modyfikacja(uint32_t** tab, uint32_t indeks, uint32_t wartosc){
	if (tab == nullptr || tab[0] == nullptr) {
		throw std::invalid_argument("pusty wskaznik");
	}
	if (indeks >= odczytajrozmiar(tab)) {
		throw std::invalid_argument("wykracza poza zakres");
	}
	tab[0][indeks] = wartosc;
}
void modyfikacja(uint32_t** tab, uint32_t indeks, const Dane& wartosc){
	modyfikacja(tab, indeks, kompresuj(wartosc));
}

void zapisbin(uint32_t** tab, const char* nazwa){
	FILE* plik = fopen(nazwa, "wb");
	if (plik == nullptr) {
		throw std::invalid_argument("plik pusty");
	}
	uint32_t rozmiar = odczytajrozmiar(tab);
	if (rozmiar > 0) {
		fwrite(tab[0], sizeof(uint32_t), rozmiar, plik);
	}
	fclose(plik);
}
uint32_t** odczytbin(const char* nazwa){
	FILE* plik = fopen(nazwa, "rb");
	if (plik == nullptr) {
		throw std::invalid_argument("plik pusty");
	}
	fseek(plik, 0, SEEK_END);
	long rozmiar = ftell(plik);
	rewind (plik);
	uint32_t** nowa_tab = alokuj(rozmiar);
	if (rozmiar > 0) {
		fread(nowa_tab[0], sizeof(uint32_t), rozmiar, plik);
	}
	fclose(plik);
	return nowa_tab;
}
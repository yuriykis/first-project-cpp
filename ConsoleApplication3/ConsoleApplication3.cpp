#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include <stdio.h>
#include "conio2.h"

int main() {
	
	klawisz k;
	int x = WSPX_PLANSZA + 1, y = WSPY_PLANSZA + 1, attr = 3, back = 0;
	char* komunikat = new char[MAX];
	komunikat = { 0 };


#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Yuriy Kis nr 169490");


	plansza_t plansza;
	
	nowa_gra(&plansza);
	int jendoz_pola = NOK;

	do {
		

		wyswietl_legende(x, y, komunikat);
		
		gotoxy(WSPX_PLANSZA, WSPY_PLANSZA);
		rysuj_plansze(&plansza, WSPX_PLANSZA, WSPY_PLANSZA);
		wyswietl_liczbe_znakow(&plansza);


		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		putch('*');

		k = pobierz_klawisz();
		if (k != WYPELNIENIE_JEDN_POL) {
			jendoz_pola = NOK;
		}

		ruch(k, zamienX(x), zamienY(y), &x, &y, &plansza, &komunikat, &jendoz_pola);

	} while (k != ESC);

	return 0;
}

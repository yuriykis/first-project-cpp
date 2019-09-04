#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "function.h"
#include <time.h>


int zamienX(int x) {
	return x - WSPX_PLANSZA;
}
int zamienY(int y) {
	return y - WSPY_PLANSZA;
}

klawisz pobierz_klawisz(void)
{
	
	int znak = getch();

	if (znak == 0) {
		znak = getch();
		if (znak == 0x48) return GORA;
		else if (znak == 0x50) return DOL;
		else if (znak == 0x4b) return LEWO;
		else if (znak == 0x4d) return PRAWO;
	}

	else {
		if (znak == 0x1b) return ESC;
		if (znak == 0x6e) return STANDARDOWE_WYPELNIENIE;
		if (znak == 0x6f) return LOSOWE_WYPELNIENIE;
		if (znak == 0x64) return REGULA_1;
		if (znak == 0x71) return REGULA_2;
		if (znak == 0x65) return REGULA_3;
		if (znak == 0x7a) return REGULA_1_PLANSZA;
		if (znak == 0x78) return REGULA_2_PLANSZA;
		if (znak == 0x63) return REGULA_3_PLANSZA;
		if (znak == 0x70) return PODPOWIEDZ;
		if (znak == 0x6b) return UKONCZENIE;
		if (znak == 0x6a) return JEDNOZNACZNE_POLA;
		if (znak == 0x77) return WYPELNIENIE_JEDN_POL;
		if (znak == 0x31) return JEDEN;
		if (znak == 0x30) return ZERO;
		if (znak == 0x72) return ZMIANA_ROZMIARU;
		if (znak == 0x73) return ZAPIS;
		if (znak == 0x6c) return ODCZYT;
		if (znak == 0x61) return AUTODETEKCJA;
		if (znak == 0x6d) return MOD;
	}

}

void nowa_gra(plansza_t* p) {
	inicjalizacja(p);
	punkty = utworz_plansze(p);
	losowe_wypelnienie(p);
}

void pisz_liczbe(int a, int x, int y) {
	char bufor[MAX];
	_itoa(a, bufor, 10);
	gotoxy(x, y);
	cputs(bufor);
}

char pobierz_znak(int x, int y) {
	return punkty[x][y].znak;
}

void wyswietl_legende(int x_p, int y_p, char* komunikat) {
	
	textbackground(BLACK);
	clrscr();
	textcolor(7);
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA);
	cputs("ESC - wyjscie z programu");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 1);
	cputs("strzalki - poruszanie");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 2);
	cputs("n - nowa gra ze standardowa plansza");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 3);
	cputs("0/1 - wpisanie odpowiedniej cyfry");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 4);
	cputs("o - losowe wypelnienie planszy");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 5);
	cputs("p - podpowiedz");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 6);
	cputs("r - zmiana rozmiaru planszy");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 7);
	cputs("d - sprawdznie reguly 1 w aktualnym punkcie (kursor)\n   Jesli nie jest spelniona, cyfra zostanie usunieta");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 9);
	cputs("z - sprawdzenie reguly 1 w calej planszy");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 10);
	cputs("q - sprawdznie reguly 2 w aktualnym punkcie (kursor)\n   Jesli nie jest spelniona, cyfra zostanie usunieta");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 12);
	cputs("x - sprawdzenie reguly 2 w calej planszy");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 13);
	cputs("e - sprawdznie reguly 3 w aktualnym punkcie (kursor)\n   Jesli nie jest spelniona, cyfra zostanie usunieta");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 15);
	cputs("c - sprawdzenie reguly 3 w calej planszy");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 16);
	cputs("k - sprawdzenie mozliwosci ukonczenia gry");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 17);
	cputs("a - automatyczna detekcja konca gry");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 17);
	cputs("j - podswietlenie jednoznacznych pol");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 18);
	cputs("w - wypelnienie jednoznacznych pol");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 19);
	cputs("s - zapisanie stanu gry");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 20);
	cputs("l - odczytanie stanu gry");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 21);
	cputs("a - tryb automatycznej detekcji konca gry");
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 22);
	cputs("Wspolzedne kursora x y: \n");
	pisz_liczbe(zamienX(x_p), WSPX_LEGENDA, WSPY_LEGENDA + 23);
	pisz_liczbe(zamienY(y_p), WSPX_LEGENDA + 4, WSPY_LEGENDA + 23);

	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 25);

	if (komunikat != NULL) {
		cputs(komunikat);
	} 
	
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 26);
	if (komunikat1 != NULL) {
		cputs(komunikat1);
	}
	
	gotoxy(WSPX_LEGENDA, WSPY_LEGENDA + 27);
	if (komunikat2 != NULL) {
		cputs(komunikat2);
	}
}

void inicjalizacja(plansza_t * p) {
	clrscr();
	gotoxy(60, 13);
	textcolor(LIGHTGRAY);
	cputs("Podaj rozmiar planszy (min 4, max 20):");
	gotoxy(60, 15);
	char tab[MAX];
	int zn, i = 0;
	do{
		tab[i] = getch();
		if (((int)tab[i] < 48 || (int)tab[i] > 57 ) && (int)tab[i] != 13){
			cputs("\nNiepoprawna wartosc. Prosze podac liczbe\n");
			continue;
		}
		else {
			putch(tab[i]);
			zn = (int)tab[i];
			i++;
		}
	} while (zn != 13);
	
	int rozmiar = atoi(tab);
	if (rozmiar % 2 == 1) {
		rozmiar--;
	}
	if (rozmiar < MIN_ROZMIAR) {
		rozmiar = 4;
	}
	else if (rozmiar > MAX_ROZMIAR) {
		rozmiar = 20;
	}

	p->rozmiar = rozmiar;

	clrscr();

}

int sprawdz_ukon(plansza_t* p) {
	int czy_ok;
	int jest_ukonczenie = OK;
	int jedynka_dostepna = NOK;
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (punkty[i][j].znak == PUSTE) {
				czy_ok = sprawdzenie_pola(p, ZNAK_1, j, i);
				if (czy_ok == NOK) {
					jedynka_dostepna = NOK;
				}
				else {
					jedynka_dostepna = OK;
				}
				czy_ok = sprawdzenie_pola(p, ZNAK_0, j, i);
				if ((jedynka_dostepna == NOK) && (czy_ok == NOK)) {
					punkty[i][j].kolor_tla = RED;
					jest_ukonczenie = NOK;
				}
				
				punkty[i][j].znak = PUSTE;
			}
		}
	} 
	komunikat1 = NULL;
	return jest_ukonczenie;
}

void jednoznaczne_pola(plansza_t* p) {
	int czy_ok;
	int jedynka_dostepna = NOK;
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (punkty[i][j].znak == PUSTE) {
				czy_ok = sprawdzenie_pola(p, ZNAK_1, j, i);
				if (czy_ok == NOK) {
					jedynka_dostepna = NOK;
				}
				else {
					jedynka_dostepna = OK;
				}
				czy_ok = sprawdzenie_pola(p, ZNAK_0, j, i);
				if ((jedynka_dostepna == OK) && (czy_ok == NOK)) {
					punkty[i][j].kolor_tla = GREEN;
				} else if ((jedynka_dostepna == NOK) && (czy_ok == OK)) {
					punkty[i][j].kolor_tla = GREEN;
				}

				punkty[i][j].znak = PUSTE;
			}
		}
	}
	komunikat1 = NULL;
}

void wypelnienie_jednoznacznych_pol(plansza_t* p) {
	int czy_ok;
	int jedynka_dostepna = NOK;
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (punkty[i][j].znak == PUSTE) {
				czy_ok = sprawdzenie_pola(p, ZNAK_1, j, i);
				if (czy_ok == NOK) {
					jedynka_dostepna = NOK;
				}
				else {
					jedynka_dostepna = OK;
				}
				czy_ok = sprawdzenie_pola(p, ZNAK_0, j, i);
				if ((jedynka_dostepna == OK) && (czy_ok == NOK)) {
					punkty[i][j].znak = ZNAK_1;
					punkty[i][j].kolor_tekstu = WHITE;
				}
				else if ((jedynka_dostepna == NOK) && (czy_ok == OK)) {
					punkty[i][j].znak = ZNAK_0;
					punkty[i][j].kolor_tekstu = WHITE;
				}
				else
					punkty[i][j].znak = PUSTE;

			}
		}
	}
	komunikat1 = NULL;
}

punkt_t** utworz_plansze(plansza_t * p){
	punkty = new punkt_t* [p->rozmiar];
	komunikat1 = NULL;
	komunikat2 = NULL;
	for (int i = 0; i < p->rozmiar; i++) {
		punkty[i] = new punkt_t[p->rozmiar];

		for (int j = 0; j < p->rozmiar; j++) {
			if (i == 0 || i == p->rozmiar - 1 || j == 0 || j == p->rozmiar - 1) {
				punkty[i][j].kolor_tekstu = LIGHTGRAY;
				punkty[i][j].znak = RAMKA;
				punkty[i][j].y = WSPY_PLANSZA + i;
				punkty[i][j].x = WSPX_PLANSZA + j;
				punkty[i][j].mod = NOK;
			}
			else {
				punkty[i][j].kolor_tekstu = DARKGRAY;
				punkty[i][j].znak = PUSTE;
				punkty[i][j].y = WSPY_PLANSZA + i;
				punkty[i][j].x = WSPX_PLANSZA + j;
				punkty[i][j].mod = OK;
			}
		}
	}
	return punkty;
}


void rysuj_plansze(plansza_t * p, int x, int y) {
	for (int i = 0; i < p->rozmiar; i++) {
		for (int j = 0; j < p->rozmiar; j++) {
			gotoxy(punkty[i][j].x, punkty[i][j].y);
			textcolor(punkty[i][j].kolor_tekstu);
			textbackground(punkty[i][j].kolor_tla);
			putch(punkty[i][j].znak);
		} gotoxy(x, y + i + 1);
	}
}

void czysc_plansze(plansza_t* p) {
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			punkty[i][j].znak = PUSTE;
			punkty[i][j].mod = OK;
			punkty[i][j].kolor_tekstu = DARKGRAY;
			punkty[i][j].kolor_tla = BLACK;
		}
	}
}

void czysc_kolory(plansza_t* p) {
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			punkty[i][j].kolor_tla = BLACK;
		}
	}
}

void ruch(klawisz k, int zmienX, int zmienY, int* x, int* y, plansza_t* p, char** komunikat, int* jednoz_pola) {
	int czy_ok;
	*komunikat = NULL;
	komunikat1 = NULL;
	czysc_kolory(p);
	czy_ok = czy_koniec(p);
	if (czy_ok) {
		czy_ok = sprawdz_plansze(p);
		if (czy_ok) {
			komunikat1 = "Gratulacje! Plansza jest uzupelniona poprawnie!";
		}
		else {
			komunikat1 = "Niestety plansza nie jest uzupelniona poprawnie. Prosze poprawic";
		}
	}
	switch (k) {
	case GORA:
		if (punkty[--zmienY][zmienX].znak == RAMKA) {
			break;
		}
		else
			(*y)--;
		break;
	case DOL:
		if (punkty[++zmienY][zmienX].znak == RAMKA) {
			break;
		}
		else
			(*y)++;
		break;
	case LEWO:
		if (punkty[zmienY][--zmienX].znak == RAMKA) {
			zmienX++;
			break;
		}
		else
			(*x)--;
		break;
	case PRAWO:
		if (punkty[zmienY][++zmienX].znak == RAMKA) {
			zmienX--;
			break;
		}
		else
			(*x)++;
		break;
	case STANDARDOWE_WYPELNIENIE:
		*x = WSPX_PLANSZA + 1;
		*y = WSPY_PLANSZA + 1;
		standardowe_wypelnienie(p);
		break;
	case LOSOWE_WYPELNIENIE:
		czysc_plansze(p);
		losowe_wypelnienie(p);
		komunikat1 = NULL;
		break;
	case JEDEN:
		if (punkty[zmienY][zmienX].mod == NOK) {
			*komunikat = "Nie mozna modyfikowac wybranego pola";
			break;
		}
		else {
			punkty[zmienY][zmienX].kolor_tekstu = WHITE;
			punkty[zmienY][zmienX].znak = ZNAK_1;
			if (autodetekcja == OK) {
				czy_ok = sprawdz_ukon(p);
				czysc_kolory(p);
				if (czy_ok == NOK) {
					komunikat2 = "Brak mozliwosci ukonczenia gry";
				}
				else {
					komunikat2 = NULL;
				}
			}
		}
		break;
	case ZERO:
		if (punkty[zmienY][zmienX].mod == NOK) {
			*komunikat = "Nie mozna modyfikowac wybranego pola";
			break;
		}
		else {
			punkty[zmienY][zmienX].kolor_tekstu = WHITE;
			punkty[zmienY][zmienX].znak = ZNAK_0;
			if (autodetekcja == OK) {
				czy_ok = sprawdz_ukon(p);
				czysc_kolory(p);
				if (czy_ok == NOK) {
					komunikat2 = "Brak mozliwosci ukonczenia gry";
				}
				else {
					komunikat2 = NULL;
				}
			}
		}
		break;
	case MOD:
		punkty[zmienY][zmienX].mod = OK;
		break;
	case PODPOWIEDZ:
		if (punkty[zmienY][zmienX].mod == NOK) {
			*komunikat = "Aktualne pole nie moze byc zmienione";
		}
		else
		{
			char aktualny_znak = punkty[zmienY][zmienX].znak;
			int jedynka_dostepna = NOK;
			czy_ok = sprawdzenie_pola(p, ZNAK_1, zmienX, zmienY);
			if (czy_ok) {
				jedynka_dostepna = OK;
			}
			czy_ok = sprawdzenie_pola(p, ZNAK_0, zmienX, zmienY);
			if (jedynka_dostepna == OK && czy_ok == OK) {
				punkty[zmienY][zmienX].znak = aktualny_znak;
				if (aktualny_znak == PUSTE) {
					punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
				}
				*komunikat = "W tym polu mozesz wpisac 1 lub 0";
			}
			else if (jedynka_dostepna == OK && czy_ok == NOK) {
				punkty[zmienY][zmienX].znak = aktualny_znak;
				if (aktualny_znak == PUSTE) {
					punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
				}
				*komunikat = "W tym polu mozesz wpisac tylko 1";
			}
			else if (jedynka_dostepna == NOK && czy_ok == OK) {
				punkty[zmienY][zmienX].znak = aktualny_znak;
				if (aktualny_znak == PUSTE) {
					punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
				}
				*komunikat = "W tym polu mozesz wpisac tylko 0";
			}
			else
			{
				punkty[zmienY][zmienX].znak = PUSTE;
				if (aktualny_znak == PUSTE) {
					punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
				}
				*komunikat = "Zadna cyfra nie jest dostepna dla aktualnego pola";
			}
		}
		break;
	case UKONCZENIE:
		sprawdz_ukon(p);
		break;
	case JEDNOZNACZNE_POLA:
		jednoznaczne_pola(p);
		*jednoz_pola = OK;
		break;
	case WYPELNIENIE_JEDN_POL:
		if (*jednoz_pola == OK) {
			wypelnienie_jednoznacznych_pol(p);
			*jednoz_pola = NOK;
			break;
		}
		else
			break;
	case ZMIANA_ROZMIARU:
		delete[] punkty;
		nowa_gra(p);
		*x = WSPX_PLANSZA + 1;
		*y = WSPY_PLANSZA + 1;
		break;
	case ZAPIS:
		zapis_gry(p);
		*komunikat = "Gra zostala zapisana";
		break;
	case ODCZYT:
		odczyt_gry(p);
		*komunikat = "Kontynuacja ostatnio zapisanej gry";
		break;
	case AUTODETEKCJA: {
		if (autodetekcja == OK) {
			autodetekcja = NOK;
			komunikat1 = "Tryb autodetekcji zostal wylaczony";
			komunikat2 = NULL;
		}
		else {
			komunikat1 = "Tryb autodetekcji zostal wlaczony";
			autodetekcja = OK;
		}
		break;
	}
	case REGULA_2:
		if (punkty[zmienY][zmienX].znak == PUSTE) {
			break;
		}
		czy_ok = reg_2_poziom(p, punkty[zmienY][zmienX].znak, zmienY);
		if (czy_ok) {
			czy_ok = reg_2_pion(p, punkty[zmienY][zmienX].znak, zmienX);
			if (czy_ok) {
				*komunikat = "Regula 2 jest spelniona w aktualnym punkcie";
			}
			else
				if (punkty[zmienY][zmienX].mod == NOK) {
					*komunikat = "Regula 2 NIE jest spelniona w aktualnym punkcie";
				}
				else
				{
					punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
					punkty[zmienY][zmienX].znak = PUSTE;
					*komunikat = "Regula 2 nie jest spelniona w aktulanym punkcie. Cyfra zostala usunieta";
				}
		}
		else
		{
			if (punkty[zmienY][zmienX].mod == NOK) {
				*komunikat = "Regula 2 NIE jest spelniona w aktualnym punkcie";
			}
			else
			{
				punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
				punkty[zmienY][zmienX].znak = PUSTE;
				*komunikat = "Regula 2 NIE jest spelniona w aktulanym punkcie. Cyfra zostala usunieta";
			}
		}

		break;
	case REGULA_3_PLANSZA:
		czy_ok = sprawdz_reg_3(p);
		if (czy_ok) {
			*komunikat = "Regula 3 jest spelniona w calej planszy";
		}
		else
			*komunikat = "Regula 3 NIE jest spelniona. Prosze poprawic";
		break;
	case REGULA_3:
		if (punkty[zmienY][zmienX].znak == PUSTE) {
			break;
		}
		czy_ok = reg_3_poziom(p, zmienY);
		if (czy_ok) {
			czy_ok = reg_3_pion(p, zmienX);
			if (czy_ok) {
				*komunikat = "Regula 3 jest spelniona w aktualnym punkcie";
			}
			else {
				if (punkty[zmienY][zmienX].mod == NOK) {
					*komunikat = "Regula 3 NIE jest spelniona w aktualnym punkcie";
				}
				else
				{
					punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
					punkty[zmienY][zmienX].znak = PUSTE;
					*komunikat = "Regula 3 NIE jest spelniona w aktualnym punkcie. Cyfra zostala usunieta";
				}
			}
		}
		else {
			if (punkty[zmienY][zmienX].mod == NOK) {
				*komunikat = "Regula 3 NIE jest spelniona w aktualnym punkcie";
			}
			else {
				punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
				punkty[zmienY][zmienX].znak = PUSTE;
				*komunikat = "Regula 3 NIE jest spelniona w aktualnym punkcie. Cyfra zostala usunieta";
			}
		}
		break;
	case REGULA_2_PLANSZA:
		czy_ok = sprawdz_reg_2(p, ZNAK_1);
		if (czy_ok) {
			czy_ok = sprawdz_reg_2(p, ZNAK_0);
			if (czy_ok) {
				*komunikat = "Regula 2 jest spelniona w calej planszy";
			}
			else
				*komunikat = "Regula 2 NIE jest spelniona. Prosze poprawic";
		}
		else
			*komunikat = "Regula 2 NIE jest spelniona. Prosze poprawic";
		break;
	case REGULA_1_PLANSZA:
		czy_ok = sprawdz_reg_1_plansza(p);
		if (czy_ok) {
			*komunikat = "Regula 1 jest spelniona w calej planszy";
		}
		else {
			*komunikat = "Regula 1 NIE jest spelniona. Prosze poprawic";
		}
		break;
	case REGULA_1:{
		char zn = pobierz_znak(zmienY, zmienX);
		if (zn == PUSTE) {
			break;
		}
		else {
			czy_ok = sprawdz_reg_1(p, zn, zmienY, zmienX);
			if (czy_ok) {
				*komunikat = "Regula 1 jest spelniona w aktulanym punkcie";
			}
			else {
				if (punkty[zmienY][zmienX].mod == NOK) {
					*komunikat = "Regula 1 NIE jest spelniona w aktulanym punkcie";
				}
				else {
					punkty[zmienY][zmienX].kolor_tekstu = DARKGRAY;
					punkty[zmienY][zmienX].znak = PUSTE;
					*komunikat = "Regula 1 NIE jest spelniona w aktulanym punkcie. Cyfra zostala usunieta";
				}
			}

		}
		break;
	}
	default:
		break;
	};
}

int czy_koniec(plansza_t* p) {
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (punkty[i][j].znak == PUSTE) {
				return NOK;
			}
		}
	}
	return OK;
}
int sprawdz_plansze(plansza_t* p) {
	int czy_ok;
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			czy_ok = sprawdzenie_pola(p, punkty[i][j].znak, j, i);
			if (czy_ok == NOK) {
				return NOK;
			}
		}
	}
	return OK;
}

int sprawdz_reg_1_plansza(plansza_t* p) {
	int czy_ok;
	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (punkty[i][j].znak == PUSTE) {
				continue;
			}
			czy_ok = sprawdz_reg_1(p, punkty[i][j].znak, i, j);
			if (czy_ok == NOK) {
				return NOK;
			}
		}
	}
	return OK;
}


int sprawdz_reg_1(plansza_t * p, char zn, int x, int y) {
	int czy_ok; //zmienna pokazuj?ca czy regu?a 1 jest spe?niona

	czy_ok = reg_1_poziom(zn, x, y);
	if (czy_ok) {
		czy_ok = reg_1_pion(zn, x, y);
		if (czy_ok) {
			return OK;
		}
		else {
			return NOK; 
		}

	} 
	else
	{
		return NOK;
	}
}

int reg_1_poziom(char zn, int i, int j) {
	
	int znak_jest = OK;

	if (punkty[i][j - 1].znak == zn) {
		znak_jest = NOK;
		if (punkty[i][j - 2].znak == zn) {
			return NOK;
		}  
	}
	if (punkty[i][j + 1].znak == zn && znak_jest == NOK) {
		return NOK;
	}

	if (punkty[i][j + 1].znak == zn) {
		if (punkty[i][j + 2].znak == zn) {
			return NOK;
		}
	}

	return OK;

}

int reg_1_pion(char zn, int i, int j) {

	int znak_jest = OK;

	if (punkty[i - 1][j].znak == zn) {
		znak_jest = NOK;
		if (punkty[i - 2][j].znak == zn) {
			return NOK;
		}
	}
	if (punkty[i + 1][j].znak == zn && znak_jest == NOK) {
		return NOK;
	}

	if (punkty[i + 1][j].znak == zn) {
		if (punkty[i + 2][j].znak == zn) {
			return NOK;
		}
	}

	return OK;

}

int sprawdz_reg_2( plansza_t * p, char zn) {
	int czy_ok;

	//sprawdzamy liczbe znakow w poszczegolnych poziomach
	for (int i = 0; i < p->rozmiar; i++) {
		czy_ok = reg_2_poziom(p, zn, i);
		if (czy_ok == NOK) {
			return NOK;
		}
	}

	
	//sprawdzamy liczbe znakow w pionie
	for (int j = 0; j < p->rozmiar; j++) {
		czy_ok = reg_2_pion(p, zn, j);
		if (czy_ok == NOK) {
			return NOK;
		}
	}
			return OK;

}

int reg_2_poziom(plansza_t* p, char zn, int i) {
	int liczba_znakow = 0;
	for (int j = 1; j < p->rozmiar - 1; j++) {
		if (punkty[i][j].znak == zn) {
			liczba_znakow++;
		}
	}
	if (liczba_znakow > (p->rozmiar - 2) / 2) {
		return NOK;
	}
	else return OK;
	
}

int reg_2_pion(plansza_t* p, char zn, int j) {
	int liczba_znakow = 0;
	for(int i = 1; i < p->rozmiar - 1; i++) {
		if (punkty[i][j].znak == zn) {
			liczba_znakow++;
		}
	}
	if (liczba_znakow > (p->rozmiar - 2) / 2) {
		return NOK;
	}
	else return OK;

}
int sprawdz_reg_3(plansza_t* p) {
	int czy_ok;
	for (int i = 1; i < p->rozmiar - 1; i++) {
		czy_ok = reg_3_poziom(p, i);
		if (czy_ok == NOK) {
			return NOK;
		}
	}

	for (int j = 1; j < p->rozmiar - 1; j++) {
		czy_ok = reg_3_pion(p, j);
		if (czy_ok == NOK) {
			return NOK;
		}
	}
	return OK;
}

int reg_3_poziom(plansza_t* p, int i) {
		int czy_ok = OK;
		char* tymczas = new char[p->rozmiar];

		for (int a = 0; a < p->rozmiar; a++) {
			tymczas[a] = punkty[i][a].znak;
			
		}

		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (i == j) {
				j++;
			}
			char* tymczas_a = new char[p->rozmiar];
			for (int a = 0; a < p->rozmiar; a++) {
				tymczas_a[a] = punkty[j][a].znak;
			}
			for (int t = 0; t < p->rozmiar; t++) {
				if (tymczas[t] != tymczas_a[t]) {
					czy_ok = OK;
					break;
				}
				else czy_ok = NOK;
			}
			delete[] tymczas_a;
			if (czy_ok == NOK) {
				delete[] tymczas;
				return NOK;
			}
		}
		
	return OK;
}

int reg_3_pion(plansza_t* p, int j) {

		int czy_ok = OK;
		char* tymczas = new char[p->rozmiar];

		for (int a = 0; a < p->rozmiar; a++) {
			tymczas[a] = punkty[a][j].znak;
		}

		for (int i = 1; i < p->rozmiar - 1; i++) {
			if (j == i) {
				i++;
			}
			char* tymczas_a = new char[p->rozmiar];
			for (int a = 0; a < p->rozmiar; a++) {
				tymczas_a[a] = punkty[a][i].znak;
			}
			for (int t = 0; t < p->rozmiar; t++) {
				if (tymczas[t] != tymczas_a[t]) {
					czy_ok = OK;
					break;
				}
				else czy_ok = NOK;
			}
			delete[] tymczas_a;
			if (czy_ok == NOK) {
				delete[] tymczas;
				return NOK;
			}
		}

	return OK;
}

void wyswietl_liczbe_znakow(plansza_t* p) {
	
	gotoxy(WSPX_PLANSZA - 12, WSPY_PLANSZA);
	cputs("L. j");
	gotoxy(WSPX_PLANSZA - 7, WSPY_PLANSZA);
	cputs("L. z");
	gotoxy(WSPX_PLANSZA - 10, WSPY_PLANSZA - 2);
	cputs("L. j");
	gotoxy(WSPX_PLANSZA - 10, WSPY_PLANSZA - 4);
	cputs("L. z");
	for (int i = 1; i < p->rozmiar - 1; i++) {
		int ile_jedynek = 0;
		int ile_zer = 0;
		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (punkty[i][j].znak == ZNAK_1) {
				ile_jedynek++;
			}
			else if (punkty[i][j].znak == ZNAK_0) {
				ile_zer++;
			}
		}
		gotoxy(WSPX_PLANSZA - 10, WSPY_PLANSZA + i);
		char* bufor = new char[5];
		_itoa(ile_jedynek, bufor, 10);
		cputs(bufor);
		gotoxy(WSPX_PLANSZA - 5, WSPY_PLANSZA + i);
		_itoa(ile_zer, bufor, 10);
		cputs(bufor);
		delete[] bufor;
	}

	for (int j = 1; j < p->rozmiar - 1; j++) {
		int ile_jedynek = 0;
		int ile_zer = 0;
		for (int i = 1; i < p->rozmiar - 1; i++) {
			if (punkty[i][j].znak == ZNAK_1) {
				ile_jedynek++;
			}
			else if (punkty[i][j].znak == ZNAK_0) {
				ile_zer++;
			}
		}
		gotoxy(WSPX_PLANSZA + j, WSPY_PLANSZA - 2);
		char* bufor = new char[5];
		_itoa(ile_jedynek, bufor, 10);
		cputs(bufor);
		gotoxy(WSPX_PLANSZA + j, WSPY_PLANSZA - 4);
		_itoa(ile_zer, bufor, 10);
		cputs(bufor);
		delete[] bufor;
	}
}

void standardowe_wypelnienie(plansza_t* p) {

	char* tab = new char[STANDARD]; //tymczasowa tablica do przechowywania standardowej planszy
	int licznik = 0;

	p->rozmiar = 14;
	delete[] punkty;
	punkty = utworz_plansze(p);

	FILE* plik = fopen("standard.txt", "r+");
		if (plik == NULL) {
			perror("Nie udalo sie otworzyc pliku");
		}
		else
		{
			for (int i = 0; i < STANDARD; i++) {
				tab[i] = fgetc(plik);
			}
		

			for (int i = 1; i < p->rozmiar - 1; i++) {
				for (int j = 1; j < p->rozmiar - 1; j++) {
					//pomijamy znak końca linii
					if (tab[licznik] == '\n') {
						licznik++;
						j--;
						continue;
					}
					
					punkty[i][j].y = WSPY_PLANSZA + i;
					punkty[i][j].x = WSPX_PLANSZA + j;
					punkty[i][j].znak = tab[licznik];


					if (punkty[i][j].znak != PUSTE) {
						punkty[i][j].mod = NOK;
						punkty[i][j].kolor_tekstu = DARKGRAY;
					}
					else {
						punkty[i][j].mod = OK;
						punkty[i][j].kolor_tekstu = DARKGRAY;
					}

					licznik++;
					komunikat1 = NULL;
				}
			} 
			delete[] tab;
		}  
		fclose(plik);

	
}

int sprawdzenie_pola(plansza_t* p, char znak, int wspx, int wspy) {
	int czy_ok;
	czy_ok = sprawdz_reg_1(p, znak, wspy, wspx);
	if (czy_ok) {
		czy_ok = reg_2_poziom(p, znak, wspy);
		if (czy_ok) {
			czy_ok = reg_2_pion(p, znak, wspx);
			if (czy_ok) {
				punkty[wspy][wspx].znak = znak;
				czy_ok = reg_3_poziom(p, wspy);
				if (czy_ok) {
					czy_ok = reg_3_pion(p, wspx);
					if (czy_ok == NOK) {
						komunikat1 = "Wpisanie innej cyfry spowoduje naruszenie reguly 3 w aktualnej kolumnie";
					}
				}
				else { 
					komunikat1 = "Wpisanie innej cyfry spowoduje naruszenie reguly 3 w aktualnym wierszu"; 
				}
			} else komunikat1 = "Wpisanie innej cyfry spowoduje naruszenie reguly 2 w aktualnej kolumnie";
		} else komunikat1 = "Wpisanie innej cyfry spowoduje naruszenie reguly 2 w aktualnym wierszu";

	}else 
		komunikat1 = "Wpisanie innej cyfry spowoduje naruszenie reguly 1";

	return czy_ok;
}

void losowe_wypelnienie(plansza_t* p) {

	float ile_min = ((p->rozmiar - 2)*(p->rozmiar - 2))*((float)MIN_PLANSZA / 100);
	float ile_max = ((p->rozmiar - 2)*(p->rozmiar - 2))*((float)MAX_PLANSZA / 100);
	int ile_pol;
	srand(time(NULL));

	ile_pol = rand() % ((int)ile_max - ((int)ile_min - 1)) + (int)ile_min;
	int czy_ok;

	for (int i = 0; i < ile_pol; i++) {

		int los = rand() % 2;
		char znak;
		
		if (los) {
			znak = ZNAK_1;
		}
		else { znak = ZNAK_0; }

		int wspx, wspy;
		wspx = rand() % (p->rozmiar - 2) + 1;
		wspy = rand() % (p->rozmiar - 2) + 1;

		if (punkty[wspy][wspx].znak != PUSTE) {
			continue;
		}

		czy_ok = sprawdzenie_pola(p, znak, wspx, wspy);
		if (czy_ok) {
			czy_ok = sprawdz_ukon(p);
		}
		czysc_kolory(p);
		
		if (czy_ok == NOK) {
			punkty[wspy][wspx].znak = PUSTE;
			punkty[wspy][wspx].mod = OK;		
			i--;
			continue;
		}
		else {
			punkty[wspy][wspx].kolor_tekstu = DARKGRAY;
			punkty[wspy][wspx].mod = NOK;
			
		}
		komunikat1 = NULL;
	}

	//sprawdzamy czy wystepuja puste wiersze, jesli tak to losujemy pole oraz liczbe i wpisujemy
	for (int i = 1; i < p->rozmiar - 1; i++) {
		int czy_puste = OK;
		for (int j = 1; j < p->rozmiar - 1; j++) {
			if (punkty[i][j].znak != PUSTE) {
				czy_puste = NOK;
				break;
			}
		}
		if (czy_puste == OK) {
			for (int q = 0; q < 1; q++) {
				int los = rand() % 2;
				char znak;

				if (los) {
					znak = ZNAK_1;
				}
				else { znak = ZNAK_0; }

				int wspx = rand() % (p->rozmiar - 2) + 1;
				czy_ok = sprawdzenie_pola(p, znak, wspx, i);
				if (czy_ok == NOK) {
					punkty[i][wspx].znak = PUSTE;
					punkty[i][wspx].mod = OK;
					q--;
					continue;
				}
				else {
					punkty[i][wspx].kolor_tekstu = DARKGRAY;
					punkty[i][wspx].mod = NOK;
					komunikat1 = NULL;
				}
			}
		}

	}

	//sprawdzamy czy wystepuja puste kolumny, jesli tak to losujemy pole oraz liczbe i wpisujemy
	for (int j = 1; j < p->rozmiar - 1; j++) {
		int czy_puste = OK;
		for (int i = 1; i < p->rozmiar - 1; i++) {
			if (punkty[i][j].znak != PUSTE) {
				czy_puste = NOK;
				break;
			}
		}
		if (czy_puste == OK) {
			for (int q = 0; q < 1; q++) {
				int los = rand() % 2;
				char znak;

				if (los) {
					znak = ZNAK_1;
				}
				else { znak = ZNAK_0; }

				int wspy = rand() % (p->rozmiar - 2) + 1;
				czy_ok = sprawdzenie_pola(p, znak, j, wspy);
				if (czy_ok == NOK) {
					punkty[wspy][j].znak = PUSTE;
					punkty[wspy][j].mod = OK;
					q--;
					continue;
				}
				else {
					punkty[wspy][j].kolor_tekstu = DARKGRAY;
					punkty[wspy][j].mod = NOK;
					komunikat1 = NULL;
				}
			}
		}

	}

}

void zapis_gry(plansza_t* p) {
	// tablica do przechowania aktualnej planszy
	int d = (p->rozmiar - 1)*(p->rozmiar - 2), licznik = 0;
	char* tab = new char[d];

	for (int i = 1; i < p->rozmiar - 1; i++) {
		for (int j = 1; j < p->rozmiar; j++) {
			if (j == p->rozmiar - 1) {
				tab[licznik] = '\n';
				licznik++;
			}
			else {
				tab[licznik] = punkty[i][j].znak;
				licznik++;
			}
		}
	}

	FILE* plik = fopen("plansza.txt", "w+");
	if (plik == NULL) {
		cputs("Nie udalo sie otworzyc pliku");
	}
	else {
		fprintf(plik, "%s", tab);
	}
	delete[] tab;
	fclose(plik);
}


void odczyt_gry(plansza_t* p) {
	char* tab = new char[MAX]; //tymczasowa tablica do przechowywania planszy
	delete[] punkty;
	int licznik = 0;
	FILE* plik = fopen("plansza.txt", "r+");
	if (plik == NULL) {
		perror("Nie udalo sie otworzyc pliku");
	}
	else
	{	//zapisujemy zawartosc pliku do tab i liczymy rozmiar
		int rozmiar = 0, rozmiar_jest = NOK;
		for (int i = 0; i < MAX; i++) {
			tab[i] = fgetc(plik);
			if (tab[i] == '\n') {
				rozmiar_jest = OK;
			}

			if (rozmiar_jest == NOK) {
				rozmiar++;
			} 		
		}

		p->rozmiar = rozmiar + 2; // dodajemy ramki
		punkty = utworz_plansze(p);

		for (int i = 1; i < p->rozmiar - 1; i++) {
			for (int j = 1; j < p->rozmiar - 1; j++) {
				//pomijamy znak końca linii
				if (tab[licznik] == '\n') {
					licznik++;
					j--;
					continue;
				}

				punkty[i][j].y = WSPY_PLANSZA + i;
				punkty[i][j].x = WSPX_PLANSZA + j;
				punkty[i][j].znak = tab[licznik];


				if (punkty[i][j].znak != PUSTE) {
					punkty[i][j].mod = NOK;
					punkty[i][j].kolor_tekstu = DARKGRAY;
				}
				else {
					punkty[i][j].mod = OK;
					punkty[i][j].kolor_tekstu = DARKGRAY;
				}

				licznik++;
				komunikat1 = NULL;
			}
		}
	}
	delete[] tab;
	fclose(plik);

}
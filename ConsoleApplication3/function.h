#pragma once
#define MAX 1000 
#define WSPX_PLANSZA 80	//wspozedna x planszy na konsoli
#define WSPY_PLANSZA 5	//wspozedna y planszy na konsoli
#define WSPX_LEGENDA 3	//wspozedna x legendy na konsoli
#define WSPY_LEGENDA 2	//wspozedna y legendy na konsoli
#define RAMKA '#'		// znak reprezentujacy ramke planszy
#define PUSTE '.'		// znak reprezentujacy puste pole na planszy
#define OK 1			//reprezentuje czy jakis warunek jest spelniony (np. czy reg 1 jest spelniona)
#define NOK 0			//reprezentuje czy jakis warunek nie jest spelniony (np. czy reg 1 nie jest spelniona)
#define STANDARD 156	// rozmiar standardowej planszy
#define ZNAK_1 '1'		//znak ktory mozna wykorzystywac w trakcie gry
#define ZNAK_0 '0'		//znak ktory mozna wykorzystywac w trakcie gry
#define MAX_PLANSZA 30	//maksymalne procentowe wypelnienie planszy
#define MIN_PLANSZA 20	//minimalne procentowe wypelnienie planszy
#define MAX_ROZMIAR 20	//maksymalny mozliwy rozmiar planszy wraz z ramka
#define MIN_ROZMIAR 4	// minimalny mozliwy rozmiar planszy wraz z ramka


enum klawisz {
	ESC,
	GORA,
	DOL,
	LEWO,
	PRAWO,
	STANDARDOWE_WYPELNIENIE,
	ZMIANA_ROZMIARU,
	REGULA_1,
	REGULA_2,
	REGULA_3,
	REGULA_1_PLANSZA,
	REGULA_2_PLANSZA,
	REGULA_3_PLANSZA,
	PODPOWIEDZ,
	UKONCZENIE,
	JEDNOZNACZNE_POLA,
	WYPELNIENIE_JEDN_POL,
	JEDEN,
	ZERO,
	LOSOWE_WYPELNIENIE,
	ZAPIS,
	ODCZYT,
	AUTODETEKCJA,
	MOD
};

struct plansza_t {
	int rozmiar;
};

struct punkt_t {
	
	char znak;
	int mod;
	int x, y;
	int kolor_tekstu;
	int kolor_tla = 0;

};
static punkt_t** punkty;
static char* komunikat1 = new char[MAX];
static char* komunikat2 = new char[MAX];
static int autodetekcja = NOK;

klawisz pobierz_klawisz(void);
int zamienX(int);
int zamienY(int);
void ruch(klawisz, int, int, int*, int*, plansza_t*, char**, int*);
void inicjalizacja(plansza_t *);
punkt_t** utworz_plansze(plansza_t *);
void rysuj_plansze(plansza_t *, int, int);
void czysc_plansze(plansza_t*);
int sprawdz_ukon(plansza_t*);
void jednoznaczne_pola(plansza_t*);
int sprawdz_reg_1_plansza(plansza_t*);
int sprawdz_reg_1(plansza_t*, char, int, int);
int reg_1_poziom(char, int, int);
int reg_1_pion( char, int, int);
int sprawdz_reg_2(plansza_t*, char);
int reg_2_poziom(plansza_t*, char, int);
int reg_2_pion(plansza_t*, char, int);
int sprawdz_reg_3(plansza_t*);
int reg_3_poziom(plansza_t*, int);
int reg_3_pion(plansza_t*, int);
void wyswietl_liczbe_znakow(plansza_t*);
void standardowe_wypelnienie(plansza_t*);
void losowe_wypelnienie(plansza_t*);
int sprawdzenie_pola(plansza_t*, char, int, int);
void wyswietl_legende(int, int, char*);
void pisz_liczbe(int, int, int);
char pobierz_znak(int, int);
void nowa_gra(plansza_t*);
void zapis_gry(plansza_t*);
void odczyt_gry(plansza_t*);
int czy_koniec(plansza_t*);
int sprawdz_plansze(plansza_t*);

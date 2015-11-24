#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;
const int A = 16;
struct rodzaj_ {
	string nazwa;
	int maszty;
	int ilosc;
};
rodzaj_ maszt2 = { "DWU-", 2 , 3 };
rodzaj_ maszt3 = { "TROJ-", 3 , 2 };
rodzaj_ maszt4 = { "CZTERO-" , 4 , 2 };
rodzaj_ maszt5 = { "PIECIO-" , 5 , 1 };

// wypelnia plansze od poczatku
void reset_pla(char pla[][A])
{
	for (int i = 0; i < A; i++)
		pla[0][i] = (char)i+64;
	for (int i = 1; i < A; i++)
		for (int j = 1; j < A; j++)
			pla[i][j] = '.';
	for (int i = 0; i < A; i++)
		pla[i][0] = (char)i+64;
}

// wyswietla tabelke
void wyswietl(char pla[][A])
{
	system("cls");
	for (int i = 0; i < A; i++)
	{
		for (int j = 0; j < A; j++)
			cout << pla[i][j];
		cout << endl;
	}
}

//sprawdza czy nie koliduje z innym statkie przy rozstawianiu, ale ju¿ po podaniu kierunku ustawiania, czyli bez poczatku statku
bool wolne(char pla[][A], int x, int y, int rodzaj, char kierunek)			// bool wolne(tablica,x,y,wielkosc,strona);
{
	if (kierunek == 'w')
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla[y - j][x] == 'o') || ((y - j) < 1) || (pla[y - j - 1][x] == 'o') || (pla[y - j - 1][x - 1] == 'o') || (pla[y - j - 1][x + 1] == 'o') || (pla[y - j][x + 1] == 'o') || (pla[y - j][x - 1] == 'o'))
				return false;	//sprawdzam czy nie jest zajete dookola
			else
				return true;
		}
	else if (kierunek == 's')
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla[y + j][x] == 'o') || ((y + j) >= A) || (pla[y + j + 1][x] == 'o') || (pla[y + j + 1][x - 1] == 'o') || (pla[y + j + 1][x + 1] == 'o') || (pla[y + j][x + 1] == 'o') || (pla[y + j][x - 1] == 'o'))
				return false;	//sprawdzam czy nie jest zajete dookola
			else
				return true;
		}
	else if (kierunek == 'a')
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla[y][x - j] == 'o') || ((x - j) < 1) || (pla[y][x - j - 1] == 'o') || (pla[y - 1][x - j - 1] == 'o') || (pla[y + 1][x - j - 1] == 'o') || (pla[y + 1][x - j] == 'o') || (pla[y - 1][x - j] == 'o'))
				return false;	//sprawdzam czy nie jest zajete dookola
			else
				return true;
		}
	else if (kierunek == 'd')
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla[y][x + j] == 'o') || ((x + j) >= A) || (pla[y][x + j + 1] == 'o') || (pla[y + 1][x + j + 1] == 'o') || (pla[y - 1][x + j + 1] == 'o') || (pla[y + 1][x + j] == 'o') || (pla[y - 1][x + j] == 'o'))
				return false;	//sprawdzam czy nie jest zajete dookola
			else
				return true;
		}
}

// rozstawia dany statek przez gracza
void rozstaw_statek(char pla[][A], int ile, int rodzaj, string nazwa)
{
	char x1;
	char y1;
	int x;
	int y;
	char kierunek;
	bool szansa;

	for (int i = 0; i < ile; i++)
	{
		x = 0;
		y = 0;
		while (x < 1 || x > A || y < 1 || y > A || pla[y][x] == 'o' || pla[y - 1][x] == 'o' || pla[y - 1][x + 1] == 'o' || pla[y - 1][x - 1] == 'o' || pla[y][x + 1] == 'o' || pla[y][x - 1] == 'o' || pla[y + 1][x + 1] == 'o' || pla[y + 1][x - 1] == 'o' || pla[y + 1][x] == 'o')	//czy nie zajete dookola
		{
			wyswietl(pla);
			cout << "ROZSTAW " << nazwa << "MASZTOWCE" << endl;
			cout << "\a" << "Podaj wspolrzedne poziome poczatku statku" << endl;
			cin >> x1;
			cout << "Podaj wspolrzedne pionowe poczatku statku" << endl;
			cin >> y1;
			x = (int)x1 - 96;
			y = (int)y1 - 96;
			if (x < 0)
				x += 32;
			if (y < 0)
				y += 32;
		}
		pla[y][x] = 'o';
		szansa = true;
		while (szansa)
		{
			szansa = false;
			wyswietl(pla);
			cout << "Klawiszami a,w,s,d ustawiaj statek" << endl;
			cin >> kierunek;
			switch (kierunek)
			{
			case 'w':
			{
				if (wolne(pla, x, y, rodzaj, kierunek))
					for (int j = 1; j < rodzaj; j++)
						pla[y - j][x] = 'o';
				else
				{
					szansa = true;
					cout << "Sprobuj jeszcze raz";
					Sleep(2500);
				}

			}
			break;
			case 's':
			{
				if (wolne(pla, x, y, rodzaj, kierunek))
					for (int j = 1; j < rodzaj; j++)
						pla[y + j][x] = 'o';
				else
				{
					szansa = true;
					cout << "Sprobuj jeszcze raz";
					Sleep(2500);
				}
			}
			break;
			case 'd':
			{
				if (wolne(pla, x, y, rodzaj, kierunek))
					for (int j = 1; j < rodzaj; j++)
						pla[y][x + j] = 'o';
				else
				{
					szansa = true;
					cout << "Sprobuj jeszcze raz";
					Sleep(2500);
				}
			}
			break;
			case 'a':
			{
				if (wolne(pla, x, y, rodzaj, kierunek))
					for (int j = 1; j < rodzaj; j++)
						pla[y][x - j] = 'o';
				else
				{
					szansa = true;
					cout << "Sprobuj jeszcze raz";
					Sleep(2500);
				}
			}
			}
			wyswietl(pla);
		}
	}
}

// rozstawianie wszystkich statkow przez gracza
void rozstaw_gracz(char pla[][A])
{
	rozstaw_statek(pla, maszt2.ilosc, maszt2.maszty, maszt2.nazwa);
	rozstaw_statek(pla, maszt3.ilosc, maszt3.maszty, maszt3.nazwa);
	rozstaw_statek(pla, maszt4.ilosc, maszt4.maszty, maszt4.nazwa);
	rozstaw_statek(pla, maszt5.ilosc, maszt5.maszty, maszt5.nazwa);
}


//sprawdza czy nie koliduje tak jak wolne_gra tylko zmienne sterujace sa cyframi
bool wolne_komp(char pla2[][A], int x, int y, int rodzaj, int kierunek)
{
	if (kierunek == 1)
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla2[y - j][x] == 'o') || ((y - j) < 1) || (pla2[y - j - 1][x] == 'o') || (pla2[y - j - 1][x - 1] == 'o') || (pla2[y - j - 1][x + 1] == 'o') || (pla2[y - j][x + 1] == 'o') || (pla2[y - j][x - 1] == 'o'))
				return false;	//sprawdzam czy jest wolne dookola
			else
				return true;
		}
	else if (kierunek == 3)
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla2[y + j][x] == 'o') || ((y + j) >= A) || (pla2[y + j + 1][x] == 'o') || (pla2[y + j + 1][x - 1] == 'o') || (pla2[y + j + 1][x + 1] == 'o') || (pla2[y + j][x + 1] == 'o') || (pla2[y + j][x - 1] == 'o'))
				return false;	//sprawdzam czy jest wolne dookola
			else
				return true;
		}
	else if (kierunek == 4)
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla2[y][x - j] == 'o') || ((x - j) < 1) || (pla2[y][x - j - 1] == 'o') || (pla2[y - 1][x - j - 1] == 'o') || (pla2[y + 1][x - j - 1] == 'o') || (pla2[y + 1][x - j] == 'o') || (pla2[y - 1][x - j] == 'o'))
				return false;	//sprawdzam czy jest wolne dookola
			else
				return true;
		}
	else if (kierunek == 2)
		for (int j = 1; j < rodzaj; j++)
		{
			if ((pla2[y][x + j] == 'o') || ((x + j) >= A) || (pla2[y][x + j + 1] == 'o') || (pla2[y + 1][x + j + 1] == 'o') || (pla2[y - 1][x + j + 1] == 'o') || (pla2[y + 1][x + j] == 'o') || (pla2[y - 1][x + j] == 'o'))
				return false;	//sprawdzam czy jest wolne dookola
			else
				return true;
		}
}
//rozstawienie danego statku przez komputer
void rozstaw_statek_komp(char pla2[][A], int ile, int rodzaj)
{
	int x;
	int y;
	int kierunek;
	bool szansa;

	srand(time(NULL));
	for (int i = 0; i < ile; i++)
	{
		x = 0;
		y = 0;
		while (x<1 || y<1 || pla2[y][x] == 'o' || pla2[y - 1][x] == 'o' || pla2[y - 1][x + 1] == 'o' || pla2[y - 1][x - 1] == 'o' || pla2[y][x + 1] == 'o' || pla2[y][x - 1] == 'o' || pla2[y + 1][x + 1] == 'o' || pla2[y + 1][x - 1] == 'o' || pla2[y + 1][x] == 'o')
		{
			x = rand() % 15 + 1;
			y = rand() % 15 + 1;
		}
		pla2[y][x] = 'o';
		szansa = true;
		while (szansa)
		{
			szansa = false;
			kierunek = rand() % 4 + 1;			// kierunek: 1-gora, 2-prawo, 3-dol, 4-lewo
			wyswietl(pla2);
			cout << kierunek << endl;
			Sleep(5000);
			if (wolne_komp(pla2, x, y, rodzaj, kierunek))
			{
				if (kierunek == 1)
					for (int j = 1; j < rodzaj; j++)
						pla2[y - j][x] = 'o';
				else if (kierunek == 2)
					for (int j = 1; j < rodzaj; j++)
						pla2[y][x + j] = 'o';
				else if (kierunek == 3)
					for (int j = 1; j < rodzaj; j++)
						pla2[y + j][x] = 'o';
				else if (kierunek == 4)
					for (int j = 1; j < rodzaj; j++)
						pla2[y][x - j] = 'o';
			}
			else
				szansa = true;
		}
	}
}

//wypelnia plansze komputera (pla2) z pomoca funkcji rozstaw_statek_komp
void rozstaw_komp(char pla2[][A])
{
	system("cls");
	cout << "CZEKAJ, TERAZ SWOJE STATKI ROZSTAWIA KOMPUTER ..." << endl;
	rozstaw_statek_komp(pla2, maszt2.ilosc, maszt2.maszty);
	rozstaw_statek_komp(pla2, maszt3.ilosc, maszt3.maszty);
	rozstaw_statek_komp(pla2, maszt4.ilosc, maszt4.maszty);
	rozstaw_statek_komp(pla2, maszt5.ilosc, maszt5.maszty);
	Sleep(2000);
}

void main()
{
	char pla[A][A];
	char pla2[A][A];

	system("cls");
	cout << "ZAGRAJ W STATKI" << endl;
	cout << endl;
	cout << "by Daniel Kica" << endl;
	Sleep(4000);

//	reset_pla(pla);
//	wyswietl(pla);
//	rozstaw_gracz(pla);
	reset_pla(pla2);
	rozstaw_komp(pla2);
	wyswietl(pla2);

	system("pause");
}
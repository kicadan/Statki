#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;
const int A = 16;

void rozstaw_gracz(int rodzaj,int pla[][A])
{
	char kierunek;
	for (int i = 0; i < 3; i++)
	{
		int x = 0;
		int y = 0;

		while (y >= 0 && y < A + 1 && x >= 0 && x < A + 1 && pla[x][y] != 1)
		{
			cout << "\a" << "Podaj x statku" << endl;
			cin >> x;
			cout << "Podaj y statku" << endl;
			cin >> y;
			cout << "Podaj kierunek w ktorym ustawic: p,l,g,d" << endl;
			cin >> kierunek;
			switch (kierunek)
			{
			case 'p':		for (int j = 0; j < rodzaj; j++)
				if ((x + rodzaj) <= A)
					pla[x][y + j] = 1;
				break;
			case 'l':		for (int j = 0; j < rodzaj; j++)
				if ((x - rodzaj) >= 0)
					pla[x][y - j] = 1;
				break;
			case 'g':		for (int j = 0; j < rodzaj; j++)
				if ((y - rodzaj) >= 0)
					pla[x - j][y] = 1;
				break;
			case 'd':		for (int j = 0; j < rodzaj; j++)
				if ((x + rodzaj) <= A)
					pla[x + j][y] = 1;
			}
		}
	}

}


void main()
{	
/*	struct rodzaj_ {
		string nazwa;
		int maszty;
		bool traf;
	};
*/
	int pla[A][A];

	srand(time(NULL));

//	rodzaj_ maszt2 = { "dwa", 2 };
//	rodzaj_ masz3 = { "trzy", 3 };

	for (int i = 0; i < A; i++)
		for (int j = 0; j < A; j++)
			pla[i][j] = rand() % 1;

	rozstaw_gracz(3,pla);
	
	for (int i = 0; i < A; i++)
	{
		for (int j = 0; j < A; j++)
			cout << pla[i][j];
		cout<< endl;
	}

	system("pause");
}
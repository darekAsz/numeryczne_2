#include <iostream>
#include <ctime>
#include <queue>
#include<math.h>
#include <iomanip>
using namespace std;
#define WLK_PLANSZY 27
int liczhistoria;
int ilerownan = 0;
int numerstruktury = 1;
int nrrownania = 0;
int tab[7] = { 0, 0, 0, 0, 0, 0, 0 };


struct x{


	int gr1 ;
	int gr2 ;
	int gracz ;
	int numer;
};
float macierz[520][520]; //[numerrownania][indeksstruktury]
float wolnewyniki[520];
float L[520][520];
float D[520][520];
float U[520][520];
float p[520];

int main(){
	cout << fixed << setprecision(15);
	////////////monte carlo
	int pulapki[27] = { 0,0,-2,0,0,-2,0,0,0,0,-4,0,0,0,-12,-2,0,-6,0,-8,0,-3,-16,0,0,-9,-22 };
	//int pulapki[31] = { 0, 0, -2, 0, 0, -2, 0, 0, 0, 0, -4, 0, 0, 0, -12, -2, 0, -6, 0, -8, 0, -3, -16, 0, 0, -9, -22,0,0,0,0 };
		//int pulapki[32] = { 0, -1,0,0,-1,0,-3,-2,0,0,0,0,0,-4,-5,0,0,-1,0,0,-2,-2,-10,0,-14,-2,0,-8, 0, 0, 0, 0 };
	//int pulapki[10] = { 0, 0, 0, 0, -2, -2, 0, 0, 0, 0 };
	//int pulapki[13] = { 0, 0, 0, 0, -2,-2,0,0,0,0,0,0,0 };
	//int pulapki[34] = { 0, 0, -1, 0, -4, -2, -5, -6, 0, 0, -1, 0, 0, -2, 0, -1, 0, 0, -4, 0, -9, 0, -3, 0, -1, 0, -26, 0, 0, 0, 0, 0, 0, 0 };
	//int pulapki[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 };
	//int pulapki[28] = { 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, -8, 0, -10, 0, -12, 0, 0, -13, 0, -15, 0, -17, 0, -1, 0, -3 };
	float wygral1 = 0, wygral2 = 0, ileprob = 100;
	srand(time(NULL));

	for (int i = 0; i < ileprob; i++){
		int obecny1 = 0, obecny2 = 0;
		int rzut = 0;

		while (1){
			rzut = rand() % 6 + 1;
			obecny1 += rzut;
			if (obecny1 >= WLK_PLANSZY){
				wygral1++;
				break;
			}
			obecny1 += pulapki[obecny1];
			obecny1 += pulapki[obecny1];

			rzut = rand() % 6 + 1;
			obecny2 += rzut;
			if (obecny2 >= WLK_PLANSZY){
				wygral2++;
				break;
			}
			obecny2 += pulapki[obecny2];
			obecny2 += pulapki[obecny2];
		}
	}

	wygral1 = wygral1 / ileprob;
	wygral2 = wygral2 / ileprob;

	cout << endl << "gracz 1: " << wygral1 << endl << "wygral2: " << wygral2 << endl;






	////////////tworzenie rownan i wpisanie ich do macierzy
	queue <x> kolejka;
	x historia[10000];
	x str = { 0, 0, 1 ,0};
	kolejka.push(str);
	ilerownan++;
	historia[0] = str;
	liczhistoria++;
	int licznik = 0;
	int zapamietany = 0;
		int wolne = 0;

	while (!kolejka.empty() ){
		licznik = 0;
		wolne = 0;
		str = kolejka.front();
		macierz[str.numer][str.numer] = -1;
		kolejka.pop();
		//cout << "x(" << str.gr1 << ',' << str.gr2 << ',' << str.gracz <<','<<str.numer<< ")  :   ";

		if (str.gracz == 1  ){
			for (int i = 1; i < 7; i++){
				if ((str.gr1 + i)<WLK_PLANSZY) tab[i] = str.gr1 + i + pulapki[str.gr1 + i];
				else tab[i] = 29;
				 //if (tab[i] == 2)tab[i] = 0;
				if(tab[i]<WLK_PLANSZY) tab[i] += pulapki[tab[i]];
			}
			//elementy wolne
			for (int j = 1; j < 7; j++){
				if (tab[j] >= WLK_PLANSZY){
					licznik++;
					tab[j] = -1;
				}
			}
			wolne = licznik;
			//tworzenie do kolejki
			for (int i = 1; i < 7; i++){
				licznik = 0;
				for (int j = i; j < 7; j++){
					zapamietany = tab[i];
					if ((zapamietany == tab[j]) && tab[i]>-1){
						licznik++;
						zapamietany = tab[i];
						if(i!= j)tab[j] = -1;
					}
				}
				if (licznik>0){
					x st = { zapamietany, str.gr2, 2,numerstruktury};
					
				//	cout << licznik << "/6 * x(" << st.gr1 << ',' << st.gr2 << ',' << st.gracz <<','<<st.numer<< ")  +  ";

					int czypowtorzone = 0;
					for (int i = 0; i < liczhistoria; i++){
						if (historia[i].gr1 == st.gr1 && historia[i].gr2 == st.gr2 && historia[i].gracz == st.gracz){
							czypowtorzone = 1;
							st.numer = historia[i].numer;

						}
					}
					if (czypowtorzone == 0){
						st.numer = numerstruktury;
						numerstruktury++;
						kolejka.push(st);
						historia[liczhistoria] = st;
						liczhistoria++;
						ilerownan++;
						//cout << licznik << "* x(" << st.gr1 << ',' << st.gr2 << ',' << st.gracz << ")    +    ";
					}
					//cout << licznik << "/6 * x(" << st.gr1 << ',' << st.gr2 << ',' << st.gracz << ',' << st.numer << ")  +  ";
					macierz[str.numer][st.numer] = (float)licznik / 6;
					//wolnewyniki[str.numer] = (float)wolne / 6;
					//if (wolne == 6)wolnewyniki[str.numer] = 1;
				}
			}
		//	cout << wolne << "/6" << endl;
			wolnewyniki[str.numer] = (float)wolne / 6;
		}
	



		if (str.gracz == 2){
			for (int i = 1; i < 7; i++){
				if ((str.gr2 + i)<WLK_PLANSZY) tab[i] = str.gr2 + i + pulapki[str.gr2 + i];
				else tab[i] = 29;
				//if (tab[i] == 2)tab[i] = 0;
				if (tab[i]<WLK_PLANSZY) tab[i] += pulapki[tab[i]];
			}
			//elementy wolne
			for (int j = 1; j < 7; j++){
				if (tab[j] >= WLK_PLANSZY){
					licznik++;
					tab[j] = -1;

				}
			}
			wolne = licznik;
			//tworzenie do kolejki
			for (int i = 1; i < 7; i++){
				licznik = 0;
				for (int j = i; j < 7; j++){
					if ((tab[i] == tab[j]) && tab[i]>-1){
						licznik++;
						zapamietany = tab[i];
						if (i != j)tab[j] = -1; 
					}
				}
				if (licznik>0){
					x st = { str.gr1, zapamietany, 1, numerstruktury };
					//cout << licznik << "/6 * x(" << st.gr1 << ',' << st.gr2 << ',' << st.gracz <<','<<st.numer<< ")  +  ";
					int czypowtorzone = 0;
					for (int i = 0; i < liczhistoria; i++){
						if (historia[i].gr1 == st.gr1 && historia[i].gr2 == st.gr2 && historia[i].gracz == st.gracz){
							czypowtorzone = 1;
							st.numer = historia[i].numer;
						}
					}
					if (czypowtorzone == 0){
						st.numer = numerstruktury;
						numerstruktury++;
						kolejka.push(st);
						historia[liczhistoria] = st;
						liczhistoria++;
						ilerownan++;
					//	cout << licznik<<"* x(" << st.gr1 << ',' << st.gr2 << ',' << st.gracz << " )   +    ";
					}
					//cout << licznik << "/6 * x(" << st.gr1 << ',' << st.gr2 << ',' << st.gracz << ',' << st.numer << ")  +  ";
					macierz[str.numer][st.numer] = (float)licznik / 6;
					wolnewyniki[str.numer] = (float)wolne / 6;
					//wolnewyniki[str.numer] = 0/ 6;
				}
			}
		//	cout <<"0/6"<< endl;
			wolnewyniki[str.numer] = (float)0 / 6;
		}

	}/////////koniec petli while


	//obie macierze *-1
	for (int k = 0; k < 600; k++){
		if (wolnewyniki[k] != 0)wolnewyniki[k] *= -1;
		//for (int p = 0; p < 600; p++){
		//	if (macierz[k][p] !=0)macierz[k][p] *= -1;
		//}
	}


	///////////////////gaussa siedla
	
	


	
	for (int i = 0; i < 520; i++){
		for (int j = 0; j < 520; j++) {
			if (i < j) {
				U[i][j] = macierz[i][j];
			}
			else if (i > j) {
				L[i][j] = macierz[i][j];
			}
			else {
				D[i][j] = macierz[i][j];
			}
		}
	}


	for (int i = 0; i<520; i++)p[i] = 0;
		


	int iteracji = 500;
	
	
	for (int k = 0; k<iteracji; k++)
	for (int i = 0; i<520; i++) {
		p[i] = wolnewyniki[i];                       // x = D^-1*b -
		for (int j = 0; j<i; j++)
			p[i] -= L[i][j] * p[j];    // D^-1*L * x -
		for (int j = i + 1; j<520; j++)
			p[i] -= U[i][j] * p[j];    // D^-1*U * x
	}

	cout << "wynik gaussa-seidla:  " << p[0]/macierz[0][0]<<endl;

	




	//for (int i = 0; i < ilerownan; i++)cout << wolnewyniki[i] << "   ";
	/////////gauss- zerowanie macierzy w gore
			float mnoznik = 0.0;

			for (int i = ilerownan; i >= 0; i--){

				for (int j = i - 1; j >= 0; j--){
					if (macierz[j][i] != 0){

						mnoznik = macierz[j][i] / macierz[i][i];
						for (int d = 0; d <= i; d++){
							macierz[j][d] -= (macierz[i][d] * mnoznik);
						}
						wolnewyniki[j] -= (wolnewyniki[i] * mnoznik);
					}
				}

			}
	

	////wypisanie kolejki
	cout << endl << endl << endl;
//		cout << "wart1: " << historia[d].gr1 << "    wart2: " << historia[d].gr2 << "    gracz: " << historia[d].gracz << endl;
	/*for (int k = 0; k < 300; k++){
		for (int p = 0; p < 300; p++){
			cout << macierz[k][p] << ' ';
		}
		cout << endl;
	}
	*/





	float wynikgaussa = wolnewyniki[0] / macierz[0][0];

	cout << "wolnewyniki[0]: " << wolnewyniki[0] << ",  macierz[0][0]:" << macierz[0][0] << endl;
	cout << "wynik gaussa: " << wolnewyniki[0] / macierz[0][0]<<endl;



		cout << endl << endl << endl << "rownan:  " << ilerownan << endl;
		//cout << "metoda gaussa: " << wynikgaussa<<endl<<endl;
	system("pause");
		return 0;
}
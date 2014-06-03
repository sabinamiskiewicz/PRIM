#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<time.h>
#include<list>
#include<windows.h>
#include<fstream>

using namespace std;

class Wierzcholek //klasa okreslajaca wierzcholek
{
public:
    int w;
    list<int> sasiedztwo; //lista wierzcholkow polaczonych krawedziami
    list<int> wagi; //lista wag krawedzi odchodzacych od wierzcholka
    void DodajWierzcholek(int i); //dodaje wierzcholek
    void DodajKrawedz(int i); //dodaje krawedz do wierzcholka
    void DodajWage(int i); //dodaje wage krawedzi
    void WypiszKrawedzie(int i);//pisisuje wszystkie krawedzie
};
void Wierzcholek::DodajWierzcholek(int i)
{
w=i;
}
void Wierzcholek::DodajWage(int i)
{
wagi.push_back(i);
}
void Wierzcholek::DodajKrawedz(int i)
{
sasiedztwo.push_back(i);
}

void Wierzcholek::WypiszKrawedzie(int i)
{
list<int> pom; //lista pomocnicza
while(!sasiedztwo.empty()) //dopuki lista nie bedzie pusta
    {
    cout<<endl<<w<<" - "<<sasiedztwo.back();
    pom.push_back(sasiedztwo.back()); //przekladamy krawedzie na 2 liste
    sasiedztwo.pop_back();
    }
while(!pom.empty()) //spowrotem wypelniamy liste sasiedztwa
    {
    sasiedztwo.push_back(pom.back());
    pom.pop_back();
    }
}

class Graf //klasa przechowuje graf
{
public:
    int *graf; //przechowuje graf w postaci tablicy
    Wierzcholek *wierzcholki; //przechowuje tablice wierzcholkow
    Graf(int V, int E);
    ~Graf(){};
    void Wypelnij(int V,int E); //wypelnia(tworzy) graf
    void Wypisz(int V); //wypisuje graf w postaci macierzy wag
    void Pelny(int V); //tworzy graf pelny (oszczedzajac czas)
};

Graf::Graf(int V, int E)
{
graf = new int[V*V]; //tworzy tablice o rozmiarze V^2
wierzcholki = new Wierzcholek[V]; //tworzy tablice wierzcholkow
for(int i=0; i< V*V; i++) //wypelnia macierz wag zerami
 	graf[i]=0;
}

void Graf::Pelny(int V)
{
int pom2,pom3,pom;
for(int i=0; i<V*V; i++) //wypelnia macierz wag losowymi
	{
	pom=1+rand()%9;
	pom2=i%V; //przeliczamy numer elementu z tablicy na 
	pom3=abs((i-pom2)/V); 
	graf[i]=pom;
	if(pom2!=pom3) //jesli nie jest to krawedz na glownej przekatnej macierzy grafu 
		{
		graf[V*pom2+pom3]=pom;
		}
	wierzcholki[pom2].DodajKrawedz(pom3);
	wierzcholki[pom2].DodajWage(pom);
	wierzcholki[pom3].DodajKrawedz(pom2);
	wierzcholki[pom3].DodajWage(pom);
	}
}
void Graf::Wypelnij(int V,int E)
{
int tab[E],i,j,l,pom2,pom3;
bool tmp;
for(i=0; i<V; i++)
	{
	wierzcholki[i].DodajWierzcholek(i); //dodaje wierzcholki tablicy
	}
srand((int) time(NULL));
l=0;
do //do momentu az bedziemy mieli okraslona ilosc krawedzi
    {
    j=rand()%(V*V); //losuje liczbe od 0 do V^2 -1
    tmp=true;
    for(i=0; i<l; i++)
        {
		pom2=j%V;
		pom3=abs((j-pom2)/V);
        if(tab[i]==j) //jesli dana krawedz juz byla zwraca falsz
            {
            tmp=false;
            break;
            }
        else if(pom2==pom3) //gdy krawedz na glownej przekatnej macierzy
			{
			tmp=false;
            break;
			}
		else
			{
			for(int k=0; k<i;k++)
				{
				if((pom3==tab[k]%V)&&(pom2==abs((tab[k]-tab[k]%V)/V))) //jesli dana krawedz juz byla zwraca falsz
					{
					tmp=false;
					break;
					}
				else if(pom2*V+pom3==tab[k])//jesli dana krawedz juz byla zwraca falsz
					{
				 	tmp=false;
                	break;
					}

				}
			}
        }
    if(tmp) //gdy tmp zwraca true
	tab[l++] = j;
    } 
while(l<E);
for(i=0;i<E;i++) //wypelnianie wylosowanych krawezi
	{
	int pom;
	pom=1+rand()%9;//losujemy wage od 1 do 9
	graf[tab[i]]=pom; //w wylosowana wczesniej krawedz dodajemy wage
	pom2=tab[i]%V; //przeliczamy numer elementu z tablicy na 
	pom3=abs((tab[i]-pom2)/V); //dwie osobne krawedzie
	graf[pom2*V+pom3]=pom;//dodajemy wage w krawedz rowniez po 2 stronie przekatnej macierzy
	wierzcholki[pom2].DodajKrawedz(pom3);
	wierzcholki[pom2].DodajWage(pom);
	wierzcholki[pom3].DodajKrawedz(pom2);
	wierzcholki[pom3].DodajWage(pom);
	}
	//delete []tab;
}

void Graf::Wypisz(int V)
{
for(int i=0; i<V*V; i++)
	{
	if(i%V==0)
	cout<<endl;
	cout<<graf[i]<<" ";
	}
}

void Prima(int V,int E, Graf g)
{
int i,j,k,l=0;
i=0;
int pom[V];
int suma=0;
int min=0;
int mins;
list<int> tmp;
list<int> tmp2;

for(i=0;i<V;i++) //wypelniamy tablice pomocnicza cyfra -1 aby moc odroznic dodane wierzcholki od niedodanych
	{
	pom[i]=-1;
	}
i=0;
for(k=0;k<V;k++) //do momentu gdy bedziemy miec wszystkie wierzcholki
	{
	if(pom[i]==-1) //jesli wierzcholka jeszcze nie dodalismy
		{
		if((!g.wierzcholki[i].wagi.empty())&&(!g.wierzcholki[i].sasiedztwo.empty())) //jesli do tego wierzcholka dochodza jakiekolwiek krawedzie
			{
			min=g.wierzcholki[i].wagi.back(); //ustalamy 1 z krawedzi jako ta o wadze minimalnej
			mins=g.wierzcholki[i].sasiedztwo.back(); //zapamietujemy wierzcholek o minimalnej ustalonej wadze
			pom[mins]=i; //dodajemy do tablicy dany wierzcholek aby zapamietac ze juz on wystapil
			tmp.push_back(min); //dodajemy wage na liste pomocnicza
			tmp2.push_back(g.wierzcholki[i].sasiedztwo.back()); //dodajemy wierzcholek na liste pomocnicza
			g.wierzcholki[i].wagi.pop_back(); //usuwamy szczyt listy wag
			g.wierzcholki[i].sasiedztwo.pop_back(); //usuwamy szczyt listy sasiedztwa
			l=1; //jesli weszlismy do petli czyli do wierzcholka dochodza krawedzie zapamietujemy l=1 jest to zmienna pomocnicza
			}
		while((!g.wierzcholki[i].wagi.empty())&&(!g.wierzcholki[i].sasiedztwo.empty())) //do momentu az listy nie beda puste
			{
			if(g.wierzcholki[i].wagi.back()<min) //jesli kolejna waga z listy jest mniejsza od poprzedniej
				{
				min=g.wierzcholki[i].wagi.back(); //ustawamy min na mniejsza wage
				mins=g.wierzcholki[i].sasiedztwo.back(); //ustawiamy mins na krawedz od mniejszej wagi
				}
			tmp.push_back(g.wierzcholki[i].wagi.back()); //dodajemy wage na liste pomocnicza
			tmp2.push_back(g.wierzcholki[i].sasiedztwo.back()); //dodajemy krawedz na liste pomocnicza
			g.wierzcholki[i].wagi.pop_back(); //usuwamy szczyt listy wag
			g.wierzcholki[i].sasiedztwo.pop_back(); //usuwamy szczyt listy sasiedztwa
			}
		while((!tmp.empty())&&(!tmp2.empty())) //zwracamy wagi i krawedzie na listy
			{
			g.wierzcholki[i].wagi.push_back(tmp.back());
			g.wierzcholki[i].sasiedztwo.push_back(tmp2.back());
			tmp.pop_back();
			tmp2.pop_back();
			}
		pom[i]=i; // dodajemy do tablicy wierzcholek aby pamietac ze on juz wystapil
		if(l==1) //jesli wierzcholek mial jakiekolwiek krawedzie
			{
			suma=suma+min; //zwiekszamy suma maksymalnego drzewa rozp o minimalna krawedz jaka znalezlismy
			i=mins;
			}
		else //jesli wierzcholek nie mial krawedzi przechodzimy do nastepnego
		i=i+1;
		l=0;//l ponownie wracado wartosci 0
		}
	else //jesli wierzcholek byl wczesniej dodany
	i=i+1; //przesuwamy sie do kolejnego
	}
}

int main()
{
int V,E,tmp;
int i=0;
V=256;
fstream Plik;//plik do zaspisu czasow
Plik.open("prima.txt");
int gestosc=50;
E=V*(V-1)*gestosc/100/2;
Graf g(V,E);
if(gestosc!=100)
    g.Wypelnij(V,E);
else
	g.Pelny(V);
	//g.Wypisz(V);
//	for(i=0;i<1;i++)
//	{
	Prima(V,E,g);
//	cout << endl << "Time:" <<tm <<endl;
//	Plik<<tm<<endl;
}
	//Plik.close();
//}

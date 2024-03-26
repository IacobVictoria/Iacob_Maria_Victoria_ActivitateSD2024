

//pointer-8 octeti ->ca are un pointer in plus fata de cea lista simpla
// creare structura(adresa nod prim, adresa nod ultim)
//mai greu de implementat
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Node Nod;
typedef struct Cafenea Cafenea;
typedef struct ListaDubla ListaDubla;
struct Cafenea {
	char* nume;
	int nrLocuri;
	float suprafata;
};
struct Node {
	Cafenea cafenea;
	Nod* anterior;
	Nod* urmator;
};
//numele cafenelei cu densitatea cea mai mica
struct ListaDubla {
	Nod* cap;
	Nod* coada;

};

void inserareInceput(ListaDubla* lista, Cafenea c) {
	Nod* node = (Nod*)malloc(sizeof(Nod));
	node->anterior = NULL;
	node->urmator = lista->cap;
	node->cafenea = c;
	if (lista->cap != NULL)
	{
		lista->cap->anterior = node;
		lista->cap = node;
	}
	else {
		//lista->cap = node;  //un singur nod este si cap si coada
		lista->coada = node;
	}
	lista->cap = node;//mereu se face chiar daca avem lista chiar daca nu avem


}
Cafenea initializare(const char* nume, int nrLocuri, float suprafata) {
	Cafenea c;
	c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrLocuri = nrLocuri;
	c.suprafata = suprafata;
	return c;
}

void afisareCafenea(Cafenea cafenea) {
	printf("cafeneaua %s are un nr de locuri de %d si spatiul %5.2f\n\n", cafenea.nume, cafenea.nrLocuri, cafenea.suprafata);
}
void afisareLista(ListaDubla lista) {
	Nod* curent = lista.cap;
	while (curent) 
	{
		afisareCafenea(curent->cafenea);
		curent = curent->urmator;
	}
	printf("\n\n");
}
//stergere Cafenea dupa nume
ListaDubla stergereCafeneaDupaNume(ListaDubla lista, char* nume) {
	//modificam adica punem * pt ca daca e cap sau coada o sa se modifice, sau facem returnat ListaDubla
	if (nume == NULL) {
		return lista;
	}
	Nod* nod = lista.cap;
	while (nod && strcmp(nod->cafenea.nume,nume)!=0) {
		nod = nod->urmator;
	}
	if (nod!=NULL)// daca nu avem nod, adica daca ne am oprit pe un nod
		//AICI MUTAM NU FACEM STERGEREA
	{
		if (nod->urmator == NULL && nod->anterior == NULL)//avem un singur nod
		{
			lista.cap = NULL;
			lista.coada = NULL;


		}
		else if(nod->anterior==NULL)//PRIMUL NOD
		{
			lista.cap = nod->urmator;
			lista.cap->anterior = NULL;
		}
		else if (nod->urmator == NULL)//ca e ultimul
		{
			lista.coada = nod->anterior;
			lista.coada->urmator = NULL;

		}
		else//nu modificam lista daca nu e capat sau coada
		{//daca e la mijloc
			nod->anterior->urmator = nod->urmator;
			nod->urmator->anterior = nod->anterior;
		}
		free(nod->cafenea.nume);
		free(nod);
	}
	return lista;
}
ListaDubla stergeLista(ListaDubla listaDubla) {
	//if (listaDubla.cap != NULL) //exista lista daca capul sau coada sunt diferite de NULL

		while (listaDubla.cap != NULL) {
			free(listaDubla.cap->cafenea.nume);
			Nod* temp = listaDubla.cap;
			listaDubla.cap=listaDubla.cap->urmator;
			free(temp);//mai intai ne deplasam si dupa stergem
		}
		listaDubla.cap = NULL;
		listaDubla.coada = NULL;
		return listaDubla;
	
}

//functie care sa mi calculeze nr de locuri total, cu suparafata mai mica decat un param dat
int nrPers(ListaDubla lista) {
	int nr = 0;
	//o parcurgem invers, plecam de la coada
	Nod* node = lista.coada;
	while (node!=NULL) {
		nr += node->cafenea.nrLocuri;
		node = node->anterior;
	}

	return nr;
}
void main() {
	Cafenea c1 = initializare("Tucano", 12, 150);
	Cafenea c2 = initializare("Teds", 18, 200);
	Cafenea c3 = initializare("Urban", 24, 350);
	Cafenea c4 = initializare("Sb", 45, 200);
	ListaDubla listaDubla;
	listaDubla.cap = NULL;
	listaDubla.coada = NULL;
	inserareInceput(&listaDubla, c1);
	inserareInceput(&listaDubla, c2);
	inserareInceput(&listaDubla, c3);
	inserareInceput(&listaDubla, c4);
	listaDubla = stergereCafeneaDupaNume(listaDubla, "Teds");

	listaDubla = stergereCafeneaDupaNume(listaDubla,"Tucano");

	listaDubla = stergereCafeneaDupaNume(listaDubla, "Starbucks");

	listaDubla = stergereCafeneaDupaNume(listaDubla, "Sbii");
	afisareLista(listaDubla);
	int n=nrPers(listaDubla);
	printf("Nr total locuri %d",n);
	//listaDubla=stergeLista(listaDubla);
	//afisareLista(listaDubla);




}

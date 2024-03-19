#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Node Nod;
typedef struct Cafenea Cafenea;
struct Cafenea {
	char* nume;
	int nrLocuri;
	float suprafata;
};
struct Node {
	Nod* pNext;
	Cafenea info;

};
//numele cafenelei cu densitatea cea mai mica

char* numeCafenea(Nod* lista) {
	Nod* node;
	if (lista != NULL) {
		if (lista->info.suprafata != 0)
		{
			float minim = lista->info.nrLocuri / lista->info.suprafata;
			node=lista;
			lista = lista->pNext;
			while (lista != NULL ) {
				if (lista->info.nrLocuri / lista->info.suprafata < minim) {
					minim = lista->info.nrLocuri / lista->info.suprafata;
					node = lista;
				}
				lista = lista->pNext;
			}
			char* nume;
			nume = (char*)malloc(strlen(node->info.nume) + 1);
			strcpy(nume, node->info.nume);
			return nume;
		}
	}
	return NULL;
	
}
Cafenea initializare( const char* nume, int nrLocuri, float suprafata) {
	Cafenea c;
	c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrLocuri = nrLocuri;
	c.suprafata = suprafata;
	return c;
}
Nod* inserareInceput(Nod* cap, Cafenea c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->pNext = cap;
	nou->info = initializare(c.nume,c.nrLocuri,c.suprafata);
	//shallow copy
	return nou;
}
void afisarelista(Nod* lista) {
	Nod* curent = lista;
	while (curent) {
		printf("cafeneaua %s are un nr de locuri de %d si spatiul %5.2f\n\n", curent->info.nume, curent->info.nrLocuri, curent->info.suprafata);
		curent = curent->pNext;
	}
}

void stergereLista(Nod** lista) {

	while (*lista!=NULL) {
		Nod* aux = (*lista);
		(*lista)=(*lista)->pNext;
		free(aux->info.nume);
		free(aux);
		
	}
	(*lista )= NULL;
}
void inserareFinal(Nod** lista, Cafenea c) {
	if ((*lista) == NULL) {
		(*lista) = inserareInceput( *lista,c);
	}
	else {
		Nod* curent = (*lista);
		while (curent->pNext != NULL) {
			curent = curent->pNext;
		}
		Nod* n = (Nod*)malloc(sizeof(Nod));

		n->info = initializare(c.nume, c.nrLocuri, c.suprafata);
		n->pNext = NULL;

		curent->pNext = n;
	}
}

void main() {
	Nod* cap = NULL;
	Cafenea c1 = initializare("Tucano", 12, 150);
	Cafenea c2 = initializare("Teds", 18, 200);
	Cafenea c3 = initializare("Urban", 24, 350);
	Cafenea c4 = initializare("Sb", 45, 200);
	cap = inserareInceput(cap, c1);
	cap = inserareInceput(cap, c2);
	cap = inserareInceput(cap, c3);
	inserareFinal(&cap, c4);
	afisarelista(cap);
	char* nume=numeCafenea(cap);
	printf("Numele este %s\n", nume);
	stergereLista(&cap);
	free(c1.nume);
	free(c2.nume);
	free(c3.nume);
	free(nume);
	afisarelista(cap);

}

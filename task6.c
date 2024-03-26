#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include <string.h>
typedef struct Carte Carte;
typedef struct ListaDubla ListaDubla;
typedef struct Nod Nod;
struct Carte {
	char* titlu;
	float pret;
	int nrPag;
};
struct Nod {
	Carte carte;
	Nod* anterior;
	Nod* urmator;

};
struct ListaDubla {
	Nod* cap;
	Nod* coada;

};
typedef struct NodSimplu {
	Carte carte;
	struct NodSimplu* urmator;
} NodSimplu;


Carte creareCarte(char* titlu, float pret, int nrPag) {
	Carte c;
	c.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy(c.titlu, titlu);
	c.pret = pret;
	c.nrPag = nrPag;
	return c;
}
ListaDubla inserareInceput(ListaDubla lista, Carte c) {
	Nod* node = (Nod*)malloc(sizeof(Nod));
	node->anterior = NULL;
	node->urmator = lista.cap;
	node->carte = c;
	if (lista.cap != NULL) {
		lista.cap->anterior = node;//daca lista nu e goala,DE SETAT cap anterior lista
	}
	else {
		lista.coada = node;//de setat coada daca lista e goala
	}
	lista.cap = node;
	return lista;
}
void InserareInc(ListaDubla* lista, Carte c) {
	Nod* node = (Nod*)malloc(sizeof(Nod));
	node->anterior = NULL;
	node->urmator = lista->cap;
	node->carte = c;
	if (lista->cap != NULL) {
		lista->cap->anterior = node;
	}
	else {
		lista->coada = node;
	}
	lista->cap = node;
	return lista;
}

void inserareSfarsit(ListaDubla* lista, Carte c) {
	Nod* node = (Nod*)malloc(sizeof(Nod));
	node->anterior = lista->coada;
	node->urmator = NULL;
	node->carte = c;
	if (lista->coada != NULL) {
		lista->coada->urmator = node;
	}
	else {
		lista->cap = node;
	}
	lista->coada = node;

}
ListaDubla citireFisier(char* numeFis) {
	ListaDubla lista;
	lista.cap = NULL;
	lista.coada = NULL;
	FILE* f = fopen(numeFis, "r");
	char buffer[100],delimitator[2]=",\n";
	char* nume=NULL;char* token;
	float pret;
	int nrPag;
	Carte carte;
	if (f) {
		while (fgets(buffer, sizeof(buffer), f)) {
			token = strtok(buffer, delimitator);
			nume = (char*)malloc(strlen(token) + 1);
			strcpy(nume, token);
			token = strtok(NULL, delimitator);
			pret = atof(token);
			token = strtok(NULL, delimitator);
			nrPag = atoi(token);
			carte = creareCarte(nume, pret, nrPag);
			inserareSfarsit(&lista, carte);

		}
	}
	return lista;

}
//stergere carte cu un anumit titlu

ListaDubla stergereCarteCuTitlu(ListaDubla lista, char* titlu) {
	if (titlu == NULL) {
		return lista;
	}
	Nod* node = lista.cap;
	while (node != NULL && strcmp(node->carte.titlu,titlu)!=0) {
      	node = node->urmator;

	}
	if (node != NULL) {
		
		if (node->urmator == NULL && node->anterior == NULL)//singurul
		{
			lista.cap = NULL; // ca o sa sterg singurul care exista deci nu o sa mai am nimic
			lista.coada = NULL;
		}
		else if (node->urmator == NULL) //ultimul
		{
			lista.coada = node->anterior;
			lista.coada->urmator = NULL;
		}
		else if (node->anterior == NULL)//primul
		{
			lista.cap = node->urmator;
			node->urmator->anterior = NULL;

		}
		else {
			node->anterior->urmator = node->urmator;
			node->urmator->anterior = node->anterior;
		}

		free(node->carte.titlu);
		free(node);


	}
	return lista;

}

//returneaza carte cu un anumit titlu
Carte returnCarteCuTitlu(ListaDubla lista, char* nume) {
	Nod* node = lista.cap;
	while (node && strcmp(node->carte.titlu, nume) != 0) {
		node = node->urmator;
	}
	if (node!=NULL) {
		return node->carte;
	}
}
void afisareLista(ListaDubla lista) {
	Nod* node = lista.cap;
	while (node) {
		printf("Cartea %s are %d nr pag si costa %5.2f\n", node->carte.titlu, node->carte.nrPag, node->carte.pret);

		node = node->urmator;
	}
}
void afisareCarte(Carte carte) {
	printf("Cartea %s are %d nr pag si costa %5.2f\n", carte.titlu,carte.nrPag, carte.pret);
}

//o functie care sterge un nod de pe o pozitie data ca parametru.
void stergerePoz(ListaDubla* lista, int poz) {
	Nod* node = lista->cap;
	int index = 1;
	if (poz == 1) {
		lista->cap = node->urmator;
		lista->cap->anterior = NULL;
		free(node->carte.titlu);
		free(node);
	}
	else
	{
		while (node && index++ < poz) {
			node = node->urmator;
		}
		if (node != NULL)//ca sa trateze si indexul incorect
		{
			if (node->urmator == NULL) {
				lista->coada = node->anterior;
				node->anterior->urmator = NULL;

			}
			else {
				node->anterior->urmator = node->urmator;
				node->urmator->anterior = node->anterior;
			}
			free(node->carte.titlu);
			free(node);
		}
	}
	return lista;

}

void inserareSortataPret(ListaDubla* lista, Carte c) {
	Nod* node = (Nod*)malloc(sizeof(Nod));
	node->carte = c;
	node->anterior = NULL;
	node->urmator = NULL;

	if (lista->cap == NULL) {
		lista->cap = node;
		lista->coada = node;
		// If it's the first node in the list
	}
	else {
		Nod* curent = lista->cap; // Start from the beginning of the list

		while (curent && curent->carte.pret < node->carte.pret) {
			curent = curent->urmator;
		}

		if (curent != NULL) {
			// Insert between nodes
			if (curent->anterior == NULL) {
				// Insert before the first node
				node->urmator = curent;
				curent->anterior = node;
				lista->cap = node; // Update the head of the list
			}
			else {
				// Insert in the middle of the list
				node->urmator = curent;
				node->anterior = curent->anterior;
				curent->anterior->urmator = node;
				curent->anterior = node;
			}
		}
		else {
			
			lista->coada->urmator = node;
			node->anterior = lista->coada;
			lista->coada = node; 
		}
	}
}
//4.
NodSimplu* inserareSimpluInc(NodSimplu* lista, Carte c) {
	NodSimplu* node = (NodSimplu*)malloc(sizeof(NodSimplu));
	node->carte = creareCarte(c.titlu,c.pret,c.nrPag);
	node->urmator = lista;
	return node;
	

}
NodSimplu* creeazaListaSimpla(ListaDubla listaDubla, float pret) {
	Nod* curent = listaDubla.cap;
	NodSimplu* listaSimpla = NULL; 

	while (curent != NULL) {
		if (curent->carte.pret <= pret) {
			
			listaSimpla = inserareSimpluInc(listaSimpla, curent->carte);
		}
		curent = curent->urmator;
	}

	return listaSimpla; 
}

void afisareListaSimpla(NodSimplu* lista) {
	NodSimplu* curent = lista;
	while (curent!=NULL) {
		printf("Cartea %s are %d nr pag si costa %5.2f\n", curent->carte.titlu, curent->carte.nrPag, curent->carte.pret);
		curent = curent->urmator;
	}
}
/// <summary>
/// 5.
/// </summary>
void interschimbaElemente(ListaDubla* lista, int pozitie1, int pozitie2) {
	if (pozitie1 == pozitie2) {
		// Dacă pozițiile sunt aceleași, nu avem ce să interschimbăm
		return;
	}

	Nod* nod1 = lista->cap;
	Nod* nod2 = lista->cap;
	int index = 1;

	
	while (nod1 != NULL && index < pozitie1) {
		nod1 = nod1->urmator;
		index++;
	}
	//!!!!!!!!!!!!!!!!!!!    INDEX=1
	
	index = 1; // Resetăm indexul pentru a-l folosi din nou
	while (nod2 != NULL && index < pozitie2) {
		nod2 = nod2->urmator;
		index++;
	}

	
	// Interschimbăm informațiile utile din cele două noduri
	Carte tempCarte = nod1->carte;
	nod1->carte = nod2->carte;
	nod2->carte = tempCarte;
}

void parcurgereDescrescatoare(ListaDubla lista) {

	Nod* curent = lista.coada;
	
	
	while (curent != NULL) {
		afisareCarte(curent->carte);
		curent = curent->anterior;
	}
	printf("\n");
}
void main() {
	ListaDubla list = citireFisier("carti.txt");
	//Carte ca = returnCarteCuTitlu(list, "Cartea Florilor");
	//list=stergereCarteCuTitlu(list, "Cartea Florilor");
	//stergerePoz(&list, 7);

	ListaDubla listaDubla ;
	listaDubla.cap = NULL;
	listaDubla.coada = NULL;
	Carte c1 = creareCarte("WOW1", 200, 80);
	Carte c2 = creareCarte("florile magice", 100, 90);
	Carte c3 = creareCarte("Masinile tari", 270, 99);
	Carte c4 = creareCarte("florile magice", 50, 88);
	inserareSortataPret(&listaDubla, c1);
	inserareSortataPret(&listaDubla, c2);
	inserareSortataPret(&listaDubla, c3);
	inserareSortataPret(&listaDubla, c4);
	NodSimplu* listaSimpla = NULL;
	listaSimpla=creeazaListaSimpla(list,60);
	//afisareListaSimpla(listaSimpla);
	//afisareCarte(ca);
	//interschimbaElemente(&list, 2, 5);
//	afisareLista(list);
	parcurgereDescrescatoare(list);
}

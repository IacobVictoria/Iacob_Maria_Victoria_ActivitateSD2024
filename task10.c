#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <string.h>
 //Sa se realizeze functia de cautare a unui  nod in arborele AVL, pe baza unui id, sau a cheii de cautare din arbore.
typedef struct Cinema Cinema;
typedef struct Nod Nod;
struct Cinema {
	int id;
	int nrFilme;
	char** filme;
};
struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
	//se poate pune un nou atribut grad de echilibru
	//in stanga+1
	//in dreapta 
};
int inaltimeArbore(Nod* rad) {
	if (rad) {
		int inaltSt = inaltimeArbore(rad->st);
		int inaltDr = inaltimeArbore(rad->dr);
		return 1 + (inaltSt < inaltDr) ? inaltDr : inaltSt;
	}
}
int calculGradEchilibru(Nod* rad) {
	if (rad) {
		int st = inaltimeArbore(rad->st);
		int dr = inaltimeArbore(rad->dr);
		return st - dr;
	}
}
Nod* rotireDreapta(Nod* rad) {
	if (rad) {
		Nod* aux = rad->st;
		rad->st = aux->dr;
		aux->dr = rad;
		return rad;
	}
}
Nod* rotireStanga(Nod* rad) {
	if (rad) {
		Nod* aux = rad->dr;
		rad->dr = aux->st;
		aux->st = rad;
		return rad;
	}
}
void inserareArbore(Nod** rad, Cinema c) {
	if (*rad) {
		if (c.id > (*rad)->info.id) {
			inserareArbore(&(*rad)->dr, c);
		}
		else {
			inserareArbore(&(*rad)->st, c);
		}

		if (calculGradEchilibru(*rad) == 2) {

			if (calculGradEchilibru((*rad)->st) != 1) {
				(*rad)->st = rotireStanga((*rad)->st);
			}
			(*rad) = rotireDreapta(*rad);

		}
		else if (calculGradEchilibru(*rad) == -2) {
			if (calculGradEchilibru((*rad)->dr) != -1) {
				(*rad)->dr = rotireDreapta((*rad)->dr);
			}
			*rad = rotireStanga(*rad);
		}
	}
	else {
		Nod* node = (Nod*)malloc(sizeof(Nod));
		node->info = c;
		node->dr = NULL;
		node->st = NULL;
		*rad = node;

	}

}
Cinema initializare(int id, int nr, char** filme) {
	Cinema c;
	c.id = id;
	c.nrFilme = nr;
	c.filme = (char**)malloc(sizeof(char*) * nr);
	for (int i = 0; i < c.nrFilme; i++) {
		c.filme[i] = (char*)malloc(strlen(filme[i]) + 1);
		strcpy(c.filme[i], filme[i]);
	}
	return c;
}
Cinema citireCinema(FILE* f) {
	Cinema c;
	fscanf(f, "%d", &c.id);
	fscanf(f, "%d", &c.nrFilme);
	if (c.nrFilme != 0) {
		c.filme = (char**)malloc(sizeof(char*) * c.nrFilme);
		for (int i = 0; i < c.nrFilme; i++) {
			char buffer[100];
			fscanf(f, "%s", buffer);
			c.filme[i] = (char*)malloc(strlen(buffer) + 1);
			strcpy(c.filme[i], buffer);

		}
	}
	else {
		c.filme = NULL;
	}

	return c;
}
Nod* citireFisier(char* numeFis) {
	FILE* f = fopen(numeFis, "r");
	Nod* radacina = NULL;
	Cinema c;
	if (f) {
		int dim = 0;
		fscanf(f, "%d", &dim);
		for (int i = 0; i < dim; i++) {
			Cinema c;
			c = citireCinema(f);
			inserareArbore(&radacina, c);
		}
		fclose(f);
	}
	return radacina;
}
//inordine   SRD
//preordine  RSD
//postordine SDR
void afisareCinema(Cinema c) {
	printf("Cinema ul cu id %d are in derulare %d filme\n", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++) {
		printf("%s\n", c.filme[i]);
	}
	printf("\n");

}
void afisareArborePreordine(Nod* rad) {
	//RSD
	if (rad) {
		afisareCinema(rad->info); //R
		afisareArborePreordine(rad->st);//S
		afisareArborePreordine(rad->dr);//D

	}
}
void afisareRadInordine(Nod* rad) {
	if (rad) {
		afisareRadInordine(rad->st);
		afisareCinema(rad->info);
		afisareRadInordine(rad->dr);
	}
}
int calculNrFilmeRedate(Nod* rad) {
	if (rad) {
		int suma = rad->info.nrFilme;
		//preordine
		suma += calculNrFilmeRedate(rad->st);
		suma += calculNrFilmeRedate(rad->dr);
		return suma;
	}
	else {
		return 0;
	}

}
Nod* cautarenodById(Nod* rad, int id) {
	if (rad) {
		if (id > rad->info.id) {
			cautarenodById(rad->dr, id);
		}
		else if (id < rad->info.id) {
			cautarenodById(rad->st, id);
		}
		else
		{
			return rad;
		}

	}
}
int nrNoduri(Nod* rad) {
	if (rad) {
		int st = nrNoduri(rad->st);
		int dr = nrNoduri(rad->dr);
		return 1 + st + dr;
	}
	else {
		return 0;
	}
}
//Sa se realizeze o functie care salveaza nodurile din arborele AVL intr-un vector,
// prin parcurgerea preordine, inordine, postordine.

void parcurgerePreordine(Nod* rad, Cinema** vector, int* index) {
	if (rad) {
		vector[(*index)++] = &rad->info; // Adăugăm nodul curent în vector
		parcurgerePreordine(rad->st, vector, index); // Parcurgem subarborele stâng
		parcurgerePreordine(rad->dr, vector, index); // Parcurgem subarborele drept
	}
}

Cinema** salvareVector(Nod* arbore, int* nr) {
	if (!arbore) {
		*nr = 0;
		return NULL;
	}

	*nr = nrNoduri(arbore);
	Cinema** vector = (Cinema**)malloc(sizeof(Cinema*) * (*nr));
	int i = 0;
	parcurgerePreordine(arbore, vector, &i);

	return vector;
}

void afisareVector(Cinema** vector, int nr) {
	for (int i = 0; i < nr; i++) {
		afisareCinema(*(vector[i]));
	}
}
//inserare in lista simpla
//PASTRARE IN LISTA SIMPLA
typedef struct NodListaSimplu NodListaSimplu;
struct NodListaSimplu {
	Cinema cinema;
	NodListaSimplu* next;

};
void inserareListaSimpla(NodListaSimplu** lista,Cinema c) {
	NodListaSimplu* node = (NodListaSimplu*)malloc(sizeof(NodListaSimplu));
	node->cinema = c;
	node->next = NULL;
	if (*lista) {
		 NodListaSimplu* cur = *lista;
		 while (cur->next!=NULL) {
			cur = cur->next;
		}
		cur->next = node;

	}
	else {
		*lista = node;
	}
}
void afisarelistaSimpla(NodListaSimplu* lista) {
	NodListaSimplu* cur = lista;
	while (cur) {
		afisareCinema(cur->cinema);
		cur = cur->next;
	}
}
void parcurgereInordinePtLista(Nod* rad, NodListaSimplu** lista) {
	if (rad) {
		NodListaSimplu* node = (NodListaSimplu*)malloc(sizeof(NodListaSimplu));
		node->cinema = rad->info;
		node->next = NULL;
		parcurgereInordinePtLista(rad->st, lista);
		inserareListaSimpla(lista, node->cinema);
		
		// Apoi parcurgem subarborele drept
		parcurgereInordinePtLista(rad->dr, lista);

	}
}
NodListaSimplu* salvareListaSimpla(Nod* rad) {
	NodListaSimplu* lista = NULL;
	parcurgereInordinePtLista(rad, &lista);
	return lista;
}

//PASTRARE IN LISTA DUBLA
typedef struct NodListaDubla {
	Cinema c;
	struct NodListaDubla* next;
	struct NodListaDubla* prev;
} NodListaDubla;


typedef struct ListaDubla {
	NodListaDubla* cap;
	NodListaDubla* coada;
} ListaDubla;

// Funcție pentru inițializarea unei liste dublu inlantuite
ListaDubla* initializareListaDubla() {
	ListaDubla* lista = (ListaDubla*)malloc(sizeof(ListaDubla));
	if (lista == NULL) {
		printf("Eroare la alocarea memoriei pentru lista dubla.\n");
		exit(EXIT_FAILURE);
	}
	lista->cap = NULL;
	lista->coada = NULL;
	return lista;
}


// Funcție pentru inserarea unui nod în lista dublu inlantuita
void inserareListaDubla(ListaDubla* lista, Cinema c) {
	NodListaDubla* node = (NodListaDubla*)malloc(sizeof(NodListaDubla));
	if (node == NULL) {
		printf("Eroare la alocarea memoriei pentru nodul din lista.\n");
		exit(EXIT_FAILURE);
	}
	node->c = c;
	node->next = NULL;
	node->prev = NULL;

	if (lista->cap == NULL) {
		
		lista->cap = node;
		lista->coada = node;
	}
	else {
		
		node->prev = lista->coada;
		lista->coada->next = node;
		lista->coada = node; 
	}
}


void parcurgereInordinePtListaDubla(Nod* rad, ListaDubla* lista) {
	if (rad != NULL) {
		
		parcurgereInordinePtListaDubla(rad->st, lista);

		
		inserareListaDubla(lista, rad->info);

		
		parcurgereInordinePtListaDubla(rad->dr, lista);
	}
}

// Funcție pentru a salva nodurile din arborele AVL într-o listă dublu inlantuita prin parcurgerea inordine
ListaDubla* salvareListaDubla(Nod* rad) {
	ListaDubla* lista = initializareListaDubla(); 
	parcurgereInordinePtListaDubla(rad, lista); 
	return lista;
}
void afisareListaDubla(ListaDubla* lista) {
	if (lista == NULL || lista->cap == NULL) {
		printf("Lista este goala.\n");
		return;
	}
	printf("Lista dubla inlantuita:\n");
	NodListaDubla* current = lista->cap;
	while (current != NULL) {
		afisareCinema(current->c);
		current = current->next;
	}
}

//stergerea intregului arbore
void stergereArbore(Nod** rad) {
	if ((*rad)!=NULL) {//DOAR POSTORDINE MERGE SA STERG

		stergereArbore(&(*rad)->st);
		stergereArbore(&(*rad)->dr);//adresa o dam
		if ((*rad)->info.filme) {
			for (int i = 0; i < (*rad)->info.nrFilme; i++)
			{
				free((*rad)->info.filme[i]);
			}
			free((*rad)->info.filme);
		}
		free(rad);
		*rad = NULL;

	}
}

 Cinema returneazaCinemaMaximFilme(Nod* rad) {
	if (rad) {
		Cinema cinemaStanga = returneazaCinemaMaximFilme(rad->st);
		Cinema cinemaDreapta = returneazaCinemaMaximFilme(rad->dr);
		Cinema cinemaMaxim;
		if (rad->info.nrFilme > cinemaStanga.nrFilme && rad->info.nrFilme>cinemaDreapta.nrFilme) {
			cinemaMaxim = rad->info;

		}
		else if (cinemaStanga.nrFilme > cinemaDreapta.nrFilme) {
			cinemaMaxim = cinemaStanga;
		}
		else {
			cinemaMaxim = cinemaDreapta;
		}
		 return cinemaMaxim;
		
	}
	else {
		Cinema c;
		c.id = -1;
		c.filme = NULL;
		c.nrFilme = 0;
		return c;
	}
}
int main() {
	Nod* arbore = NULL;
	arbore = citireFisier("cinema.txt");
	//afisareArborePreordine(arbore);
	//elem sortate dupe id
	int nr2 = nrNoduri(arbore);
	printf("NR NODURI:%d \n", nr2);
	int nr = 0;
	Cinema** vector = salvareVector(arbore, &nr);
	//afisareVector(vector, nr);
	NodListaSimplu* lista = salvareListaSimpla(arbore);
	//afisarelistaSimpla(lista);


	ListaDubla* listaD = salvareListaDubla(arbore);
	 afisareListaDubla(listaD);

	return 0;
}

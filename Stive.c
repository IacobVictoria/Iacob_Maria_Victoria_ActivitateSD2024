#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include<malloc.h>
typedef struct Curs Curs;
typedef struct Nod Nod;
struct Curs {
	char* materie;
	int credite;
};
struct Nod {
	Curs info;
	Nod* next;
};
Curs initializareCurs(const char* materie, int nr) {
	Curs c;
	c.materie = (char*)malloc(strlen(materie) + 1);
	strcpy(c.materie, materie);
	c.credite = nr;
	return c;
}
void afisareCurs(Curs c) {
	printf("Cursul la materia %s are %d credite.\n", c.materie, c.credite);
}

void push(Nod** stiva, Curs c) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));

	
	nou->info = initializareCurs(c.materie, c.credite);


	nou->next = *stiva;

	
	*stiva = nou;
}

Curs pop(Nod** stiva) {
	
	Curs rezultat = (*stiva)->info;

	Nod* auxiliar = (*stiva)->next;

	free(*stiva);


	*stiva = auxiliar;


	return rezultat;
}


int sumaCredite(Nod* stiva) {
	int suma = 0;
	Nod* copie = NULL;
	while (stiva) {
		Curs c;
		c = pop(&stiva);
		suma += c.credite;
		push(&copie, c);
	}
	while (copie) {
		push(&stiva, pop(&copie));
		//adaug in stiva ce scot din copie
	}
	return suma;
}

void stergereCurs(Nod** stiva, const char* materie) {
	Nod* copie = NULL;
	while (*stiva && strcmp((*stiva)->info.materie, materie) != 0)
	{
		//cat timp  stiva diferita de null si materiile diferite de cea cautata
		//extrag materiile 
		Curs c = pop(stiva);
		//le adaug in copie
		push(&copie, c);// tr sa pun adresa la copie
	}
	if (*stiva) {
		Curs c = pop(stiva);
		free(c.materie);
	}
	while (copie) {
		push(stiva, pop(&copie));
	}
}
void afisareStiva(Nod** stiva) {
	Nod* copie = NULL;
	Nod* temp = *stiva;

	// Copiază stiva într-o variabilă auxiliară pentru afișare
	while (temp) {
		Curs c = temp->info;
		push(&copie, c);
		temp = temp->next;
	}

	// Afisează conținutul stivei din copie
	while (copie) {
		Curs c = pop(&copie);
		afisareCurs(c);
	}
}

Curs* salvareVector(Nod** stiva, int* nr, int prag) {
	Nod* copie = NULL;
	int k = 0;
	while (*stiva) {
		Curs c = pop(stiva);
		push(&copie, c);
		if (c.credite >= prag) {
			k++;
		}
	}
	*nr = k;
	Curs* vector = (Curs*)malloc(sizeof(Curs)*k);
	int i = 0;
	while (copie) {
		Curs c = pop(&copie);
		push(stiva, c);
		if (c.credite >= prag) {
			vector[i] = initializareCurs(c.materie, c.credite);
			i++;
		}
	}
	return vector;
}
//-------------- lista dubla
typedef struct NodDublu NodDublu;
typedef struct ListaDubla ListaDubla;
struct NodDublu {
	Curs c;
	NodDublu* prev;
	NodDublu* urm;
};
struct ListaDubla {
	NodDublu* coada;
	NodDublu* cap;
};
void adaugaListaDubla(ListaDubla* lista, Curs c) {
	NodDublu* node = (NodDublu*)malloc(sizeof(NodDublu));
	node->c = initializareCurs(c.materie, c.credite);
	node->prev = NULL;
	node->urm = NULL;
	if (lista->cap == NULL) {
		lista->cap = node;
		lista->coada = node;
	}
	else {
		lista->coada->urm = node;
		node->prev = lista->coada;
		lista->coada = node;
	}
}
void salvareListaDubla(ListaDubla* lista, Nod** stiva, int prag) {
	Nod* copie = NULL;
	while (*stiva) {
		Curs c = pop(stiva);
		push(&copie, c);
		if (c.credite >= prag) {
			adaugaListaDubla(lista, c);
		}
	}
	while (copie) {
		Curs c = pop(&copie);
		push(stiva, c);

	}
}
void afisareListaDubla(ListaDubla* lista) {
	 NodDublu* aux = lista->cap;
	while (aux) {
		afisareCurs(aux->c);
		aux = aux->urm;
	}
}
//----------lista simpla
typedef struct NodSimplu NodSimplu;
struct NodSimplu {
	NodSimplu* next;
	Curs c;
};
void adaugareInSimplu(NodSimplu** lista,Curs c) {
	NodSimplu* node = (NodSimplu*)malloc(sizeof(NodSimplu));
	node->c = initializareCurs(c.materie, c.credite);
	node->next = *lista;
	*lista = node;
}
void salvareInSimplu(Nod** stiva, NodSimplu** lista, int prag) {
	Nod* copie = NULL;
	while (*stiva) {
		Curs c = pop(stiva);
		push(&copie, c);
		if (c.credite >= prag) {
			adaugareInSimplu(lista, c);
		}
	}
	while (copie) {
		Curs c = pop(&copie);
		push(stiva, c);
	}
}
void afisareListSimpla(NodSimplu* lista) {
	NodSimplu* cur = lista;
	while (cur) {
		afisareCurs(cur->c);
		cur = cur->next;
	}
}
void main() {

	Nod* stiva = NULL;
	push(&stiva, initializareCurs("SDD", 5));//ii iau adresa la stiva!!!!!!!
	push(&stiva, initializareCurs("POO", 4));
	push(&stiva, initializareCurs("PAW", 5));
	// afisareStiva(&stiva);
	//afisareCurs(pop(&stiva));
	//suma credite
	//printf("Numar total de credite: %d\n", sumaCredite(stiva));

	//stergere curs POO
	//stergereCurs(&stiva, "POO");
	//verificare
	//printf("Numar total de credite dupa stergere curs POO: %d\n", sumaCredite(stiva));

	//afisare stiva
	//afisareStiva(&stiva);
	//printf("----------------------------");
	//creare vector
	/*
	Curs* vector;
	int nr = 0;
	vector = salvareVector(&stiva, &nr, 5);
	for (int i = 0; i < nr; i++) {
		afisareCurs(vector[i]);
	}*/
	NodSimplu* lista=NULL;
	//
    salvareInSimplu( &stiva, & lista, 5);

	//// Afișare lista dublă
	 afisareListSimpla(lista);

	////afisare stiva iar
	//afisareStiva(stiva);


}


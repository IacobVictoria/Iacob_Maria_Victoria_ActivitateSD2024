#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <string.h>
//arbori binari de cautare (fiecare nod are maxim 2 descendenti)
//un graf aciclic si conex
//orientat
//reguli de asezare-> cautare eficienta
//toate nodurile din dreapta mai mare decat radacina
//descendentii din dr au val mai mare decat nodul parinte
//in stanga e mai mic
// divide et impera 
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
};
void inserareInArbore(Nod** radacina, Cinema c) {
	if (*radacina) //verif daca avem radacina , daca exista arbore
	{
		if ((*radacina)->info.id > c.id)
		{
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else {
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;//nod frunza
		//inserare mereu in nod frunza
		nod->info = c;
		//tr initializez si radacina
		*radacina = nod;
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
			inserareInArbore(&radacina, c);
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


void stergereArbore(Nod** rad)
{
	if ((*rad) != NULL)
	{
		stergereArbore(&(*rad)->st);
		stergereArbore(&(*rad)->dr);
		for (int i = 0; i < (*rad)->info.nrFilme; i++) {
			free((*rad)->info.filme[i]);
		}
		free((*rad)->info.filme);
		free(*rad);
	}
	*rad = NULL;
}
Nod* gasesteMinim(Nod* nod) {
	Nod* curent = nod;
	while (curent && curent->st != NULL) {
		curent = curent->st;
	}
	return curent;
}
int inaltimeArbore(Nod* rad)
{
	if (rad)
	{
		if (inaltimeArbore(rad->st) < inaltimeArbore(rad->dr))
		{
			return inaltimeArbore(rad->dr) + 1;
		}
		else
		{
			return inaltimeArbore(rad->st) + 1;
		}
	}
	else
	{
		return 0;
	}
}
Nod* subarboreCuInaltimeMaxima(Nod* rad) {
	if (rad == NULL) {
		return NULL;
	}

	int inaltimeStanga = inaltimeArbore(rad->st);
	int inaltimeDreapta = inaltimeArbore(rad->dr);

	if (inaltimeStanga > inaltimeDreapta) {
		return rad->st;
	}
	else {
		return rad->dr;
	}
}
void stergeNod(Nod** rad, int id) {
	if (*rad == NULL) {
		return;
	}
	// Cautăm nodul cu id-ul dat
	if (id < (*rad)->info.id) {
		stergeNod(&(*rad)->st, id);
	}
	else if (id > (*rad)->info.id) {
		stergeNod(&(*rad)->dr, id);
	}
	else {
		// Nodul a fost găsit
		// Cazul 1: Nodul este frunza sau are un singur fiu
		if ((*rad)->st == NULL) {
			Nod* temp = (*rad)->dr;
			free((*rad));
			(*rad) = temp;
		}
		else if ((*rad)->dr == NULL) {
			Nod* temp = (*rad)->st;
			free((*rad));
			(*rad) = temp;
		}
		else {
			// Cazul 2: Nodul are doi fii
			// Găsim succesorul sau (în acest caz, cel mai mic nod din subarborele drept)
			Nod* temp = gasesteMinim((*rad)->dr);
			// Înlocuim valoarea nodului curent cu cea a succesorului său
			(*rad)->info = temp->info;
			// Ștergem succesorul
			stergeNod(&(*rad)->dr, temp->info.id);
		}
	}
}
int numarNoduriInSubordine(Nod* rad) {
	if (rad == NULL) {
		return 0;
	}
	else {
		// Numaram nodurile din subarborele stang
		int numarStanga = numarNoduriInSubordine(rad->st);
		// Numaram nodurile din subarborele drept
		int numarDreapta = numarNoduriInSubordine(rad->dr);

		// Adaugam 1 pentru nodul curent
		return numarStanga + numarDreapta+1;
	}
}
Nod* subarboreCuMaiMulteNoduri(Nod* rad) {
	if (rad == NULL) {
		return NULL;
	}

	// Numarul de noduri din subarborele stang
	int numarNoduriStanga = numarNoduriInSubordine(rad->st);
	// Numarul de noduri din subarborele drept
	int numarNoduriDreapta = numarNoduriInSubordine(rad->dr);

	// Returnam radacina subarborelui cu mai multe noduri
	if (numarNoduriStanga > numarNoduriDreapta) {
		return rad->st;
	}
	else {
		return rad->dr;
	}
}
int main() {
	Nod* arbore = NULL;
	arbore = citireFisier("cinema.txt");
	//stergeNod(&arbore, 5);
	stergeNod(&arbore, 8);
	afisareArborePreordine(arbore);
	/*Nod* subarbore = subarboreCuInaltimeMaxima(arbore->st);
	if (subarbore != NULL) {
		printf("Subarborele cu inaltimea maxima este:\n");
		afisareCinema(subarbore->info);
	}
	else {
		printf("Arborele este gol sau are doar un singur nod.\n");
	}

	 int numarNoduri = numarNoduriInSubordine(arbore->dr);
	printf("Numarul de noduri aflate in subordine este: %d\n", numarNoduri-1);

	Nod* subarbore2 = subarboreCuMaiMulteNoduri(arbore->st);

	if (subarbore2 != NULL) {
		printf("Subarborele cu mai multe noduri este:\n");
		afisareCinema(subarbore2->info);
	}
	else {
		printf("Arborele este gol sau are doar un singur nod.\n");
	}*/
	return 0;
}

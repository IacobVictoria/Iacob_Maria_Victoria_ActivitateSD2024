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
Cinema citireCinema(FILE *f) {
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
			c=citireCinema(f);
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
		suma+=calculNrFilmeRedate(rad->st);
		suma += calculNrFilmeRedate(rad->dr);
		return suma;
	}
	else {
		return 0;
	}
}
//stegere nod-> 

int main() {
	Nod* arbore = NULL;
	arbore=citireFisier("cinema.txt");
	afisareArborePreordine(arbore);
	//elem sortate dupe id
	return 0;
}

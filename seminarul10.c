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

void stergeFrunze(Nod** radacina) {
	if (*radacina) {
		if ((*radacina)->st == NULL && (*radacina)->dr == NULL) { // If the current node is a leaf
			free((*radacina)->info.filme); 
			free(*radacina); 
			*radacina = NULL; 
		}
		else { // If the current node is not a leaf
			stergeFrunze(&((*radacina)->st)); 
			stergeFrunze(&((*radacina)->dr)); 
		}
	}
}
void stergereArbore(Nod** rad)
{
	if ((*rad) != NULL)////DOAR POSTORDINE MERGE SA STERG
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
Nod* stergereNodBTS(Nod* radacina, int valoare) {
	// Cazul de bază: dacă arborele este gol
	if (radacina == NULL) {
		return radacina;
	}

	// Dacă valoarea de șters este mai mică decât valoarea din nodul curent,
	// continuăm căutarea în subarborele stâng
	if (valoare < radacina->info.id) {
		radacina->st = stergereNodBTS(radacina->st, valoare);
	}
	// Dacă valoarea de șters este mai mare decât valoarea din nodul curent,
	// continuăm căutarea în subarborele drept
	else if (valoare > radacina->info.id) {
		radacina->dr = stergereNodBTS(radacina->dr, valoare);
	}
	// Dacă am găsit nodul de șters
	else {
		// Nodul curent este nodul de șters

		// Cazul 1: Nodul are cel mult un descendent
		if (radacina->st == NULL) {
			Nod* temp = radacina->dr;
			free(radacina);
			return temp;
		}
		else if (radacina->dr == NULL) {
			Nod* temp = radacina->st;
			free(radacina);
			return temp;
		}

		// Cazul 2: Nodul are doi descendenti
		// Obținem succesorul în ordinea sortării (cel mai mic element din subarborele drept)
		Nod* succesor = radacina->dr;
		while (succesor && succesor->st != NULL) {
			succesor = succesor->st;
		}

		// Copiem valoarea succesorului în nodul curent
		radacina->info = succesor->info;

		// Ștergem succesorul
		radacina->dr = stergereNodBTS(radacina->dr, succesor->info.id);
	}

	return radacina;
}
Nod* stergeDescendent(Nod* radacina, int valoare) {
	// Cazul de bază: arborele este gol
	if (radacina == NULL) {
		return NULL;
	}

	// Cautăm nodul în arbore
	if (valoare < radacina->info.id) {
		// Dacă valoarea este mai mică, continuăm căutarea în subarborele stâng
		radacina->st = stergeDescendent(radacina->st, valoare);
	}
	else if (valoare > radacina->info.id) {
		// Dacă valoarea este mai mare, continuăm căutarea în subarborele drept
		radacina->dr = stergeDescendent(radacina->dr, valoare);
	}
	else {
		// Am găsit nodul căruia îi ștergem un descendent

		// Cazul în care nodul are cel mult un descendent
		if (radacina->st == NULL && radacina->dr == NULL) {
			// Nodul nu are descendenti, nu putem sterge nimic
			return radacina;
		}
		else if (radacina->st != NULL && radacina->dr == NULL) {
			// Nodul are doar descendent stâng
			Nod* temp = radacina->st;
			free(radacina->st);
			radacina->st = NULL;
			return radacina;
		}
		else if (radacina->st == NULL && radacina->dr != NULL) {
			// Nodul are doar descendent drept
			Nod* temp = radacina->dr;
			free(radacina->dr);
			radacina->dr = NULL;
			return radacina;
		}
		else {
			// Nodul are ambii descendenti, putem alege să ștergem unul
			// Pentru exemplificare, vom alege să ștergem descendentul stâng
			Nod* temp = radacina->st;
			free(radacina->st);
			radacina->st = NULL;
			return radacina;
		}
	}

	return radacina;
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

int main() {
	Nod* arbore = NULL;
	arbore=citireFisier("cinema.txt");
	//arbore = stergereNodBTS(arbore, 5);
	//arbore = stergeDescendent(arbore, 5);
	//stergereArbore(&arbore);
	printf("Inalt %d", inaltimeArbore(arbore));
	//stergeFrunze(&arbore);//1,4,10 sunt frunze si le a sters
	afisareArborePreordine(arbore);
	//elem sortate dupe id
//	printf("Nr %d", calculNrFilmeRedate(arbore));
	int nr2 = nrNoduri(arbore);
	printf("nR NODURI:%d \n", nr2);
	return 0;
}

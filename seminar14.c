#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct Camion Camion;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Camion {
	int serie;
	char* marca;
	float greutate;
};

struct NodPrincipal {
	Camion info;
	NodSecundar* vecini;
	NodPrincipal* next;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

// inserare in lista principala la inceput
NodPrincipal* inserarePrincipala(NodPrincipal* graf, Camion c) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = c;
	nou->next = graf;
	nou->vecini = NULL;
	return nou;
}

// functie de cautare NodPrincipal dupa Serie Camion
NodPrincipal* cautaDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) {
		graf = graf->next;
	}
	return graf;
}

// inserare in lista secundara la sfarsit
void inserareSecundara(NodSecundar** cap, NodPrincipal* nod) {
	NodSecundar* nou = (NodSecundar*)(malloc)(sizeof(NodSecundar));
	nou->nod = nod;
	nou->next = NULL;
	if (*cap) {
		NodSecundar* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

//  functie de inserare muchie in lista
void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautaDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaDupaSerie(graf, serieStop);

	inserareSecundara(&(nodStart->vecini), nodStop);
	inserareSecundara(&(nodStop->vecini), nodStart);
}

Camion creeareCamion(int serie, const char* marca, float greutate) {
	Camion c;
	c.serie = serie;
	c.greutate = greutate;
	c.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy(c.marca, marca);
	return c;
}



#pragma region coada

typedef struct NodCoada NodCoada;
struct NodCoada {
	int info;
	NodCoada* next;
};


//inserarea si extragerea capete diferite
//extragerea inceput, inserare sf

void pushCoada(NodCoada** coada, int seria) {

	
		NodCoada* node = (NodCoada*)malloc(sizeof(NodCoada));
		node->next = NULL;
		node->info = seria;
		if (*coada) {

			NodCoada* aux = *coada;
			while (aux->next) {
				aux = aux->next;
			}
			aux->next = node;

		}
		else {
			*coada = node;
		}
}
//return serie pentru pop
int popCoada(NodCoada** coada) {

	if (*coada) {
		int rez = (*coada)->info;
		NodCoada* aux = *coada;
		*coada = (*coada)->next;
		free(aux);
		return rez;
     }
	else {
		return -1;
	}
}




int nrNoduri(NodPrincipal* graf) {
	int nr = 0;
	while (graf) {
		nr++;
		graf = graf->next;
	}
	return nr;
}

void afisareCamion(Camion c) {
	printf("%d . Camionul %s  si greutate %f \n", c.serie, c.marca, c.greutate);
}

//graful+ nr de la care plecam
void AfisareParcurgereLatime(NodPrincipal* graf, int serieStart)
{
	if (graf)
	{
		//coada
		NodCoada* coada = NULL;
		//vector de vizitare de lung -cate noduri avem
		int nrNod = nrNoduri(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNod);
		for (int i = 0; i < nrNod; i++) {
			vizitat[i] = 0; //codul ascii 0
		}

		vizitat[serieStart] = 1; //vizitam nodul de start si il punem in coada
		pushCoada(&coada, serieStart);

		while (coada) {

			int serieCurenta = popCoada(&coada);
			//cautam nod dupa serie
			NodPrincipal* nodCurent = cautaDupaSerie(graf, serieCurenta);
			afisareCamion(nodCurent->info);
			//afisam nodurile
			//inserez in structura mea nodurile nevizitate vecine cu nodul meu extras
			//structura acum e coada
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini) {
				//inseram doar nodurile nevizitate
				if (vizitat[vecini->nod->info.serie] == 0) {
					pushCoada(&coada, vecini->nod->info.serie);
					vizitat[vecini->nod->info.serie] = 1;//marchez ca vizitat
				}
				vecini = vecini->next;
			}
		}
		//dezalocam vectorul de char uri
		if (vizitat)
		{
			free(vizitat);
		}

	}

}
void pushStiva(NodCoada** stiva, int serie) {
	//folosesc aceeasi structura dar fac LIFO, ca tot o lista simpla o sa ma si la stiva ca la coada
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = serie;
	nod->next = *stiva;
	*stiva = nod;

}
int popStiva(NodCoada** stiva) {
	return popCoada(stiva);
}
void AfisareParcurgereAdancime(NodPrincipal* graf, int serieStart)
{
	if (graf)
	{
		//coada
		NodCoada* stiva = NULL;
		//vector de vizitare de lung -cate noduri avem
		int nrNod = nrNoduri(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNod);
		for (int i = 0; i < nrNod; i++) {
			vizitat[i] = 0; //codul ascii 0
		}

		vizitat[serieStart] = 1; //vizitam nodul de start si il punem in coada
		pushStiva(&stiva, serieStart);

		while (stiva) {

			int serieCurenta = popStiva(&stiva);
			//cautam nod dupa serie
			NodPrincipal* nodCurent = cautaDupaSerie(graf, serieCurenta);
			afisareCamion(nodCurent->info);
			//afisam nodurile
			//inserez in structura mea nodurile nevizitate vecine cu nodul meu extras
			//structura acum e coada
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini) {
				//inseram doar nodurile nevizitate
				if (vizitat[vecini->nod->info.serie] == 0) {
					pushStiva(&stiva, vecini->nod->info.serie);
					vizitat[vecini->nod->info.serie] = 1;//marchez ca vizitat
				}
				vecini = vecini->next;
			}
		}

		// sa vizitez si ce am in alta componenta conexa, caut in vectorul de vizitate unde am 0

		if (vizitat)
		{
			free(vizitat);
		}
	}

}
#pragma endRegion

//facem dezalocare
void stergereListaVecini(NodSecundar** vecini) {
	while (*vecini) {
		NodSecundar* aux = *vecini;
		*vecini = (*vecini)->next;
		free(aux);
	}
}
void stergereGraf(NodPrincipal** graf) {
	while (*graf) {
		NodPrincipal* p = *graf;
		free(p->info.marca);
		stergereListaVecini(&(p->vecini));
		(*graf) = p->next; // sau (*graf)->next;  mut graful pe nodul urm
		free(p);
	}
}
void main() {
	NodPrincipal* graf = NULL;
	// inseram 5 noduri cu id urile 0 1 2 3 4

	graf = inserarePrincipala(graf, creeareCamion(4, "Scania", 20));
	graf = inserarePrincipala(graf, creeareCamion(3, "Volvo", 30));
	graf = inserarePrincipala(graf, creeareCamion(2, "Renault", 50));
	graf = inserarePrincipala(graf, creeareCamion(1, "MAN", 15));
	graf = inserarePrincipala(graf, creeareCamion(0, "Mercedes", 40));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 0, 3);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 1, 3);

	AfisareParcurgereAdancime(graf, 4);
	stergereGraf(&graf);
	AfisareParcurgereLatime(graf, 4);

}
//parcurgere adancime : 4 2 1 0 3  sau 4 3 0 1 2 , 43102   -folosesc stiva
// si latime : 4 2 3 1 0 sau 4 3 2 0 1    - folosesc coada

//in lista princ am toate nodurile  chiar daca e alta componenta conexa, vecinii sunt doar in listele adiacente

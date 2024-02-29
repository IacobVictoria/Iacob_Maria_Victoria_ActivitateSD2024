
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <malloc.h>

struct Avion {
	char* companie;
	float bilet;
	int nrPasageri;
};
//citeste de la tastatura
struct Avion citesteAvion() {
	struct Avion a;
	printf("Compania este: ");
	getchar();
	char buffer[100];
	fgets(buffer, sizeof(buffer), stdin);
	buffer[strcspn(buffer, "\n")] = '\0';
	a.companie = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(a.companie, buffer);

	printf("Introduceti pretul biletului: ");
	scanf("%f", &a.bilet);

	printf("Introduceti nr de pasageri: ");

	scanf("%d", &a.nrPasageri);
	return a;
}

void ScriereAvioaneInFisier(int nr) {
	//o sa scriu intr-un fisier nr Avioane
	FILE* f;
	f = fopen("date1.txt","w");
	if (f == NULL) {
		printf("No way");
		return;
	}
	for (int i = 0; i < nr; i++) {
		struct Avion avion = citesteAvion();
		fprintf(f,"%5.2f\n%s\n%d\n", avion.bilet, avion.companie, avion.nrPasageri);
	}
	fclose(f);
}
struct Avion citesteFisierAvion() {
	FILE* f;
	f = fopen("date1.txt", "r");
	if (f == NULL) {
		printf("Nu se poate deschide fisierul");
		return;
	}
	struct Avion a;
	fscanf(f, "%f", &a.bilet);
	fgetc(f);
	//ESTE BINE SA NU CITESC PRIMA DATA CHAR*
	
	char buffer[100];
	fgets(buffer, sizeof(buffer), f);
	buffer[strcspn(buffer, "\n")] = '\0';
	a.companie = (char*)malloc(strlen(buffer) + 1);
	strcpy(a.companie, buffer);

	
	fscanf(f, "%d", &a.nrPasageri);

	return a;


}

struct Avion initializeaza(const char* companie, float bilet, int nrPasageri) {
	struct Avion a;
	a.bilet = bilet;
	a.nrPasageri = nrPasageri;
	a.companie = (char*)malloc(sizeof(char) * (strlen(companie) + 1));
	strcpy(a.companie, companie);
	return a;
}
void initializeazaVector(struct Avion* a, int nr) {
	for (int i = 0; i < nr; i++) {
		a[i] = initializeaza("Tarom", i + 500 * (i + 1), i + 10);
	}

}
void afiseaza(struct Avion a) {
	printf("Compania %s are %d pasageri si biletul este %5.2f\n", a.companie, a.nrPasageri, a.bilet);

}
void afisareVector(struct Avion* avioane, int nr) {
	if (avioane != NULL) {
		for (int i = 0; i < nr; i++) {
			afiseaza(avioane[i]);
		}
	}
	else {
		struct Avion a = initializeaza("N\A", -1, -1);
		afiseaza(a);

	}

}
void reducePreturile(struct Avion* a, int nr) {
	for (int i = 0; i < nr; i++) {
		a[i].bilet = -5;
	}
}
void schimbaCompaniaAvioanelorPretSubLimita(struct Avion* a, int nr, float prag) {
	for (int i = 0; i < nr; i++)
	{
		if (a[i].bilet < prag) {
			free(a[i].companie);
			a[i].companie = (char*)malloc(sizeof(char) * (strlen("Aero") + 1));
			strcpy(a[i].companie, "Aero");
		}
	}
}

void dezalocare(struct Avion** avioane, int* nr) {
	if ((*avioane) != NULL) {
		for (int i = 0; i < *nr; i++) {
			free((*avioane)[i].companie);
		}
		free(*avioane);
		*nr = 0;
		*avioane = NULL;
	}
}

void copiazaAvioaneCuBileteReduse(struct Avion* avioane, int nrAvioane, float prag, struct Avion** avioaneNou, int* nrNou) {
	if (avioaneNou != NULL) {
		dezalocare(avioaneNou, nrNou);
	}
	else {
		*nrNou = 0;
	}

	for (int i = 0; i < nrAvioane; i++) {
		if (avioane[i].bilet < prag) {
			(*nrNou)++;
		}
	}
	*avioaneNou = (struct Avion*)malloc(sizeof(struct Avion) * (*nrNou));
	int k = 0;
	for (int i = 0; i < nrAvioane; i++) {
		if (avioane[i].bilet < prag) {
			(*avioaneNou)[k++] = initializeaza(avioane[i].companie, avioane[i].bilet, avioane[i].nrPasageri);
		}
	}

}

struct Avion PrimulAvionCompanie(struct Avion* avioane, int nr, const char* nume) {
	if (avioane != NULL) {
		for (int i = 0; i < nr; i++) {
			if (strcmp(avioane[i].companie, nume) == 0){
				return initializeaza(avioane[i].companie,avioane[i].bilet,avioane[i].nrPasageri);
				//ca sa nu faca shallow copy face initializeaza
			}
		}
	}
}
struct Avion* copiazaPrimeleN(struct Avion* avioane, int nr, int nrNou) {
	struct Avion* avioaneCopiate = (struct Avion*)malloc(sizeof(struct Avion) * nrNou);

	for (int i = 0; i < nr; i++) {
		avioaneCopiate[i] = initializeaza(avioane[i].companie, avioane[i].bilet, avioane[i].nrPasageri);
	}
	return avioaneCopiate;
}
//sa fac aceeasi functie cu avioaneNou** in lista de param
void copiazaPrimeleNAvioane(struct Avion* avioane, int nrAvioane, struct Avion** avioaneNou, int* nrNou,int n) {
	if (*avioaneNou != NULL) {
		dezalocare(avioaneNou, nrNou);
	}
	else {
		*nrNou = 0;
	}
	(*nrNou) = n;
	if (avioane != NULL) {
		*avioaneNou = (struct Avion*)malloc(sizeof(struct Avion)*(*nrNou));
		for (int i = 0; i < n; i++) {
			(*avioaneNou)[i] = initializeaza(avioane[i].companie, avioane[i].bilet, avioane[i].nrPasageri);
		}
		
	}
	else { printf( "is null"); }
}
//citeste din fisier un nr de avioane dat ca param si pune le intr un vector deja existent
void creeazaVector(int nr, struct Avion** nouAv, int* nrNou) {
	FILE* f;
	f = fopen("date1.txt", "r");
	if (f == NULL) {
		printf("Nu s-a putut deschide fisierul.\n");
		return;
	}
	if (*nouAv != NULL) {
		dezalocare(nouAv, nrNou);
	}
	else {
		*nrNou = nr;
	}
	*nouAv = (struct Avion*)malloc(sizeof(struct Avion) * (*nrNou));
	for (int i = 0; i < *nrNou; i++) { 
		struct Avion a;
		fscanf(f, "%f", &a.bilet);
		fgetc(f);                                    // nu pot sa folosesc citireFisierAvion pt ca o sa mi l citeasca mereu pe primul
		char buffer[100];
		fgets(buffer, sizeof(buffer), f);
		buffer[strcspn(buffer, "\n")] = '\0';
		a.companie = (char*)malloc(strlen(buffer) + 1);
		strcpy(a.companie, buffer);
		fscanf(f, "%d", &a.nrPasageri);
		(*nouAv)[i] = a;
	}
}
////creaza vector de la zero care contine primele 3 avionele tarom din fisier
//struct Avion* creezAvioaneTarom(int nr) {
//
//
//}


void main() {
	struct Avion a = initializeaza("Tarom", 200, 2);
	//afiseaza(a);
	int nrAvioane = 5;
	struct Avion* avioane = (struct Avion*)malloc(sizeof(struct Avion) * nrAvioane);
	initializeazaVector(avioane, nrAvioane);
	//schimbaCompaniaAvioanelorPretSubLimita(avioane,nrAvioane,1500);
	//struct Avion* bileteReduse=NULL;
	//int nrReduse = 0;
	//copiazaAvioaneCuBileteReduse(avioane, nrAvioane,1500, &bileteReduse, &nrReduse);
	////afisareVector(bileteReduse,nrReduse);
	//struct Avion nou = PrimulAvionCompanie(avioane, 5, "Tarom");
	//struct Avion* cop = copiazaPrimeleN(avioane, 5, 2);

	//
	struct Avion* copiateAv = NULL;
	int nrAvCopiate = 0;

	copiazaPrimeleNAvioane(avioane, nrAvioane, &copiateAv, &nrAvCopiate,4);
	//

	//afisareVector(copiateAv,nrAvCopiate);



	//etapa cu fisiere si citire tastatura
	//struct Avion a1 = citesteAvion();
	
	/*int nAv1 = 3;
	struct Avion* av1=(struct Avion*)malloc(sizeof(struct Avion) * nAv1);           //citeste vector tastatura
	for (int i = 0; i < nAv1; i++) {
		av1[i] = citesteAvion();
	}*/
	//afisareVector(av1,nAv1);


	//citeste vector fisier
	
	struct Avion  avv = citesteFisierAvion();
	afiseaza(avv);

	//
	//ScriereAvioaneInFisier(3);

	struct Avion* avioaneNou = NULL;
	int nouNrr = 0;
	
	creeazaVector(2,&avioaneNou, &nouNrr);
	afisareVector(avioaneNou, nouNrr);

}

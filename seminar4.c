#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Locuinta {
	int id;
	char* strada;
	int numar;
};

void afisareLocuinta(struct Locuinta l) {
	printf("ID-ul: %d Strada: %s Numarul: %d\t", l.id, l.strada, l.numar);
}

void afisareVectorLocuinta(struct Locuinta* vector, int dim)
{
	for (int i = 0; i < dim; i++) {
		afisareLocuinta(vector[i]);
	}
}

void inserareLocuintaInVector(struct Locuinta** vector, int* dim, struct Locuinta l) {
	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) * (++(*dim)));
	for (int i = 0; i < (*dim) - 1; i++) {
		copie[i] = (*vector)[i];
	}
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL) {
		free((*vector));
	}
	(*vector) = copie;
}

void stergeLocuinta(struct Locuinta** vector, int* dim, int id) {
	int pozitie = -1; // Initialize with an invalid position
	for (int i = 0; i < *dim; i++) {
		if ((*vector)[i].id == id) {
			pozitie = i; // Store the position of the item to be deleted
			break;
		}
	}

	if (pozitie != -1) { // Check if the item was found
		struct Locuinta* copie = malloc(sizeof(struct Locuinta) * (*dim - 1));
		if (copie == NULL) {
			// Handle memory allocation failure
			printf("Memory allocation failed\n");
			return;
		}

		int j = 0;
		for (int i = 0; i < *dim; i++) {
			if (i != pozitie) {
				copie[j++] = (*vector)[i];
			}
		}
		(*dim)--;
		free(*vector);
		*vector = copie;
	}
}

void citesteFisier(const char* nume_fisier, struct Locuinta** vector, int* dim) {
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitator); //strtok lasa un flag in buffer pe care il cauta la urmatorul apel
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator); // folosim NULL pt a continua de unde a ramas apelul precedent
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				inserareLocuintaInVector(vector, dim, locuinta);
			}
		}
		fclose(f);
	}
}



void citesteMatriceLocuinta(const char* nume_fisier, struct Locuinta** matrice, int nr_linii, int* nr_coloane)
{//nu schimb adresa deci nu transmit prin referinta, clusterele le am decis in main nu le modific(nr_linii), eu modific doar ce contine
	//nu modific adresa nr coloane, deci nu e  prin referinta
	//MODIFIC CONTINUTUL NU ADRESA
	if (nume_fisier != NULL && strlen(nume_fisier) > 0) {
		FILE* f = fopen(nume_fisier, "r");
		if (f != NULL) {
			char buffer[100];
			char delimitator[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {
				char* token;
				token = strtok(buffer, delimitator); //strtok lasa un flag in buffer pe care il cauta la urmatorul apel
				struct Locuinta locuinta;
				locuinta.id = atoi(token);
				token = strtok(NULL, delimitator); // folosim NULL pt a continua de unde a ramas apelul precedent
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);
				token = strtok(NULL, delimitator);
				locuinta.numar = atoi(token);
				int pozitie;
				 pozitie = locuinta.numar%2;
				inserareLocuintaInVector(&(matrice[pozitie]), &(nr_coloane[pozitie]), locuinta);
			}
		}
		fclose(f);
	}

}
void afisareMatrice(struct Locuinta** matrice, int nr_linii, int* nr_coloane) {
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_coloane[i]; j++) {
			afisareLocuinta(matrice[i][j]);
			
		}
		printf("\n");
	}
	
}

//id-urile locuintelor de numar par(dupa criteriul dupa care s a facut clusterizarea)
void afisareIdDePeOParte(int paritate,struct Locuinta** matrice, int nr_linii, int* nr_coloane) {
	paritate = paritate % 2;//ca sa nu dam alte numere inafara de 0 si 1
	
		for (int j = 0; j < nr_coloane[paritate]; j++) { //merg direct pe linia cu paritatea respectiva
			//pe linia cu paritate 0 am nr pare iar paritate 1 are elem impare, deci nu tr sa merg prin toata matricea

				printf("%d ", matrice[paritate][j].numar);

		
	}


}

//cautam locuinta dupa id
struct Locuinta cautLocDupaId(int idCautat, struct Locuinta** matrice, int nr_linii, int* nr_coloane) {
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_coloane[i]; j++) {
			if (matrice[i][j].id == idCautat) {
				return matrice[i][j];
			}

		}
	
	}
	//daca  nu am gasit id-ul 
	struct Locuinta copie;
	copie.id = -1;
	copie.numar = -1;
	copie.strada = NULL;
	return copie;
}
void dezalocareMatrice(struct Locuinta*** matrice, int* nrLinii, int** nrElementeLinie) {
	for (int i = 0; i < *nrLinii; i++) {
		for (int j = 0; j < (*nrElementeLinie)[i]; j++) {
			free((*matrice)[i][j].strada);//dereferentiem matrice si dupa o indexam(*matrice)[i][j]


		}
		if ((*matrice)[i]) {
			free((*matrice)[i]);
		}
	}
	free(*matrice);//avem alocat si o sa i fac  free
	*matrice = NULL;//am sters acum il setez cu null
	free(*nrElementeLinie);
	*nrElementeLinie = NULL;
	*nrLinii = 0;
	
}
//sa-i modific numarul si o sa fie pe alta linie in matrice daca fac din par in impar
//nu o modific
//void schimbareNumarLocuinta(struct Locuinta** matrice, int nr_linii, int* nr_coloane, int nr_locuinta) {
	//int pozitie = nr_locuinta % 2;
	//int id_loc = -1;
	//int index_vector = -1;
	//for (int i = 0; i < nr_coloane[pozitie]; i++) {
	//	if (matrice[pozitie][i].numar == nr_locuinta) {
	//		//l am identificat
	//		matrice[pozitie][i].numar++; // cresc numarul cu o unitate/
	//		//il eliminam si il mutam in cealalta parte
	//		id_loc = matrice[pozitie][i].id;
	//		//salvez id-ul loc
	//		index_vector = i;
	//	}
	//}
	//if (id_loc != -1) {
	//	//matricea este un vector de vectori
	//	int index = ((nr_locuinta + 1) % 2);// sa ne duca in cealalta parte, daca e par acum sa fie impar, sa fie pus in vcetorul cu impare, sa pun in celalat vector
	//	inserareLocuintaInVector(&(matrice[index]), &(nr_coloane[index]), matrice[pozitie][index_vector]);
	//		//matrice[index] este un vector, il punem in noul vector, vectorul opus matrice[index]

	//	stergeLocuinta(&(matrice[pozitie]), &(nr_coloane[pozitie]), id_loc);
	//		//stergem din locul lui initial din vectorul matrice[pozitie]
	//}
void schimbareNrLocuinta(struct Locuinta** matrice, int nr_linii, int* nr_coloane, int nrLocuinta)
{
	int pozitie = nrLocuinta % 2;
	int idLocuinta = -1;
	int indexInVector = -1;
	for (int i = 0; i < nr_coloane[pozitie]; i++)
	{
		if (matrice[pozitie][i].numar == nrLocuinta)
		{
			matrice[pozitie][i].numar++;
			idLocuinta = matrice[pozitie][i].id;
			indexInVector = i;
		}
	}
	if (idLocuinta != -1)
	{
		int index = ((nrLocuinta + 1) % 2);
		inserareLocuintaInVector(&matrice[index], &(nr_coloane[index]), matrice[pozitie][indexInVector]);
		stergeLocuinta(&(matrice[pozitie]), &(nr_coloane[pozitie]), idLocuinta);
	}
}

void main()
{
	int nr_linii;
	int* nr_coloane;//retine adresa, are 2 elem, nu modifica adresa si continut
	struct Locuinta** matrice;
	nr_linii = 2;
	nr_coloane = (int*)malloc(sizeof(int) * nr_linii);
	matrice = (struct Locuinta**)malloc(sizeof(struct Locuinta*) * nr_linii);
	for (int i = 0; i < nr_linii; i++) {
		matrice[i] = NULL;        //initilizare matrice
		(nr_coloane)[i] = 0;
	}
	citesteMatriceLocuinta("locuinte.txt", matrice, nr_linii, nr_coloane);
	afisareMatrice(matrice, nr_linii, nr_coloane);
	afisareIdDePeOParte(1, matrice, nr_linii, nr_coloane);
	struct Locuinta loc=cautLocDupaId(19, matrice, nr_linii, nr_coloane);
	afisareLocuinta(loc);
	
	schimbareNrLocuinta(matrice, nr_linii, nr_coloane, 2);
	afisareMatrice(matrice, nr_linii, nr_coloane);
	dezalocareMatrice(&matrice, &nr_linii, &nr_coloane);
}

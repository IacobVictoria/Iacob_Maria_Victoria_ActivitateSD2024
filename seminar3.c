#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Locuinta {
	int id;
	char* strada;
	int numar;

};
//modific deci transmit prin adresa **vector(primul * este ca este vector si al doilea ca este prin referinta), si * dim, 
void inserareLocuinta(struct Locuinta** vector, int* dim, struct Locuinta l) {
	struct Locuinta* copie;
	//+1 pt ca adaug o locuinta l
	//++ ca sa ramana modificat "dim" ul si jos
	copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) *(++ (*dim)));
	for (int i = 0; i < (*dim)-1; i++) {
		copie[i] = (*vector)[i]; // important de pus (*vector), parantezele,  e ok sa fac shallow copy, ca sa nu mai sterg mai jos , ca ambele pointeaza catre acelasi obiect acum
	}//atribuire pointeri  
	copie[(*dim) - 1] = l;
	if ((*vector) != NULL) {
		free((*vector));
}
	(*vector) = copie;

}

void citesteFisier(const char* numeFisier, struct Locuinta** vector, int* dim) {


	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL) {
			(*dim) = 0;
			while (!feof(f)) {
				char buffer[100]; //linia din fisier
				char delimitator[] = ",\n";
				while (fgets(buffer, 100, f) != NULL) {
					// ne va returna un pointer pe care o sa l verificam
					char* token;

					token = strtok(buffer, delimitator); // sir de delimitari
					struct Locuinta locuinta;
					locuinta.id = atoi(token);  // atoi din string in integer ( atoi=asci to int)
					token = strtok(NULL, delimitator); // nu ii mai dam buffer, ca sa plece de unde a ramas ii dau NULL
					locuinta.strada = (char*)malloc(strlen(token) + 1);
					strcpy(locuinta.strada, token);
					token = strtok(NULL, delimitator);
					locuinta.numar = atoi(token); // daca aveam float puneam .........
					inserareLocuinta(vector, dim, locuinta);

				}
			}
			fclose(f);
		}

	}
}
void afisareLocuinte(struct Locuinta l) {
	printf("Id-ul: %d\nStrada: %s numarul %d\n", l.id, l.strada, l.numar);

}
//le transmitem prin valoare ca nu le modificam

void afisareVector(struct Locuinta* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareLocuinte(vector[i]);
	}
}
//transmitere prin adresa la ambele, daca se modif
void stergeLocuinta(struct Locuinta** vector, int* dim, int id) {
	char flag = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			// Marca?i locuin?a de ?ters ?i continua?i itera?ia
			// pentru a le ?terge pe toate
			break;
		}
	}

	if (flag == 1) {
		struct Locuinta* copie = (struct Locuinta*)malloc(sizeof(struct Locuinta) * ((*dim) - 1));

		int j = 0; // Indice pentru noua copie
		for (int i = 0; i < (*dim); i++) {
			if ((*vector)[i].id != id) {
				copie[j++] = (*vector)[i];
			}
		}

		(*dim)--;
		free(*vector);
		*vector = copie;
	}
}

void main() {
	struct Locuinta* vector = NULL;
	int dim = 3;
	citesteFisier("locuinte.txt", &vector, &dim);
	printf("\n");
	stergeLocuinta(&vector, &dim, 20);
	//NU merge stergerea
	afisareVector(vector, dim);

}

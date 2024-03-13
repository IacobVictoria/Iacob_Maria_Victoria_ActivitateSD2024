#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Student {
	char* nume;
	int anUniversitar;

};
struct Node {
	struct Student* student;
	struct Node* pNext;
};
typedef struct Student StudentInfo;
typedef struct Node ListNode;

StudentInfo* creareStudent(char* nume, int anUniversitar) {
	StudentInfo* stud = NULL;
	stud = (StudentInfo*)malloc(sizeof(StudentInfo));
	stud->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(stud->nume, nume);
	stud->anUniversitar = anUniversitar;
	return stud;
}
ListNode* creareNod(StudentInfo* student) {
	ListNode* node = NULL;
	node = (ListNode*)malloc(sizeof(ListNode));
	node->pNext = NULL;
	node->student = student;
	return node;
}
ListNode* inserareInceputLista(ListNode* lista, StudentInfo* student) {
	ListNode* node = creareNod(student);
	node->pNext = lista;
	return node;
}
void afisareLista(ListNode* lista) {
	while (lista) {
		printf("Studentul %s, An universitar %d \n", lista->student->nume, lista->student->anUniversitar);
		lista = lista->pNext;
	}
}
ListNode* inserareSfarsitLista(ListNode* lista, StudentInfo* student) {
	ListNode* node = creareNod(student);

	if (lista == NULL) {
		// Dacă lista este goală, noul nod devine lista
		return node;
	}

	// Parcurgeți lista până la ultimul nod
	ListNode* current = lista;
	while (current->pNext != NULL) {
		current = current->pNext;
	}

	// Legați noul nod la sfârșitul listei
	current->pNext = node;

	return lista;
}

//sterge un nod de pe o pozitie data ca parametru
ListNode* stergereNodPoz(ListNode* lista, int poz) {
	int index = 1;
	ListNode* aux = NULL;
	if (poz == 1) {
		ListNode* aux = lista;
		lista = lista->pNext;
	}
	else if (poz > 1) {
		ListNode* i = lista;
		while (i && index++ < poz - 1) {
			i = i->pNext;
		}
		if (i && i->pNext) {
			ListNode* aux = i->pNext;
			i->pNext = aux->pNext;
		}
	}
	if (aux) {
		free(aux->student->nume);
		free(aux->student);
		free(aux);
	}
	return lista;
}
void sortareListaDupaAn(ListNode* lista) {
	for (ListNode* aux = lista; aux; aux = aux->pNext) {
		for (ListNode* saux = aux; saux; saux = saux->pNext) {
			if (aux->student->anUniversitar > saux->student->anUniversitar) {
				StudentInfo* temp = aux->student;
				aux->student = saux->student;
				saux->student = temp;
			}
		}
	}
}

void inserareSortata(ListNode** lista, StudentInfo* student) {
	// Sortați lista înainte de inserarea noului student
	sortareListaDupaAn(*lista);

	// Creează un nod nou pentru noul student
	ListNode* nouNod = creareNod(student);

	// Verifică cazurile speciale pentru inserare la începutul listei
	if (*lista == NULL || (*lista)->student->anUniversitar >= student->anUniversitar) {
		nouNod->pNext = *lista;
		*lista = nouNod;
		return;
	}

	// Găsește poziția corectă pentru inserare
	ListNode* current = *lista;
	while (current->pNext != NULL && current->pNext->student->anUniversitar < student->anUniversitar) {
		current = current->pNext;
	}

	// Inserează noul nod între current și current->pNext
	nouNod->pNext = current->pNext;
	current->pNext = nouNod;
}
StudentInfo* salvareInVector(ListNode* lista, int* dimensiune, int anUniversitarCautat) {
	*dimensiune = 0;
	ListNode* curent = lista;
	while (curent) {
		if (curent->student->anUniversitar == anUniversitarCautat) {
			(*dimensiune)++;
		}
		curent = curent->pNext;
	}
	
	StudentInfo* vector = (StudentInfo*)malloc(sizeof(StudentInfo) * (*dimensiune));
	if (vector == NULL) {
		printf("Eroare la alocarea memoriei pentru vector.");
		return NULL;
	}

	int index = 0;
	ListNode* aux = lista;
	while (aux) {
		if (aux->student->anUniversitar == anUniversitarCautat) {
			vector[index].nume = (char*)malloc(strlen(aux->student->nume) + 1);
			strcpy(vector[index].nume, aux->student->nume);
			vector[index].anUniversitar = aux->student->anUniversitar;
			index++;
		}
		aux = aux->pNext;
	}
	return vector;
}
void interschimbareElemente(ListNode* lista, int pozitie1, int pozitie2) {
	
	if (lista == NULL || pozitie1 < 1 || pozitie2 < 1) {
		printf("Lista este goala sau pozițiile sunt invalide.\n");
		return;
	}
	int index = 1;
  
	ListNode* nod1 = NULL, * nod2 = NULL;

	ListNode* curent = lista;
	while (curent != NULL) {
		if (index == pozitie1) {
			nod1 = curent;
		}
		if (index == pozitie2) {
			nod2 = curent;
		}
		curent = curent->pNext;
		index++;
	}

	if (nod1 == NULL || nod2 == NULL) {
		printf("Poziții invalide.\n");
		return;
	}

	StudentInfo* temp = nod1->student;
	nod1->student = nod2->student;
	nod2->student = temp;
}

void afisareVector(StudentInfo* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		printf("Studentul %s este anul %d\n", vector[i].nume, vector[i].anUniversitar);
	}
}

void  main() {
	FILE* f = fopen("studenti.txt", "r");
	ListNode* listaPrincipala = NULL;
	StudentInfo* student = NULL;
	char* token;
	char delimitator[] = ",\n";
	char buffer[100];
	char* nume; int anUniversitar;
	if (f) {
		while (fgets(buffer, sizeof(buffer), f)) {
			token = strtok(buffer, delimitator);
			nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(nume, token);
			token = strtok(NULL, delimitator);
			anUniversitar = atoi(token);

			student = creareStudent(nume, anUniversitar);
			listaPrincipala =inserareSfarsitLista(listaPrincipala, student);
		}
	}
	//1.
	//stergereNodPoz(listaPrincipala, 2);
	//2.
	StudentInfo* stud=creareStudent("Raul", 2);
	inserareSortata(&listaPrincipala, stud);
	//3.
	int dim = 0;
	StudentInfo* vector = salvareInVector(listaPrincipala, &dim, 2);
	//afisareVector(vector, dim);
	//4.   2 pozitii interschimbate
	interschimbareElemente(listaPrincipala, 1, 3);

	afisareLista(listaPrincipala);

}

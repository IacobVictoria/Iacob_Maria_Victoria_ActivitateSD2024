#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>

//radacina < informatiile din fii directi
//fac minim de jos , le inversez ca sa am minimul pe prima poz

//pozitiile fiilor: mapam pozitiile in vectorul nostru, fiul stanga=2*p+1, fiu dreapta=2*p+2
typedef struct Quiz Quiz;
typedef struct Heap Heap;
struct Quiz {
	char* materie;
	int grileGresite;
};
struct Heap {
	Quiz* vector;
	int dimensiune;
	int dimensiuneTotala;

};
Heap initializareHeap(int nr) {
	Heap heap;
	heap.vector = (Quiz*)malloc(sizeof(Quiz) * nr);
	heap.dimensiuneTotala = nr;
	heap.dimensiune = 0;

return heap;//mereu returnat
}

Heap adaugareQuiz(Quiz quiz,Heap  heap) {
	if (heap.dimensiune < heap.dimensiuneTotala) {
		heap.vector[heap.dimensiune] = quiz;
		//shallow copy
		heap.dimensiune++;
		//filtrare, adaug element tr sa filtrez tot iar ca sa fie iar minimul sus
	}
	return heap;
}
Quiz initializareQuiz(char* materie, int grileGresite) {
	Quiz q;
	q.grileGresite = grileGresite;
	q.materie = (char*)malloc(strlen(materie) + 1);
	strcpy(q.materie, materie);
	return q;
}
void afisareQuiz(Quiz q) {
	printf("Quiz la materia %s are %d grile gresite\n", q.materie, q.grileGresite);
}
void afisareHeap(Heap h) {
	for (int i = 0; i < h.dimensiune; i++) {
		afisareQuiz(h.vector[i]);
	}
}
void afisareTotalaHeap(Heap h) {
	for (int i = 0; i < h.dimensiuneTotala; i++) {
		afisareQuiz(h.vector[i]);
	}
}
void filtreazaHeap(Heap heap, int pozRadacina) {
	//vizibil am pana la dimensiune
	int nodSt = pozRadacina * 2 + 1;
	int nodDr = pozRadacina * 2 + 2;
	int indxMin = pozRadacina;
	if (nodSt < heap.dimensiune && heap.vector[nodSt].grileGresite < heap.vector[indxMin].grileGresite) {
		indxMin = nodSt;
	}

	if (nodDr < heap.dimensiune && heap.vector[nodDr].grileGresite < heap.vector[indxMin].grileGresite) {
		indxMin = nodDr;
		//exista nod si este mai mic decat cel din s
	}

	if(indxMin!=pozRadacina){
		Quiz aux;
		aux = heap.vector[pozRadacina];
		heap.vector[pozRadacina] = heap.vector[indxMin];
		heap.vector[indxMin] = aux;
		if(indxMin*2+1<heap.dimensiune-1)// daca nodul pozmin are copii
		filtreazaHeap(heap, indxMin);

	}


}
Quiz extrageMinim(Heap* heap) {//modificam dimensiunea transmitem prin pointer
	if (heap->dimensiune > 0) {
		Quiz aux;
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dimensiune - 1];
		heap->vector[heap->dimensiune - 1] = aux;
		//am schimbat primul elem cu ultimul
		heap->dimensiune--;
		//am ascuns ultimul elem

		for (int i = (heap->dimensiune) / 2 - 1; i >= 0; i--)
		{
			filtreazaHeap(*heap, i);
		}
		return aux;
		//refiltram
	
	}
	else {
		return initializareQuiz('N/A', -1);
	}
}
void dezalocareTotalaHeap(Heap *heap) {
	for (int i = 0; i < heap->dimensiuneTotala; i++) {
		free(heap->vector[i].materie);
	}
	free(heap->vector);
	heap->dimensiune = 0;
	heap->dimensiuneTotala = 0;
	heap->vector = NULL;
}
int main() {
	Heap heap;
	heap = initializareHeap(6);
	heap.vector[0] = initializareQuiz("Sdd", 3);
	heap.vector[1] = initializareQuiz("Java", 7);
	heap.vector[2] = initializareQuiz("Analiza", 5);
	heap.vector[3] = initializareQuiz("C#", 2);
	heap.vector[4] = initializareQuiz("POO", 9);
	heap.vector[5] = initializareQuiz("Macro", 4);
	heap.dimensiune = 6;
	afisareHeap(heap);
	for (int i = (heap.dimensiune) / 2 - 1; i >= 0; i--)
	{
		filtreazaHeap(heap, i);
	}
	printf("\n\n");
	afisareHeap(heap);
	printf("---------------\n");
	afisareQuiz(extrageMinim(&heap));
	afisareQuiz(extrageMinim(&heap));
	afisareQuiz(extrageMinim(&heap));
	afisareQuiz(extrageMinim(&heap));
	afisareQuiz(extrageMinim(&heap));
	afisareQuiz(extrageMinim(&heap));
	printf("---------------\n");
	afisareHeap(heap);
	
}

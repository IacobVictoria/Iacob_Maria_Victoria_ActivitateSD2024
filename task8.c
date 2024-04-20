#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Pacient Pacient;
typedef struct Heap Heap;
struct Pacient {
	char* nume;
	int gradUrgenta;
};
struct Heap {
	Pacient* vector;
	int dim;
	int dimTotal;
};
Heap initializareHeap(int dim) {
	Heap h;
	h.vector = (Pacient*)malloc(sizeof(Pacient) * dim);
	h.dim = 0;
	h.dimTotal = dim;
	return h;
}
Pacient initializarePacient(char* nume, int ur) {
	Pacient p;
	p.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(p.nume, nume);
	p.gradUrgenta = ur;
	return p;

}
Heap adaugarePacient(Pacient p, Heap h) {
	if (h.dim < h.dimTotal) {
		h.vector[h.dim] = initializarePacient(p.nume, p.gradUrgenta);
		h.dim++;
	}
	return h;
}
void filtrareHeap(Heap heap, int rad) {
	int nodSt = rad * 2 + 1;
	int nodDr = rad * 2 + 2;
	int indMax = rad;
	if (nodDr<heap.dim && heap.vector[nodDr].gradUrgenta>heap.vector[indMax].gradUrgenta) {
		indMax = nodDr;
	}
	if (nodSt<heap.dim && heap.vector[nodSt].gradUrgenta>heap.vector[indMax].gradUrgenta) {
		indMax = nodSt;
	}
	if (indMax != rad) {
		Pacient p = heap.vector[indMax];
		heap.vector[indMax] = heap.vector[rad];
		heap.vector[rad] = p;
		if (indMax * 2 + 1 < heap.dim-1) {
			filtrareHeap(heap, indMax);
		}
	}
}
Pacient extrageMaxim(Heap* h) {
	if (h->dim > 0) {
		Pacient aux = h->vector[0];
		h->vector[0] = h->vector[h->dim - 1];
		h->vector[h->dim - 1] = aux;
		h->dim--;
		for(int i = (h->dim) / 2 - 1; i >= 0; i--) {
			filtrareHeap(*h, i);
		}
		return aux;
	}
	else {
		return initializarePacient("N/A", -1);
	}
}
void afisarePacient(Pacient p) {
	printf("Pacientul %s cu grad urgents %d\n", p.nume, p.gradUrgenta);

}
void afisareHeap(Heap h) {
	for (int i = 0; i < h.dim; i++) {
		afisarePacient(h.vector[i]);
	}
}
void dezalocareTotalaHeap(Heap* heap) {
	for (int i = 0; i < heap->dimTotal; i++) {
		free(heap->vector[i].nume);
	}
	free(heap->vector);
	heap->dim = 0;
	heap->dimTotal = 0;
	heap->vector = NULL;
}
void main() {
	Heap heap = initializareHeap(10);

	heap = adaugarePacient(initializarePacient("John", 3), heap);
	heap = adaugarePacient(initializarePacient("Alice", 5), heap);
	heap = adaugarePacient(initializarePacient("Bob", 8), heap);

	for (int i = (heap.dim / 2 )- 1; i >= 0; i--) {
		filtrareHeap(heap, i);
	}
	printf("Heapul initial filtrat:\n");
	afisareHeap(heap);

	printf("\nPacientul cu gradul maxim de urgenta: ");
	Pacient maxPacient = extrageMaxim(&heap);

	printf("\nHeapul dupa extragerea pacientului cu gradul maxim de urgenta:\n");
	afisareHeap(heap);
}

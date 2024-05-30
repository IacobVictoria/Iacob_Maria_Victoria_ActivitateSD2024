#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct Curs {
    char* materie;
    int credite;
} Curs;

typedef struct NodDublu {
    struct NodDublu* prev;
    struct NodDublu* next;
    Curs info;
} NodDublu;

typedef struct {
    NodDublu* cap;
    NodDublu* coada;
} ListaDubla;

NodDublu* createNodDublu(Curs data) {
    NodDublu* nod = (NodDublu*)malloc(sizeof(NodDublu));
    nod->info = data;
    nod->prev = NULL;
    nod->next = NULL;
    return nod;
}

void enqueue(ListaDubla* lista, Curs data) {
    NodDublu* nod = createNodDublu(data);
    if (lista->coada != NULL) {
        lista->coada->next = nod;
        nod->prev = lista->coada;
        lista->coada = nod;
    }
    else {
        lista->cap = lista->coada = nod;
    }
}

Curs dequeue(ListaDubla* lista) {
    if (lista->cap==NULL) {
        printf("Queue is empty\n");
        Curs cursVid = { "", 0 }; 
        return cursVid;
    }
    NodDublu* nodEliminat = lista->cap;
    Curs data = nodEliminat->info;
    lista->cap = nodEliminat->next;
    if (lista->cap == NULL) {
        lista->coada = NULL;
    }
    else {
        lista->cap->prev = NULL;
    }
    free(nodEliminat);
    return data;
}

void displayQueue(ListaDubla* lista) {
    NodDublu* nod = lista->cap;
    printf("Queue: ");
    while (nod != NULL) {
        printf("(%s, %d) ", nod->info.materie, nod->info.credite);
        nod = nod->next;
    }
    printf("\n");
}

int main() {
    ListaDubla lista;
    lista.cap = NULL;
    lista.coada = NULL;

    enqueue(&lista, (Curs) { "Matematica", 5 });
    enqueue(&lista, (Curs) { "Informatica", 6 });
    enqueue(&lista, (Curs) { "Fizica", 4 });
    enqueue(&lista, (Curs) { "Chimie", 3 });

    displayQueue(&lista);

    printf("Dequeued: ");
    Curs cursEliminat = dequeue(&lista);
    if (cursEliminat.materie[0] != '\0')
        printf("(%s, %d)\n", cursEliminat.materie, cursEliminat.credite);

    displayQueue(&lista);

    return 0;
}

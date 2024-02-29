
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct Imobil {
    int cod;
    char* adresa;
    int nrEtaje;
    float* preturi;
};

// Funcția pentru citirea unui obiect de tipul Imobil de la tastatură
struct Imobil citesteImobil() {
    struct Imobil imobil;
    printf("Introduceti codul imobilului: ");
    scanf("%d", &imobil.cod);

    printf("Introduceti adresa imobilului: ");
    getchar(); 
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    
    buffer[strcspn(buffer, "\n")] = '\0'; 
    imobil.adresa = (char*)malloc(strlen(buffer) + 1);
    strcpy(imobil.adresa, buffer);

    printf("Introduceti numarul de etaje al imobilului: ");
    scanf("%d", &imobil.nrEtaje);

   
    imobil.preturi = (float*)malloc(imobil.nrEtaje * sizeof(float));

    for (int i = 0; i < imobil.nrEtaje; ++i) {
        printf("Introduceti pretul pentru etajul %d: ", i + 1);
        scanf("%f", &imobil.preturi[i]);
    }

    return imobil;
}

// Funcția pentru calcularea mediei prețurilor dintr-un obiect de tipul Imobil
float calculeazaMediePreturi(struct Imobil imobil) {
    if (imobil.nrEtaje == 0 || imobil.preturi == NULL) {
        return 0;
    }

    float suma = 0;
    for (int i = 0; i < imobil.nrEtaje; i++) {
        suma += imobil.preturi[i];
    }

    return suma / imobil.nrEtaje;
}

// Funcția pentru modificarea adresei unui obiect de tipul Imobil
void modificaAdresa(struct Imobil* imobil, const char* nouaAdresa) {
    free(imobil->adresa); 
    imobil->adresa = (char*)malloc(strlen(nouaAdresa) + 1);
    strcpy(imobil->adresa, nouaAdresa);
}

// Funcția pentru afișarea informațiilor despre un obiect de tipul Imobil
void afiseazaImobil(struct Imobil imobil) {
    printf("Codul imobilului: %d\n", imobil.cod);
    printf("Adresa imobilului: %s\n", imobil.adresa);
    printf("Numarul de etaje al imobilului: %d\n", imobil.nrEtaje);
    if (imobil.nrEtaje > 0 && imobil.preturi != NULL) {
        printf("Preturile pe fiecare etaj: ");
        for (int i = 0; i < imobil.nrEtaje; i++) {
            printf("%.2f ", imobil.preturi[i]);
        }
        printf("\n");
    }
}
//Functia care creeaza un nou vector
struct Imobil* creeazaVector(struct Imobil* v,int nr, int* dim) {
    struct Imobil* nou = (struct Imobil*)malloc(nr * sizeof(struct Imobil));
    int k = 0;
   
      
        for (int i = 0; i < nr; i++)
        {  
            if (v[i].nrEtaje != 1 && v[i].cod != 90) {
            nou[k] = v[i];
            k++;
        }
    }
    nou = (struct Imobil*)realloc(nou,k * sizeof(struct Imobil));
    *dim = k;
    return nou;
}
//Functia care concateneaza 2 vectori
struct Imobil* concatenareVectori(struct Imobil* v, int nr, struct Imobil* vv, int nr1, int* dim) {
    int d = nr + nr1;
    struct Imobil* nou = (struct Imobil*)malloc(d * sizeof(struct Imobil));
    int k = 0;


    for (int i = 0; i < nr; i++)
    {  
            nou[k] = v[i];
            k++;
        
    }
    for (int i = 0; i < nr1; i++) {
        nou[k] = vv[i];
        k++;
    }
    nou = (struct Imobil*)realloc(nou, k * sizeof(struct Imobil));
    *dim = k;
    return nou;
}
//Functia afisare vector
void afisareVector(struct Imobil* v, int nr) {
    for (int i = 0; i < nr; i++) {
        afiseazaImobil(v[i]);

    } 
}
int main() {
    //struct Imobil imobil1 = citesteImobil();
    //afiseazaImobil(imobil1);


    // Eliberăm memoria alocată pentru adresa imobilului și pentru vectorul de preturi
   /* free(imobil1.adresa);
    free(imobil1.preturi);*/
    int nr = 2;
    struct Imobil* vector = (struct  Imobil*)malloc(nr * sizeof(struct Imobil));
    for (int i = 0; i < nr; ++i) {
        printf("Introduceti informatiile pentru imobilul %d:\n", i + 1);
        vector[i] = citesteImobil();
    }
    int dim = 0;
    int dim1 = 0;
    struct Imobil* nou=creeazaVector(vector, 2,&dim);
    struct Imobil* concat = concatenareVectori(vector, 2, vector, 2, &dim1);

    
  /*  for (int i = 0; i < dim1; ++i) {
        printf("\nInformatii pentru imobilul %d:\n", i + 1);
        afiseazaImobil(concat[i]);
    }*/
    printf("\nInf Vector: ");
    afisareVector(concat,dim1);


    free(vector);
    free(nou);
    free(concat);
    return 0;
}

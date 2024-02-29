
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
struct Imobil* creeazaVector(struct Imobil* v, int nr, int* dim) {
    struct Imobil* nou = (struct Imobil*)malloc(nr * sizeof(struct Imobil));
    int k = 0;


    for (int i = 0; i < nr; i++)
    {
        if (v[i].nrEtaje != 1 && v[i].cod != 90) {
            nou[k] = v[i];
            k++;
        }
    }
    nou = (struct Imobil*)realloc(nou, k * sizeof(struct Imobil));
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


//Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create.
//  Asezarea in fisier a elementelor o faceti la libera alegere.
void creareaFisier(int n) {
    FILE *f;
    f = fopen("imobile.txt", "w");
    if (f == NULL) {
        printf("Eroare deschidere");
        return;
    }
    for (int i = 0; i < n; i++) {
        struct Imobil imobil = citesteImobil();
        fprintf(f, "%d\n%s\n%d\n", imobil.cod, imobil.adresa, imobil.nrEtaje); 

      
        for (int j = 0; j < imobil.nrEtaje; ++j) {
            fprintf(f, "%.2f ", imobil.preturi[j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}


//Scrieti intr-un program C functia care sa citeasca obiectele din fisier 
// si sa le salveze intr-un vector.
struct Imobil* citireFisierCreareVector(int* dim) {
    FILE* f;
    f = fopen("imobile.txt", "r");
    if (f == NULL) {
        printf("Nu se poate deschide fisierul.\n");
        return NULL;
    }

    struct Imobil* vector = NULL;
    int k = 0;
    int cap = 10; 
    vector = (struct Imobil*)malloc(cap * sizeof(struct Imobil));
  

    while (1) {
        if (k >= cap) {
            
            cap *= 2;
            struct Imobil* temp = (struct Imobil*)realloc(vector, cap * sizeof(struct Imobil));
            vector = temp;
        }

        struct Imobil imobil;
       if( fscanf(f, "%d", &imobil.cod)!=1)break; //am while(1) tr sa ies candva asa ca fac !=1 care inseamna ca nu a reusit sa citeasca aia si va iesi cu break
        fgetc(f); 

        char buffer[100];
        fgets(buffer, sizeof(buffer), f) ; 
        buffer[strcspn(buffer, "\n")] = '\0';
        imobil.adresa = (char*)malloc(strlen(buffer) + 1);

        strcpy(imobil.adresa, buffer);

        if (fscanf(f, "%d", &imobil.nrEtaje) != 1) break; 
        imobil.preturi = (float*)malloc(imobil.nrEtaje * sizeof(float));
       

        for (int i = 0; i < imobil.nrEtaje; i++) {
            fscanf(f, "%f", &imobil.preturi[i]);
        }

        vector[k++] = imobil;
    }

    *dim = k;
    fclose(f);
    return vector;
}


//salvare obiect intr-un fisier text

void salvareImobilFisier(struct Imobil imobil) {
    FILE* f;
    f = fopen("imobile.txt", "a+"); //a+ to append to file
    if (f == NULL) {
        printf("Eroare");
    }
    fprintf(f, "%d\n%s\n%d\n", imobil.cod, imobil.adresa, imobil.nrEtaje);


    for (int j = 0; j < imobil.nrEtaje; ++j) {
        fprintf(f, "%.2f ", imobil.preturi[j]);
    }
    fprintf(f, "\n");
}



//salvare vector fisier text
void salvareVectImobilFisier(struct Imobil* imobil,int nr) {
    FILE* f;
    f = fopen("imobile.txt", "a+"); //a+ to append to file
    if (f == NULL) {
        printf("Eroare");
    }
    for (int i = 0; i < nr; i++) {
        fprintf(f, "%d\n%s\n%d\n", imobil[i].cod, imobil[i].adresa, imobil[i].nrEtaje);


        for (int j = 0; j < imobil[i].nrEtaje; ++j) {
            fprintf(f, "%.2f ", imobil[i].preturi[j]);
        }
        fprintf(f, "\n");
    }
}



int main() {
    struct Imobil i1 = citesteImobil();
    int nr = 0;
    struct Imobil* vector = (struct  Imobil*)malloc(nr * sizeof(struct Imobil));
    for (int i = 0; i < nr; ++i) {
        printf("Introduceti informatiile pentru imobilul %d:\n", i + 1);
        vector[i] = citesteImobil();
    }
    int dim = 0;
    int dim1 = 0;
    struct Imobil* nou = creeazaVector(vector, 0, &dim);
    struct Imobil* concat = concatenareVectori(vector, 0, vector, 0, &dim1);


  
    printf("\nInf Vector: ");
    afisareVector(concat, dim1);

  //  creareaFisier(10);
    //vector din fisier
    int dimenV = 0;
    struct Imobil* vectorF = citireFisierCreareVector(&dimenV);
    afisareVector(vectorF, dimenV);

    //salvare imobil fisier
    salvareImobilFisier(i1);

    //salvare vector
    salvareVectImobilFisier(vectorF, dimenV);
    free(vector);
    free(nou);
    free(concat);
    return 0;
}

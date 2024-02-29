
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Pentru strcpy și strlen

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
    getchar(); // Consumă newline-ul rămas în buffer
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    // stdin -programul va aștepta să introduceți date de la tastatură și le va citi în variabila buffer.
    buffer[strcspn(buffer, "\n")] = '\0'; // Elimină newline-ul de la sfârșitul șirului
    imobil.adresa = (char*)malloc(strlen(buffer) + 1);
    strcpy(imobil.adresa, buffer);

    printf("Introduceti numarul de etaje al imobilului: ");
    scanf("%d", &imobil.nrEtaje);

    // Alocare memorie pentru vectorul de preturi
    imobil.preturi = (float*)malloc(imobil.nrEtaje * sizeof(float));

    // Citirea preturilor pentru fiecare etaj
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

int main() {
    struct Imobil imobil1 = citesteImobil();
    afiseazaImobil(imobil1);

    // Calculăm media prețurilor pentru imobilul citit
    float medie = calculeazaMediePreturi(imobil1);
    printf("Media preturilor pentru imobil: %.2f\n", medie);

    // Modificăm adresa imobilului și afișăm informațiile actualizate
    modificaAdresa(&imobil1, "Bulevard Basarabia 77");
    printf("Adresa imobilului actualizata: %s\n", imobil1.adresa);

    // Eliberăm memoria alocată pentru adresa imobilului și pentru vectorul de preturi
    free(imobil1.adresa);
    free(imobil1.preturi);

    return 0;
}

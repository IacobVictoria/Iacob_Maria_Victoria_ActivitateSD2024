#include <stdio.h>
#include <malloc.h>

struct Haina {
    char* marca;
	//nu avem functii metode
	int marime;
	float pret;
	// nu avem tipul bool in limbajul c
	// bool gen;
	char gen;

};
//char ocupa 1
void afiseazaHaina(struct Haina h) {
	if (h.marca != NULL) {
		{
			printf("Marca: %s\n", h.marca);
		}
		printf("Pret este: %5.2f\n", h.pret);
		printf("Marime este: %d\n", h.marime);
		printf("Gen: %c\n", h.gen);
	}
	};

struct Haina initializare(const char* marca, float p, int marime, char gen) {
	struct Haina h;
	h.marime = marime;
	if (marca != NULL && strlen(marca) > 0)
	{
		h.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
		strcpy(h.marca, marca);
	}
	else {
		h.marca = NULL;
	}
	h.pret =p;
	h.gen = gen;

}
void dezalocare(struct Haina* h)//tr transmis prin pointer ca sa nu avem dangling pointer
{
	free(h->marca);
	h->marca = NULL;
}
void main() {
	struct Haina h1;
	h1.marime = 33;
	h1.marca = (char*)malloc(sizeof(char) * (strlen("Nike") + 1));
	strcpy(h1.marca, "Nike");
	h1.pret = 62;
	h1.gen = 'F';

	afiseazaHaina(h1);
	dezalocare(&h1);

	struct Haina h2 = initializare("Adidas", 89.90, 22, 'M');
	afiseazaHaina(h2);
	dezalocare(&h2);


}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Osoba {
    char ime[50];
    char prezime[50];
    int godina_rodjenja;
    struct _Osoba* sljedeci;
} Osoba;

void dodaj_na_pocetak(Osoba** head, const char* ime, const char* prezime, int godina) {
    Osoba* novi = (Osoba*)malloc(sizeof(Osoba));
    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->godina_rodjenja = godina;
    novi->sljedeci = *head;
    *head = novi;
}

void ispisi_listu(Osoba* head) {
    Osoba* trenutni = head;
    printf("\n--- POPIS OSOBA ---\n");
    while (trenutni != NULL) {
        printf("%s %s (%d)\n", trenutni->ime, trenutni->prezime, trenutni->godina_rodjenja);
        trenutni = trenutni->sljedeci;
    }
}

void dodaj_na_kraj(Osoba** head, const char* ime, const char* prezime, int godina) {
    Osoba* novi = (Osoba*)malloc(sizeof(Osoba));
    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->godina_rodjenja = godina;
    novi->sljedeci = NULL;

    if (*head == NULL) {
        *head = novi;
    }
    else {
        Osoba* trenutni = *head;
        while (trenutni->sljedeci != NULL) {
            trenutni = trenutni->sljedeci;
        }
        trenutni->sljedeci = novi;
    }
}

Osoba* pronadji(Osoba* head, char* prezime) {
    Osoba* trenutni = head;
    while (trenutni != NULL) {
        if (strcmp(trenutni->prezime, prezime) == 0) return trenutni;
        trenutni = trenutni->sljedeci;
    }
    return NULL;
}

void obrisi(Osoba** head, char* prezime) {
    Osoba* trenutni = *head;
    Osoba* prethodni = NULL;

    if (trenutni != NULL && strcmp(trenutni->prezime, prezime) == 0) {
        *head = trenutni->sljedeci;
        free(trenutni);
        return;
    }

    while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0) {
        prethodni = trenutni;
        trenutni = trenutni->sljedeci;
    }

    if (trenutni == NULL) return;

    prethodni->sljedeci = trenutni->sljedeci;
    free(trenutni);
}

int main() {
    Osoba* glava = NULL;

    dodaj_na_pocetak(&glava, "Ana", "Anic", 2000);
    dodaj_na_pocetak(&glava, "Ivan", "Ivic", 1995);
    dodaj_na_kraj(&glava, "Pero", "Peric", 1998);

    printf("Nakon dodavanja:");
    ispisi_listu(glava);

    Osoba* p = pronadji(glava, "Anic");
    if (p != NULL) printf("\nPronadjen: %s %s\n", p->ime, p->prezime);

    obrisi(&glava, "Anic");
    printf("\nNakon brisanja Anic:");
    ispisi_listu(glava);

    return 0;
}
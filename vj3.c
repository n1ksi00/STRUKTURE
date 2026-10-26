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

int dodaj_na_pocetak(Osoba** head, const char* ime, const char* prezime, int godina) {
    Osoba* novi = (Osoba*)malloc(sizeof(Osoba));
    if (novi == NULL) return -1;
    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->godina_rodjenja = godina;
    novi->sljedeci = *head;
    *head = novi;
    return 0;
}

int ispisi_listu(Osoba* head) {
    Osoba* trenutni = head;
    printf("\n--- POPIS OSOBA ---\n");
    while (trenutni != NULL) {
        printf("Ime: %s, Prezime: %s, Godina: %d\n", trenutni->ime, trenutni->prezime, trenutni->godina_rodjenja);
        trenutni = trenutni->sljedeci;
    }
    printf("-------------------\n");
    return 0;
}

int dodaj_iza(Osoba* head, const char* prezime_meta, const char* ime, const char* prezime, int godina) {
    Osoba* trenutni = head;
    while (trenutni != NULL && strcmp(trenutni->prezime, prezime_meta) != 0) {
        trenutni = trenutni->sljedeci;
    }
    if (trenutni == NULL) return -1;

    Osoba* novi = (Osoba*)malloc(sizeof(Osoba));
    if (novi == NULL) return -1;
    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->godina_rodjenja = godina;

    novi->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = novi;
    return 0;
}

int dodaj_ispred(Osoba** head, const char* prezime_meta, const char* ime, const char* prezime, int godina) {
    if (*head == NULL) return -1;

    if (strcmp((*head)->prezime, prezime_meta) == 0) {
        return dodaj_na_pocetak(head, ime, prezime, godina);
    }

    Osoba* trenutni = *head;
    while (trenutni->sljedeci != NULL && strcmp(trenutni->sljedeci->prezime, prezime_meta) != 0) {
        trenutni = trenutni->sljedeci;
    }

    if (trenutni->sljedeci == NULL) return -1;

    Osoba* novi = (Osoba*)malloc(sizeof(Osoba));
    if (novi == NULL) return -1;
    strcpy(novi->ime, ime);
    strcpy(novi->prezime, prezime);
    novi->godina_rodjenja = godina;

    novi->sljedeci = trenutni->sljedeci;
    trenutni->sljedeci = novi;
    return 0;
}

int sortiraj_listu(Osoba* head) {
    if (head == NULL) return -1;
    int promjena;
    Osoba* i;
    Osoba* zadnji = NULL;

    do {
        promjena = 0;
        i = head;
        while (i->sljedeci != zadnji) {
            if (strcmp(i->prezime, i->sljedeci->prezime) > 0) {
                char t_ime[50], t_prezime[50];
                int t_godina;

                strcpy(t_ime, i->ime);
                strcpy(t_prezime, i->prezime);
                t_godina = i->godina_rodjenja;

                strcpy(i->ime, i->sljedeci->ime);
                strcpy(i->prezime, i->sljedeci->prezime);
                i->godina_rodjenja = i->sljedeci->godina_rodjenja;

                strcpy(i->sljedeci->ime, t_ime);
                strcpy(i->sljedeci->prezime, t_prezime);
                i->sljedeci->godina_rodjenja = t_godina;

                promjena = 1;
            }
            i = i->sljedeci;
        }
        zadnji = i;
    } while (promjena);
    return 0;
}

int upisi_u_datoteku(Osoba* head, const char* naziv_datoteke) {
    FILE* f = fopen(naziv_datoteke, "w");
    if (f == NULL) return -1;

    Osoba* trenutni = head;
    while (trenutni != NULL) {
        fprintf(f, "%s %s %d\n", trenutni->ime, trenutni->prezime, trenutni->godina_rodjenja);
        trenutni = trenutni->sljedeci;
    }
    fclose(f);
    return 0;
}

int citaj_iz_datoteke(Osoba** head, const char* naziv_datoteke) {
    FILE* f = fopen(naziv_datoteke, "r");
    if (f == NULL) return -1;

    char ime[50], prezime[50];
    int godina;

    while (fscanf(f, "%49s %49s %d", ime, prezime, &godina) == 3) {
        dodaj_na_pocetak(head, ime, prezime, godina);
    }
    fclose(f);
    return 0;
}

int main() {
    Osoba* glava = NULL;

    dodaj_na_pocetak(&glava, "Ana", "Anic", 2000);
    dodaj_na_pocetak(&glava, "Marko", "Maric", 1995);
    dodaj_na_pocetak(&glava, "Ivana", "Ivic", 1998);

    printf("Pocetna lista:");
    ispisi_listu(glava);

    dodaj_iza(glava, "Maric", "Pero", "Peric", 1992);
    printf("Nakon dodavanja iza prezimena 'Maric':");
    ispisi_listu(glava);

    dodaj_ispred(&glava, "Anic", "Maja", "Majic", 2002);
    printf("Nakon dodavanja ispred prezimena 'Anic':");
    ispisi_listu(glava);

    sortiraj_listu(glava);
    printf("Nakon sortiranja po prezimenima:");
    ispisi_listu(glava);

    upisi_u_datoteku(glava, "popis_osoba.txt");
    printf("\nPodatci uspjesno upisani u datoteku 'popis_osoba.txt'.\n");

    return 0;
}
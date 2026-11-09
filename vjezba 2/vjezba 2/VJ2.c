#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 50

struct _Osoba;
typedef struct _Osoba* Pozicija;

typedef struct _Osoba {
    char ime[MAX_STR];
    char prezime[MAX_STR];
    int godinaRodjenja;
    Pozicija next;
} Osoba;

Pozicija stvoriOsobu(char* ime, char* prezime, int godinaRodjenja);
int dodajNaPocetak(Pozicija head, char* ime, char* prezime, int godinaRodjenja);
int ispišiListu(Pozicija head);
int dodajNaKraj(Pozicija head, char* ime, char* prezime, int godinaRodjenja);
Pozicija pronadjiPoPrezimenu(Pozicija head, char* prezime);
int obrisiElement(Pozicija head, char* prezime);

int main() {

    Osoba head;
    head.next = NULL;

    dodajNaPocetak(&head, "Ivan", "Ivic", 1995);
    dodajNaPocetak(&head, "Ana", "Anic", 1998);
    dodajNaKraj(&head, "Marko", "Markic", 1990);

    printf("--- TRENUTNA LISTA ---\n");
    ispišiListu(&head);

    printf("\n--- PRETRAGA (Prezime: Ivic) ---\n");
    Pozicija pronadjeni = pronadjiPoPrezimenu(&head, "Ivic");
    if (pronadjeni != NULL) {
        printf("Pronadjena osoba: %s %s, Godina: %d\n", pronadjeni->ime, pronadjeni->prezime, pronadjeni->godinaRodjenja);
    }
    else {
        printf("Osoba nije pronadjena.\n");
    }

    printf("\n--- BRISANJE OSOBE (Prezime: Ivic) ---\n");
    obrisiElement(&head, "Ivic");
    ispišiListu(&head);

    while (head.next != NULL) {
        obrisiElement(&head, head.next->prezime);
    }

    return 0;
}

Pozicija stvoriOsobu(char* ime, char* prezime, int godinaRodjenja) {
    Pozicija novaOsoba = (Pozicija)malloc(sizeof(Osoba));
    if (novaOsoba == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godinaRodjenja = godinaRodjenja;
    novaOsoba->next = NULL;
    return novaOsoba;
}

int dodajNaPocetak(Pozicija head, char* ime, char* prezime, int godinaRodjenja) {
    Pozicija novaOsoba = stvoriOsobu(ime, prezime, godinaRodjenja);
    if (novaOsoba == NULL) return -1;

    novaOsoba->next = head->next;
    head->next = novaOsoba;

    return 0;
}

int ispišiListu(Pozicija head) {
    Pozicija trenutna = head->next;
    if (trenutna == NULL) {
        printf("Lista je prazna.\n");
        return 0;
    }

    while (trenutna != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rođenja: %d\n",
            trenutna->ime, trenutna->prezime, trenutna->godinaRodjenja);
        trenutna = trenutna->next;
    }
    return 0;
}

int dodajNaKraj(Pozicija head, char* ime, char* prezime, int godinaRodjenja) {
    Pozicija novaOsoba = stvoriOsobu(ime, prezime, godinaRodjenja);
    if (novaOsoba == NULL) return -1;

    Pozicija trenutna = head;
    while (trenutna->next != NULL) {
        trenutna = trenutna->next;
    }

    trenutna->next = novaOsoba;
    return 0;
}

Pozicija pronadjiPoPrezimenu(Pozicija head, char* prezime) {
    Pozicija trenutna = head->next;
    while (trenutna != NULL) {
        if (strcmp(trenutna->prezime, prezime) == 0) {
            return trenutna;
        }
        trenutna = trenutna->next;
    }
    return NULL;
}

int obrisiElement(Pozicija head, char* prezime) {
    Pozicija prethodna = head;
    Pozicija trenutna = head->next;

    while (trenutna != NULL && strcmp(trenutna->prezime, prezime) != 0) {
        prethodna = trenutna;
        trenutna = trenutna->next;
    }

    if (trenutna == NULL) {
        printf("Osoba s prezimenom %s nije pronadjena za brisanje.\n", prezime);
        return -1;
    }

    prethodna->next = trenutna->next;
    free(trenutna);

    return 0;
}
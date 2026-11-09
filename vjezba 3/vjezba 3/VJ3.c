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
Pozicija pronadjiPrethodnog(Pozicija head, char* prezime);
int obrisiElement(Pozicija head, char* prezime);
int dodajIza(Pozicija element, char* ime, char* prezime, int godinaRodjenja);
int dodajIspred(Pozicija head, Pozicija element, char* ime, char* prezime, int godinaRodjenja);
int sortirajListu(Pozicija head);
int upisiUDatoteku(Pozicija head, char* nazivDatoteke);
int citajIzDatoteke(Pozicija head, char* nazivDatoteke);

int main() {
    Osoba head;
    head.next = NULL;

    dodajNaPocetak(&head, "Ivo", "Ivic", 1995);
    dodajNaKraj(&head, "Ana", "Anic", 1998);

    Pozicija p = pronadjiPoPrezimenu(&head, "Ivic");
    if (p != NULL) {
        dodajIza(p, "Luka", "Lukic", 2000);
    }

    Pozicija p2 = pronadjiPoPrezimenu(&head, "Anic");
    if (p2 != NULL) {
        dodajIspred(&head, p2, "Maja", "Majic", 1992);
    }

    printf("--- LISTA PRIJE SORTIRANJA ---\n");
    ispišiListu(&head);

    sortirajListu(&head);
    printf("\n--- LISTA NAKON SORTIRANJA PO PREZIMENIMA ---\n");
    ispišiListu(&head);

    upisiUDatoteku(&head, "osobe.txt");
    printf("\nLista je uspjesno upisana u datoteku 'osobe.txt'.\n");

    while (head.next != NULL) {
        obrisiElement(&head, head.next->prezime);
    }

    citajIzDatoteke(&head, "osobe.txt");
    printf("\n--- LISTA PROCITANA IZ DATOTEKE ---\n");
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

Pozicija pronadjiPrethodnog(Pozicija head, char* prezime) {
    Pozicija prethodna = head;
    Pozicija trenutna = head->next;

    while (trenutna != NULL && strcmp(trenutna->prezime, prezime) != 0) {
        prethodna = trenutna;
        trenutna = trenutna->next;
    }

    if (trenutna == NULL) return NULL;
    return prethodna;
}

int obrisiElement(Pozicija head, char* prezime) {
    Pozicija prethodna = pronadjiPrethodnog(head, prezime);
    if (prethodna == NULL || prethodna->next == NULL) {
        return -1;
    }

    Pozicija zaBrisanje = prethodna->next;
    prethodna->next = zaBrisanje->next;
    free(zaBrisanje);

    return 0;
}

int dodajIza(Pozicija element, char* ime, char* prezime, int godinaRodjenja) {
    if (element == NULL) return -1;

    Pozicija novaOsoba = stvoriOsobu(ime, prezime, godinaRodjenja);
    if (novaOsoba == NULL) return -1;

    novaOsoba->next = element->next;
    element->next = novaOsoba;

    return 0;
}

int dodajIspred(Pozicija head, Pozicija element, char* ime, char* prezime, int godinaRodjenja) {
    if (element == NULL) return -1;

    Pozicija prethodna = head;
    while (prethodna->next != NULL && prethodna->next != element) {
        prethodna = prethodna->next;
    }

    if (prethodna->next == NULL) {
        printf("Zadani element nije pronadjen u listi.\n");
        return -1;
    }

    return dodajIza(prethodna, ime, prezime, godinaRodjenja);
}

int sortirajListu(Pozicija head) {
    if (head->next == NULL || head->next->next == NULL) return 0;

    int promjena;
    Pozicija trenutna;
    Pozicija zadnja = NULL;

    do {
        promjena = 0;
        trenutna = head;

        while (trenutna->next->next != zadnja) {
            Pozicija p1 = trenutna->next;
            Pozicija p2 = p1->next;

            if (strcmp(p1->prezime, p2->prezime) > 0) {
                trenutna->next = p2;
                p1->next = p2->next;
                p2->next = p1;
                promjena = 1;
            }
            trenutna = trenutna->next;
        }
        zadnja = trenutna->next;
    } while (promjena);

    return 0;
}

int upisiUDatoteku(Pozicija head, char* nazivDatoteke) {
    FILE* datoteka = fopen(nazivDatoteke, "w");
    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke za pisanje!\n");
        return -1;
    }

    Pozicija trenutna = head->next;
    while (trenutna != NULL) {
        fprintf(datoteka, "%s %s %d\n", trenutna->ime, trenutna->prezime, trenutna->godinaRodjenja);
        trenutna = trenutna->next;
    }

    fclose(datoteka);
    return 0;
}

int citajIzDatoteke(Pozicija head, char* nazivDatoteke) {
    FILE* datoteka = fopen(nazivDatoteke, "r");
    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke za citanje!\n");
        return -1;
    }

    char ime[MAX_STR];
    char prezime[MAX_STR];
    int godinaRodjenja;

    while (fscanf(datoteka, "%s %s %d", ime, prezime, &godinaRodjenja) == 3) {
        dodajNaKraj(head, ime, prezime, godinaRodjenja);
    }

    fclose(datoteka);
    return 0;
}
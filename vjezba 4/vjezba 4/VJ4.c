#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _Polin;
typedef struct _Polin* Pozicija;

typedef struct _Polin {
    int koeficijent;
    int eksponent;
    Pozicija next;
} Polin;

Pozicija stvoriElement(int koeficijent, int eksponent);
int sortiraniUnos(Pozicija head, int koeficijent, int eksponent);
int citajIzDatoteke(Pozicija head, char* nazivDatoteke);
int ispišiPolinom(Pozicija head);
int zbrojiPolinome(Pozicija p1, Pozicija p2, Pozicija rezultat);
int pomnožiPolinome(Pozicija p1, Pozicija p2, Pozicija rezultat);
int obrišiPolinom(Pozicija head);

int main() {
    Polin p1;
    Polin p2;
    Polin suma;
    Polin produkt;

    p1.next = NULL;
    p2.next = NULL;
    suma.next = NULL;
    produkt.next = NULL;

    citajIzDatoteke(&p1, "polinom1.txt");
    citajIzDatoteke(&p2, "polinom2.txt");

    printf("Prvi polinom: ");
    ispišiPolinom(&p1);

    printf("Drugi polinom: ");
    ispišiPolinom(&p2);

    zbrojiPolinome(&p1, &p2, &suma);
    printf("Zbroj polinoma: ");
    ispišiPolinom(&suma);

    pomnožiPolinome(&p1, &p2, &produkt);
    printf("Produkt polinoma: ");
    ispišiPolinom(&produkt);

    obrišiPolinom(&p1);
    obrišiPolinom(&p2);
    obrišiPolinom(&suma);
    obrišiPolinom(&produkt);

    return 0;
}

Pozicija stvoriElement(int koeficijent, int eksponent) {
    if (koeficijent == 0) return NULL;
    Pozicija novi = (Pozicija)malloc(sizeof(Polin));
    if (novi == NULL) return NULL;
    novi->koeficijent = koeficijent;
    novi->eksponent = eksponent;
    novi->next = NULL;
    return novi;
}

int sortiraniUnos(Pozicija head, int koeficijent, int eksponent) {
    if (koeficijent == 0) return 0;

    Pozicija prethodni = head;
    Pozicija trenutna = head->next;

    while (trenutna != NULL && trenutna->eksponent > eksponent) {
        prethodni = trenutna;
        trenutna = trenutna->next;
    }

    if (trenutna != NULL && trenutna->eksponent == eksponent) {
        trenutna->koeficijent += koeficijent;
        if (trenutna->koeficijent == 0) {
            prethodni->next = trenutna->next;
            free(trenutna);
        }
    }
    else {
        Pozicija novi = stvoriElement(koeficijent, eksponent);
        if (novi == NULL) return -1;
        novi->next = trenutna;
        prethodni->next = novi;
    }

    return 0;
}

int citajIzDatoteke(Pozicija head, char* nazivDatoteke) {
    FILE* datoteka = fopen(nazivDatoteke, "r");
    if (datoteka == NULL) return -1;

    int koef, eksp;
    while (fscanf(datoteka, "%d %d", &koef, &eksp) == 2) {
        sortiraniUnos(head, koef, eksp);
    }

    fclose(datoteka);
    return 0;
}

int ispišiPolinom(Pozicija head) {
    Pozicija trenutna = head->next;
    if (trenutna == NULL) {
        printf("0\n");
        return 0;
    }

    while (trenutna != NULL) {
        if (trenutna->koeficijent > 0 && trenutna != head->next) {
            printf(" + ");
        }
        else if (trenutna->koeficijent < 0) {
            printf(" - ");
        }

        int k = trenutna->koeficijent < 0 ? -trenutna->koeficijent : trenutna->koeficijent;

        if (trenutna->eksponent == 0) {
            printf("%d", k);
        }
        else if (trenutna->eksponent == 1) {
            printf("%dx", k);
        }
        else {
            printf("%dx^%d", k, trenutna->eksponent);
        }

        trenutna = trenutna->next;
    }
    printf("\n");
    return 0;
}

int zbrojiPolinome(Pozicija p1, Pozicija p2, Pozicija rezultat) {
    Pozicija t1 = p1->next;
    Pozicija t2 = p2->next;

    while (t1 != NULL) {
        sortiraniUnos(rezultat, t1->koeficijent, t1->eksponent);
        t1 = t1->next;
    }

    while (t2 != NULL) {
        sortiraniUnos(rezultat, t2->koeficijent, t2->eksponent);
        t2 = t2->next;
    }

    return 0;
}

int pomnožiPolinome(Pozicija p1, Pozicija p2, Pozicija rezultat) {
    Pozicija t1 = p1->next;
    while (t1 != NULL) {
        Pozicija t2 = p2->next;
        while (t2 != NULL) {
            int noviKoef = t1->koeficijent * t2->koeficijent;
            int noviEksp = t1->eksponent + t2->eksponent;
            sortiraniUnos(rezultat, noviKoef, noviEksp);
            t2 = t2->next;
        }
        t1 = t1->next;
    }
    return 0;
}

int obrišiPolinom(Pozicija head) {
    Pozicija trenutna = head->next;
    while (trenutna != NULL) {
        Pozicija temp = trenutna;
        trenutna = trenutna->next;
        free(temp);
    }
    head->next = NULL;
    return 0;
}
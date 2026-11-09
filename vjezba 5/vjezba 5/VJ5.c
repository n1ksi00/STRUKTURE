#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Cvor;
typedef struct _Cvor* Pozicija;

typedef struct _Cvor {
    double element;
    Pozicija next;
} Cvor;

Pozicija stvoriCvor(double element);
int push(Pozicija head, double element);
double pop(Pozicija head);
int izracunajPostfiks(char* nazivDatoteke, double* rezultat);
int obrisiStog(Pozicija head);

int main() {
    Cvor head;
    head.next = NULL;
    double rezultat = 0;

    if (izracunajPostfiks("postfix.txt", &rezultat) == 0) {
        printf("Rezultat postfiks iznosa je: %.2lf\n", rezultat);
    }
    else {
        printf("Greska pri izracunavanju postfiks iznosa.\n");
    }

    return 0;
}

Pozicija stvoriCvor(double element) {
    Pozicija novi = (Pozicija)malloc(sizeof(Cvor));
    if (novi == NULL) return NULL;
    novi->element = element;
    novi->next = NULL;
    return novi;
}

int push(Pozicija head, double element) {
    Pozicija novi = stvoriCvor(element);
    if (novi == NULL) return -1;
    novi->next = head->next;
    head->next = novi;
    return 0;
}

double pop(Pozicija head) {
    if (head->next == NULL) return 0.0;
    Pozicija temp = head->next;
    double vrijednost = temp->element;
    head->next = temp->next;
    free(temp);
    return vrijednost;
}

int izracunajPostfiks(char* nazivDatoteke, double* rezultat) {
    FILE* datoteka = fopen(nazivDatoteke, "r");
    if (datoteka == NULL) return -1;

    Cvor head;
    head.next = NULL;

    char buffer[50];
    while (fscanf(datoteka, "%s", buffer) == 1) {
        double broj = 0;
        if (sscanf(buffer, "%lf", &broj) == 1) {
            push(&head, broj);
        }
        else {
            double op2 = pop(&head);
            double op1 = pop(&head);
            double rez = 0;

            if (strcmp(buffer, "+") == 0) rez = op1 + op2;
            else if (strcmp(buffer, "-") == 0) rez = op1 - op2;
            else if (strcmp(buffer, "*") == 0) rez = op1 * op2;
            else if (strcmp(buffer, "/") == 0) {
                if (op2 == 0) {
                    fclose(datoteka);
                    obrisiStog(&head);
                    return -1;
                }
                rez = op1 / op2;
            }
            else {
                fclose(datoteka);
                obrisiStog(&head);
                return -1;
            }
            push(&head, rez);
        }
    }

    fclose(datoteka);

    if (head.next != NULL) {
        *rezultat = head.next->element;
        obrisiStog(&head);
        return 0;
    }

    return -1;
}

int obrisiStog(Pozicija head) {
    while (head->next != NULL) {
        Pozicija temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128
#define MAX_FILE_NAME 50

typedef struct {
    char ime[50];
    char prezime[50];
    double bodovi;
} Student;

int main() {
    char filename[MAX_FILE_NAME];
    printf("Unesite naziv datoteke (npr. studenti.txt): ");
    scanf("%s", filename);

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    int brojacRedaka = 0;
    char buffer[MAX_LINE];

    while (fgets(buffer, MAX_LINE, fp) != NULL) {

        if (strlen(buffer) > 1) {
            brojacRedaka++;
        }
    }

    rewind(fp);

    if (brojacRedaka == 0) {
        printf("Datoteka je prazna.\n");
        fclose(fp);
        return 0;
    }

    Student* studenti = (Student*)malloc(brojacRedaka * sizeof(Student));
    if (studenti == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        fclose(fp);
        return 1;
    }

    int i = 0;
    double maxBodova = 0;

    while (i < brojacRedaka && fscanf(fp, "%s %s %lf", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi) == 3) {
        if (studenti[i].bodovi > maxBodova) {
            maxBodova = studenti[i].bodovi;
        }
        i++;
    }

    fclose(fp);

    if (maxBodova == 0) {
        maxBodova = 1.0;
    }

    printf("\n--- POPIS STUDENATA I BODOVA ---\n");
    for (int j = 0; j < brojacRedaka; j++) {
        double relativniBodovi = (studenti[j].bodovi / maxBodova) * 100.0;
        printf("Ime: %s, Prezime: %s, Apsolutni bodovi: %.2f, Relativni bodovi: %.2f%%\n",
            studenti[j].ime,
            studenti[j].prezime,
            studenti[j].bodovi,
            relativniBodovi);
    }

    free(studenti);

    return 0;
}
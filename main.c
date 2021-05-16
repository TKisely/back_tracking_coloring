#include <stdio.h>

//Csucsok szama
#define V 5

void printSolution(int szinek[]);

//TODO: Atnevezes
int isSafe(int v, int graf[V][V], const int szinek[], int c) {
    int i;
    for (i = 0; i < V; i++)
        if (
                graf[v][i] && c == szinek[i])
            return 0;
    return 1;
}

//TODO: Atnevezes, "c" elnevezese
int graphColoringUtil(int graf[V][V], int szinek_szama, int szinek[], int v) {
    int c;
    if (v == V)
        return 1;

    for (c = 1; c <= szinek_szama; c++) {

        if (isSafe(v, graf, szinek, c)) {
            szinek[v] = c;

            if (graphColoringUtil(graf, szinek_szama, szinek, v + 1) == 1)
                return 1;
            szinek[v] = 0;
        }
    }
    return 0;
}

int graphColoring(int graf[V][V], int szinekSzama) {
    int szinek[V];
    int i;
    for (i = 0; i < V; i++)
        szinek[i] = 0;

    if (graphColoringUtil(graf, szinekSzama, szinek, 0) == 0) {
        printf("Nem letezik megoldas");
        return 0;
    }

    printSolution(szinek);
    return 1;
}

void printSolution(int szinek[]) {
    int i;
    printf(
            "Letezik megoldas:"
            " A kovetkezo szinekkel kell a csucsokat szinezni \n");
    for (i = 0; i < V; i++)
        printf(" %d ", szinek[i]);
    printf("\n");
}

int main() {

    int teljes_graf[V][V] = {
            { 0, 1, 1, 1, 1 },
            { 1, 0, 1, 1, 1 },
            { 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1 },
            { 1, 1, 1, 1, 0 },
    };
    int ut_graf[V][V] = {
            { 0, 1, 0, 0, 0 },
            { 1, 0, 1, 0, 0 },
            { 0, 1, 0, 1, 0 },
            { 0, 0, 1, 0, 1 },
            { 0, 0, 0, 1, 0 },
    };
    int kor_graf[V][V] = {
            { 0, 1, 0, 0, 1 },
            { 1, 0, 1, 0, 0 },
            { 0, 1, 0, 1, 0 },
            { 0, 0, 1, 0, 1 },
            { 1, 0, 0, 1, 0 },
    };

    int szinekSzama = 5;
    printf("Maximalisan hasznalhato szinek szama: %d \n", szinekSzama);

    printf("Teljes graf:\n");
    graphColoring(teljes_graf, szinekSzama);
    printf("Ut graf:\n");
    graphColoring(ut_graf, szinekSzama);
    printf("Kor graf:\n");
    graphColoring(kor_graf, szinekSzama);

    printf("Vege a kodnak!\n");
    return 0;
}

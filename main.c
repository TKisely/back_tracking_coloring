#include <stdio.h>
#include <time.h>

//Csucsok szama
#define V 5
//Teszt futttatasok szama
#define FUTASOKSZAMA 100

void kiiras_Megoldas(int *szinek);

//TODO: Atnevezes
int bc_JoE(int v, int graf[V][V], const int szinek[], int c) {
    int i;
    for (i = 0; i < V; i++)
        if (
                graf[v][i] && c == szinek[i])
            return 0;
    return 1;
}

//TODO: Atnevezes, "c" elnevezese
int bc_graphColoringUtil(int graf[V][V], int szinek_szama, int szinek[], int v) {
    int c;
    if (v == V)
        return 1;

    for (c = 1; c <= szinek_szama; c++) {

        if (bc_JoE(v, graf, szinek, c)) {
            szinek[v] = c;

            if (bc_graphColoringUtil(graf, szinek_szama, szinek, v + 1) == 1)
                return 1;
            szinek[v] = 0;
        }
    }
    return 0;
}

int bc_graphColoring(int graf[V][V], int szinekSzama) {
    int szinek[V];
    int i;
    for (i = 0; i < V; i++)
        szinek[i] = 0;

    if (bc_graphColoringUtil(graf, szinekSzama, szinek, 0) == 0) {
        printf("Nem letezik megoldas");
        return 0;
    }

    kiiras_Megoldas(szinek);
    return 1;
}

int nv_JoE(int graf[V][V], int szinek[])
{
    int i,j;
    for (i = 0; i < V; i++)
        for (j = i + 1; j < V; j++)
            if (graf[i][j] && szinek[j] == szinek[i])
                return 0;
    return 1;
}

int nv_grafSzinezes(int graf[V][V], int m, int i,
                     int szinek[V])
{
    int j;
    // if current index reached end
    if (i == V) {
        // if coloring is safe
        if (nv_JoE(graf, szinek)) {
            // Print the solution
            kiiras_Megoldas(szinek);
            return 1;
        }
        return 0;
    }

    for (j = 1; j <= m; j++) {
        szinek[i] = j;

        // Recur of the rest vertices
        if (nv_grafSzinezes(graf, m, i + 1, szinek))
            return 1;

        szinek[i] = 0;
    }

    return 0;
}

void kiiras_Megoldas(int *szinek) {
    int i;
    printf(
            "Letezik megoldas:"
            " A kovetkezo szinekkel kell a csucsokat szinezni \n");
    for (i = 0; i < V; i++)
        printf(" %d ", szinek[i]);
    printf("\n");
}

double naiv_teszt(int teljes_graf[V][V],int ut_graf[V][V],int kor_graf[V][V], int szinekSzama){
    int i;
    int color[V];
    double eltelt_ido=0.0;
    clock_t kezdet=clock();
    printf("Naiv megoldas\n");
    for (i = 0; i < V; i++)
        color[i] = 0;
    printf("Teljes graf:\n");
    if (!nv_grafSzinezes(teljes_graf, szinekSzama, 0, color))
        printf("Megoldas nem letezik");
    printf("Ut graf:\n");
    if (!nv_grafSzinezes(ut_graf, szinekSzama, 0, color))
        printf("Megoldas nem letezik");
    printf("Kor graf:\n");
    if (!nv_grafSzinezes(kor_graf, szinekSzama, 0, color))
        printf("Megoldas nem letezik");
    clock_t vege=clock();
    eltelt_ido+=(double)(vege-kezdet)/CLOCKS_PER_SEC;
    printf("\n Eltelt idoegyseg: %f \n",eltelt_ido);
    return eltelt_ido;
}

double backtrack_teszt(int teljes_graf[V][V],int ut_graf[V][V],int kor_graf[V][V], int szinekSzama){
    double eltelt_ido=0.0;
    clock_t kezdet=clock();
    printf("Backtrack megoldas\n");
    printf("Teljes graf:\n");
    bc_graphColoring(teljes_graf, szinekSzama);
    printf("Ut graf:\n");
    bc_graphColoring(ut_graf, szinekSzama);
    printf("Kor graf:\n");
    bc_graphColoring(kor_graf, szinekSzama);
    clock_t vege=clock();
    eltelt_ido+=(double)(vege-kezdet)/CLOCKS_PER_SEC;
    printf("\n Eltelt idoegyseg: %f \n",eltelt_ido);
    return eltelt_ido;
}

int main() {
    double backtrack_atlag,naiv_atlag;
    double aktualis_bc_ido,aktualis_naiv_ido;
    double backtrack_ossz=0;
    double naiv_ossz=0;
    int naiv_jobb_volt=FUTASOKSZAMA;
    int i;
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

    for (i = 0; i < FUTASOKSZAMA; ++i) {
        aktualis_bc_ido=backtrack_teszt(teljes_graf,ut_graf,kor_graf,szinekSzama);
        aktualis_naiv_ido=naiv_teszt(teljes_graf,ut_graf,kor_graf,szinekSzama);
        if(aktualis_bc_ido<=aktualis_naiv_ido){naiv_jobb_volt--;}
        backtrack_ossz+=aktualis_bc_ido;
        naiv_ossz+=aktualis_naiv_ido;
    }
    backtrack_atlag=backtrack_ossz/FUTASOKSZAMA;
    naiv_atlag=naiv_ossz/FUTASOKSZAMA;

    printf("\n\n%f a backtrack atlag es \n%f a naiv atlag",backtrack_atlag,naiv_atlag);
    printf("\n A naiv ennyiszer volt jobb %d esetbol: %d",FUTASOKSZAMA, naiv_jobb_volt);

    printf("\nVege a kodnak!\n");
    return 0;
}

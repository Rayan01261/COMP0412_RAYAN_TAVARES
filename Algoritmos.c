#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------- INSERTION SORT ----------
void insertion_sort(int A[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > chave) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = chave;
    }
}

// ---------- QUICK SORT ----------
int particionar(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim];
    int i = inicio - 1;
    int j, aux;

    for (j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
        }
    }

    aux = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = aux;
    return i + 1;
}

void quicksort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(vetor, inicio, fim);
        quicksort(vetor, inicio, p - 1);
        quicksort(vetor, p + 1, fim);
    }
}

// ---------- MERGE SORT ----------
void intercala(int vetor[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = vetor[inicio + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    i = 0;
    j = 0;
    k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergesort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergesort(vetor, inicio, meio);
        mergesort(vetor, meio + 1, fim);
        intercala(vetor, inicio, meio, fim);
    }
}

// ---------- FUNÇÃO PRINCIPAL ----------
int main() {
    int tamanhos[] = {100, 500, 1000, 5000, 10000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int vetor_testes[] = {3,1,9,5,10};
    int i, n;
    double tempo;
    clock_t inicio, fim;

    printf("Tamanho\tTempo (s)\n");




    for (i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = (int *)malloc(n * sizeof(int));

        for (int j = 0; j < n; j++)
            A[j] = rand() % 10000;

        inicio = clock();
        mergesort(A, 0, n - 1);
        fim = clock();

        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("%d\t%.4f\n", n, tempo);

        free(A);
    }

    return 0;
}

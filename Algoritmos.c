#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ------------------- INSERTION SORT -------------------
void insertion_sort(int *A, int n) {
    for (int i = 1; i < n; i++) {
        int chave = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > chave) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = chave;
    }
}

// ------------------- QUICK SORT -------------------
int particionar(int *A, int inicio, int fim) {
    int pivo = A[fim];
    int i = inicio - 1, aux;

    for (int j = inicio; j < fim; j++) {
        if (A[j] <= pivo) {
            i++;
            aux = A[i];
            A[i] = A[j];
            A[j] = aux;
        }
    }

    aux = A[i + 1];
    A[i + 1] = A[fim];
    A[fim] = aux;

    return i + 1;
}

void quicksort_rec(int *A, int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(A, inicio, fim);
        quicksort_rec(A, inicio, p - 1);
        quicksort_rec(A, p + 1, fim);
    }
}

void quicksort(int *A, int n) {
    quicksort_rec(A, 0, n - 1);
}

// ------------------- MERGE SORT -------------------
void intercala(int *A, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = A[inicio + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[meio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            A[k++] = L[i++];
        else
            A[k++] = R[j++];
    }

    while (i < n1)
        A[k++] = L[i++];
    while (j < n2)
        A[k++] = R[j++];

    free(L);
    free(R);
}

void mergesort_rec(int *A, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergesort_rec(A, inicio, meio);
        mergesort_rec(A, meio + 1, fim);
        intercala(A, inicio, meio, fim);
    }
}

void mergesort(int *A, int n) {
    mergesort_rec(A, 0, n - 1);
}

// ------------------- MAIN -------------------
int main() {
    srand(time(NULL));

    int tamanhos[] = {100, 500, 1000, 5000, 10000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int n;
    double tempo;
    clock_t inicio, fim;

    FILE *arquivo = fopen("resultados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // ---------- TESTES COM VALORES ALEATÓRIOS ----------
    fprintf(arquivo, "MergeSort - Valores Aleatorios\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = rand() % 10000;

        inicio = clock();
        mergesort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    fprintf(arquivo, "\nQuickSort - Valores Aleatorios\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = rand() % 10000;

        inicio = clock();
        quicksort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    fprintf(arquivo, "\nInsertionSort - Valores Aleatorios\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = rand() % 10000;

        inicio = clock();
        insertion_sort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    // ---------- TESTES COM VALORES CRESCENTES ----------
    fprintf(arquivo, "\nMergeSort - Valores Crescentes\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = j;

        inicio = clock();
        mergesort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    fprintf(arquivo, "\nQuickSort - Valores Crescentes\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = j;

        inicio = clock();
        quicksort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    fprintf(arquivo, "\nInsertionSort - Valores Crescentes\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = j;

        inicio = clock();
        insertion_sort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    // ---------- TESTES COM VALORES DECRESCENTES ----------
    fprintf(arquivo, "\nMergeSort - Valores Decrescentes\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = n - j;

        inicio = clock();
        mergesort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    fprintf(arquivo, "\nQuickSort - Valores Decrescentes\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = n - j;

        inicio = clock();
        quicksort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    fprintf(arquivo, "\nInsertionSort - Valores Decrescentes\n");
    for (int i = 0; i < num_tamanhos; i++) {
        n = tamanhos[i];
        int *A = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            A[j] = n - j;

        inicio = clock();
        insertion_sort(A, n);
        fim = clock();
        tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d\t%.6f\n", n, tempo);
        free(A);
    }

    fclose(arquivo);

    printf("Resultados salvos em resultados.txt\n");
    return 0;
}


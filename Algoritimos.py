import random
import time
import matplotlib.pyplot as plt
def insertion_sort(A):
    for i in range(1, len(A)):
        chave = A[i]
        j = i - 1
        while j >= 0 and A[j] > chave:
            A[j + 1] = A[j]
            j -= 1
        A[j + 1] = chave


def particionar(vetor, inicio, fim):
    pivo = vetor[fim]
    i = inicio - 1
    for j in range(inicio, fim):  # ← corrigido aqui
        if vetor[j] <= pivo:
            i = i + 1
            aux = vetor[i]
            vetor[i] = vetor[j]
            vetor[j] = aux
    aux = vetor[i + 1]
    vetor[i + 1] = vetor[fim]
    vetor[fim] = aux
    return i + 1


def quicksort(vetor, inicio, fim):
    if inicio < fim:
        p = particionar(vetor, inicio, fim)
        quicksort(vetor, inicio, p-1)
        quicksort(vetor, p+1, fim)


def intercala(vetor, inicio, meio, fim):
    l = []
    r = []
    l = vetor[inicio:meio+1]  # meio incluso
    r = vetor[meio+1:fim+1]  # meio+1 até fim
    
    i = 0
    j = 0 
    k = inicio

    while i < len(l) and j < len(r):
        if l[i]<=r[j]:
            vetor[k] = l[i]
            i = i+1
        else:
            vetor[k] = r[j]
            j = j+1
        k = k+1

    while i < len(l):
        vetor[k] = l[i]
        i = i + 1
        k = k + 1
    while j < len(r):
        vetor[k] = r[j]
        j = j + 1
        k = k + 1
    

def mergesort(vetor, inicio, fim):
    if inicio < fim:
        meio = (inicio + fim) // 2
        mergesort(vetor, inicio, meio)
        mergesort(vetor, meio + 1, fim)
        intercala(vetor, inicio, meio, fim)



# Tamanhos de entrada para o experimento
tamanhos = [100, 500, 1000, 5000, 10000]

# Resultados
tempos = []


for n in tamanhos:
    A = [random.randint(0, 10000) for _ in range(n)]
    inicio = time.time()
    mergesort(A,0,len(A)-1)
    fim = time.time()
    tempos.append(fim - inicio)

# Exibição dos resultados
print("Tamanho\tTempo (s)")
for n, t in zip(tamanhos, tempos):
    print(f"{n}\t{t:.4f}")


plt.plot(tamanhos, tempos)

plt.xlabel('Tamanho do vetor')
plt.ylabel('Tempo')
plt.grid(True)
plt.show()
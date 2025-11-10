import matplotlib.pyplot as plt

# Nome do arquivo com os dados
arquivo = "resultados.txt"

# Estrutura de dados: {tipo: {algoritmo: {tamanho: tempo}}}
dados = {}
algoritmo = None
tipo = None

with open(arquivo, "r", encoding="utf-8") as f:
    for linha in f:
        linha = linha.strip()
        if not linha:
            continue
        
        # Cabeçalho do tipo "mergesort2 - Valores Aleatorios"
        if "-" in linha and "Valores" in linha:
            partes = linha.split(" - ")
            algoritmo = partes[0].strip()
            tipo = partes[1].strip()
            if tipo not in dados:
                dados[tipo] = {}
            if algoritmo not in dados[tipo]:
                dados[tipo][algoritmo] = {"tamanho": [], "tempo": []}
        
        # Linha de valores: "100    0.000000"
        elif algoritmo and tipo:
            partes = linha.split()
            if len(partes) == 2:
                tamanho, tempo = partes
                dados[tipo][algoritmo]["tamanho"].append(int(tamanho))
                dados[tipo][algoritmo]["tempo"].append(float(tempo))

# ---- PLOTAGEM ----
for tipo, algoritmos in dados.items():
    plt.figure(figsize=(8, 5))
    for algoritmo, valores in algoritmos.items():
        plt.plot(valores["tamanho"], valores["tempo"], marker='o', label=algoritmo)
    
    plt.title(f"Comparação de Algoritmos - {tipo}")
    plt.xlabel("Tamanho do Vetor")
    plt.ylabel("Tempo (s)")
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.tight_layout()
    plt.show()

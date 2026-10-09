
import subprocess
import csv
from pathlib import Path
import matplotlib.pyplot as plt

# Descobre a pasta onde este arquivo Python está localizado
pasta = Path(__file__).resolve().parent

executavel = pasta / "lancamentoOb.exe"
arquivo_csv = pasta / "trajetoria.csv"

# Solicita o tempo da simulação
tempo = input("Digite o tempo máximo da simulação (s): ")

# Executa o programa C++ e fornece o tempo pelo teclado
subprocess.run(
    [str(executavel)],
    input=f"{tempo}\n",
    text=True,
    check=True
)

# Lê os pontos gerados pelo C++
x = []
y = []

with open(arquivo_csv, "r", newline="") as arquivo:
    leitor = csv.DictReader(arquivo)

    for linha in leitor:
        x.append(float(linha["x"]))
        y.append(float(linha["y"]))

# Desenha a trajetória
plt.figure(figsize=(10, 5))
plt.plot(x, y, label="Trajetória simulada")

plt.title("Simulação de lançamento oblíquo")
plt.xlabel("Distância horizontal (m)")
plt.ylabel("Altura (m)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
import sys

reservatorio = [5, 4, 3, 2, 1, 4]

# maximo ponto do reservatorio
idx_pico = 0
pico = -1

for i, v in enumerate(reservatorio):
    if v >= pico:
        pico = v
        idx_pico = i

print(f"{idx_pico} {pico}")
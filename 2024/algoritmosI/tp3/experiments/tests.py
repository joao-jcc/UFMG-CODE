import os
import subprocess
import time

INPUT_DIR = "testCases/inputs"
OUTPUT_FILE = "results_greedy.txt"
EXECUTABLE = "./tp3"

if not os.path.exists(EXECUTABLE):
    print(f"Erro: Executável '{EXECUTABLE}' não encontrado.")
    exit(1)

with open(OUTPUT_FILE, "w") as result_file:
    result_file.write("Test Case\tVertices\tTime (nanoseconds)\n")
    
    for input_file in sorted(f for f in os.listdir(INPUT_DIR) if f.endswith(".txt")):
        input_path = os.path.join(INPUT_DIR, input_file)
        print(f"Processando {input_file}...")
        
        try:
            with open(input_path) as f:
                num_vertices = int(f.readlines()[1].split()[0])
            
            start_time = time.perf_counter_ns()
            output = subprocess.run([EXECUTABLE], stdin=open(input_path), capture_output=True, text=True).stdout.strip()
            elapsed_time = time.perf_counter_ns() - start_time
            
            if output:
                result_file.write(f"{input_file}\t{num_vertices}\t{elapsed_time}\n")
                print(f"Tempo: {elapsed_time} ns")
            else:
                print(f"Erro: Nenhuma saída gerada para {input_file}.")
        
        except Exception as e:
            print(f"Erro ao processar {input_file}: {e}")

print(f"Resultados salvos em {OUTPUT_FILE}")

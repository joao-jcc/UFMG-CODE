#include "time.hpp"

Time::Time(TSP tsp) : tsp(tsp) {

}

std::chrono::milliseconds Time::execute(size_t repeat, char method) {
    tsp.method = method;

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i=0; i < repeat; ++i) {
        tsp.solve();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration;
}


void Time::save(std::string path, size_t times) { 
    std::string base_name = path.substr(0, path.find_last_of("."));
    std::string extension = path.substr(path.find_last_of("."));
    std::string new_path = base_name + "_" + std::to_string(tsp.method) + "_"; 
    new_path += std::to_string(times) + extension; 

    std::ofstream os(path);

    if (!os.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
        exit(1);
    }

    for (auto clock : clocks) {
        os << clock.count() << " ms" << std::endl;
    }

    os.close();

    std::cout << "Dados escritos em: " << path << std::endl;
}

#include <filesystem>
#include <iostream>

void Time::executeAll(std::string folder, std::string save_path, size_t repeat, char method) {
    namespace fs = std::filesystem;

    // Verifica se o diretório existe
    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        std::cerr << "Erro: O diretório especificado não existe ou não é um diretório." << std::endl;
        return;
    }

    // Limpa os relógios anteriores
    clocks.clear();

    // Itera por todos os arquivos no diretório
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            // Lê o arquivo no grafo e configura o método
            std::string file_path = entry.path().string();
            tsp.graph.read(file_path);
            tsp.method = method;

            // Executa o TSP e registra o tempo
            auto duration = execute(repeat, method);
            clocks.push_back(duration);

            std::cout << "Arquivo: " << file_path << " - Tempo: " << duration.count() << " ms" << std::endl;
        }
    }

    // Salva os tempos no arquivo especificado
    save(save_path, repeat);
}

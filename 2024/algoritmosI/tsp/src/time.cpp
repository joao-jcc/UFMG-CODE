#include "time.hpp"


Time::Time() :  tsp(TSP()) {

}

std::chrono::microseconds Time::execute(char method, size_t repeat) {
    if (!tsp.initialized) {
        std::cerr << "TSP não inicilizado!" << std::endl;
        exit(1);
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i=0; i < repeat; ++i) {
        tsp.solve(method);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return duration;
}


void Time::save(std::string path) { 
    std::ofstream os(path);

    if (!os.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << path << std::endl;
        exit(1);
    }

    for (size_t i=0; i < clocks.size(); ++i) {
        os << clocks[i].count() << " " << number_vertices[i] << std::endl;
    }

    os.close();

    std::cout << "Dados escritos em: " << path << std::endl;
}


void Time::executeAll(std::string folder, std::string save_path, size_t repeat, char method) {
    namespace fs = std::filesystem;

    // Verifica se o diretório existe
    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        std::cerr << "Erro: diretório não existe." << std::endl;
        return;
    }

    clocks.clear();
    number_vertices.clear();

    for (const auto& entry : fs::directory_iterator(folder)) {
        std::string file_path = entry.path().string();
        std::cout << "executing: " << file_path << std::endl;
        Graph graph; 
        graph.read(file_path);
        tsp.set(graph);
        auto duration = execute(method, repeat);
        clocks.push_back(duration);
        number_vertices.push_back(graph.N);
        std::cout << "\t concluded: " << duration.count() << "microseconds" << std::endl;
    }
    save(save_path);
}

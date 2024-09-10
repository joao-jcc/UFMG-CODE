pair<int, stringstream&> EncontraCaminhosCaravana(int s, int t, int k) {
    // Adicionando as arestas de permanência
    for (int i = 1; i <= n_; ++i) {
      grafo_[i].push_back({i, 1});
    } ///  JÁ FIZEMOS

    // Inicializando os vetores de custo acumulado e de precedência
    custo_dij_.assign(n_ + 1, vector<int>(t + 1, INF));
    pai_dij_.assign(n_ + 1, vector<pair<int, int>>(t + 1, {-1, -1}));

    // Marcando o estado inicial
    custo_dij_[s][0] = 0;
    pai_dij_[s][0] = {s, -1};

    // Inicializando a fila do algoritmo
    priority_queue<EstadoDij, vector<EstadoDij>, EstadoDij> fila;
    fila.push({s, 0, 0});

    // Armazenando o estado mínimo mais profundo (será usado caso não seja
    // possível chegar ao final) e o estado de vitória, caso essa ocorra
    EstadoDij maior = {s, 0, 0}, vitoria = {0, 0, 0};

    while (!fila.empty()) {
      EstadoDij e = fila.top();
      fila.pop();
      // Significado: a caravana termina o tempo nesta posicao, tendo gasto este
      // custo
      int posicao = e.posicao, tempo = e.tempo, custo = e.custo;
      // Se o custo atual for antigo (o vértice espaco-tempo atual já foi
      // visitado) pula o processamento
      if (custo_dij_[posicao][tempo] < custo) {
        continue;
      }

      // Atualiza o vertice mais profundo mais barato encontrado
      if ((tempo > maior.tempo) ||
          (tempo == maior.tempo && custo < maior.custo) ||
          (tempo == maior.tempo && custo == maior.custo &&
           posicao < maior.posicao)) {
        maior = e;
      }

      // Se chegou à posição final, os jogadores venceram e o processamento para
      if (posicao == n_) {
        vitoria = e;
        break;
      }

      // Se chegou ao fim do tempo t, não há mais processamento a ser feito
      if (tempo == t) {
        continue;
      }

      // Analisa a vizinhança do vértice espaco-tempo atual
      for (pair<int, int> arco : grafo_[posicao]) {
        int u = arco.first, w = arco.second;

        // Descarta o arco se um monstro tiver terminado o turno atual no
        // destino (pois a caravana chegaria lá antes que o monstro tenha saído)
        // ou se um monstro terminar o próximo turno no destino (pois, a nao ser
        // que o destino seja a posição final e os jogadores já tenham ganhado,
        // o monstro chegaria ao destino enquanto a caravana ainda está lá)
        if (pos_monstros_.count({u, tempo}) ||
            (u != n_ && tempo + 1 != n_ &&
             pos_monstros_.count({u, tempo + 1}))) {
          continue;
        }

        // Se o vértice puder ser relaxado e o custo da aresta cabe dentro dos
        // recursos, relaxa o vértice
        int custo_atual_u = custo_dij_[u][tempo + 1];
        int novo_custo_u = custo_dij_[posicao][tempo] + w;
        int total_recursos = (tempo + 1) * k;

        if (custo_atual_u > novo_custo_u && novo_custo_u <= total_recursos) {
          custo_dij_[u][tempo + 1] = novo_custo_u;
          pai_dij_[u][tempo + 1] = {posicao, tempo};
          fila.push({u, tempo + 1, custo_dij_[u][tempo + 1]});
        }
      }
    }
    
    // AQUI
    // Encontrando o valor de vitória dos jogadores e a posição final da caravana
    pair<int, int> atual;
    int valor_vitoria = 0;

    if (vitoria.tempo != 0) {
      // Se chegou ao destino, começa a percorrer o caminho pelo espaco-tempo
      // onde a vitória ocorreu

      valor_vitoria = 1;
      atual.first = vitoria.posicao;
      atual.second = vitoria.tempo;
    } else {
      // Se não chegou ao destino, começa a percorrer o caminho pelo espaço mais
      // profundo mais barato que foi explorado;

      valor_vitoria = 0;
      atual.first = maior.posicao;
      atual.second = maior.tempo;
    }

    // Adicionando o custo e a quantidade de turnos na string de saída do Dijkstra
    caminho_caravana_ << custo_dij_[atual.first][atual.second] << " "
                      << atual.second << "\n";

    // Inverte a ordem as posições do caminho da caravana (se os
    // valores fossem colocados diretamente na saída, o caminho seria impresso
    // ao contrário)
    vector<int> tmp(atual.second + 1, -1);
    while (atual.second != -1) {
      tmp[atual.second] = atual.first;
      atual = pai_dij_[atual.first][atual.second];
    }

    // Adiciona as posições da caravana à string de saída
    for (int i = 0; i < tmp.size(); i++) {
      if (i == 0) {
        caminho_caravana_ << tmp[i];
      } else {
        caminho_caravana_ << " " << tmp[i];
      }
    }
    caminho_caravana_ << "\n";

    return {valor_vitoria, caminho_caravana_};
  }
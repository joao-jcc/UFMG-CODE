stringstream& EncontraCaminhosMonstros(int s, int t, vector<int>& monstros) {
    visitado_bfs_.assign(n_ + 1, false);
    pai_bfs_.assign(n_ + 1, 0);
    dist_bfs_.assign(n_ + 1, INF);

    visitado_bfs_[s] = true;
    dist_bfs_[s] = 0;
    queue<int> fila;
    fila.push(s);

    int v = 0;
    while (!fila.empty()) {
      v = fila.front();
      fila.pop();

      for (int u : grafo_transposto_[v]) {
        if (!visitado_bfs_[u]) {
          visitado_bfs_[u] = true;
          dist_bfs_[u] = dist_bfs_[v] + 1;
          pai_bfs_[u] = v;
          fila.push(u);
        } else if (dist_bfs_[u] == dist_bfs_[v] + 1 && pai_bfs_[u] > v) {
          pai_bfs_[u] = v;
        }
      }
    }

    for (int i = 0; i < monstros.size(); ++i) {
      int posicao = monstros[i];

      if (!visitado_bfs_[posicao]) {
        for (int t_atual = 0; t_atual <= t; ++t_atual) {
          pos_monstros_.insert({posicao, t_atual});
        }
      } else {
        for (int t_atual = 0; t_atual <= t; ++t_atual) {
          pos_monstros_.insert({posicao, t_atual});
          if (pai_bfs_[posicao] != 0) {
            posicao = pai_bfs_[posicao];
          }
        }
      }
    }

    for (int i = 0; i < monstros.size(); ++i) {
      int posicao = monstros[i];

      if (!visitado_bfs_[posicao]) {
        caminhos_monstros_ << "1 " << posicao << "\n";
        // printf("1 %d\n", posicao);
      } else {
        caminhos_monstros_ << (dist_bfs_[posicao] + 1);
        while (posicao != 0) {
          caminhos_monstros_ << " " << posicao;
          posicao = pai_bfs_[posicao];
        }
        caminhos_monstros_ << "\n";
      }
    }

    return caminhos_monstros_;
  }
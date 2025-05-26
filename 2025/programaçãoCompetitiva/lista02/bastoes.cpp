#include <iostream>
#include <vector>
#include <stack>

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

using namespace std;

int N, T;
string S;
vector<int> result;

int main() {
    cin >> T;
    
    while (T--) {
        cin >> N >> S;
        
        // Inicializa o vetor de resposta
        result.resize(N);
        
        // Pilha para auxiliar na construção da resposta
        stack<int> stk;
        int current_number = 1;
        
        // Preenche o vetor respeitando os sinais
        for (int i = 0; i < N - 1; ++i) {
            stk.push(current_number++);
            
            // Quando encontramos um sinal '>', significa que devemos
            // desempilhar a pilha para preencher a sequência em ordem decrescente
            if (S[i] == '>') {
                while (!stk.empty()) {
                    result[i - stk.size() + 1] = stk.top();
                    stk.pop();
                }
            }
        }
        
        // Coloca o último número na pilha
        stk.push(current_number++);
        
        // Desempilha os números restantes
        while (!stk.empty()) {
            result[N - stk.size()] = stk.top();
            stk.pop();
        }

        // Imprimir o resultado
        for (int i = 0; i < N; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    return 0;
}

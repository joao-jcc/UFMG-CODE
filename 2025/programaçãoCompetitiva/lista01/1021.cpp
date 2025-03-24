#include <iostream>
#include <vector>

using namespace std;

double D; long long N;
vector<unsigned> notes = {100*100, 50*100, 20*100, 10*100, 5*100, 2*100};
vector<unsigned> coins = {100, 50, 25, 10, 5, 1};


int main(void) {
    cin >> D; N = (int)(D*100);

    cout << "NOTAS:" << endl;

    for (unsigned note : notes) {
        unsigned counter = N / note;

        cout << counter << " nota(s) de R$ " << note/100 << ".00" << endl;
        N -= counter * note;
    }

    cout << "MOEDAS:" << endl;

    for (unsigned coin : coins) {
        unsigned counter = N / coin;        

        if (coin == 100) {
            cout << counter << " moeda(s) de R$ 1.00" << endl;
        } else if (coin < 100 && coin > 5) {
            cout << counter << " moeda(s) de R$ 0." << coin << endl;
        } else {
            cout << counter << " moeda(s) de R$ 0.0" << coin << endl;

        }

        N -= counter * coin;
    }

    return 0;
}
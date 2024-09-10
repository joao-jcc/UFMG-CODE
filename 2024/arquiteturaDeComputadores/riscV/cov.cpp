#include <iostream>

using namespace std;

double mean(int* arr, int n) {
    double acc = 0;
    for (int i=0; i < n; ++i) {
        acc += arr[i];
    }

    return acc/n;
}

int main(void) {
    int A[4] = {1, 2, 3, 4};
    int B[4] = {1, 2, 3, 4};

    double cov = 0;
    double m_a = mean(A, 4);
    double m_b = mean(B, 4);

     for (int i=0; i < 4; ++i) {
        cov += (A[i] - m_a) * (B[i] - m_b);
    }

    cov = cov/(3);

    cout << cov << endl;
}
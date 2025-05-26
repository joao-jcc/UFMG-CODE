#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

int main(void) {_
    int C;
    cin >> C;

    while (C--) {
        string header;
        cin >> header;

        // Parse product codes (P1, P2, ..., PN)
        vector<string> productCodes;
        int N = 0;
        for (int i = 0; i < header.length(); i++) {
            if (header[i] == 'P') {
                string code = header.substr(i, 2); // P1, P2, ...
                productCodes.push_back(code);
                i++; // skip number part
                N++;
            }
        }

        // Read the sales lines
        vector<string> sellers;
        vector<vector<int>> sales;
        string line;
        while (true) {
            cin >> line;
            if (line.substr(0, 2) == "TP") {
                // This is the totals line
                vector<int> totals;
                for (int i = 2; i < line.length(); i++) {
                    if (line[i] >= '0' && line[i] <= '9') {
                        string num = "";
                        while (i < line.length() && line[i] >= '0' && line[i] <= '9') {
                            num += line[i++];
                        }
                        totals.push_back(stoi(num));
                    }
                }
                sales.push_back(totals);
                break;
            } else {
                // Parse seller data
                string name = "";
                int i = 0;
                while (i < line.length() && isalpha(line[i])) {
                    name += line[i];
                    i++;
                }

                // Ensure that we correctly split the concatenated sales numbers
                vector<int> quantities;
                string currentNumber = "";
                while (i < line.length() && quantities.size() < N) {
                    if (line[i] >= '0' && line[i] <= '9') {
                        currentNumber += line[i];
                    } else if (!currentNumber.empty()) {
                        quantities.push_back(stoi(currentNumber));
                        currentNumber = "";
                    }
                    i++;
                }

                if (!currentNumber.empty() && quantities.size() < N) {
                    quantities.push_back(stoi(currentNumber));
                }

                sellers.push_back(name);
                sales.push_back(quantities);
            }
        }

        // Output the reconstructed report
        // Print header
        for (int i = 0; i < N; i++) {
            cout << productCodes[i] << " ";
        }
        cout << "Totals" << endl;

        // Print seller data
        for (int i = 0; i < sellers.size(); i++) {
            cout << sellers[i] << " ";
            int total = 0;
            for (int j = 0; j < N; j++) {
                cout << sales[i][j] << " ";
                total += sales[i][j];
            }
            cout << total << endl;
        }

        // Print the total row
        cout << "TP ";
        int total = 0;
        for (int i = 0; i < N; i++) {
            cout << sales[sales.size() - 1][i] << " ";
            total += sales[sales.size() - 1][i];
        }
        cout << total << endl;
    }

    return 0;
}

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);


unordered_map<char, string> dig_to_braille = {
    {'1', "*. .. .."},
    {'2', "*. *. .."},
    {'3', "** .. .."},
    {'4', "** .* .."},
    {'5', "*. .* .."},
    {'6', "** *. .."},
    {'7', "** ** .."},
    {'8', "*. ** .."},
    {'9', ".* *. .."},
    {'0', ".* ** .."}
};

unordered_map<string, char> braille_to_digit = {
    {"*. .. ..", '1'},
    {"*. *. ..", '2'},
    {"** .. ..", '3'},
    {"** .* ..", '4'},
    {"*. .* ..", '5'},
    {"** .* *.", '6'},
    {"** ** ..", '7'},
    {"*. ** ..", '8'},
    {".* *. ..", '9'},
    {".* ** ..", '0'}
};

int D; char L;
string w;

int main(void) {_
    
    cin >> D >> L;
    if (L == 'S') {
        cin >> w;
        
        for (int i=0; i < D-1; ++i) {
            cout << dig_to_braille.at(w[i]) << " ";
        }
        cout << dig_to_braille.at(w[D-1]) << endl;
    } 
    
    else {
        string p1, p2, p3;
        for (int i=0; i <D-1; ++i) {
            cin >> p1 >> p2 >> p3; w = p1 + " " + p2 + " " + p3;

            cout << "\n--------w------" << endl;
            cout << w << endl;
            cout << braille_to_digit.at(w) << " ";
        }
        cin >> p1 >> p2 >> p3; w = p1 + " " + p2 + " " + p3; 
        cout << braille_to_digit.at(w) << endl;
    }

    exit(0);
}
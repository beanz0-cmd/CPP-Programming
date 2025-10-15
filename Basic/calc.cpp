#include <iostream>
#include <limits>
using namespace std;

int getInputNumber(int number) {
    cout << "Gib die " << number << ". Zahl an: ";

    int input = 0;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ungültige Eingabe! Bitte eine Zahl eingeben. " << endl;
        cout << "Gib die " << number <<". Zahl an: ";
    }

    cout << endl;
    return input;
}

void menu();

void printResult(int result) {
    cout << "Das Ergebnis ist: " << result << "\n\n";
    menu();
}

void addition() {
    int num1 = getInputNumber(1);
    int num2 = getInputNumber(2);
    int result = num1 + num2;
    printResult(result);
}

void subtract() {
    int num1 = getInputNumber(1);
    int num2 = getInputNumber(2);
    int result = num1 - num2;
    printResult(result);
}

void multiply() {
    int num1 = getInputNumber(1);
    int num2 = getInputNumber(2);
    int result = num1 * num2;
    printResult(result);
}

void divide() {
    int num1 = getInputNumber(1);
    int num2 = getInputNumber(2);
    int result = num1 / num2;
    printResult(result);
}

void menu() {
    cout << "Wähle deinen Modus:\n(1): Addieren\n(2): Subtrahieren\n(3): Multiplizieren\n(4): Dividieren\n(q): Beenden\n> ";
    char input = ' ';
    cin >> input;
    cout << "\n";
    switch(input) {
        case('1'): 
            addition();
        break;
        case('2'): 
            subtract();
        break;
        case('3'): 
            multiply();
        break;
        case('4'): 
            divide();
        break;
        case('q'): 
            cout << "Taschenrechner wird geschlossen.\nAuf Wiedersehen!\n\n" << endl;
            return;
        break;
        default:
            cout << "Eingabe ungültig, bitte versuche es erneut!\n\n";
            menu();
    }
}

const char *str = R"(
   + ========================================================================== +
   +  _____              _                              _                       +
   + |_   _|_ _ ___  ___| |__   ___ _ __  _ __ ___  ___| |__  _ __   ___ _ __   +
   +   | |/ _` / __|/ __| '_ \ / _ \ '_ \| '__/ _ \/ __| '_ \| '_ \ / _ \ '__|  +
   +   | | (_| \__ \ (__| | | |  __/ | | | | |  __/ (__| | | | | | |  __/ |     +
   +   |_|\__,_|___/\___|_| |_|\___|_| |_|_|  \___|\___|_| |_|_| |_|\___|_|     +
   +                                                                            +
   +                                                          gemacht von beanZ +
   + ========================================================================== +
)";

int main() {
    cout << str << endl;
    
    string start = " ";
    while (start != "start") {
        cout << "Tippe zum starten 'start'\n> ";
        cin >> start;
        cout << endl;

        if (start == "q") {
            break;
        }
    }
    if(start != "q") menu();
    
    return 0;
} 
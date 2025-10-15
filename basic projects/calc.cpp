#include <iostream>
#include <limits>
using namespace std;

int getInputNumber(int number) {
    cout << "Give the " << number << ". number: ";

    int input = 0;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number. " << endl;
        cout << "Give the " << number << ". number: ";
    }

    cout << endl;
    return input;
}

void menu();

void printResult(int result) {
    cout << "The result is: " << result << "\n\n";
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
    cout << "Choose the mode:\n(1): Addition\n(2): Subtraction\n(3): Multiply\n(4): Divide\n(q): Quit\n> ";
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
            cout << "Closing Calculator.\nGood Bye!\n\n" << endl;
            return;
        break;
        default:
            cout << "Invalid input, please try again!\n\n";
            menu();
    }
}

const char *str = R"(
   + ========================================================================== +
   +                ____      _            _       _                            +
   +               / ___|__ _| | ___ _   _| | __ _| |_ ___  _ __                +
   +              | |   / _` | |/ __| | | | |/ _` | __/ _ \| '__|               +
   +              | |__| (_| | | (__| |_| | | (_| | || (_) | |                  + 
   +               \____\__,_|_|\___|\__,_|_|\__,_|\__\___/|_|                  +
   +                                                                            +
   +                                                            made by beanZ   +
   + ========================================================================== +
)";

int main() {
    cout << str << endl;
    
    string start = " ";
    while (start != "start") {
        cout << "Type 'start' to begin calculating.\n> ";
        cin >> start;
        cout << endl;

        if (start == "q") {
            break;
        }
    }
    if(start != "q") menu();
    
    return 0;
} 
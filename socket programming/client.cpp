#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int PORT;
#define ADDR "127.0.0.1" 

int askForPort() {
    int port;
    cout << "Please define the port you want to connect to: ";

    while(!(cin >> port) || port < 1 || port > 65535) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again! Please input a number between 1 and 65535" << endl;
        cout << "Please define the port you want to connect to: ";
    }

    return port;
}

int main() {
    PORT = askForPort();
    
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(ADDR);

    cout << "Connecting to " << ADDR << ":" << PORT << "..." << endl;

    if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Connecting error" << endl;
        close(clientSocket);
        return -1;
    }

    cout << "Connected to server!" << endl;
    cout << "Type 'quit' to disconnect" << endl;
    cout << endl;
    
    string message;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "> ";
            
        if (!getline(cin, message)) {
            cerr << "Error reading input" << endl;
            break;
        }

        if (message.empty()) {
            continue;
        }

        int bytesSent = send(clientSocket, message.c_str(), message.length(), 0);

        if (bytesSent < 0) {
            cerr << "Error sending message" << endl;
            break;
        }

        if (message == "quit") {
            cout << "Disconnecting..." << endl;
            break;
        }
    }

    close(clientSocket);
    cout << "Connection closed" << endl;

    return 0;
}
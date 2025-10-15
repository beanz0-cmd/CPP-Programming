#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <limits>

using namespace std;

const int numAcceptedClients = 5;
int PORT;
#define ADDR "127.0.0.1"

int receiveMessage(int clientSocket) {
    const char* exit_cmd = "quit";
    char buffer[1024] = {0};
    
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    
    if (bytesReceived < 0) {
        cerr << "Error receiving data" << endl;
        return -1;
    }
    
    if (bytesReceived == 0) {
        cout << "Client disconnected" << endl;
        return 1;
    }
    
    buffer[bytesReceived] = '\0';
    cout << "> " << buffer << endl;
    
    if (strstr(buffer, exit_cmd) != nullptr) {
        cout << "Exit command received" << endl;
        return 1;
    }
    
    return 0;
}

int cli_accept(int serverSocket) {
    struct sockaddr_in cli;
    socklen_t addrlen = sizeof(cli);
    
    memset(&cli, 0, sizeof(cli));
    
    int clientSocket = accept(serverSocket, (struct sockaddr*)&cli, &addrlen);
    
    if (clientSocket < 0) {
        cerr << "accept() error" << endl;
        return -1;
    }
    
    cout << "Connected with client from " 
         << inet_ntoa(cli.sin_addr) << ":" 
         << ntohs(cli.sin_port) << endl;
    
    return clientSocket;
}

int askForPort() {
    int port = 0;
    cout << "Bitte gib den Port für den Server an: ";
    
    while (!(cin >> port) || port < 1 || port > 65535) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again! Please input a number between 1 and 65535" << endl;
        cout << "Please define the server port: ";
    }
    
    cout << "Server wird an Port " << port << " gestartet." << endl;
    return port;
}

void createServer() {
    cout << "Welcome to the server!" << endl;
    
    PORT = askForPort();
    
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Socket creation failed" << endl;
        return;
    }
    
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        cerr << "setsockopt failed" << endl;
        close(serverSocket);
        return;
    }
    
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr(ADDR);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Bind failed - Port may be already in usage" << endl;
        close(serverSocket);
        return;
    }
    
    if (listen(serverSocket, numAcceptedClients) < 0) {
        cerr << "Listen failed" << endl;
        close(serverSocket);
        return;
    }
    
    cout << "Server runs at " << ADDR << ":" << PORT << endl;
    cout << "Waiting for connection..." << endl;
    
    int clientSocket = cli_accept(serverSocket);
    if (clientSocket < 0) {
        close(serverSocket);
        return;
    }
    
    const char* helpMsgBuf = "To close discard the connection type 'quit'\n";
    send(clientSocket, helpMsgBuf, strlen(helpMsgBuf), 0);

    while (true) {
        int result = receiveMessage(clientSocket);
        
        if (result > 0) {
            break;
        } else if (result < 0) {
            cerr << "Error reading message" << endl;
            break;
        }
    }
    
    close(clientSocket);
    close(serverSocket);
    cout << "Server terminated" << endl;
}

int main() {
    string input;
    cout << "Please type in 'start' to create the server or 'exit' to exit" << endl;
    cin >> input;
    
    if (input == "start") {
        createServer();
    } else if (input == "exit") {
        return 0;
    } else {
        cerr << "A problem occurred while starting the server." << endl;
        return -1;
    }
    
    return 0;
}
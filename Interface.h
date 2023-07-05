#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <string>
#include "valency-core/ui/console-ui/ConsoleUI.h"
#include "valency-network/node-functions/NodeFunctions.h"
#include "valency-core/file-recognition/file-writer/FileWriter.h"
#include "valency-core/file-recognition/file-reader/FileReader.h"
#include "valency-core/cryptography/aes-encryption/AES-Encryption.h"


class Interface {
private:
    ConsoleUI ui(0)
    FileReader reader;
    FileWriter writer;
    NodeFunctions node;
    AESEncryption aes(256);

    std::string privateKey;     // Read from a file on login (AES encrypted using private key)
    std::string publicKey;      // Read from a file on login (AES encrypted using private key)
    double stakedVLNC;          // Read from a file on login (AES encrypted using private key)

    // CUSTOM CONSOLE-UI TEXT
    std::vector<std::string> headerText{"{THE VALENCY NETWORK}", "Node"};    // Header
    
    std::vector<std::string> loginMenuText{"Login using User + Pass", "Login using Private Key", "Exit"};   // Login Menu
    std::string usernameLoginText = "Enter the Username";
    std::string passwordLoginText = "Enter the Password";
    std::string privateKeyLoginText = "Enter the Private Key";
    std::vector<std::string> loginSuccessText(std::string publicAddress, std::string time, std::string date, std::string ipAddress, int port);
    std::string loginFailureText = "LOGIN FAILURE";

    std::vector<std::string> displayDataText{"Display Data in Console", "Do not Display Data in Console"};

    std::string nodeIsRunningText = "NODE IS RUNNING";

    std::vector<std::string> newConnectionText(std::string ipAddress);

    std::vector<std::string> transactionReceived(std::string ipAddress);

    std::vector<std::string> transactionVerified(std::string time, std::string date, unsigned int numOfVerificationNodes, double verificationReward);

public:
    Interface() {};

    void run();
};


#endif
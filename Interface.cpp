#include "Interface.h"


void Interface::getStakedVLNC() {
    stakedVLNC = stod(aes.decrypt(privateKey, reader.getData(stakedVLNCFilePath)));
}

std::vector<std::string> Interface::loginSuccessText(std::string publicAddress, std::string time, std::string date, std::string ipAddress, int port) {
    std::vector<std::string> output{
        "LOGIN SUCCESS", 
        time + " on the " + date,
        "On IP: " + ipAddress + ":" + std::to_string(port),
        std::to_string(stakedVLNC) + "vlnc Staked",
        publicAddress};
    return output;
}

std::vector<std::string> Interface::transactionVerified(std::string time, std::string date, unsigned int numOfVerificationNodes, double verificationReward) {
    std::vector<std::string> output{
        "TRANSACTION VERIFIED", 
        time + " on the " + date, 
        "Number of Nodes: " + numOfVerificationNodes, 
        verificationReward + "vlnc Rewarded"};
    return output;
}

void Interface::login() {
    while(1) {
        switch(ui.input(loginMenuText)) {
        case 1:
            std::string user = ui.input(usernameLoginText);
            std::string pass = ui.input(passwordLoginText);

            std::pair<std::string, std::string> output = wallet.generateKeyPair(user, pass);
            privateKey = output.first;
            publicKey = output.second;

            break;
        default:
            std::string privKey = ui.input(privateKeyLoginText);
            publicKey = wallet.generatePublicKey(privKey);
        }

        if(publicKey.empty()) {
            ui.message(loginFailureText);
            continue;
        }

        ui.message(loginSuccessText(publicKey));
    }
}

bool Interface::chooseDisplayData() {
    switch(stoi(ui.input(displayDataText))) { case 1: return true; }
    return false;
}

void Interface::displayData() {
    ui.message(nodeIsRunningText);
    KnownTransactionDetails details;
    KnownTransactionDetails comparison;
    while(1) {
        comparison = node.getKnownTransactionDetails();
        if(comparison != details) {
            details = comparison;
            ui.message(transactionVerified(details.time, details.date, details.numOfVerificationNodes, details.verificationReward));
        }
    }
}

void Interface::run() {
    ui.header(headerText);

    login();

    // Get the correct filepath for stakedvlnc, read the file, decrypt it, and store it
    stakedVLNCFilePath = "stakedVLNC-" + publicKey + vlncFileType;
    getStakedVLNC();

    
    std::thread backend(node.run());     // Run the backend for the node (NodeFunctions framework from Valency Core) - run on another thread

    if(chooseDisplayData())
        displayData();
}
#include "Interface.h"


std::vector<std::string> Interface::loginSuccessText(std::string publicAddress, std::string time, std::string date, std::string ipAddress, int port) {
    std::vector<std::string> output{
        "LOGIN SUCCESS", 
        time + " on the " + date,
        "On IP: " + ipAddress + ":" + std::to_string(port),
        std::to_string(stakedVLNC) + "vlnc Staked",
        publicAddress};
    return output;
}

std::vector<std::string> Interface::newConnectionText(std::string ipAddress) {
    std::vector<std::string> output{"NEW CONNECTION", ipAddress};
    return output;
}

std::vector<std::string> Interface::transactionReceived(std::string ipAddress) {
    std::vector<std::string> output{"TRANSACTION RECEIVED FROM", ipAddress};
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
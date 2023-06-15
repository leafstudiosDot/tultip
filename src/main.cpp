#include "Block/Block.h"
#include <iostream>
#include <vector>

int main() {
    Block genesisBlock;
    genesisBlock.index = 0;
    genesisBlock.previousHash = "0";
    genesisBlock.timestamp = std::time(nullptr);
    genesisBlock.nonce = 0;

    std::vector<Transaction> transactions;

    Block newBlock;
    newBlock.mineBlock(genesisBlock, transactions);

    std::ostringstream hashStream;
    for (const auto& byte : newBlock.calculateHash()) {
        hashStream << std::setw(2) << std::setfill('0') << std::hex << std::uppercase
                   << static_cast<unsigned int>(static_cast<unsigned char>(byte));
    }
    std::string hashString = hashStream.str();

    std::cout << "Mined Block Hash: " << hashString << std::endl;

    return 0;
}

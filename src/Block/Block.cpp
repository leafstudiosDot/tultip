#include "Block.h"

std::string Block::calculateHash() const {
    std::string data = std::to_string(index) + previousHash + std::to_string(timestamp) + std::to_string(nonce);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);

    std::string calculatedHash(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);

    return calculatedHash;
}

void Block::mineBlock(const Block& previousBlock, const std::vector<Transaction>& transactions) {
    index = previousBlock.index + 1;
    previousHash = previousBlock.hash;
    timestamp = std::time(nullptr);
    this->transactions = transactions;

    difficulty = 2;

    unsigned int nonce = 0;
    std::string target(difficulty, '0');

    while (true) {
        std::string data = std::to_string(index) + previousHash + std::to_string(timestamp) + std::to_string(nonce);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.length(), hash);

        std::string calculatedHash(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);

        if (calculatedHash.substr(0, difficulty) == target) {
            this->nonce = nonce;
            this->hash = calculatedHash;
            break;
        }

        ++nonce;
    }
}

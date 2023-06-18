#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <openssl/sha.h>
#include <leveldb/db.h>
#include <nlohmann/json.hpp>

#include "Transaction/Transaction.h"

struct Block {
    int index;
    std::string previousHash;
    time_t timestamp;
    std::vector<Transaction> transactions;
    int nonce;
    std::string hash;

    int difficulty;

    std::string calculateHash() const;
    std::string serializeJson() const;
    void mineBlock(const Block& previousBlock, const std::vector<Transaction>& transactions);
};

#endif  // BLOCK_H

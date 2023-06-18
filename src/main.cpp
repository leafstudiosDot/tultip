#include "Block/Block.h"
#include <iostream>
#include <vector>
#include <string>

Block makeBlock(const Block& prevBlock, std::vector<Transaction> transaction, leveldb::DB* db) {
    Block newBlock;
    newBlock.mineBlock(newBlock, transaction);
    newBlock.index = prevBlock.index + 1;
    newBlock.previousHash = prevBlock.convertToStringHash();
    newBlock.timestamp = std::time(nullptr);
    newBlock.nonce = 0;

    std::string newKey = "block_" + std::to_string(newBlock.index);
    std::string serializedNewBlock = newBlock.serializeJson();
    leveldb::Status storeStatus = db->Put(leveldb::WriteOptions(), newKey, serializedNewBlock);
    if (!storeStatus.ok()) {
        std::cerr << "Failed to store genesis block: " << storeStatus.ToString() << std::endl;
        delete db;
        return newBlock;
    }

    return newBlock;
}

int main() {
    Block genesisBlock;
    genesisBlock.index = 0;
    genesisBlock.previousHash = "0";
    genesisBlock.timestamp = std::time(nullptr);
    genesisBlock.nonce = 0;

    std::vector<Transaction> transactions;

    Block newBlock;
    newBlock.mineBlock(genesisBlock, transactions);
    // To a Real Hash
    std::cout << "Mined Block Hash: " << newBlock.calculateHash() << std::endl;
    std::cout << "Mined Block String Hash: " << newBlock.convertToStringHash() << std::endl;
    // LevelDB
    std::string dbPath = "./blocks";
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::DB* db;
    leveldb::Status status = leveldb::DB::Open(options, dbPath, &db);
    if (!status.ok()) {
        std::cerr << "Failed to open database: " << status.ToString() << std::endl;
        return 1;
    }

    // Genesis Block to Database
    std::string genesisKey = "genesis";
    std::string serializedGenesisBlock = genesisBlock.serializeJson();
    leveldb::Status storeStatus = db->Put(leveldb::WriteOptions(), genesisKey, serializedGenesisBlock);
    if (!storeStatus.ok()) {
        std::cerr << "Failed to store genesis block: " << storeStatus.ToString() << std::endl;
        delete db;
        return 1;
    }

    Block block2 = makeBlock(newBlock, transactions, db);
    std::cout << "Mined Block Hash: " << block2.calculateHash() << std::endl;
    std::cout << "Mined Block String Hash: " << block2.convertToStringHash() << std::endl;

    Block block3 = makeBlock(block2, transactions, db);
    std::cout << "Mined Block Hash: " << block3.calculateHash() << std::endl;
    std::cout << "Mined Block String Hash: " << block3.convertToStringHash() << std::endl;


    // End
    delete db;
    return 0;
}

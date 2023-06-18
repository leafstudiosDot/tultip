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


    // End
    delete db;
    return 0;
}

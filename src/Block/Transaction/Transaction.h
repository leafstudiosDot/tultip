#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

struct Transaction {
    std::string sender;
    std::string receiver;
    double amount;
    time_t timestamp;
};

#endif  // TRANSACTION_H

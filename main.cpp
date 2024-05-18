#include <iostream>
#include <string>

#include "test.h"
#include "user.h"

#define SAMPLE_SIZE 100000

int main() {
    User * users = readEntries();
    Random r{users};
    Clock c;
    c.start();

    long long * ids = r.generateIDSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    std::string * names = r.generateUsernameSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    long long * f_ids = r.generateFalseIDSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    std::string * f_names = r.generateFalseUsernameSample(SAMPLE_SIZE);
    std::cout << c.lap() << " ms."<< std::endl;

    return 0;
}
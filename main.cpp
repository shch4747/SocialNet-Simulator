#include <iostream>
#include <string>
#include "SocialNet.hpp"

int main() {
    SocialNet sn;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        sn.processCommand(line);
    }
    return 0;
}

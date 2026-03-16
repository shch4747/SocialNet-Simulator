#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <set>
#include "AVLTree.hpp"

class User {
public:
    std::string username;
    std::set<std::string> friends;
    AVLTree posts;

    User(std::string name = "") {
        for (auto &ch : name) ch = tolower(ch);
        username = name;
    }

    void addFriend(const std::string &fname) { friends.insert(fname); }
};

#endif

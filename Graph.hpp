#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <iostream>
#include <queue>
#include <algorithm>
#include <map>
#include "User.hpp"

class Graph {
private:
    std::unordered_map<std::string, User*> users;

public:
    void addUser(const std::string &name) {
        std::string uname = toLower(name);
        if (users.count(uname)) return;
        users[uname] = new User(uname);
    }

    static std::string toLower(std::string s) {
        for (auto &c : s) c = tolower(c);
        return s;
    }

    User* getUser(const std::string &name) {
        std::string uname = toLower(name);
        if (users.count(uname)) return users[uname];
        return nullptr;
    }

    void addFriendship(const std::string &u1, const std::string &u2) {
        User *a = getUser(u1), *b = getUser(u2);
        if (!a || !b || a == b) return;
        a->addFriend(b->username);
        b->addFriend(a->username);
    }

    void listFriends(const std::string &name) {
        User *u = getUser(name);
        if (!u) return;
        for (auto &f : u->friends)
            std::cout << f << " ";
        std::cout << "\n";
    }

    void suggestFriends(const std::string &name, int N) {
        User *u = getUser(name);
        if (!u || N == 0) return;

        std::map<std::string, int> mutualCount;

        for (auto &f : u->friends) {
            User *friendUser = getUser(f);
            for (auto &fof : friendUser->friends) {
                if (fof == u->username || u->friends.count(fof)) continue;
                mutualCount[fof]++;
            }
        }

        std::vector<std::pair<std::string, int>> suggestions(mutualCount.begin(), mutualCount.end());
        std::sort(suggestions.begin(), suggestions.end(),
            [](auto &a, auto &b) {
                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
            });

        int count = 0;
        for (auto &s : suggestions) {
            if (count == N) break;
            std::cout << s.first << " ";
            count++;
        }
        if (count) std::cout << "\n";
    }

    int degreesOfSeparation(const std::string &u1, const std::string &u2) {
        std::string s = toLower(u1), t = toLower(u2);
        if (!users.count(s) || !users.count(t)) return -1;
        if (s == t) return 0;

        std::queue<std::pair<std::string, int>> q;
        std::set<std::string> visited;
        q.push({s, 0});
        visited.insert(s);

        while (!q.empty()) {
            auto [curr, dist] = q.front(); q.pop();
            for (auto &nbr : users[curr]->friends) {
                if (nbr == t) return dist + 1;
                if (!visited.count(nbr)) {
                    visited.insert(nbr);
                    q.push({nbr, dist + 1});
                }
            }
        }
        return -1;
    }
};

#endif

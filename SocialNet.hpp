#ifndef SOCIALNET_HPP
#define SOCIALNET_HPP

#include <sstream>
#include "Graph.hpp"

class SocialNet {
private:
    Graph graph;
    long long timestampCounter = 0;

public:
    void processCommand(const std::string &line) {
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "ADD") {
            std::string sub;
            ss >> sub;
            if (sub == "USER") {
                std::string uname;
                ss >> uname;
                graph.addUser(uname);
            }
            else if (sub == "FRIEND") {
                std::string u1, u2;
                ss >> u1 >> u2;
                graph.addFriendship(u1, u2);
            }
            else if (sub == "POST") {
                std::string uname;
                ss >> uname;
                size_t start = line.find('"');
                size_t end = line.rfind('"');
                if (start != std::string::npos && end != std::string::npos && end > start) {
                    std::string content = line.substr(start + 1, end - start - 1);
                    User *u = graph.getUser(uname);
                    if (u) {
                        u->posts.insert(Post(++timestampCounter, content));
                    }
                }
            }
        }

        else if (cmd == "LIST") {
            std::string sub, uname;
            ss >> sub >> uname;
            if (sub == "FRIENDS") graph.listFriends(uname);
        }

        else if (cmd == "SUGGEST") {
            std::string sub, uname;
            int N;
            ss >> sub >> uname >> N;
            if (sub == "FRIENDS") graph.suggestFriends(uname, N);
        }

        else if (cmd == "DEGREES") {
            std::string tmp, uname1, uname2;
            ss >> tmp >> tmp >> uname1 >> uname2;
            int deg = graph.degreesOfSeparation(uname1, uname2);
            std::cout << deg << "\n";
        }

        else if (cmd == "OUTPUT") {
            std::string sub, uname;
            int N;
            ss >> sub >> uname >> N;
            if (sub == "POSTS") {
                User *u = graph.getUser(uname);
                if (u) {
                    auto posts = u->posts.getRecentPosts(N == -1 ? 1e9 : N);
                    for (auto &p : posts)
                        std::cout << "\"" << p.content << "\"\n";
                }
            }
        }
    }
};

#endif

#ifndef POST_HPP
#define POST_HPP

#include <string>

struct Post {
    long long timestamp;
    std::string content;

    Post(long long ts = 0, const std::string &c = "") {
        timestamp = ts;
        content = c;
    }

    bool operator<(const Post &other) const {
        return timestamp < other.timestamp;
    }
};

#endif

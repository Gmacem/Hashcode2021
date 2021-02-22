#pragma once

#include <algorithm>
#include <iostream>

using ll = long long;

struct Config {
    int n;
};

Config parse(std::istream& in) {
    return Config{0};
}

class Creator {
public:
    explicit Creator(std::ostream& out): out_(out) {
    }

    void Print() {
    }

private:
    std::ostream& out_;
};

long long judge(Creator& c) {
    return 0;
}

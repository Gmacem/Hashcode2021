#include <iostream>
#include <iomanip>
#include "jenkins.h"

using namespace std;

using ll = long long;

bool request_compare(Request& lhs, Request& rhs) {
    return lhs.amount_of_requests > rhs.amount_of_requests;
}

bool connection_compare(CacheConnection& lhs, CacheConnection& rhs) {
    return lhs.latency < rhs.latency;
}

void solution(Config &data, Creator &creator) {
    sort(data.requests.begin(), data.requests.end(), request_compare);
    for (auto& endpoint : data.connections) {
        sort(endpoint.cache_connections.begin(), endpoint.cache_connections.end(),
                connection_compare);
    }

    for (Request& req : data.requests) {
        int id = req.endpoint_id;
        for (auto conn : data.connections[id]) {
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    clock_t start = clock();
    auto data = parse(std::cin);
    auto creator = Creator(std::cout);

    solution(data, creator);

    cerr << "Score: " << judge(creator) << '\n';
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cerr << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cerr << " sec " << endl;
    return 0;
}

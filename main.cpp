#include <iostream>
#include <iomanip>
#include "jenkins.h"

using namespace std;

using ll = long long;

Answer solution(Config &data, Creator &creator)
{
    Answer ans;

    CacheServer first;
    first.server_id = 0;
    first.videos_to_store.push_back(2);

    CacheServer second;
    second.server_id = 1;
    second.videos_to_store.push_back(3);
    second.videos_to_store.push_back(1);

    CacheServer third;
    third.server_id = 2;
    third.videos_to_store.push_back(0);
    third.videos_to_store.push_back(1);

    ans.servers.push_back(first);
    ans.servers.push_back(second);
    ans.servers.push_back(third);

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    clock_t start = clock();
    auto data = parse(std::cin);
    auto creator = Creator(std::cout);

    Answer ans = solution(data, creator);

    cerr << "Score: " << judge(data, ans) << '\n';
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cerr << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cerr << " sec " << endl;

    return 0;
}

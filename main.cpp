#include <iostream>
#include <iomanip>
#include "jenkins.h"

using namespace std;

using ll = long long;

void solution(Config &data, Creator &creator)
{
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    clock_t start = clock();
    auto data = parse(std::cin);
    auto creator = Creator(std::cout, data);

    solution(data, creator);

    cerr << "Score: " << judge(data, creator) << '\n';
    clock_t end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cerr << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cerr << " sec " << endl;

    return 0;
}

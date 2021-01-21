#pragma comment(linker, "/STACK:556777216")
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <bitset>
#include <stack>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <cmath>
#include <climits>
#include <ctime>
#include <random>
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

#define forx(_name, _from, to, value) for (int name = from; name < to; name += value)
#define rforx(_name, from, to, value) for (int name = from; name > to; name -= _value)
#define all(_STL_NAME) _STL_NAME.begin(), _STL_NAME.end()
#define rall(_STL_NAME) _STL_NAME.rbegin(), _STL_NAME.rend()
#define mp(_FIRST, _SECOND) make_pair(_FIRST, _SECOND)

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
const ld eps = 1e-9;
mt19937 rndm;

void start()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(5);
    cout.setf(ios::fixed);
    string FILENAME = "dice";
    rndm.seed(time(0));
#ifdef _DEBUG
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#else
    /*freopen((FILENAME + ".in").c_str(), "rt", stdin);
	freopen((FILENAME + ".out").c_str(), "wt", stdout);*/
#endif
}

const int MAX_N = 1e6 + 1;
const int INF = 1e15 + 7;
const int MOD = 1e9 + 7;

pair<int, pair<int, int>> choose_team_sizes(int pizzas_cnt, int team_2_cnt, int team_3_cnt, int team_4_cnt)
{
    int pizzas_left = pizzas_cnt;
    int team_2_amount, team_3_amount, team_4_amount = 0;

    team_2_amount = pizzas_left / (2 * team_2_cnt);
    pizzas_left -= team_2_amount * 2;

    if (pizzas_left > 0)
    {
        team_3_amount = pizzas_left / (3 * team_3_cnt);
        pizzas_left -= team_3_amount * 3;
    }

    if (pizzas_left > 0)
    {
        team_4_amount = pizzas_left / (4 * team_3_cnt);
        pizzas_left -= team_3_amount * 4;
    }

    return {team_2_amount, {team_3_amount, team_4_amount}};
}

struct Comparator
{
    Comparator() {}

    bool operator()(vector<int> &first, vector<int> &second) const
    {
        return first.size() > second.size();
    }
};

void solve()
{
    int pizzas_cnt, team_2_cnt, team_3_cnt, team_4_cnt;
    cin >> pizzas_cnt >> team_2_cnt >> team_3_cnt >> team_4_cnt;
    vector<vector<string>> pizza_ingr(pizzas_cnt);
    for (int i = 0; i < pizzas_cnt; ++i)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            string s;
            cin >> s;
            pizza_ingr[i].push_back(s);
        }
    }

    pair<int, pair<int, int>> team_sizes = choose_team_sizes(pizzas_cnt, team_2_cnt, team_3_cnt, team_4_cnt);

    //Output: need vector<vector<int>> delivered_pizzas - indices of delivered pizzas to one team
    vector<vector<int>> delivered_pizzas = {};

    sort(pizza_ingr.begin(), pizza_ingr.end(), Comparator());

    while (team_sizes.first > 0)
    {
        unordered_set<int> current_ingredients;

        for (int ingr : pizza_ingr.back())
        {
            current_ingredients.emplace(ingr);
        }

        for (int i = 0; i < pizza_ingr.size(); i++)
        {
        }
    }

    cout << "Pizza are delivered to " << delivered_pizzas.size() << " teams\n";
    for (auto &team_pizzas_ind : delivered_pizzas)
    {
        cout << "A " << team_pizzas_ind.size() << "-person team will receive ";
        cout << "Pizza " << team_pizzas_ind[0];
        for (int j = 1; j < team_pizzas_ind.size() - 1; ++j)
        {
            cout << ", Pizza " << team_pizzas_ind[j];
        }
        cout << " and Pizza " << team_pizzas_ind.back() << "\n";
    }
}

void multitest()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        cout << "Case #" << i + 1 << ": ";
        solve();
    }
}

int main()
{
    start();
    //multitest();
    solve();
    return 0;
}
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

struct Pizza
{
    Pizza(int i, vector<int> &ingr) : id(i), ingredients(ingr) {}

    Pizza &operator=(const Pizza &other)
    {
        ingredients = other.ingredients;
        id = other.id;
        return *this;
    }

    bool operator==(const Pizza &other) const
    {
        return id == other.id;
    }

    vector<int> &ingredients;
    int id = -1;
};

struct PizzaHash
{
    size_t operator()(const Pizza &v) const
    {
        hash<int> hasher;
        size_t seed = 0;
        for (int i : v.ingredients)
        {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed ^ v.id;
    }
};

int GetHash(const string &s)
{
    ll hash = 0;
    const int HASH_MOD = 1e9 + 7;
    const ll PRIME = 97;
    for (auto c : s)
    {
        int c_hash = c != '-' ? (c - 'a' + 1) : 27;
        hash = ((hash * PRIME) % HASH_MOD + c_hash) % HASH_MOD;
    }
    return (int)hash;
}

vector<int> emptyVector;
Pizza EmptyPizza(-1, emptyVector);

const int max_count = 100;

int calc_intersect(unordered_set<int>& cur, vector<int>& ing) {
    int res = 0;
    for (int v : ing) {
        if (cur.find(v) == cur.end()) {
            ++res;
        }
    }
    return res;
}

vector<vector<int>> delivered_pizzas;

void distribute_pizzas(int amount, int team_size, vector<Pizza>& pizzas) {
    for (int i = 0; i < amount && pizzas.size() >= team_size; ++i) {
        unordered_set<int> cur_ing;
        delivered_pizzas.push_back({team_size});
        for (int j = 0; j < team_size; ++j) {
            int best_id = pizzas.size() - 1;
            int best_intersect = calc_intersect(cur_ing, pizzas[best_id].ingredients);
            for (int z = best_id; z >= 0; --z) {
                int d = calc_intersect(cur_ing, pizzas[z].ingredients);
                if (d > best_intersect) {
                    best_id = z;
                    best_intersect = d;
                }
            }
            for (int v : pizzas[best_id].ingredients) {
                cur_ing.insert(v);
            }
            delivered_pizzas.back().push_back(pizzas[best_id].id);
            pizzas.erase(pizzas.begin() + best_id);
        }
    }
}

void solve()
{
    int pizzas_cnt, team_2_cnt, team_3_cnt, team_4_cnt;
    cin >> pizzas_cnt >> team_2_cnt >> team_3_cnt >> team_4_cnt;

    vector<vector<int>> input(pizzas_cnt);
    vector<Pizza> pizza_ingr;

    for (int i = 0; i < pizzas_cnt; ++i)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            string s;
            cin >> s;
            input[i].push_back(GetHash(s));
        }
    }

    for (int i = 0; i < pizzas_cnt; ++i)
    {
        Pizza pizza(i, input[i]);

        pizza_ingr.push_back(pizza);
    }

    sort(pizza_ingr.begin(), pizza_ingr.end(), [](Pizza& a, Pizza& b) { return a.ingredients.size() < b.ingredients.size(); });

    distribute_pizzas(team_2_cnt, 2, pizza_ingr);
    distribute_pizzas(team_3_cnt, 3, pizza_ingr);
    distribute_pizzas(team_4_cnt, 4, pizza_ingr);
    cout << delivered_pizzas.size() << '\n';
    for (int i = 0; i < delivered_pizzas.size(); ++i) {
        cout << delivered_pizzas[i][0] << ' ';
        for (int j = 1; j < delivered_pizzas[i].size(); ++j) {
            cout << delivered_pizzas[i][j] << ' ';
        }
        cout << '\n';
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

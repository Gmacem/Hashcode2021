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

    if (pizzas_left > 0)
    {
        team_4_amount = min(pizzas_left / 4, team_4_cnt);
        pizzas_left -= 4 * team_4_amount;
    }

    if (pizzas_left > 0)
    {
        team_3_amount = min(pizzas_left / 3, team_3_cnt);

        pizzas_left -= 3 * team_3_amount;
    }

    if (pizzas_left > 0)
    {
        team_2_amount = min(pizzas_left / 2, team_2_cnt);
        pizzas_left -= 2 * team_2_amount;
    }

    return {team_2_amount, {team_3_amount, team_4_amount}};
}

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

void distribute_pizzas(int &amount, int team_size, unordered_set<Pizza, PizzaHash> &pizza_ingr, vector<vector<int>> &delivered_pizzas)
{
    while (amount > 0)
    {
        unordered_set<int> current_ingredients;
        vector<int> pizzas;

        for (int j = 0; j < team_size; j++)
        {
            int max_addition = -1;
            Pizza &max_pizza = EmptyPizza;

            int counter = 0;
            for (Pizza pizza : pizza_ingr)
            {
                int current_addition = 0;
                for (int ingr : pizza.ingredients)
                {
                    if (current_ingredients.count(ingr) == 0)
                    {
                        current_addition++;
                    }
                }

                if (current_addition > max_addition)
                {
                    max_addition = current_addition;
                    max_pizza = pizza;
                }

                if (counter++ > 1000 && max_addition > -1)
                    break;
            }

            if (max_addition != -1)
            {
                for (int ingr : max_pizza.ingredients)
                {
                    current_ingredients.emplace(ingr);
                }

                pizzas.push_back(max_pizza.id);

                pizza_ingr.erase(pizza_ingr.find(max_pizza));
            }
        }

        if (pizzas.size() == team_size)
        {
            delivered_pizzas.push_back(vector<int>());

            for (int id : pizzas)
            {
                delivered_pizzas.back().push_back(id);
            }
        }

        amount--;
    }
}

void solve()
{
    int pizzas_cnt, team_2_cnt, team_3_cnt, team_4_cnt;
    cin >> pizzas_cnt >> team_2_cnt >> team_3_cnt >> team_4_cnt;

    vector<vector<int>> input(pizzas_cnt);
    unordered_set<Pizza, PizzaHash> pizza_ingr;

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

        pizza_ingr.emplace(pizza);
    }

    pair<int, pair<int, int>> team_sizes = choose_team_sizes(pizzas_cnt, team_2_cnt, team_3_cnt, team_4_cnt);

    //Output: need vector<vector<int>> delivered_pizzas - indices of delivered pizzas to one team
    vector<vector<int>> delivered_pizzas = {};

    distribute_pizzas(team_sizes.first, 2, pizza_ingr, delivered_pizzas);

    distribute_pizzas(team_sizes.second.first, 3, pizza_ingr, delivered_pizzas);

    distribute_pizzas(team_sizes.second.second, 4, pizza_ingr, delivered_pizzas);

    cout << delivered_pizzas.size() << "\n";
    for (auto &team_pizzas_ind : delivered_pizzas)
    {
        cout << team_pizzas_ind.size();
        for (auto pizza_ind : team_pizzas_ind)
        {
            cout << " " << pizza_ind;
        }
        cout << "\n";
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
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

#define forx(_name,_from, to, value) for (int name = from; name < to; name += value)
#define rforx(_name, from, to, value) for (int name = from; name > to; name -= _value)
#define all(_STL_NAME) _STL_NAME.begin(), _STL_NAME.end()
#define rall(_STL_NAME) _STL_NAME.rbegin(), _STL_NAME.rend()
#define mp(_FIRST,_SECOND) make_pair(_FIRST,_SECOND)

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
const ld eps = 1e-9;
mt19937 rndm;

void start() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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

int GetHash(const string& s) {
	ll hash = 0;
	const int HASH_MOD = 1e9 + 7;
	const ll PRIME = 97;
	for (auto c : s) {
		int c_hash = c != '-' ? (c - 'a' + 1) : 27;
		hash = ((hash * PRIME) % HASH_MOD + c_hash) % HASH_MOD;
	}
	return (int)hash;
}

void solve() {
	//Input
	int pizzas_cnt, team_2_cnt, team_3_cnt, team_4_cnt;
	cin >> pizzas_cnt >> team_2_cnt >> team_3_cnt >> team_4_cnt;
	vector<vector<string>> pizza_ingr(pizzas_cnt);
	for (int i = 0; i < pizzas_cnt; ++i) {
		int k;
		cin >> k;
		for (int j = 0; j < k; ++j) {
			string s;
			cin >> s;
			pizza_ingr[i].push_back(s);
		}
	}


	//Output: need vector<vector<int>> delivered_pizzas - indices of delivered pizzas to one team
	//Example: vector<vector<int>> delivered_pizzas = { {1, 4}, {0, 2, 3}, {5, 6, 7, 8}, {1, 4}, {0, 2, 3}, {5, 6, 7, 8} };
	cout << delivered_pizzas.size() << "\n";
	for (auto& team_pizzas_ind : delivered_pizzas) {
		cout << team_pizzas_ind.size();
		for (auto pizza_ind : team_pizzas_ind) {
			cout << " " << pizza_ind;
		}
		cout << "\n";
	}
	
}


void multitest() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		cout << "Case #" << i + 1 << ": ";
		solve();
	}
}

int main() {
	start();
	//multitest();
	solve();
	return 0;
}
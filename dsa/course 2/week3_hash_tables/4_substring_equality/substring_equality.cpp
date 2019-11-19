#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <math.h>

using std::cin;
using std::cout;
using std::map;
using std::stack;
using std::string;
using std::vector;
typedef unsigned long long ull;
using namespace std;

long long MOD1 = 1e9 + 7;
long long MOD2 = 1e9 + 9;

class Solver
{
	string s;
	vector<int> h1;
	vector<int> h2;
	vector<long long> x1;
	vector<long long> x2;

public:
	Solver(string s) : s(s)
	{
		// initialization, precalculation
		long long xx = 31;
		x1.push_back(1);
		for (int i = 1; i < s.length(); i++)
		{
			x1.push_back((x1.back() * xx) % MOD1);
		}
		x2.push_back(1);
		for (int i = 1; i < s.length(); i++)
		{
			x2.push_back((x2.back() * xx) % MOD2);
		}
		h1.push_back(s[0]);
		h2.push_back(s[0]);
		for (int i = 1; i < s.length(); i++)
		{
			long long p = (h1[i - 1] * xx) % MOD1;
			p = (p + s[i]) % MOD1;
			h1.push_back(p);
			p = (h2[i - 1] * xx) % MOD2;
			p = (p + s[i]) % MOD2;
			h2.push_back(p);
		}
	}
	bool ask(int a, int b, int l)
	{
		int computed_hash1 = (h1[a + l - 1] - (x1[l] * h1[a - 1]) % MOD1 + MOD1) % MOD1;
		int computed_hash2 = (h2[a + l - 1] - (x2[l] * h2[a - 1]) % MOD2 + MOD2) % MOD2;
		int computed_hash3 = (h1[b + l - 1] - (x1[l] * h1[b - 1]) % MOD1 + MOD1) % MOD1;
		int computed_hash4 = (h2[b + l - 1] - (x2[l] * h2[b - 1]) % MOD2 + MOD2) % MOD2;
		return computed_hash1 == computed_hash3 && computed_hash2 == computed_hash4;
	}
};

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++)
	{
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}

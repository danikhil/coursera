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

long long MOD = 100000000003;

int match_pat(string &text, int s, string &pat)
{
    for (int i = 0; i < pat.length(); i++)
    {
        if (pat[i] != text[i + s])
            return 0;
    }
    return 1;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    string pattern, text;
    cin >> pattern >> text;

    int pl = pattern.length();
    int tl = text.length();

    long long x = 5;

    long long x_pow_pl = 1;
    for (int i = 1; i < pl; i++)
    {
        x_pow_pl = (x_pow_pl * x) % MOD;
    }

    long long ph = 0;
    for (int i = pl - 1; i >= 0; i--)
    {
        ph = (ph * x) % MOD;
        ph = (ph + pattern[i]) % MOD;
    }

    //cout << ph << '\n';

    long long temp_hash = 0;
    stack<long long> match;
    for (int i = tl - 1; i >= 0; i--)
    {
        if (i < tl - pl)
        {
            temp_hash = temp_hash - (text[i + pl] * x_pow_pl) % MOD;
            temp_hash = (temp_hash + MOD) % MOD;
        }
        temp_hash = (temp_hash * x) % MOD;
        temp_hash = (temp_hash + text[i]) % MOD;
        if (i < tl - pl + 1)
        {
            //cout << temp_hash << '\n';
            if (temp_hash == ph)
            {
                if (match_pat(text, i, pattern))
                    match.push(i);
            }
        }
    }
    while (!match.empty())
    {
        /* code */
        cout << match.top() << ' ';
        match.pop();
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::map;
using std::set;
using std::string;
using std::vector;

long long MOD = 1e9 + 7;

int string_to_index(string &s, int m)
{
    long long ans = 0;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        long long k = ((int)s[i]);
        ans = (ans * 263) % MOD;
        ans = (ans + k) % MOD;
    }
    ans %= m;
    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    int query;
    cin >> query;
    map<int, vector<string>> hashmap;
    for (int i = 0; i < query; i++)
    {
        string s;
        cin >> s;
        if (s == "add")
        {
            string str;
            cin >> str;
            int pos = string_to_index(str, bucket_count);
            //cout << "pos " << pos << '\n';
            vector<string> lc = hashmap[pos];
            if (find(lc.begin(), lc.end(), str) == lc.end())
                lc.push_back(str);
            hashmap[pos] = lc;
        }
        else if (s == "find")
        {
            string str;
            cin >> str;
            int pos = string_to_index(str, bucket_count);
            if (find(hashmap[pos].begin(), hashmap[pos].end(), str) == hashmap[pos].end())
            {
                cout << "no";
            }
            else
            {
                cout << "yes";
            }
            cout << '\n';
        }
        else if (s == "del")
        {
            string str;
            cin >> str;
            int pos = string_to_index(str, bucket_count);
            auto it = find(hashmap[pos].begin(), hashmap[pos].end(), str);
            if (it != hashmap[pos].end())
                hashmap[pos].erase(it);
        }
        else
        {
            int indx;
            cin >> indx;
            for (auto it = hashmap[indx].rbegin(); it != hashmap[indx].rend(); ++it)
                cout << *it << ' ';
            cout << '\n';
        }
    }
    return 0;
}

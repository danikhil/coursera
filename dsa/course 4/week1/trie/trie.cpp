#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::string;
using std::vector;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> &patterns)
{
  trie t;
  // write your code here
  t.resize(1);
  for (auto s : patterns)
  {
    int cn = 0;
    for (int i = 0; i < s.size(); i++)
    {
      if (t[cn].find(s[i]) == t[cn].end())
      {
        t.resize(t.size() + 1);
        t[cn][s[i]] = t.size() - 1;
        cn = t.size() - 1;
      }
      else
      {
        cn = t[cn][s[i]];
      }
    }
  }
  return t;
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++)
  {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i)
  {
    for (const auto &j : t[i])
    {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
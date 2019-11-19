#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::vector;

struct Node
{
  map<char, Node> child;
  int start, end, s_pos;
  bool is_end;

  Node() {}
  Node(int len, bool is_end) : end(len), is_end(is_end) {}
  Node(int s, int s_pos, int len, bool is_end) : start(s), end(len), s_pos(s_pos), is_end(is_end) {}
};

void print_Node(Node t, string text)
{
  cout << '\n';
  if (t.start != -1)
    cout << "Node " << text[t.start] << '\n';
  cout << "Node start " << t.start << '\n';
  cout << "Node end " << t.end << '\n';
  cout << "Node start_pos " << t.s_pos << '\n';
  for (auto it = t.child.begin(); it != t.child.end(); ++it)
  {
    cout << "Node child " << it->first << '\n';
  }
  cout << '\n';
}

void find_edges(Node t, vector<pair<int, int>> &v, int fl = 0)
{
  if (fl)
  {
    int s = t.start;
    int e = t.end;
    while (t.child.size() == 1)
    {
      auto it = t.child.begin();
      e = (it->second).end;
      //v.push_back({t.start, (it->second).end});
      t = it->second;
    }
    // if (t.child.size() == 1)
    // {
    //   auto it = t.child.begin();
    //   //v.push_back({t.start, (it->second).end});
    //   t = it->second;
    // }
    v.push_back({s, e});
  }
  for (auto it = t.child.begin(); it != t.child.end(); ++it)
  {
    find_edges(it->second, v, 1);
  }
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
void make_tree(Node *t, int i, int k, int len, const string &text)
{
  if (k > len)
    return;
  char c = text[k];
  // cout << '\n';
  // cout << "k " << k;
  // print_Node(*t, text);
  if (t->child.find(c) == t->child.end())
  {
    if (t->end && text[t->start + 1] != c)
    {
      t->child.insert({text[t->start + 1], Node(t->start + 1, t->s_pos, len, true)});
      t->child.insert({c, Node(k, i, len, true)});
    }
    else if (t->end && text[t->start + 1] == c)
      t->child.insert({c, Node(t->start + 1, i, len, true)});
    else
    {
      t->child.insert({c, Node(k, i, len, true)});
    }

    if (t->is_end && k != (t->start + 1) && text[t->start + 1] == c)
    {
      make_tree(&(t->child[c]), i, k + 1, len, text);
    }
    t->is_end = false;
    t->end = t->start;
    return;
    //print_Node(*t, text);
  }
  else
  {
    t = &(t->child[c]);
    make_tree(t, i, k + 1, len, text);
  }
}

vector<string> ComputeSuffixTreeEdges(const string &text)
{
  vector<string> result;
  // Implement this function yourself
  int len = text.length() - 1;
  Node trie(-1, -1, -1, false);
  for (int i = 0; i <= len; i++)
  {
    int k = i;
    Node *t = &trie;
    make_tree(t, i, k, len, text);
    // while (k <= len)
    // {
    //   cout << '\n';
    //   cout << "k " << k;
    //   print_Node(*t, text);
    //   if (t->child.find(k) == t->child.end())
    //   {
    //     if (t->is_end)
    //     {
    //       t->is_end = false;
    //       t->end = t->start;
    //       t->child.insert({t->start + 1, Node(t->start + 1, t->s_pos, len, true)});
    //     }
    //     t->child.insert({k, Node(k, i, len, true)});
    //     //print_Node(*t, text);
    //     break;
    //   }
    //   else
    //   {
    //     t = &(t->child[k]);
    //   }
    //   k++;
    // }
  }
  vector<pair<int, int>> v;
  find_edges(trie, v);
  for (auto i : v)
  {
    //cout << i.first << ' ' << i.second << '\n';
    string s(text.begin() + i.first, text.begin() + i.second + 1);
    //cout << s << '\n';
    result.push_back(s);
  }
  return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i)
  {
    cout << edges[i] << endl;
  }
  return 0;
}

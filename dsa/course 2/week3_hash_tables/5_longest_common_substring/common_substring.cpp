#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <limits.h>
#include <math.h>
#include <algorithm>

typedef unsigned long long ull;
typedef long long ll;
using namespace std;

struct Node
{
	map<char, Node> child;
	int start, end, s_pos;
	bool is_end;

	Node() {}
	Node(int len, bool is_end) : end(len), is_end(is_end) {}
	Node(int s, int s_pos, int len, bool is_end) : start(s), end(len), s_pos(s_pos), is_end(is_end) {}
};

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
		{
			if (k != (t->start + 1))
				t->child.insert({c, Node(t->start + 1, t->s_pos, len, true)});
			else
			{
				t->child.insert({c, Node(t->start + 1, i, len, true)});
			}
		}

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

int main()
{
	string pat, text;
	while (cin >> pat >> text)
	{
		int pl = pat.length();
		int tl = text.length();
		bool rev = false;
		if (pl > tl)
		{
			swap(pat, text);
			swap(pl, tl);
			rev = true;
		}
		text += '$';
		tl += 1;
		Node trie(-1, -1, -1, false);
		for (int i = 0; i < tl; i++)
		{
			int k = i;
			Node *t = &trie;
			make_tree(t, i, k, tl - 1, text);
		}
		// 		vector<pair<int, int>> v;
		// 		find_edges(trie, v);
		// 		for (auto i : v)
		// 		{
		// 			//cout << i.first << ' ' << i.second << '\n';
		// 			string s(text.begin() + i.first, text.begin() + i.second + 1);
		// 			//cout << s << '\n';
		// 			cout << s << '\n';
		// 		}
		int ans = INT_MIN, t_s, p_s;
		for (int i = 0; i < pl && ans < pl - i; i++)
		{
			int l = 0;
			int k = i;
			Node *t = &trie;
			while (k < pl && t->child.find(pat[k]) != t->child.end())
			{
				l++;
				t = &(t->child[pat[k]]);
				k++;
			}
			if (k == pl)
			{
				while (!t->child.empty())
				{
					auto it = (t->child).begin();
					t = &(it->second);
				}
			}
			else if (text[t->start] == pat[k - 1])
			{
				for (int j = t->start + 1; j <= t->end && k < pl; j++)
				{
					if (text[j] != pat[k])
						break;
					l++;
					k++;
				}
			}
			if (l > ans)
			{
				p_s = i;
				t_s = t->s_pos;
				ans = l;
			}
		}
		if (rev)
			swap(t_s, p_s);
		if (ans)
			cout << p_s << ' ' << t_s << ' ' << ans << '\n';
		else
			cout << 0 << ' ' << 0 << ' ' << 0 << '\n';
	}
	return 0;
}
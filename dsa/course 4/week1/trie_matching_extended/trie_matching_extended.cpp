#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters = 4;
int const NA = -1;

struct Node
{
	int next[Letters];
	bool patternEnd;

	Node()
	{
		fill(next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex(char letter)
{
	switch (letter)
	{
	case 'A':
		return 0;
		break;
	case 'C':
		return 1;
		break;
	case 'G':
		return 2;
		break;
	case 'T':
		return 3;
		break;
	default:
		assert(false);
		return -1;
	}
}

vector<int> solve(string text, int n, vector<string> patterns)
{
	vector<int> result;

	// write your code here
	vector<Node> trie(1);
	//cout << "I'm in";
	for (auto s : patterns)
	{
		int indx = 0;
		for (int i = 0; i < s.length(); i++)
		{
			int c = letterToIndex(s[i]);
			if (trie[indx].next[c] != NA)
			{
				indx = trie[indx].next[c];
			}
			else
			{
				trie[indx].next[c] = trie.size();
				indx = trie.size();
				trie.push_back(Node());
			}
			if (i == s.length() - 1)
				trie[indx].patternEnd = true;
		}
	}
	// for (int i = 0; i < trie.size(); i++)
	// 	cout << trie[i].patternEnd << ' ';
	// cout << '\n';
	for (int i = 0; i < text.size(); i++)
	{
		int indx = 0, k = i, fl = 0;
		while (k < text.size())
		{
			int c = letterToIndex(text[k++]);
			if (trie[trie[indx].next[c]].patternEnd)
			{
				fl = 1;
			}
			if (trie[indx].next[c] == NA)
			{
				break;
			}
			indx = trie[indx].next[c];
		}
		if (fl)
			result.push_back(i);
	}
	return result;
}

int main(void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector<string> patterns(n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector<int> ans;
	ans = solve(t, n, patterns);

	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i];
		if (i + 1 < (int)ans.size())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}

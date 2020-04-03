#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;
using std::make_pair;

int l1,l2;

struct Node
{
	map<char, Node *> child;
	int start, end, s_pos;
	bool is_end;

	Node() {}
    Node(int end, bool is_end) : end(end), is_end(is_end) {}
    Node(int s, int s_pos, int end, bool is_end) : start(s), end(end), s_pos(s_pos), is_end(is_end) {}
}; 

void make_tree(Node *t, int i, int k, int len, const string &text)
{
	if (k > len)
        return;
    if ((!t->is_end) && t->start == t->end)
    {
        //cout << "I'm here" << '\n';
        if ((t->child).find(text[k]) == (t->child).end())
            t->child[text[k]] = new Node(k, i, k, true);
        else
        {
            t = t->child[text[k]];
            make_tree(t, i, k + 1, len, text);
        }
        return;
    }
    int j;
    for (j = t->start + 1; k <= len; j++, k++)
    {
        if (text[j] != text[k] || (!t->is_end && j > t->end))
            break;
        if (j > t->end)
            t->end = j;
    }
    //cout << k << ' ' << j << '\n';
    if (t->is_end)
    {
        t->child[text[j]] = new Node(j, t->s_pos, j, true);
        t->child[text[k]] = new Node(k, i, k, true);
        t->is_end = false;
        t->end = j - 1;
    }
    else if (j <= t->end)
    {
        Node *child_copy = new Node();
        *child_copy = *t;
        (t->child).clear();
        //free(t);
        child_copy->start = j;
        t->child[text[j]] = child_copy;
        t->child[text[k]] = new Node(k, i, k, true);
        t->end = j - 1;
        t->is_end = false;
    }
    else
    {
        //k = k - j + t->end + 1; //slow method
        if ((t->child).find(text[k]) == (t->child).end())
            t->child[text[k]] = new Node(k, i, k, true);
        else
        {
            t = t->child[text[k]];
            make_tree(t, i, k + 1, len, text);
        }
        return;
    }
}

pair<int, int> min_pair(const pair<int, int> &a, const pair<int, int> &b)
{
	return (a.second<b.second)? a: b;
}

int tree_num(int pos)
{
	if(pos<l1-1)
	return 1;
	else if(pos>=l1&&pos<l1+l2-1)
	return 2;
	return 0;
}

pair<int, int> non_shared_len(Node *t, int d)
{
	pair<int, int> ans = make_pair(t->s_pos, INT32_MAX);
	int fl=1;
	for(auto it=t->child.begin();it!=t->child.end();++it)
	{
		Node *p = it->second;
		if(p->is_end)
		{
			if(tree_num(p->s_pos))
			{
				pair<int, int> k=make_pair(p->s_pos, d+p->end-p->start+1);
				if(tree_num(k.first)!=tree_num(ans.first))
				fl=0;
				ans = min_pair(ans, k);
			}
		}
		else
		{
			pair<int, int> k=non_shared_len(p, d+p->end-p->start+1);
			if(tree_num(k.first)!=tree_num(ans.first))
			fl=0;
			ans = min_pair(ans, k);
		}
		if(fl&&ans.second==d+1)
		ans.second=d;
	}
	return ans;
}

string solve(string texts[])
{
	texts[0]+='$';
	texts[1]+='#';
	l1=texts[0].length();
	l2=texts[1].length();

	string text = texts[0]+texts[1];

	Node *tree = new Node(-1, -1, -1, false);
	
	for(int i=0;i<l1+l2;i++)
	{
		Node *t=tree;
		make_tree(t, i, i, l1+l2-1, text);
	}

	pair<int, int> ans = non_shared_len(tree, 0);
	cout << ans.first << ' ' << ans.second << '\n';
	string s = text.substr(ans.first, ans.second);
	return s;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	string texts[2];
	cin >> texts[0];
	cin >> texts[1];

	string ans = solve(texts);

	cout << ans << endl;

	return 0;
}

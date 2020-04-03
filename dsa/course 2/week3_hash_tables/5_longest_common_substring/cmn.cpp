#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <stack>
#include <limits.h>
#include <math.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::swap;
using std::unordered_map;
using std::vector;

struct Node
{
    unordered_map<char, Node *> child;
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

void find_edges(Node *t, vector<string> &result, int fl, const string &text)
{
    if (fl)
    {

        if (t->is_end)
        {
            //cout << t->start << ' ' << text.length() - 1 << '\n';
            result.push_back(&text[t->start]);
        }
        else
        {
            //cout << t->start << ' ' << t->end << '\n';
            result.push_back(string(text.begin() + t->start, text.begin() + t->end + 1));
        }
    }
    for (auto it = t->child.begin(); it != t->child.end(); ++it)
    {
        find_edges(it->second, result, 1, text);
    }
}

vector<string> ComputeSuffixTreeEdges(const string &text)
{
    vector<string> result;
    // Implement this function yourself
    int len = text.length() - 1;
    Node *trie = new Node(-1, -1, -1, false);
    for (int i = 0; i <= len; i++)
    {
        int k = i;
        Node *t = trie;
        make_tree(t, i, k, len, text);
    }
    find_edges(trie, result, 0, text);
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
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
        Node *trie = new Node(-1, -1, -1, false);
        for (int i = 0; i < tl; i++)
        {
            int k = i;
            Node *t = trie;
            make_tree(t, i, k, tl - 1, text);
        }
        int ans = INT_MIN, t_s, p_s;
        for (int i = 0; i < pl && ans < pl - i; i++)
        {
            int l = 0;
            int k = i;
            Node *t = trie;
            while (k < pl && (t->child).find(pat[k]) != t->child.end())
            {
                l++;
                bool run = true;
                if (t->start == t->end)
                {
                    t = t->child[pat[k]];
                    if (t->is_end)
                        continue;
                    for (int m = t->start + 1; m <= t->end; m++)
                    {
                        if (text[m] == pat[k])
                            k++;
                        else
                        {
                            run = false;
                            break;
                        }
                    }
                    k--;
                }
                k++;
                if (!run)
                    break;
            }
            if (k == pl)
            {
                while (!t->child.empty())
                {
                    auto it = (t->child).begin();
                    t = it->second;
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
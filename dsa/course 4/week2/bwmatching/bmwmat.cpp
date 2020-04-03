#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

int ctoi(char c)
{
    if(c=='$')
    return 0;
    return c-63;
}

void PreprocessBWT(const string &bwt, int index[], vector<vector<int> > &count)
{
    int j=0, len=bwt.length();
    for(auto i:bwt)
    {
        int idx = ctoi(i);
        count[j++][idx]++;
        if(idx!=0)
        index[idx]++;
    }

    for(int i=1;i<27;i++)
    {
        index[i]+=index[i-1];
    }

    for(int i=0;i<27;i++)
    {
        for(int j=1;j<len;j++)
        count[j][i]+=count[j-1][i];
    }
}

int find_indx(int index[], char c, int k)
{
    if(c=='$')
    return 0;
    return index[ctoi(c)-1]+k;
}

int CountOccurrences(const string &pattern, const string &bwt, int index[], const vector<vector<int> >&count)
{
    int len = bwt.length();
    int bottom = index[ctoi(pattern.back())];
    int top=0;
    if(bottom>0)
    top = index[ctoi(pattern.back())-1]+1;

    // cout << top << ' ' << bottom << '\n';

    for(auto i=pattern.rbegin()+1;i!=pattern.rend();i++)
    {
        if(top>bottom)
        return 0;
        char c = *i;
        int tmp=top;
        top = count[top][ctoi(c)];
        bottom = count[bottom][ctoi(c)];
        // cout << top << ' ' << bottom <<"\n\n";
        if(bwt[tmp]!=c)
        top+=1;
        top = find_indx(index, c, top);
        bottom = find_indx(index, c, bottom);
        // cout << top << ' ' << bottom <<'\n';
    }
    return bottom-top+1;
}

int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;

  int len=bwt.size();

  int index[27]={0}; 

  vector<vector<int> > count(len, vector<int>(27, 0));

  PreprocessBWT(bwt, index, count);
  
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, index, count);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
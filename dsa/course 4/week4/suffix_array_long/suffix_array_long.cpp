#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

int ctoi(char c)
{
  if(c=='$')
  return 0;
  if(c=='A')
  return 1;
  if(c=='C')
  return 2;
  if(c=='G')
  return 3;
  return 4;
}

vector<int> SortCharacter(const string &text)
{
  int len=text.length();
  vector<int> order(len);

  vector<int> count(5,0);

  for(auto i:text)
  count[ctoi(i)]++;

  for(int i=1;i<5;i++)
  count[i]+=count[i-1];

  for(int i=len-1;i>=0;i--)
  {
    //cout << text[i] << '\n';
    count[ctoi(text[i])]--;
    //cout << ctoi(text[i]) << '\n';
    //cout << count[]
    order[count[ctoi(text[i])]]=i;
  }

  return order;
}

vector<int> ComputeCharClasses(const string &text, const vector<int> &order)
{
  int len=text.length();
  vector<int> class_ch(len,0);

  for(int i=1;i<len;i++)
  {
    if(text[order[i]]!=text[order[i-1]])
    class_ch[order[i]]=class_ch[order[i-1]]+1;
    else
    {
      class_ch[order[i]]=class_ch[order[i-1]];
    }
  }
  return class_ch;
}

vector<int> SortDoubled(const string &text, int l, const vector<int> &order, 
                        const vector<int> &class_ch)
{
  int len=text.length();
  
  vector<int> count(len, 0);
  vector<int> newOrder(len);

  for(auto i:class_ch)
  count[i]++;

  for(int i=1;i<len;i++)
  count[i]+=count[i-1];

  for(int i=len-1;i>=0;i--)
  {
    int char_pos = (order[i]-l+len)%len;
    int cls = class_ch[char_pos];
    count[cls]-=1;
    newOrder[count[cls]]=char_pos;
  }
  return newOrder;
}

vector<int> UpdateClasses(int l, const vector<int> &newOrder, const vector<int> class_ch)
{
  int len = newOrder.size();
  vector<int> newClass(len);

  newClass[newOrder[0]]=0;

  for(int i=1;i<len;i++)
  {
    int cur1 = newOrder[i];
    int prev1 = newOrder[i-1];
    int cur2 = (cur1+l)%len;
    int prev2 = (prev1+l)%len;

    if(class_ch[cur1]!=class_ch[prev1]||class_ch[cur2]!=class_ch[prev2])
    newClass[cur1]=newClass[prev1]+1;
    else
    {
      newClass[cur1]=newClass[prev1];
    }
  }
  return newClass;
}
// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
  // Implement this function yourself

  vector<int> order=SortCharacter(text);
  vector<int> class_ch = ComputeCharClasses(text, order);

  // for(auto i:order)
  // cout << i << ' ';
  // cout << '\n';
  int len=text.length();
  int l=1;

  while(l<len)
  {
    // for(auto i:order)
    // cout << i << ' ';
    // cout << '\n';

    // for(auto i:class_ch)
    // cout << i << ' ';
    // cout << "\n\n";
    order = SortDoubled(text,l,order,class_ch);
    class_ch = UpdateClasses(l,order,class_ch);
    l<<=1;
  }

  return order;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}

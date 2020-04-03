#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <math.h>

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

vector<int> BuildSuffixArray(const string& text) {
  vector<int> order=SortCharacter(text);
  vector<int> class_ch = ComputeCharClasses(text, order);
  int len=text.length();
  int l=1;

  while(l<len)
  {
    order = SortDoubled(text,l,order,class_ch);
    class_ch = UpdateClasses(l,order,class_ch);
    l<<=1;
  }

  return order;
}

// void PreprocessBWT(const string &bwt, int index[], vector<vector<int> > &count)
// {
//     int j=0, len=bwt.length();
//     for(auto i:bwt)
//     {
//         int idx = ctoi(i);
//         count[j++][idx]++;
//         if(idx!=0)
//         index[idx]++;
//     }

//     for(int i=1;i<5;i++)
//     {
//         index[i]+=index[i-1];
//     }

//     for(int i=0;i<5;i++)
//     {
//         for(int j=1;j<len;j++)
//         count[j][i]+=count[j-1][i];
//     }
// }

// int find_indx(int index[], char c, int k)
// {
//     if(c=='$')
//     return 0;
//     return index[ctoi(c)-1]+k;
// }


// pair<int,int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
//   int len = suffix_array.size();

//   string bwt="";

//   for(auto i:suffix_array)
//   bwt.push_back(text[(i-1+len)%len]);

//   //cout << bwt << '\n';

//   int index[5]={0};
//   vector<vector<int> > count(len, vector<int>(5, 0));

//   PreprocessBWT(bwt, index, count);

//   // for(auto i:count)
//   // {
//   //   for(auto j:i)
//   //   cout << j << ' ';
//   //   cout << '\n';
//   // }
//   // cout << '\n';

//   int bottom = index[ctoi(pattern.back())];
//   int top=0;
//   if(bottom>0)
//   top = index[ctoi(pattern.back())-1]+1;

//   // cout << top << ' ' << bottom << '\n';
//   int pl=pattern.length();
//   for(auto i=pl-2;i>=0;i--)
//   {
//     if(top>bottom)
//     return make_pair(0,-1);
//     char c = pattern[i];
//     int tmp=top;
//     top = count[top][ctoi(c)];
//     bottom = count[bottom][ctoi(c)];
//     // cout << top << ' ' << bottom <<"\n\n";
//     if(bwt[tmp]!=c)
//     top+=1;
//     top = find_indx(index, c, top);
//     bottom = find_indx(index, c, bottom);
//     // cout << top << ' ' << bottom <<'\n';
//   }
//   return make_pair(top, bottom);
// }

void FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array, vector<int>& result) {

	int minIndex = 0;
	int maxIndex = text.size();
	while(minIndex < maxIndex)
	{
		int midIndex = (minIndex + maxIndex) / 2;
		int flag = text.compare(suffix_array[midIndex], std::min(text.size() - suffix_array[midIndex], pattern.size()), pattern);
		if (flag < 0)
		{
			minIndex = midIndex + 1;
		}
		else
		{
			maxIndex = midIndex;
		}

	}

	int start = minIndex;
	maxIndex = text.size();
	while(minIndex < maxIndex)
	{
		int midIndex = (minIndex + maxIndex) / 2;
		int flag = text.compare(suffix_array[midIndex], std::min(text.size() - suffix_array[midIndex], pattern.size()), pattern);
		if (flag > 0)
		{
			maxIndex = midIndex;
		}
		else
		{
			minIndex = midIndex + 1;
		}

	}

	int end = maxIndex;
	if (start <= end)
	{
		for (int i = start; i < end; i++)
		{
			result.push_back(suffix_array[i]);
		}

	}

}

int main() {

  char buffer[100001];
  scanf("%s", buffer);
  string text = buffer;
  text += '$';
  vector<int> suffix_array = BuildSuffixArray(text);

  // for(auto i:suffix_array)
  // cout << i << ' ';
  // cout << '\n';
  
  int pattern_count;
  scanf("%d", &pattern_count);
  vector<bool> occurs(text.length(), false);
  for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
    scanf("%s", buffer);
    string pattern = buffer;
    vector<int> occurrences;
		FindOccurrences(pattern, text, suffix_array, occurrences);
		for (int j = 0; j < occurrences.size(); ++j) {
			occurs[occurrences[j]] = true;
		}
    
  }
  for (int i = 0; i < occurs.size(); ++i) {
    if (occurs[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  return 0;
}

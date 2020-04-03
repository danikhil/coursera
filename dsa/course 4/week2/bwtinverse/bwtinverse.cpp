#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string InverseBWT(const string& bwt) {

  int l = bwt.size();

  int cnt[27]={0};
  int c_ar[l];

  for(int i=0;i<l;i++)
  {
    if(bwt[i]!='$')
    {
      cnt[bwt[i]-63]++;
      c_ar[i]=cnt[bwt[i]-63];
    }
  }

  for(int i=1;i<27;i++)
  cnt[i]+=cnt[i-1];

  int j=l-2;
  int pos=0;
  string text(bwt);

  text[l-1]='$';
  while(j>=0)
  {
    text[j]=bwt[pos];
    pos = cnt[bwt[pos]-64]+c_ar[pos];
    j--;
  }

  // write your code here
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}

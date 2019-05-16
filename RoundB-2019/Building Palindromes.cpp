///Building Palindromes
///Author: Ognjen Arsenijevic
///username: ognjen1998
///Full points solution (5+12=17)
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int t,n,q;
string s;
int mat[100000][26];

int main()
{
    ios_base::sync_with_stdio(0);
    cin>>t;
    for(int tc=1;tc<=t;tc++)
    {
        cin>>n>>q;
        cin>>s;
        memset(mat,0,sizeof(mat));
        mat[0][s[0]-'A']++;
        for(int i=1;i<s.size();i++)
        {
            for(int j=0;j<26;j++)
                mat[i][j]=mat[i-1][j];
            mat[i][s[i]-'A']++;
        }
        int ans=0;
        while(q--)
        {
            int l,r,cnt=0;
            cin>>l>>r;
            l--;
            r--;
            int arr[26];
            for(int i=0;i<26;i++)
                arr[i]=mat[r][i]-(l>0 ? mat[l-1][i] : 0);
            for(int i=0;i<26;i++)
            {
                if(arr[i] & 1)
                    cnt++;
            }
            if(cnt<2)
                ans++;
        }
        cout<<"Case #"<<tc<<": "<<ans<<"\n";
    }
    return 0;
}

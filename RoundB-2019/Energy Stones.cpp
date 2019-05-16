///Energy Stones
///Author: Ognjen Arsenijevic
///username: ognjen1998
///Full points solution (17+24=41)
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;

typedef struct Stone
{
    int s,e,l;
    Stone(int s, int e, int l)
    {
        this->s=s;
        this->e=e;
        this->l=l;
    }
    bool operator<(const Stone &st) const
    {
        return (this->s * st.l < st.s * this->l);
    }
}STONE;

int t,n,dp[101][10001];
vector<STONE> v;

int main()
{
    ios_base::sync_with_stdio(0);
    cin>>t;
    for(int tc=1;tc<=t;tc++)
    {
        int sum=0;
        cin>>n;
        v.clear();
        while(n--)
        {
            int s,e,l;
            cin>>s>>e>>l;
            v.push_back(Stone(s,e,l));
            sum+=s;
        }
        sort(v.begin(),v.end());
        memset(dp,-1,sizeof(dp));
        dp[0][0]=0;
        for(int i=1;i<=v.size();i++)
        {
            for(int sec=0;sec<=sum;sec++)
            {
                if(dp[i-1][sec]==-1) continue;
                dp[i][sec]=max(dp[i][sec],dp[i-1][sec]);
                dp[i][sec+v[i-1].s]=max(dp[i][sec+v[i-1].s],dp[i-1][sec]+max(0,v[i-1].e-v[i-1].l*sec));
            }
        }
        int ans=*max_element(dp[v.size()],dp[v.size()]+sum+1);
        cout<<"Case #"<<tc<<": "<<ans<<"\n";
    }
    return 0;
}

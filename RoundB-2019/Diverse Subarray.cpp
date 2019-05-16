///Diverse Subarray
///Author: Ognjen Arsenijevic
///username: ognjen1998
///Full points solution (14+28=42)
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define INF 1e9

using namespace std;

int segTree[400005],lazy[400005];

void lazyWork(int l, int r, int pos)
{
    if(lazy[pos])
    {
        segTree[pos]+=lazy[pos];
        if(l!=r)
        {
            lazy[pos*2]+=lazy[pos];
            lazy[pos*2+1]+=lazy[pos];
        }
        lazy[pos]=0;
    }
}

void update(int ul, int ur, int l, int r, int pos, int val)
{
    lazyWork(l,r,pos);
    if(l>ur || r<ul) return;
    if(l>=ul && r<=ur)
    {
        lazy[pos]+=val;
        lazyWork(l,r,pos);
        return;
    }
    int mid=(l+r)/2;
    update(ul,ur,l,mid,pos*2,val);
    update(ul,ur,mid+1,r,pos*2+1,val);
    segTree[pos]=max(segTree[pos*2],segTree[pos*2+1]);
}

int query(int ql, int qr, int l, int r, int pos)
{
    if(l>qr || r<ql) return -INF;
    lazyWork(l,r,pos);
    if(l>=ql && r<=qr)
        return segTree[pos];
    int mid=(l+r)/2;
    return max(query(ql,qr,l,mid,pos*2),query(ql,qr,mid+1,r,pos*2+1));
}

vector<int> v;
vector<int> vArr[100005];
int currIdx[100005];

int main()
{
    ios_base::sync_with_stdio(0);
    int t;
    cin>>t;
    for(int tc=1;tc<=t;tc++)
    {
        int n,s;
        v.clear();
        memset(segTree,0,sizeof(segTree));
		memset(lazy,0,sizeof(lazy));
		memset(currIdx,0,sizeof(currIdx));
		for(int i=0;i<100005;i++)
            vArr[i].clear();
        cin>>n>>s;
        for(int i=0;i<n;i++)
        {
            int in;
            cin>>in;
            v.push_back(in);
            vArr[in].push_back(i);
        }
        int ans=0;
        for(int i=0;i<n;i++)
        {
            currIdx[v[i]]++;
            update(0,i,0,n-1,1,1);
            if(currIdx[v[i]]>s+1)
                update(0,vArr[v[i]][currIdx[v[i]]-s-2],0,n-1,1,s);
            if(currIdx[v[i]]>s)
                update(0,vArr[v[i]][currIdx[v[i]]-s-1],0,n-1,1,-s-1);
            ans=max(ans,query(0,i,0,n-1,1));
        }
        cout<<"Case #"<<tc<<": "<<ans<<"\n";
    }
    return 0;
}

#include<bits/stdc++.h>
#define MAXN 400010
using namespace std;
long long a[MAXN];
long long n,m;
long long tree[MAXN];
long long b[MAXN];
void build(int s,int t,int p) {
    if(s == t) { 
        tree[p]=a[s];
        return;
    }
    int tmp=s+((t-s)/2);
    build(s,tmp,p*2);
    build(tmp+1,t,p*2+1);
    tree[p]=tree[p*2]+tree[p*2+1];
}
void update(int l,int r,int c,int s,int t,int p) {
    if(l<=s&&t<=r) {
        tree[p]+=(t-s+1)*c;
        b[p]+=c;
        return;
    }
    int tmp=s+((t-s)/2);
    if(b[p]&&s!=t) {
        tree[p*2]+=(tmp-s+1)*b[p];
        tree[p*2+1]+=(t-tmp)*b[p];
        b[p*2]+=b[p];
        b[p*2+1]+=b[p];
        b[p]=0;
    }
    if(l<=tmp) update(l,r,c,s,tmp,p*2);
    if(r>tmp) update(l,r,c,tmp+1,t,p*2+1);
    tree[p]=tree[p*2]+tree[p*2+1];
}
long long getsum(int l,int r,int s,int t,int p) {
    if(l<=s&&t<=r) return tree[p];
    long long tmp=s+((t-s)/2),sum=0;
    if (b[p]) {
        tree[p*2]+=b[p]*(tmp-s+1);
        tree[p*2+1]+=b[p]*(t-tmp);
        b[p*2]+=b[p];
        b[p*2+1]+=b[p];
        b[p] = 0;
    }
    if(l<=tmp) sum+=getsum(l,r,s,tmp,p*2);
    if(r>tmp) sum+=getsum(l,r,tmp+1,t,p*2+1);
    return sum;
}
int main() {
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    build(1,n,1);
    for(int i=1;i<=m;i++) {
        int op;
        cin>>op;
        if(op==1) {
            int l,r,c;
            cin>>l>>r>>c;
            update(l,r,c,1,n,1);
        }else {
            int l,r;
            cin>>l>>r;
            cout<<getsum(l,r,1,n,1)<<endl;
        }
    }
    return 0;
}
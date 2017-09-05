#include <cstdio>
#include <vector>
#include <fstream>

using namespace std;

const int MOD = 2014;
const int N = 100001;

int a[N];
int tree[15][N];
vector<int> v;

int index( int i ){
    i++;
    if( i == 14 ){
        i = 2;
    }
    return i;
}

int main(){
    freopen("test/15.dat", "r", stdin);
    int n, m, op, id, l, r;
    scanf("%d %d", &n, &m);
    for( int i=1; i<=n; i++ ){
        scanf("%d", &a[i]);
    }
    v.push_back(0);
    for( int i=0; i<14; i++ ){
        for( int j=1; j<=n; j++ ){
            tree[i][j] = ( tree[i][j-1] + a[j] ) % MOD ;
            a[j] *= a[j];
            a[j] %= MOD;
        }
    }
    for( int i=0; i<m; i++ ){
        scanf("%d", &op);
        if( op == 1 ){
            scanf("%d %d %d", &id, &l, &r);
            id = v[id];
            printf("%d\n", ( tree[id][r] - tree[id][l-1] + MOD) % MOD);
        } else {
            scanf("%d", &id);
            v.push_back(index( v[id] ));
        }
    }
    return 0;
}

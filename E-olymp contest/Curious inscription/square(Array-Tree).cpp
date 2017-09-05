#include <cstdio>
#include <vector>
#include <fstream>

using namespace std;

const int MOD = 2014;
const int N = 100001;

int a[N];
int tree[15][4*N];
vector<int> v;

void build( int v, int i, int l, int r ){
    if( l == r ){
        tree[i][v] = a[l];
        return;
    }
    int m = ( l + r ) / 2;
    build( v * 2, i, l, m );
    build( v * 2 + 1, i,  m + 1, r );
    tree[i][v] = (tree[i][v*2] + tree[i][2*v+1]) % MOD;
}

int sum( int v, int i, int L, int R, int l, int r ){
    if( l > r ) return 0;
    if( L == l && r == R ){
        return tree[i][v];
    }
    int m = ( L + R ) / 2;
    return ( sum( v * 2, i, L, m, l, min(r, m) ) + sum( 2 * v + 1, i, m + 1, R, max(m + 1, l), r ) ) % MOD;
}

int index( int i ){
    i++;
    if( i == 14 ){
        i = 2;
    }
    return i;
}

int main(){
    freopen("test/1.dat", "r", stdin);
    int n, m, op, id, l, r;
    scanf("%d %d", &n, &m);
    for( int i=1; i<=n; i++ ){
        scanf("%d", &a[i]);
    }
    v.push_back(0);
    for( int i=0; i<14; i++ ){
        build( 1, i, 1, n );
        for( int j=1; j<=n; j++ ){
            a[j] *= a[j];
            a[j] %= MOD;
        }
    }
    for( int i=0; i<m; i++ ){
        scanf("%d", &op);
        if( op == 1 ){
            scanf("%d %d %d", &id, &l, &r);
            id = v[id];
            printf("%d\n", sum(1, id, 1, n, l, r));
        } else {
            scanf("%d", &id);
            int k = index( v[id] );
            v.push_back(k);
        }
    }
    return 0;
}

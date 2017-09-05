#include <cstdio>
#include <vector>
#include <fstream>

using namespace std;

const int MOD = 2014;
const int N = 100001;

typedef struct Node{
    int sum;
    Node * l, * r;
    Node(int sum = 0, Node * l = NULL, Node * r = NULL) : sum(sum), l(l), r(r) {}
} * PNode;

int a[N];
PNode tree[15];
vector<int> v;

PNode build( int l, int r ){
    if( l == r ){
        return new Node( a[l] );
    }
    int m = ( l + r ) / 2;
    PNode p1 = build( l, m );
    PNode p2 = build( m + 1, r );
    return new Node( ( p1->sum + p2->sum ) % MOD, p1, p2 );
}

int sum( PNode p, int L, int R, int l, int r ){
    if( l > r ) return 0;
    if( L == l && r == R ){
        return p->sum;
    }
    int m = ( L + R ) / 2;
    return ( sum(p->l, L, m, l, min(r, m) ) + sum(p->r, m + 1, R, max(m + 1, l), r ) ) % MOD;
}

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
    for( int i=0; i<n; i++ ){
        scanf("%d", &a[i]);
    }
    v.push_back(0);
    for( int i=0; i<14; i++ ){
        tree[i] = build( 0, n-1 );
        for( int j=0; j<n; j++ ){
            a[j] *= a[j];
            a[j] %= MOD;
        }
    }
    for( int i=0; i<m; i++ ){
        scanf("%d", &op);
        if( op == 1 ){
            scanf("%d %d %d", &id, &l, &r);
            id = v[id];
            printf("%d\n", sum(tree[id], 0, n-1, l-1, r-1));
        } else {
            scanf("%d", &id);
            int k = index( v[id] );
            v.push_back(k);
        }
    }
    return 0;
}

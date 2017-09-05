#include <cstdio>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

typedef long long ll;

typedef struct Node{
   ll sum;
   Node * l, * r;
   Node(){}
   Node( ll s, Node * l = NULL, Node * r = NULL ) : sum(s), l(l), r(r) {}
} * PNode;

PNode tree[100100];
int sz = 1;

PNode build( int l, int r ){
   if( l == r ) return new Node( 0 );
   int m = ( l + r ) / 2;
   return new Node( 0, build( l, m ), build( m+1, r ) );
}

ll sum( PNode p, int L, int R, int l, int r ){
   if( l > r ) return 0;
   if( L == l && r == R ) return p->sum;
   int m = (L + R) / 2;
   return sum( p->l, L, m, l, min(r, m) ) + sum( p->r, m+1, R, max(l, m+1), r );
}

PNode update( PNode p, int l, int r, int pos, ll v ){
   if( l == r ) return new Node( p->sum + v );
   int m = (l + r) / 2;
   PNode t = new Node();
   if( pos <= m ){
       t->l = update( p->l, l, m, pos, v );
       t->r = p->r;
   } else {
       t->l = p->l;
       t->r = update( p->r, m+1, r, pos, v );
   }
   t->sum = t->l->sum + t->r->sum;
   return t;
}

int main(){
 freopen("test/1.dat", "r", stdin);
 long long y = 0, x;
 int n, f, m, op, u, v, l, r;
 scanf("%d %d", &n, &m);
 tree[0] = build( 0, n-1 );
 for( int i=0; i<m; i++ ){
   scanf("%d %lld", &op, &x);
   x = ( y + x ) % sz;
   if( op == 1 ){
       scanf("%d %d", &u, &v);
       tree[sz++] = update( tree[(int)x], 0, n-1, u-1, v );
   } else {
       scanf("%d %d", &l, &r);
       printf("%lld\n", y = sum(tree[(int)x], 0, n-1, l-1, r-1));
       y = sum(tree[(int)x], 0, n-1, l-1, r-1);
   }
 }
 return 0;
}

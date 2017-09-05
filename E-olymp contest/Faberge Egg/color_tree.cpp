#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct Node{
   unsigned int colors, add;
   Node * l, * r;
   Node(Node * p){
    if( p ){
       *this = *p;
    }
   }
   Node( unsigned int colors = 0, unsigned int add = -1, Node * l = NULL, Node * r = NULL ) : colors(colors), add(add), l(l), r(r) {}
} * PNode;

PNode tree[100100];
int sz=0;

PNode build( int l, int r ){
   if( l == r ) return new Node();
   int m = ( l + r ) / 2;
   return new Node( 0, -1, build( l, m ), build( m + 1, r ) );
}

PNode push(PNode p){
    if( p->add != -1 ){
        PNode p1 = new Node( p->l );
        PNode p2 = new Node( p->r );
        p1->colors = p1->add = p->add;
        p2->colors = p2->add = p->add;
        return new Node( p->add, -1, p1, p2 );
    } else {
        return new Node( p );
    }
}

unsigned int get( PNode &p, int L, int R, int l, int r ){
   if( l > r ) return 0;
   if( L == l && r == R ) return p->colors;
   p = push(p);
   int m = (L + R) / 2;
   return get( p->l, L, m, l, min(r, m) ) | get( p->r, m+1, R, max(l, m+1), r );
}

PNode update( PNode p, int L, int R, int l, int r, unsigned  int color ){
   if( l > r ) return p;
   if( L == l && r == R ) {
        PNode t = new Node( p );
        t->colors = color;
        t->add = color;
        return t;
   }
   PNode t = push(p);
   int m = (L + R) / 2;
   t->l = update( t->l, L, m, l, min(r, m), color );
   t->r = update( t->r, m + 1, R, max(l, m + 1), r, color );
   t->colors = t->l->colors | t->r->colors;
   return t;
}

int count_bits( unsigned  int x ){
    if( x == 0 ) return 0;
    return (x % 2) + count_bits( x / 2 );
}

int main(){
 //freopen("test/1.dat", "r", stdin);
 int M, N, id, k, v = 0, l, r, col, res;
 scanf("%d %d", &M, &N);
 tree[sz++] = build(0, M-1);
 for( int i=0; i<N; i++ ){
    scanf("%d %d", &id, &k);
    int x = ( id + v ) % id;
    tree[sz++] = tree[x];
    x = sz-1;
    for( int j=0; j<k; j++ ){
        scanf("%d %d %d", &l, &r, &col);
        tree[x] = update( tree[x], 0, M-1, l-1, r-1, 1<<(col-1) );
    }
    scanf("%d %d", &l, &r);
    printf("%d\n", v = count_bits( get( tree[sz-1], 0, M-1, l-1, r-1 ) ) );
 }
 return 0;
}

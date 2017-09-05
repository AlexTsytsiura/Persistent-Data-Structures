#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 999999;

class Treap{
protected:
  typedef struct Node{
      int cnt, prior, sum, mn, value;
      Node * l, * r;
      Node(){}
      Node( int prior, int sum, int mn, int value, Node * l = NULL, Node * r = NULL ) : prior(prior), sum(sum), mn(mn), value(value), l(l), r(r){}
  } * PNode;
  vector<PNode> treap;
  int cnt (PNode t) {
      return t ? t->cnt : 0;
  }
  int sum (PNode t) {
      return t ? t->sum : 0;
  }
  int mn (PNode t) {
      return t ? t->mn : INF;
  }
  void update (PNode t) {
      if ( t ) {
          t->cnt = 1 + cnt(t->l) + cnt(t->r);
          t->sum = sum(t->l) + sum(t->r) + t->value;
          t->mn = min( min( mn(t->l), sum(t->l) + t->value), t->value + sum(t->l) + mn(t->r) );
      }
  }
  PNode copy( PNode t ){
      PNode p = new Node();
      *p = *t;
      return p;
  }
  void merge(PNode &t, PNode l, PNode r){
      PNode p;
      if( !l || !r ){
          t = l ? l : r;
      } else {
          if( l->prior > r->prior ){
              p = copy(l);
              merge (p->r, l->r, r),  t = p;
          } else {
              p = copy(r);
              merge (p->l, l, r->l),  t = p;
          }
      }
      update(t);
  }

  void split(PNode t, PNode &l, PNode &r, int pos){
      PNode p = NULL;
      if( !t ){
          l = r = NULL;
      } else {
          p = copy(t);
          if( pos <= cnt(t->l) ){
              split( t->l, l, p->l, pos ), r = p;
          } else {
              split( t->r, p->r, r, pos - cnt(t->l) - 1 ), l = p;
          }
      }
      update(p);
  }

public:
  Treap(){
      treap.push_back( NULL );
  }
  bool insert( int i, int pos, char c ){
      PNode temp = treap[i], p1, p2;
      int val = ( c == '(' ) ? 1 : -1;
      split( temp, p1, p2, pos );
      merge( p1, p1, new Node( rand(), val, val, val ) );
      merge( p1, p1, p2 );
      treap.push_back( p1 );
      return ( p1->sum == 0 ) && ( p1->mn >= 0 );
  }
  bool erase( int i, int pos ){
      PNode temp = treap[i], p1, p2, p3;
      split( temp, p1, p2, pos );
      if( p2 ){
          split( p2, p2, p3, 1 );
          merge( p1, p1, p3 );
      }
      treap.push_back( p1 );
      if( !p1 ) {
          return true;
      }
      return ( p1->sum == 0 ) && ( p1->mn >= 0 );
  }
};

int main(){
//freopen("My/4554/9.dat", "r", stdin);
Treap * treap = new Treap();
int n, a, b, type;
char c;
scanf("%d", &n);
for( int i=1; i<=n; i++ ){
  scanf("%d %d %d", &type, &a, &b);
  bool res;
  if( type == 1 ){
      scanf(" %c", &c);
      res = treap->insert( a, b - 1, c );
  } else {
      res = treap->erase( a, b - 1 );
  }
  if( res ){
      printf("YES\n");
  } else {
      printf("NO\n");
  }
}
return 0;
}

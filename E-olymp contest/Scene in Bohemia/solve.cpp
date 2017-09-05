#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

const int N = 100010;

int M[10*N], pos, nw;
map< pair<int, int>, int> mp;

struct Query{
    int a, b, pair, used, aa, bb;
    bool ans;
    char type;
    Query( char type=0, int a=0, int b=0, int aa=0, int bb=0,  int pair=0 ) : type(type), a(a), b(b), aa(aa), bb(bb), pair(pair){used = -1;}
} *query[N];

class DSU{
private:
    int parent[N];
    int mem[2*N];
    int sz;
    void set( int x, int y ){
        mem[sz++] = x;
        mem[sz++] = parent[x];
        parent[x] = y;
    }
    void step_back(){
        sz -= 2;
        parent[mem[sz]] = mem[sz + 1];
    }
public:
    DSU(int n = 0){
        sz = 0;
        for( int i=0; i<=n; i++ ){
            parent[i] = i;
        }
    }
    int find_set( int a ){
        return a == parent[a] ? a : find_set( parent[a] );
    }
    void union_sets( int a, int b ){
        a = find_set(a);
        b = find_set(b);
        set(a, b);
    }
    bool is_union( int a, int b ){
        return find_set(a) == find_set(b);
    }
    void repair( int x ){
        while( x-- ){
            step_back();
        }
    }
    int size(){
        return sz >> 1;
    }
} * dsu;

void run( int l, int r, int N = 0, int *p = 0 ){
 if( l + 1 == r ){
   for( int i=0; i<N; i++ ){
     int t = p[i];
     if (query[t]->pair > l){
       dsu->union_sets(query[t]->a, query[t]->b);
     }
   }
   if( query[l]->type == '?' ){
     query[l]->ans = dsu->is_union(query[l]->aa, query[l]->bb);
   }
   return;
 }

 int oldPos = pos, oldSize = dsu->size(), * q = M + pos;
 nw++;
 for (int i=l; i<r; i++){
   if( query[i]->type == '-'){
     query[query[i]->pair]->used = nw;
   }
 }

 for( int i=0; i<N; i++ ){
   int t = p[i];
   if( query[t]->used == nw ){
     *q++ = t;
   } else if (query[t]->pair > l){
     dsu->union_sets(query[t]->a, query[t]->b);
   }
 }
 pos += q - (M + oldPos);
 int mid = (l + r) >> 1;
 run(l, mid, pos - oldPos, M + oldPos);
 for( int i = l; i < mid; i++ ){
  if( query[i]->type == '+' ){
    *q++ = i;
  }
 }
 pos += q - (M + oldPos);
 run(mid, r, pos - oldPos, M + oldPos);
 pos = oldPos;
 dsu->repair( dsu->size() - oldSize );
}

int main(){
  //freopen("test/1.dat", "r", stdin);
  int n, k, a, b;
  char type;
  scanf("%d %d\n", &n, &k);
  dsu = new DSU(n);

  for( int i=0; i<k; i++ ){
    scanf("\n%c", &type);
    scanf(" %d %d", &a, &b);
    a--, b--;
    if (a > b) swap(a, b);
    if( type == '?' ){
        query[i] = new Query( type, 0, 0, a, b, k );
        continue;
    }
    pair<int, int> p = make_pair(a, b);
    if( mp.count(p) ){
      query[i] = new Query(type, a, b, 0, 0, mp[p]);
      query[query[i]->pair]->pair = i;
      mp.erase(p);
    } else {
      query[i] = new Query( type, a, b, 0, 0, k );
      mp[p] = i;
    }
  }

  run(0, k);

  for( int i=0; i<k; i++ ){
    if( query[i]->type == '?' ){
        printf("%s\n", ((query[i]->ans) ? ("Yes") : ("No")));
    }
  }

  return 0;
}

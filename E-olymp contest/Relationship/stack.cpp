#include <cstdio>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

class Stack{
private:
   vector< pair<int, int> > stack;
public:
   Stack(){
       stack.push_back( make_pair(0, 0) );
   }
   int push( int n, int x ){
       stack.push_back( make_pair( stack[n].first ^ x, n ) );
       return stack.back().first;
   }
   int pop( int n ){
       stack.push_back( stack[ stack[n].second ] );
       return stack.back().first;
   }
   int top( int n ){
       return stack[n].first;
   }
} * stack;

int main(){
    freopen("test/1.dat", "r", stdin);
    stack = new Stack();
    int n, a, b;
    char c;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("\n%c", &c);
        if( c == '+' ){
            scanf("%d %d", &a, &b);
            printf("%s\n", stack->push( a, b ) == 0 ? "Second" : "First" );
        } else {
            scanf("%d", &a);
           printf("%s\n", stack->pop(a) == 0 ? "Second" : "First" );
        }
    }
    return 0;
}

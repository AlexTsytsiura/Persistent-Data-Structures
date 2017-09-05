#include <cstdio>

char s[100];

int main(){
    freopen("test/1.dat", "r", stdin);
    int n, m, d, r = 1;
    scanf("%d %d", &n, &m);
    for( int i=0; i<n; i++ ) scanf("%d", &d);
    getchar();
    for( int i=0; i<m; i++ ){
        gets(s);
        r += ( s[0] == 'S' );
    }
    printf("%d\n", r);
    return 0;
}

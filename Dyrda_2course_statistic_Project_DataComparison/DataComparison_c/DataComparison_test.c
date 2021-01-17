#include < stdio.h >  
#include < stdlib.h >
#include <DataComparison.h>

int main()
{
    int N = 10;
    int a[N];
    for (int i = 0; i < N; i++) {
            cout << "[" << i + 1 << "]" << ": ";
            cin >> a[i];
        }

    int b[N];
    for (int i = 0; i < N; i++) {
            cout << "[" << i + 1 << "]" << ": ";
            cin >> b[i];
        }
        
        
    unsigned long result = compar(compar(a, b, N));
    return result;


}

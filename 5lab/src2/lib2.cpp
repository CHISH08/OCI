#include <bits/stdc++.h>
using namespace std;

int nod_ev(int a, int b){
    while(b != 0) {
        a = a % b;
        swap(a,b);
    }
    return a;
}

int nod_simp(int a, int b) {
    int m = min(a,b), nod=1;
    for (int i = m; i >= 1; --i) {
        if ((a % i == 0) && (b % i == 0)) {
            nod = i;
            break;
        }
    }
    return nod;
}
#include <bits/stdc++.h>
#include "math1.h"
#include "version.h"
using namespace std;

int main(int argc, char *argv[]){
    cout << g_version;
    double (*fun)(double a, double d);
    fun = &dif1;

    if (argc == 1){
        perror("INCORRECT INPUT KEYS (at least 2 arguments needed)\n");
        exit(0);
    }
    else {
        if ((*argv[1] == '1') && ((argc % 2) != 0)) {
            perror("INCORRECT INPUT KEYS (for every computation of dif 2 args needed)\n");
            exit(0);
        }
        else{
            for (int i = 2; i < argc; i += 2){
                cout << fun(atof(argv[i]), atof(argv[i+1])) << "\n";
            }
        }
        return 0;
    }
}

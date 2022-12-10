#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
using namespace std;
string backFile1 = "main1.back";

string backFile2 = "main2.back";
int accessPerm = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;

int main(int argc, char *argv[]) {

    ofstream fout("./pipe2.txt", ios_base::out | ios_base::trunc);

    string mapped2 = argv[0];
    int mapSize2 = mapped2.length();

    for (int i = mapSize2 - 2; i >= 0; --i) {
        fout << mapped2[i];
    }
    fout.close();
}
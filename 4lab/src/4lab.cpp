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


void wrt_fd(string &ans1, string &ans2, string name_file)
{
    ifstream file1(name_file);
    string line;
    if (file1.is_open()) {
        while (getline(file1, line)) {
            line = line + "\n";
            int lineSize = line.length();
            if (lineSize > 10) {
                ans1 += line;
            } else {
                ans2 += line;
            }
        }
    }
    file1.close();
}

int main(int argc, char *argv[])
{
    int id = fork(), id2;
    int flag = 0;
    if (id > 0) {
        id2 = fork();
        flag = 1;
    }
    if (id == -1 || id2 == -1) {
        cout << "An error ocurred with fork\n";
        return 5;
    } else if (id2 != 0 && id != 0) {
        string ans1, ans2;
        wrt_fd(ans1, ans2, "./file1.txt");
        wrt_fd(ans1, ans2, "./file2.txt");
        int mapSize1 = ans1.size(), mapSize2 = ans2.size();
        int fd1 = shm_open(backFile1.c_str(), O_RDWR | O_CREAT, accessPerm);
        ftruncate(fd1, mapSize1);
        if (fd1 == -1){
            perror("shm_open1_parent");
            exit(EXIT_FAILURE);
        }
        int fd2 = shm_open(backFile2.c_str(), O_RDWR | O_CREAT, accessPerm);
        ftruncate(fd2, mapSize2);
        if (fd2 == -1){
            perror("shm_open2_parent");
            exit(EXIT_FAILURE);
        }
        char *mapped1 = (char*) mmap(NULL, mapSize1, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
        char *mapped2 = (char*) mmap(NULL, mapSize2, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
        if (mapped1 == MAP_FAILED && mapped2 == MAP_FAILED){
            perror("mmap_parent");
            exit(EXIT_FAILURE);
        }
        memset(mapped1, '\0', mapSize1);
        for (int i = 0; i < mapSize1; ++i) {
            mapped1[i] = ans1[i];
        }
        memset(mapped2, '\0', mapSize2);
        for (int i = 0; i < mapSize2; ++i) {
            mapped2[i] = ans2[i];
        }
        wait(NULL);
    } else if (flag) {
        usleep(0015000);
        int fd1 = shm_open(backFile1.c_str(), O_RDWR, accessPerm);
        if (fd1 == -1){
            perror("shm_open1_child");
            exit(EXIT_FAILURE);
        }
        struct stat statBuf1;
        fstat(fd1, &statBuf1);
        int mapSize1 = statBuf1.st_size;
        char *mapped1 = (char*) mmap(NULL, mapSize1, PROT_READ, MAP_SHARED, fd1, 0);
        if (mapped1 == MAP_FAILED){
            perror("mmap1_child");
            exit(EXIT_FAILURE);
        }
        char *argv1[] = {NULL, NULL};
        argv1[0] = (char *) malloc(mapSize1);
        strcpy(argv1[0], mapped1);
        execv("child1", argv1);
    } else {
        usleep(0015000);
        int fd2 = shm_open(backFile2.c_str(), O_RDWR, accessPerm);
        if (fd2 == -1){
            perror("shm_open2_child");
            exit(EXIT_FAILURE);
        }
        struct stat statBuf2;
        fstat(fd2, &statBuf2);
        int mapSize2 = statBuf2.st_size;
        char *mapped2 = (char*) mmap(NULL, mapSize2, PROT_READ, MAP_SHARED, fd2, 0);
        if (mapped2 == MAP_FAILED){
            perror("mmap2_child");
            exit(EXIT_FAILURE);
        }
        char *argv2[] = {NULL, NULL};
        argv2[0] = (char *) malloc(mapSize2);
        strcpy(argv2[0], mapped2);
        execv("child2", argv2);
    }
    return 0;
}
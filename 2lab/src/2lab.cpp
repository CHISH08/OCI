#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

using namespace std;

void reverseStr(string &str)
{
    int n = str.length();

    for (int i = 0; i < n / 2; i++)
    {
        swap(str[i], str[n - i - 1]);
    }
}

void wrt_fd(int *fd1, int *fd2, string name_file)
{
    ifstream file1(name_file);
    string line;
    if (file1.is_open()) {
        while (getline(file1, line)) {
            line = line + "\n";
            int lineSize = line.length();
            if (lineSize > 10) {
                if (write(fd2[1], line.c_str(), lineSize * sizeof(char)) == -1)
                {
                    cout << "An error ocurred with writing to the pipe2\n";
                    return;
                }
            }
            else
            {
                if (write(fd1[1], line.c_str(), lineSize * sizeof(char)) == -1)
                {
                    cout << "An error ocurred with writing to the pipe1\n";
                    return;
                }
            }
        }
    }
    file1.close();
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1)
    {
        cout << "An error ocurred with opening the pipe1\n";
        return 1;
    }

    if (pipe(fd2) == -1)
    {
        cout << "An error ocurred with opening the pipe2\n";
        return 2;
    }

    int id = fork(), id2;
    int flag = 0;
    if (id > 0)
    {
        id2 = fork();
        flag = 1;
    }
    if (id == -1 || id2 == -1)
    {
        cout << "An error ocurred with fork\n";
        return 5;
    }
    else if (id2 != 0 && id != 0)
    {
        close(fd1[0]);
        close(fd2[0]);
        char *name_file1;
        char *name_file2;
        string line;
        // cin >> name_file1 >> name_file2;
        wrt_fd(fd1, fd2, "./file1.txt");
        wrt_fd(fd1, fd2, "./file2.txt");
        close(fd1[1]);
        close(fd2[1]);
    }
    else if (flag)
    {
        close(fd1[1]);
        close(fd1[1]);
        close(fd2[0]);
        dup2(fd1[0], STDIN_FILENO);
        execlp("./child1", "child1", NULL);
        close(fd1[0]);
    }
    else {
        close(fd2[1]);
        close(fd1[0]);
        close(fd1[1]);
        dup2(fd2[0], STDIN_FILENO);
        execlp("./child2", "child2", NULL);
        close(fd2[0]);
    }
    return 0;
}
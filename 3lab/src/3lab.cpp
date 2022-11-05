#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <chrono>
#include <ctime>
using namespace std;

pthread_mutex_t mtx;

typedef struct {
    int N;
    vector<vector<long long>> pol_mtx;
} dat;

dat dt;

void* mult(void *arg)
{
    pthread_mutex_lock(&mtx);
    vector<long long> m1, m2;
    int N = dt.pol_mtx.size();
    m1 = dt.pol_mtx[N - 1];
    m2 = dt.pol_mtx[N - 2];
    dt.pol_mtx.pop_back();
    dt.pol_mtx.pop_back();
    pthread_mutex_unlock(&mtx);
    
    int K1 = m1.size(), K2 = m2.size();
    vector<long long> m3(K1 + K2 - 1, 0);

    for (int i = 0; i < K1; ++i) {
        for (int j = 0; j < K2; ++j) {
            m3[i + j] += m1[i] * m2[j];
        }
    }
    pthread_mutex_lock(&mtx) == 0;
    dt.pol_mtx.push_back(m3);
    --dt.N;
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mtx, NULL);
    int file1 = open("./input3.txt", O_RDONLY);
    dup2(file1, STDIN_FILENO);

    int K, N, th_c;

    //cout << "Введите количество потоков: ";
    cin >> th_c;

    pthread_t threads[th_c];

    //cout << "\nВведите количество полиномов: ";
    cin >> N;

    //cout << "\nВведите максимальную степень вводимых полиномов: ";
    cin >> K;

    dt.N = N;

    for (int i = 0; i < N; ++i) {
        vector<long long> pol(K + 1, 0);
        for (int j = K; j >= 0; --j) {
            // cout << "\nВведите полином " << j << " степени: ";
            cin >> pol[j];
        }
        (dt.pol_mtx).push_back(pol);
    }

	auto start_time = std::chrono::steady_clock::now();
    delete new int(1);

    while(dt.N > 1) {
        int j = 0;
        for (int i = 0; i < th_c && i < dt.N / 2 && dt.N > 1 && dt.pol_mtx.size() >= 2; ++i) {
            ++j;
            if (pthread_create(&threads[i], NULL, &mult, NULL) != 0) {
                perror("Failed to creating thread!");
            }
        }

        for(int i = 0; i < j; ++i) {
	        if (pthread_join(threads[i], NULL) != 0) {
                perror("Failed to joining thread!");
            }
        }
    }

	auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    std::cout << elapsed_ns.count() << " ns\n";

    pthread_mutex_destroy(&mtx);

    for (int j = 0; j < dt.pol_mtx.size(); ++j) {
        for (int i = dt.pol_mtx[j].size() - 1; i >= 0; --i) {
            cout << dt.pol_mtx[j][i] << "x^" << i; 
            if (i != 0) {
                cout << " + ";
            } else {
                cout << '\n';
            }
        }
    }

    return 0;
}

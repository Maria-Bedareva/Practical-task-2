#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

mutex mtx;

int result = 0;

void without_mutex() {
    for (int i = 1; i <= 25; ++i) {
        result = pow(2, i);
        cout << "2 ^" << i << "=" << result << endl;
    }
}

void with_mutex() {
    unique_lock<mutex> lock(mtx);
    for (int i = 1; i <= 25; ++i) {
        result = pow(2, i);
        cout << "2 ^" << i << "=" << result << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Решение без использования мьютексов: " << endl;
    auto start = std::chrono::high_resolution_clock::now();
    thread t1(without_mutex);
    thread t2(without_mutex);
    t1.join();
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto durationWithoutSync = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    cout << "_________________________________________________________________________________________________ " << endl;
    cout << "Решение с использованием мьютексов: " << endl;
    auto startM = std::chrono::high_resolution_clock::now();
    thread t3(with_mutex);
    thread t4(with_mutex);
    t3.join();
    t4.join();
    auto endM = std::chrono::high_resolution_clock::now();
    auto durationWithSync = std::chrono::duration_cast<std::chrono::milliseconds>(endM - startM);


    std::cout << "Время при решении без мьютексов: " << durationWithoutSync.count() << " ms\n";
    std::cout << "Время при решении с мьютексами: " << durationWithSync.count() << " ms\n";

    return 0;
}
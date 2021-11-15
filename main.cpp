#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include "WorkerThread.h"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <signal.h>
#endif

bool stopped = false;

#if defined(_WIN32) || defined(_WIN64)
BOOL WINAPI interruptHandler(DWORD signal) {
    if (signal == CTRL_C_EVENT) {
        stopped = true;
    }
    return TRUE;
}
#else
void interruptHandler(int signal) {
    stopped = true;
}
#endif

int main() {
    int threadCount;
    std::cout << "Please input the number of worker threads (minimum 4): ";
    while (!(std::cin >> threadCount && threadCount > 3)) {
        std::cin.clear();
        std::cout << "Invalid syntax! Input must be a whole integer greater than 3." << std::endl;
    }

    std::vector<WorkerThread> threads;
    for (int i = 0; i < threadCount; i++) {
        auto worker = std::make_shared<Worker>();
        auto thread = std::make_shared<std::thread>(std::thread(&Worker::process, worker));
        threads.emplace_back(WorkerThread(worker, thread));
    }

#if defined(_WIN32) || defined(_WIN64)
    if (!SetConsoleCtrlHandler(interruptHandler, TRUE)) {
        std::cout << "Error: Failed to set control handler!" << std::endl;
        return 1;
    }
#else
    signal(SIGINT, interruptHandler);
#endif

    std::mt19937 mt(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> uniformDist(0, (int32_t) threads.size() - 1);
    while (!stopped) {
        auto &wt = threads[uniformDist(mt)];
        wt.getWorker()->notify();
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    std::for_each(std::begin(threads), std::end(threads), [](auto &wt) {
        wt.getWorker()->stop();
        wt.getThread()->join();
    });
    return 0;
}
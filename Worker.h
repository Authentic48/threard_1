#ifndef TSU_MULTITHREADING_2_WORKER_H
#define TSU_MULTITHREADING_2_WORKER_H

#include <condition_variable>

class Worker {
private:
    static std::mutex mutex;
    std::condition_variable condition;
    bool sleeping = false;
    bool running = true;
public:
    void notify();
    void stop();
    void process();
};

#endif
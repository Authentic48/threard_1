#ifndef TSU_MULTITHREADING_2_WORKERTHREAD_H
#define TSU_MULTITHREADING_2_WORKERTHREAD_H

#include <thread>
#include "Worker.h"

class WorkerThread {
private:
    std::shared_ptr<std::thread> thread;
    std::shared_ptr<Worker> worker;
public:
    WorkerThread(std::shared_ptr<Worker> worker, std::shared_ptr<std::thread> thread);
    [[nodiscard]] const std::shared_ptr<std::thread> &getThread() const;
    [[nodiscard]] const std::shared_ptr<Worker> &getWorker() const;
};


#endif

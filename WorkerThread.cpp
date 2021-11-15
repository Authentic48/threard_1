#include "WorkerThread.h"

WorkerThread::WorkerThread(std::shared_ptr<Worker> worker, std::shared_ptr<std::thread> thread) : worker(std::move(worker)), thread(std::move(thread)) {}

const std::shared_ptr<std::thread> &WorkerThread::getThread() const {
    return thread;
}

const std::shared_ptr<Worker> &WorkerThread::getWorker() const {
    return worker;
}

#include "../sylar/sylar.h"
#include <vector>
#include <thread>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void func1() {
    LOG_INFO(g_logger) << "thread_id" << sylar::Thread::GetName()
                       << " this.name: " << sylar::Thread::GetThis()->getName()
                       << " id: " << sylar::GetThreadId()
                       << " this.id: " << sylar::Thread::GetThis()->getId();
}

void func2() {

}

int main(int argc, char** argv){
    LOG_INFO(g_logger) << "thread test begin";
    std::vector<sylar::Thread::ptr> thrs;
    for(int i = 0; i < 5; i++){
        sylar::Thread::ptr thr(new sylar::Thread(&func1, "name_" + std::to_string(i)));
        thrs.push_back(thr);
    }
    sleep(20);

    for(int i = 0; i < 5; i++){
        thrs[i]->join();
    }

    LOG_INFO(g_logger) << "thread test end" << std::endl;
    return 0;
}
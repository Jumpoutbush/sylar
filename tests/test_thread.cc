#include "../sylar/sylar.h"
#include <vector>
#include <thread>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int count = 0;
// 加锁
// sylar::RWMutex s_mutex;
sylar::Mutex s_mutex;

void func1() {
    LOG_INFO(g_logger) << "thread_id" << sylar::Thread::GetName()
                       << " this.name: " << sylar::Thread::GetThis()->getName()
                       << " id: " << sylar::GetThreadId()
                       << " this.id: " << sylar::Thread::GetThis()->getId();
    for(int i = 0; i < 1000000; i++) {
        // sylar::RWMutex::WriteLock lock(s_mutex);
        sylar::Mutex::Lock lock(s_mutex);
        ++count;
    }
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

    for(int i = 0; i < 5; i++){
        thrs[i]->join();
    }
    LOG_INFO(g_logger) << "count = " << count << std::endl;
    LOG_INFO(g_logger) << "thread test end" << std::endl;
    return 0;
}
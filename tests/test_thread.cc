#include "../sylar/sylar.h"
#include <vector>
#include <thread>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

volatile int count = 0;
// 加锁
// sylar::RWMutex s_mutex;
sylar::Mutex s_mutex;

void func1() {
    SYLAR_LOG_INFO(g_logger) << "thread_id" << sylar::Thread::GetName()
                       << " this.name: " << sylar::Thread::GetThis()->getName()
                       << " id: " << sylar::GetThreadId()
                       << " this.id: " << sylar::Thread::GetThis()->getId();
    for(int i = 0; i < 100; ++i) {
        // sylar::RWMutex::WriteLock lock(s_mutex);
        sylar::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void func2() {
    while(true) {
        SYLAR_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void func3() {
    while(true) {
        SYLAR_LOG_INFO(g_logger) << "=======================================";
    }
}

int main(int argc, char** argv){
    SYLAR_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("../bin/conf/log2.yml");
    sylar::Config::LoadFromYaml(root);

    std::vector<sylar::Thread::ptr> thrs;
    for(int i = 0; i < 2; i++){
        sylar::Thread::ptr thr(new sylar::Thread(&func1, "name_" + std::to_string(i * 2))); 
        sylar::Thread::ptr thr2(new sylar::Thread(&func2, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr); 
    } 

    for(size_t i = 0; i < thrs.size(); i++){
        thrs[i]->join();
    }
    SYLAR_LOG_INFO(g_logger) << "thread test end" << std::endl;
    SYLAR_LOG_INFO(g_logger) << "count = " << count << std::endl;

    return 0;
}
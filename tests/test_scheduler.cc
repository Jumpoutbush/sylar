#include "../frame/sylar.h"
#include <chrono>
static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_fiber() {
    static int s_count = 3;
    SYLAR_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    if(--s_count) {
        sylar::Scheduler::GetThis()->schedule(&test_fiber, sylar::GetThreadId());
    }
}
// m fibers swap among n threads
int main(int argc, char** argv) {
    sylar::Scheduler sc(3, true, "test");  
    sc.start();
    SYLAR_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    SYLAR_LOG_INFO(g_logger) << "over";
    return 0;
}

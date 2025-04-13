#include "../sylar/sylar.h"
#include "../sylar/mutex.h"
sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();
sylar::Spinlock s_mutex;
void run_in_fiber() {
    uint64_t cur_id = sylar::Fiber::GetThis()->GetFiberId();
    SYLAR_LOG_INFO(g_logger) << "run_in_fiber " << cur_id << " begin";
    sylar::Fiber::YieldToHold();
    SYLAR_LOG_INFO(g_logger) << "run_in_fiber " << cur_id << " end";
    sylar::Fiber::YieldToHold();
}

void test_fiber() {
    SYLAR_LOG_INFO(g_logger) << "main begin -1";
    {
        sylar::Spinlock::Lock lock(s_mutex);
        sylar::Fiber::GetThis();
        SYLAR_LOG_INFO(g_logger) << "main begin";
        sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));
        fiber->swapIn();
        SYLAR_LOG_INFO(g_logger) << "main after swapIn";
        fiber->swapIn();
        SYLAR_LOG_INFO(g_logger) << "main after end";
        fiber->swapIn();
    }
    SYLAR_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    // 设置当前线程的名称为 "main"
    sylar::Thread::SetName("main");

    // 创建一个存储线程指针的向量
    std::vector<sylar::Thread::ptr> thrs;
    // 循环三次，创建三个线程
    for(int i = 0; i < 3; ++i) {
        // 创建一个新的线程，线程函数为 test_fiber，线程名称为 "name_" + i
        thrs.push_back(sylar::Thread::ptr(
                    new sylar::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    // 遍历线程向量，等待每个线程执行完毕
    for(auto i : thrs) {
        i->join();
    }
    // 返回 0，表示程序正常结束
    return 0;
}
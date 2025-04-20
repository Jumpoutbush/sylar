#include "thread.h"
#include "log.h"
#include "util.h"

namespace sylar {

static thread_local Thread* t_thread = nullptr;  // 定义一个静态线程局部变量，用于存储当前线程的指针，初始值为nullptr
static thread_local std::string t_thread_name = "UNKNOW";   //  定义一个静态线程局部变量，用于存储线程名称，初始值为"UNKNOW"

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");  //  定义一个静态全局变量，用于存储日志器的指针，使用SYLAR_LOG_NAME宏获取名为"system"的日志器

Thread* Thread::GetThis() {
    return t_thread;
}

const std::string& Thread::GetName() {
    return t_thread_name;
}

void Thread::SetName(const std::string& name) {
    if(name.empty()) {
        return;
    }
    if(t_thread) {
        t_thread->m_name = name;
    }
    t_thread_name = name;
}

Thread::Thread(std::function<void()> cb, const std::string& name)
    :m_cb(cb)
    ,m_name(name) {
    if(name.empty()) {
        m_name = "UNKNOW";
    }
    int rt = pthread_create(&m_thread, nullptr, &Thread::run, this);    //run接收一个 void* 类型的参数，这个参数就是 this 指针。
    if(rt) {
        SYLAR_LOG_ERROR(g_logger) << "pthread_create thread fail, rt=" << rt
            << " name=" << name;
        throw std::logic_error("pthread_create error");
    }
    m_semaphore.wait(); //  等待信号量，确保线程正确启动
}

Thread::~Thread() {
    if(m_thread) { //  检查线程指针是否有效
        pthread_detach(m_thread); //  将线程与调用线程分离，以便线程结束时自动回收资源
    }
}

void Thread::join() {
    if(m_thread) { //  检查线程指针m_thread是否非空，即线程是否已经创建
        int rt = pthread_join(m_thread, nullptr); //  调用pthread_join等待线程结束，第二个参数为nullptr表示不获取线程的返回值
        if(rt) {
            SYLAR_LOG_ERROR(g_logger) << "pthread_join thread fail, rt=" << rt
                << " name=" << m_name;
            throw std::logic_error("pthread_join error");
        }
        m_thread = 0;
    }
}

void* Thread::run(void* arg) {
    Thread* thread = static_cast<Thread*>(arg); //  将传入的void*类型的参数转换为Thread*类型
    t_thread = thread;
    t_thread_name = thread->m_name;
    thread->m_id = sylar::GetThreadId();
    pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str()); //  设置当前线程的名称，名称长度最多为15个字符

    std::function<void()> cb; //  定义一个std::function<void()>类型的变量cb
    cb.swap(thread->m_cb); //  将线程对象的m_cb成员变量与cb进行交换，清空线程对象的m_cb

    thread->m_semaphore.notify();

    cb();
    return 0;
}

}

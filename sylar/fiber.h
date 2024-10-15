#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include <memory>
#include <functional>
#include <ucontext.h>
#include "thread.h"

namespace  sylar
{
class Scheduler;

class Fiber : public std::enable_shared_from_this<Fiber> {
public:
    typedef std::shared_ptr<Fiber> ptr;

    // 协程几个阶段
    enum State {
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCEPT
    };
private:
    Fiber();
public:
    Fiber(std::function<void()> cb, size_t stacksize = 0);
    ~Fiber();

    // INIT, TERM
    void reset(std::function<void()> cb);
    // EXEC
    void swapIn();
    // EXEC in the background
    void swapOut();
    uint64_t getId() const { return m_id;}
    State getState() { return m_state;}
public:
    static void SetThis(Fiber* f);
    // return to current fiber
    static Fiber::ptr GetThis();
    // READY
    static void YieldToReady();
    // HOLD
    static void YieldToHold();
    // total numbers
    static uint64_t TotalFibers();

    static void MainFunc();
    static uint64_t GetFiberId();
private:
    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void* m_stack = nullptr;

    std::function<void()> m_cb;

};
} 

#endif

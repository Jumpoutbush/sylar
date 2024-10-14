#include "../sylar/sylar.h"
#include "../sylar/util.h"
#include <assert.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test(){
    SYLAR_LOG_INFO(g_logger) << sylar::BacktraceToString(10);
    SYLAR_ASSERT2(1, "abcdef xx");
}

int main(int argc, char** argv) {
    test();
    return 0;
}

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "../sylar/log.h"
#include "../sylar/singleton.h"

int main(int argc, char **argv) {
  std::cout << "======START======" << std::endl;
  sylar::Logger::ptr lg(new sylar::Logger("yyc"));
  lg->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
  sylar::FileoutLogAppender::ptr file_appender(new sylar::FileoutLogAppender("./log.txt"));
  sylar::LogEvent::ptr event(new sylar::LogEvent(
                                  lg->getName(),
                                  sylar::LogLevel::INFO,      //日志级别
                                  __FILE__,            //文件名称
                                  __LINE__,            //行号
                                  1234567,             //运行时间
                                  sylar::GetThreadId(), //线程ID
                                  sylar::GetFiberId(), //协程ID
                                  time(0)              //当前时间
                                  ));

  sylar::LogFormatter::ptr formatter(new sylar::LogFormatter(""));
  //string = "%d{%Y-%m-%d %H:%M:%S}%T%t%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"
  //添加控制台输出适配器
  sylar::StdoutLogAppender::ptr stdApd(new sylar::StdoutLogAppender());
  stdApd->setFormatter(formatter);
  lg->addAppender(stdApd);
  LOG_LEVEL(lg, sylar::LogLevel::INFO) << "[hello logger yyc]";  //event->getSS() << ...
  // lg->log(event);
  LOG_LEVEL(lg, sylar::LogLevel::INFO) << "追加内容";    //sylar::LogEventWrap(lg, event).getSS() is an annoymous object
  
  auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
  LOG_LEVEL(l, sylar::LogLevel::ERROR) << "xxx";

  std::cout << "=======END=======" << std::endl;
  return 0;
}
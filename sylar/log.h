#ifndef _SYLAR_LOG_H__
#define _SYLAR_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdarg.h>
#include <map>
#include <iostream>
#include <unistd.h>
#include "util.h"
#include "singleton.h"

#define LOG_LEVEL(logger, level)                                              \
  		if (logger->getLevel() <= level)                                        \
 			sylar::LogEventWrap(logger, sylar::LogEvent::ptr(new sylar::LogEvent(   \
                           logger->getName(), level, __FILE__, __LINE__, 0,   \
                           sylar::GetThreadId(), sylar::GetFiberId(), time(0)))).getSS()  //改为从util中获取线程和协程id
                           //解决报错initialize...是改了编译器为c++17

#define LOG_DEBUG(logger) LOG_LEVEL(logger, sylar::LogLevel::DEBUG)
#define LOG_INFO(logger) LOG_LEVEL(logger, sylar::LogLevel::INFO)
#define LOG_WARN(logger) LOG_LEVEL(logger, sylar::LogLevel::WARN)
#define LOG_ERROR(logger) LOG_LEVEL(logger, sylar::LogLevel::ERROR)
#define LOG_FATAL(logger) LOG_LEVEL(logger, sylar::LogLevel::FATAL)

#define LOG_FMT_LEVEL(logger, level, fmt, ...)                                  \
  		if (logger->getLevel() <= level)                                        \
 			sylar::LogEventWrap(logger, sylar::LogEvent::ptr(new sylar::LogEvent(   \
                           logger->getName(), level, __FILE__, __LINE__, 0,   \
                           sylar::GetThreadId(), sylar::GetFiberId(), time(0)))).getEvent()->format(fmt, __VA_ARGS__)

#define LOG_FORMAT_DEBUG(logger, fmt, ...) LOG_FMT_LEVEL(logger, sylar::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define LOG_FORMAT_INFO(logger, fmt, ...) LOG_FMT_LEVEL(logger, sylar::LogLevel::INFO, fmt, __VA_ARGS__)
#define LOG_FORMAT_WARN(logger, fmt, ...) LOG_FMT_LEVEL(logger, sylar::LogLevel::WARN, fmt, __VA_ARGS__)
#define LOG_FORMAT_ERROR(logger, fmt, ...) LOG_FMT_LEVEL(logger, sylar::LogLevel::ERROR, fmt, __VA_ARGS__)
#define LOG_FORMAT_FATAL(logger, fmt, ...) LOG_FMT_LEVEL(logger, sylar::LogLevel::FATAL, fmt, __VA_ARGS__)

#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()

namespace sylar{

//日志级别
class LogLevel{
public:
    enum Level {
        UNKNOWN = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };  
    static const char* ToString(LogLevel::Level level);
};

//日志事件
class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(const std::string& logName, LogLevel::Level level, const char *file,
           int32_t m_line, uint32_t elapse, uint32_t thread_id,
           uint32_t fiber_id, uint64_t time);

    const std::string& getLogName() const {return m_logName;}
    const char* getFile() const {return m_file;}
    int32_t getLine() const {return m_line;}
    uint32_t getElapse() const {return m_elapse;}
    uint32_t getThreadId() const {return m_threadId;}
    uint32_t getFiberId() const {return m_fiberId;}
    uint64_t getTime() const {return m_time;}
    LogLevel::Level getLevel() const {return m_level;}
    std::string getContent() const {return m_ss.str();}
    std::stringstream& getSS() {return m_ss;}  

private:
    std::string m_logName;      //日志器名称
    LogLevel::Level m_level;
    const char* m_file = nullptr;   //文件名
    int32_t m_line = 0;         //行号
    uint32_t m_elapse = 0;      //程序启动到现在的毫秒数
    uint32_t m_threadId = 0;    //线程id    uint和int有什么不同？
    uint32_t m_fiberId = 0;     //协程id
    uint64_t m_time = 0;        //时间戳   
    std::string m_content;      //消息
    std::stringstream m_ss;     

};

//日志格式器
class LogFormatter
{
public: 
    class FormatItem
    {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        //有子类 需要虚析构
        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, LogEvent::ptr event) = 0;
    };
    typedef std::shared_ptr<LogFormatter>ptr;
    LogFormatter(const std::string& pattern);

    //不同转义符对应的格式
    std::string format(LogEvent::ptr event);

    void init();
private:
    std::string m_pattern;  //接收模板字符串的字段
    std::vector<FormatItem::ptr> m_items;
};

class MessageFormatItem : public LogFormatter::FormatItem {
public:
    MessageFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << "Message";
    }
};

class LevelFormatItem : public LogFormatter::FormatItem {
public:
    LogLevel::Level level;
    LevelFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << LogLevel::ToString(level);
    }
};

class ElapseFormatItem : public LogFormatter::FormatItem {
public:
    ElapseFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << event->getElapse();
    }
};

class NameFormatItem : public LogFormatter::FormatItem {
public:
    NameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << event->getLogName();
    }
};

class ThreadIdFormatItem : public LogFormatter::FormatItem {
public:
    ThreadIdFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << event->getThreadId();
    }
};

class FiberIdFormatItem : public LogFormatter::FormatItem {
public:
    FiberIdFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << event->getFiberId();
    }
};

class DateTimeFormatItem : public LogFormatter::FormatItem {
public:
    DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S")
        :m_format(format) {
        if(m_format.empty()) {
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }

    void format(std::ostream& os, LogEvent::ptr event) override {
        struct tm tm;
        time_t time = event->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);
        os << buf;
    }
private:
    std::string m_format;
};

class FilenameFormatItem : public LogFormatter::FormatItem {
public:
    FilenameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << event->getFile();
    }
};

class LineFormatItem : public LogFormatter::FormatItem {
public:
    LineFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << event->getLine();
    }
};

class NewLineFormatItem : public LogFormatter::FormatItem {
public:
    NewLineFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << std::endl;
    }
};

class StringFormatItem : public LogFormatter::FormatItem {
public:
    StringFormatItem(const std::string& str)
        :m_string(str) {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << m_string;
    }
private:
    std::string m_string;
};

class TabFormatItem : public LogFormatter::FormatItem {
public:
    TabFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, LogEvent::ptr event) override {
        os << "\t";
    }
private:
    std::string m_string;
};

//日志输出地
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}
    
    virtual void log(LogEvent::ptr event) = 0;

    void setFormatter(LogFormatter::ptr val){m_formatter = val;}
    LogFormatter::ptr getFormatter() const {return m_formatter;}
protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger : public std::enable_shared_from_this<Logger>{
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");

    const std::string& getName() const { return m_name; }
    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level val) {m_level = val; }

    void log(LogEvent::ptr event);  //不允许使用抽象类的对象

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);     // Logger中新增
    void delAppender(LogAppender::ptr appender);     // 销毁LoggerAppender的方法
private:
    std::string m_name;         //日志名称
    LogLevel::Level m_level;    //日志级别
    std::list<LogAppender::ptr> m_appenders;        //日志输出适配器基类LogAppender
                                                    //因为一个Logger类可以输出日志到多个地方,所以可以有多个LogAppender
    LogFormatter::ptr m_formatter;
};

// LogAppender是干什么的?
// 两种类型的适配器，file和std，将日志输出到文件与控制台
// LogAppender作为基类
// 输出到控制台的Appender
class StdoutLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(LogEvent::ptr event) override;
private:
};

//输出到文件的Appender
class FileoutLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<FileoutLogAppender> ptr;
    FileoutLogAppender(const std::string& filename);
    void log(LogEvent::ptr event) override;
    
    bool reopen();//打开成功返回1
private:
    std::string m_filename;
    std::ofstream m_filestream;
};


class LogEventWrap {
public:
  LogEventWrap(Logger::ptr logger, LogEvent::ptr e);
  ~LogEventWrap();
  LogEvent::ptr getEvent() const { return m_event; }
  std::stringstream &getSS();

private:
  Logger::ptr m_logger;
  LogEvent::ptr m_event;
};

class LoggerManager {
public:
    LoggerManager();
    Logger::ptr getLogger(const std::string& name);

    void init();
    Logger::ptr getRoot() const { return m_root;}
private:
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};
typedef sylar::Singleton<LoggerManager> LoggerMgr;
}

#endif

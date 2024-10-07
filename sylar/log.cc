#include "log.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <time.h>
namespace sylar{

    const char* LogLevel::ToString(LogLevel::Level level){
        switch (level)
        {
    #define XX(name) \
            case LogLevel::name: \
                return #name; \
                break;
            XX(DEBUG);
            XX(INFO);
            XX(WARN);
            XX(ERROR);
            XX(FATAL);
    #undef XX
        default:
            return "UNKNOW";
        }
        return "UNKNOW";
    }

    Logger::Logger(const std::string& name )
        :m_name(name)
        ,m_level(LogLevel::DEBUG){

        m_formatter.reset(new LogFormatter(""));
    }

    void Logger::addAppender(LogAppender::ptr appender){
        if(!appender->getFormatter()){
            appender->setFormatter(m_formatter);
        }
        m_appenders.push_back(appender);
    }
    void Logger::delAppender(LogAppender::ptr appender){
        for(auto it = m_appenders.begin();
                it != m_appenders.end(); ++it)
                {
                    if(*it == appender)
                    {
                        m_appenders.erase(it);
                        break;
                    }
                }
    }
    void Logger::log(LogEvent::ptr event){
        if(event->getLevel() >= m_level){
            for(auto& i : m_appenders){
                i->log(event);
            }
        }
    }

    void Logger::debug(LogEvent::ptr event){
        log(event);
    }
    void Logger::info(LogEvent::ptr event){
        log(event);
    }
    void Logger::warn(LogEvent::ptr event){
        log(event);
    }
    void Logger::error(LogEvent::ptr event){
        log(event);
    }
    void Logger::fatal(LogEvent::ptr event){
        log(event);
    }

    FileoutLogAppender::FileoutLogAppender(const std::string& filename)
        :m_filename(filename){

    }

    bool FileoutLogAppender::reopen(){
        if(m_filestream){
            m_filestream.close();
        }
        m_filestream.open(m_filename);
        return !!m_filestream;
    }

    void FileoutLogAppender::log(LogEvent::ptr event){
        std::cout << "输出到文件" << m_filename << std::endl;
    }
    
    void StdoutLogAppender::log(LogEvent::ptr event){
        //format time
        const std::string format = "%Y-%m-%d %H:%M:%S";
        struct tm tm;
        time_t t = event->getTime();
        localtime_r(&t, &tm);
        char tm_buf[64];
        strftime(tm_buf, sizeof(tm_buf), format.c_str(), &tm); 

        std::cout
            << "time:" << event->getTime() << " "
            << "threadId:" << event->getThreadId() << " "
            << "fiberId:" << event->getFiberId() << " "
            << "["
            << LogLevel::ToString(event->getLevel())
            << "] "
            << "["
            << event->getLogName()
            << "] "
            << event->getFile() << ":" << event->getLine() << " "
            //<< "输出到控制台的信息" << " "
            << event->getContent()
            << std::endl;
    }
    
    LogFormatter::LogFormatter(const std::string& pattern)
        :m_pattern(pattern){
            init();
    }
    std::string LogFormatter::format(LogEvent::ptr event){
        std::stringstream ss;
        for(auto& i : m_items) {
            i->format(ss,event);
        }
        return ss.str();
    }

    // %d{%Y-%m-%d %H:%M:%S}%T%t%T%F%T[%p]%T[%c]%T%f%l%T%m%n
    void LogFormatter::init(){
        // string, format, type
        std::vector<std::tuple<std::string, std::string, int> > vec;
        std::string nstr;
        for(size_t i = 0; i < m_pattern.size(); ++i)
        {
            if(m_pattern[i] != '%'){
                nstr.append(1, m_pattern[i]);
                continue;
            }
            if((i + 1)< m_pattern.size() && m_pattern[i + 1] == '%'){
                nstr.append(1, '%');    // nstr后面添加一个'%'
                continue;
            }

            size_t n = i + 1;
            int fmt_status = 0;
            size_t fmt_begin = 0;

            std::string str;
            std::string fmt;
            while(n < m_pattern.size())
            {
                if(!fmt_status && (!isspace(m_pattern[n]) && !isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}')){
                    str = m_pattern.substr(i + 1, n - i - 1);
                    break;
                }
                if(fmt_status == 0){
                    if(m_pattern[n] == '{'){
                        str = m_pattern.substr(i + 1, n - i - 1);
                        fmt_status = 1;
                        fmt_begin = n;
                        ++n;
                        continue;
                    }
                }
                if(fmt_status == 1){
                    if(m_pattern[n] == '}'){
                        fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                        fmt_status = 2;
                        break;
                    }
                }
                ++n;
                if(n == m_pattern.size()) {
                    if(str.empty()) {
                        str = m_pattern.substr(i + 1);
                    }
                }
            }

            if(fmt_status == 0){
                if(!nstr.empty()){
                    vec.push_back(std::make_tuple(nstr, std::string(), 0));
                    nstr.clear();
                }
                str = m_pattern.substr(i + 1, n - i - 1);
                vec.push_back(std::make_tuple(str, fmt, 1));
                i = n;
            }else if(fmt_status == 1){
                std::cout << "pattern parse error:" << m_pattern << " - " << m_pattern.substr(i) << std::endl;
                vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
            }else if(fmt_status == 2){
                if(!nstr.empty()){
                    vec.push_back(std::make_tuple(nstr,"",0));
                    nstr.clear();
                }
                vec.push_back(std::make_tuple(str, fmt, 1));
                i = n;
            }
        }

        if(!nstr.empty()){
            vec.push_back(std::make_tuple(nstr, "", 0));
        }

        for(auto& it : vec) {
        std::cout 
            << std::get<0>(it) 
            << " : " << std::get<1>(it) 
            << " : " << std::get<2>(it)
            << std::endl;
    }

    static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)> > s_format_items = {
#define XX(str, C) \
        {#str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt));}}

        XX(m, MessageFormatItem),
        XX(p, LevelFormatItem),
        XX(r, ElapseFormatItem),
        XX(c, NameFormatItem),
        XX(t, ThreadIdFormatItem),
        XX(n, NewLineFormatItem),
        XX(d, DateTimeFormatItem),
        XX(f, FilenameFormatItem),
        XX(l, LineFormatItem),
        XX(T, TabFormatItem),
        XX(F, FiberIdFormatItem),
#undef XX
    };

    for(auto& i : vec) {
        if(std::get<2>(i) == 0) {
            m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if(it == s_format_items.end()) {
                m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
            } else {
                m_items.push_back(it->second(std::get<1>(i)));
                }
            }
        }
    }
    LogEvent::LogEvent(const std::string& logName, LogLevel::Level level
                ,const char* file, int32_t line, uint32_t elapse
                , uint32_t thread_id, uint32_t fiber_id, uint64_t time){
                    m_logName = logName;
                    m_level = level;    m_file = file;
                    m_line = line;  m_elapse = elapse;
                    m_threadId = thread_id; m_fiberId = fiber_id;
                    m_time = time;
    }

    LogEventWrap::LogEventWrap(Logger::ptr logger, LogEvent::ptr e)
    : m_logger(logger), m_event(e) {
    }

    LogEventWrap::~LogEventWrap() { 
        m_logger->log( m_event); 
    }

    std::stringstream &LogEventWrap::getSS() { return m_event->getSS(); }

    LoggerManager::LoggerManager() {
        m_root.reset(new Logger);
        m_root->addAppender(LogAppender::ptr(new StdoutLogAppender));
    }

    Logger::ptr LoggerManager::getLogger(const std::string& name) {
        auto it = m_loggers.find(name);
        return it == m_loggers.end() ? m_root : it->second;
    }
}
#include "log.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <time.h>
#include "config.h"
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
        return "UNKNOWN";
    }
    return "UNKNOWN";
}
LogLevel::Level LogLevel::FromString(const std::string& str){
#define XX(level, v) \
    if(str == #v){ \
        return LogLevel::level; \
    } 
    XX(DEBUG, debug);
    XX(INFO, info);
    XX(WARN, warn);
    XX(ERROR, error);
    XX(FATAL, fatal);

    XX(DEBUG, DEBUG);
    XX(INFO, INFO);
    XX(WARN, WARN);
    XX(ERROR, ERROR);
    XX(FATAL, FATAL);

    return LogLevel::UNKNOWN;
}
#undef XX

Logger::Logger(const std::string& name)
    :m_name(name)
    ,m_level(LogLevel::DEBUG){

    m_formatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));

    // if(name == "root"){
    //     m_appenders.push_back(StdoutLogAppender::ptr(new StdoutLogAppender));
    // }
}
void Logger::setFormatter(LogFormatter::ptr val){
    MutexType::Lock lock(m_mutex);
    m_formatter = val;

    for(auto& i : m_appenders){
        MutexType::Lock ll(i->m_mutex);
        if(!i->m_hasFormatter){
            i->m_formatter = m_formatter; 
        }
    }
}

void Logger::setFormatter(const std::string& val){
    sylar::LogFormatter::ptr new_val(new sylar::LogFormatter(val));
    if(new_val->isError()){
        std::cout << "Logger setFormatter name=" << m_name
                  << "value=" << val << "invalid formatter"
                  << std::endl;
        return;
    }
    m_formatter.reset(new sylar::LogFormatter(val));
}

LogFormatter::ptr Logger::getFormatter(){
    MutexType::Lock lock(m_mutex);
    return m_formatter;
}

std::string Logger::toYamlString() {
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    node["name"] = m_name;
    if(m_level != LogLevel::UNKNOWN) {
        node["level"] = LogLevel::ToString(m_level);
    }
    if(m_formatter){
        node["formatter"] = m_formatter->getPattern();
    }
    for(auto& i : m_appenders){
        node["appenders"].push_back(YAML::Load(i->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

void Logger::addAppender(LogAppender::ptr appender){
    MutexType::Lock lock(m_mutex);
    if(!appender->getFormatter()){
        MutexType::Lock ll(appender->m_mutex);
        appender->m_formatter = m_formatter;
        // appender->setFormatter(m_formatter);
    }
    m_appenders.push_back(appender);
}
void Logger::delAppender(LogAppender::ptr appender){
    MutexType::Lock lock(m_mutex);
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

void Logger::clearAppender(){
    MutexType::Lock lock(m_mutex);
    m_appenders.clear();
}
void Logger::log(LogEvent::ptr event){
    if(event->getLevel() >= m_level){
        MutexType::Lock lock(m_mutex);
        if(!m_appenders.empty()){
            for(auto& i : m_appenders){
                i->log(event);
            }
        } else if(m_root){
            m_root->log(event);
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

void LogAppender::setFormatter(LogFormatter::ptr val){
    MutexType::Lock lock(m_mutex);
    m_formatter = val;
    if(m_formatter){
        m_hasFormatter = true;
    } else {
        m_hasFormatter = false;
    }
}


LogFormatter::ptr LogAppender::getFormatter(){
    MutexType::Lock lock(m_mutex);
    return m_formatter;
}
FileoutLogAppender::FileoutLogAppender(const std::string& filename)
    :m_filename(filename){
        reopen();
}

std::string FileoutLogAppender::toYamlString() {
    YAML::Node node;
    node["type"] = "FileoutLogAppender";
    node["file"] = m_filename;
    if(m_level != LogLevel::UNKNOWN){
        node["level"] = LogLevel::ToString(m_level);
    }
    
    if (m_hasFormatter && m_formatter) {
        node["formatter"] = m_formatter->getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

bool FileoutLogAppender::reopen(){
    MutexType::Lock lock(m_mutex);
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

std::string StdoutLogAppender::toYamlString() {
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    node["type"] = "StdoutLogAppender";
    if(m_level != LogLevel::UNKNOWN) {
        node["level"] = LogLevel::ToString(m_level);
    }
    if (m_hasFormatter && m_formatter) {
        node["formatter"] = m_formatter->getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
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
            m_error = true;
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

//     for(auto& it : vec) {
//     std::cout 
//         << std::get<0>(it) 
//         << " : " << std::get<1>(it) 
//         << " : " << std::get<2>(it)
//         << std::endl;
//      }

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
            m_error = true;
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
    m_logger->log(m_event); 
}

std::stringstream &LogEventWrap::getSS() { return m_event->getSS(); }

LoggerManager::LoggerManager() {
    m_root.reset(new Logger);
    m_root->addAppender(LogAppender::ptr(new StdoutLogAppender));
    m_loggers[m_root->m_name] = m_root;
    init();
}

Logger::ptr LoggerManager::getLogger(const std::string& name) {
    MutexType::Lock lock(m_mutex);
    auto it = m_loggers.find(name);
    if(it != m_loggers.end()){
        return it->second;
    }
    Logger::ptr logger(new Logger(name));
    logger->m_root = m_root;
    m_loggers[name] = logger;
    return logger;
    // return it == m_loggers.end() ? m_root : it->second;
}

struct LogAppenderDefine{
    int type = 0;   // 1 - Fileout, 2 - Stdout
    LogLevel::Level level = LogLevel::UNKNOWN;
    std::string formatter;
    std::string file;
    
    bool operator==(const LogAppenderDefine& oth) const{
        return type == oth.type
            && level == oth.level
            && formatter == oth.formatter
            && file == oth.file;
    }
};

struct LogDefine{
    std::string name;
    LogLevel::Level level = LogLevel::UNKNOWN;
    std::string formatter
    ;
    std::vector<LogAppenderDefine> appenders;

    bool operator==(const LogDefine& oth) const { 
        return name == oth.name
            && level == oth.level
            && formatter == oth.formatter
            && appenders == oth.appenders;
    }
    
    bool operator<(const LogDefine& oth) const {
        return name < oth.name;
    }
};

template<>
class LexicalCast<std::string, std::set<LogDefine> >{
public:
    std::set<LogDefine> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        std::set<LogDefine> vec;
        
        for(size_t i = 0; i < node.size(); ++i){
            auto n = node[i];
            if(!n["name"].IsDefined()){
                std::cout << "log config error: name is null, " << n
                          << std::endl;
                continue;
            }
            LogDefine ld;
            ld.name = n["name"].as<std::string>();
            ld.level = LogLevel::FromString(n["level"].IsDefined() ? n["level"].as<std::string>() : "");
            if(n["formatter"].IsDefined()){
                ld.formatter = n["formatter"].as<std::string>();
            }   
            if(n["appenders"].IsDefined()){
                for(size_t x = 0; x < n["appenders"].size(); ++x){
                    auto a = n["appenders"][x];
                    if(!a["type"].IsDefined()){
                        std::cout << "log config error: appender type is null, " << a
                          << std::endl;
                        continue;
                    }
                    std::string type = a["type"].as<std::string>();
                    LogAppenderDefine lad;
                    if(type == "FileoutLogAppender"){
                        lad.type = 1;
                        if(!a["file"].IsDefined()){
                            std::cout << "log config error: fileappender type is invalid, " << a
                                  << std::endl;
                            continue;
                        }
                        lad.file = a["file"].as<std::string> ();
                        if(a["formatter"].IsDefined()){
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    } else if (type == "StdoutLogAppender") {
                        lad.type = 2;
                        if(a["formatter"].IsDefined()) {
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    } else {
                        std::cout << "log config error: appender type is invalid, " << a
                                  << std::endl;
                        continue;
                    }
                    ld.appenders.push_back(lad);
                }
            }
            // std::cout << "---" << ld.name << " - "
            //           << ld.appenders.size() << std::endl;
            vec.insert(ld);
        }
        return vec;
    }
};

template<>
class LexicalCast<std::set<LogDefine>, std::string>{
public:
    std::string operator() (const std::set<LogDefine>& v){
        YAML::Node node;
        for(auto& i : v){
            YAML::Node n;
            n["name"] = i.name;
            if(i.level == LogLevel::UNKNOWN){
                n["level"] = LogLevel::ToString(i.level);
            }
            n["level"] = LogLevel::ToString(i.level);
            if(i.formatter.empty()){
                n["level"] = i.formatter;
            }

            for(auto& a : i.appenders){
                YAML::Node na;
                if(a.type == 1){
                    na["type"] = "FileoutLogAppener";
                    na["file"] = a.file;
                }else if(a.type == 2){
                    na["type"] = "StdoutLogAppender";
                }
                if(a.level != LogLevel::UNKNOWN){
                    na["level"] = LogLevel::ToString(a.level);
                }
                if(a.formatter.empty()){
                    na["formatter"] = a.formatter;
                }
                n["appenders"].push_back(na);
            }
            node.push_back(n);
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

sylar::ConfigVar<std::set<LogDefine> >::ptr g_log_defines =
    sylar::Config::Lookup("logs", std::set<LogDefine>(), "logs config");

struct LogIniter{
    LogIniter(){
        g_log_defines->addListener(0xF1E231, [](const std::set<LogDefine>& old_value,
                                        const std::set<LogDefine>& new_value){
            // add
            LOG_INFO(SYLAR_LOG_ROOT()) << "on_logger_conf_changed";
            for(auto& i : new_value){
                auto it = old_value.find(i);
                sylar::Logger::ptr logger;
                if(it == old_value.end()){
                    // add logger
                    logger = SYLAR_LOG_NAME(i.name);
                } else {
                    if(!(i == *it)){
                        // revise logger
                        logger = SYLAR_LOG_NAME(i.name);
                        } else {
                            continue;
                        }
                }

                logger->setLevel(i.level);
                if(!i.formatter.empty()){
                    logger->setFormatter(i.formatter);
                }
                logger->clearAppender();
                for(auto& a : i.appenders){
                    sylar::LogAppender::ptr ap;
                    if(a.type == 1){
                        ap.reset(new FileoutLogAppender(a.file));
                    } else if(a.type == 2){
                        ap.reset(new StdoutLogAppender);
                    }
                    ap->setLevel(a.level);
                    if(!a.formatter.empty()){
                        LogFormatter::ptr fmt(new LogFormatter
                                            (a.formatter));
                        if(!fmt->isError()){
                            ap->setFormatter(fmt);
                        } else{
                            std::cout << "log.name = " << i.name << "append type = " << a.type
                                      << " formatter = " << a.formatter
                                      << " is invalid" << std::endl;
                        }
                    }
                    logger->addAppender(ap);
                }
            }

            for(auto& i : old_value){
                auto it = new_value.find(i);
                if(it == new_value.end()){
                    // del logger
                    auto logger = SYLAR_LOG_NAME(i.name);
                    logger->setLevel((LogLevel::Level)100);
                    logger->clearAppender();
                }
            }

        });
    }
};

static LogIniter __log_init;

std::string LoggerManager::toYamlString() {
    MutexType::Lock lock(m_mutex);
    YAML::Node node;
    for(auto& i : m_loggers) {
        node.push_back(YAML::Load(i.second->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

void LoggerManager::init(){
    
}
}
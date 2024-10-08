#ifndef __SYLAR_CONFIG_H__
#define __SYLAR_CONFIG_H__

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "log.h"

namespace sylar{

class ConfigVarBase{
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string& name, const std::string& description = "")
        : m_name(name)
        , m_description(description){
            std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);
        }
        virtual ~ConfigVarBase(){}  //有具体类型的子类，所以要变成虚析构
        const std::string& getName() const {return m_name;}
        const std::string& getDescription() const {return m_description;}

        virtual std::string toString() = 0;
        virtual bool fromString(const std::string& val) = 0;
        virtual std::string getTypeName() const = 0;
protected:
    std::string m_name;
    std::string m_description;
};

// F = from_type; T = to_type
// 没有boost了，先定义基础类型的解析
template<class F, class T>
class LexicalCast{
public:
    T operator()(const F& v){
        return boost::lexical_cast<T>(v);
    }
};

//vector
template<class T>
class LexicalCast<std::string, std::vector<T> >{
public:
    std::vector<T> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::vector<T> vec;
        std::stringstream ss;
        for(size_t i = 0; i < node.size(); ++i){
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, T> ()(ss.str()));
        }
        return vec;
    }
};

template<class T>
class LexicalCast<std::vector<T>, std::string>{
public:
    std::string operator() (const std::vector<T>& v){
        YAML::Node node;
        for(auto& i : v){
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//list
template<class T>
class LexicalCast<std::string, std::list<T> >{
public:
    std::list<T> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::list<T> vec;
        std::stringstream ss;
        for(size_t i = 0; i < node.size(); ++i){
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, T> ()(ss.str()));
        }
        return vec;
    }
};

template<class T>
class LexicalCast<std::list<T>, std::string>{
public:
    std::string operator() (const std::list<T>& v){
        YAML::Node node;
        for(auto& i : v){
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//set
template<class T>
class LexicalCast<std::string, std::set<T> >{
public:
    std::set<T> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::set<T> vec;
        std::stringstream ss;
        for(size_t i = 0; i < node.size(); ++i){
            ss.str("");
            ss << node[i];
            vec.insert(LexicalCast<std::string, T> ()(ss.str()));
        }
        return vec;
    }
};

template<class T>
class LexicalCast<std::set<T>, std::string>{
public:
    std::string operator() (const std::set<T>& v){
        YAML::Node node;
        for(auto& i : v){
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//unordered_set
template<class T>
class LexicalCast<std::string, std::unordered_set<T> >{
public:
    std::unordered_set<T> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::unordered_set<T> vec;
        std::stringstream ss;
        for(size_t i = 0; i < node.size(); ++i){
            ss.str("");
            ss << node[i];
            vec.insert(LexicalCast<std::string, T> ()(ss.str()));
        }
        return vec;
    }
};

template<class T>
class LexicalCast<std::unordered_set<T>, std::string>{
public:
    std::string operator() (const std::unordered_set<T>& v){
        YAML::Node node;
        for(auto& i : v){
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//map
template<class T>
class LexicalCast<std::string, std::map<std::string, T> >{
public:
    std::map<std::string, T> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::map<std::string, T> vec;
        std::stringstream ss;
        for(auto it = node.begin();
            it != node.end(); ++it){
            ss.str("");
            ss << it->second;
            vec.insert(std::make_pair(it->first.Scalar(),
                        LexicalCast<std::string, T> ()(ss.str())));
        }
        return vec;
    }
};

template<class T>
class LexicalCast<std::map<std::string, T>, std::string>{
public:
    std::string operator() (const std::map<std::string, T>& v){
        YAML::Node node;
        for(auto& i : v){
            node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//unordered_map
template<class T>
class LexicalCast<std::string, std::unordered_map<std::string, T> >{
public:
    std::unordered_map<std::string, T> operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        typename std::unordered_map<std::string, T> vec;
        std::stringstream ss;
        for(auto it = node.begin();
            it != node.end(); ++it){
            ss.str("");
            ss << it->second;
            vec.insert(std::make_pair(it->first.Scalar(),
                        LexicalCast<std::string, T> ()(ss.str())));
        }
        return vec;
    }
};

template<class T>
class LexicalCast<std::unordered_map<std::string, T>, std::string>{
public:
    std::string operator() (const std::unordered_map<std::string, T>& v){
        YAML::Node node;
        for(auto& i : v){
            node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

//复杂类型比如我的配置是一个vector或者map，或者自定义的struct，不能直接从字符串转换
//FromStr T operator() (const std::string&)
//ToStr std::string operator() (const T&)
//template形参2个，class形参0个——泛化
template<class T, class FromStr = LexicalCast<std::string, T>, class ToStr = LexicalCast<T, std::string> >
class ConfigVar : public ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVar> ptr;

    ConfigVar(const std::string& name, 
              const T& default_value, 
              const std::string& description = "")
            :ConfigVarBase(name, description)
            , m_val(default_value){

            }

    // 以下两个函数替换ConfigVar中对应toString() 和 fromString() 写死的部分       
    // 也就是不仅仅支持string类型转化 
    std::string toString() override{
        try{
            //return boost::lexical_cast<std::string>(m_val);
            return ToStr() (m_val);
        }catch (std::exception& e){
            LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
            << e.what() << " convert: " << typeid(m_val).name() << " to string";
        }
        return "";
    }

    bool fromString(const std::string& val) override{
        try{
            //m_val = boost::lexical_cast<T>(val);
            setValue(FromStr()(val));
        }catch (std::exception& e){
            LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception"
            << e.what() << " convert: string to " << typeid(m_val).name();
        }
        return false;
    }    
    
    const T getValue() const {return m_val;}
    void setValue(const T& v) {m_val = v;}
    std::string getTypeName() const override { return typeid(T).name();}
private:
    T m_val;    //m_name + m_val + m_description
};

//configvar这两个模板函数的泛化
class Config{
public:
    typedef std::unordered_map<std::string, ConfigVarBase::ptr> ConfigVarMap;
    
    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name,
                    const T& default_value, const std::string& description = ""){
                // 类型转换报错处理
                auto it = s_datas.find(name);
                if(it != s_datas.end()){
                    auto tmp = std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
                    if(tmp){
                        LOG_INFO(SYLAR_LOG_ROOT()) << "Lookup name = " << name << "exists";  //root()返回一个logger::ptr, 第二个参数为level
                        return tmp;
                    } else{
                        LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name = " << name << "exists but type not "
                                                    <<  typeid(T).name() << "real_type = " << it->second->getTypeName()
                                                    << " " << it->second->toString();
                        return nullptr;
                    }
                }

                //报错原因少打了一个u
                if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789")
                        != std::string::npos){
                            LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name invalid " << name;
                            throw std::invalid_argument(name);
                        }
                        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
                        s_datas[name] = v;
                        return v;
                }

    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name){
        auto it = s_datas.find(name);
        if(it == s_datas.end()){
            return nullptr;
        }  
        return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
    }

    static void LoadFromYaml(const YAML::Node& root);

    static ConfigVarBase::ptr LookupBase(const std::string& name);
private:
    static ConfigVarMap s_datas;
};

}

#endif
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include "../sylar/config.h"
#include "../sylar/log.h"

// Lookup里的name对应yaml里的node名, 用','分割
sylar::ConfigVar<int>::ptr g_int_value_config = 
    sylar::Config::Lookup("system.port", (int)8080, "system port");

// sylar::ConfigVar<float>::ptr g_int_valuex_config = 
//     sylar::Config::Lookup("system.port", (float)8080, "system port");

sylar::ConfigVar<float>::ptr g_float_value_config = 
    sylar::Config::Lookup("system.value", (float)12.34, "system value");

//泛化了Lookup的s_datas参数, 找一下在Config里
sylar::ConfigVar<std::vector<int> >::ptr g_int_vec_config = 
    sylar::Config::Lookup("system.int_vec", std::vector<int>{1, 2}, "system int vec");
//list
sylar::ConfigVar<std::list<int> >::ptr g_int_list_config = 
    sylar::Config::Lookup("system.int_list", std::list<int>{3, 4}, "system int list");
//set
sylar::ConfigVar<std::set<int> >::ptr g_int_set_config = 
    sylar::Config::Lookup("system.int_set", std::set<int>{5, 6}, "system int set");
//unordered_set
sylar::ConfigVar<std::unordered_set<int> >::ptr g_int_uset_config = 
    sylar::Config::Lookup("system.int_uset", std::unordered_set<int>{5, 6}, "system int uset");
//map
sylar::ConfigVar<std::map<std::string, int> >::ptr g_str_int_map_config = 
    sylar::Config::Lookup("system.str_int_map", std::map<std::string, int>{{"yyc1", 5}, {"yyc2", 6}}, "system str_int map");
//unordered_map
sylar::ConfigVar<std::unordered_map<std::string, int> >::ptr g_str_int_umap_config = 
    sylar::Config::Lookup("system.str_int_umap", std::unordered_map<std::string, int>{{"yyc1", 5}, {"yyc2", 6}}, "system str_int umap");


//function
void print_yaml(const YAML::Node& node, int level){
    if(node.IsScalar()){
        LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ') 
            << node.Scalar() << " - " << node.Type() << " - " << level;
    } else if(node.IsNull()){
        LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()){
        for(auto it = node.begin(); it != node.end(); ++it){    //map类型的yaml这样遍历
            LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()){
        for(size_t i = 0; i < node.size(); ++i){
            LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level * 4, ' ')
            << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}
void test_yaml(){
    YAML::Node root = YAML::LoadFile("../bin/conf/log.yml");   //导入yaml文件为一个node
    print_yaml(root, 0);
    
    //LOG_INFO(SYLAR_LOG_ROOT()) << root;
}

void test_config(){
    //sylar::Logger::ptr lg(new sylar::Logger("yyc"));
    //如果不用单例宏SYLAR_LOG_ROOT()的话, 就要声明定义lg, 然后一个个把Appender加进去
    LOG_INFO(SYLAR_LOG_ROOT()) << "before int_value: " << g_int_value_config->getValue();
    LOG_INFO(SYLAR_LOG_ROOT()) << "before float_value: " << g_float_value_config->toString();   //return toStr()(m_val)
    //auto v = g_int_vec/list..._config->getValue();
#define XX(g_var, name, prefix) \
    { \
        auto v = g_var->getValue(); \
        for(auto& i : v){ \
            LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name ": " << i; \
        } \
        LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
    }

#define XX_M(g_var, name, prefix) \
    { \
        auto v = g_var->getValue(); \
        for(auto& i : v){ \
            LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name ": {" \
            << i.first << " - " << i.second << "}"; \
        } \
        LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " yml: " << g_var->toString(); \
    }
    XX(g_int_vec_config, int_vec, before);
    XX(g_int_list_config, int_list, before);
    XX(g_int_set_config, int_set, before);
    XX(g_int_uset_config, int_uset, before);
    XX_M(g_str_int_map_config, str_int_map, before);
    XX_M(g_str_int_umap_config, str_int_umap, before);

    // import yaml
    YAML::Node root = YAML::LoadFile("../bin/conf/log.yml");
    sylar::Config::LoadFromYaml(root);
    std::cout << "import yaml nodes" << std::endl;
    LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
    LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_float_value_config->toString();
    
    XX(g_int_vec_config, int_vec, after);
    XX(g_int_list_config, int_list, after);
    XX(g_int_set_config, int_set, after);
    XX(g_int_uset_config, int_uset, after);
    XX_M(g_str_int_map_config, str_int_map, after);    // map在yaml里的写法需要注意
    XX_M(g_str_int_umap_config, str_int_umap, after);
}
class Person{
public:
    Person(){};
    std::string m_name;
    int m_age = 0;
    bool m_sex = 0;

    std::string toString() const{
        std::stringstream ss;
        ss << "[Person name = " << m_name
           << " age = " << m_age
           << " sex = " << m_sex
           << "]";
        return ss.str();
    }
    bool operator==(const Person& oth) const{
        return m_name == oth.m_name
            && m_age == oth.m_age
            && m_sex == oth.m_sex;
    }
};

namespace sylar{
// 给Person模板类全特化
template<>
class LexicalCast<std::string, Person> {
public:
    Person operator() (const std::string& v){
        YAML::Node node = YAML::Load(v);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};

template<>
class LexicalCast<Person, std::string>{
public:
    std::string operator() (const Person& p){
        YAML::Node node;
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};


}

sylar::ConfigVar<Person>::ptr g_person = 
    sylar::Config::Lookup("class.person", Person(), "system person");

// map + Person
sylar::ConfigVar<std::map<std::string, Person> >::ptr g_person_map = 
    sylar::Config::Lookup("class.map", std::map<std::string, Person>(), "system map_person");

// map + vector<Person>
sylar::ConfigVar<std::map<std::string, std::vector<Person> > >::ptr g_person_vector_map = 
    sylar::Config::Lookup("class.vec_map", std::map<std::string, std::vector<Person> >(), "system map_vector_person");


void test_class(){
    LOG_INFO(SYLAR_LOG_ROOT()) << "before yaml: " << g_person->getValue().toString()
                               << " - " << g_person->toString();
#define XX_PM(g_var, prefix) \
    { \
        auto m = g_person_map->getValue(); \
        for(auto& i : m){ \
            LOG_INFO(SYLAR_LOG_ROOT()) << prefix << " : " << i.first  << " - " << i.second.toString(); \
        } \
        LOG_INFO(SYLAR_LOG_ROOT()) << prefix << ": size = " << m.size(); \
    }

    // 回调函数会在LoadFromYaml下一步执行, 因为配置内容变更了
    // lambda表达式拿回调函数作为参数
    g_person->addListener(10, [](const Person& old_value, const Person& new_value){
        LOG_INFO(SYLAR_LOG_ROOT()) << "old_value = " << old_value.toString()
                                   << "new_value = " << new_value.toString();
    });

    XX_PM(g_person_map, "class.map before");
    LOG_INFO(SYLAR_LOG_ROOT()) << "before yaml: " << g_person_vector_map->toString();

    YAML::Node root = YAML::LoadFile("../bin/conf/test.yml");
    sylar::Config::LoadFromYaml(root);
    
    //person
    LOG_INFO(SYLAR_LOG_ROOT()) << "after yaml: " << g_person->getValue().toString()
                               << " - " << g_person->toString();
    //map_person
    XX_PM(g_person_map, "class.map after yaml");
    //map_vector_person
    LOG_INFO(SYLAR_LOG_ROOT()) << "after yaml : " << g_person_vector_map->toString();
}

void test_log() {
    static sylar::Logger::ptr system_log = SYLAR_LOG_NAME("system");
    LOG_INFO(system_log) << "hello system" << std::endl;
    std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;
    YAML::Node root = YAML::LoadFile("../bin/conf/test.yml");
    sylar::Config::LoadFromYaml(root);
    std::cout << "==================" << std::endl;
    std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << root << std::endl;

    system_log->setFormatter("%d - %m%n");
    LOG_INFO(system_log) << "hello system" << std::endl;
}
int main(int argc,char** argv){
    
    //test_yaml();
    //test_config();
    //test_class();
    test_log();
    return 0;
}

// int main(int argc,char** argv){
// 	YAML::Node node = YAML::LoadFile("../bin/conf/test.yaml");
// 	std::cout << node["name"].as<std::string>() << std::endl;
//     std::cout << node["sex"].as<std::string>() << std::endl;
//     std::cout << node["age"].as<int>() << std::endl;//18
//     std::cout << node["system"]["port"].as<std::string>() << std::endl;
//     std::cout << node["system"]["value"].as<std::string>() << std::endl;
//     for(auto it = node["system"]["int_vec"].begin(); it != node["system"]["int_vec"].end(); ++it){
// 		std::cout << *it <<" ";
// 	}
// 	std::cout << std::endl;
// 	return 0;
// }

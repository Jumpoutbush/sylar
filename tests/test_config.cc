#include <yaml-cpp/yaml.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include "../sylar/config.h"
#include "../sylar/log.h"

sylar::ConfigVar<int>::ptr g_int_value_config = 
    sylar::Config::Lookup("system.port", (int)8080, "system port");

sylar::ConfigVar<float>::ptr g_float_value_config = 
    sylar::Config::Lookup("system.value", (float)12.34f, "system value");

sylar::ConfigVar<std::vector<int> >::ptr g_int_vec_config = 
    sylar::Config::Lookup("system.int_vec", std::vector<int>{1, 2}, "system int vec");

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
    YAML::Node root = YAML::LoadFile("../bin/conf/log.yaml");   //导入yaml文件为一个node
    print_yaml(root, 0);
    
    //LOG_INFO(SYLAR_LOG_ROOT()) << root;
}
int main(int argc,char** argv){
    //sylar::Logger::ptr lg(new sylar::Logger("yyc"));
    //如果不用单例宏SYLAR_LOG_ROOT()的话, 就要声明定义lg, 然后一个个把Appender加进去
    
    LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
    LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_float_value_config->toString();
    auto v = g_int_vec_config->getValue();
    for(auto& i : v){
        LOG_INFO(SYLAR_LOG_ROOT()) << "before int_vec: " << i;
    }

    YAML::Node root = YAML::LoadFile("../bin/conf/log.yml");
    sylar::Config::LoadFromYaml(root);

    LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
    LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_float_value_config->toString();
    
    v = g_int_vec_config->getValue();
    for(auto& i : v){
        LOG_INFO(SYLAR_LOG_ROOT()) << "after int_vec: " << i;
    }
    //test_yaml();
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

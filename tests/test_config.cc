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
    sylar::Config::Lookup("system.value", (float)10.2f, "system value");

void test_yaml(){
    YAML::Node root = YAML::LoadFile("../bin/conf/log.yaml");
    LOG_INFO(SYLAR_LOG_ROOT()) << root;
}
int main(int argc,char** argv){
    std::cout << "already compiled successfully!" << std::endl;
    //sylar::Logger::ptr lg(new sylar::Logger("yyc"));
    //如果不用单例宏SYLAR_LOG_ROOT()的话, 就要声明定义lg, 然后一个个把Appender加进去
    
    LOG_LEVEL(SYLAR_LOG_ROOT(), sylar::LogLevel::INFO) << g_int_value_config->getValue();
    LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->toString();
    
    //LOG_INFO(SYLAR_LOG_ROOT()) << g_float_value_config->getValue();
    test_yaml();
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

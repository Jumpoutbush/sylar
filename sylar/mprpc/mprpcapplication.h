#pragma once
#include "../log.h"
#include "../config.h"
#include "../singleton.h"

namespace sylar
{
//mprpc框架的基础类，负责框架的一些初始化操作，使用单例模式设计
class MprpcApplication : public Singleton<MprpcApplication>
{
    friend class Singleton<MprpcApplication>;
public:
    static void Init(int argc,char **argv);
    static MprpcApplication& GetInstance();
private:
    MprpcApplication(){};
    MprpcApplication(const MprpcApplication&)=delete;
    MprpcApplication(MprpcApplication&&)=delete;
};

}
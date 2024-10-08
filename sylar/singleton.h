#ifndef __SYLAR_SINGLETON_H__
#define __SYLAR_SINGLETON_H__
namespace sylar{
    //X 为了创造多个实例对应的Tag
    //N 同一个Tag创造多个实例索引
    template<class T, class X = void, int N = 0>
    class Singleton {
    public:
        static T* GetInstance() {
            static T v;  // 这步为什么会知道去找LoggerManager的: [log.h]typedef sylar::Singleton<LoggerManager>
                         // T为需要被单例化的类, 即LoggerManager
            return &v;
        }
    };

    template<class T, class X = void, int N = 0>
    class SingletonPtr {
    public:
        static std::shared_ptr<T> GetInstance() {
            static std::shared_ptr<T> v(new T);
            return v;
        }
    };
    
}
#endif
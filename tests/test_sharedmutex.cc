#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex rw_mutex; // 共享互斥锁
int shared_data = 0;

// 读操作函数
void reader(int id) {
    std::shared_lock<std::shared_mutex> lock(rw_mutex); // shared_lock 共享锁
    std::cout << "Reader " << id << " reads data: " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// 写操作函数
void writer(int id) {
    std::unique_lock<std::shared_mutex> lock(rw_mutex); // unique_lock 互斥锁
    ++shared_data;
    std::cout << "Writer " << id << " writes data: " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

int main() {
    std::vector<std::thread> threads;

    // 创建多个读线程
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(reader, i);
    }

    // 创建多个写线程
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(writer, i);
    }

    // 等待所有线程完成
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
#pragma once
#include <iostream>
#include <filesystem>
#include <CommonDef.h>
extern int testOptioal();



// 复制目录及其内容
void copyDirectory(const std::filesystem::path& source, const std::filesystem::path& destination);
// 删除目录及其内容

void clearDirectory(const std::filesystem::path& dir);

void createDirectory(const std::filesystem::path& path);

// extern void quit_command();
// extern void help_command();


#pragma once

#include <functional>
#include <vector>

template <typename... Args>
class C_Signal
{
    using CALLBACK_TYPE = std::function<void(Args...)>;
public:
    void Connect(std::function<void(Args...)> callback)
    {
        regfunction = callback;
    }

    template <class Self, class MemFun>
    void Connect(Self* self, MemFun fun)
    {
       regfunction=  [self,fun](Args... args)
        {
            (self->*fun)(std::forward<Args>(args)...);
        };
    }
    void Emit(Args... args) 
    {
        if (regfunction)
        {  // 检查是否已注册回调
            regfunction(args...);
        } 
        else 
        {
            std::cerr << "Error: No callback connected!\n";
        }
    }
private:
    CALLBACK_TYPE regfunction;
};


//测试例子
// C_Signal<int, std::string> temp;
// temp.Connect([](int a, string b){
//     std::cout << "emit signal : " << a << ", " << b << std::endl;
// });
// temp.Emit(10, "test");


// template <typename... Args>
// class Signal {
//  public:
//   void Connect(std::function<void(Args...)> callback) {
//     //
//     m_callBacks.push_back(std::move(callback));
//   }
//   template <class Self, class MemFun>
//   void Connect(Self* self, MemFun fun) {
//     m_callBacks.push_back(bind(self, fun));
//   }
//   void Emit(Args... args) {
//     for (auto&& callback : m_callBacks) {
//       callback(args...);
//     }
//   }

//  private:
//   template <class Self, class MemFun>
//   auto bind(Self* self, MemFun memfn) 
//   {
//     return [self, memfn](auto... args) {  // define 形参包
//       (self->*memfn)(args...);            // 使用形参包
//     };
//   }
//   std::vector<std::function<void(Args...)>> m_callBacks;
// };


void testString_view();
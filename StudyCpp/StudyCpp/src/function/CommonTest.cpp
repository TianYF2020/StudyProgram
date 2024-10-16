#include "CommonDef.h"
#include "CommonTest.h"

void quit_command() 
{

}
void help_command() 
{

}









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

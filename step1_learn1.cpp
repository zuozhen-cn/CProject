// lesson01_hello.cpp
// 目标：验证「编译 → 链接 → 运行 → 调试」这条完整链路。

#include <iostream>
#include "birthday.h"
#include "privateBirthday.h"
using namespace std;
int main() {
    birthday liming;
   int setday1;
   cin >> setday1;
   liming.setday(setday1);
   std::cout <<"liming公开调用成员：" <<liming.day << "\t\n\t";

   //私有的加成员函数
    p_birthday wangli;
   int setday2;
   cin >> setday2;
   wangli.setp_day(setday2);
   std::cout << "wangli公开调用函数：" << wangli.getday() << "\t\n\t";



}
// lesson01_hello.cpp
// 目标：验证「编译 → 链接 → 运行 → 调试」这条完整链路。

#include <ql/settings.hpp>
#include <ql/time/date.hpp>
#include <ql/version.hpp>
#include <ql/time/schedule.hpp>
#include <ql/time/calendar.hpp>
#include <ql/time/calendars/target.hpp> 
#include <iostream>

int main() {
    using namespace QuantLib;

    // 1) 版本号来自 ql/version.hpp 里的宏
    std::cout << "QuantLib version : " << QL_VERSION << "\n";

    // 2) 构造一个日期（年 月 日），验证类与枚举可用
    Date today(13, Nov, 2026);
    std::cout << "Date             : " << today << " (" << today.weekday() << ")\n";

    // 3) 运算符重载：日期 + 天数
    std::cout << "Next day         : " << today + 1 << "\n";

    // 4) 日期相减得到天数
    Date newYear(1, Jan, 2027);
    std::cout << "Days to 2027     : " << (newYear - today) << "\n";

    // 5) 全局设置里的估值日（QuantLib 的核心全局状态）
    std::cout << "Evaluation date  : " << Settings::instance().evaluationDate() << "\n";

    Schedule fixedBondSchedule(
        Date(15, May, 2007), Date(15, May, 2017), Period(Annual),
        TARGET(), Unadjusted, Unadjusted, DateGeneration::Backward, false);
    std::cout << "Schedule size    : " << fixedBondSchedule.size() << "\n";
    for (const auto& d : fixedBondSchedule)
        std::cout << "  " << d << "\n";


    return 0;
}

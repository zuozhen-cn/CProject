第 0 步：类（class）和对象（object）

// step0.cpp
#include <iostream>

class Birthday {
public:
    int day = 15;     // 成员变量（member variable）
};

int main() {
    Birthday b;                   // 用类创建对象
    std::cout << b.day << "\n";   // 用 . 访问成员
    return 0;
}
输出：


15
语法要点：

写法	含义
class Birthday { ... };	定义一个新类型。class 是"图纸"，末尾分号不能少
public:	从这里开始的成员对外可见
int day = 15;	成员变量，每个 Birthday 对象内部都有一份
Birthday b;	按图纸创建一个对象，名字叫 b
b.day	用点号访问对象的成员
类比：class 是房屋图纸，b 是按图纸盖出来的一栋房子，day 是房子里的一个房间。

// step2.cpp
#include <iostream>
#include <vector>
#include <cstddef>

class MiniSchedule {
private:
    std::vector<int> dates_ = {10, 20, 30};   // 动态数组

public:
    std::size_t size() const { return dates_.size(); }

    int at(std::size_t i) const { return dates_.at(i); }
};

int main() {
    MiniSchedule s;
    std::cout << "size = " << s.size() << "\n";
    std::cout << "s.at(1) = " << s.at(1) << "\n";
    return 0;
}
输出：


size = 3
s.at(1) = 20
语法要点：

std::vector<int> —— 可以自动增长的数组，里面装 int。Schedule 里是 std::vector<Date>，只是把 int 换成日期类型。
{10, 20, 30} —— 初始化列表，依次放入 0、1、2 号位置。
dates_.size() —— 返回元素个数。
dates_.at(i) —— 取第 i 个元素，带越界检查（越界会抛异常）；dates_[i] 不带检查。

std::size_t —— 专门表示"大小/下标"的无符号整数类型。QuantLib 用 typedef std::size_t Size;（ql/types.hpp:58），所以 Schedule::size() 返回 Size 就等于 std::size_t。


第 1 步：私有成员 + 成员函数 + const

// step1.cpp
#include <iostream>

class Birthday {
private:
    int day_ = 15;                       // 私有成员，外部不能直接访问

public:
    int day() const { return day_; }     // 成员函数（方法）
};

int main() {
    Birthday b;
    std::cout << b.day() << "\n";        // 调用成员函数
    // b.day_ = 20;                      // 错误：private 成员不能直接改
    return 0;
}
输出：


15
语法要点：

private: / public: —— 访问权限。成员函数放在 public，数据成员通常放 private。
成员变量的 _ 后缀是 QuantLib 的命名习惯（dates_、calendar_），用来区分"成员"和"局部变量/参数"。
int day() const 的 const 在括号后面，意思是："这个函数不会修改对象"。所以 const Birthday 对象也能调用它。
b.day() 调用的是成员函数，不是访问变量。Schedule 里的 size()、dates() 都是这种函数。
好问题。先说结论：const 加上去，最直接的效果是"约定这个函数只读、不修改对象"，并让 const 对象也能调用它。 我结合你这段代码具体讲。

如果给 setp_day 加 const：

void setp_day(int d) const;   // 声明
那么在这个函数内部，你不能修改任何成员变量，也就是：

void p_birthday::setp_day(int d) const {
    p_day_ = d;   // ❌ 编译报错：const 成员函数里不能修改成员变量！
}
因为 const 承诺"不修改对象"，而 setter 的功能恰恰就是要改数据，所以语义上对不上——setter 一般不应该加 const。

如果给 day() 这种只读函数加 const：

像你前面那个例子：

int day() const { return day_; }   // ✅ 正确
因为 day() 只是读取数据，不修改任何东西，所以加 const 非常合适，而且有实际好处：

好处 1：const 对象也能调用

const p_birthday b;
int x = b.day();   // ✅ 可以，因为 day() 是 const 成员函数
int y = b.p_day_;  // ❌ 不行，私有；即使公开，const 下也不能随便调非 const
好处 2：编译器帮你"守规矩"
如果函数体里不小心写了修改语句，编译器直接报错，防止你误改。

一句话区分：

函数类型	该不该加 const	原因
setter（改数据）setp_day	不该加	它的职责就是改成员变量
getter（读数据）day()	该加	它只读取，加 const 后 const 对象也能调
放在你的代码里：

setp_day（会修改 p_day_）→ 不加 const，像我前面给的正确写法那样。
如果你再加一个"查询生日"的函数（比如 int get_day() const），那它就该加 const。
这就是 const 在这个场景下的全部区别——核心是"能不能改成员变量"，以及"const 对象能不能调用"。还有想验证或展开的点，尽管问。


第 2 步：用 std::vector 存一组数

// step2.cpp
#include <iostream>
#include <vector>
#include <cstddef>

class MiniSchedule {
private:
    std::vector<int> dates_ = {10, 20, 30};   // 动态数组

public:
    std::size_t size() const { return dates_.size(); }

    int at(std::size_t i) const { return dates_.at(i); }
};

int main() {
    MiniSchedule s;
    std::cout << "size = " << s.size() << "\n";
    std::cout << "s.at(1) = " << s.at(1) << "\n";
    return 0;
}
输出：


size = 3
s.at(1) = 20
语法要点：

std::vector<int> —— 可以自动增长的数组，里面装 int。Schedule 里是 std::vector<Date>，只是把 int 换成日期类型。
{10, 20, 30} —— 初始化列表，依次放入 0、1、2 号位置。
dates_.size() —— 返回元素个数。
dates_.at(i) —— 取第 i 个元素，带越界检查（越界会抛异常）；dates_[i] 不带检查。
std::size_t —— 专门表示"大小/下标"的无符号整数类型。QuantLib 用 typedef std::size_t Size;（ql/types.hpp:58），所以 Schedule::size() 返回 Size 就等于 std::size_t。


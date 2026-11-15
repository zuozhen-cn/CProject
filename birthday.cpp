#include <iostream>
#include "birthday.h"
using namespace std;
void birthday::setday(int setday) {
	 birthday::day = setday;
}

birthday::birthday() {
	cout << "开始计量生日" << "\n\t";
}
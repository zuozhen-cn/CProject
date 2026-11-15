#include <iostream>
#include "privateBirthday.h"
using namespace std;
p_birthday::p_birthday() {
	cout << "ÊäÈëÉúÈÕ"<<"\n";

}
void p_birthday::setp_day(int setdayp) {
	p_birthday::p_day_ = setdayp;
}
int p_birthday::getday() const {
	return p_birthday::p_day_;
}
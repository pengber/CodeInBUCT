#include <iostream>

using namespace std;
class human {
public:
	human();
	human(const string &,const int &,const float &,const float &);
	virtual ~human();
private:
	string name_;
	int age_;
	float weight_;
	float height_;
};
human::human() {};
human::human(const string& name, const int& age, const float& weight, const float& height) {
	name_ = name;
	age_ = age;
	weight_ = weight;
	height_ = height;
}

class Pengber:public human {
};
human::~human() {};
int main() {
	return 0;
}
#include <iostream>
#include <string>

using namespace std;

class Staff {
protected:
	int code;
	string name;
	static int count;
public:
	Staff(string n) { name = n; code = count; count ++; }
	void SetName(string n) { name = n; }
	string GetName() const { return name; }
	int GetCode() const { return code; }
	static int GetStaffCount()  { return count -1 ; }
};

int Staff::count = 1;
class Teacher :virtual public Staff {
protected:
	string subject;
public:
	Teacher(string n,string s) :Staff(n) { name = n; subject = s; }
	void SetSubject(string s) { subject = s; }
	string GetSubject() const { return subject; }
};
class Officer : virtual public Staff {
protected:
	string work;
public:
	Officer(string n, string w):Staff(n) { name = n; work = w; }
	void SetWork(string w) { work = w; }
	string GetWork() const { return work; }
};
class Teacher_Officer :public Teacher, public Officer {
public:
	Teacher_Officer(string n, string s, string w) :Staff(n),Teacher(n, s), Officer(n, w) {//这行代码注意要先初始化Staff

	}
};
int main()
{
	Teacher t1("孔子", "儒家文学"); //创建教学类员工t1 
	Teacher t2("公输班", "建筑学");
	Officer o1("端木赐", "财务科长"); //创建教辅类员工o1 
	Teacher_Officer to3("颜回", "儒家文学", "副院长");//创建教师教辅类员工to3 

	cout << "共有教职工" << Staff::GetStaffCount() << "人" << endl;
	cout << t1.GetCode() << ", " << t1.GetName() << ", " << t1.GetSubject() << endl;
	cout << t2.GetCode() << ", " << t2.GetName() << ", " << t2.GetSubject() << endl;
	cout << o1.GetCode() << ", " << o1.GetName() << ", " << o1.GetWork() << endl;
	cout << to3.GetCode() << ", " << to3.GetName() << ", " << to3.GetSubject() << ", " << to3.GetWork() << endl;
	return 0;
}
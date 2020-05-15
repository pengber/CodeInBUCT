#include <iostream>
#include <string>
using namespace std;

class Zerg {
protected:
	int blood;
public:
	Zerg(int a = 0) :blood(a) {}
	void AddBlood(int a) {
		blood += a;
		this->Laugh();
	}
	void ShowBlood() {
		cout << blood << endl;
	}
	virtual void Laugh() = 0;
};
class Drone :public Zerg{
public:
	Drone(int a = 100) :Zerg(a) {}
	void Laugh() {
		cout << "咯吱咯吱...我是勤劳的采矿工" << endl;
	}
};
class Hydralisk :public Zerg {
public:
	Hydralisk(int a = 200) :Zerg(a) {}
	void Laugh() {
		cout << "噗噗噗噗...我是口水龙，口水威力无边" << endl;
	}
};
class Lurker :public Zerg {
public:
	Lurker(int a = 300) :Zerg(a) {}
	void Laugh() {
		cout << "刷刷刷刷...我是潜行蜘蛛，刀过无痕" << endl;
	}
};

void Lair(Zerg& zerg) //虫族补给站函数
{
	zerg.AddBlood(10);
}
int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	Drone zerg1, zerg4(a); //创建矿工对象
	Hydralisk zerg2, zerg5(b); //创建口水龙对象
	Lurker zerg3, zerg6(c); //创建蜘蛛对象

	Lair(zerg1); //进入补给站
	Lair(zerg2);
	Lair(zerg3);

	zerg1.ShowBlood(); //输出现有血量
	zerg2.ShowBlood();
	zerg3.ShowBlood();
	zerg4.ShowBlood();
	zerg5.ShowBlood();
	zerg6.ShowBlood();
	return 0;
}
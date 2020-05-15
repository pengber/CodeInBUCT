#include <iostream>
#include <list>
#include <iterator>
#include <iomanip>
using namespace std;
//任务类，有任务名称和所需空间两个属性
class Work{
public:
	int workId;
	int volume;
	Work(int i, int v) :workId(i), volume(v) {}
};
//空闲分区类，有空闲分区的大小和起始地址两个属性，并且重载<运算符
class Partition {
public:
	int volume;
	int start;
	Partition(int v, int s):volume(v),start(s){}
	bool operator < (const Partition& b) {
		return this->start < b.start;
	}
};
//工作分区类，继承空闲分区，派生一个属性记录这个分区的工作名
class WorkPartition :public Partition {
public:
	int workId;
	WorkPartition(int v, int s, int id) :Partition(v, s) {
		workId = id;
	}
	bool operator < (const WorkPartition& b) {
		return this->start < b.start;
	}
};
//系统类，有工作分区和空闲分区
class System {
protected:
	list<WorkPartition> hadDivide;			//工作分区链表
	list<Partition> notDivide;				//空闲分区链表
public:
	System() {}
	System(WorkPartition* hadD, int n,Partition* notD,int m) {//初始化系统
		for (int i = 0; i < n; i++) {
			hadDivide.push_back(hadD[i]);
		}
		for (int i = 0; i < m; i++) {
			notDivide.push_back(notD[i]);
		}
	}
	void sort() {
		hadDivide.sort();
		notDivide.sort();
	}
	//对工作分区进行任务分区的装载
	void loadWork(Work w) {
		this->sort();
		Partition selectPartition = this->selectPartition(w);
		WorkPartition newWorkPartition(w.volume, selectPartition.start, w.workId);
		hadDivide.push_back(newWorkPartition);
		this->sort();
	}
	//对工作分区进行任务分区的卸载
	void unloadWork(int workId) {
		list<WorkPartition>::iterator listPoint;
		for (listPoint = hadDivide.begin(); listPoint != hadDivide.end(); listPoint++) {//得到workPartition;
			if (listPoint->workId == workId) break;
		}

		Partition newRestPartition(listPoint->volume, listPoint->start);//得到被卸载工作的起始地址和大小后的新空闲分区
		hadDivide.erase(listPoint);//删除工作空间的这个任务
		list<Partition>::iterator insertPoint = insertPartition(newRestPartition);//在空闲分区加入
		unionPartition(--insertPoint);//合并新加入的空闲分区前后


	}
	//选择空闲区并返回，并合并剩余碎片区间
	Partition selectPartition(const Work & w) {
		list<Partition>::iterator listPoint = notDivide.begin();
		while (listPoint-> volume < w.volume && listPoint != notDivide.end()) {
			listPoint++;
		}
		if (listPoint == notDivide.end()) {
			cout << "the not divided is not enough!";
			return *notDivide.end();
		}
		else if (listPoint->volume == w.volume) {
			return *listPoint;
		}
		else {
			Partition selectPartition(listPoint->volume,listPoint->start);
			Partition restPartition(selectPartition.volume - w.volume, selectPartition.start + w.volume);
			notDivide.erase(listPoint);
			list<Partition>::iterator insertPoint = insertPartition(restPartition); //将剩余碎片空间插入并得到插入位置的迭代器
			this->unionPartition(insertPoint);//合并前后两个区间，如果可以的话
			return selectPartition;
		}
	}
	//插入空闲空间r并返回插入的位置的迭代器
	list<Partition>::iterator insertPartition(const Partition& r) {
		list<Partition>::iterator listPoint = notDivide.begin();
		list<Partition>::iterator insertPoint;
		while (listPoint->start < r.start && listPoint != notDivide.end()) {
			listPoint++;
		}
		if (listPoint != notDivide.begin()) {
			insertPoint = listPoint;//如果不是头指针则减减得到上一个指针	
		}
		else {
			insertPoint = notDivide.begin();//如果是头指针则在头指针处插入
		}
		notDivide.insert(insertPoint, r);//在合适的地方（按起始地址大小排序）插入剩余碎片区间
		return insertPoint;

	}
	//将插入位置迭代器的前后两个空闲空间尝试合并
	void unionPartition(list<Partition>::iterator& insertPoint) {
		list<Partition>::iterator initialPoint = insertPoint;//保存两个插入位置的迭代器，因为此迭代器只能自增和自减
		list<Partition>::iterator initialPoint2 = insertPoint;
		list<Partition>::iterator beforeInsertPonit; 
		if (initialPoint2 != notDivide.begin() ) beforeInsertPonit = --insertPoint;

		list<Partition>::iterator afterInsertPonit;
		if (initialPoint2 != notDivide.end()) afterInsertPonit = ++initialPoint;

		if (initialPoint2 != notDivide.begin()) {//如果插入碎片位置为头的话不于前面的指针合并
			if (beforeInsertPonit->start + beforeInsertPonit->volume == initialPoint2->start) {
				initialPoint2->start = beforeInsertPonit->start;
				initialPoint2->volume = beforeInsertPonit->volume + initialPoint2->volume;
				notDivide.erase(beforeInsertPonit);
			}
		}
		if (initialPoint2 != --notDivide.end()) {//为尾的话不于后面的指针合并,注意要比较的是end（）前面的那个迭代器，而不是end
			if (afterInsertPonit->start == initialPoint2->start + initialPoint2->volume) {
				initialPoint2->volume += afterInsertPonit->volume;
				notDivide.erase(afterInsertPonit);
			}
		}
	}
	//输出系统状态
	void printSystem() {
		cout << "The work partition is:" << endl;
		cout << setw(10) <<setiosflags(ios::right)<< "start" << setw(10) << "volume" << setw(10) << "workId" <<endl;
		for (auto ptr = hadDivide.begin(); ptr != hadDivide.end(); ptr++) {
			cout << setw(10) << ptr->start << setw(10) << ptr->volume << setw(10) << ptr->workId <<endl;
		}

		cout << "The rest Partition is:" << endl;
		cout << setw(10) <<"start" << setw(10) << "volume" << endl;
		for (auto ptr = notDivide.begin(); ptr != notDivide.end(); ptr++) {
			cout << setw(10) << ptr->start << setw(10) <<  ptr->volume << endl;
		}
	}
};

int main() {
	WorkPartition works[3] = { WorkPartition(5,0,1),WorkPartition(5,5,3),WorkPartition(6,26,2) };
	Partition rests[2] = { Partition(12,14),Partition(96,32) };
	System system(works, 3, rests, 2);
	cout << "initial system:" << endl;
	system.printSystem();
	cout << endl;

	cout << "load work with 4 workId and 6 volume:" << endl;
	Work work(4,6);
	system.loadWork(work);
	cout << "changing system is:" << endl;
	system.printSystem();

	cout << "unload work with 3 workId:" << endl;
	system.unloadWork(3);
	system.printSystem();

	cout << "unload work with 2 workId:" << endl;
	system.unloadWork(2);
	system.printSystem();
	getchar();
	return 0;
}
#include <iostream>
#include <queue>
#include <ctime>
#include "CircleLinkList.h"				//自己的循环链表
#include <iomanip>							//控制PCB表输出格式
using namespace std;
#define random(x) rand() % x

int num = 5;								//进程数量
//进程类
class Process {
private:
	int id;									//进程id
	int time;								//进程时间片，初始用随机赋值生成
	int pastTime;							//进程度过时间
	int status;								//进程状态，简单的划分为0，1，0表示进程结束，1表示就绪。
	static int pid;							//用于计数进程号
public:
	Process() {
		id = pid++;
		time = random(10) + 5;				//时间片生成5-14之间的数。
		pastTime = 0;							//已运行时间初始为0
		status = 1;							//进程初始状态为就绪
	}
	void run() {							//进行执行
		pastTime++;
	}
	int getId() const {
		return id;
	}
	int getTime() const {					//返回进程时间片
		return time;
	}
	int getPastTime() const {
		return pastTime;
	}
	int getStatus() const {
		return status;
	}
	void setFailure() {
		status = 0;
	}
	void print() const {
		cout << "id:" << id << ",time:" << time << ",pastTime:" << pastTime << ",status:" << status << endl;
	}
	
};

void printPcb(CircleLinkList<Process> &temp);//声明必须放在类之后，因为形参用到了此类
int Process::pid = 0;//静态成员赋值，保证进程对象id的递增。

int main() {
	CircleLinkList<Process> pcb;
	int index = 1;
	//构建对象,此时id = 6
	srand(int(time(0)));
	Process* processes;
	processes = new Process[num];			//下面一行与这一行有严格的顺序关系和while里面的else代码也有关系，（静态成员变量）
	Process temp;

	for (int i = 0; i < num; i++) {
		pcb.insert(i+1,processes[i]);
	}

	
	while (pcb.getLength() != 0) {
		printPcb(pcb);
		pcb.getElem(index, temp);

		temp.run();
		cout << "pcd had scheduled:" << endl;
		temp.print();
		if (temp.getPastTime() == temp.getTime()) {
			temp.setFailure();
			processes[temp.getId()] = temp;
			int tempIndex = index;						//不同于优先数调度算法，优先数采用优先队列，将元素弹出队列后再进行处理，而此队列是处理符合条件再弹出
			index = (index + 1) % (pcb.getLength()+1);

			pcb.deleteElem(tempIndex,temp);
		}
		else {//如果没有到达自己的时间片，要把弹出来的这个元素进行操作了之后再写入，虽然temp是引用，但是我们要更新pcb表里的，所以temp引用不顶用，还是用用setElem
			pcb.setElem(index, temp);
			index = (index+1)%(pcb.getLength()+1);//取getLength+1是因为循环队列是对1-length进行操作，如果取余数length就不能index=length的那个进行操作陷入死循环
		}
	}
	getchar();
	return 0;
}

//显示PCB表的内容，注意因为优先队列不能保持数据完整性的遍历，所以我用了一个数组存放形参，因为形参传参是值传递，所以没有
//值更改对main的PCB没有什么影响。用数组是为了保证PCB表的输出直观。
void printPcb(CircleLinkList<Process> & temp) {
	int size = temp.getLength();
	Process* tempProcesses = new Process[size];
	for (int i = 1; i <= size; i++) {
		temp.getElem(i, tempProcesses[i - 1]);
	}
	cout << "******************PCB STRAT********************" << endl;
	cout << setw(10) << "id:";
	for (int i = 0; i < size; i++) {
		cout << setw(5) << tempProcesses[i].getId();
	}
	cout << endl;

	cout << setw(10) << "time:";
	for (int i = 0; i < size; i++) {
		cout << setw(5) << tempProcesses[i].getTime();
	}
	cout << endl;

	cout << setw(10) << "pastTime:";
	for (int i = 0; i < size; i++) {
		cout << setw(5) << tempProcesses[i].getPastTime();
	}
	cout << endl;
	cout << "-------------------PCB ENDING------------------" << endl;

}
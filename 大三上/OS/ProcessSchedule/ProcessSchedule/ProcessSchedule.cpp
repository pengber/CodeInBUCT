#include <iostream>
#include <queue>
#include <ctime>

#include <iomanip>							//控制PCB表输出格式
using namespace std;
#define random(x) rand() % x


int num = 5;								//进程数量
//进程类
class Process {
private:
	int id;									//进程id
	int time;								//进程时间片，初始用随机赋值生成
	int priority;							//进程优先级，初始随机生成。
	int status;								//进程状态，简单的划分为0，1，0表示进程结束，1表示就绪。
	static int pid;							//用于计数进程号
public:
	Process() {
		id = pid++;
		time = random(10)+5;				//时间片生成5-14之间的数。
		priority = random(10);				//优先级生成0-9之间的数。
		status = 1;							//进程初始状态为就绪
	}
	void run() {							//进行执行
		time--;
		priority--;
	}
	int getId() const {
		return id;
	}
	int getTime() const  {					//返回进程时间片
		return time;
	}
	int getPriority() const {
		return priority;
	}
	int getStatus() const {
		return status;
	}
	void setFailure() {
		status = 0;
	}
	void print() const {
		cout << "id:" << id << ",time:" << time << ",priority:" << priority << ",status:" << status << endl;
	}
	friend bool operator < (const Process& a, const Process& b);//用于优先队列排序
};

bool operator < (const Process& a, const Process& b) {
	return a.getPriority() < b.getPriority();
}
void printPcb(priority_queue<Process> temp);//声明必须放在类之后，因为形参用到了此类
int Process::pid = 0;//静态成员赋值，保证进程对象id的递增。
int main() {
	priority_queue<Process> pcb;
				//构建对象,此时id = 6
	srand(int (time(0)));
	Process* processes;
	processes = new Process[num];			//下面一行与这一行有严格的顺序关系和while里面的else代码也有关系，（静态成员变量）
	Process temp;

	for (int i = 0; i < num; i++) {

	}
	for (int i = 0; i < num; i++) {
		pcb.push(processes[i]);
	}
	while (!pcb.empty()) {
		printPcb(pcb);
		temp = pcb.top();
		pcb.pop();
		cout <<  "pcd is scheduling:" << endl;
		temp.print();
		temp.run();
		//temp.print();
		if (temp.getTime() != 0) {
			pcb.push(temp);
		}
		else {
			temp.setFailure();
			processes[temp.getId()] = temp;//因为最初始构造的num个id是0——num-1，所以利用数组下标和id相等的特性再赋值。
		}
	}
	getchar();
	return 0;
}

//显示PCB表的内容，注意因为优先队列不能保持数据完整性的遍历，所以我用了一个数组存放形参，因为形参传参是值传递，所以没有
//值更改对main的PCB没有什么影响。用数组是为了保证PCB表的输出直观。
void printPcb(priority_queue<Process> temp) {
	int size = temp.size();
	Process *tempProcesses = new Process[size];
	for (int i = 0; i < size; i++) {
		tempProcesses[i] = temp.top();
		temp.pop();
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

	cout << setw(10) << "priority:";
	for (int i = 0; i < size; i++) {
		cout << setw(5) << tempProcesses[i].getPriority();
	}
	cout << endl;
	cout << "-------------------PCB ENDING------------------" << endl;
	
}
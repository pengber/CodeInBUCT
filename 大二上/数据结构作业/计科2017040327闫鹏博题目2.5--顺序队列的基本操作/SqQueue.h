/************************************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/10/21
************************************************************************************/
/************************************************************************************
*Problem	:
			1.DEBUG没打，但DEBUG感觉没用，以后想起来再打吧
*Tips:		:
			1.线性循环队列空和满都是front == rear;所以得改变条件来判空判满,一种方法是
			设置一个标志位flag,flag当队列内有元素时为1,无元素时为0,满的条件时s==1并且
			front == rear,空的条件则为flag == 0;第二种方法是损失掉队列里面的头指针前
			面的那个存储空间,则当rear == front时队列为空,当(rear + 1) %maxSize == front
			时为满
			2.如果用第二种用法的时候,用户如果想建立100大小的队列,参考程序写成maxSize =
			100,但实际上队列为满的只能存储99个数据并且队列长99,所以我认为参考程序有一个
			逻辑BUG,而修正的办法就是maxSize = size + 1;对逻辑进行修正;测试后一切正如老夫
			所料。
			3.注意一下,求队列元素长度的函数写法和出队时front的写法
			4.默认rear指向队尾元素的下一个空间,front指向队首元素
************************************************************************************/
/************************************************************************************
*History	:

************************************************************************************/
#ifndef SQQUEUE_H_INCLUDE
#define SQQUEUE_H_INCLUDE

#include <iostream>

//#define DEBUG											//DEBUG打开这条注释
#define REMIND											//REMIND打开这条注释
#define DEFAULT_SIZE 100

template <class ElemType>
class SqQueue {
/***********************************公共接口声明*******************************/
public:
	//基本成员函数
	SqQueue(int capacity = DEFAULT_SIZE);

	virtual ~SqQueue();
	//特征函数
	//得
	int getLength() const;

	bool getFrontElem(ElemType & elem) const;

	//判
	bool isEmpty() const;

	bool isFull() const;

	//插
	bool inQueue(const ElemType & elem);

	//改
	//无

	//删
	bool outQueue(ElemType & elem);

	void clean();
	//特殊函数
	void display() const;
	//重载函数
	SqQueue<ElemType> & operator=(const SqQueue<ElemType> & copy);

/*=================================公共接口声明完毕============================*/
/***********************************保护接口声明*******************************/
protected:
	ElemType * elems;
	
	int capacity;

	int front, rear;
/*=================================保护接口声明完毕============================*/
};
/***********************************公共接口实现*******************************/
template <class ElemType>
SqQueue<ElemType>::SqQueue(int capacity) {
	elems = new ElemType[capacity + 1];							//对capacity进行修正
	front = rear = 0;
	this->capacity = capacity + 1;								//对capacity进行修正
}
template <class ElemType>
SqQueue<ElemType>::~SqQueue() {
	delete[] elems;
}
//函数名称: int getLength() const
//函数功能: 返回队列元素长度
//无子函数
//注意事项: 加capacity再取余得原因是,因为队列是循环队列,所以当队尾超过容量但队列未满
//			时进入循环,所以加一个capacity是为了让rear在逻辑上一直比front大,这样他们
//			在rear比front小时相减就还是队列长度,而取余是为了让rear比front大时不受相
//			加的capacity的影响
template <class ElemType>
int SqQueue<ElemType>::getLength() const {
	return (rear + capacity - front) % capacity;
}
//函数名称: bool getFrontElem(ElemType & elem) const
//函数功能: 得到队首元素值
template <class ElemType>
bool SqQueue<ElemType>::getFrontElem(ElemType & elem) const {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "队列为空,不能得到队首元素的值" << std::endl;
#endif
		return false;
	}
	else {
		elem = elems[front];
		return true;
	}
}
//函数名称: bool isEmpty() const
//函数功能: 判断队是否为空，为空返回1，否则返回0
template <class ElemType>
bool SqQueue<ElemType>::isEmpty() const {
	if (rear == front) return true;
	else return false;
}
//函数名称: bool isFull() const
//函数功能: 判断队是否已满，已满返回1,否则返回0
template <class ElemType>
bool SqQueue<ElemType>::isFull() const {
	if ((rear + 1) % capacity == front) return true;
	else return false;
}
//函数名称: bool inQueue(const ElemType & elem)
//函数功能: 入队，队满则返回假，否则将元素入队返回真
//其子函数：bool isFull()
template <class ElemType>
bool SqQueue<ElemType>::inQueue(const ElemType & elem) {
	if (this->isFull()) {
#ifdef REMIND
		std::cout << "队列为满,不能入队" << std::endl;
#endif
		return false;
	}
	else {
		elems[rear++ % capacity] = elem;
		return true;
	}
}
//函数名称: bool outQueue(ElemType & elem)
//函数功能: 队空返回假，否则将队首元素由引用参数得回并返回真
//其子函数: bool isEmpty()
//注意事项: 注意front的写法
template <class ElemType>
bool SqQueue<ElemType>::outQueue(ElemType & elem) {
	if (this->isEmpty()) {
#ifdef REMING
		std::cout << "队列为空,不能出队" << std::endl;
#endif
		return false;
	}
	else {
		elem = elems[front];
		front = ++front % capacity;			//front++;不能front++就完事了,因为是循环队列
		return true;
	}
}
//函数名称: void clean()
//函数功能: 将队清空
template <class ElemType>
void SqQueue<ElemType>::clean() {
	front = rear = 0;

	/*将队清空的另一种方法:

	ElemType tempElem;
	while (!this->isEmpty()) {
		this->outQueue(tempElem);
	}
	*/
}
template <class ElemType>
void SqQueue<ElemType>::display() const {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "链表为空" << std::endl;
#endif
	}
	else {
		int tempFront = front;
		int tempRear = rear;
		
		for (int i = tempFront; i != rear; (i++) % capacity) {
			std::cout << elems[i] << std::endl;
		}
	}

	
}
/*=================================公共接口实现完毕============================*/
#endif // !SQQUEUE_H_INCLUDE

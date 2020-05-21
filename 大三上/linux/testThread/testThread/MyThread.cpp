#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <iostream>
#define gettid() syscall(__NR_gettid)
#define MAX 10				//对共享数据的访问次数的控制
using namespace std;
pthread_t thread_1,thread_2;  //两个线程id
pthread_mutex_t mutex;		//信号量
int number = 0;

void* thread1(void* arg)
{
	printf("thread1 : I'm runing,Tid is %d\n", gettid());//输出线程号
	int i;
	for (i = 0; i < MAX; i++)   //模拟线程执行时间
	{

		cout << "now i is" << i << endl;
		cout << "thread_1:number = " << number<< endl;
		pthread_mutex_lock(&mutex);//对信号量进行P操作
		number++;
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
	cout << "This is end of thread_1" << endl;
	pthread_exit(NULL);
}

void* thread2(void* arg)
{
	printf("thread2 : I'm thread 2,Tid is %d\n", gettid());//输出线程号
	int j;
	for (j = 0; j < MAX; j++)
	{
		cout << "now j is" << j << endl;//输出线程的执行到第几个循环
		cout << "thread_2:number = " << number << endl;//输出number现在的值
		pthread_mutex_lock(&mutex);//临界资源访问
		number++;
		pthread_mutex_unlock(&mutex);
		sleep(3);
	}


	cout << "This is end of thread_2" << endl;
	pthread_exit(NULL);			//线程结束
}

void thread_wait() {			//写成函数，以免调试时等待线程1结束后才能执行线程2
	if (thread_1 != 0 || thread_2 != 0) {
		pthread_join(thread_1, NULL);
		pthread_join(thread_2, NULL);
	}
}


int main()
{
	int flag_1, flag_2;//判断线程是否创建成功的变量
	pthread_mutex_init(&mutex, NULL);//用默认属性初始化互斥锁

	pid_t pid;
	pid = getpid();
	cout << "main is running, and pid is" << pid << endl;
	cout << "now I will create thread!" << endl;

	//创建两个线程，两个线程都对number做累加，所以需要保证number是同步的
	flag_1 = pthread_create(&thread_1, NULL, thread1, NULL);
	if (flag_1 != 0) cout << "thread_1 fail" << endl;
	else cout << "thread_1 success!" << endl;

	flag_2 = pthread_create(&thread_2, NULL, thread2, NULL);
	if (flag_2 != 0) cout << "thread_2 fail" << endl;
	else cout << "thread_2 success!" << endl;
	//创建结束

	thread_wait();//等待线程运行结束，否则主程序结束，线程会结束


	cout << "This is end of main function" << endl;
	return 0;
}


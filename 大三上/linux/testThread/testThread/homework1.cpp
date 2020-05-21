/*
程序目的：1.生产者消费者的一个操作系统作业
解决问题：*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 20
#define NUM 100//NUM控制线程对缓冲区信号量和互斥量的请求次数，用for循环代替while避免永久循环
int in = 0;
int out = 0;
int buff[N] = { 0 };	//缓冲区没有产品
sem_t empty;
sem_t full;
pthread_mutex_t mutex;//互斥信号量

void print()
{
	int i;
	for (i = 0; i < N; i++)
		printf("%d ", buff[i]);
	printf("\n");
}

void wait_end(pthread_t &producer_id,pthread_t & prochaser_id) {
	pthread_join(producer_id, NULL);
	pthread_join(prochaser_id, NULL);
}

void* produce(void*) {
	for (int i = 0; i < NUM; i++) {
		sleep(1);
		sem_wait(&empty);//消耗掉一个无
		pthread_mutex_lock(&mutex);
		printf("before produce:\n");
		print();
		buff[in] = 1;	//生产
		in = (in + 1) % N;
		printf("after produce: \n");
		print();
		pthread_mutex_unlock(&mutex);
		sem_post(&full);//增加一个有
	}
}

void* prochase(void*) {
	for(int j = 0;j < NUM;j++){
		sleep(1);
		sem_wait(&full);//消耗一个无
		pthread_mutex_lock(&mutex);
		printf("before prochase:\n");
		print();
		buff[out] = 0;//消费
		out = (out + 1) % N;
		printf("after prochase: \n");
		print();//观察消费后的
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);//增加一个有
	}
}

int main() {
	pthread_t producer_id;//生产者
	pthread_t prochaser_id;
	//初始化信号量
	int init1 = sem_init(&empty, 0, N);
	int init2 = sem_init(&full, 0, 0);
	if (init1 != 0 || init2 != 0) {
		printf("sem init faild \n");
		exit(1);//exit通知操作系统程序终止，1为异常终止，0为正常终止，头文件为stdlib.h
		//健壮性的增强
	}
	//初始化互斥量
	int init3 = pthread_mutex_init(&mutex, NULL);
	if (init3 != 0) {
		printf("mutex init failed! \n");
		exit(1);//同上
	}

	int create_flag1 = pthread_create(&producer_id, NULL, produce, NULL);
	int create_flag2 = pthread_create(&prochaser_id, NULL, prochase, NULL);
	if (create_flag1 != 0 || create_flag2 != 0) {
		printf("crate pthread failed!\n");
		exit(1);
	}

	wait_end(producer_id, prochaser_id);//等待线程结束
	exit(0);
	return 0;
}

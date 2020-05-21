/*
1.这个程序用来检测pthread_join函数
2.这个程序很好的展示了pthread_create函数*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_message_function(void* ptr);

int main()
{
	int tmp1, tmp2;
	void* retval;
	pthread_t thread1, thread2;
	char* message1 = "thread1";
	char* message2 = "thread2";

	int ret_thrd1, ret_thrd2;

	ret_thrd1 = pthread_create(&thread1, NULL, print_message_function, (void*)message1);
	ret_thrd2 = pthread_create(&thread2, NULL, print_message_function, (void*)message2);

	// 线程创建成功，返回0,失败返回失败号
	if (ret_thrd1 != 0) {
		printf("线程1创建失败\n");
	}
	else {
		printf("线程1创建成功\n");
	}

	if (ret_thrd2 != 0) {
		printf("线程2创建失败\n");
	}
	else {
		printf("线程2创建成功\n");
	}

	//同样，pthread_join的返回值成功为0
	tmp1 = pthread_join(thread1, &retval);
	printf("thread1 return value(retval) is %p\n", retval);
	printf("thread1 return value(tmp) is %d\n", tmp1);
	if (tmp1 != 0) {
		printf("cannot join with thread1\n");
	}
	printf("thread1 end\n");

	tmp2 = pthread_join(thread1, &retval);
	printf("thread1 return value(retval) is %p\n", retval);
	printf("thread1 return value(tmp2) is %d\n", tmp2);
	if (tmp2 != 0) {
		printf("cannot join with thread1 again.\n");
	}
	printf("thread2 end\n");

}

void* print_message_function(void* ptr) {
	int i = 0;
	for (i; i < 5; i++) {
		printf("%s:%d\n", (char*)ptr, i);
	}
}

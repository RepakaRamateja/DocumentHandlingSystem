#include"Queue.h"

int main()
{

	Queue que;
	que.enqueue("ram");
	que.enqueue("teja");
	que.enqueue("akhil");
	que.enqueue("rammohan");

	que.dequeue();
	que.dequeue();
	que.dequeue();
	long size = que.size();
	std::cout << "the size is------>" << size;


	return 0;
}
/*
【队列】
实现一个队列，包括入队、出队、判空和判满操作。
*/
#include <iostream>
#define MAXSIZE 100
class queue
{
public:
    bool enQueue(int x)
    {
        if (isFull())
            return false;
        nums[rear % MAXSIZE] = x;
        rear = (rear + 1) % MAXSIZE;
        return true;
    }
    int deQueue()
    {
        if (isEmpty())
            return 0;
        int ans = nums[front];
        front = (front + 1) % MAXSIZE;
        return ans;
    }
    bool isEmpty()
    {
        if (front == rear)
            return true;
        else
            return false;
    }
    bool isFull()
    {
        if ((rear + 1) % MAXSIZE == front)
            return true;
        else
            return false;
    }
    queue()
    {
        front = 0;
        rear = 0;
    }
    ~queue() {}

private:
    int nums[MAXSIZE];
    int front;
    int rear;
};
int main()
{
    queue myQueue;
    if (myQueue.isFull())
        std::cout << "error ! full queue" << std::endl;
    else
        myQueue.enQueue(4);
    if (!myQueue.isEmpty())
        int res = myQueue.deQueue();
    else
        std::cout << "error! no element" << std::endl;
    return 0;
}
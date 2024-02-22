#ifndef STACKQUEUE_H
#define STACKQUEUE_H
#include <iostream>

using namespace std;

template <class T>
class StackQueue
{
    private:
        static const int stackqueue_Size=100 ; //we have static constant number for the size of stackqueue array
        T stackqueue_list[stackqueue_Size]; //we define the stackqueue array as type T
        int rear, front, count; //parameters which help to follow where to push and pop

    public:
        StackQueue(); //constructor
        void push_front(const T &item); //pushes to the front
        T pop_front(); //pops the last pushed element
        T pop_rear(); //pops the first pushed element
        int is_Empty();
        int is_Full();

};


template <class T>
StackQueue<T>::StackQueue() //constructor initializes the parameters
        {
         rear=0; front=0; count=0;
        }

template <class T>
void StackQueue<T>::push_front(const T &item) //pushes to the front
        {
            if(is_Full()) //if the array is full, we have an error message and exits the code
            {
                cerr<<"Full"<<endl;
                exit(1);
            }

            stackqueue_list[front]=item; //we put the input item to the front and front number and count number are increased by one
            front=(front+1)%stackqueue_Size;
            count++;

        }
template <class T>
T StackQueue<T>::pop_front() //pops the last pushed element
        {

            if(is_Empty()) //if the array is empty, we have an error message and exits the code
            {
                cerr<<"Empty"<<endl;
                exit(1);
            }
            if(front==0) //if no element popped before, we set the front number to the last element
            {
                front=stackqueue_Size-1;
            }
            else // if already popped before, we just decrease the front and count numbers by one
            {
                front=front-1;
            }

            count--;
            return stackqueue_list[front];
        }
template <class T>
T StackQueue<T>::pop_rear() //pops the first pushed element
        {
            T temp;
            if(is_Empty()) //if the array is empty, we have an error message and exits the code
            {
                cerr<<"Empty"<<endl;
                exit(1);
            }
            temp=stackqueue_list[rear]; //the value at the rear is set to a type T temporary element, and rear number is increased by one, count is decreased by one
            rear=(rear+1)%stackqueue_Size;
            count--;
            return temp; //the element which is pushed first is popped and it is returned by this method
        }
template <class T>
int StackQueue<T>::is_Empty() //checks the number of elements is zero
        {
            return count==0;
        }
template <class T>
int StackQueue<T>::is_Full() //checks the number of elements is equal to the max number of elements
        {
            return count==stackqueue_Size;
        }





#endif // STACKQUEUE_H

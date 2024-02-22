#ifndef STACKQUEUE2_H
#define STACKQUEUE2_H
#include <iostream>

using namespace std;


template <class U>
class Node //we create a U type node class
{
    public:
    Node *prev, *next; //nodes have two pointer pointing to previous and next nodes, and includes a U type data
    U data;

    Node()
    {

    }
    Node(U input_data) //node constructor initializes the data from input data and pointers do not point anywhere at the beginning
    {
        data=input_data;
        prev=NULL;
        next=NULL;
    }

};

template <class T>
class StackQueue2 //this class is implementation of doubly linked list
{
    public:
        Node <T> *head; //we have node type head and tail of the doubly linked list and at the beginning the do not point anywhere
        Node <T> *tail;

        StackQueue2()
        {
            head=NULL;
            tail=NULL;
        }

        void push_front(const T &item);//pushes to the front
        T pop_front(); //pops the last pushed element
        T pop_rear(); //pops the first pushed element
        int is_Empty();



};



template <class T>
void StackQueue2<T>::push_front(const T &item) //this method creates a node type pointer and if it does not point anywhere, the head and tail are set to point that node
{
    Node <T> *node;
    node=new Node <T>(item);
    if(head==NULL)
    {
        head=node;
        tail=node;
    }
    else //else the next of tail is set to node, previous of node is set to point tail and finally node is assigned to tail
    {
        tail->next=node;
        node->prev=tail;
        tail=node;
    }


}
template <class T>
T StackQueue2<T>::pop_front() //
{
    if(tail==NULL)
        return NULL;

    T temp_data=tail->data;
    Node <T> *temp_tail=tail;
    if(tail->prev!=NULL)
    {
        tail->prev->next=NULL;
        tail=tail->prev;
    }
    else
    {
        tail=NULL;
        head=NULL;
    }
    delete temp_tail;

    return temp_data;


}

template <class T>
T StackQueue2<T>::pop_rear()
{

    if(head==NULL)
        return NULL;

    T temp_data=head->data;
    Node <T> *temp_head=head;
    if(head->next!=NULL)
    {
        head->next->prev=NULL;
        head=head->next;
    }
    else
    {
        tail=NULL;
        head=NULL;
    }
    delete temp_head;

    return temp_data;
}

template <class T>
int StackQueue2<T>::is_Empty()
{
    return head==NULL;
}






#endif // STACKQUEUE2_H

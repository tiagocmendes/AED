//
// Tomás Oliveira e Silva, AED, October 2014, September 2015
//
// Generic queue (First In First Out) implementation based on an linked list
//

#ifndef _AED_lQueue_
#define _AED_lQueue_

#include <cassert>
#include <math.h>

template <typename T>
class Node
{
    public:
        T data;
        Node<T> *next;
        Node(T values)
        {
            data = values;
            next = NULL;
        }


};

template <typename T>
class lQueue
{
  private:
    Node<T> *head;
    Node<T> *tail;
  public:
    lQueue(void)
    {
        head = NULL;
        tail = NULL;
    }
    ~lQueue(void)
    {
        clear();
    }
    void clear(void)
    {
      while(!is_empty())
      {
          dequeue();
      }
    }
    int size(void) const
    {
        if(head == NULL) return 0;

        unsigned _size = 0;
        Node<T> *i = head;
        while(i != tail)
        {
            i = i -> next;
            _size++;
        }
        return _size;
            
    }
    int is_full(void) const
    {
        return 0;
    }
    int is_empty(void) const
    {
        return head == NULL;
    }
    void enqueue(T &v)
    {   
        if(tail == NULL || head == NULL)
        {
            tail = new Node<T>(v);
        }
        else
        {
            tail->next = new Node<T>(v);
            tail = tail->next;
        }
        if(head == NULL)
        {
            head = tail;
        }
    }
    T dequeue(void)
    {
        assert(!is_empty());

        T temp = head->data;

        Node<T> *lixo = head;
        head = head->next;

        delete lixo;
        return temp;
    }
    T peek(void)
    {
        return head->data;
    }
};

#endif

#include <iostream>
#include "IntList.h"
using namespace std;

 //Initializes an empty list.
    IntList::IntList()
    {
        dummyHead = 0;
        dummyTail = 0;
    }
    //Deallocates all remaining dynamically allocated memory (all remaining IntNodes).
    IntList::~IntList()
    {
        while(dummyHead != 0)
        {
            pop_front();
        }
    }
    void IntList::push_front(int value)
    {
        IntNode *temp = new IntNode(value);
        if(dummyHead == 0)
        {
            dummyHead = temp;
            dummyTail = temp;
        }
        else
        {
            temp->next = dummyHead;
            dummyHead->prev = temp;
            dummyHead = temp;
        }
    }
    //Returns true if the list does not store any data values (it only has dummy dummyHead and dummy dummyTail), otherwise returns false.
    bool IntList::empty() const
    {
        if(dummyHead == 0 && dummyTail == 0)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    /*Removes the node at the front end of the list (the node after the dummy dummyHead). 
    Does nothing if the list is already empty. This must be an O(1) operation.*/
    void IntList::pop_front()
    {
        if(dummyHead != 0)
        {
            IntNode * temp = dummyHead;
            dummyHead = dummyHead->next;
            if(dummyHead != 0)
            {
                dummyHead->prev = 0;
            }
            else
            {
                dummyTail = 0;
            }
            delete temp;
        }
        
    }
    
    // Inserts a data value (within a new node) at the back end of the list. This must be an O(1) operation.
    void IntList::push_back(int value)
    {
        IntNode*temp = new IntNode(value);
        if(dummyTail == 0)
        {
            dummyHead = temp;
            dummyTail = temp;
        }
        else
        {
            dummyTail->next = temp;
            temp->prev = dummyTail;
            dummyTail = temp;
        }
       
    }
    /* Removes the node at the back end of the list (the node before the dummy dummyTail).
    Does nothing if the list is already empty. This must be an O(1) operation.*/
    void IntList::pop_back()
    {
        if(!empty() )
        {
            IntNode * temp = dummyTail;
            if(dummyHead == dummyTail)
            {
                delete temp;
                dummyHead = 0;
                dummyTail = 0;
            }
            else
            {
                dummyTail = dummyTail->prev;
                dummyTail->next = 0;
                delete temp;
            }
        }
        
    }
    /*prints to a single line all of the int values stored in the list in REVERSE order, each separated by a space. 
    This function does NOT output a newline or space at the end.*/
    void IntList::printReverse() const
    {
        for(IntNode*temp = dummyTail; temp != 0; temp = temp->prev)
        {
            cout << temp->data;
            if(temp->prev != 0)
            {
                cout << " ";
            }
        }
        
    }
    
    /* A global friend function that outputs to the stream all of the integer values within the list on a single line,
    each separated by a space. This function does NOT send to the stream a newline or space at the end.*/
    ostream & operator<<(ostream &out, const IntList &rhs)
    {
        IntNode *dataA = rhs.dummyHead;
        while (dataA != 0) {
        out << dataA->data;
        if (dataA->next != 0) {
            out << ' ';
        }
        dataA = dataA->next;
    }
        
        return out;
    }
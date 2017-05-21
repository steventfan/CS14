#include <iostream>
#include "IntList.h"

using namespace std;

//Fan
//Steven
//861230571
//Sanka
//Haasith 
//861215756

int main()
{
    IntList Test;
    
    Test.push_front(3);
    cout << Test << endl;
    Test.push_back(1);
    cout << Test << endl;
    Test.push_back(5);
    cout << Test << endl;
    Test.push_front(2);
    cout << Test << endl;
    Test.pop_back();
    cout << Test << endl;
    Test.pop_front();
    cout << Test << endl;
    Test.printReverse();
    cout << endl;
    
    return 0;
}
#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <stack>
#include <queue>

using namespace std;

WordLadder::WordLadder(const string &fileName)
{
    ifstream inFS;
    
    inFS.open(fileName.c_str() );
    if(!inFS.is_open() )
    {
        cout << "Could not open file \"" << fileName << "\"" << endl;
    }
    else
    {
        string dictWord;
        
        while(!inFS.eof() )
        {
            inFS >> dictWord;
            if(dictWord.length() != 5)
            {
                cout << "Error: Word is smaller than 5 character" << endl;
                
                return;
            }
            dict.push_back(dictWord);
        }
        inFS.close();
    }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
{
    if(validateWords(start, end) )
    {
        queue<stack<string> > queueStacks;
        ofstream outFS;
        
        outFS.open(outputFile.c_str() );
        if(createWordLadder(start, end, queueStacks) )
        {
            stack<string> outputStack;
            
            while(!queueStacks.back().empty() )
            {
                outputStack.push(queueStacks.back().top() );
                queueStacks.back().pop();
            }
            while(!outputStack.empty() )
            {
                outFS << outputStack.top();
                outFS << endl;
                outputStack.pop();
            }
        }
        else
        {
            outFS << "No Word Ladder Found." << endl;
        }
        outFS.close();
    }
    else
    {
        cout << "Error: Word is not in dictionary" << endl;
    }
}

bool WordLadder::validateWords(const string &start, const string &end)
{
    list<string>::iterator dictIterator = dict.begin();
    bool startValid = false;
    bool endValid = false;
    
    while(dictIterator != dict.end() )
    {
        if(*dictIterator == start)
        {
            startValid = true;
        }
        if(*dictIterator == end)
        {
            endValid = true;
        }
        ++dictIterator;
    }
    
    return startValid && endValid;
}

bool WordLadder::createWordLadder(const string &start, const string &end, queue<stack<string> > &queueStacks)
{
    stack<string> stackStrings;
    list<string>::iterator dictIterator = dict.begin();
    bool isEndWord = true;
    
    stackStrings.push(start);
    queueStacks.push(stackStrings);
    if(!(start == end) )
    {
        isEndWord = false;
        while(!queueStacks.empty() && !isEndWord)
        {
            list<string>::iterator dictIterator = dict.begin();
            
            while(dictIterator != dict.end() && !isEndWord)
            {
                int contrastCount = 0;
                
                for(int i = 0; i < 5; ++i)
                {
                    if(queueStacks.front().top().at(i) != dictIterator->at(i) )
                    {
                        ++contrastCount;
                    }
                }
                if(contrastCount == 1)
                {
                    if(*dictIterator == end)
                    {
                        isEndWord = true;
                    }
                    stack<string> copyStack = queueStacks.front();
                    copyStack.push(*dictIterator);
                    queueStacks.push(copyStack);
                    dictIterator = dict.erase(dictIterator);
                }
                else
                {
                    ++dictIterator;
                }
            }
            queueStacks.pop();
        }
    }
    
    return isEndWord;
}
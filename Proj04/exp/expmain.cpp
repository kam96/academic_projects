// expmain.cpp
//
// ICS 46 Spring 2017
// Project #4: Rock and Roll Stops the Traffic
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.

#include <iostream>
#include <string>
#include "Digraph.hpp"
using namespace std;

int main()
{
    string a = "potato";
    string b = "testing";
    string c = "moretest";
    string d = "information";
    string e = "something";
    string f = "anodder";

    Digraph<string,string> test;

    try
    {
        test.addVertex(0,a);
        test.addVertex(1,b);
        test.addVertex(2,c);
        test.addVertex(3,d);
        test.addVertex(4,e);

        test.addEdge(0,1,b);
        test.addEdge(1,2,e);
        test.addEdge(2,3,a);
        test.addEdge(3,4,f);
        test.addEdge(4,0,e);

        vector<pair<int,int>> eat = test.edges();
        for (int i = 0; i < eat.size(); i++)
            cout << eat[i].second << endl;

        cout << "------" << endl;

        cout << test.isStronglyConnected() << endl;
        test.removeEdge(2,3);
        cout << test.isStronglyConnected() << endl;

        cout << "------" << endl;

        vector<pair<int,int>> fat = test.edges();
        for (int i = 0; i < fat.size(); i++)
            cout << fat[i].second << endl;
    }

    catch (DigraphException c)
    {
        cout << "caught exception" << endl;
    }

    return 0;
}


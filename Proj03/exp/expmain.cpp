// expmain.cpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.

#include <iostream>
#include "BSTSet.hpp"
using namespace std;

int main()
{
    BSTSet<string> Tree;
    Tree.add("Merp");
    Tree.add("Alice");
    Tree.add("Cool");
    Tree.add("Merp");
    Tree.add("Hello");
    Tree.add("Poopscok");

    cout << Tree.contains("Merp") << endl;
    cout << Tree.contains("{pp[") << endl;
    cout << Tree.contains("Hello") << endl;
    cout << Tree.contains("Alice") << endl;
    cout << Tree.contains("Cool") << endl;
    return 0;
}


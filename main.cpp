#include <iostream>
#include <set>
#include <deque>
using namespace std;
#include "node.h"
#include "tree.h"

/*
Author: Scott Tabaka
CMPSCI 4280 Project0

Purpose: This program takes 0 or 1 command line arguments and then creates a binary tree.  With 0 arguments the program
    will prompt the user to input strings manually followed by <ctrl+d> and insert them into the tree.  With 1 command
    line argument the program will use the given file to input strings into the tree.  It then prints the trees into
    separate files for each traversal type(Preorder,Inorder,Postorder).
*/

int main(int argc, char *argv[])
{
    if(argc > 2)                                //checks for correct amount of arguments
    {
        cout << "Usage Error: P0 <filename>" << endl;
        exit(1);
    }

    buildTree *tree = new buildTree();
    string inputFilename = "";

    switch (argc)                           //switch
    {
        case 1:
            tree->run1();               //run program with no file name
            break;
        case 2:
            inputFilename = argv[1];
            tree->run2(inputFilename);        //run program with file name
            break;
        default:
            cout << "Usage Error: P0 <filename>" << endl;		//display for proper usage
            exit(1);
    }

    tree->printPreorder(inputFilename);
    tree->printInorder(inputFilename);
    tree->printPostorder(inputFilename);

    delete tree;
}
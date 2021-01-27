#include <iostream>
#include <set>
#include <deque>
#include <fstream>
using namespace std;
#include "node.h"
#include "tree.h"


buildTree::buildTree()
{
    root = NULL;
}

buildTree::~buildTree()
{
    destroy_tree();
}

void buildTree::destroy_tree()
{
    destroy_tree(root);
}

void buildTree::destroy_tree(node *leaf)
{
    if(leaf != NULL){
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void buildTree::run1()
{
    string inputFilename,inputString,bufferString;
    size_t pos = 0;

    cout << "Please Enter Strings and press <ctrl+d> when finished." << endl;

    while (getline(cin, bufferString))  //appends each input by user to a string and cleans all excess spacing
    {
        bufferString = cleanString(bufferString);
        inputString.append(bufferString);
        inputString.append(" ");
    }

    while ((pos = inputString.find(" ")) != string::npos)  //Reads each substring separated by spaces and inputs into tree
    {
        bufferString = inputString.substr(0, pos);
        insert(bufferString);
        inputString.erase(0, pos + 1);
    }
}

void buildTree::run2(string inputFilename)
{
    string inputString,bufferString;
    ifstream input;
    inputFilename = appendFileExtension(inputFilename);
    input.open(inputFilename);

    if(input)
    {
        while (!input.eof())                //reads contents of input file and inserts into tree
        {
            input >> inputString;
            insert(inputString);
        }
    }else{
        cout << "Error: Cannot open file -- " << inputFilename << endl;
    }
    input.close();
}

string buildTree::appendFileExtension(string s)             //adds .fs19 file extension if it does not exist
{
    if(s.length() > 5)
    {
        if (s.substr(s.length() - 5, 5).compare(".fs19") != 0)
        {
            s.append(".fs19");
        }
    }else{
        s.append(".fs19");
    }
    return s;
}

string buildTree::removeFileExtension(string s)         //removes .fs19 file extension if it exists
{
    if(s.length() > 5)
    {
        if (s.substr(s.length() - 5, 5).compare(".fs19") == 0)
        {
            s = s.substr(0,s.length() - 5);
        }
    }
    return s;
}

int buildTree::cmpSubstring(string x, string y)
{
    return x.substr(0,1).compare(y.substr(0,1));
}

string buildTree::trimString(const string &str, const string &whitespace)     //removes leading and trailing white spaces
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
    {
        return "";
    }
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

string buildTree::cleanString(const string &str, const string &fill, const string &whitespace)    //removes excess whitespaces
{
    auto result = trimString(str, whitespace);
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;
        result.replace(beginSpace, range, fill);
        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }
    return result;
}

void buildTree::insert(string newdata)      //insert string into tree
{
    if(root != NULL)
    {
        insert(newdata, root);
    }else{
        root = new node;
        root->str.push_back(newdata);
        root->setString.insert(newdata);
        root->left = NULL;
        root->right = NULL;
    }
}

void buildTree::insert(string newdata, node *leaf)
{
    if(cmpSubstring(newdata,*leaf->str.begin()) < 0)    //If new string is less than string in node.
    {
        if(leaf->left != NULL)
        {
            insert(newdata, leaf->left);
        }else{
            leaf->left = new node;
            leaf->left->str.push_back(newdata);
            leaf->left->setString.insert(newdata);
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    }else if(cmpSubstring(newdata,*leaf->str.begin()) > 0){    //If new string is greater than string in node.
        if(leaf->right != NULL)
        {
            insert(newdata, leaf->right);
        }else{
            leaf->right = new node;
            leaf->right->str.push_back(newdata);
            leaf->right->setString.insert(newdata);
            leaf->right->right = NULL;
            leaf->right->left = NULL;
        }
    }else{                      //If first character of new string matches first character in node.

        if (!leaf->setString.count(newdata))    //If new string is not already in set.
        {
            leaf->str.push_back(newdata);
            leaf->setString.insert(newdata);
        }
    }
}

void buildTree::printCurrentNode(node *leaf, int level, ostream &output)
{
    output << string(2*level, ' ');
    output << (*leaf->str.begin()).substr(0,1) + " ";

    for(deque<string>::iterator i = leaf->str.begin(); i != leaf->str.end(); i++)
    {
        output << *i << " ";
    }
    output << endl;
}

string buildTree::prepareOutputFilename(string outputFilename, string outputFileExtension)
{
    if(outputFilename == "")
    {
        outputFilename = "tree";
    }
    outputFilename = removeFileExtension(outputFilename);
    outputFilename.append(outputFileExtension);

    return outputFilename;
}

void buildTree::printPreorder(string outputFilename)
{
    outputFilename = prepareOutputFilename(outputFilename,".preorder");
    ofstream output(outputFilename);
    printPreorder(root,0,output);
    output.close();
}

void buildTree::printPreorder(node *leaf, int level,ostream& output)
{
    if(leaf != NULL)
    {
        printCurrentNode(leaf, level, output);
        printPreorder(leaf->left,level+1,output);
        printPreorder(leaf->right,level+1,output);
    }
}

void buildTree::printInorder(string outputFilename)
{
    outputFilename = prepareOutputFilename(outputFilename,".inorder");
    ofstream output(outputFilename);
    printInorder(root, 0,output);
    output.close();
}

void buildTree::printInorder(node *leaf, int level, ostream& output)
{
    if(leaf != NULL)
    {
        printInorder(leaf->left, level+1,output);
        printCurrentNode(leaf, level, output);
        printInorder(leaf->right, level+1,output);
    }
}

void buildTree::printPostorder(string outputFilename)
{
    outputFilename = prepareOutputFilename(outputFilename,".postorder");
    ofstream output(outputFilename);
    printPostorder(root,0,output);
    output.close();
}

void buildTree::printPostorder(node *leaf, int level, ostream& output)
{
    if(leaf != NULL)
    {
        printPostorder(leaf->left, level+1,output);
        printPostorder(leaf->right, level+1,output);
        printCurrentNode(leaf, level, output);
    }
}
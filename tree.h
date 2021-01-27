#ifndef INC_4280P0CPP_TREE_H
#define INC_4280P0CPP_TREE_H


typedef class buildTree
{
public:
    buildTree();
    ~buildTree();

    void run1();
    void run2(string inputString);
    void insert(string newdata);
    void destroy_tree();
    void printPreorder(string inputFilename);
    void printInorder(string inputFilename);
    void printPostorder(string inputFilename);

private:
    static void destroy_tree(node *leaf);
    static void insert(string key, node *leaf);
    static void printCurrentNode(node *leaf, int level, ostream &output);
    static void printPreorder(node *leaf, int level, ostream& output);
    static void printInorder(node *leaf, int level, ostream& output);
    static void printPostorder(node *leaf, int level, ostream& output);
    static int cmpSubstring(string x, string y);
    static string appendFileExtension(string s);
    static string removeFileExtension(string s);
    static string prepareOutputFilename(string outputFilename, string outputFileExtension);
    static string trimString(const string &str, const string &whitespace = " \t");
    static string cleanString(const string &str, const string &fill = " ", const string &whitespace = " \t");

    node *root;
}buildTree;

#endif
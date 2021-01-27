#ifndef INC_4280P0CPP_NODE_H
#define INC_4280P0CPP_NODE_H


typedef struct node
{
    set<string> setString;
    deque<string> str;
    node *left;
    node *right;
}node;

#endif
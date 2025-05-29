#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>

using namespace std;

typedef int Info;
struct Node
{
  Node* left,
      * right;
  Info info;
};

void PrintTree(Node* root, int level);
void PrintTreeWithHighlight(Node* root, int level, int highlight_value);
int Height(Node* root);
int BFactor(Node* root);
void RightRotation(Node*& root);
void LeftRotation(Node*& root);
Node* FindMin(Node* root);
void DeleteTree(Node*& root);
void PostfixOrderWithHighlight(Node* root, int highlight_value);
void PostfixOrderWithMin(Node* root, Node*& minNode);
Node* CreateTree(int nodeCount);
Node* BinarySearchInsert(Node*& root, Info value, bool& found);
void BalanceHeight(Node*& root);
Node* BinarySearchDelete(Node* root, Info value);
void FindFirstMin(Node* root);
void showMenu();

#endif //FUNCTIONS_H
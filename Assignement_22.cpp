/*
<aside>
💡 Question-1:

Given a Binary Tree (Bt), convert it to a Doubly Linked List(DLL). The left and right pointers in nodes are to be used as previous and next pointers respectively in converted DLL. The order of nodes in DLL must be the same as in Inorder for the given Binary Tree. The first node of Inorder traversal (leftmost node in BT) must be the head node of the DLL.

</aside>
*/

#include <bits/stdc++.h>
using namespace std;
struct node {
    int data;
    node* left;
    node* right;
};

void BinaryTree2DoubleLinkedList(node* root, node** head)
{
    
    if (root == NULL)
        return;
    static node* prev = NULL;
    BinaryTree2DoubleLinkedList(root->left, head);
    if (prev == NULL)
        *head = root;
    else {
        root->left = prev;
        prev->right = root;
    }
    prev = root;
    BinaryTree2DoubleLinkedList(root->right, head);
}

/*
<aside>
💡 Question-2

A Given a binary tree, the task is to flip the binary tree towards the right direction that is clockwise. See the below examples to see the transformation.

In the flip operation, the leftmost node becomes the root of the flipped tree and its parent becomes its right child and the right sibling becomes its left child and the same should be done for all left most nodes recursively.

</aside>
*/

node* flipBinaryTree(node* root)
{
    // Base cases
    if (root == NULL)
        return root;
    if (root->left == NULL && root->right == NULL)
        return root;
    node* flippedRoot = flipBinaryTree(root->left);

    root->left->left = root->right;
    root->left->right = root;
    root->left = root->right = NULL;
 
    return flippedRoot;
}

/*
<aside>
💡 Question-3:

Given a binary tree, print all its root-to-leaf paths without using recursion. For example, consider the following Binary Tree.

Input:

        6
     /    \
    3      5
  /   \     \
 2     5     4
     /   \
    7     4

Output:

There are 4 leaves, hence 4 root to leaf paths -
  6->3->2
  6->3->5->7
  6->3->5->4
  6->5>4

</aside>
*/

void printPaths(node* node)
{
    int path[1000];
    printPathsRecur(node, path, 0);
}
void printArray(int ints[], int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        cout << ints[i] << " ";
    }
    cout<<endl;
}
void printPathsRecur(node* node, int path[], int pathLen)
{
    if (node == NULL)
        return;

    path[pathLen] = node->data;
    pathLen++;
     
   
    if (node->left == NULL && node->right == NULL)
    {
        printArray(path, pathLen);
    }
    else
    {
        printPathsRecur(node->left, path, pathLen);
        printPathsRecur(node->right, path, pathLen);
    }
}
/*
Given Preorder, Inorder and Postorder traversals of some tree. Write a program to check if they all are of the same tree.

**Examples:**

Input : 

        Inorder -> 4 2 5 1 3
        Preorder -> 1 2 4 5 3
        Postorder -> 4 5 2 3 1
Output : 

Yes
Explanation : 

All of the above three traversals are of
the same tree 

                           1
                         /   \
                        2     3
                      /   \
                     4     5

Input : 

        Inorder -> 4 2 5 1 3
        Preorder -> 1 5 4 2 3
        Postorder -> 4 1 2 3 5
Output : 

No
*/

int search(int arr[], int strt, int end, int value)
{
    for (int i = strt; i <= end; i++)
    {
        if(arr[i] == value)
            return i;
    }
}
 

node* buildTree(int in[], int pre[], int inStrt,
                                      int inEnd)
{
    static int preIndex = 0;
  
    if(inStrt > inEnd)
        return NULL;
    node *tNode = new node(pre[preIndex++]);
    if (inStrt == inEnd)
        return tNode;
    int inIndex = search(in, inStrt, inEnd, tNode->data);

    tNode->left = buildTree(in, pre, inStrt, inIndex-1);
    tNode->right = buildTree(in, pre, inIndex+1, inEnd);
  
    return tNode;
}
 

int checkPostorder(node* node, int postOrder[], int index)
{
    if (node == NULL)
        return index;
    index = checkPostorder(node->left,postOrder,index);

    index = checkPostorder(node->right,postOrder,index);   

    if (node->data == postOrder[index])
        index++;
    else
        return -1;
 
    return index;
}
 
int main()
{
    int inOrder[] = {4, 2, 5, 1, 3};
    int preOrder[] = {1, 2, 4, 5, 3};
    int postOrder[] = {4, 5, 2, 3, 1};
 
    int len = sizeof(inOrder)/sizeof(inOrder[0]);
    node *root = buildTree(inOrder, preOrder, 0, len - 1);
    int index = checkPostorder(root,postOrder,0);
    if (index == len)
        cout << "Yes";
    else
        cout << "No";
 
    return 0;
}
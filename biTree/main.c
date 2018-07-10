#include <stdio.h>
#include <stdlib.h>

typedef char elementT;

typedef struct biTreeNode
{
    elementT data;
    struct biTreeNode *lChild; //left child
    struct biTreeNode *rChild; //right child
}biTreeNodeT;


/*
 * Test data, input
 * HDB#A##C##G#FE###
 * ABDH###E##CF##G##
 * ABDH##I##E#J##CF#K##G##
*/


/*Create the binary tree: first order bitree*/
biTreeNodeT *createBiTree(elementT *e, int *i)
{
    biTreeNodeT *bt = NULL;

    if(e[(*i)++] != '#') //Note: This is a recursive implementation, pointer i should not be added
    {
        bt = (biTreeNodeT *)malloc(sizeof(biTreeNodeT));
        bt->data = e[*i - 1];
        bt->lChild = createBiTree(e, i);
        bt->rChild = createBiTree(e, i);
    }

    return bt;
}

/*Insert a node:
 * The new node will be compared with the root.
 * if new node is bigger than root, insert it as left child.
 * if the new node is less than root, insert it as right child.
 * recursive until insert the new node.
*/
biTreeNodeT *insertBiTreeNode(biTreeNodeT *bt, biTreeNodeT *node)
{
    if(bt != NULL)
    {
        if(node->data < bt->data)
        {
            bt->lChild = insertBiTreeNode(bt->lChild, node);
        }
        else
        {
            bt->rChild = insertBiTreeNode(bt->rChild,node);
        }

    }
    else
    {
        bt = node;
    }

    return bt;
}

/*Get MAX bi Tree depth*/
int maxBiTreeDepth(biTreeNodeT *bt)
{
    if(bt != NULL)
    {
        if(bt->lChild == NULL && bt->rChild ==NULL)
        {
            return 1;
        }

        int lDepth = maxBiTreeDepth(bt->lChild) + 1; //+root
        int rDepth = maxBiTreeDepth(bt->rChild) + 1;//+root
        return (lDepth>rDepth)?lDepth:rDepth; //Get the max one
    }

    return 0;
}

/*Get min bi tree depth*/
int minBiTreeDepth(biTreeNodeT *bt)
{

    if (bt != NULL)
    {
        if(bt->lChild == NULL && bt->rChild ==NULL)
        {
            return 1;
        }  

        int lDepth = minBiTreeDepth(bt->lChild) + 1; //+root
        int rDepth = minBiTreeDepth(bt->rChild) + 1;//+root

        lDepth = (lDepth==1)?INT_MAX:lDepth; //if depth =1, it means the node does not have left child
        rDepth = (rDepth==1)?INT_MAX:rDepth;

        return (lDepth>rDepth)?rDepth:lDepth; //Get the min one        
    }

    return 0;
}

/*Preorder: Root-Left-Right*/
void preOrderBiTree(biTreeNodeT *bt)
{
    if(bt !=NULL)
    {
        printf("%c", bt->data);
        preOrderBiTree(bt->lChild);
        preOrderBiTree(bt->rChild);
    }
}

/*In order:Left-Root-Right*/
void inOrderBiTree(biTreeNodeT *bt)
{
    if(bt != NULL)
    {
        inOrderBiTree(bt->lChild);
        printf("%c", bt->data);
        inOrderBiTree(bt->rChild);
    }
}

/*Post order: Left-Right-Root*/
void postOrderBiTree(biTreeNodeT *bt)
{
    if(bt != NULL)
    {
        postOrderBiTree(bt->lChild);
        postOrderBiTree(bt->rChild);
        printf("%c",bt->data);
    }
}

/*Main function*/
int main() 
{
    int i = 0;
    printf("Create BiTree, inout the string:\n");
    char cStr[100];
    gets(cStr);
    biTreeNodeT *bt = createBiTree(cStr, &i);
    printf("Bi tree creation is done!\n\n");

    printf("Pre order the bi tree:\n");
    preOrderBiTree(bt);
    printf("\n\n");
    printf("In order the bi tree:\n");
    inOrderBiTree(bt);
    printf("\n\n");
    printf("Post order the bi tree:\n");
    postOrderBiTree(bt);
    printf("\n\n");

    printf("Max Depth: %d\n", maxBiTreeDepth(bt));
    printf("Min Depth: %d\n", minBiTreeDepth(bt));

    printf("\nInsert a node:\n");
    biTreeNodeT newNode =
    {
        .data = 'L'
    };
    printf("Node data:'%c'\n",newNode.data);
    bt = insertBiTreeNode(bt, &newNode);
    printf("Pre order the bi tree:\n");
    preOrderBiTree(bt);
    printf("\n\n");
    printf("Max Depth: %d\n", maxBiTreeDepth(bt));
    printf("Min Depth: %d\n", minBiTreeDepth(bt));
    return 0;
}

/* Run result:
C:\Users\hongf\CLionProjects\study_02_bitree\cmake-build-debug\study_02_bitree.exe
Create BiTree, inout the string:
ABDH##I##E#J##CF#K##G##
ABDH##I##E#J##CF#K##G##
Bi tree creation is done!

Pre order the bi tree:
ABDHIEJCFKG

In order the bi tree:
HDIBEJAFKCG

Post order the bi tree:
HIDJEBKFGCA

Max Depth: 4
Min Depth: 3

Insert a node:
Node data:'L'
Pre order the bi tree:
ABDHIEJCFKGL

Max Depth: 4
Min Depth: 4

Process finished with exit code 0

 */
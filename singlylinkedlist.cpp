#include <iostream>
using namespace std;

struct listNode
{
    int value;
    listNode *next;
};

listNode *head = NULL; 

void appendNode(int num)
{
    listNode *newNode, *nodeptr;
    newNode = new listNode;
    newNode->value = num;
    newNode->next = NULL;

    if (head == NULL)
        head = newNode;
    else
    {
        nodeptr = head;
        while (nodeptr->next != NULL)
        {
            nodeptr = nodeptr->next;
        }
        nodeptr->next = newNode;
    }
}

void insertNode(int num)
{
    listNode *newNode, *nodeptr, *previousNode;
    newNode = new listNode;
    newNode->value = num;
    previousNode = NULL;
    if (head == NULL)
    {
        head = newNode;
        newNode->next = NULL;
    }
    else
    {
        nodeptr = head;
        while (nodeptr->next != NULL && nodeptr->value < num)
        {
            previousNode = nodeptr;
            nodeptr = nodeptr->next;
        }
        if (previousNode == NULL)
        {
            head = newNode;
            newNode->next = nodeptr;
        }
        else
        {
            previousNode->next = newNode;
            newNode->next = nodeptr;
        }
    }
}

void deleteNode(int num)
{
    listNode *nodeptr, *previousNode;
    if (head == NULL)
    {
        return;
    }
    if (head->value == num)
    {
        nodeptr = head;
        head = head->next;
        delete nodeptr;
    }
    else
    {
        nodeptr = head;
        while (nodeptr != NULL && nodeptr->value != num)
        {
            previousNode = nodeptr;
            nodeptr = nodeptr->next;
        }
        previousNode->next = nodeptr->next;
        delete nodeptr;
    }
}
void printList()
{
    listNode *nodeptr = head;
    while (nodeptr != NULL)
    {
        cout << nodeptr->value << ",";
        nodeptr = nodeptr->next;
    }
    cout << endl;
}
int main()
{
    appendNode(2);
    appendNode(4);
    appendNode(6);
    printList();
    insertNode(5);
    // printList();
    deleteNode(4);
    insertNode(4);
    insertNode(8);
    printList();
}
/* this one also addds at the end

void insertNode(int num)
{
    listNode *newNode, *nodeptr, *previousNode;

    newNode = new listNode;
    newNode->value = num;
    newNode->next = NULL;

    previousNode = NULL;
    nodeptr = head;

    // Case 1: Empty list
    if (head == NULL)
    {
        head = newNode;
        return;
    }

    // Traverse until we find the right spot
    while (nodeptr != NULL && nodeptr->value < num)
    {
        previousNode = nodeptr;
        nodeptr = nodeptr->next;
    }

    // Case 2: Insert at the beginning
    if (previousNode == NULL)
    {
        newNode->next = head;
        head = newNode;
    }
    // Case 3: Insert in the middle OR at the end
    else
    {
        previousNode->next = newNode;
        newNode->next = nodeptr;  // if nodeptr == NULL, newNode goes at the end
    }
}
*/

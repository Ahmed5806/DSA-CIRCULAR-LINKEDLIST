#include <iostream>
using namespace std;

struct listNode
{
    int value;
    listNode *next;
    listNode *tail; // pointer to previous node
};

listNode *head = NULL;

void insertNode(int num)
{
    listNode *newNode, *nodeptr;
    newNode = new listNode;
    newNode->value = num;
    newNode->next = NULL;
    newNode->tail = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else if (num < head->value)
    {
        newNode->next = head;
        head->tail = newNode;
        head = newNode;
    }
    else
    {
        nodeptr = head;
        while (nodeptr->next != NULL && nodeptr->next->value < num)
        {
            nodeptr = nodeptr->next;
        }
        newNode->next = nodeptr->next;
        newNode->tail = nodeptr;
        nodeptr->next = newNode;
        if (newNode->next != NULL)
        {
            newNode->next->tail = newNode;
        }
    }
}

void deleteNode(int num)
{
    listNode *nodeptr;
    if (head == NULL)
    {
        return;
    }

    nodeptr = head;

    // Delete head node
    if (head->value == num)
    {
        listNode *temp = head;
        head = head->next;
        if (head != NULL)
        {
            head->tail = NULL;
        }
        delete temp;
        return;
    }

    // Find node to delete
    while (nodeptr != NULL && nodeptr->value != num)
    {
        nodeptr = nodeptr->next;
    }

    if (nodeptr == NULL)
    {
        return; // value not found
    }

    // If node is not last node
    if (nodeptr->next != NULL)
    {
        nodeptr->next->tail = nodeptr->tail;
    }

    // Connect previous node to next node
    if (nodeptr->tail != NULL)
    {
        nodeptr->tail->next = nodeptr->next;
    }

    delete nodeptr;
}

void printList()
{
    if (head == NULL)
    {
        cout << "List is empty." << endl;
        return;
    }

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
    insertNode(10);
    insertNode(5);
    insertNode(20);
    insertNode(15);

    cout << "Doubly Linked List: ";
    printList();

    deleteNode(10);
    cout << "After deleting 10: ";
    printList();

    deleteNode(5);
    cout << "After deleting 5: ";
    printList();

    deleteNode(20);
    cout << "After deleting 20: ";
    printList();

    deleteNode(15);
    cout << "After deleting 15 (should be empty): ";
    printList();

    return 0;
}

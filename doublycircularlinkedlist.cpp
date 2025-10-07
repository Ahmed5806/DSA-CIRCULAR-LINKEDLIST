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
        head->next = head; // circular forward link
        head->tail = head; // circular backward link
    }
    else if (num < head->value)
    {
        nodeptr = head->tail; // last node
        newNode->next = head;
        newNode->tail = nodeptr;
        nodeptr->next = newNode;
        head->tail = newNode;
        head = newNode;
    }
    else
    {
        nodeptr = head;
        while (nodeptr->next != head && nodeptr->next->value < num)
        {
            nodeptr = nodeptr->next;
        }
        newNode->next = nodeptr->next;
        newNode->tail = nodeptr;
        nodeptr->next->tail = newNode;
        nodeptr->next = newNode;
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

    // Deleting the head node
    if (head->value == num)
    {
        // Only one node
        if (head->next == head)
        {
            delete head;
            head = NULL;
            return;
        }
        else
        {
            listNode *last = head->tail;
            listNode *temp = head;
            head = head->next;
            head->tail = last;
            last->next = head;
            delete temp;
            return;
        }
    }

    nodeptr = head->next;
    while (nodeptr != head && nodeptr->value != num)
    {
        nodeptr = nodeptr->next;
    }

    if (nodeptr == head)
    {
        return; // value not found
    }

    nodeptr->tail->next = nodeptr->next;
    nodeptr->next->tail = nodeptr->tail;
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
    do
    {
        cout << nodeptr->value << ",";
        nodeptr = nodeptr->next;
    } while (nodeptr != head);
    cout << endl;
}

int main()
{
    insertNode(10);
    insertNode(5);
    insertNode(20);
    insertNode(15);

    cout << "Doubly Circular Linked List: ";
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

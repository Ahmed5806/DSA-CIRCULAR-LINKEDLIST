#include <iostream>
using namespace std;

struct listNode
{
    int value;
    listNode *next;
};

listNode *head = NULL;

void insertNode(int num)
{
    listNode *newNode, *nodeptr, *previousNode;
    newNode = new listNode;
    newNode->value = num;
    newNode->next = NULL;
    previousNode = NULL;

    if (head == NULL)
    {
        head = newNode;
        newNode->next = head; // circular link
    }
    else if (num < head->value)
    {
        nodeptr = head;
        while (nodeptr->next != head)
        {
            nodeptr = nodeptr->next;
        }
        nodeptr->next = newNode;
        newNode->next = head;
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
        nodeptr->next = newNode;
    }
}

void deleteNode(int num)
{
    listNode *nodeptr, *previousNode;
    if (head == NULL)
    {
        return;
    }

    nodeptr = head;
    previousNode = NULL;

    // Deleting the head node case
    if (head->value == num)
    {
        if (head->next == head)
        {
            delete head;
            head = NULL;
        }
        else
        {
            nodeptr = head;
            while (nodeptr->next != head)
            {
                nodeptr = nodeptr->next;
            }
            nodeptr->next = head->next;
            listNode *temp = head;
            head = head->next;
            delete temp;
        }
        return;
    }

    nodeptr = head;
    while (nodeptr->next != head && nodeptr->next->value != num)
    {
        nodeptr = nodeptr->next;
    }

    if (nodeptr->next->value == num)
    {
        listNode *temp = nodeptr->next;
        nodeptr->next = temp->next;
        delete temp;
    }
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

    cout << "Circular Linked List: ";
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

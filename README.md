# DSA-UNIVERSITY
Nice — here’s a clear, step-by-step walk through how that circular, sorted, singly linked list code works. I’ll explain each part, show the different cases the functions handle, and then trace the main() example so you can see how the list changes over time.

Quick overview

The list is circular: the last node’s next points back to head.

The list is kept sorted ascending by insertNode().

insertNode() handles creating the node and placing it in the correct spot (so we removed appendNode()).

deleteNode() removes a node (handles head, single-node, and middle deletions).

printList() prints values using a do...while because the list is circular.

Data structure and global
struct listNode
{
    int value;
    listNode *next;
};

listNode *head = NULL;


listNode holds an int and a pointer to the next node.

head is the global pointer to the start of the list. head == NULL means empty.

insertNode(int num) — step by step

Create node

newNode = new listNode; newNode->value = num; newNode->next = NULL;

We allocate memory and store the value.

Empty-list case

if (head == NULL):

Set head = newNode.

Set newNode->next = head; → node points to itself (single-node circular list).

Result: list now contains one node whose next points to itself.

Insert before current head (new smallest)

else if (num < head->value):

We must insert newNode before head and update the last node to point to the new head.

Find the last node: nodeptr = head; while (nodeptr->next != head) nodeptr = nodeptr->next;

Set nodeptr->next = newNode; newNode->next = head; head = newNode;

Why find last node? Because in a circular list the old last node still points to the old head — when head changes we must redirect that last node to the new head.

Insert somewhere after head (middle or end)

else:

Start at nodeptr = head.

Move forward while nodeptr->next != head && nodeptr->next->value < num — this finds the node after which we should insert.

Insert: newNode->next = nodeptr->next; nodeptr->next = newNode;

If nodeptr->next == head after the loop, we are inserting at the end (node becomes new last node pointing back to head).

Note about duplicates: since the loop uses < num, insertion stops before the first equal value, so the new node will be placed before any existing nodes equal to num.

deleteNode(int num) — step by step

Empty list

if (head == NULL) return; — nothing to delete.

Deleting head node

if (head->value == num)

Single-node list: if head->next == head, delete head; head = NULL;

Multiple nodes:

Find last node: nodeptr = head; while (nodeptr->next != head) nodeptr = nodeptr->next;

Point last node to second node: nodeptr->next = head->next;

Move head forward: listNode *temp = head; head = head->next; delete temp;

This preserves the circular property and updates head.

Deleting a non-head node

Otherwise we look for a node whose next contains the target:

nodeptr = head; while (nodeptr->next != head && nodeptr->next->value != num) nodeptr = nodeptr->next;

If nodeptr->next->value == num then:

temp = nodeptr->next; nodeptr->next = temp->next; delete temp;

If the loop terminates because nodeptr->next == head, the value wasn’t found — function does nothing.

Notes:

The code never checks for nullptr accesses because in a circular list next is never NULL for non-empty lists.

Deleting a non-existent value simply results in no action.

printList()
if (head == NULL) { cout << "List is empty." << endl; return; }

listNode *nodeptr = head;
do {
    cout << nodeptr->value << ",";
    nodeptr = nodeptr->next;
} while (nodeptr != head);
cout << endl;


If empty, prints a message.

Otherwise uses do...while to visit head first and continue until it returns to head (prints every node once).

Trace the main() example (state after each operation)

Start: head = NULL.

insertNode(10);

Empty case → list: [10] (10 -> 10)

insertNode(5);

5 < head(10) → insert before head. Find last (10) and reconnect:

list: [5 -> 10 -> back to 5] (head = 5)

insertNode(20);

Insert after 10 (end).

list: [5 -> 10 -> 20 -> back to 5]

insertNode(15);

Insert between 10 and 20.

list: [5 -> 10 -> 15 -> 20 -> back to 5]

printList() prints: 5,10,15,20,

Now deletes:

deleteNode(10);

Finds node whose next is 10 (that is node 5), removes 10.

list: [5 -> 15 -> 20 -> back to 5]

deleteNode(5);

Head equals 5. Find last node (20) and set 20->next = head->next (15), set head = 15, delete old head.

list: [15 -> 20 -> back to 15] (head = 15)

deleteNode(20);

Remove 20 (node whose next was 20 is 15). After removal:

list: [15] (15 -> 15)

deleteNode(15);

Head equals 15 and head->next == head (single node) → delete and set head = NULL.

list: empty

Complexity

insertNode() — O(n) worst-case (may need to scan to last or to insertion point).

deleteNode() — O(n) worst-case (may need to scan whole list).

printList() — O(n).

Edge cases, safety notes and small improvements

Memory: code uses new and delete correctly. If new fails it will throw bad_alloc (not handled here).

Deleting a non-existent value: function does nothing (silent). You could return a bool to indicate success/failure if you want feedback.

previousNode unused: your previousNode variable is declared in some places but not used — you can remove it to clean up.

Robustness improvements: add a find() function, return success status from deleteNode(), add clear() to free the entire list, or add error messages on failed deletes or inserts.

Style: set newNode->next = nullptr; then overwrite as needed — it’s clearer but not required.
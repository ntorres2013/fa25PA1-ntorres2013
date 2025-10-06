#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

// Node for Circular Linked List
template<typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& val) : data(val), next(nullptr) {}
};

// Circular Linked List
template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    bool empty() const { return head == nullptr; }
    int size() const { return count; }

    void append(const T& value)
    {
        Node<T>* newnode = new Node<T>(value);

        if(empty())
//        Case 1: List is empty
        {
            head = newnode;     // Set head endpoint
            tail = newnode;     // Set tail endpoint
            tail->next = head;  //   Tail circling and pointing back to head rather than to nullptr
        }
        else
//        Case 2: List is not empty
        {
            tail->next = newnode;   // Previous tail points to new node
            tail = newnode;         // Set tail to new node
            tail->next = head;      // Close the circularly linked list as seen in SP25 List ADT.pdf in modules
        }
        count++;    // Increment count (append)
    }

    T& front()
    {
        return head->data;      // Returning the data at front, which would be at the head
    }

    void set_front(const T& value)
    {
        head->data = value;     // Setting the parameter value input as front
    }

    void pop_front()
    {
//        Case 1: Empty List
        if(empty())
        {
            return;
        }

//        Case 2: Single Node
        if(head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
//        Case 3: Multiple nodes
        else
        {
            Node<T>* temp = head;   // Create temporary
            head = head->next;  // Move head forward
            tail->next = head;  // Loop, keeping linked list circular
            delete temp;        // Pop
        }
        count--;    // Decrement count (popping off)
    }

    void rotate()
    {
        head = head->next;
        tail = tail->next;
    }

    void clear()
    {
        if(empty())
        {
            return;
        }
        tail->next = nullptr;   // Discontinue circularly linked list for iteration

        Node<T>* curr = head;   // Pointer used to iterate
        while(curr != nullptr)  // Until it iterates from beginning to end
        {
            Node<T>* nextnode = curr->next;     // Points to next node before deleting current
            delete curr;        // Delete current node data
            curr = nextnode;     // Current set to next node in list
        }

        head = nullptr;
        tail = nullptr;
        count = 0;      // Set count to zero (cleared list)
    }

    void display() const
    {
        if(empty())
        {
            cout << "[] (circular)" << endl;
            return;
        }

        Node<T>* curr = head;
        cout << "[";

        for(int i = 0; i < count; i++)
        {
            cout << "Robot(" << curr->data.name << ", Battery=" << curr->data.battery << ")";
            if (i != count - 1)
            {
                cout << " -> ";
            }
            curr = curr->next;
        }
        cout << "] (circular)" << endl;
    }

    void splitIntoTwo(LinkedList<T>& first, LinkedList<T>& second)
    {
        if(empty())
//        Case 1: Linked List is empty
        {
            return;
        }

        if(count == 1)
//        Case 2: Linked List has one single node. No split necessary
        {
//            Since it is 1 node, it would go into the first half - first list. Must empty the original
            first.head = head;      // Move to first list
            first.tail = tail;      // Move to first list
            first.tail->next = first.head;  //   Tail circling and pointing back to head to maintain circularity
            first.count = 1;  // Update count for first list

//            After split, the original list should be empty (ownership transferred)
            head = nullptr;
            tail = nullptr;
            count = 0;

            return;
        }

//        Case 3: Multiple nodes, enough to split into 2 lists
        int split = (count + 1) / 2;    // Obtain midpoint/split section
        Node<T>* curr = head;           // Iterate with curr starting at the head

//        First Linked List Split. Beginning to midpoint
        for (int i = 0; i < split; i++)
        {
            Node<T>* next = curr->next;        // Save pointer to next node

            if (first.empty())
            {
//                Current node goes into first linked list
                first.head = curr;
                first.tail = curr;
                first.tail->next = first.head; //   Tail circling and pointing back to head to maintain circularity
            }
            else
            {
                first.tail->next = curr;        // Set previous tail to current node
                first.tail = curr;              // Update tail to current
                first.tail->next = first.head; //   Tail circling and pointing back to head to maintain circularity
            }

            curr = next;        // Move to next node
        }
        first.count = split;    // Update first list count

        //        Second Linked List Split. Midpoint to end
        for (int i = split; i < count; i++)
        {
            Node<T>* next = curr->next;     // Save pointer to next node

            if (second.empty())
            {
                second.head = curr;
                second.tail = curr;
                second.tail->next = second.head; //   Tail circling and pointing back to head to maintain circularity
            }
            else
            {
                second.tail->next = curr;       // Set previous tail to current node
                second.tail = curr;             // Update tail to current
                second.tail->next = second.head; //   Tail circling and pointing back to head to maintain circularity
            }

            curr = next;        // Move to next node
        }
        second.count = count - split;       // Update second list count

//        After split, the original list should be empty (ownership transferred)
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    void mergeWith(LinkedList<T>& other)
    {
        //        Case 1: This linked list is empty. No merge necessary
        if(other.empty())
        {
            return;
        }

//        Case 2: The outside linked list is empty. Merge this one into the outside one
        if(empty())
        {
            head = other.head;      // Set that head to this one
            tail = other.tail;      // Set that tail to this one
            count = other.count;    // Set that count to this one

            other.head = nullptr;   // Set other list head to nullptr
            other.tail = nullptr;   // Set other list tail to nullptr
            other.count = 0;        // Set the count of nodes to zero
            return;
        }

//        Case 3: Both linked lists contain at least one node each
        tail->next = other.head;      // Connects the last node of the first list to the first node of the second list
        other.tail->next = head;       // Loop back to the start
        tail = other.tail;          // Updates the tail of this list
        count += other.count;       // Merges the count
        other.head = nullptr;   // Set other list head to nullptr
        other.tail = nullptr;   // Set other list tail to nullptr
        other.count = 0;        // Set the count of nodes to zero
    }
};

#endif
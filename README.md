# Programming Assignment 1 – Robot Relay Ring
# Author : [Niko Torres]
## Overview
- Circular Linked List implementation
- Robot Relay Ring (round-robin scheduler)
- Split a Circular Linked List problem

## What I Implemented
- [x] Append
- [x] Pop front
- [x] Rotate
- [x] Display
- [x] Split
- [x] Merge
- [x] Run turns

## How the Circular List Works
The circular linked list uses "tail->next == head" to maintain the circular linked list loop by having the last node point back to the first node. Once it is at the tail, it will point back to the head, rather than pointing to nullptr. In this way, it would go like 1 2 3 1 2 3 1... rather than in a single linked list where it goes 1 2 3 then ends at nullptr. We keep circularity by forming a continuous loop, where the tail keeps pointing to the head, even as updated for appending, removing, rotating, etc.

## Why Circular Linked List Fits a Relay
A circular linked list fits a relay because of how it allows each robot to run a turn with the functions we were given to implement. Through the ring, the list will eventually reach the last robot (tail) then return to the first (head). This makes it fair to each robot, where turns are being taken and tracked and accounted for.

## Comparison
Head only list: the linked list only includes and keeps track of the first node (head). Append O(n): Traverse to last node, link new node at the end. Delete O(1): Update head to point to next node, delete the old head. Traverse O(n): starts from the head all the way to the end.

Tail pointer list: the linked list would include and keep track of the first and last node (head and tail). Append O(1): Add new node directly after tail, update tail pointer. Delete O(1): Update head to point to next node, delete the old head. Traverse O(n): Starts from the head all the way to the tail.

Circular list: the linked list includes and keeps track of head and tail, where the last node will loop and point back to the first node. Append O(1): Add new node after tail, update tail, set tail->next to head. Delete O(1): Update head to next node, update tail->next to new head, delete old head. Traverse O(n): Start from head and loop through all nodes.

## Split Problem
The split function splits a circular linked list into 2 separate linked lists. First list will contain the first half of the original list, second list will contain the remaining half of the original list. After splitting into the 2 new lists, original should be empty.
Even list example: if there are 4 robots, the first 2 robots will go in the first list, and the last 2 robots will go in the second list.
Odd list example: if there are 5 robots, the first 3 robots will go in the first list, and the last 2 robots will go in the second list.
This is due to the fact of this following line: int split = (count + 1) / 2;. When it is an odd number of nodes, the extra will split into the first.

## Reflection
- The hardest bug I faced was documented in my devlog. This happened for my showRing() and display() functions where I was getting errors calling display from showRing.
- I fixed this by writing a new display function. I kept the previous display() but would write a second one to overload the << operator for robot in order to display properly.
- I learned that there is not always a simple and easy fix to things. It took me a very long time of looking through my code, making unnecessary changes, and breaking my project to figure out the answer. And I found the answer from Professor Manju's responses in discord server. She gave a link for 3 options to fixing this common error, and I chose to write another display function. I learned that stepping back and seeking other options rather than forcing a fix/solution is a better option to debug your problems.

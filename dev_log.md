# Developer Log – Programming Assignment 1

## Entry 1
**What I tried:**  
We created a templated circularly linked list with private data members Node<T>* head, Node<T>* tail, and int count. This linked list class included functions called empty, size, append, front, set_front, pop_front, rotate, clear, display, split, merge, etc.

**What broke:**  
After what I initially thought was a completed circularly linked list, I wanted to test the linked list along with functionality and make sure it worked properly. Broken functions included size, display, splitintotwo, mergewith, append, etc. The size of the linked list would always return a value of 0. The display function would not output correctly.

**Why it happened:**  
It took me a while to realize what happened. I had to look through my code line by line multiple times just to catch my mistake. Though I knew that the linked list had 3 data members, I completely forgot and ignored the int count. It didn't cross my mind to update count for the necessary functions to keep my linked list working.

**Fix:**  
In order to fix this, I had to update the count for the functions that required int count. For append, I would increment by 1 when adding a node. For pop_front, I would decrement by 1 when removing a node. For clear, I would set the value of count to 0. For mergewith, I would need to update count because it is needed to add both sizes together.

**Proof it works:**  
It works because when testing in main, I appended 5 int variables. When calling and printing size, it would output 5. With the rest of the updated functions as well, they now output correctly.

---

## Entry 2
**What I tried:**
For the circular linked list, I was on the final function called mergeWith. The instructions said to merge another circular linked list with this one. I tried coding this with 3 edge cases; empty linked list, the other is empty but this one isn't, and both linked lists contain nodes. 

**What broke:**
After testing this function in main, the output of this function broke. For example, I had 4 int values, 2 per list. After merging, the size should output 4 nodes. Instead, I got some garbage large int value that should not be there.

**Why it happened:**
This happened because I had an error in my edge cases for mergeWith. Inside of this function, I would call the clear function which broke my code. Calling clear would delete my nodes from the list, which is why it was not outputting the correct size, because not every node was accounted for.

**Fix:**
I fixed this error by updating the code in my function. Instead of calling the clear function, I would write code manually in order to not delete what I need for merging. I would set the other linked lists pointers to nullptr and their count to 0. This would clear the linked list safely without deleting it before using.

**Proof it works:**
It works because when testing in main, I created 2 linked lists. When merging both nodes to one of the linked lists, it displays each node properly along with the correct size.

## Entry 3
**What I tried:**
For showRing() function in main, it asks to call the display() function from LinkedList. showRing was meant to output the robot rings using the display function. I tried simply calling the function using a dot operator.

**What broke:**
This broke my function, specifically the line where I am calling display using the dot operator. This is broken because it is not coded correctly and will not have the proper functionalities.

**Why it happened:**
This happened because of the way I have my display function set up and because of how I am calling it.

**Fix:**
The fix for this was found from our discord. I looked through the faq section and saw that you had 3 ways to handle this case. I chose the 3rd way, which was just to write another display function for the class. Professor Manju said an option was to make it truly data independent and overload the << operator. This was something I was not familiar with, but I followed the example code from the website as closely as possible.

**Proof it works:**
This works now because there are no errors in showRing with relation to the display function. Whereas earlier on, there was some templating/permission issues. I have tested this and it now works properly.
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstring>

using namespace std;

struct Node
{
    Node* left = nullptr;
    Node* middle = nullptr;
    Node* right = nullptr;
    int frequency;
    char c;
};

// Data structure for Min Heap
struct PriorityQueue
{
private:
    // vector to store heap elements
    vector<Node*> A;

    // return parent of A[i]
    int PARENT(int i)
    {
        return (i - 1) / 2;
    }

    // return left child of A[i]
    int LEFT(int i)
    {
        return (2 * i + 1);
    }

    // return right child of A[i]
    int RIGHT(int i)
    {
        return (2 * i + 2);
    }

    // Recursive Heapify-down algorithm
    // the node at index i and its two direct children
    // violates the heap property
    void heapify_down(int i)
    {
        // get left and right child of node at index i
        int left = LEFT(i);
        int right = RIGHT(i);

        int smallest = i;
        // compare A[i] with its left and right child
        // and find smallest value
        if (left < size() && A[left]->frequency < A[i]->frequency)
            smallest = left;

        if (right < size() && A[right]->frequency < A[smallest]->frequency)
            smallest = right;
        // swap with child having lesser value and
        // call heapify-down on the child
        if (smallest != i) {
            swap(A[i], A[smallest]);
            heapify_down(smallest);
        }
    }
    // Recursive Heapify-up algorithm
    void heapify_up(int i)
    {
        // check if node at index i and its parent violates
        // the heap property
        if (i && A[PARENT(i)]->frequency > A[i]->frequency)
        {
            // swap the two if heap property is violated
            swap(A[i], A[PARENT(i)]);

            // call Heapify-up on the parent
            heapify_up(PARENT(i));
        }
    }

public:
    // return size of the heap
    unsigned int size()
    {
        return A.size();
    }

    // function to check if heap is empty or not
    bool empty()
    {
        return size() == 0;
    }

    // insert key into the heap
    void push(Node *key)
    {
        // insert the new element to the end of the vector
        A.push_back(key);

        // get element index and call heapify-up procedure
        int index = size() - 1;
        heapify_up(index);
    }
    // function to remove element with lowest priority (present at root)
    void pop()
    {
        try {
            // if heap has no elements, throw an exception
            if (size() == 0)
                throw out_of_range("Vector<X>::at() : "
                                   "index is out of range(Heap underflow)");

            // replace the root of the heap with the last element
            // of the vector
            A[0] = A.back();
            A.pop_back();

            // call heapify-down on root node
            heapify_down(0);
        }
            // catch and print the exception
        catch (const out_of_range& oor) {
            cout << "\n" << oor.what();
        }
    }

    // function to return element with lowest priority (present at root)
    Node* top()
    {
        try {
            // if heap has no elements, throw an exception
            if (size() == 0)
                throw out_of_range("Vector<X>::at() : "
                                   "index is out of range(Heap underflow)");

            // else return the top (first) element
            return A.at(0);	// or return A[0];
        }
            // catch and print the exception
        catch (const out_of_range& oor) {
            cout << "\n" << oor.what();
        }
    }
};

void PreOrderTraversal(Node *node);
Node* createHuffman(PriorityQueue &pq);
void countSort(char arr[],PriorityQueue &pq);

// Min Heap C++ Implementation
int main()
{
    PriorityQueue pq;
    char arr[] = "FAST NUCES LAHORE";
    countSort(arr,pq);

    if(pq.size() % 2 == 0) //if there are even number of nodes, there will be a internal node with 2 children. We can't allow that.
    {
        Node *n = new Node;
        n->c = '#';
        n->frequency = 0;
        pq.push(n);
    }

    Node *n = createHuffman(pq); //root
    cout<<" @ represents character of the merged node."<<endl;
    cout<<" # represents character of node created to make total number of nodes odd.\n"<<endl;
    cout<<"Priority Queue size: "<<pq.size()<<endl;
    cout<<"Frequency of Root: "<<n->frequency<<endl;
    cout<<"Character of Root: "<<n->c<<endl;
    cout<<endl;

    PreOrderTraversal(n);
    return 0;
}

Node *createHuffman(PriorityQueue &pq)
{
    int n = pq.size();

    for(int i=0; i<n/2; i++) //0(N). Priority Queue operations take O(log(N)). Hence, complexity = O(N * log(N))
    {
        Node *z = new Node;
        z->c = '@';
        z->left = pq.top();
        pq.pop();
        z->middle = pq.top();
        pq.pop();
        z->right = pq.top();
        pq.pop();
        z->frequency = (z->left->frequency) + (z->middle->frequency) + (z->right->frequency);
        pq.push(z);
    }
    return pq.top();
}

void countSort(char arr[],PriorityQueue &pq)
{
    int RANGE = 255;
    Node *n;

    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));

    // Store count of each character
    for(i = 0; arr[i]; ++i)
        ++count[arr[i]];

    for(int i=0; i<256; i++)
    {
        if(count[i] != 0)
        {
            n = new Node;
            n->c = (char) i;
            n->frequency = count[i];
            pq.push(n);
        }
    }
}

void PreOrderTraversal(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    cout<<node->c<<" "<<node->frequency<<endl;

    PreOrderTraversal(node->left);
    PreOrderTraversal(node->middle);
    PreOrderTraversal(node->right);
}
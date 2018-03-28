#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node * next;
    
    Node(int newData, Node * nextNode = nullptr);
    ~Node();
};

Node::Node(int newData, Node * nextNode){
    data = newData;
    next = nextNode;
}

class Queue{
public:
    Node * front;
    Node * back;
    int size;
    
    Queue();
    ~Queue();
    bool isEmpty(){return size==0;};
    void enqueue(int val);
    int dequeue(void);
};

Queue::Queue(){
    front = nullptr;
    back = nullptr;
    size = 0;
}

Queue::~Queue(){
    if (front != nullptr) {
        free(front);
    }
    if (back != nullptr){
        free(back);
    }
}

void Queue::enqueue(int val){
    Node * newNode = new Node(val);
    if (this->isEmpty()){
        front = newNode;
        back = front;
    }
    else{
        back->next = newNode;
        back = newNode;
    }
    size++;
}

int Queue::dequeue(){
    int val = 0;
    if (!this->isEmpty()){
        Node * temp = front;
        val = temp->data;
        front = front->next;
        free(temp);
        size--;
    }
    return val;
}

int killPeeps(int numPeeps){
    //Create Queue
    Queue * theQueue = new Queue();
    for (int i = 1; i <= numPeeps; i++){
        theQueue->enqueue(i);
    }
    //while queue != empty
    int temp1;
    int temp2;
    while (!theQueue->isEmpty()){
        try {
            temp1 = theQueue->dequeue();
            temp2 = theQueue->dequeue();
            cout << temp1 << " Kills " << temp2 << endl;
            //If these were the last two elements, don't bother inserting the last one back in the queue
            if (!theQueue->isEmpty()){
                theQueue->enqueue(temp1);
            }
        }
        catch (exception &e) {
            cout << "Empty Queue Error!";
        }
    }
    return temp1;
}

int main(){
    int numPeople = 0;
    cout << "Enter the num people in the circle: ";
    cin >> numPeople;
    cin.clear();
    int result = killPeeps(numPeople);
    cout << result << endl;
    return 0;
}









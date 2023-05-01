#include <iostream>
#include <mutex>

using namespace std;
struct Node
{
    int value;
    Node* next;
    std::mutex* node_mutex;
};

class FineGrainedQueue
{public:
    Node* head;
    std::mutex* queue_mutex;

    void push(const int& val)
    {
        queue_mutex->lock();
        Node* newNode = new Node;
        newNode->value = val;
        newNode->node_mutex = new mutex;
        newNode->next = nullptr;
        Node* curNode = head;
        while (curNode->next != nullptr) {
            curNode = curNode->next;
        }
        curNode->next = newNode;
        queue_mutex->unlock();
    }

    void PrintF() {
        Node* curNode = head;

        while (curNode != nullptr) {
            cout << curNode->value << endl;
            curNode = curNode->next;
        }
    }

    void insertIntoMiddle(const int& value, const int& pos)
    {
        int ticker = 0;
        queue_mutex->lock();
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        Node* curNode = head;
        while (ticker < pos && curNode->next != nullptr)
        {
            curNode = curNode->next;
            ticker++;
        }
        if (curNode->next == nullptr)
        {
            if (curNode) {
                curNode->node_mutex->lock();
                curNode->next = newNode;
                curNode->node_mutex->unlock();
            }
        }
        else {
            if (curNode) {
                newNode->next = curNode->next;
                curNode->node_mutex->lock();
                curNode->next = newNode;
                curNode->node_mutex->unlock();
            }
        }
        queue_mutex->unlock();
   }
};

int main()
{
    Node* root = new Node;
    root->value = 0;
    root->next = nullptr;
    mutex* mutexNode = new mutex;
   root->node_mutex = mutexNode;
    FineGrainedQueue* FGQ = new FineGrainedQueue;
    FGQ->head = root;
    mutex* FGQmutex = new mutex;
    FGQ->queue_mutex = FGQmutex;

    for (int i = 1; i <= 20; i++) {
        FGQ->push(i);
    }
    FGQ->insertIntoMiddle(555, 7);
    FGQ->insertIntoMiddle(100, 0);
    FGQ->PrintF();

    delete FGQmutex;
    delete mutexNode;
    delete FGQ;
    delete root;
}

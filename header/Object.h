#ifndef OBJECT_H
#define OBJECT_H
#include "includeFile.h"
using namespace std;

class BaseObject
{
    public:
        int Health;
        int Level;
        int X, Y;
        bool isRunning;
        bool isAttacking;
        bool isDeath;
        bool isHurt;
        bool isIdle;
        int direction;
        

};

class Soldier : public BaseObject
{
    public:
        float v = 4;
        int size;
        float range = 200.0f;
        soldierState state;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        const Uint32 frameDelay = 75; // ms


};

class Orc : public BaseObject
{
    public:
        float v = 1;
        int size;
        float range = 3.0;
        int currentFrame = 0;
        Uint32 lastFrameTime = 0;
        const Uint32 frameDelay = 75; // ms

        
};

struct Object {
    int x, y;
};

struct Node {
    Object *data;
    Node *next;
};

class LinkedList {
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current->data;
            delete current;
            current = nextNode;
        }
    }

    void insertAtEnd(Object* value) {
        Node* newNode = new Node{value};

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void deleteAtPosition(int position){
        Node* temp = head;
        for (int i = 1; i < position - 1 && temp; ++i){
            temp = temp->next;
        }

        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    Object* takeDataAtPosition(int position){
        Node* temp = head;
        for (int i = 1; i < position && temp; ++i){
            temp = temp->next;
        }

        return temp->data;
    }
};

#endif
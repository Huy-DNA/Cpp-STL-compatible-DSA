#ifndef __LINKED_LIST_FOR_BUCKET_SORT_HELL__
#define __LINKED_LIST_FOR_BUCKET_SORT_HELL__

#include <type_traits>

template <typename Elem_T>
struct LinkedList {
    struct Node {
        Elem_T data;
        Node* next;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    
public:
    ~LinkedList() {
        while (head != nullptr) {
            Node* tmp = head->next;
            delete head;
            head = tmp;
        }
    }

    void push_back(Elem_T data) {
        if (head == nullptr) {
            head = tail = new Node{data, nullptr};
        } else {
            tail->next = new Node{data, nullptr};
            tail = tail->next;
        }
    }

    /*Note: this implementation isn't stable!!*/
    void insertion_sort() {
        if (head == nullptr) return;

        for (Node* cur = head->next, *prev = head; cur != nullptr; ) {
            Node* ins_pos = nullptr;                               //position to insert cur next to
            for (Node* bef = head; ; bef = bef->next)
                if (bef->data < cur->data) {
                    ins_pos = bef;
                } else break;

            //Update prev & cur properly
            if (prev == ins_pos) {
                prev = cur;
                cur = cur->next;
            } else {
                move(cur, prev, ins_pos);
                cur = prev->next;
            }
        }
    }

    std::vector<Elem_T> get_list_content() const {
        std::vector<Elem_T> res;
        for (Node* cur = head; cur != nullptr; cur = cur->next)
            res.push_back(cur->data);
        return res;
    }

    LinkedList& concat(LinkedList& other) {
        if (head == nullptr) {
            head = other.head;
            tail = other.tail;
        } else {
            tail->next = other.head;
            if (other.tail != nullptr)
                tail = other.tail;
        }
        other.head = other.tail = nullptr;

        return *this;
    }
private:      
    /*Move u to next to ins_pos*/
    void move(Node* u, Node* prev, Node* ins_pos) {
        //remove u from list
        prev->next = u->next;              
        if (u->next == nullptr)
            tail = prev;

        //add u to ins_pos
        if (ins_pos == nullptr) {         
            u->next = head;
            head = u;
        } else {
            u->next = ins_pos->next;
            ins_pos->next = u;
        }
        if (u->next == nullptr)
            tail = u;

    } 
};

#endif
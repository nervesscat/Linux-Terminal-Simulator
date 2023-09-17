#include <iostream>

template <typename T>
class LinkedList;

// * Node Class

template <typename T>
class Node {
private:
    T data;
    Node<T> *next;
    LinkedList<T> *children;
public:
    Node();
    Node(T t);
    void setData(T t);
    T getData();
    void setNext(Node<T> *current);
    Node<T>* getNext();
    LinkedList<T>* getChildren();
    ~Node();
};

template <typename T>
Node<T>::Node(){
    next = NULL;
    children = new LinkedList<T>();
}

template <typename T>
Node<T>::Node(T t){
    data = t;
    next = NULL;
    children = new LinkedList<T>();
}

template <typename T>
void Node<T>::setData(T t){
    data = t;
}

template <typename T>
T Node<T>::getData(){
    return data;
}

template <typename T>
void Node<T>::setNext(Node<T> *current){
    next = current;
}

template <typename T>
Node<T>* Node<T>::getNext(){
    return next;
}

template <typename T>
LinkedList<T>* Node<T>::getChildren(){
    return children;
}

template <typename T>
Node<T>::~Node(){
    delete next;
}

// * LinkedList Class

template <typename T>
class LinkedList{
private:
    Node<T> *first;
    int size;
public:
    LinkedList();
    Node<T>* getFirst();
    void add(T t);
    void print();
    Node<T>* search(T t);
    int getSize();
    bool isEmpty();
    ~LinkedList();
};

template <typename T>
LinkedList<T>::LinkedList(){
    first = NULL;
    size = 0;
}

template <typename T>
Node<T>* LinkedList<T>::getFirst(){
    return first;
}

template <typename T>
void LinkedList<T>::add(T t){
    Node<T> *add = new Node<T>(t);
    if(first == NULL){
        first = add;
    } else {
        Node<T> *current = first;
        while (current->getNext()!=NULL){
            current = current->getNext();
        }
        current->setNext(add); 
    } 
    size++;
}

template <typename T>
void LinkedList<T>::print(){
    Node<T> *current = first;
    while (current!=NULL){
        std::cout << current->getData() << " -> ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

template <typename T>
Node<T>* LinkedList<T>::search(T t){
    Node<T> *current = first;
    while (current!=NULL){
        if(current->getData() == t){
            return current;
        }
        current = current->getNext();
    } 
    return NULL;
}

template <typename T>
int LinkedList<T>::getSize(){
    return size;
}

template <typename T>
bool LinkedList<T>::isEmpty(){
    if(size==0){
        return true;
    } else {
        return false;
    }
}

template <typename T>
LinkedList<T>::~LinkedList(){
    delete first;
}

template <typename T>
class Tree{
private:
    Node<T> *root;
    Node<T>* search(T t);
    Node<T>* search(Node<T>* current, T t);
public:
    Tree();
    Tree(T t);
    void add(T t);
    void add(Node<T>* current ,T t);
    ~Tree();
};

template <typename T>
Tree<T>::Tree(){
    root = new Node<T>();
}

template <typename T>
Tree<T>::Tree(T t){
    root = new Node<T>(t);
}

template <typename T>
void Tree<T>::add(T t){

}

template <typename T>
Node<T>* Tree<T>::search(T t){
    return search(root, t);
}

template <typename T>
Node<T>* Tree<T>::search(Node<T>* current, T t){
    if(current->getData() == t){
        return current;
    }

    if(current->getChildren()->isEmpty) return;

    Node<T> *children = current->getChildren()->getFirst();

    search(children, t);

    return NULL;
}

template <typename T>
Tree<T>::~Tree(){
    delete root;
}


int main(){
    LinkedList<int> *list = new LinkedList<int>();

    list->add(4);
    list->add(13);
    list->add(11);
    list->add(111);

    list->print();
}
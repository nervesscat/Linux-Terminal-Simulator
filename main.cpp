#include <iostream>
#include <string>

template <typename T>
class LinkedList;

// * Node Class

template <typename T>
class Node {
private:
    T data;
    Node<T> *next;
    Node<T> *parent;
    LinkedList<T> *children;
public:
    Node();
    Node(T t);
    void setData(T t);
    T getData();
    void setNext(Node<T> *current);
    Node<T>* getNext();
    Node<T>* getParent();
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
Node<T>* Node<T>::getParent(){
    return parent;
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
        std::cout << current->getData() << " ";
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

// * Tree Class

template <typename T>
class Tree{
private:
    Node<T> *root;
public:
    Tree();
    Tree(T t);
    void add(T t);
    void add(Node<T>* parent ,T t);
    Node<T>* getRoot();
    Node<T>* search(T t);
    Node<T>* search(Node<T>* current, T t);
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
    add(root, t);
}

template <typename T>
void Tree<T>::add(Node<T>* parent, T t){
    parent->getChildren()->add(t);
}

template <typename T>
Node<T>* Tree<T>::search(T t){
    return search(root, t);
}

template <typename T>
Node<T>* Tree<T>::search(Node<T>* current, T t){
    while (current != NULL){
        if(current->getData() == t) return current;

        if(!current->getChildren()->isEmpty()){
            Node<T> *children = current->getChildren()->getFirst();
            Node<T> *result = search(children, t);
            if(result != NULL){
                return result;
            }
        }

        current = current->getNext();
    }
    return NULL;
}

template <typename T>
Node<T>* Tree<T>::getRoot(){
    return root;
}

template <typename T>
Tree<T>::~Tree(){
    delete root;
}

int main(){
    Tree<std::string> *tree = new Tree<std::string>("root");
    Node<std::string> *actualPath = tree->getRoot();
    std::string cmd;
    while(true){
        std::cout << "> ";
        std::getline(std::cin, cmd);
        if(cmd == "exit"){
            break;
        } else if(cmd == "ls"){
            actualPath->getChildren()->print();
        } else if(cmd == "pwd"){
            Node<std::string> *current = actualPath;
            while (current->getParent()!=NULL){
                std::cout << current->getData() << "/";
                current = current->getParent();
            }
            std::cout << std::endl;
        } else if(cmd == "cd .."){
            if(actualPath->getParent()!=NULL){
                actualPath = actualPath->getParent();
            }
        } else if(cmd.substr(0, 3) == "cd "){
            std::string path = cmd.substr(3, cmd.length());
            Node<std::string> *result = tree->search(path);
            if(result != NULL){
                actualPath = result;
            } else {
                std::cout << "Path not found" << std::endl;
            }
        } else if(cmd.substr(0, 6) == "mkdir "){
            std::string path = cmd.substr(6, cmd.length());
            tree->add(actualPath, path);
        } else {
            std::cout << "Command not found" << std::endl;
        }
    }
    
}
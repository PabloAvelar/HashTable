#ifndef NODE_HPP
#define NODE_HPP
#include <string.h>

class Node{
    //private:
    public:
        char artist[30];
        char album[30];
        char title[30];
        char year[5];
        int reference;

        Node* next;
        Node* prev;

    //public:
        // Constructores
        Node(){
            this->next = nullptr;
            this->prev = nullptr;
            this->reference = 0;
        }

        Node(char* _artist, char* _album, char* _title, char* _year){
            strcpy(this->artist, _artist);
            strcpy(this->album, _album);
            strcpy(this->title, _title);
            strcpy(this->year, _year);

            this->reference = 0;
            this->next = nullptr;
            this->prev = nullptr;
        }

        // Destructor
        ~Node(){}
    
        // Getters
        const char *getArtist() const;
        const char* getAlbum() const;
        const char* getTitle() const;
        const char* getYear() const;
        int& getReference();

        Node* getNext() const;
        Node* getPrev() const;

        // Setters
        void setNext(Node*);
        void setPrev(Node*);
        void setReference(int);


};  // Total: 104

// Getters

const char* Node::getArtist() const{
    return artist;
}

const char* Node::getAlbum() const{
    return album;
}

const char* Node::getTitle() const{
    return title;
}

const char* Node::getYear() const{
    return year;
}

Node* Node::getNext() const{
    return this->next;
}

Node* Node::getPrev() const{
    return this->prev;
}

int& Node::getReference(){
    return this->reference;
}

// Setters

void Node::setNext(Node* node){
    this->next = node;
}

void Node::setPrev(Node* node){
    this->prev = node;
}

void Node::setReference(int _reference){
    this->reference = _reference;
}



#endif
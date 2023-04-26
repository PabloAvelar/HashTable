#ifndef NODE_HPP
#define NODE_HPP
#include <string.h>
#define REGISTERS 20

class Node{
    private:
        char artist[30];
        char album[30];
        char title[30];
        char year[5];
        int reference;


    public:
        Node* collisions[REGISTERS];
        int nCollisions;
        // Constructores
        Node(){
            for(int i=0; i<REGISTERS; i++) this->collisions[i] = nullptr;
            this->reference = 0;
            this->nCollisions = 0;
        }

        Node(char* _artist, char* _album, char* _title, char* _year){
            strcpy(this->artist, _artist);
            strcpy(this->album, _album);
            strcpy(this->title, _title);
            strcpy(this->year, _year);

            this->reference = 0;
            this->nCollisions = 0;
            for(int i=0; i<REGISTERS; i++) this->collisions[i] = nullptr;
        }

        // Destructor
        ~Node(){
            delete[] artist;
            delete[] album;
            delete[] title;
            delete[] year;
        }
    
        bool destroyNode(Node*);
        void addCollision(Node*);


        // Getters
        const char *getArtist() const;
        const char* getAlbum() const;
        const char* getTitle() const;
        const char* getYear() const;
        int getReference();

        Node* getNext() const;
        Node* getPrev() const;
        int getCollisions() const;

        // Setters
        void setNext(Node*);
        void setPrev(Node*);
        void setReference(int);


};  // Total: 104

bool Node::destroyNode(Node* node){
    delete[] artist;
    delete[] album;
    delete[] title;
    delete[] year;
    delete node;
    node = nullptr;
}

void Node::addCollision(Node* node){
    this->collisions[nCollisions] = node;
    this->nCollisions++;
}

// Getters

int Node::getCollisions() const{
    return nCollisions;
}

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

int Node::getReference(){
    return reference;
}

// Setters
void Node::setReference(int _reference){
    this->reference = _reference;
}



#endif
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "node.hpp"
#define REGISTERS 20

/*

Para tener mayor control sobre los registros para un archivo binario, se utilizaron los 
        registros de longitud fija

Así se evitan problemas de desface al querer acceder a la información de un archivo binario.

En este programa, el archivo binario tendrá la capacidad de almacenar hasta 20 registros.

*/

class HashTable{
    private:
        Node* nodes[REGISTERS];
        int counter;
        int collisions;
        int* index = new int[REGISTERS];
        bool isLoaded;
        Node* nodeptr;
    
    public:
        // Constructor
        HashTable(){
            counter=0;
            isLoaded = false;
            collisions = 0;
            for(int i=0; i<REGISTERS; i++) this->nodes[i] = nullptr;
        };

        // Destructor
        ~HashTable(){
            delete[] nodes;
            delete[] index;
        }

        // Métodos
        void insertRegister(char*, char*, char*, char*);
        void show();
        void showCollisions(Node*);
        void deleteRegister(int);

        void getPrimaryKey(char*, char*, char*) const; // recibe artista y titulo
        int hash(char*); // recibe la key y devuelve la referencia del registro.
        Node* getNodeByReference(int) const;
        int getCounter() const;
        int getCollisions() const;
        void save() const;
        void load();

        bool isEmpty() const;
        bool isFull() const;
};


#endif
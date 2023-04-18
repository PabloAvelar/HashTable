#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "node.hpp"

/*

Para tener mayor control sobre los registros para un archivo binario, se utilizaron los 
        registros de longitud fija

Así se evitan problemas de desface al querer acceder a la información de un archivo binario.

En este programa, el archivo binario tendrá la capacidad de almacenar hasta 20 registros.

*/

class HashTable{
    private:
        Node* init;
        Node* last;
        int counter;
    
    public:
        // Constructor
        HashTable(){init=nullptr;last=nullptr;counter=0;};

        // Destructor
        ~HashTable(){}

        // Métodos
        void insertRegister(char*, char*, char*, char*);
        void show();
        void deleteRegister();

        void getPrimaryKey(char*, char*, char*) const; // recibe artista y titulo
        int hash(char*); // recibe la key y devuelve la referencia del registro.
        void save() const;
        void load();

        bool isEmpty() const;
};


#endif
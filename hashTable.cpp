#include "hashtable.hpp"
#include <iostream>
#include <fstream>

#define REGISTERS 20

bool HashTable::isEmpty() const{
    return !this->counter;
}

void HashTable::getPrimaryKey(char* key, char* artist, char*title) const{

    // Haciendo minusculas todas las letras
    for(int i=0; artist[i] != '\0'; i++) artist[i] = tolower(artist[i]);
    for(int i=0; title[i] != '\0'; i++) title[i] = tolower(title[i]);

    strcpy(key, artist);
    strcat(key, title);

}

int HashTable::hash(char* key){
    // 1) Pasar cadena de texto a código ASCII y sumar esos códigos
    int count = 0;
    int reference = 0;

    for(int i=0; i<strlen(key); i++) count += int(key[i]);
    // 2) Obtener la referencia que tendrá el registro dentro del archivo binario.
    reference = count % REGISTERS;
    
    return reference;
}

void HashTable::save() const{
    
    if(isEmpty()){
        std::cout<<"Save: La tabla Hash esta vacia."<<std::endl;
        return;
    }

    std::ofstream file("file01.bin", std::ios::binary); // ios::app no me permite mover la cabecera del seekp
    std::ofstream index("index.bin", std::ios::binary | std::ios::out); // Este no es archivo disperso.
    Node* aux = this->init;

    if(file.fail()){
        std::cout<<"Save: no se pudo abrir el archivo file01."<<std::endl;
        return;
    }

    if(index.fail()){
        std::cout<<"Save: no se pudo abrir el archivo index."<<std::endl;
        return;
    }
    
    index.seekp(0, std::ios::beg);
    while(aux){
        // Para el archivo binario que guarda los registros (file01.bin)
        file.seekp(aux->getReference() * sizeof(Node), std::ios::beg);
        file.write( (char*)aux, sizeof(Node) );

        // Para el archivo que guarda los indices (index.bin)
        //std::cout<<aux->getArtist()<<std::endl;
        index.write( (char*)&aux->getReference(), sizeof(int) );

        // Continua con el siguiente Nodo de la lista.
        aux = aux->getNext();
    }

    if(!file){
        std::cout<<"Save: error al escribir en el archivo"<<std::endl;
        return;
    }

    std::cout<<"Save: se han guardado los registros correctamente."<<std::endl;
    index.close();
    file.close();
}

void HashTable::load(){
    std::ifstream file("file01.bin", std::ios::binary);
    std::ifstream index("index.bin", std::ios::binary);
    int ref;
    Node* aux = new Node();

    if(file.fail()){
        std::cout<<"Load: no se pudo abrir el archivo file01."<<std::endl;
        return;
    }

    if(index.fail()){
        std::cout<<"Load: no se pudo abrir el archivo index."<<std::endl;
        return;
    }

    // Leyendo cada referencia guardada en index.bin
    while(!index.eof()){
        index.read( (char*)&ref, sizeof(int) );

        // Buscando la posición del registro con su indice
        file.seekg(ref * sizeof(Node), std::ios::beg);

        // Recuperando la información del archivo binario
        file.read( (char*)aux, sizeof(Node) );

        // Insertando el Nodo a la lista de la Tabla Hash.
        if(index.good())
            insertRegister((char*)aux->getArtist(),
                        (char*)aux->getAlbum(),
                        (char*)aux->getTitle(),
                        (char*)aux->getYear()
            );
    }

    if(isEmpty()) std::cout<<"Load: No hay registros para cargar..."<<std::endl;
    else{
        std::cout<<"Load: se han cargado todos los registros exitosamente!"<<std::endl;
        show();
    }

    file.close();
    index.close();

}

void HashTable::insertRegister(char* artist, char* album, char* title, char* year){
    Node* aux = new Node(artist, album, title, year);
    int length = strlen(artist) + strlen(title);
    int reference;
    char* key = new char[length];

    // Caso 1: Agregando en la primera posición
    if(isEmpty()){
        this->init = aux;
        this->last = aux;
    }
    else{ // Caso 2: Agregando en cualquier otra posición
        this->last->setNext(aux);
        aux->setPrev(this->last);
        this->last = aux;
    }

    getPrimaryKey(key, artist, title); // Se obtiene la key en el array "key"

    // se le manda la key a la función hash
    //system("pause");
    reference = hash(key);
    aux->setReference(reference);
    
    this->counter++;
}

void HashTable::show(){
    Node* aux = this->init;
    if(isEmpty()) return;
    while(aux){
        std::cout<<
            "Artista: "<<aux->getArtist() << std::endl <<
            "Album: " << aux->getAlbum() << std::endl <<
            "Cancion: "<<aux->getTitle() << std::endl <<
            "Lanzamiento: " << aux->getYear() << std::endl <<
            "Referencia: " << aux->getReference() << std::endl << std::endl;

        aux = aux->getNext();
    }
}
#include "hashtable.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

bool HashTable::isEmpty() const{
    return !this->counter;
}

bool HashTable::isFull() const{
    return this->counter == REGISTERS;
}

Node* HashTable::getNodeByReference(int ref) const{
    return nodes[ref];
}

int HashTable::getCounter() const{
    return this->counter;
}

int HashTable::getCollisions() const{
    return this->collisions;
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

    std::ofstream file("file01.bin", std::ios::binary); // Archivo principal
    std::ofstream collisionsFile("collisions.bin", std::ios::binary); // Archivo con las colisiones
    std::ofstream index("index.bin", std::ios::binary | std::ios::out); // Este no es archivo disperso.
    int ref;
    Node* aux = new Node();

    if(file.fail()){
        std::cout<<"Save: no se pudo abrir el archivo file01."<<std::endl;
        return;
    }

    if(collisionsFile.fail()){
        std::cout<<"Save: no se pudo abrir el archivo collisions.bin"<<std::endl;
        return;
    }

    if(index.fail()){
        std::cout<<"Save: no se pudo abrir el archivo index."<<std::endl;
        return;
    }
    
    for(int i=0; i<counter; i++){
        ref = this->index[i];
        aux = getNodeByReference(ref);
        // Para el archivo binario que guarda los registros (file01.bin)
        file.seekp(aux->getReference() * sizeof(Node), std::ios::beg);
        file.write( (char*)aux, sizeof(Node) );

        // Guardando colisiones sólo en caso de que existan
        collisionsFile.seekp(aux->getReference() * sizeof(aux->collisions) * REGISTERS, std::ios::beg);
        for(int j=0; j<aux->nCollisions; j++)
            collisionsFile.write( (char*)aux->collisions[j], sizeof(Node) );

        // Para el archivo que guarda los indices (index.bin)
        index.write( (char*)&ref, sizeof(int) );
    }

    if(!file){
        std::cout<<"Save: error al escribir en el archivo"<<std::endl;
        return;
    }



    std::cout<<"Save: se han guardado los registros correctamente."<<std::endl;

    collisionsFile.close();
    index.close();
    file.close();
    
}

void HashTable::load(){
    if(this->isLoaded){
        std::cout<<"Load: los datos ya han sido cargados..."<<std::endl;
        return;
    }

    std::ifstream file("file01.bin", std::ios::binary);
    std::ifstream collisionsFile("collisions.bin", std::ios::binary);
    std::ifstream index("index.bin", std::ios::binary);

    if(file.fail()){
        std::cout<<"Load: no se pudo abrir el archivo file01."<<std::endl;
        return;
    }

    if(collisionsFile.fail()){
        std::cout<<"Load: no se pudo abrir el archivo collisions.bin"<<std::endl;
        return;
    }

    if(index.fail()){
        std::cout<<"Load: no se pudo abrir el archivo index."<<std::endl;
        return;
    }

    // Leyendo cada referencia guardada en index.bin
    int ref;
    Node* aux = new Node();
    Node* collision = new Node();

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

        // Recuperando colisiones si es que existen
        collisionsFile.seekg(ref * sizeof(aux->collisions) * REGISTERS, std::ios::beg);
        for(int i=0; i<aux->nCollisions; i++){
            collisionsFile.read( (char*)collision, sizeof(Node) );
            if(index.good())
                insertRegister(
                    (char*)collision->getArtist(),
                    (char*)collision->getAlbum(),
                    (char*)collision->getTitle(),
                    (char*)collision->getYear()
                );
        }
    }

    if(isEmpty()) std::cout<<"Load: No hay registros para cargar..."<<std::endl;
    else{
        std::cout<<"Load: se han cargado todos los registros exitosamente!"<<std::endl;
        show();
    }

    file.close();
    collisionsFile.close();
    index.close();

    nodeptr->destroyNode(collision);
    nodeptr->destroyNode(aux);

    this->isLoaded = true;

}

void HashTable::insertRegister(char* artist, char* album, char* title, char* year){
    Node* aux = new Node(artist, album, title, year);
    int length = strlen(artist) + strlen(title);
    int reference;
    char* key = new char[length];

    getPrimaryKey(key, artist, title); // Se obtiene la key en el array "key"

    // se le manda la key a la función hash
    reference = hash(key);
    aux->setReference(reference);

    // Verificando que haya colision por su referencia
    if(!nodes[reference]){
        nodes[reference] = aux;
        index[counter] = reference;
        this->counter++;
    }else{
        nodes[reference]->addCollision(aux);
        this->collisions++;
    } 
    
}

void HashTable::showCollisions(Node* aux){
    std::cout<<std::endl;
    std::cout<< std::setw(10) << std::left << "Indice"
                << std::setw(1) << "|"
                <<std::setw(20) << std::left << "Artista"
                << std::setw(1) << "|"
                << std::setw(20) << std::left << "Album"
                << std::setw(1) << "|"
                << std::setw(20) << std::left << "Cancion"
                << std::setw(1) << "|"
                << std::setw(20) << std::left << "Lanzamiento"
    << std::endl;

    for(int i=0; i< (20*4+5+10); i++) std::cout<<"-";
    std::cout<<std::endl<<std::endl;
    
    
    std::cout << std::setw(10) << std::left << "[0]"
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getArtist()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getAlbum()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getTitle()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getYear()
        << std::endl;


    for(int i=0; i < aux->getCollisions(); i++){

            std::cout<< "["<<i+1<<"]" << std::setw(10-3) << std::left << " "
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[i]->getArtist()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[i]->getAlbum()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[i]->getTitle()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[i]->getYear()
            << std::endl;
    }
}

void HashTable::deleteRegister(int reference){
    int n;
    Node* node = getNodeByReference(reference);

    if(!node->nCollisions){ // Caso 1: eliminar nodo sin colisiones
        nodeptr->destroyNode(node);
        this->counter--;
    }else{ // Caso 2: eliminar nodo con colisiones
        std::cout<<"Registros con la referencia: "<<reference<<std::endl<<std::endl;
        showCollisions(node);        

        std::cout<<std::endl<<std::endl;
        std::cout<<"Indice del registro a eliminar: ";
        std::cin>>n;

        if(n==0){ // 1) Si el nodo es el indice 0
            int lastPosition = node->nCollisions-1;
            nodes[reference] = node->collisions[ lastPosition ];
            nodeptr->destroyNode(node);
        }else{ // 2) Si el indice es cualquier otro
            Node* aux = node->collisions[n];
            for(int i=n; i < node->nCollisions-1; i++) node->collisions[i] = node->collisions[i+1];
            node->nCollisions --;
            nodeptr->destroyNode(aux);
        }

        this->collisions --;
    }

    std::cout<<"Delete: se ha eliminado el registro exitosamente..."<<std::endl;

}

void HashTable::show(){
    if(isEmpty()) return;
    Node* aux = nullptr;

    std::cout<<std::endl;
    std::cout<< std::setw(20) << std::left << "Referencia"
                << std::setw(1) << "|"
                <<std::setw(20) << std::left << "Artista"
                << std::setw(1) << "|"
                << std::setw(20) << std::left << "Album"
                << std::setw(1) << "|"
                << std::setw(20) << std::left << "Cancion"
                << std::setw(1) << "|"
                << std::setw(20) << std::left << "Lanzamiento"
    << std::endl;

    for(int i=0; i< (20*5+5); i++) std::cout<<"-";
    std::cout<<std::endl<<std::endl;

    for(int i=0; i<counter; i++){
        aux = getNodeByReference(index[i]);
        std::cout << std::setw(20) << std::left << aux->getReference()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getArtist()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getAlbum()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getTitle()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->getYear()
        << std::endl;

        for(int j=0; j < aux->getCollisions(); j++){

            std::cout<< std::setw(20) << std::left << aux->getReference()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[j]->getArtist()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[j]->getAlbum()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[j]->getTitle()
                 << std::setw(1) << "|"
                 << std::setw(20) << std::left << aux->collisions[j]->getYear()
            << std::endl;
        }

        for(int i=0; i< (20*5+5); i++) std::cout<<"-";
        std::cout<<std::endl;

    }
}
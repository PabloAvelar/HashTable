#include <iostream>
#include "hashTable.cpp"

enum{
    SALIR,
    AGREGAR,
    MOSTRAR, GUARDAR, CARGAR,
    ELIMINAR
};

int main(){

    int opc, ref;
    char artist[30];
    char album[30];
    char title[30];
    char year[5];
    HashTable* hashTable = new HashTable();

    do{
        system("cls");
        system("color a");
        
        std::cout<<"Hash Table: serialization and indexing."<<std::endl<<std::endl;
        std::cout<<"Registros: "<<hashTable->getCounter()<<std::endl;
        std::cout<<"Colisiones en registros: "<<hashTable->getCollisions()<<std::endl<<std::endl;

        std::cout<<AGREGAR<<") AGREGAR"<<std::endl;
        std::cout<<MOSTRAR<<") MOSTRAR"<<std::endl;
        std::cout<<GUARDAR<<") GUARDAR"<<std::endl;
        std::cout<<CARGAR<<") CARGAR"<<std::endl;
        std::cout<<ELIMINAR<<") ELIMINAR"<<std::endl;
        std::cout<<SALIR<<") SALIR"<<std::endl;

        
        std::cin>>opc;


        switch(opc){
            
            case AGREGAR:
                system("cls");
                system("color 1");
                std::cin.ignore();

                if(hashTable->isFull()){
                    std::cout<<"Insert: la lista de registros esta llena..."<<std::endl;
                    continue;
                }
                
                std::cout<<"Artista: ";
                std::cin.getline(artist, 30);

                std::cout<<"Album: ";
                std::cin.getline(album, 30);

                std::cout<<"Cancion: ";
                std::cin.getline(title, 30);

                std::cout<<"Lanzamiento: ";
                std::cin.getline(year, 5);

                hashTable->insertRegister(artist, album, title, year);

                system("pause");
            break;

            case MOSTRAR:
                system("cls");
                system("color b");
                if(hashTable->isEmpty()){
                    std::cout<<"Show: no hay registros existentes..."<<std::endl;
                    system("pause");
                    continue;
                }
                hashTable->show();
                system("pause");
            break;

            case GUARDAR:
                system("cls");
                hashTable->save();
                system("pause");
            break;

            case CARGAR:
                system("cls");
                system("color 6");
                hashTable->load();
                system("pause");
            break;

            case ELIMINAR:
                system("cls");
                system("color 4");
                if(hashTable->isEmpty()){
                    std::cout<<"Delete: no hay registros existentes..."<<std::endl;
                    system("pause");
                    continue;
                }
                hashTable->show();
                std::cout<<"Referencia del registro a eliminar: ";
                std::cin>>ref;
                fflush(stdin);

                hashTable->deleteRegister(ref);

                system("pause");
            break;

        }
    }while(opc != SALIR);



    return 0;
}
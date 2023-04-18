#include <iostream>
#include "hashTable.cpp"

enum{
    SALIR,
    AGREGAR,
    MOSTRAR, GUARDAR, CARGAR,
    ELIMINAR
};

int main(){

    int opc;
    char artist[30];
    char album[30];
    char title[30];
    char year[5];
    HashTable* hashTable = new HashTable();

    do{
        system("cls");
        
        std::cout<<"Hash Table"<<std::endl<<std::endl;

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
                std::cin.ignore();
                
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
                hashTable->load();
                system("pause");
            break;

        }
    }while(opc != SALIR);



    return 0;
}
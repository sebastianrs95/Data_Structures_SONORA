#include <cstdlib>
#include <iostream>
#include "TreeNode.h"
#include "BPTree.h"


using namespace std;

int main()
{
    int degree;
    cout<<"Programa implementa un Arbol-B+ de grado n"<<endl<<endl;

    cout<<"Ingrese el grado de el arbol (Minimo de valores en un nodo): ";
    cin>>degree;
    BPTree bp(degree);

    int option, value;
    char path[50];

    do
    {
        system("cls");
        cout<<"------MENU------"<<endl<<endl;
        cout<<"1) Ingresar datos de un archivo"<<endl;
        cout<<"2) Buscar un numero en el arbol"<<endl;
        cout<<"3) Eliminar datos de un archivo"<<endl;
        cout<<"4) Imprimir hojas de el arbol"<<endl;
        cout<<"5) Guardar datos en un archivo"<<endl;
        cout<<"0) Salir"<<endl;
        cout<<"Ingrese su opcion: ";
        cin>>option;

        if(option<0 || option>5)
        {
            cout<<"Opcion invalida"<<endl;
            continue;
        }

        switch(option)
        {
            case 1:
                cout<<"Nombre del archivo a que contiene los valores a ingresas: ";
                cin>>path;
                bp.readFromFile(path);
                cout<<"Los valores han sido ingresados"<<endl;
                system("pause");
                break;

            case 2:
                cout<<"Ingrese el valor a buscar: ";
                cin>>value;
                //bp.searchValue(value)
                system("pause");;
                break;

            case 3:
                cout<<"Nombre del archivo a que contiene los valores a eliminar: ";
                cin>>path;
                bp.deleteFromFile(path);
                cout<<"Los valores han sido eliminados"<<endl;
                system("pause");
                break;

            case 4:
                cout<<"Imprimiendo los valores que se encuentran en el arbol"<<endl;
                bp.print();
                system("pause");
                break;

            case 5:
                cout<<"Nombre del archivo para guardar los datos: ";
                cin>>path;
                bp.saveToFile(path);
                cout<<"Se ha creado el archivo"<<endl;
                system("pause");
                break;
        }
    }while(option!=0);

    cout<<"Gracias por usar el Arbol-B+"<<endl;

    return 0;
}

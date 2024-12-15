/*Este código tem como objetivo criar um programa que retorne o endereço
de um array bidimensional com os dados de leitura do arquivo csv para
o projeto 1 da disciplina PROGRAMAÇÃO ORIENTADA A OBJETOS.
lucas Antônio Cunha Rodrigues da Silva - 14/12/2024 14:17*/

#include "read.csv.h"

int main(){
    bool state = true;
    string fileName = "features-Aula 13 - Projeto 1 - dataset2.csv";
    csvImport<float>*obj = new csvImport<float>(fileName);
    if (obj->getType() == false){
        delete obj;
        obj = nullptr;
        state = false;
        }
    if (!state){
        csvImport<int>*obj2 = new csvImport<int>(fileName);
        obj2->geraTabela();
        obj2->printData();
        delete obj2;
        obj2 = nullptr;
    }
    else{    
    // Obtém os dados do arquivo
    obj->geraTabela();
    // Imprime os valores lidos
    cout << "Dados lidos do arquivo:" << endl;
    obj->printData();  // Chama a função de impressão
    delete obj;
    }
    return 0;
}

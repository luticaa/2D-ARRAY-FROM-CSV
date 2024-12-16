/*Este código tem como objetivo criar um programa que retorne o endereço
de um array bidimensional com os dados de leitura do arquivo csv para
o projeto 1 da disciplina PROGRAMAÇÃO ORIENTADA A OBJETOS.
lucas Antônio Cunha Rodrigues da Silva - 14/12/2024 14:17*/
#include "read.csv2.h" //importação arquivo com classe

int main(){ //declarção main()
    bool state = true;//variavel de estado para identificar tipo 
    string fileName = "features-Aula 13 - Projeto 1 - dataset1.csv"; 
    //variavel fileName armazena string com nome do arquivo a ser lido
    csvImport<float>*obj = new csvImport<float>(fileName);
    //instanciação objeto classe como float
    bool header = obj->headerCheck();
    //header check verifica letras na primeira linha se sim pula;
/*obj->interaction();//interaction questiona usuário sobre a presença de cabeçalho
fiz de duas formas, perguntando e identificando a presença de letras no cabeçalho
mas caso exista cabeçalho apenas numerico podemos usar essa função*/
    if (obj->getType() == false){//função verifica o tipo de dado
        delete obj;//caso nao haja ponto, o  dado é int excluimos a instancia
        obj = nullptr;//ponteiro anulado 
        state = false;//variavel de estado para falso
        }
    if (!state){//se state false o dado é int
        csvImport<int>*obj2 = new csvImport<int>(fileName);
        //instanciamos o segundo objeto agora com formato adequado
        obj2->geraTabela();
        //função preenche a matriz criada pelo construtor com dados do arquivo
        cout << "Dados lidos do arquivo:" << endl;//mensagem informativa
        obj2->printData();//impressão da matriz baseada nos dados lidos
        delete obj2;//exclusao do objeto criado anteriormente
        obj2 = nullptr;//anula ponteiro
    }
    else{//se for float segue o baile 
    // Obtém os dados do arquivo
    obj->geraTabela();//le e preenche matriz com dados do arquivo
    cout << "Dados lidos do arquivo:" << endl;//mensagem informativa
    obj->printData();  // Chama a função de impressão
    delete obj;//exclui memoria no final
    }
    return 0;//se main concluida com secesso retorna 0
}

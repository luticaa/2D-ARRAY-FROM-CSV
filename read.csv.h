/*Este código tem como objetivo criar a classe para o programa que
irá retornar o endereço de um array bidimensional com os dados de
leitura do arquivo csv para o projeto 1 da disciplina PROGRAMAÇÃO
ORIENTADA A OBJETOS.
lucas Antônio Cunha Rodrigues da Silva - 14/12/2024 14:17*/
#include <fstream> // Diretriz pré-processamento fluxo de arquivo;
#include <iostream>//Diretriz pré-processamento fluxo de entrada e saída;
#include <sstream>//Diretriz pré-processamento fluxo string
#include <string>//Diretriz pré-processamento biblioteca string
#include <typeinfo>//Diretriz pré-processamento biblioteca informação tipo
#include<cctype>//Diretriz pré-processamento biblioteca tipo
using namespace std;//Define namespace std como padrão 

template <typename T> //template T para padronização do tipo (float/int)
class csvImport{//declaração classe csvImport
    private://DADOS PRIVADOS
        string delimitador; //delimitador para leitura do arquivo
        string nomeArquivo;//nome do arquivo a ser lido
        string linha; //variavel linha a ser utilizada nas leituras das linhas 
        char caractere;//variavel caractere usada na identificação de float ('.')
        bool isThereAHeader;//variavel armazena a presença de Header ou nao;
        int maxLinhas;//valor inicial para instanciação do objeto fixada em 1000
        int maxColunas;//valor inicial para instanciação do objeto fixada em 1000
        int linhaAtual;//variavel para contagem das linhas presentes no arquivo
        int colunaAtual;//variavel para contagem das colunas presentes no arquivo
        T** tabela;//ponteiro duplo nosso retorno desejado pela função
    public:
        void setMaxLinhas(int maxLines);//assinaturas das setters
        void setMaxColunas(int maxCols);
        void setDelimitador(string newDel);
        void setIsThereAHeader(bool level);
        int getMaxLinhas();//assinatura das getters
        int getMaxColunas();
        bool getType();
        //void interaction();
        bool headerCheck();
        //função verifica se é cabeçalho ou não baseado na presença de letra
        string getDelimitador();//caso deseje saber o delimitador sendo usado
        csvImport(const string& arquivo){
            /*construtor da nossa classe já cria um array dinâmico bidimensional
            bem como ajusta os parâmetros nessários para o código*/
            delimitador = ",";
            nomeArquivo = arquivo;
            maxLinhas = 1000;
            maxColunas = 1000;
            tabela = new T*[maxLinhas];
        for (int i = 0; i < maxLinhas; ++i) {
            tabela[i] = new T[maxColunas];
        }
        }
        T** geraTabela(){ /*função para obter dados do arquivo e faz o 
            redimensionamento no final para o tamanho obtido no arquivo*/
            ifstream arquivo(nomeArquivo);  // Abrir o arquivo para leitura
            if (!arquivo.is_open()) {
    //caso erro na abertura informa usuário isso se repete algumas vezes no codigo
                cout << "Erro ao abrir o arquivo!" << endl;
            tabela = nullptr;
            return tabela;  // Retorna um array vazio em caso de erro
    }
            //variaveis linha e coluna atuais para incremento no loop
            linhaAtual = 0;
            colunaAtual = 0;
            if (isThereAHeader){//se a variavel Header é true pulamos a primeira
                getline(arquivo, linha);
            }
        // Lê o arquivo linha por linha
            while (getline(arquivo, linha) && linhaAtual < maxLinhas) {
                stringstream ss(linha);//fluxo de leitura linha arquivo
                string item; //variavel que ira armazenar o valor lido do fluxo
                colunaAtual = 0;//variavel acumuladora colunas
                
                while(getline(ss, item, delimitador[0])&& colunaAtual < maxColunas){
                    stringstream(item)>>tabela[linhaAtual][colunaAtual];
                    //salva na matriz e Converte para o tipoT
                    colunaAtual++;//incrementa coluna a cada item
                        }
                    linhaAtual++;//incrementa linha a cada grupo de colunas
                }
            arquivo.close();  // Fecha o arquivo após a leitura
            //como agora conhecemos o tamanho da lista vamos realocar a memoria
            T** temp = new T*[linhaAtual];
            //alocando um novo local de memoria do tamanho ideal
            for (int i = 0; i<linhaAtual;i++){
                temp[i] = new T[colunaAtual];
            }
            for (int i = 0;i<linhaAtual;i++){//salvando dados no novo local temp
                for(int j = 0; j<colunaAtual; j++){
                    temp[i][j] = tabela[i][j];
                }
            }
           
            for (int i = 0; i < maxLinhas; ++i){
                //exclusao memoria inicialmente alocada
                delete[] tabela[i]; //Libera cada linha do array
                    }
            delete[] tabela;  // Libera o ponteiro para as linhas de tabela
            tabela = temp;//agora tabela é igual a temp
            temp = nullptr;  //temp invalidado
            return tabela;//Retorna o ponteiro do array bidimensional com os dados
        }

        void printData() {//funçaõ impressão dos dados 
        for (int i = 0; i < linhaAtual; i++) {//loop fora linhas
            for (int j = 0; j < colunaAtual; j++) {//loop dentro colunas
                // Imprime o valor na célula
                cout <<"["<< tabela[i][j] <<"]"<<" ";
            //impressão...coloquei um par de colchete pra melhorar visualização
            }
            cout << endl;  // Nova linha após cada linha do array
        }
    }
    ~csvImport() {//destrutor fundamental para que nao haja 'MEMORY LEAK'
        for (int i = 0; i < maxLinhas; ++i) {//Remove a alocação dinamica
            delete[] tabela[i];  // Libera cada linha do array
        }
        delete[] tabela;  // Libera o ponteiro para as linhas
    }
};
/*aqui são todas as funções da classe
setters e getters funções de 1 linha muito simples preferi deixar aqui
apesar de ter que usar repetidas vezes o comando template mas achei que
visualmente (legibilidade) ficou melhor. Lá em cima temos construtor,
geraTabela e destrutor o resto todo está aqui. Algumas nao são usadas
mas estão ai caso seja necessário.*/
template <typename T> 
//caso haja necessidade de alterar o maximo de linhas
void csvImport<T> ::setMaxLinhas(int maxLines){
    maxLinhas = maxLines;
}
template <typename T>
//caso haja necessidade de alterar o maximo de colunas
void csvImport<T> ::setMaxColunas(int maxCols){
    maxColunas = maxCols;
}
template <typename T>
//caso seja necessário mudar o delimitador
void csvImport<T> ::setDelimitador(string newDel){
    delimitador = newDel;
}
template <typename T>
//função escreve na variável isThereAHeader, importante pra gente
void csvImport<T> ::setIsThereAHeader(bool level){
    isThereAHeader = level;
}
template <typename T>
//obtem max linhas
int csvImport<T> ::getMaxLinhas(){
    return maxLinhas;
}
template <typename T>
//obtem max colunas
int csvImport<T> ::getMaxColunas(){
    return maxColunas;
}
template <typename T>
//retorna delimitador sendo usado
string csvImport<T> ::getDelimitador(){
    return delimitador;
}
/*Função pergunta ao usuário se há cabeçalho ou nao, inicialmente estava usando-a
mas depois preferi identificar pela presença de letras na linha;
template <typename T>
void csvImport<T>::interaction(){
    char answer;
    cout<<"The file you're openning has a header??? (Y/N)"<<endl;
    cin>>answer;
    while(tolower(answer) != 'y' && tolower(answer) != 'n'){
        cout<<"Wrong answer please select 'Y' either 'N'"<<endl;
        cout<<"The file you're openning has a header??? (Y/N)"<<endl;
        cin>>answer; 
        }
    isThereAHeader = (tolower(answer) == 'y') ? true:false;
}*/
template <typename T>
//Função checa presença de letras na primeira linha, em substituição à anterior
bool csvImport<T>::headerCheck(){
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()){
                cout << "Erro ao abrir o arquivo!" << endl;
                return false;
                }
    getline(arquivo,linha);
        for (char caractere : linha) {
            //cout << "Caractere lido: " << caractere << endl;
            if (isalpha(caractere)) { 
                //se caractere alfanumerico a-z e A-Z retorna true
            arquivo.close();//fecha arquivo nesta condição
            return true;
        }
    }
    arquivo.close();//fecha arquivo caso nao entre no if anterior
    return false; 
}

template <typename T>
//função verifica o tipo lido buscando por '.'
bool csvImport<T>::getType(){
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return false;
        }
    if (isThereAHeader){
        getline(arquivo, linha); // Lê a linha e continua
    }
    getline(arquivo,linha);
    for (char caractere : linha) {
        //cout << "Caractere lido: " << caractere << endl;
        if (caractere == '.') {
        arquivo.close();
        return true;
        }
    }
    arquivo.close();
    return false;
    }
            arquivo.close();
            return false;
            }

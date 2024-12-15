/*Este código tem como objetivo criar a classe para o programa que
irá retornar o endereço de um array bidimensional com os dados de
leitura do arquivo csv para o projeto 1 da disciplina PROGRAMAÇÃO
ORIENTADA A OBJETOS.
lucas Antônio Cunha Rodrigues da Silva - 14/12/2024 14:17*/
#include <fstream> //FLUXO DE ARQUIVO
#include <iostream>//FLUXO ENTRADA E SAIDA
#include <sstream>//
#include <string>
#include <typeinfo>
using namespace std;

template <typename T>
class csvImport{
    private:
        string delimitador;
        string nomeArquivo;
        string linha;
        char caractere;
        int maxLinhas;
        int maxColunas;
        int linhaAtual;
        int colunaAtual;
        T** tabela;
    public:
        void setMaxLinhas(int maxLines);
        void setMaxColunas(int maxCols);
        void setDelimitador(string newDel);
        int getMaxLinhas();
        int getMaxColunas();
        bool getType();
        string getDelimitador();
        csvImport(const string& arquivo){
            delimitador = ",";
            nomeArquivo = arquivo;
            maxLinhas = 1000;
            maxColunas = 1000;
            tabela = new T*[maxLinhas];
        for (int i = 0; i < maxLinhas; ++i) {
            tabela[i] = new T[maxColunas];
        }
        }

        T** geraTabela(){
            ifstream arquivo(nomeArquivo);  // Abrir o arquivo para leitura
            if (!arquivo.is_open()) {
                cout << "Erro ao abrir o arquivo!" << endl;
            tabela = nullptr;
            return tabela;  // Retorna um array vazio em caso de erro
    }
            //string linha;
            linhaAtual = 0;
            colunaAtual = 0;
            getline(arquivo, linha);//descartando cabeçalho
        
        // Lê o arquivo linha por linha
            while (getline(arquivo, linha) && linhaAtual < maxLinhas) {
                stringstream ss(linha);
                string item;
                colunaAtual = 0;
                // Lê cada coluna da linha
                while (getline(ss, item, delimitador[0]) && colunaAtual < maxColunas) {
                    stringstream(item)>>tabela[linhaAtual][colunaAtual];  // Converte para o tipo T
                    colunaAtual++;
                        }
                    linhaAtual++;
                }
            arquivo.close();  // Fecha o arquivo após a leitura
            
            //MUDAR O PONTEIRO PARA ENXUGAR MEMÓRIA AQUI
            
            
            return tabela;  // Retorna o ponteiro do array bidimensional com os dados
        }

        void printData() {
        for (int i = 0; i < linhaAtual; i++) {
            for (int j = 0; j < colunaAtual; j++) {
                // Imprime o valor na célula
                cout << tabela[i][j] << " ";
            }
            cout << endl;  // Nova linha após cada linha do array
        }
    }
    ~csvImport() {
        for (int i = 0; i < maxLinhas; ++i) {
            delete[] tabela[i];  // Libera cada linha do array
        }
        delete[] tabela;  // Libera o ponteiro para as linhas
    }
};
template <typename T>
void csvImport<T> ::setMaxLinhas(int maxLines){
    maxLinhas = maxLines;
}
template <typename T>
void csvImport<T> ::setMaxColunas(int maxCols){
    maxColunas = maxCols;
}
template <typename T>
void csvImport<T> ::setDelimitador(string newDel){
    delimitador = newDel;
}
template <typename T>
int csvImport<T> ::getMaxLinhas(){
    return maxLinhas;
}
template <typename T>
int csvImport<T> ::getMaxColunas(){
    return maxColunas;
}
template <typename T>
string csvImport<T> ::getDelimitador(){
    return delimitador;
}
template <typename T>
bool csvImport<T>::getType(){
            ifstream arquivo(nomeArquivo);
            if (!arquivo.is_open()){
                cout << "Erro ao abrir o arquivo!" << endl;
                return false;
                }
            getline(arquivo,linha);
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
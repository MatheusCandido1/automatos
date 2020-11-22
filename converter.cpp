#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

using namespace std;

int quantidade_funcoes = 0;
int num_estado_final = 0;
vector<int> estado_inicial;

void lerArquivo(vector<int> &origem, vector<char> &letra, vector<vector<int>> &num, vector<int> &estados_finais, char* afn){
    string formalismo;
    int num_estados;
    int num_simbolos;

    vector<char> simbolos;
    vector<int> estados;

    int n1,n2;
    char c1;
    int n = 0;
    ifstream file;
    string temp;
    file.open("afn.txt");


        // Lendo formalismo
        getline(file, formalismo);

        // Lendo numero de estados

        getline(file, temp);
        num_estados = (int)temp[0] - 48;


        // Lendo todos os estados
        for(int i = 2; i <= num_estados * 2; i = i+2){
            estados.push_back((int)temp[i] - 48);
        }

        // Lendo numero de simbolos
        getline(file, temp);
        num_simbolos = (int)temp[0] - 48;

        // Lendo todos os simbolos
       for(int i = 2; i <= num_simbolos * 2; i = i+2){
            simbolos.push_back(temp[i]);
        }

        // Lendo Estado Inicial
        getline(file, temp);
        estado_inicial.push_back((int)temp[0] - 48);

        // Lendo numero de estados finais
        getline(file, temp);
        num_estado_final = (int)temp[0] - 48;


        // Lendo todos os estados finais
       for(int i = 2; i <= num_estado_final * 2; i = i+2){
            estados_finais.push_back((int)temp[i] - 48);
        }

        while(!file.eof()){
        // Preenchendo Origem
        getline(file, temp);
        origem.push_back((int)temp[0] - 48);

        // Preenchendo Letras
        letra.push_back(temp[2]);

        vector<int> newTemp;
        for(int i = 4; i <= temp.size(); i = i + 2){
            newTemp.push_back((int)temp[i] - 48);
        }


        // Montando Arrays de Regras
        num.push_back(newTemp);
        quantidade_funcoes++;
    }

    file.close();
}

void escreverArquivo() {
    ofstream file;
    file.open("teste1.txt");
    file << "AFD" << endl;
    file.close();
}

int existeRegra(vector<int> origem, vector<char> letra, vector<int> num, char palavra, int EA) {
    if(palavra == '\0') {
        return EA;
    }
    for(int i = 0; i < origem.size(); i++) {
        if(origem[i] == EA && letra[i] == palavra){
            return num[i];
        }
    }
    return -1;
}

bool verificarEstados(int estado_atual, vector<int> estados_finais) {
    for(int i = 0; i < estados_finais.size(); i++){
    if(estado_atual == estados_finais[i]) {
        return true;
        }
    }
    return false;
}

vector<int> findIndex(vector<int> origem, int valorBusca) {
    vector<int> resultante;
    for(int i = 0; i < origem.size(); i++){
        if(origem[i] == valorBusca){
            resultante.push_back(i);
        }
    }
    return resultante;
}

bool existe(vector<vector<int>> usados, vector<int> valor)
{
    for(int i = 0; i < usados.size(); i++){
        if(usados[i] == valor){
            return true;
        }
    }
    return false;
}

vector<int> concat(vector<int> v1, vector<int> v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
    sort( v1.begin(), v1.end() );
    v1.erase( unique( v1.begin(), v1.end() ), v1.end() );
    return v1;
}

bool pertence(vector<int> value, vector<vector<int>> array) {
    if(find(array.begin(), array.end(), value) != array.end()) {
        return true;
    }
    return false;
}

void imprimeFila(queue<vector<int>> temp) {
    while (!temp.empty()) {

    vector<int> p2(temp.front());
    cout << "Elemento: ";
    for(int i =0; i < p2.size(); i++){
    cout <<  p2[i] << ",";
    }
    cout << endl;
    temp.pop();
    }
    cout << endl;
}

int main(int argc, char *argv[])
{

    vector<int> origem;
    vector<char> letra;
    vector<vector<int>> num;
    vector<int> estados_finais;

    vector<string> palavras;
    lerArquivo(origem, letra, num, estados_finais, argv[1]);

    queue<vector<int>> etapas;
    vector<vector<int>> usados;
    etapas.push(estado_inicial);
    usados.push_back(estado_inicial);

    vector<vector<int>> resultante_origem;
    vector<char> resultante_letra;
    vector<vector<int>> resultante_numero;

    while (!etapas.empty()) {
        vector<int> estado_atual = etapas.front();

        etapas.pop();
        vector<int> indice;

        vector<int> tempIndice;


        cout << "Estado atual: " << endl;
        for(int i = 0; i < estado_atual.size(); i++){
            tempIndice = findIndex(origem, estado_atual[i]);
            indice = concat(tempIndice, indice);
            cout << estado_atual[i];
        }

        char letraTempo = 'a';
        vector<int> concatTempo;

        for(int i = 0; i < indice.size(); i++){
            cout << "Fila: ";
            imprimeFila(etapas);
            cout <<"Indice: " << indice[i] << endl;
            if(i+1 <= indice.size() && letra[i] != letra[i+1]) {

                cout << "Letra Atual: " << letra[i] << endl;
                //recebe estado atual concatenado
                resultante_origem.push_back(estado_atual);
                resultante_letra.push_back(letra[i]);
                for(int j = 0; j < num[i].size(); j++) {
                    cout << "Resultado num: " << num[i][j] << endl;
                }
                vector<int> saida_numero = concat(concatTempo,num[i]);
                resultante_numero.push_back(saida_numero);
        for(int x = 0; x < saida_numero.size(); x++) {
            cout << "Saida Numero: " << saida_numero[x] << endl;
        }

        cout << "Saida função pertence: " << pertence(saida_numero,usados) << endl;
                if(!pertence(saida_numero,usados)) {
                    etapas.push(saida_numero);
                    usados.push_back(saida_numero);
                }
            }
            else {
                 cout << "entrou else";
                concatTempo = concat(concatTempo,num[i]);
                letraTempo = letra[i];
            }
        }
    }


 /*    cout << "Origem  |  Letra  |  Saida" << endl;
    for(int x = 0; x < resultante_origem.size(); x++) {
        for(int z = 0; z < resultante_origem[x].size(); z++)
            cout << resultante_origem[x][z];
        cout << " | " << resultante_letra[x] << " | ";
        for(int z = 0; z < resultante_numero[x].size(); z++)
            cout << resultante_numero[x][z];
        cout << endl;
    }*/
/*
    cout << "-------------" << endl;
    cout << "ORIGENS" << endl;
    for(int x = 0; x < resultante_origem.size(); x++) {
        for(int z = 0; z < resultante_origem[x].size(); z++)
            cout << resultante_origem[x][z];
    }

    cout << "-------------" << endl;
    cout << "SAIDAS" << endl;
    for(int x = 0; x < resultante_numero.size(); x++) {
        for(int z = 0; z < resultante_numero[x].size(); z++)
            cout << resultante_numero[x][z];
    }
//    escreverArquivo(); */


    return 0;
}

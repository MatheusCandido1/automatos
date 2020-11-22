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
            newTemp.push_back(temp[i]);
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

int main(int argc, char *argv[])
{
    vector<int> origem;
    vector<char> letra;
    vector<vector<int>> num;
    vector<int> estados_finais;

    vector<string> palavras;
    lerArquivo(origem, letra, num, estados_finais, argv[1]);

    queue <vector<int>> etapas;
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


        for(int i = 0; i < estado_atual.size(); i++){
            indice = findIndex(origem, estado_atual[i]);
        }

        char letraTempo = 'a';
        vector<int> concatTempo;

        for(int i = 0; i < indice.size(); i++){
            if(letraTempo == letra[i]) {
                //recebe estado atual concatenado
                resultante_origem.push_back(estado_atual);
                resultante_letra.push_back(letra[i]);
                vector<int> saida_numero = concat(concatTempo,num[i]);
                resultante_numero.push_back(saida_numero);
                if(!pertence(saida_numero,usados)) {
                    etapas.push(saida_numero);
                    usados.push_back(saida_numero);
                }
            }
            else {
                concatTempo = concat(concatTempo,num[i]);
                letraTempo = letra[i];
            }
        }
    }


    // for(int x = 0; x < resultante_letra.size(); x++) {
    //     cout << "Origem: " << resultante_origem[x] << " - " << "Letra: " << resultante_letra[x] << " - " << "Destino: " << resultante_numero[x] << endl;
    // }

//    escreverArquivo();


    return 0;
}

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

vector<char> simbolos;

void lerArquivo(vector<int> &origem, vector<char> &letra, vector<vector<int>> &num, vector<int> &estados_finais, char* afn){
    string formalismo;
    int num_estados;
    int num_simbolos;


    vector<int> estados;

    int n1,n2;
    char c1;
    int n = 0;
    ifstream file;
    string temp;
    file.open(afn);


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

bool pertenceSimples(int value, vector<int> array) {
    if(find(array.begin(), array.end(), value) != array.end()) {
        return true;
    }
    return false;
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
    for(int i =0; i < p2.size(); i++){
    }
    temp.pop();
    }
}

int main(int argc, char *argv[])
{

    vector<int> origem;
    vector<char> letra;
    vector<vector<int>> num;
    vector<int> estados_finais;
    vector<vector<int>> res_estados_finais;

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


        for(int i = 0; i < estado_atual.size(); i++){
            tempIndice = findIndex(origem, estado_atual[i]);
            indice = concat(tempIndice, indice);
        }

        char letraTempo = 'a';
        vector<int> concatTempo;
        for(int j = 0; j < estados_finais.size(); j++) {
            if(pertenceSimples(estados_finais[j], estado_atual)) {
                res_estados_finais.push_back(estado_atual);
            }
        }
        for(int i = 0; i < indice.size(); i++){
            imprimeFila(etapas);
            if(i+1 <= indice.size() && letra[indice[i]] != letra[indice[i]+1]) {

                //recebe estado atual concatenado
                resultante_origem.push_back(estado_atual);
                resultante_letra.push_back(letra[indice[i]]);
                for(int j = 0; j < num[indice[i]].size(); j++) {
                }
                vector<int> saida_numero = concat(concatTempo,num[indice[i]]);
                resultante_numero.push_back(saida_numero);
        for(int x = 0; x < saida_numero.size(); x++) {
        }

                if(!pertence(saida_numero,usados)) {
                    etapas.push(saida_numero);
                    usados.push_back(saida_numero);
                }
            }
            else {
                concatTempo = concat(concatTempo,num[indice[i]]);
                letraTempo = letra[indice[i]];
            }
        }
    }



    vector<vector<int>> new_estados = resultante_numero;
    sort( new_estados.begin(), new_estados.end() );
    new_estados.erase( unique( new_estados.begin(), new_estados.end() ), new_estados.end() );



    ofstream file;
    file.open(argv[2]);
    file << "AFD" << endl;
    file << new_estados.size() + 1 << " " << estado_inicial[0];
    for(int j = 0; j < new_estados.size(); j++){
        file << " ";
    for(int i = 0; i < new_estados[j].size(); i++){
       file << new_estados[j][i];
    }
    }
    file << endl;
    file << simbolos.size();
    for(int i = 0; i < simbolos.size(); i++){

        file << " " << simbolos[i];
    }

    file << endl;
    file << res_estados_finais.size()-1;
      for(int i = 0; i < res_estados_finais.size()-1; i++) {
             file << " ";
        for(int j = 0; j < res_estados_finais[i].size(); j++){
          file << res_estados_finais[i][j];
        }
    }
    file << endl;
    for(int i = 0; i < resultante_origem.size(); i++){
             for(int j = 0; j < resultante_origem[i].size(); j++){
            file << resultante_origem[i][j];
        }
        file <<  " " << resultante_letra[i] << " ";
        for(int j = 0; j < resultante_numero[i].size(); j++){
            file << resultante_numero[i][j];
        }
        file << endl;
    }


    file.close();



    return 0;
}

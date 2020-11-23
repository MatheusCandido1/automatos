#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

using namespace std;

int quantidade_funcoes = 0;
int num_estado_final = 0;
int estado_inicial = 0;

void lerArquivo(vector<int> &origem, vector<char> &letra, vector<int> &num, vector<int> &estados_finais, char* afd){
    string formalismo;
    int num_estados;
    int num_simbolos;

    vector<char> simbolos;
    vector<int> estados;

    ifstream file;
    string temp;
    file.open(afd);

    int n1,n2;
    char c1;
    int n = 0;

        getline(file, formalismo);

        // Lendo número de estados*/

        getline(file, temp);
        num_estados = (int)temp[0] - 48;

        // Lendo todos os estados
        for(int i = 2; i <= num_estados * 2; i = i+2){
            estados.push_back((int)temp[i] - 48);
        }


        // Lendo número de simbolos
        getline(file, temp);
        num_simbolos = (int)temp[0] - 48;

        // Lendo todos os simbolos
         for(int i = 2; i <= num_simbolos * 2; i = i+2){
            simbolos.push_back(temp[i]);
        }

        // Lendo Estado Inicial
        getline(file, temp);
        estado_inicial = (int)temp[0] - 48;

        // Lendo número de estados finais
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


        num.push_back((int)temp[4] - 48);
        quantidade_funcoes++;
    }
    for(int i = 0; i < num.size(); i++){
        cout << num[i];
    }
    file.close();
}

void lerPalavra(vector<string> &palavras, char* entrada){
    int n = 0;
    FILE *file = fopen(entrada,"r");
    while(!feof(file)){
        string palavra(10,'\0');
        fscanf(file, " %s",palavra.c_str());
        palavras.push_back(palavra);
    }
}

void escreverArquivo(vector<int> origem, vector<char> letra, vector<int> num) {
    for(int i = 0; i < quantidade_funcoes; i++){
        cout << origem[i] << " ";
        cout << letra[i] << " ";
        cout << num[i] << endl;
    }
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

int main(int argc, char *argv[])
{
    vector<int> origem;
    vector<char> letra;
    vector<int> num;
    vector<int> estados_finais;

    vector<string> palavras;

    lerArquivo(origem, letra, num, estados_finais, argv[1]);
    lerPalavra(palavras, argv[2]);

    ofstream file;

    file.open(argv[3]);

    for(int j = 0; j < palavras.size(); j++) {
        file << palavras[j];
        int EA = estado_inicial;
        for(int i = 0; i < palavras[j].size(); i++) {

            if(palavras[j][i] == '_')
            {
                break;
            }
            EA = existeRegra(origem, letra,num, palavras[j][i], EA);
            if(EA == -1) {
                break;
            }
        }

        if(verificarEstados(EA, estados_finais)) {
           file << " aceita" << endl;
        } else {
           file << " rejeita" << endl;
        }

    }
    file.close();
    return 0;
}

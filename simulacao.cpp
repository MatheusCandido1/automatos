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

    int n1,n2;
    char c1;
    int n = 0;
    FILE *file = fopen(afd,"r");

        // Lendo formalismo
        fscanf(file, " %s", formalismo);

        // Lendo número de estados*/

        fscanf(file, "%d", &num_estados);

        // Lendo todos os estados
        for(int i = 0; i < num_estados; i++){
            int aux;
            fscanf(file, "%d", &aux);
            estados.push_back(aux);
        }

        // Lendo número de simbolos
        fscanf(file, "%d", &num_simbolos);

        // Lendo todos os simbolos
        for(int i = 0; i < num_simbolos; i++){
            char aux;
            fscanf(file, " %c", &aux);
            simbolos.push_back(aux);
        }

        // Lendo Estado Inicial
        fscanf(file, "%d", &estado_inicial);

        // Lendo número de estados finais
        fscanf(file, "%d", &num_estado_final);

        // Lendo todos os estados finais
        for(int i = 0; i < num_estado_final; i++){
            int aux;
            fscanf(file, "%d", &aux);
            estados_finais.push_back(aux);
        }

        while(!feof(file)){
        // Preenchendo Origem
        fscanf(file, "%d",&n1);

        // Preenchendo Letras
        fscanf(file, " %c",&c1);

        // Preenchendo Num
        fscanf(file, "%d",&n2);

        // Montando Arrays de Regras
        origem.push_back(n1);
        letra.push_back(c1);
        num.push_back(n2);
        quantidade_funcoes++;
    }
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

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


int main()
{
}

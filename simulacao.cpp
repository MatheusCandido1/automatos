#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

using namespace std;

void lerArquivo(int origem[7], char letra[7], int num[7]){
    int n1,n2;
    char c1;
    int n = 0;
    FILE *file = fopen("afd.txt","r");
    while(!feof(file)){
        fscanf(file, "%d",&n1);
        fscanf(file, " %c",&c1);
        fscanf(file, "%d",&n2);
        origem[n] = n1;
        letra[n] = c1;
        num[n] = n2;
        n++;
    }
}

void lerPalavra(char palavra[6]){
    int n = 0;
    FILE *file = fopen("entrada.txt","r");
    while(!feof(file)){
        fscanf(file, " %s",palavra);
    }
}

void escreverArquivo(int origem[7], char letra[7], int num[7]) {
    for(int i = 0; i < 7; i++){
        cout << origem[i] << " ";
        cout << letra[i] << " ";
        cout << num[i] << endl;
    }
}

int existeRegra(int origem[7], char letra[7], int num[7], char palavra, int EA) {
    for(int i = 0; i < 7; i++) {
        if(origem[i] == EA && letra[i] == palavra){
            return num[i];
        }
    }
    return -1;
}

int main()
{
    int origem[7];
    char letra[7];
    int num[7];

    char palavra[6];

    lerArquivo(origem, letra, num);
    escreverArquivo(origem, letra, num);
    lerPalavra(palavra);

    int EA = 0, EF = 3;

    for(int i = 0; i < 6; i++) {
        EA = existeRegra(origem, letra,num, palavra[i], EA);
        if(EA == -1) {
            break;
        }
    }

    if(EA == EF) {
        cout << "aceita";
    } else {
        cout << "rejeita";
    }



    return 0;
}

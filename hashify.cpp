#include <iostream>

using namespace std;

struct Musica{
    int tempo = 0;
    int tempoTotal = 0;
    string nome;
    int chave = 0;
    int flag = -1;
};
struct Tabela{
    Musica *musiquinha;
    int tamt = 0;
    int total = 0;
};
int funcaoHash(string nome){

    int tam = nome.size();
    int c = 0;
    for(int cont = 0; cont < tam; cont++){
        c += nome[cont]*cont;
    }      
    return c;
}

int dispercao(int key, Tabela *item){

    int ho = 0, flag = 0, cont = 0;
    ho = key % (item->tamt);
    flag = ho;
    while(item->musiquinha[flag].flag != 0){
        flag = (ho + cont) % item->tamt;
        cont++;
    }
    item->musiquinha[flag].flag = 1;
    return flag;
}
void add(int posicao, Tabela *item, Musica nome){
    
    item->musiquinha[posicao] = nome;
    item->total += 1;
}
void rehashing(Tabela *item){

    Tabela hash;
    int tamanho = 0, cont = 0;
    
    tamanho = (item->tamt * 2) + 1;
    hash.musiquinha = (Musica*)calloc(tamanho, sizeof(Musica));
    hash.tamt = tamanho;
    for(cont = 0; cont < item->tamt; cont++){
        if(item->musiquinha[cont].flag != 0){
            int posicao = dispercao(item->musiquinha[cont].chave, &hash);
            add(posicao, &hash, item->musiquinha[cont]);
        }
    }
    free(item->musiquinha);
    *item = hash;
}

void jouedetemps(Tabela *item, bool decision){

    Musica musiquinha;
    int chave = 0, posicao = 0, flag = 1, cont = 0;

    cin >> musiquinha.nome;
    chave = funcaoHash(musiquinha.nome);

    while(flag){
        posicao = (chave + cont) % item->tamt;

        if(musiquinha.nome == item->musiquinha[posicao].nome){

            if (decision) item->musiquinha[posicao].tempoTotal += item->musiquinha[posicao].tempo;
            cout << musiquinha.nome << " " << item->musiquinha[posicao].tempoTotal<<endl;
            flag = 0;
        }
        cont++;
    }
}

int main(){

    int tamHash = 0, tempo = 0, flag = -1,hashOcupado = 0;
    string funcao, musica;
    Musica musiquinha;
    Tabela item;
    int posicao = 0, key = 0;

    cin >> tamHash;
    item.musiquinha = (Musica*)calloc(tamHash,sizeof(Musica));
    
    item.tamt = tamHash;

    while(flag != 0){
        cin >> funcao;

        if(funcao == "ADD"){
            
            cin >> musiquinha.nome >> musiquinha.tempo;
            if (item.total -1 >= item.tamt/2) {
                rehashing(&item);
            }
            
            key = funcaoHash(musiquinha.nome);

            posicao = dispercao(key, &item);
            musiquinha.chave = key;
            add(posicao, &item, musiquinha);           
            cout << musiquinha.nome <<" "<< posicao << endl;
        }

        else if(funcao == "PLAY"){
            jouedetemps(&item, true);
        }
        else if(funcao == "TIME"){
            jouedetemps(&item, false);
        }
        else if(funcao == "END")flag = 0;
    }
    
    return 0;
}
#include <iostream>
using namespace std;

class loja
{
public:
    int qtdItens, minItens, maxDinheiro;
    int contador, itens;
    int itensArray[31];

    void casos(int caso){
        contador = 0;
        itens = 0;
        cin >> qtdItens;
        itensArray[qtdItens];
        for (int j = 0; j < qtdItens; j++)
        {
            cin >> itensArray[j];
        }
        cin >> minItens;
        cin >> maxDinheiro;

        if(minItens == 0){ 
            contador = 1; 
        }
        start(0, 0);
        
        cout << "caso " << caso << ": "<< contador << endl;
        contador = 0;
        itens = 0;
    }
    
    
    
    void start(int cur, int soma){
    if(qtdItens == cur){ //ta no final?
        return;
    } 

    else if(soma + itensArray[cur] <= maxDinheiro){ //testo se ja passo dinheiro
        itens++;
        
        if(itens >= minItens){ //checo se o numero de itens ja passou do minimo
            contador++; 
        }
        start(cur+1, (soma+itensArray[cur])); //chamo a funcao dnv continuando a partir do caso que ta funcionando
        itens--; 
    }
    start(cur+1, soma);
    }

    
};

int main() {   
    loja loja;
    int qtdCasos;
    cin >> qtdCasos;

    for (int i = 0; i < qtdCasos; i++)
    {
        loja.casos(i);     
    }
   return 0;
}
#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;
struct Hospital{
    int id = 0;
    int casos = 0;
};

struct Heap{
    Hospital hospital;
    int tam = 0;
    int tamOcupado = 0;
};
Heap* heapify(Heap *heap, int posicao){
    int left, right, mid;
    Heap aux;
    left = 2*posicao + 1;
    right = 2*posicao + 2;
    mid = posicao;
    if(left < heap->tam && heap[left].hospital.casos >= heap[mid].hospital.casos){
        mid = left;
    }
    if(right < heap->tam && heap[right].hospital.casos >= heap[mid].hospital.casos){
        mid = right;
    }
    if(mid != posicao){
        aux.hospital = heap[mid].hospital;
        heap[mid].hospital = heap[posicao].hospital;
        heap[posicao].hospital = aux.hospital;
        return heapify(heap, mid);
    }
    return heap;
}
Heap* bubbleUp(Heap *heap, int posicao) {
    int indice = posicao - 1;
    Heap aux;
    while(indice > 0 && heap[indice].hospital.casos >= heap[(indice-1)/2].hospital.casos){
        aux.hospital = heap[indice].hospital;
        heap[indice].hospital = heap[(indice-1)/2].hospital;
        heap[(indice-1)/2].hospital = aux.hospital;
        indice = (indice-1)/2;
    }
    return heap;
}
Heap* deletar(Heap *heap, int id) {
    Heap aux;
    aux.hospital = heap[id].hospital;
    heap[id].hospital = heap[heap->tam-1].hospital;
    heap[heap->tam-1].hospital = aux.hospital;
    heap->tam--;
    heapify(heap, id);
    return heap;
}
Heap* inserir(Heap *heap, int casos) { 
    heap[heap->tam-1].hospital.casos = casos;
    heap[heap->tam-1].hospital.id = heap->tamOcupado - 1;
    heap = bubbleUp(heap, heap->tam);
    return heap;
}
Heap* heapar(Heap *heap, int tam){
    for(int contador = floor(tam/2)-1; contador >= 0; contador --){
        heapify(heap, contador);
    }
    return heap;
}
// void startHeap(int tam_Inicial){
//     int val;
//     //Heap *heap = new Heap[tam_Inicial];
//     Heap *heap = NULL;
//     heap = (Heap *) calloc(tam_Inicial, sizeof(Heap));
//     for(int contador = 0; contador < tam_Inicial; contador++){
//         cin >> val;
//         heap[contador].casos = val;
//         heap[contador].id = contador;  
//     }
//     heapar(heap, tam_Inicial);
// }

int main(){
    int tam, casos, id, somatorio = 0, pag, resto;
    char comando[4];
    Heap *heap = NULL;
    
    cin >> tam;
    //Heap *heap = new Heap[tam_Inicial];
    heap = (Heap*)calloc(tam,sizeof(Heap));

    for(int contador = 0; contador < tam; contador++){
        cin >> casos;
        somatorio = somatorio + casos;
        heap->tamOcupado++;
        heap->tam++;
        heap = inserir(heap, casos);
    }
    scanf(" %s", comando);
    while(strcmp(comando, "END") != 0){
        
        if(strcmp(comando, "NEW") == 0){
            cin >> id;
            cin >> casos;
            
            heap->tamOcupado++;
            heap->tam++;
            somatorio = somatorio + casos;
            //cout << somatorio << endl;
            heap = (Heap*)realloc(heap, heap->tam*sizeof(Heap));
            heap = inserir(heap, casos);
            // for(int contador = 0; contador < tam; contador++){
            //     cout << heap[contador].hospital.casos << "|" << heap[contador].hospital.id<<endl;
            // }
            cout << heap[0].hospital.id << " " << heap[0].hospital.casos << endl;;
        }
        else if(strcmp(comando, "DEL") == 0){
            cin >> id;
            if(heap->tam == 0){
                cout << "-1 -1"<< endl;
                somatorio = 0;
            }
            else{
                for(int contador = 0; contador < heap->tam; contador++){
                    if(id == heap[contador].hospital.id){
                        somatorio -= heap[contador].hospital.casos;
                        heap[contador].hospital.casos = 0;
                        heap = deletar(heap, contador);
                        heap = (Heap*)realloc(heap, heap->tam*sizeof(Heap));
                        contador = heap->tam;
                        //for(int contador = 0; contador < tam; contador++){
                        //  cout << heap[contador].hospital.casos << "|" << heap[contador].hospital.id<<endl;
                        //}
                    }
                }
                cout << heap[0].hospital.id <<" " << heap->hospital.casos << endl;
            }
        }
        else if(strcmp(comando,"IN") == 0){
            cin >> id >> casos;
            somatorio += casos;
            for(int contador = 0; contador < heap->tam; contador++){
                if(id == heap[contador].hospital.id){
                    heap[contador].hospital.casos += casos;
                    cout << heap[contador].hospital.casos << endl;
                    heap = heapar(heap, heap->tam);
                    contador = heap->tam;
                }
            }
        }
        else if(strcmp(comando,"OUT") == 0){
            cin >> id >> casos;
            somatorio -= casos;
            for(int contador = 0; contador < heap->tam; contador++){
                if(id == heap[contador].hospital.id){
                    heap[contador].hospital.casos -= casos;
                    cout << heap[contador].hospital.casos << endl;
                    heap = heapar(heap, heap->tam);
                    contador = heap->tam;
                }
            }
        }
        else if(strcmp(comando, "PAY") == 0) 
        {
            
            cin >> pag;
            if((heap[0].hospital.casos - pag) > 0){
                heap = heapar(heap, heap->tam);
                somatorio -= pag;
                cout << resto;
            }
            else{
                heap->tam--;
                resto = pag - heap[0].hospital.casos;
                heap = deletar(heap, 0);
                heap =(Heap*)realloc(heap, heap->tam*sizeof(Heap));
                somatorio -= pag;
                cout << resto;
            }
            
        }
        scanf(" %s", comando);
    }
    cout << somatorio << endl;
    return 0;
}


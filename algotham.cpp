#include <iostream>


using namespace std;
#define LIM 1000000

typedef struct union_find{
    int pai;
    int size;
}union_find;


int checar_Click(char **matriz, int *clique1, int *clique2, int k, int n);
bool comparar_Click(int *clique1, int *clique2, int k);


int **build_matriz_teste(int **teste, int k, int n){
    int j, l;
    int aux = 0, flag = 0,i = 1, has_terminado = 0;
    for(j = 0; j < k; j++)
        teste[0][j] = j;
    
    while(has_terminado == 0){
        for(j = 0; j < k; j++)
            teste[i][j] = teste[i - 1][j];
        flag = 0;
        aux = 1;
        for(j = k - 1; flag == 0 && j >= 0; j--){
            if(teste[i][j] + 1 < n){
                teste[i][j] += 1;
                flag = 1;
            }
            if(flag == 1){
                for(l = 1; l < aux; l++){
                    if(teste[i][j + l - 1] + 1 < n) 
                        teste[i][j + l] = teste[i][ j + l - 1] + 1;
                    
                    else 
                        flag = 0;
                }
            }
            if(flag == 0)
                aux++;
        }
        i++;

        if(aux == k + 1)
            has_terminado = 1;

    }

    return teste;
}
char ***build_Matriz(char ***matriz, int x, int n){
    
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++)
            cin >> matriz[x][i][j];
    }
    return matriz;
}


int *find_Click(char **matriz, int *clique, int **teste, int k, int n);

int find(union_find *disj_Set, int i){
    if(disj_Set[i].pai != i)
        disj_Set[i].pai = find(disj_Set, disj_Set[i].pai);
    return disj_Set[i].pai;
}

union_find *uniao(union_find *disj_Set, int x, int y){
    x = find(disj_Set, x);
    y = find(disj_Set, y);
    if(disj_Set[x].size > disj_Set[y].size)
        disj_Set[y].pai = x;
        else 
            if(disj_Set[x].size < disj_Set[y].size)
                disj_Set[x].pai = y;
                else{
                    disj_Set[y].pai = x;
                    disj_Set[x].size += 1;
                }
    return disj_Set;
}

int main(){

    int x = 0, y = 0;
    int i, j, a, k, n, q, res;

    cin >> a >> n >> k >> q;
    union_find *disj_Set = new union_find[a];
    int *check = new int[a];
    int **clique = new int*[a];
    int *vet_chec = new int[a];
    char ***matriz = new char**[a];
    int **teste = new int*[LIM];
    
    for(i=0; i<a; i++){
        vet_chec[i] = 0;
        check[i] = 0;
        disj_Set[i].pai = i;
        disj_Set[i].size = 0;
        clique[i] = new int[k];
        matriz[i] = new char*[n]; 
        for(j=0; j<n; j++){
            matriz[i][j] = new char[n];
        }
    }
    
    for(i=0; i<LIM; i++)
        teste[i] = new int[k];
    
    teste = build_matriz_teste(teste, k, n);

    for(int iteracao = 0; iteracao < q; iteracao++){
        cin >> x >> y;
        res = 0;
        
        if(vet_chec[x] == 0){
            matriz = build_Matriz(matriz, x, n);
            vet_chec[x] = 1;
                
        }
        if(vet_chec[y] == 0){
            matriz = build_Matriz(matriz, y, n);
            vet_chec[y] = 1;
        }

        if(check[x] == 0){
            if(check[y] == 0){
                clique[x] = find_Click(matriz[x], clique[x], teste, k, n);
                check[x] = 1;
            }
            else check[x] = checar_Click(matriz[x], clique[y], clique[x], k, n);
            //else check[x] = checar_Click(matriz[x], clique[x], clique[y], n,k);
        }
        if(check[y] == 0)check[y] = checar_Click(matriz[y], clique[x], clique[y], k, n);


        if(disj_Set[x].pai==x && disj_Set[y].pai==y){
            if(comparar_Click(clique[x], clique[y], k)){
                disj_Set = uniao(disj_Set, x, y);
                res = 1;
            }
        }
        else if(disj_Set[x].pai!=x && disj_Set[y].pai!=y){
                x = find(disj_Set, x);
                y = find(disj_Set, y);
                if(x == y)res = 1;
                else{
                    //cout << "aqui2" << clique[x][i] << endl;
                    if(comparar_Click(clique[x], clique[y], k)){
                        disj_Set = uniao(disj_Set, x, y);
                        res = 1;
                    }
                }    
            }
            else if(disj_Set[x].pai==x && disj_Set[y].pai!=y){
                    if(find(disj_Set, y) == x)
                        res = 1;
                        else{
                            //cout << "aqui1" << clique[x][i] << endl;
                            if(comparar_Click(clique[x], clique[y], k)){
                                disj_Set = uniao(disj_Set, x, y);
                                res = 1;
                            }
                        }     
                }
                else{
                    if(find(disj_Set, x) == y)
                        res = 1;
                        else{
                            //cout << "aqui" << clique[x][i] << endl;
                            if(comparar_Click(clique[y], clique[x], k)){
                                disj_Set = uniao(disj_Set, y, x);
                                res = 1;
                            }
                        } 
                }
        if(res==1){
            cout << "SUCC ";
            for(i=0; i<k; i++){
                cout << clique[x][i];
                if(i+1 != k)
                    cout << " ";
            }
            cout << endl;
        }
        else  cout << "FAIL" << endl;
        
    }
    return 0;
}
int checar_Click(char **matriz, int *clique1, int *clique2, int k, int n){
    int i, j;
    int flag=0;
    for(i=k-1; i>0 && flag==0; i--){
        for(j=i-1; j>=0 && flag==0; j--){
            if(matriz[clique1[i]][clique1[j]] != '1')flag = 1;
        }
    }
    if(flag==0){
        for(i=0; i<k; i++)
            clique2[i] = clique1[i];
        return 1;
    }
    else 
        return 0;
}
bool comparar_Click(int *clique1, int *clique2, int k){
    bool result = true;
    for(int i=0; i<k; i++){
        if(clique1[i] != clique2[i]){
            i=k;
            result = false;
        }
    }
    return result;
}
int *find_Click(char **matriz, int *clique, int **teste, int k, int n){
    int i, j, found = 0, aux, m, falso, flag, x = 0;

    while(found==0){
        falso = 0;
        flag = 0;
        for(aux = k - 1; aux >= 0 && falso == 0; aux--){
            i=teste[x][aux];
            for( m = 1; m <= aux && falso == 0; m++){
                j=teste[x][aux-m];
                if( matriz[i][j] == '0')
                    falso = 1;
            }
        }
        if(falso==1)x++;
        
        else found = 1;

    }
    for(i=0; i<k; i++)clique[i] = teste[x][i];
    
    return clique;
}
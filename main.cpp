#include <sys/time.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <limits>
#include <string>
#include <vector>
#include <time.h>
#define V 300
#define inf 9999

int ultim;

void printArray(int **array, int size);

using namespace std;

void descompunDrum(int graf[][V],int i,int j,int size){
    int ok=0,k=1;
    while(k <= size && !ok){
    if(i != k && j != k)
        if(graf[i][j] == graf[i][k] + graf[k][j]){
            descompunDrum(graf,i,k,size);
            descompunDrum(graf,k,j,size);
            ok = 1;
        }
    k++;
    }
    if(!ok){
        if(j!=ultim)
            printf("(%d)->%d--",graf[i][j],j+1);
        else
            printf("(%d)->%d",graf[i][j],j+1);
    }

}

void print_floyd(int graf[][V], int nod_initial,int nod_final, int size){

    if(graf[nod_initial][nod_final] < inf && nod_initial != nod_final){
         cout << endl << nod_initial + 1 << "->" << nod_final + 1 << "\t\t" << graf[nod_initial][nod_final];
         cout << "\t\t" << nod_initial + 1 << "--";
         descompunDrum(graf, nod_initial,nod_final, size);
         ultim++;
     }else{
        cout << endl << nod_initial + 1 << "->" << nod_final + 1 << "\t\t-\t\t" << "Nu exista";
        ultim++;
     }
}

void print_dijkstra(int dist[], int src, int size){
    cout << "\n\nDrumul   Costul pina la sursa   Calea\n" ;
    for (int i = 0; i < size; i++)
        if(dist[i] == 0 || dist[i] > inf){
            cout << endl << src + 1 << "->" << i + 1 << "\t\t-\t\tNu exista";

        }else{
            cout << endl << src + 1 << "->" << i + 1 << "\t\t" << dist[i] <<"\t\t";

        }

}

int minDistance(int dist[], bool drum[], int size){
    int min = INT_MAX, minIndex;

    for (int v = 0; v < size; v++)
        if (drum[v] == false && dist[v] <= min){
            min = dist[v], minIndex = v;
        }

   return minIndex;
}

void dijkstra(int graf[V][V], int src, int size){
    cout << endl << endl << endl << endl;
    cout << "\n\nAlgoritmul lui Dijkstra.\n\n";

    int dist[size];
    bool drum[size];
    for (int i = 0; i < size; i++){
        dist[i] = INT_MAX;
        drum[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < size-1; count++){
        int u = minDistance(dist, drum, size);
        drum[u] = true;

        for (int v = 0; v < size; v++)
            if (!drum[v] && graf[u][v] && dist[u] != INT_MAX && dist[u]+graf[u][v] < dist[v]){
                dist[v] = dist[u] + graf[u][v];
            }
    }

    print_dijkstra(dist, src, size);
}

void Floyd(int graf[][V], int size){
    cout << "\n\nAlgoritmul lui Floyd.\n\n";
    int matrix[V][V], i, j, k;

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            matrix[i][j] = graf[i][j];

    for (k = 0; k < size; k++) {
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
    int x = 0;
    ultim = 0;
    cout << "\n\nDrumul   Costul pina la sursa   Calea" ;
    for (i = 0; i < size; i++)
        print_floyd(matrix,x,i,size);
}



double densitatea(){
    return (double)rand()/RAND_MAX;
}

short check = 0;

int **makeSymmetricArray(int size, int *muchiiGener, int fi){

    struct timeval good_seed;
    gettimeofday(&good_seed, NULL);
    srand((good_seed.tv_sec*1000 + good_seed.tv_usec/1000));

    int** array = new int*[size];
    for(int i=0;i<size;i++){
        array[i] = new int[size];
    }

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            array[i][j]=0;
        }
    }

    ofstream graf{"graf.txt"};

    if (!graf){
        cerr << "Nu s-a putut deschide fisierul pentru scriere" << endl;
         exit(-1) ;
    }
    graf << "digraph G {\nnode [shape = circle,height=.1];\n";
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(densitatea() > fi && i != j){
                array[i][j]=rand()%9 + 1;
                (*muchiiGener)++;
                graf << "\t" << i+1 << " -> " << j+1 << " [label=\""<< array[i][j]<< "\"]\n";
            }
            if(i == j){
                array[i][j]=0;
            }
        }
    }

    graf <<"\n\n}";

    return array;
}

void deleteMemory(int **array, int size){

    for(int i=0;i<size;i++){
        delete[] array[i];
    }

    delete[] array;
}

void printArray(int **array, int size){

    for(int i=0;i<size;i++){
        cout << endl;
        for(int j=0;j<size;j++){
            cout << array[i][j] << " ";
        }
    }

}

void creareGraf(){

    int nodes_count, alege1, alege2;
    double fi;

    l1:
    cout << "Care e numarul de varfuri din graf?\n";
    cout << "\t1. 100  varfuri\n";
    cout << "\t2. 200  varfuri\n";
    cout << "\t3. 300 varfuri\n";
    cout << "Alegerea ta este: ";
    cin >> alege1;
    if (alege1 == 1)
        nodes_count = 100;
    else if (alege1 == 2)
        nodes_count = 200;
    else if (alege1 == 3)
        nodes_count = 300;
    else {
        cout << "Optiune inexistenta" << endl;
        goto l1;
    }

    cout << "\nCare este tipul grafului?\n";
    cout << "\t1. Graf rar(0.32 < fi <= 0.41)\n";
    cout << "\t2. Graf mediu(0.41 < fi <= 0.68)\n";
    cout << "\t3. Graf dens(0.68 < fi <= 1)\n";
    cout << "Alegerea ta este: ";
    cin >> alege2;



alfi:
    cout << "Alegeti valoare lui fi: ";
    cin >> fi;

    switch (alege2) {
    case 1:
        if(fi > 0.32 && fi <= 0.41)
        {
            break;
        }else {
        cout << "Fi introdus nu corespunde cazului ales. Alegeti alta valoare!\n";
        goto alfi;
    }
    case 2:
        if (fi > 0.41 && fi <= 0.68)
        {
            break;
        } else {
        cout << "Fi introdus nu corespunde cazului ales. Alegeti alta valoare!\n";
        goto alfi;
    }
    case 3:
        if (fi > 0.68 && fi <= 1)
        {
            break;

        } else {
        cout << "Fi introdus nu corespunde cazului ales. Alegeti alta valoare!\n";
        goto alfi;
    }
    default: cout << "gresit";
    }


    int nrMaxMuchiiPosib = (nodes_count * (nodes_count-1));
    int nrMuchiiGenerate = 0;
    int **matriceAdiacenta = makeSymmetricArray(nodes_count, &nrMuchiiGenerate, fi);
    double raport = (double)nrMuchiiGenerate / nrMaxMuchiiPosib;
    int graf[V][V];
    int floyd[V][V];

    cout << "Nr de varfuri: "<< nodes_count <<
    endl << "Nr maxim de muchii posibile (intr-un graf neorientat): " << nrMaxMuchiiPosib <<
    endl << "Nr de muchii generate: " << nrMuchiiGenerate <<
    endl << "Raportul in cazul dat:" << raport<< endl<< endl;
    if(0.01 < raport && raport <= 0.41) cout << "\tAveti un graf rar" << endl;
    if(0.41 < raport && raport <= 0.68) cout << "\tAveti un graf mediu" << endl;
    if(0.68 < raport && raport <= 1.00) cout << "\tAveti un graf dens" << endl;

    for(int i = 0; i < nodes_count; i++){
        cout << endl;
        cout << i+1 << "->";
        for(int j = 0 ; j < nodes_count; j++){

            if( matriceAdiacenta[i][j] != 0){
                cout << j+1 << "(" << matriceAdiacenta[i][j] << "), ";
            }
        }
    }

    for(int i=0;i<nodes_count;i++){
        for(int j=0;j<nodes_count;j++){
             graf[i][j]=matriceAdiacenta[i][j];
             if(graf[i][j]!=0)
                floyd[i][j]=matriceAdiacenta[i][j];
            else
                floyd[i][j]=inf;
        }
    }

    int nod;
    cout << "\n\nNodul sursa:" << endl;
    cin >> nod;

    clock_t start1 = clock();
    Floyd(floyd, nodes_count);
    clock_t end1 = clock();
    double timp_floyd = ((double)(end1 - start1)) / CLOCKS_PER_SEC;

    clock_t start2 = clock();
    dijkstra(graf, nod-1, nodes_count);
    clock_t end2 = clock();
    double timp_dijkstra = ((double)(end2 - start2)) / CLOCKS_PER_SEC;

    cout << "\nTimpul (Floyd) este: " << timp_floyd << endl;
    cout << "\nTimpul (Dijkstra) este: " << timp_dijkstra << endl;

    cout << endl<< endl;
    deleteMemory(matriceAdiacenta, nodes_count);
}

int main(){


    creareGraf();

    if(check == 1){
        system("dot -Tpng graf.txt -o graf.png");
        system("graf.png");
    }
	//system("pause");
	return 0;
}
/*
dot -Tpng graf.txt -o graf1.png
neato -Tpng graf.txt -o graf1.png
twopi -Tpng graf.txt -o graf1.png
circo -Tpng graf.txt -o graf1.png
fdp -Tpng graf.txt -o graf1.png
sfdp -Tpng graf.txt -o graf1.png
patchwork -Tpng graf.txt -o graf1.png
osage -Tpng graf.txt -o graf1.png
*/

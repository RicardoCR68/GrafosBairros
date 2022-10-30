#include "TGrafo.h"

// Construtor do TGrafo, responsável por 
// criar a matriz de adjacência v x v do Grafo
using namespace std;

const float inf_num = numeric_limits<float>::infinity();
const int N = 70;

// NODE
TNode::TNode() { this -> id = 999; this -> label = "VAZIO"; }

TNode::TNode(int id, string label) {
    this -> id = id;
    this -> label = label;
}

TNode::~TNode() {}

int TNode::getID() {
    return this -> id;
}

string TNode::getLabel() {
    return this -> label;
}

// GRAPH

TGrafo::TGrafo() {
    this -> n = 0;
    this -> m = 0; 
    
    // aloca a matriz do TGrafo
    TNode *list = new TNode[N]; // N limite de nós
    float **helper_min = new float*[N];
    float **helper_km = new float*[N];
    
    for(int i = 0; i < N; i++) {
    	helper_min[i]= new float[N];
    	helper_km[i]= new float[N];
    }

    min = helper_min;
    km = helper_km;
    locals = list;

    for(int i = 0; i< N; i++) {
        for(int j = 0; j< N; j++) {
            km[i][j] = inf_num;
            min[i][j] = inf_num;
        }
    }
            
    // Inicia a matriz com zeros
}

// Destructor, responsável por
// liberar a memória alocada para a matriz
TGrafo::~TGrafo(){
	n = 0;
	m = 0;
	
    delete [] *km;
	delete [] *min;
	delete [] locals;
    
	cout << "Espaço Liberado" << endl;
}

int TGrafo::getN() {
    return n;
}

int TGrafo::getM() {
    return m;
}

float** TGrafo::getKm() {
    return km;
}

float** TGrafo::getMin() {
    return min;
}

TNode* TGrafo::getLocals() {
    return locals;
}

// Insere uma aresta no Grafo tal que
// v é adjacente a w

void TGrafo::insereN(int id, string label) {
    if (n == N) { cout << "CAPACIDADE MAXIMA ATINGIDA! NENHUMA MUDANÇA FEITA" << endl; }
    if (locals[id].getID() == 999) {
        TNode new_node(id, label);
        locals[id] = new_node;
        ++n;
        for (int l = 0; l < N; ++l) {
            km[l][id] = inf_num;
            min[l][id] = inf_num;
        }
        for (int c = 0; c < N; ++c) {
            km[id][c] = inf_num;
            min[id][c] = inf_num;
        }
    }
}

void TGrafo::insereA(int f, int t, float n_km, float n_min) {
    // testa se nao temos a aresta
    if (f == 42) {cout << "teste" << endl;} 
    if(km[f][t] == inf_num) {
        km[f][t] = n_km;
        min[f][t] = n_min;
        m++; // atualiza qtd arestas
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int f, int t){
    // testa se temos a aresta
    if(km[f][t] != inf_num) {
        km[f][t] = inf_num;
        min[f][t] = inf_num;
        m--;
    }
}

int TGrafo::inDegree (int v) {
    int deg = 0;
    for (int i = 0; i < n; ++i) {
        if (km[i][v] != inf_num) { ++deg; }
    }
    return deg;
}

int TGrafo::outDegree (int v) {
    int deg = 0;
    for (int i = 0; i < n; ++i) {
        if (km[i][v] != inf_num) { ++deg; }
    }
    return deg;
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida

void TGrafo::showLocals(){
    cout << "====== LOCAIS ======" << endl;
    for( int l = 0; l < n; l++) {
        cout << locals[l].getID() << " --- " << locals[l].getLabel();
        cout << endl;
    }
    cout << endl;
}

void TGrafo::showKm(){
    cout << "===================== KILOMETROS ====================="<< endl;
    
    for( int l = 0; l < n; l++) {
        cout << endl;
        for( int c = 0; c < n; c++) {
            if (km[l][c] != inf_num) {
                cout << "\033[1;31mKM[" << l << "," << c << "]=" << km[l][c] << "\033[0m ";
            } else {
                cout << "KM[" << l << "," << c << "]=" << km[l][c] << " ";
            }
        }
    }
    cout << endl;
}

void TGrafo::showMin(){
    cout << "===================== MINUTOS =====================" << endl;
    
    for( int l = 0; l < n; l++) {
        cout << endl;
        for( int c = 0; c < n; c++) {
            if (min[l][c] != inf_num) {
                cout << "\033[1;31mKM[" << l << "," << c << "]=" << min[l][c] << "\033[0m ";
            } else {
                cout << "KM[" << l << "," << c << "]=" << min[l][c] << " ";
            }
        }
    }
    cout << endl;
}

int isSourceM (TGrafo &g, int v) {
    int out_deg = g.outDegree(v);
    int in_deg = g.inDegree(v);
    return ((out_deg > 0) && (in_deg == 0));
}

int isSinkM (TGrafo &g, int v) {
    int out_deg = g.outDegree(v);
    int in_deg = g.inDegree(v);
    return ((in_deg > 0) && (out_deg == 0));
}

int isSimetricM(TGrafo &g) {
    int n = g.getN();
    float** km = g.getKm();

    for (int i = 0; i < n - 1 ; i++) {
        for (int j = 1 + i; j < n; j++) {
            if (km[i][j] != km[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

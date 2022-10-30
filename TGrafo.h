#ifndef __T_GRAFO__
#define __T_GRAFO__

#include <stdio.h>
#include <iostream>
#include <limits>
#include "string.h"

using namespace std;

class TNode {
    private:
        int id;
        string label;
    public:
        TNode();
        TNode(int id, string label);
        ~TNode();
        
        int getID();
        string getLabel();
};

class TGrafo{
	private:
		int n;      // Quantidade de vértices
		int m;      // Quantidade de arestas
		
        TNode *locals;  // Lista com os nós
		float **km;  // Matriz em km
		float **min;  // Matriz em min
	public:
		TGrafo();

        int getN();
        int getM();
        TNode* getLocals();
        float** getKm();
        float** getMin();

        void insereN(int id, string label);

        void insereA(int f, int t, float n_km, float n_min);
		void removeA(int f, int t);

        int inDegree (int v);
        int outDegree (int v);

        void showLocals();
        void showKm();
        void showMin();
		
        ~TGrafo();		
};

int isSourceM(TGrafo &g, int v);
int isSinkM(TGrafo &g, int v);
int isSimetricM(TGrafo &g);

#endif //__T_GRAFO__
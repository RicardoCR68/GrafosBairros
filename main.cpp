#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "TGrafo.h"
// Funções que recebem grafos como parâmetros:
using namespace std;

const int MAX = 40;
const float inf_num = numeric_limits<float>::infinity();

void printSource(TGrafo &g, int v) {
  TNode *list = g.getLocals();
  cout << "Rotulo do nó " << v << ": " << list[v].getLabel() << endl;
  float **mins = g.getMin();
  for (int i = 0; i < g.getN(); ++i) {
    if (mins[v][i] != inf_num) {
      cout << "Alcança:          " << list[i].getLabel() << endl;
    }
  }
  cout << endl;
}
void printSink(TGrafo &g, int v) {
  TNode *list = g.getLocals();
  cout << "Rotulo do nó " << v << ":    " << list[v].getLabel() << endl;
  float **mins = g.getMin();
  for (int j = 0; j < g.getN(); ++j) {
    if (mins[j][v] != inf_num) {
      cout << "É Alcançado por:  " << list[j].getLabel() << endl;
    }
  }
  cout << endl;
}

int main() {
  TGrafo g = TGrafo();
  while (true) {
    int choice;
    int inner_choice;

    cout << "================ MENU ================" << endl;
    cout << "1.  Ler localLigacao.txt" << endl;
    cout << "2.  Escrever localLigacao.txt" << endl;
    cout << "3.  Inserir Local" << endl;
    cout << "4.  Inserir Ligacao" << endl;
    cout << "5.  Mostrar Locais" << endl;
    cout << "6.  Mostrar Ligacoes" << endl;
    cout << "7.  Mostrar Loc. Alcançados por Origem" << endl;
    cout << "8.  Mostrar Loc. que Alcançam Origem" << endl;
    cout << "9.  Prim" << endl;
    cout << "10. Ecerrar Aplicação" << endl;
    cout << "--------------------------------------" << endl;
    cout << "> ";

    cin >> choice;

    switch (choice) {
    case 10: {
      return 0;
    }
    case 1: {
      ifstream fin("localLigacao.txt");
      char verts[MAX] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                         '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                         '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                         '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                         '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

      fin.getline(verts, MAX);
      string s_v = verts;
      int v = stoi(s_v);

      for (int j = 0; j < v; ++j) {
        char line_arr[MAX] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                              '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                              '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                              '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                              '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
        fin.getline(line_arr, MAX);
        string line = line_arr;

        char id_str[2];
        char label_str[MAX] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                               '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                               '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                               '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
                               '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

        for (int i = 0; i < line.length(); i++) {
          if (isdigit(line[i])) {
            id_str[i] = line[i];
          } else {
            break;
          }
        }

        bool flag_s = false;
        bool flag_e = false;
        int l_size = 0;

        for (int i = 0; i < line.length(); i++) {
          if (!isdigit(line[i]) || flag_s && !flag_e) {
            if (flag_s && line[i] != '"') {
              label_str[l_size] = line[i];
              ++l_size;
            } else if (line[i] == '"' && !flag_s) {
              flag_s = true;
            } else if (flag_s && line[i] == '"') {
              flag_s = false;
              flag_e = true;
            }
          } else if (flag_e) {
            label_str[i] = '\0';
          }
        }

        stringstream str_id(id_str);
        int id;
        str_id >> id;

        string label = label_str;

        g.insereN(id, label);
      }
      char edges[MAX];
      fin.getline(edges, MAX);
      string s_e = edges;
      int e = stoi(s_e);

      for (int j = 0; j < e; ++j) {
        char e_line[MAX];
        fin.getline(e_line, MAX);
        string e_l = e_line;

        stringstream e_str(e_l);
        int f, t;
        float k, m;

        e_str >> f;
        e_str >> t;
        e_str >> k;
        e_str >> m;
        g.insereA(f, t, k, m);
      }
      break;
    }
    case 3: {
      string new_lab;
      int new_id;
      cout << "ID: ";
      cin >> new_id;
      cout << "Rotulo: ";
      cin >> new_lab;

      g.insereN(new_id, new_lab);
      break;
    }
    case 4: {
      float new_km;
      float new_min;
      int id_f;
      int id_t;
      cout << "Formato:\nOrigem (id: int)\\n\nDestino (id: int)\\n\nDist. (km: "
              "float)\\n\nTempo (min: float)"
           << endl;
      cin >> id_f >> id_t >> new_km >> new_min;

      g.insereA(id_f, id_t, new_km, new_min);
      break;
    }
    case 5: {
      g.showLocals();
      break;
    }
    case 6: {
      g.showMin();
      g.showKm();
      break;
    }
    case 7: {
      cout << "Qual ID do nó: ";
      cin >> inner_choice;
      printSource(g, inner_choice);
      break;
    }
    case 8: {
      cout << "Qual ID do nó: ";
      cin >> inner_choice;
      printSink(g, inner_choice);
      break;
    }
    case 9: {
      cout << "Prim" << endl;
      g.prim();
      break;
    }
    case 2: {
      ofstream out_file;
      out_file.open("localLigacao.txt");
      out_file << g.getN() << endl;
      for (int k = 0; k < g.getN(); ++k) {
        out_file << g.getLocals()[k].getID() << " \""
                 << g.getLocals()[k].getLabel() << '"' << endl;
      }
      out_file << g.getM() << endl;
      for (int k = 0; k < g.getN(); ++k) {
        for (int h = 0; h < g.getN(); ++h) {
          if (g.getKm()[k][h] != inf_num) {
            out_file << g.getLocals()[k].getID() << ' '
                     << g.getLocals()[h].getID() << ' ' << g.getKm()[k][h]
                     << ' ' << g.getMin()[k][h] << endl;
          }
        }
      }
      break;
    }
    default: {
      cout << "Comando não Reconhecido!" << endl;
    }
    }
  }

  return 0;
}

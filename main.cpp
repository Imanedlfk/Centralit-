#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include <fstream>
#include <sstream> // ajout de l'inclusion pour std::stringstream
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, property<vertex_name_t, std::string>, property<edge_weight_t, float> > Graph; // correction du type de vertex_name_t
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

int main()
{
    std::ifstream file("testCSV.csv");
    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    Graph G;

    if (file.is_open()) {
        std::string line,line2;
        std::getline(file, line); // sauter la première ligne (en-têtes)
        int i=0;
        while (std::getline(file, line) && std::getline(file,line2)) { // lire chaque ligne du fichier
            std::stringstream ss(line);
            std::stringstream ss2(line2);
            std::string token;
            std::string token2;
            std::vector<std::string> tokens;
            std::vector<std::string> token2s;
            while (std::getline(ss, token, ',')) { // séparer chaque champ de la ligne
                tokens.push_back(token);
            }
string a=tokens[3];
a+=',';
  a+=tokens[4];
    while (std::getline(ss2, token2, ',')) { // séparer chaque champ de la ligne
                token2s.push_back(token2);
            }

            string b=token2s[3];
            b+=',';
            b+=token2s[4];
            Vertex v1 = add_vertex(a, G); // correction de l'ajout des vertex
            Vertex v2 = add_vertex(b, G);
            add_edge(v1, v2, stof(token2s[2].c_str()), G); // correction de la conversion du poids
        }
        file.close(); // fermer le fichier

        property_map<Graph, vertex_name_t>::type name_map = get(vertex_name, G);
        property_map<Graph, edge_weight_t>::type weight_map = get(edge_weight, G);

        // Afficher les sommets et leurs noms
        graph_traits<Graph>::vertex_iterator vi, vi_end;
        for (tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi) {
            cout << "Sommet " << *vi << " avec nom " << name_map[*vi] << endl;
        }

        // Afficher les arêtes et leurs poids
        graph_traits<Graph>::edge_iterator ei, ei_end;
        for (tie(ei, ei_end) = edges(G); ei != ei_end; ++ei) {
            Edge e = *ei;
            Vertex u = source(e, G);
            Vertex v = target(e, G);
            cout << "Arete entre " << name_map[u] << " et " << name_map[v] << " avec poids " << weight_map[e] << endl;
        }



        return 0;
    }
}

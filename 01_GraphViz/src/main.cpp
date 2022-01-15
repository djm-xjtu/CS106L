#include <iostream>
#include "SimpleGraph.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <ctime>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;   
using std::stringstream;
using std::getline;

const double PI =  3.14159265358979323;
const double Krepel = 1e-3;
const double Kattract = 1e-3;
const int N = 1e6+10;
std::pair<double,double> delta[N];


int NodeNum;

SimpleGraph graph;
void Welcome();
void initNodes();
void inputNodes();
inline double distance(Node m ,Node n);
void forceDirected();
void forcecompute();
void attractcompute();
void final();
// Main method
int main() {
    Welcome();
    inputNodes();
    final();
    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;
}

void inputNodes(){
    ifstream inputFile;
    string filename;
    cout << "Input a file name: ";
    cin >> filename;
    inputFile.open(filename);
    while(!inputFile){
        cout << endl << "Open failed!" << endl << "Input a file name: ";
        cin >> filename;
    }
    cout << endl << "Open success!" << endl;
    string str;
    stringstream stream;
    getline(inputFile,str);
    stream.str(str);
    stream >> NodeNum;
    stream >> std::ws;
    while(getline(inputFile, str)){
        stream.clear();
        stream.str(str);
        std::size_t u,v;
        stream >> u >> v;
        graph.edges.push_back({u,v});
    }
    initNodes();
    InitGraphVisualizer(graph);
    DrawGraph(graph);
}

void initNodes(){
    for(int i = 0 ; i < NodeNum; i++)
    {
        graph.nodes.push_back({cos(2*PI*i / NodeNum), sin(2*PI*i / NodeNum)});
    }
}

inline double distance(Node m, Node n){
    return std::sqrt(std::pow(m.x - n.x,2) + std::pow(m.y - n.y,2));
}

void forcecompute()
{
    for(int i = 0 ; i < NodeNum; i++){
        for(int j = i + 1 ; j < NodeNum; j++){
            auto node1 = graph.nodes[i];
            auto node2 = graph.nodes[j];
            double Frepel = Krepel / distance(node1, node2);
            double angel = std::atan2(node2.y - node1.y, node2.x - node1.x);
            delta[i].first -= Frepel * cos(angel);
            delta[i].second -= Frepel * sin(angel);
            delta[j].first += Frepel * cos(angel);
            delta[j].second += Frepel * sin(angel);
        }
    }

}

void attractcompute()
{
    for(int i = 0 ; i < NodeNum; i++){
        for(int j = i + 1 ; j < NodeNum; j++){
            auto node1 = graph.nodes[i];
            auto node2 = graph.nodes[j];
            double Frepel = Kattract * distance(node1, node2);
            double angel = std::atan2(node2.y - node1.y, node2.x - node1.x);
            delta[edge.start].first += Frepel * cos(angel);
            delta[edge.start].second += Frepel * sin(angel);
            delta[edge.end].first -= Frepel * cos(angel);
            delta[edge.end].second -= Frepel * sin(angel);
        }
    }
}
void forceDirected()
{
    for(int i = 0; i < NodeNum ; i++){
        graph.nodes[i].first += delta[i].first;
        graph.nodes[i].second += delta[i].second; 
    }
}

void final(){

   int iterTimes;
   cout<<"please input iter times"<<endl;
   cin>>iterTimes;
   for ( int i = 1 ; i <= iterTimes ; i++){
       memset(delta,0,sizeof(delta));
       forcecompute();
       attractcompute();
       forceDirected();
       cout<<" running for "<<i<<" times"<<endl;
       DrawGraph(graph);
   }
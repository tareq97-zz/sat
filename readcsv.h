#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <utility>
#include <list>
#include<stdio.h>
#include <unordered_set>
#include <unordered_map>

using namespace std;

//static unordered_map<int, EdgeAttributes> allmap;

class Cordinates{
    public: int g;
    public: string lat;
    public: string longi;
};

class EdgeAttributes{
    public: int u_id;
    public: int v_id;
    public: float edgelength;
    public: Cordinates src;
    public: Cordinates des;
};

list<string> getLatLongi(string str){
    size_t s = str.find("((");
    size_t e = str.find("))");

    string r = str.substr(s+2,e-(s+2));
    char rs[r.length()];

    list<string> l;
    strcpy(rs, r.c_str());
    char *token = strtok(rs,",");
    while(token!=NULL){
        l.push_back(token);
        token = strtok(NULL, ",");
    }

    string src = l.front();
    string des = l.back();
    
    l.clear();

    char src_a[src.length()];
    strcpy(src_a, src.c_str());
    char *actual_src = strtok(src_a," ");
    while(actual_src!=NULL){
        l.push_back(actual_src);
        actual_src = strtok(NULL, " ");
    }
    char des_a[des.length()];
    strcpy(des_a, des.c_str());
    char *actual_des = strtok(des_a," ");
    while(actual_des!=NULL){
        l.push_back(actual_des);
        actual_des = strtok(NULL, " ");
    }
    
    return l;
}

static int v_count = 0;

static int vertexCount(unordered_set<int> s){
    int count = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        count++;
    }
    v_count = count;
    return v_count;
}

void addEdge(vector<EdgeAttributes> adj[], vector<EdgeAttributes> me,int i){
    
    //adj[me[i].src.g].push_back(me[i].des.g);
}

vector<EdgeAttributes> readfile(string filename){
    string line;
    ifstream stream;
    stream.open(filename);
    if(!stream.is_open()){
        exit(EXIT_FAILURE);
    }

    string u_id;
    string v_id;
    string meter;
    string ms;
    unordered_set<int> v;
    unordered_map<int,int> u_maps;

    vector<EdgeAttributes> nodes;
    unordered_multiset<EdgeAttributes> actualNodes;
    
    int count=1;
    while(getline(stream,line)){
        stringstream ss(line);
        getline(ss,u_id,',');
        getline(ss,v_id,',');
        getline(ss,meter,',');
        getline(ss,ms);    

        EdgeAttributes *attribute =  new EdgeAttributes();
        attribute->u_id = stoi(u_id); 
        attribute->v_id = stoi(v_id);
        v.insert(attribute->u_id);
        v.insert(attribute->v_id);
        
        attribute->edgelength=stof(meter);

        list<string> l = getLatLongi(ms);
        for(auto x = l.begin(); x!=l.end(); x++){
            attribute->src.longi = *x;
            x++;
            attribute->src.lat = *x;
            x++;
            attribute->des.longi = *x;
            x++;
            attribute->des.lat = *x;
        }
        if(u_maps.find(attribute->u_id) == u_maps.end()){
            attribute->src.g = count;
            u_maps[attribute->u_id] = count;
            count++;
        }
        else{
            auto i = u_maps.find(attribute->u_id);
            attribute->src.g = i->second;
        }
        if(u_maps.find(attribute->v_id) == u_maps.end()){
            attribute->des.g = count;
            u_maps[attribute->v_id] = count;
            count++;
        }
        else{
            auto i = u_maps.find(attribute->v_id);
            attribute->des.g = i->second;
        }
        //cout << attribute->u_id << " " << attribute->v_id << " " ;
        //cout << "EdgeLength : " << attribute->edgelength << ":::::" << attribute->src.lat << " ";
        //cout << attribute->src.longi << " " << attribute->des.lat << " " << attribute->des.longi << "\n";

        nodes.push_back(*attribute);
        actualNodes.insert(*attribute);
    }

    for (auto i = u_maps.begin(); i != u_maps.end(); i++)
    {
        /* code */
        cout << "Here : " << i->first << " " << i->second << "\n"; 
    }
    
    int vertex = vertexCount(v);

    return nodes;
}

void dijkstra(vector<EdgeAttributes> adj[], float lat, float longi){
    int i =0;
    

    for (size_t i = 0; i < v_count; i++)
    {
        /* code */
    }
    
}

void s(float lat, float longi){
    vector<EdgeAttributes> nodes = readfile("../output/o2.csv");

    for (size_t i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i].src.g << "\t" << nodes[i].des.g << "\t" ;
        cout << nodes[i].u_id << "\t" << nodes[i].v_id << "\t" ;
        cout << nodes[i].src.lat << " " << nodes[i].src.longi << "\t";
        cout << nodes[i].des.lat << " " << nodes[i].des.longi << "\n"; 
    }

    int v = v_count;
    vector<EdgeAttributes> adj[v];
    for (size_t i = 0; i < nodes.size(); i++)
    {
        addEdge(adj,nodes,i);
    }
    
    dijkstra(adj,lat,longi);
    
    cout << v << "\n";
}
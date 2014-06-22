#pragma once
#include <iostream>
#include <fstream>
using namespace std;


template<class T> void mapcout(map<int, vector<int> > test){
	for (map<int, vector<int> >::iterator it = test.begin(); it != test.end(); it++){
		cout << it->first;
		cout << " -> ";
		for (vector<int>::iterator jt = it->second.begin(); jt != it->second.end(); jt++){
			cout << *jt << " ";
		}
		cout << "\n";
	}
}



template<class T> void veccout(vector<T>a){
	for (vector<int>::iterator it = a.begin(); it != a.end(); it++){
		cout << *it;
		if ((it + 1) != a.end())
			cout << ", ";
	}
	cout << endl;
}


template<class T> vector<T> getData(string file){
	vector<T> data;
	ifstream doc;
	int item;
	doc.open(file, ios::in);
	if (doc.is_open()){
		while (!doc.eof()){
			doc >> item;
			data.push_back(item);
		}
	}
	doc.close();
	return data;
}
////////////////////////////////////////////////////////


template<class T> 
class graph_{

private:
	int id; // Aktuelle Reihenfolge
	int V; // Anzahl Knoten
	int E; // Anzahl Kanten
	vector<int> nodelist; // Knotenliste
	map<int, vector<int> > adjlist; // Adjazenzliste
	
	void recursiveDepthSearch(map<int, vector<int> > adjlist, int node, vector<int> &val);		// Rekursive Tiefensuche
	map<int, vector<int> > nodelist2adjlist(const vector<int> &a);

public:
	graph_() : id(0) {} // Konstruktor
	void setNodelist(vector<int> &newnodelist) { nodelist = newnodelist; };			// setNodelist speichert die Knotenliste als private Variable

	map<int, vector<int> >	getAdjlist(void);										// getAdjlist liefert die Adjazenzliste aus der Knotenliste
	vector<int> startRecursiveDepthSearch(map<int, vector<int> > adjlist);			// Starten der rekursiven Tiefensuche
	vector<int> iterativeDepthSearch(map<int, vector<int> > adjlist, int startnode);// Iterative Tiefensuche
	vector<int> iterativeBreadthSearch(map<int, vector<int> > adjlist, int startnode);// Iterative Breitensuche
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>  map<int, vector<int> > graph_<T>::nodelist2adjlist(const vector<int> &a) {
	 V = a[0]; // Anzahl Knoten
	 E = a[1]; // Anzahl Kanten
	int nodelistSize = V + E + 2; // Größe der Knotenliste
	int i = 2;
	int j = 0;
	map<int, vector<int> > graph; // DS für die Adjazenzliste
	while (i < nodelistSize) // Knoten verarbeiten
	{
		int ag = a[i]; // Knotenanzahl
		graph[j]; // damit der Knoten j in der Adjazenzliste
		// angelegt wird
		for (int k = i + 1; k < i + ag + 1; k++)
		{
			int node = a[k]; // Knoten
			graph[j].push_back(node); // Knoten zum Feld hinzufügen
		}
		i = i + ag + 1; // Index weitersetzen
		j++;
	}
	return graph;
}


template<class T> map<int, vector<int> >  graph_<T>::getAdjlist(void){

	return nodelist2adjlist(nodelist);
}



template<class T> int* edgelist2adjmatrix(const vector<int> &a){
	int n = a[0]; // Anzahl Knoten
	int m = a[1]; // Anzahl Kanten
	int *adj = new int[n*n]; // 2D-Feld der Größe nxn
	for (int i = 0; i < n; i++){ // Initialisierung mit 0
		for (int j = 0; j < n; j++)
			{ adj[i*n + j] = 0; }
	}
	for (int j = 2; j < 2 * m; j = j + 2) // Einträge speichern
	{
		int x = a[j]; // Knoten a[j] ist mit Knoten a[j+1]
		int y = a[j + 1]; // verbunden
		adj[x*n + y] = 1; // Kante in der Matrix speichern  // ACHTUNG: Knotennamen = {0,1,...,n-1}
		adj[y*n + x] = 1;
	}
	return adj;
}





template<class T> vector<int> graph_<T>::startRecursiveDepthSearch(map<int, vector<int> > adjlist){

	vector<int> val;

	for (int i = 0; i < V; i++)			//initialisiere val-Array mit allen Knoten als äußere Knoten
		val.push_back(0);

	recursiveDepthSearch(adjlist, 0, val);		//kick-off

	return val;
}

template<class T>void graph_<T>::recursiveDepthSearch(map<int, vector<int> > adjlist, int node, vector<int> &val){

	static int n = 1;
	val[node] = n;

	for (vector<int>::iterator it = adjlist[node].begin(); it != adjlist[node].end(); it++){
		if (val[*it] == 0){
			n++;
			recursiveDepthSearch(adjlist, *it, val);
		}
	}
	return;
}


template<class T> vector<int> graph_<T>::iterativeDepthSearch(map<int, vector<int> > adjlist, int startnode){

	stack<int> halde;
	int node;
	int n = 0;
	vector<int> val;

	for (int i = 0; i < V; i++)			//initialisiere val-Array mit allen Knoten als äußere Knoten
		val.push_back(0);

	halde.push(startnode);

	do{
		n++;
		node = halde.top();
		halde.pop();
		val[node] = n;

		for (vector<int>::iterator it = adjlist[node].begin(); it != adjlist[node].end(); it++){
			if (val[*it] == 0){
				val[*it] = -1;
				halde.push(*it);
			}
		}
	} while (!halde.empty());

	return val;
}



template<class T> vector<int> graph_<T>::iterativeBreadthSearch(map<int, vector<int> > adjlist, int startnode){

	queue<int> schlange;
	int node;
	int n = 0;
	vector<int> val;

	for (int i = 0; i < V; i++)			//initialisiere val-Array mit allen Knoten als äußere Knoten
		val.push_back(0);

	schlange.push(startnode);

	do{
		n++;
		node = schlange.front();
		schlange.pop();
		val[node] = n;

		for (vector<int>::iterator it = adjlist[node].begin(); it != adjlist[node].end(); it++){
			if (val[*it] == 0){
				val[*it] = -1;
				schlange.push(*it);
			}
		}
	} while (!schlange.empty());

	return val;

}



//minimaler Spannbaum
// -Prioritätssuche  -Kruskal -Prim

//kürzester Weg
// -Prioritätssuche -Breitensuche -Dijkstra
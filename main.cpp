#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include "my_graph.h"
using namespace std;

int main(){

	cout << "Hello World\n";
	graph_<int> testg;
	vector<int> kntlist;
	vector<int> TSR;
	map<int, vector<int> > adjlist;
	kntlist = getData<int>("knt.txt");
	veccout(kntlist);

	testg.setNodelist(kntlist);
	adjlist = testg.getAdjlist();
	mapcout<int>(adjlist);

	TSR = testg.iterativeBreadthSearch(adjlist, 0);

	for (int i = 0; i < 10; i++)
		cout << i << "  ";
	cout << endl;
	veccout(TSR);





	system("PAUSE");
	return 0;
}
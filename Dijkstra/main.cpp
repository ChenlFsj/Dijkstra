#include <iostream>
#include <iomanip>
#include<queue>
#include<vector>

#include "Dijkstra.h"

using namespace std;


int main() {

	Graph a;
	a.Create();
	a.show();

	VertexType startpoint;
	cout << "��������㣺" << endl;
	cin >> startpoint;
	a.Dijkstra(startpoint);

	system("pause");
	return 0;
}
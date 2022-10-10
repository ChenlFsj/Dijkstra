#include <iostream>
#include <iomanip>
#include<queue>
#include<vector>

#include "Dijkstra.h"

using namespace std;


// ������ͼ
void Graph::Create() {

	// 1. ���붥����Ŀ���ߵ���Ŀ
	cout << "�����붥����Ŀ�Լ��ߵ���Ŀ��" << endl;
	cin >> this->Vexnum >> this->Arcnum;

	// 2. ������ڵ�ĺ���
	cout << "���������������֣�";
	for (int i = 0; i < this->Vexnum; ++i) {
		cin >> Vexs[i];
	}

	// 3. ��ʼ���ڽӾ���
	for (int i = 0; i < this->Vexnum; ++i) {
		for (int j = 0; j < this->Vexnum; ++j) {
			arcs[i][j] = MAX;
		}
	}

	// 4. �����ڽӾ���
	for (int i = 0; i < this->Arcnum; ++i) {
		cout << "�������" << i + 1 << "���ߵ������յ��Լ���Ӧ��Ȩֵ��";
		int v1, v2, w;

		cin >> v1 >> v2 >> w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		arcs[m][n] = w;

	}
}


// ����ĳ������ڶ�����е��±�
int Graph::LocateVex(VertexType u) {

	for (int i = 0; i < this->Vexnum; ++i) {
		if (u == this->Vexs[i]) {
			return i;
		}
	}
	return -1;
}


// ʹ�õϽ�˹�����㷨��ӡ��Դ���·��
void Graph::Dijkstra(VertexType startpoint) {

	// 1. ��ʼ����̾�������
	for (int i = 0; i < this->Vexnum; ++i) {
		this->dist[i] = MAX;
	}
	// ��ʼ�����̾���Ϊ0
	this->dist[LocateVex(startpoint)] = 0;

	// 2. ��ʼ������·��������
	queue<VertexType> temp;
	temp.push(startpoint);
	//�������Ϊ���ʼ��·������ÿ������Ӧ�Ķ�����
	for (int i = 0; i < this->Vexnum; ++i) {
		path.push_back(temp);
	}

	// 3. ��ʼ��solved����
	for (int i = 0; i < this->Vexnum; ++i) {
		this->solved[i] = false;
	}
	// ������ʼ�������е�������ľ���
	for (int i = 0; i < this->Vexnum; ++i) {
		// ���������ͨ��·�����޸�dist�Լ�path
		if (this->arcs[LocateVex(startpoint)][i] != MAX) {

			this->dist[i] = this->arcs[LocateVex(startpoint)][i];
			path[i].push(this->Vexs[i]);
		}
	}
	solved[LocateVex(startpoint)] = true;


	for (int i = 0; i < this->Vexnum; ++i) {
		ArcType mind = MAX;
		int v = i;

		for (int j = 0; j < this->Vexnum; ++j) {

			if (!solved[j] && dist[j] < mind) {
				mind = dist[j];
				v = j;
			}
			solved[v] = true;
			int w = this->firstadj(v);

			while (w != -1) {
				if (dist[v] + this->arcs[v][w] < dist[w]) {

					dist[w] = dist[v] + this->arcs[v][w];
					path[w] = path[v];
					path[w].push(Vexs[w]);
				}
				w = this->nextadj(v, w);
			}
		}
	}


	cout << "�ӽ��" << startpoint << "��ʼ����������·����·����������:" << endl;

	for (int i = 0; i < this->Vexnum; ++i) {
		
		if (dist[i] == MAX) {
			cout << "�޷��ҵ�·����" << endl;
		}
		else {
			cout << "�ִ��յ�" << Vexs[i] << "�����·��Ϊ��";
			int path_length = path[i].size();
			for (int j = 0; j < path_length; ++j) {
				cout << path[i].front() << " ";
				path[i].pop();
			}
			cout << "����Ϊ" << dist[i] << endl;
		}
	}
}


// ���ҵ�һ���������ӵĵ�
int Graph::firstadj(int v) {

	for (int i = 0; i < this->Vexnum; ++i) {
		if (arcs[v][i] != MAX) {
			return i;
		}
	}
	return -1;
}


// ���Һ���������ӵĵ�
int Graph::nextadj(int v, int w) {

	for (int i = w + 1; i < this->Vexnum; ++i) {
		if (arcs[v][i] != MAX) {
			return i;
		}
	}
	return -1;
}


void Graph::show() {

	for (int i = 0; i < this->Vexnum; ++i) {
		for (int j = 0; j < this->Vexnum; ++j) {
			cout << setw(4) << arcs[i][j] << " ";
		}
		cout << endl;
	}
}
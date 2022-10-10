#include <iostream>
#include <iomanip>
#include<queue>
#include<vector>

#include "Dijkstra.h"

using namespace std;


// 创建地图
void Graph::Create() {

	// 1. 输入顶点数目及边的数目
	cout << "请输入顶点数目以及边的数目：" << endl;
	cin >> this->Vexnum >> this->Arcnum;

	// 2. 输入各节点的号码
	cout << "请输入各顶点的数字：";
	for (int i = 0; i < this->Vexnum; ++i) {
		cin >> Vexs[i];
	}

	// 3. 初始化邻接矩阵
	for (int i = 0; i < this->Vexnum; ++i) {
		for (int j = 0; j < this->Vexnum; ++j) {
			arcs[i][j] = MAX;
		}
	}

	// 4. 构造邻接矩阵
	for (int i = 0; i < this->Arcnum; ++i) {
		cout << "请输入第" << i + 1 << "条边的起点和终点以及对应的权值：";
		int v1, v2, w;

		cin >> v1 >> v2 >> w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		arcs[m][n] = w;

	}
}


// 查找某个起点在顶点表中的下标
int Graph::LocateVex(VertexType u) {

	for (int i = 0; i < this->Vexnum; ++i) {
		if (u == this->Vexs[i]) {
			return i;
		}
	}
	return -1;
}


// 使用迪杰斯特拉算法打印单源最短路径
void Graph::Dijkstra(VertexType startpoint) {

	// 1. 初始化最短距离数组
	for (int i = 0; i < this->Vexnum; ++i) {
		this->dist[i] = MAX;
	}
	// 起始点的最短距离为0
	this->dist[LocateVex(startpoint)] = 0;

	// 2. 初始化保存路径的向量
	queue<VertexType> temp;
	temp.push(startpoint);
	//将起点作为最初始的路径加入每个结点对应的队列中
	for (int i = 0; i < this->Vexnum; ++i) {
		path.push_back(temp);
	}

	// 3. 初始化solved数组
	for (int i = 0; i < this->Vexnum; ++i) {
		this->solved[i] = false;
	}
	// 遍历起始点所在行的其他点的距离
	for (int i = 0; i < this->Vexnum; ++i) {
		// 如果存在走通的路，则修改dist以及path
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


	cout << "从结点" << startpoint << "开始到各点的最短路径和路径长度如下:" << endl;

	for (int i = 0; i < this->Vexnum; ++i) {
		
		if (dist[i] == MAX) {
			cout << "无法找到路径！" << endl;
		}
		else {
			cout << "抵达终点" << Vexs[i] << "的最短路径为：";
			int path_length = path[i].size();
			for (int j = 0; j < path_length; ++j) {
				cout << path[i].front() << " ";
				path[i].pop();
			}
			cout << "长度为" << dist[i] << endl;
		}
	}
}


// 查找第一个可以连接的点
int Graph::firstadj(int v) {

	for (int i = 0; i < this->Vexnum; ++i) {
		if (arcs[v][i] != MAX) {
			return i;
		}
	}
	return -1;
}


// 查找后面可以连接的点
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
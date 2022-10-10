#pragma once
#include <vector>

using namespace std;

// define 预处理不用加;
#define MAX 999		// 表示距离最大值
#define MAXNUM 20	// 表示最大的节点数

typedef int VertexType;
typedef int ArcType;

// 创建地图类

class Graph {

public:

	// 创建地图
	void Create();

	// 查找某个起点在顶点表中的下标
	int LocateVex(VertexType u);

	// 使用迪杰斯特拉算法打印单源最短路径
	void Dijkstra(VertexType startpoint);

	// 查找第一个可以连接的点
	int firstadj(int v);

	// 查找后面可以连接的点
	int nextadj(int v, int w);

	void show();

private:

	// 顶点表，将顶点的信息存储
	VertexType Vexs[MAXNUM];

	// 领接矩阵
	ArcType arcs[MAXNUM][MAXNUM];

	// 顶点数，边数
	int Vexnum, Arcnum;

	// 保存路径
	vector<queue<VertexType>> path;

	// 最短路径大小
	ArcType dist[MAXNUM];

	// 是否找到路径
	bool solved[MAXNUM];
};
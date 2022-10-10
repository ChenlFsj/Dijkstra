#pragma once
#include <vector>

using namespace std;

// define Ԥ�����ü�;
#define MAX 999		// ��ʾ�������ֵ
#define MAXNUM 20	// ��ʾ���Ľڵ���

typedef int VertexType;
typedef int ArcType;

// ������ͼ��

class Graph {

public:

	// ������ͼ
	void Create();

	// ����ĳ������ڶ�����е��±�
	int LocateVex(VertexType u);

	// ʹ�õϽ�˹�����㷨��ӡ��Դ���·��
	void Dijkstra(VertexType startpoint);

	// ���ҵ�һ���������ӵĵ�
	int firstadj(int v);

	// ���Һ���������ӵĵ�
	int nextadj(int v, int w);

	void show();

private:

	// ��������������Ϣ�洢
	VertexType Vexs[MAXNUM];

	// ��Ӿ���
	ArcType arcs[MAXNUM][MAXNUM];

	// ������������
	int Vexnum, Arcnum;

	// ����·��
	vector<queue<VertexType>> path;

	// ���·����С
	ArcType dist[MAXNUM];

	// �Ƿ��ҵ�·��
	bool solved[MAXNUM];
};
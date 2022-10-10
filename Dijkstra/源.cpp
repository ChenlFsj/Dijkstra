#include<iostream>
#include<iomanip>
#include<queue>
#include<vector>
using namespace std;

//用邻接矩阵构建有向图
#define MAX 999//表示无穷
#define MVNum 20//最大结点数
typedef int VertexType;//设置结点的数据类型为int型（方便后续修改成char...）
typedef int ArcType;//设置的权值为int型（方便后续修改成float...）

class Graph//Adjacency Matrix Graph有向图，用邻接矩阵表示
{
public:
	void Create();
	int LocateVex(VertexType u);//查找Graph中的顶点u，并返回其对应在顶点表中的下标，未找到则返回-1
	int firstadj(int v);
	int nextadj(int v, int w);
	void Dijkstra(VertexType start_point);//使用迪杰斯特拉算法打印单源最短路径
	void Show();//调试用，打印邻接矩阵
private:
	VertexType vexs[MVNum];//顶点表,将顶点保存的信息存入此处
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	int vexnum, arcnum;//图当前的顶点数和边数
	vector<queue<VertexType>>path;//保存各结点最短路径的path[i]
	ArcType dist[MVNum];//最短路径大小
	bool solved[MVNum];//是否找到最短路径
};
int Graph::LocateVex(VertexType u)
{//查找Graph中的顶点u，并返回其对应在顶点表中的下标，未找到则返回-1
	int i;
	for (i = 0; i < this->vexnum; i++)
	{
		if (u == this->vexs[i])
			return i;
	}
	return -1;
}
int Graph::firstadj(int v)
{
	for (int i = 0; i < this->vexnum; i++)
	{
		if (this->arcs[v][i] != MAX)
			return i;
	}
	return -1;
}
int Graph::nextadj(int v, int w)
{
	for (int i = w + 1; i < this->vexnum; i++)
	{
		if (this->arcs[v][i] != MAX)
			return i;
	}
	return -1;
}
void Graph::Show()
{
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			// setw(n) : 对紧接着的输出有用，设置字宽

			cout << setw(4) << this->arcs[i][j] << " ";
		}
		cout << endl;
	}
}
void Graph::Create()
{
	cout << "请输入总结点数和总边数:";
	cin >> this->vexnum >> this->arcnum;//输入总顶点数和总边数
	cout << "请输入各结点的信息:";
	for (int i = 0; i < this->vexnum; i++)
	{
		cin >> this->vexs[i];
	}
	//初始化邻接矩阵
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->arcs[i][j] = MAX;
		}
	}
	//构造邻接矩阵
	for (int i = 0; i < this->arcnum; i++)
	{
		int v1, v2, w;
		cout << "请输入第" << i + 1 << "条边的起点和终点及其对应的权值:";
		cin >> v1 >> v2 >> w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		this->arcs[m][n] = w;
	}
	return;
}
void Graph::Dijkstra(VertexType start_point)
{
	//初始化最短距离数组
	for (int i = 0; i < this->vexnum; i++)
	{
		this->dist[i] = MAX;
	}
	dist[this->LocateVex(start_point)] = 0;
	//初始化保存路径的向量
	queue<VertexType>temp;
	temp.push(start_point);
	for (int i = 0; i < this->vexnum; i++)
	{
		//（移到for外）queue<VertexType>temp;
		//temp.push(start_point);
		path.push_back(temp);
		//（不可行）path[i].push(start_point);//将起点作为最初始的路径加入每个结点对应的队列中
	}
	//初始化solved数组
	for (int i = 0; i < this->vexnum; i++)
	{
		solved[i] = false;
	}
	for (int i = 0; i < this->vexnum; i++)
	{
		if (this->arcs[this->LocateVex(start_point)][i] != MAX)
		{
			dist[i] = this->arcs[this->LocateVex(start_point)][i];
			path[i].push(this->vexs[i]);
		}
	}
	solved[this->LocateVex(start_point)] = true;
	for (int i = 0; i < this->vexnum; i++)
	{//返回地找
		ArcType mind = MAX;
		int v = i;
		for (int j = 0; j < this->vexnum; j++)
		{//一个劲地往前走
			//（移出for）int v = i;
			if (!solved[j] && dist[j] < mind)
			{
				mind = dist[j];
				v = j;
			}
			solved[v] = true;
			int w = this->firstadj(v);
			while (w != -1)
			{
				if (dist[v] + this->arcs[v][w] < dist[w])
				{
					dist[w] = dist[v] + this->arcs[v][w];
					path[w] = path[v];
					path[w].push(vexs[w]);
				}
				w = this->nextadj(v, w);
			}
		}
	}
	cout << "从结点" << start_point << "开始到各点的最短路径和路径长度如下:" << endl;
	for (int i = 0; i < this->vexnum; i++)
	{
		if (dist[i] == MAX)
		{
			cout << "无法到达结点" << this->vexs[i] << endl;
		}
		else
		{
			cout << "抵达结点" << this->vexs[i] << "的最短路径:";
			int path_length = path[i].size();
			for (int j = 0; j < path_length; j++)
			{
				cout << path[i].front() << " ";
				path[i].pop();
			}
			cout << "长度为" << dist[i] << endl;
		}
	}
}
int main()
{
	Graph s;
	s.Create();
	s.Show();
	VertexType start_point;
	cout << "请输入起点:";
	cin >> start_point;
	s.Dijkstra(start_point);
	system("pause");
	return 0;
}


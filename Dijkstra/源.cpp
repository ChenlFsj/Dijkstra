#include<iostream>
#include<iomanip>
#include<queue>
#include<vector>
using namespace std;

//���ڽӾ��󹹽�����ͼ
#define MAX 999//��ʾ����
#define MVNum 20//�������
typedef int VertexType;//���ý�����������Ϊint�ͣ���������޸ĳ�char...��
typedef int ArcType;//���õ�ȨֵΪint�ͣ���������޸ĳ�float...��

class Graph//Adjacency Matrix Graph����ͼ�����ڽӾ����ʾ
{
public:
	void Create();
	int LocateVex(VertexType u);//����Graph�еĶ���u�����������Ӧ�ڶ�����е��±꣬δ�ҵ��򷵻�-1
	int firstadj(int v);
	int nextadj(int v, int w);
	void Dijkstra(VertexType start_point);//ʹ�õϽ�˹�����㷨��ӡ��Դ���·��
	void Show();//�����ã���ӡ�ڽӾ���
private:
	VertexType vexs[MVNum];//�����,�����㱣�����Ϣ����˴�
	ArcType arcs[MVNum][MVNum];//�ڽӾ���
	int vexnum, arcnum;//ͼ��ǰ�Ķ������ͱ���
	vector<queue<VertexType>>path;//�����������·����path[i]
	ArcType dist[MVNum];//���·����С
	bool solved[MVNum];//�Ƿ��ҵ����·��
};
int Graph::LocateVex(VertexType u)
{//����Graph�еĶ���u�����������Ӧ�ڶ�����е��±꣬δ�ҵ��򷵻�-1
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
			// setw(n) : �Խ����ŵ�������ã������ֿ�

			cout << setw(4) << this->arcs[i][j] << " ";
		}
		cout << endl;
	}
}
void Graph::Create()
{
	cout << "�������ܽ�������ܱ���:";
	cin >> this->vexnum >> this->arcnum;//�����ܶ��������ܱ���
	cout << "�������������Ϣ:";
	for (int i = 0; i < this->vexnum; i++)
	{
		cin >> this->vexs[i];
	}
	//��ʼ���ڽӾ���
	for (int i = 0; i < this->vexnum; i++)
	{
		for (int j = 0; j < this->vexnum; j++)
		{
			this->arcs[i][j] = MAX;
		}
	}
	//�����ڽӾ���
	for (int i = 0; i < this->arcnum; i++)
	{
		int v1, v2, w;
		cout << "�������" << i + 1 << "���ߵ������յ㼰���Ӧ��Ȩֵ:";
		cin >> v1 >> v2 >> w;
		int m = LocateVex(v1);
		int n = LocateVex(v2);
		this->arcs[m][n] = w;
	}
	return;
}
void Graph::Dijkstra(VertexType start_point)
{
	//��ʼ����̾�������
	for (int i = 0; i < this->vexnum; i++)
	{
		this->dist[i] = MAX;
	}
	dist[this->LocateVex(start_point)] = 0;
	//��ʼ������·��������
	queue<VertexType>temp;
	temp.push(start_point);
	for (int i = 0; i < this->vexnum; i++)
	{
		//���Ƶ�for�⣩queue<VertexType>temp;
		//temp.push(start_point);
		path.push_back(temp);
		//�������У�path[i].push(start_point);//�������Ϊ���ʼ��·������ÿ������Ӧ�Ķ�����
	}
	//��ʼ��solved����
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
	{//���ص���
		ArcType mind = MAX;
		int v = i;
		for (int j = 0; j < this->vexnum; j++)
		{//һ��������ǰ��
			//���Ƴ�for��int v = i;
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
	cout << "�ӽ��" << start_point << "��ʼ����������·����·����������:" << endl;
	for (int i = 0; i < this->vexnum; i++)
	{
		if (dist[i] == MAX)
		{
			cout << "�޷�������" << this->vexs[i] << endl;
		}
		else
		{
			cout << "�ִ���" << this->vexs[i] << "�����·��:";
			int path_length = path[i].size();
			for (int j = 0; j < path_length; j++)
			{
				cout << path[i].front() << " ";
				path[i].pop();
			}
			cout << "����Ϊ" << dist[i] << endl;
		}
	}
}
int main()
{
	Graph s;
	s.Create();
	s.Show();
	VertexType start_point;
	cout << "���������:";
	cin >> start_point;
	s.Dijkstra(start_point);
	system("pause");
	return 0;
}


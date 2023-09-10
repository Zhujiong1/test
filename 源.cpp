#include<iostream>
using namespace std;
#define MAX 20
typedef struct aft
{
	int loc;
	aft* next;
}aft;
typedef struct
{
	int indegree;
	char data[3];
	aft *aft;
}vnode;
typedef struct queuenode
{
	vnode data;
	struct queuenode* next;
}queuenode;
typedef struct
{
	queuenode* front;
	queuenode* rear;
}link;
void initqueue(link& q)
{
	q.front = q.rear = new queuenode;
	q.front->next = NULL;
}
void enqueue(link& q,vnode v)
{
	queuenode* p = new queuenode;
	p->data = v;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
}
vnode outqueue(link& q)
{
	vnode v;
	v = q.front->next->data;
	q.front = q.front->next;
	return v;
}
int main()
{
	char c;
	int n1,n2;
	cout << "请输入顶点数,弧数:" << endl;
	cin >> n1>>c>>n2;
	vnode v[20];
	cout << "请依次输入各个顶点的数据：" << endl;
	for (int i = 0; i < n1; i++)
	{
		v[i].indegree = 0;
		cin >> v[i].data;
		v[i].aft = NULL;
	}
	cout << "请输入顶点的数据,其直接后继的数据:"<<endl;
	for (int i = 0; i < n2; i++)
	{
		int a,b;
		char d1[3], d2[3];
		cin.get();
		scanf("%[^,],%s",&d1,&d2);
		for (int j = 0; j < n1; j++)
		{
			if (strcmp(d1, v[j].data) == 0)
			{
				a = j;
			}
			else if (strcmp(d2, v[j].data) == 0)
			{
				b = j;
				v[j].indegree++;
			}
		}
		aft* pp = new aft;
		pp->loc = b;
		pp->next = v[a].aft;
		v[a].aft = pp;
	}
	link q;
	initqueue(q);
	for (int i = 0; i < n1; i++)
	{
		if (v[i].indegree == 0)
		{
			enqueue(q, v[i]);
		}
	}
	cout << "拓扑排序的结果为：" << endl;
	while (q.front != q.rear)
	{
		vnode uu=outqueue(q);
		cout << uu.data << " ";
		if (uu.aft != NULL)
		{
			v[uu.aft->loc].indegree--;
			if (v[uu.aft->loc].indegree == 0)
				enqueue(q, v[uu.aft->loc]);
			aft* ii=uu.aft->next;
			while (ii != NULL)
			{
				v[ii->loc].indegree--;
				if (v[ii->loc].indegree == 0)
					enqueue(q, v[ii->loc]);
				ii = ii->next;
			}
		}
	}
	return 0;
}
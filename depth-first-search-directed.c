/*Implementing Depth First Search on a Directed Graph*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct Node /*a node in the adjacency list*/
{
	int value;
	struct Node* next;
};
struct Vertex /*a vertex in the adjacency list array*/
{
	int value;
	struct Node* head;
	int color;
	int predecessor;
	int d;
	int f;
};
int v; /*No. of vertices*/
int e; /*No. of edges*/
int **edge; /*Array to store the edges and their types*/
struct Vertex* G; /*The adjacency list*/
void createGraph();
void addEdge(int,int);
void printGraph();
void DFS();
int DFSVisit(int,int);
int ancestor(int,int);
void changeEdge(int,int,int);

void createGraph() 
{
	int i,a,b;
	G=(struct Vertex *)malloc(v*sizeof(struct Vertex));
	for(i=0;i<v;i++)
	{
		G[i].value=i;
		G[i].head=NULL;
	}
	printf("\nEnter no. of edges : ");
	scanf("%d",&e);
	edge=(int**)malloc(e*sizeof(int*));
	printf("\nVertices start numbering from 0. Enter the edges in format a b");
	for(i=0;i<e;i++)
	{
		printf("\nEnter vertices of edge no. %d : ",i);
		scanf("%d %d",&a,&b);
		addEdge(a,b);
		edge[i]=(int*)malloc(3*sizeof(int));
		edge[i][0]=a;
		edge[i][1]=b;
		edge[i][2]=3;
	}
}
void addEdge(int a,int b) /*To add an edge to the graph*/
{
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->value=b;
	newNode->next=G[a].head;
	G[a].head=newNode;
}
void printGraph()
{
	int i;
    for(i=0;i<v;i++)
	{
		printf("\nAdjacency List for vertex %d : ",i);
		struct Node* node=G[i].head;
		while(node)
		{
			printf("%d , ",node->value);
			node=node->next;
		}
	}
}
void DFS() /*Cormen's algo*/
{
	int i,time;
	for(i=0;i<v;i++)
	{
		G[i].color=0;
		G[i].predecessor=-1;
	}
	time=0;
	for(i=0;i<v;i++)
	{
		if(G[i].color==0)
			time=DFSVisit(i,time);
	}
}
int DFSVisit(int u,int time)
{
	int p;
	time++;
	G[u].d=time;
	G[u].color=1;
	printf("%d, ",u);
	struct Node* node=G[u].head;
	while(node)
	{
		p=node->value;
		if(G[p].color==1)
			changeEdge(u,p,1);
		if(G[p].color==2)
			if(ancestor(u,p))
				changeEdge(u,p,2);		
		if(G[p].color==0)
		{
			changeEdge(u,p,0);
			G[p].predecessor=u;
			printf("(%d,%d), ",u,p);
			time=DFSVisit(p,time);
		}
		node=node->next;
	}
	G[u].color=2;
	time++;
	G[u].f=time;
	return time;
}
void changeEdge(int a,int b,int c)
{
	int i;
	for(i=0;i<e;i++)
	{
		if(edge[i][0]==a && edge[i][1]==b)
			edge[i][2]=c;
		if(edge[i][0]==b && edge[i][1]==a)
			edge[i][2]=c;	
	}
}
int ancestor(int a,int b)
{
	int k=G[b].predecessor;
	do
	{
		if(k==a)
			return 1;
		k=G[k].predecessor;
	}while(k!=-1);
	return 0;
}
int main()
{
	int i;
	printf("Enter no. of vertices : ");
	scanf("%d",&v);
	createGraph();
	printGraph();
	printf("\nDepth First Traversal of the graph : ");
	DFS();
	printf("\nTree Edges : ");
	for(i=0;i<e;i++)
		if(edge[i][2]==0)
			printf("(%d,%d), ",edge[i][0],edge[i][1]);
	printf("\nBack Edges : ");
	for(i=0;i<e;i++)
		if(edge[i][2]==1)
			printf("(%d,%d), ",edge[i][0],edge[i][1]);
	printf("\nForward Edges : ");
	for(i=0;i<e;i++)
		if(edge[i][2]==2)
			printf("(%d,%d), ",edge[i][0],edge[i][1]);
	printf("\nCross Edges : ");
	for(i=0;i<e;i++)
		if(edge[i][2]==3)
			printf("(%d,%d), ",edge[i][0],edge[i][1]);
	return 0;
}


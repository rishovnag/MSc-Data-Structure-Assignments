/*Depth First Search on a Graph*/
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

void createGraph_undirected();
void createGraph_directed();
void addEdge_undirected(int,int);
void addEdge_directed(int,int);
void printGraph();
void DFS_undirected(int);
void DFS_directed(int);
int DFSVisit_undirected(int,int);
int DFSVisit_directed(int,int);
void changeEdge_undirected(int,int,int);
void changeEdge_directed(int,int,int);
int ancestor(int,int);
int map(int);

void createGraph_undirected() 
{
	int i,a,b,vertex;
	G=(struct Vertex *)malloc(v*sizeof(struct Vertex));
	for(i=0;i<v;i++)
	{
		printf("\nEnter the value for vertex %d ",i+1);
		scanf("%d",&vertex);
		G[i].value=vertex;
		G[i].head=NULL;
	}
	printf("\nEnter no. of edges : ");
	scanf("%d",&e);
	edge=(int**)malloc(e*sizeof(int*));
	printf("\nEnter the edges in format a b");
	for(i=0;i<e;i++)
	{
		printf("\nEnter vertices of edge no. %d : ",i+1);
		scanf("%d %d",&a,&b);
		addEdge_undirected(a,b);
		edge[i]=(int*)malloc(4*sizeof(int));
		edge[i][0]=map(a);
		edge[i][1]=map(b);
		edge[i][2]=3;
		edge[i][3]=0;
	}
}

void createGraph_directed() 
{
	int i,a,b,vertex;
	G=(struct Vertex *)malloc(v*sizeof(struct Vertex));
	for(i=0;i<v;i++)
	{
		printf("\nEnter the value for vertex %d ",i+1);
		scanf("%d",&vertex);
		G[i].value=vertex;
		G[i].head=NULL;
	}
	printf("\nEnter no. of edges : ");
	scanf("%d",&e);
	edge=(int**)malloc(e*sizeof(int*));
	printf("\nEnter the edges in format a b");
	for(i=0;i<e;i++)
	{
		printf("\nEnter vertices of edge no. %d : ",i+1);
		scanf("%d %d",&a,&b);
		addEdge_directed(a,b);
		edge[i]=(int*)malloc(4*sizeof(int));
		edge[i][0]=map(a);
		edge[i][1]=map(b);
		edge[i][2]=3;
	}
}

void addEdge_undirected(int a,int b) /*To add an edge to the graph*/
{
	int i;
	struct Node* newNode1=(struct Node*)malloc(sizeof(struct Node));
	newNode1->value=b;
	i=map(a);
	newNode1->next=G[i].head;
	G[i].head=newNode1;
	struct Node* newNode2=(struct Node*)malloc(sizeof(struct Node));
	newNode2->value=a;
	i=map(b);
	newNode2->next=G[i].head;
	G[i].head=newNode2;
}

void addEdge_directed(int a,int b) /*To add an edge to the graph*/
{
	int i;
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->value=b;
	i=map(a);
	newNode->next=G[i].head;
	G[i].head=newNode;
}

void printGraph()
{
	int i;
    for(i=0;i<v;i++)
	{
		printf("\nAdjacency List for vertex %d : ",G[i].value);
		struct Node* node=G[i].head;
		while(node)
		{
			printf("%d , ",node->value);
			node=node->next;
		}
	}
}

void DFS_undirected(int s) /*Cormen's algo*/
{
	int i,time,p;
	for(i=0;i<v;i++)
	{
		G[i].color=0;
		G[i].predecessor=-1;
	}
	time=0;
	p=map(s);
	for(i=p;i<v;i++)
	{
		if(G[i].color==0)
			time=DFSVisit_undirected(i,time);
	}
	for(i=0;i<p;i++)
	{
		if(G[i].color==0)
			time=DFSVisit_undirected(i,time);
	}
}

void DFS_directed(int s) /*Cormen's algo*/
{
	int i,time,p;
	for(i=0;i<v;i++)
	{
		G[i].color=0;
		G[i].predecessor=-1;
	}
	time=0;
	p=map(s);
	for(i=p;i<v;i++)
	{
		if(G[i].color==0)
			time=DFSVisit_directed(i,time);
	}
	for(i=0;i<p;i++)
	{
		if(G[i].color==0)
			time=DFSVisit_directed(i,time);
	}
}


int DFSVisit_undirected(int u,int time)
{
	int p,q;
	time++;
	G[u].d=time;
	G[u].color=1;
	printf("%d, ",G[u].value);
	struct Node* node=G[u].head;
	while(node)
	{
		q=node->value;
		p=map(q);
		if(G[p].color==1)
			changeEdge_undirected(u,p,1);
		if(G[p].color==2)
			if(ancestor(u,p))
				changeEdge_undirected(u,p,2);		
		if(G[p].color==0)
		{
			changeEdge_undirected(u,p,0);
			G[p].predecessor=u;
			printf("(%d,%d), ",G[u].value,G[p].value);
			time=DFSVisit_undirected(p,time);
		}
		node=node->next;
	}
	G[u].color=2;
	time++;
	G[u].f=time;
	return time;
}

int DFSVisit_directed(int u,int time)
{
	int p,q;
	time++;
	G[u].d=time;
	G[u].color=1;
	printf("%d, ",G[u].value);
	struct Node* node=G[u].head;
	while(node)
	{
		q=node->value;
		p=map(q);
		if(G[p].color==1)
			changeEdge_directed(u,p,1);
		if(G[p].color==2)
			if(ancestor(u,p))
				changeEdge_directed(u,p,2);		
		if(G[p].color==0)
		{
			changeEdge_directed(u,p,0);
			G[p].predecessor=u;
			printf("(%d,%d), ",G[u].value,G[p].value);
			time=DFSVisit_directed(p,time);
		}
		node=node->next;
	}
	G[u].color=2;
	time++;
	G[u].f=time;
	return time;
}

void changeEdge_undirected(int a,int b,int c)
{
	int i;
	for(i=0;i<e;i++)
	{
		if(edge[i][0]==a && edge[i][1]==b && edge[i][3]==0)
		{
			edge[i][2]=c;
			edge[i][3]=1;
		}
		if(edge[i][0]==b && edge[i][1]==a && edge[i][3]==0)
		{
			edge[i][2]=c;
			edge[i][3]=1;
		}
	}
}

void changeEdge_directed(int a,int b,int c)
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

int map(int a)
{
	int i;
	for(i=0;i<v;i++)
	{
		if(G[i].value==a)
			return i;
	}
	return -1;
}

int main()
{
	int i,s,ch,c;
	do
	{
		printf("\n1.Directed Graph\t2.Undirected Graph ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					printf("Enter no. of vertices : ");
					scanf("%d",&v);
					createGraph_directed();
					printGraph();
					do
					{
						printf("\nEnter the vertex from which DFS should start : ");
						scanf("%d",&s);
						printf("\nDepth First Traversal of the graph : ");
						DFS_undirected(s);
						printf("\nTree Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==0)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nBack Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==1)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nForward Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==2)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nCross Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==3)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nDo you want to continue with the same graph? Press 1 for Yes...");
						scanf("%d",&c);
					}while(c==1);
					break;
			case 2:
					printf("Enter no. of vertices : ");
					scanf("%d",&v);
					createGraph_undirected();
					printGraph();
					do
					{
						printf("\nEnter the vertex from which DFS should start : ");
						scanf("%d",&s);
						printf("\nDepth First Traversal of the graph : ");
						DFS_undirected(s);
						printf("\nTree Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==0)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nBack Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==1)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nForward Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==2)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nCross Edges : ");
						for(i=0;i<e;i++)
							if(edge[i][2]==3)
								printf("(%d,%d), ",G[edge[i][0]].value,G[edge[i][1]].value);
						printf("\nDo you want to continue with the same graph? Press 1 for Yes...");
						scanf("%d",&c);
					}while(c==1);
					break;
			default:
					printf("\nwrong Choice!!Enter Again.....");
		}
		printf("Do you want to continue with another graph? Press 1 for Yes..");
		scanf("%d",&ch);
	}while(ch==1);
	return 0;
}

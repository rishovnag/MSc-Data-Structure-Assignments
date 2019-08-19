/*BFS*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct Node  /*adjacency list er node*/
{
	int value;
	struct Node* next;
};

struct Vertex /*adjacency list er array*/
{
	int value;
	struct Node* head;
	int color;
	int predecessor;
	int distance;
};

struct QueueNode
{
	int value;
	struct QueueNode* next;
};

int v; /*No. of vertices*/
struct Vertex* G; /*The adjacency list*/
struct QueueNode* qhead; /*The queue using FIFO strategy*/

void addQueue(int);
int delQueue();
void createGraph_directed();
void createGraph_undirecteddirected();
void addEdge_directed(int,int);
void addEdge_undirected(int,int);
void printGraph();
void BFS_directed(int);
void BFS_undireted(int);
void printpath(int,int);
int map(int);

void addQueue(int a) 
{
	struct QueueNode* newNode=(struct QueueNode*)malloc(sizeof(struct QueueNode));
	newNode->value=a;
	if(!qhead)
	{
			qhead=newNode;
			qhead->next=NULL;
	}
	else
	{
		newNode->next=qhead;
		qhead=newNode;
	}
}

int delQueue() /*Return the value of the deleted node*/
{
	int x;
	if(!qhead)
		return -1;
	struct QueueNode* node=qhead, *prev=qhead;
	while(node->next)
	{
		prev=node;
		node=node->next;
	}
	if(node==qhead)
		qhead=NULL;
	else
		prev->next=NULL;
	x=node->value;
	return x;
}

void createGraph_directed() 
{
	int i,a,b,vertex,e;
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
	printf("\nEnter the edges in format a b");
	for(i=0;i<e;i++)
	{
		printf("\nEnter vertices of edge no. %d : ",i+1);
		scanf("%d %d",&a,&b);
		addEdge_directed(a,b);
	}
}

void createGraph_undirected() 
{
	int i,a,b,vertex,e;
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
	printf("\nEnter the edges in format a b");
	for(i=0;i<e;i++)
	{
		printf("\nEnter vertices of edge no. %d : ",i+1);
		scanf("%d %d",&a,&b);
		addEdge_undirected(a,b);
	}
}

void addEdge_directed(int a,int b) /*To add an edge to the graph*/
{
	int i;
	struct Node* newNode1=(struct Node*)malloc(sizeof(struct Node));
	newNode1->value=b;
	i=map(a);
	newNode1->next=G[i].head;
	G[i].head=newNode1;
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

void BFS_directed(int s) /*Cormen's algo*/
{
	int i,u,p,q,flag=0;
	q=map(s);
	for(i=0;i<v;i++)
	{
		if(i==q)
			continue;
		G[i].color=0;
		G[i].distance=INT_MAX;
		G[i].predecessor=-1;
	}
	G[q].color=1;
	G[q].distance=0;
	G[q].predecessor=-1;
	
	do
	{
		flag=0;
		qhead=NULL;
		addQueue(s);
		while(qhead)
		{
			u=map(delQueue());
			struct Node* node=G[u].head;
			while(node)
			{
				p=map(node->value);
				if(G[p].color==0)
				{
					G[p].color=1;
					G[p].distance=G[u].distance+1;
					G[p].predecessor=u;
					addQueue(G[p].value);
					printf("(%d,%d), ",G[u].value,G[p].value);
				}
				node=node->next;
			}
			G[u].color=2;
			printf("%d, ",G[u].value);
		}
		for(i=0;i<v;i++)
		{
			if(G[i].color!=2)
			{
				flag=1;
				s=G[i].value;
				break;
			}
		}
	}while(flag==1);
}

void BFS_undirected(int s) /*Cormen's algo*/
{
	int i,u,p,q,flag=0;
	q=map(s);
	for(i=0;i<v;i++)
	{
		if(i==q)
			continue;
		G[i].color=0;
		G[i].distance=INT_MAX;
		G[i].predecessor=-1;
	}
	G[q].color=1;
	G[q].distance=0;
	G[q].predecessor=-1;
	
	do
	{
		flag=0;
		qhead=NULL;
		addQueue(s);
		while(qhead)
		{
			u=map(delQueue());
			struct Node* node=G[u].head;
			while(node)
			{
				p=map(node->value);
				if(G[p].color==0)
				{
					G[p].color=1;
					G[p].distance=G[u].distance+1;
					G[p].predecessor=u;
					addQueue(G[p].value);
					printf("(%d,%d), ",G[u].value,G[p].value);
				}
				node=node->next;
			}
			G[u].color=2;
			printf("%d, ",G[u].value);
		}
		for(i=0;i<v;i++)
		{
			if(G[i].color!=2)
			{
				flag=1;
				s=G[i].value;
				break;
			}
		}
	}while(flag==1);
}

void printpath(int s,int t)
{
	if(s==t)
		printf("%d, ",G[t].value);
	else if(G[t].predecessor==-1)
		printf("No path from %d to %d exists",G[s].value,G[t].value);
	else
	{
		printpath(s,G[t].predecessor);	
		printf("%d, ",G[t].value);
	}
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
	int s,a,b,ch,c,choice;
	do
	{
		printf("\n1.Directed Graph \t2.Undirected Graph\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
					printf("\nDirected Graph\n");
					printf("Enter no. of vertices : ");
					scanf("%d",&v);
					createGraph_directed();
					printGraph();
					do{
							printf("\nEnter 1 for BFS,2 for shortest distance and 3 for Exit : ");
							scanf("%d",&ch);
							switch(ch)
							{
								case 1: printf("\nEnter the vertex from which BFS should start : ");
										scanf("%d",&s);
										printf("\nBreadth First Traversal of the graph : ");
										BFS_directed(s);
										break;
								case 2: printf("\nEnter the 2 vertices : ");
										scanf("%d %d",&a,&b);
										BFS_directed(a);
										printf("Shortest distance : %d",G[map(b)].distance);
										printf("\nPath : ");
										printpath(map(a),map(b));
										break;
								case 3: break;
							}
						}while(ch!=3);
						break;
			case 2:
					printf("\nUndirected Graph\n");
					printf("Enter no. of vertices : ");
					scanf("%d",&v);
					createGraph_undirected();
					printGraph();
					do{
							printf("\nEnter 1 for BFS,2 for shortest distance and 3 for Exit : ");
							scanf("%d",&ch);
							switch(ch)
							{
								case 1: printf("\nEnter the vertex from which BFS should start : ");
										scanf("%d",&s);
										printf("\nBreadth First Traversal of the graph : ");
										BFS_undirected(s);
										break;
								case 2: printf("\nEnter the 2 vertices : ");
										scanf("%d %d",&a,&b);
										BFS_undirected(a);
										printf("Shortest distance : %d",G[map(b)].distance);
										printf("\nPath : ");
										printpath(map(a),map(b));
										break;
								case 3: break;
							}
						}while(ch!=3);
						break;
		}
		printf("Do you want to continue with another graph? Press 1 for Yes..");
		scanf("%d",&c);
	}while(c==1);
	return 0;
}

























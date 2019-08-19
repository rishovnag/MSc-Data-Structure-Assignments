/*Implementing Breadth First Search on a directed graph*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
struct Node
{
	int value;
	struct Node* next;
};
struct Vertex
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
struct QueueNode* qhead; /*The queue using FIFO startegy*/
void addQueue(int);
int delQueue();
void createGraph();
void addEdge(int,int);
void printGraph();
void BFS(int);
void printpath(int,int);

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
void createGraph()
{
	int i,e,a,b;
	G=(struct Vertex *)malloc(v*sizeof(struct Vertex));
	for(i=0;i<v;i++)
	{
		G[i].value=i;
		G[i].head=NULL;
	}
	printf("\nEnter no. of edges : ");
	scanf("%d",&e);
	printf("\nVertices start numbering from 0.");
	for(i=0;i<e;i++)
	{
		printf("\nEnter vertices of edge no. %d : ",i);
		scanf("%d %d",&a,&b);
		addEdge(a,b);
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
void BFS(int s) /*Cormen's algo*/
{
	int i,u,p;
	for(i=0;i<v;i++)
	{
		if(i==s)
			continue;
		G[i].color=0;
		G[i].distance=INT_MAX;
		G[i].predecessor=-1;
	}
	G[s].color=1;
	G[s].distance=0;
	G[s].predecessor=-1;
	qhead=NULL;
	addQueue(s);
	while(qhead)
	{
		u=delQueue();
		struct Node* node=G[u].head;
		while(node)
		{
			p=node->value;
			if(G[p].color==0)
			{
				G[p].color=1;
				G[p].distance=G[u].distance+1;
				G[p].predecessor=u;
				addQueue(p);
				printf("(%d,%d), ",u,p);
				printf("%d, ",p);
			}
			node=node->next;
		}
		G[u].color=2;
	}
}
void printpath(int s,int t)
{
	if(s==t)
		printf("%d, ",t);
	else if(G[t].predecessor==-1)
		printf("No path from %d to %d exists",s,t);
	else
	{
		printpath(s,G[t].predecessor);	
		printf("%d, ",t);
	}
}
int main()
{
	int s,a,b,ch;
	printf("Enter no. of vertices : ");
	scanf("%d",&v);
	createGraph();
	printGraph();
	do{
		printf("\nEnter 1 for BFS,2 for shortest distance and 3 for Exit : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: printf("\nEnter the vertex from which BFS should start : ");
	                scanf("%d",&s);
	                printf("\nBreadth First Traversal of the graph : ");
	                BFS(s);
	                break;
	        case 2: printf("\nEnter the 2 vertices : ");
	        		scanf("%d %d",&a,&b);
	        		BFS(a);
	        		printf("Shortest distance : %d",G[b].distance);
	        		printf("\nPath : ");
	        		printpath(a,b);
	        case 3: break;
		}
	}while(ch!=3);
	return 0;
}


/*Implementation of a graph using adjacency list*/
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	int weight;
	struct node *next;
};
void undirectedunweighted(); /*function for an undirected and unweighted graph*/
void undirectedweighted(); /*function for an undirected and weighted graph*/
void directedunweighted(); /*function for an directed and unweighted graph*/
void directedweighted(); /*function for an directed and weighted graph*/
int map(struct node* [],int,int); /*This function maps the vertices to a ordered list of numbers*/
void insert(struct node*,int,int); /*This function enters a node into the adjacency list*/
void display(struct node* [],int); /*This function displays the adjacency list*/

int main()
{
	int ch,c;
	do{
		printf("\n1. Undirected and Unweighted Graph \n2. Undirected and Weighted Graph \n3. Directed and Unweighted Graph \n4. Directed and Weighted Graph \n5. Exit \t");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: undirectedunweighted();
					break;
			case 2: undirectedweighted();
					break;
			case 3: directedunweighted();
					break;
			case 4: directedweighted();
					break;
			case 5: exit(1);
			default: printf("\nWrong Choice. Enter Again.......");
					 break;
		}
		printf("\nDo you want to continue? (Press 1 for yes)");		
		scanf("%d",&c);
	}while(c==1);
}
void undirectedunweighted()
{
	struct node *n[100], *q;
	int v,e,i,ch,ver1,ver2,ver;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		/*When a new vertex is taken as an input, a node is created and added to the array n[]*/
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=(struct node *)(malloc(sizeof(struct node)));
		n[i]->data=ch;
		n[i]->next=NULL;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the adjacency list*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("\nEnter edge number %d \n",(i+1));
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		ver=map(n,ver1,v);
		q=n[ver];
		/*After vertex 1 is mapped into the corresponding position of the array, vertex 2 is linked to that position through a link*/
		insert(q,ver2,0);
		ver=map(n,ver2,v);
		q=n[ver];
		/*After vertex 2 is mapped into the corresponding position of the array, vertex 1 is linked to that position through a link
		 as this is an undirected graph*/
		insert(q,ver1,0);
	}
	display(n,v);
}

void undirectedweighted()
{
	int i,v,e,ver,ver1,ver2,ch,w;
	struct node *n[100],*q;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		/*When a new vertex is taken as an input, a node is created and added to the array n[]*/
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=(struct node *)(malloc(sizeof(struct node)));
		n[i]->data=ch;
		n[i]->next=NULL;
		n[i]->weight=0;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the adjacency list*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("\nEnter edge number %d \n",(i+1));
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		/*The weight for each and every edge is asked*/
		printf("Enter the weight of the edge: ");
		scanf("%d",&w);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		ver=map(n,ver1,v);
		q=n[ver];
		/*After vertex 1 is mapped into the corresponding position of the array, vertex 2 is linked to that position through a link*/
		insert(q,ver2,w);
		ver=map(n,ver2,v);
		q=n[ver];
		/*After vertex 2 is mapped into the corresponding position of the array, vertex 1 is linked to that position through a link
		 as this is an undirected graph*/
		insert(q,ver1,w);
	}
	display(n,v);
}

void directedunweighted()
{
	int i,v,e,ver,ver1,ver2,ch;
	struct node *n[100], *q;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		/*When a new vertex is taken as an input, a node is created and added to the array n[]*/
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=(struct node *)(malloc(sizeof(struct node)));
		n[i]->data=ch;
		n[i]->next=NULL;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the adjacency list*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("\nEnter edge number %d \n",(i+1));
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		ver=map(n,ver1,v);
		q=n[ver];
		/*After vertex 1 is mapped into the corresponding position of the array, vertex 2 is linked to that position through a link.
		 This is not done for vertex 2 as this is a directed graph*/
		insert(q,ver2,0);
	}
	display(n,v);
}

void directedweighted()
{
	int i,v,e,ver,ver1,ver2,ch,w;
	struct node *n[100],*q;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		/*When a new vertex is taken as an input, a node is created and added to the array n[]*/
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=(struct node *)(malloc(sizeof(struct node)));
		n[i]->data=ch;
		n[i]->next=NULL;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the adjacency list*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("\nEnter edge number %d \n",(i+1));
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		printf("Enter the weight of the edge: ");
		scanf("%d",&w);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		ver=map(n,ver1,v);
		q=n[ver];
		/*After vertex 1 is mapped into the corresponding position of the array, vertex 2 is linked to that position through a link.
		 This is not done for vertex 2 as this is a directed graph*/
		insert(q,ver2,w);
	}
	display(n,v);
}

int map(struct node *ver[], int val, int v)
{
	/*The value of a vertex is compared to the elements of the ver array to get the index of that vertex which is used as a 
	 standard notation for all the calculations*/
	int i;
	for(i=0;i<v;i++)
	{
		if(ver[i]->data==val)
			return i;
	}
	return -999;
}

void insert(struct node *q, int v, int w)
{
	/*In this function a node is inserted into the adjacency list. q is the node to which we have to connect the new node.
	 The value abd weight of the new node are v and w respectively*/
	struct node *nv;
	nv=(struct node*)(malloc(sizeof(struct node)));
	nv->data=v;
	nv->weight=w;
	nv->next=NULL;
	while(q->next!=NULL)
	{ /*Here we have to check if there are any nodes previously connected to q or not*/
		q=q->next; 
	}
	q->next=nv;
}

void display(struct node *v[],int nv)
{
	/*The respective adjacency list is displayed for the respective graphs*/
	struct node *q;
	int i;
	for(i=0;i<nv;i++)
	{
		q=v[i];
		while(q->next!=NULL)
		{
			/*For each node present in the graph we print all the nodes connected to that node*/
			printf(" %d (%d) -> ",q->data,q->weight);
			q=q->next;
		}
		printf(" %d (%d) \n",q->data,q->weight);		
	}
}

/*Implementation of a graph using incidence matrix*/
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int direction;
	int weight;
};
void undirectedunweighted(); /*function for an undirected and unweighted graph*/
void undirectedweighted(); /*function for an undirected and weighted graph*/
void directedunweighted(); /*function for an directed and unweighted graph*/
void directedweighted(); /*function for an directed and weighted graph*/
int map(int [100],int,int); /*This function maps the vertices to a ordered list of numbers*/
void display(struct node [100][200],int[100],int,int); /*This function displays the incidence matrix*/

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
	int n[100];
	struct node a[100][200];
	int v,e,i,j,ch,ver1,ver2,v1,v2;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*All the direction elements of the incidence matrix is assigned to zero*/
	for(i=0;i<v;i++)
		for(j=0;j<e;j++)
			a[i][j].direction=0;
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=ch;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the incidence matrix*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("\nEnter edge number %d \n",(i+1));
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		v1=map(n,ver1,v);
		v2=map(n,ver2,v);
		/*Input into the incidence matrix is made keeping in mind it is an undirected graph*/
		a[v1][i].direction=1;
		a[v2][i].direction=1;
		a[v1][i].weight=0;
		a[v2][i].weight=0;
	}
	display(a,n,v,e);
}

void undirectedweighted()
{
	int n[100];
	struct node a[100][200];
	int v,e,i,j,ch,ver1,ver2,v1,v2,w;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*All the weight and distance elements of the incidence matrix are assigned to -999 and 0 respectively, 
	  where -999 is used to represent an absece of an edge*/
	for(i=0;i<v;i++)
		for(j=0;j<e;j++)
			{
				a[i][j].direction=0;
				a[i][j].weight=-999;
			}
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=ch;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the incidence matrix*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("\nEnter edge number %d ",(i+1));
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		/*The weight for each and every edge is asked*/
		printf("Enter the weight of the edge ");
		scanf("%d",&w);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		v1=map(n,ver1,v);
		v2=map(n,ver2,v);
		/*Input into the incidence matrix is made keeping in mind it is an undirected but weighted graph*/
		a[v1][i].direction=1;
		a[v2][i].direction=1;
		a[v1][i].weight=w;
		a[v2][i].weight=w;
	}
	display(a,n,v,e);
}

void directedunweighted()
{
	int n[100];
	struct node a[100][200];
	int v,e,i,j,ch,ver1,ver2,v1,v2;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*All the direction elements of the incidence matrix is assigned to zero*/
	for(i=0;i<v;i++)
		for(j=0;j<e;j++)
			a[i][j].direction=0;
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=ch;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the incidence matrix*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		v1=map(n,ver1,v);
		v2=map(n,ver2,v);
		/*Input into the incidence matrix is made keeping in mind it is a directed graph*/
		a[v1][i].direction=1;
		a[v2][i].direction=-1;
		a[v1][i].weight=0;
		a[v2][i].weight=0;
	}
	display(a,n,v,e);
}

void directedweighted()
{
	int n[100];
	struct node a[100][200];
	int v,e,i,j,ch,ver1,ver2,v1,v2,w;
	/*The input for number of vertices and number of edges is taken*/
	printf("\nEnter the number of vertices: ");
	scanf("%d",&v);
	printf("\nEnter the number of edges: ");
	scanf("%d",&e);
	/*All the direction and weight elements of the incidence matrix are assigned to 0 and -999 respectively, 
	  which is used to represent an absece of an edge*/
	for(i=0;i<v;i++)
		for(j=0;j<e;j++)
			{
				a[i][j].direction=0;
				a[i][j].weight=-999;
			}
	/*Input for the name of all the vertices is asked (strictly integers)*/
	printf("\nEnter the name of the vertices: ");
	for(i=0;i<v;i++)
	{
		printf("\nEnter vertice number %d ",(i+1));
		scanf("%d",&ch);
		n[i]=ch;
	}
	/*The edges are mapped accordingly to a given standard notation for representing each vertex and entered correspondingly 
	  into the incidence matrix*/
	printf("\nEnter the name of the edges: ");
	for(i=0;i<e;i++)
	{
		printf("The edge is connected from ");
		scanf("%d",&ver1);
		printf("to ");
		scanf("%d",&ver2);
		/*The Weight of the edge is asked for input*/
		printf("Enter the weight of the edge ");
		scanf("%d",&w);
		/*the map function maps the two vertices accordingly, i.e we know in which position of the array n the vertices lie*/
		v1=map(n,ver1,v);
		v2=map(n,ver2,v);
		/*Input into the incidence matrix is made keeping in mind it is directed and weighted graph*/
		a[v1][i].direction=1;
		a[v2][i].direction=-1;
		a[v1][i].weight=w;
		a[v2][i].weight=w;
	}
	display(a,n,v,e);
}

int map(int ver[], int val, int v)
{
	/*The value of a vertex is compared to the elements of the ver array to get the index of that vertex which is used as a 
	 standard notation for all the calculations*/
	int i;
	for(i=0;i<v;i++)
	{
		if(ver[i]==val)
			return i;
	}
	return -999;
}

void display(struct node a[100][200], int b[100], int nv,int ne)
{
	/*The respective incidence matrix is displayed for the respective graphs*/
	int i,j;
	printf("\t");
	for(i=0;i<ne;i++)
		printf("%d\t",(i+1));
	printf("\n");
	for(i=0;i<nv;i++)
	{
		printf("%d\t",b[i]);
		for(j=0;j<ne;j++)
			printf("%d(%d)\t",a[i][j].direction,a[i][j].weight); /*This nested loop prints the respective elements of the array*/
		printf("\n");
	}
}


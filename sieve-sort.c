/* ASSIGNMENT 10 : SIEVE SORT */

#include<stdio.h>
#include<stdlib.h>


struct node
{
	int d;
	struct node *left;
	struct node *right;
};

struct node *createlist(int n);
struct node *firstlist(struct node *h1, int *c);
struct node *sort(struct node *h1,int n);
struct node *right(struct node *h1, int *c);
struct node *left(struct node *h1, int *c);
struct node *create();
void display(struct node *h);


int main(void)
{
	int n,c=0,flag=0;
	struct node *h1, *h2;
	while(flag==0)
	{
		flag=1;
		printf("Enter number of elements: ");
		scanf("%d",&n);
		if(n<=0)
		printf("\nNo elements to enter!");
		else
		{
			h1=createlist(n);
			h1=firstlist(h1,&c);
			h1=sort(h1,n);
			display(h1);
		}
		printf("\n");
		printf("\nPress 0 to continue... ");
		scanf("%d",&flag);
	}
	return 0;
}


struct node *createlist(int n)
{
	struct node *h=NULL, *t, *s;
	int i;
	for(i=0;i<n;i++)
	{
	t=(struct node *)malloc(sizeof(struct node));
	printf("\nEnter data: ");
	scanf("%d",&t->d);
	if(h==NULL)
	{
	h=t;
	t->left=NULL;
	}
	else
	{
	s->right=t;
	t->left=s;
	}
	t->right=NULL;
	s=t;
	}
	return h;
}


struct node *firstlist(struct node *h1, int *c)
{
	struct node *h=NULL, *t=h1, *t1, *s, *t2, *t3;
	while(t!=NULL)
	{
	t1=create();
	t1->d=t->d;
	if(h==NULL)
	{
	h=t1;
	(*c)++;
	}
	else
	{
	t2=h;
	if(t1->d > t2->d)
	{
	while(t1->d > t2->d && t2->left!=NULL)
	t2=t2->left;
	if(t1->d > t2->d && t2->left==NULL)
	{
	(*c)++;
	t2->left=t1;
	}
	else if(t1->d < t2->d)
	{
	t3=t2;
	while(t3->right!=NULL)
	t3=t3->right;
	t3->right=t1;
	t1->left=t3;	
	}
	}
	else
	{
	t3=t2;
	while(t3->right!=NULL)
	t3=t3->right;
	t3->right=t1;
	t1->left=t3;	
	}	
	}
	s=t1;
	t=t->right;
	}
	return h;
}


struct node *sort(struct node *h1, int n)
{
	int i=1, c=0;
	struct node *t;
	while(c<n)
	{
	if(i%2==0)
	{
	c=0;
	h1=right(h1,&c);	
	t=h1;
	}
	else
	{
	c=0;
	h1=left(h1,&c);
	}
	i++;
	}
	return h1;
}


struct node *right(struct node *h1, int *c)
{
	struct node *h=h1, *t1, *t2, *head, *h2=h1, *t3;
	int flag, f=0;
	while(h->left!=NULL)
	{
	h=h->left;
	f=1;
	}
	t1=create();
	t1->d=h->d;
	h=h->right;
	head=t1;
	(*c)++;
	if(f==0)
	h2=h2->right;
	while(h2!=NULL)
	{
	flag=0;
	while(flag==0 && h!=NULL)
	{
	if(h==h2)
	flag=1;
	t1=create();
	t1->d=h->d;
	t2=head;
	if(t1->d > t2->d)
	{
	while(t1->d > t2->d && t2->left!=NULL)
	t2=t2->left;
	if(t1->d > t2->d && t2->left==NULL)
	{
	t2->left=t1;
	(*c)++;
	}
	else if(t1->d < t2->d)
	{
	t3=t2;
	while(t3->right!=NULL)
	t3=t3->right;
	t3->right=t1;
	t1->left=t3;	
	}
	}
	else
	{
	t3=t2;
	while(t3->right!=NULL)
	t3=t3->right;
	t3->right=t1;
	t1->left=t3;	
	}
	h=h->right;	
	}
	h2=h2->right;
	if(h2!=NULL)
	{
	h=h2;
	while(h->left!=NULL)
	h=h->left;
	}
	}
	return head;
}


struct node *left(struct node *h1, int *c)
{
	struct node *h=h1, *t1, *t2, *head, *h2=h1, *t3;
	int flag=0, f=0;
	while(h->right!=NULL)
	{
	h=h->right;
	f=1;
	}
	t1=create();
	t1->d=h->d;
	h=h->left;
	head=t1;
	(*c)++;
	if(f==0)
	h2=h2->left;
	while(h2!=NULL)
	{
	flag=0;
	while(flag==0 && h!=NULL)
	{
	if(h==h2)
	flag=1;
	t1=create();
	t1->d=h->d;
	t2=head;
	if(t1->d > t2->d)
	{
	while(t1->d > t2->d && t2->right!=NULL)
	t2=t2->right;
	if(t1->d > t2->d && t2->right==NULL)
	{
	(*c)++;
	t2->right=t1;
	}
	else if(t1->d < t2->d)
	{
	t3=t2;
	while(t3->left!=NULL)
	t3=t3->left;
	t3->left=t1;
	t1->right=t3;	
	}
	}
	else
	{
	t3=t2;
	while(t3->left!=NULL)
	t3=t3->left;
	t3->left=t1;
	t1->right=t3;	
	}
	h=h->left;	
	}
	h2=h2->left;
	if(h2!=NULL)
	{
	h=h2;
	while(h->right!=NULL)
	h=h->right;
	}
	}
	return head;
}


struct node *create()
{
	struct node *t=(struct node *)malloc(sizeof(struct node));
	t->left=NULL;
	t->right=NULL;
	return t;
}


void display(struct node *h)
{
	struct node *t=h;
	printf("\nThe sorted list is...\n");
	if(t->left!=NULL)
	{
	while(t!=NULL)
	{
	printf("\n%d",t->d);
	t=t->left;
	}
	}
	else if(t->right!=NULL)
	{
	while(t!=NULL)
	{
	printf("\n%d",t->d);
	t=t->right;
	}
	}
}


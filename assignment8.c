/*Implementing operations on an AVL Tree*/
 
#include<stdio.h>
#include<stdlib.h>
#define COUNT 10

struct node
{
    int data;
    struct node *left,*right;
    int height;
}node;
 
struct node *insert_node(struct node *,int);	/*Inserting a node into the AVL Tree*/
struct node *delete_node(struct node *,int);	/*deleting a node from the AVL Tree*/
int height_tree(struct node *);	/*Calculating height of the AVL Tree*/
struct node *rotateright(struct node *);	/*Rotating the given tree right*/
struct node *rotateleft(struct node *); /*Rotating the given tree left*/
struct node *RR(struct node *);	/*This function implements the case of the double right rotation*/
struct node *LL(struct node *);	/*This function implements the case of the double left rotation*/
struct node *LR(struct node *);	/*This function implements the case of the left roation and then the right rotation*/
struct node *RL(struct node *);	/*This function implements the case of the right roation and then the left rotation*/
int balance_factor(struct node *); 	/*This function calculates the balance factor of a given node*/
void print2DUtil(struct node *,int);	/*Printing the the given tree*/   
void print2D(struct node *);


 
void print2DUtil(struct node *T, int space)   /*This function helps in printing the tree and is inspired from MyCodeSchool*/
{
	int i,j;
    // Base case
    if (T == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(T->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (i = COUNT; i < space; i++)
        printf(" ");
    j=balance_factor(T);    
    printf("%d(%d)\n", T->data,j);
 
    // Process left child
    print2DUtil(T->left, space);
    
}
 
// Wrapper over print2DUtil()
void print2D(struct node *T)
{
   // Pass initial space count as 0
   print2DUtil(T, 0);
} 
 
struct node * insert_node(struct node *T,int x)   
/*The insert function takes the root of the tree and the data field of the node to be inserted as the input parameters*/ 
{
    if(T==NULL)
    { /*If the tree is empty a new node is created and the data is inserted into this node */
        T=(struct node*)malloc(sizeof(struct node));
        T->data=x;
        T->left=NULL;
        T->right=NULL;
    }
    else
    { /*We have to decide where the new node is to be inserted*/
		if(x > T->data)        
        {  /*inserting in the right subtree*/
			T->right=insert_node(T->right,x);
            if(balance_factor(T)==-2) /*Case of Right High*/
			{
				/*here we have to balance the tree if required*/
                if(x>T->right->data)
                    T=RR(T); /*this is the case of a double right rotation*/
                else
                    T=RL(T); /*this is the case of a right rotation and then a left rotation*/
			}
		}
        else	
        { /*inserting in the left subtree*/
			T->left=insert_node(T->left,x);
            if(balance_factor(T)==2) /*Case of Left High*/
			{
				/*here we have to balance the tree if required*/
				if(x < T->left->data)
					T=LL(T); /*this is the case of a double left rotation*/
                else
                    T=LR(T); /*this is the case of a left rotation and then a right rotation*/
			}
		}
	}
    T->height=height_tree(T); /*height of the tree for the node T is calculated*/
    return(T);
}
 
struct node * delete_node(struct node *T,int x)
{
	/*The delete function takes the root of the tree and the data field of the node to be deleted as the input parameters*/ 
    struct node *p;
    if(T==NULL)
    {
        return NULL;
    }
    else
        if(x > T->data)        
        {
			/*If x is greater than the data present in the node T, we again call the delete function and send the right
			 child of node T till the node to be deleted is found*/
            T->right=delete_node(T->right,x);
            if(balance_factor(T)==2) /*Case of Left High*/
            {
				/*here we have to rebalance the tree if required*/
                if(balance_factor(T->left)>=0)
                    T=LL(T);  /*this is the case of a double left rotation*/
                else
                    T=LR(T); /*this is the case of a left rotation and then a right rotation*/
			}
        }
        else
            if(x<T->data)
            {
				/*If x is less than the data present in the node T, we again call the delete function and send the left
			    child of node T till the node to be deleted is found*/
                T->left=delete_node(T->left,x);
                if(balance_factor(T)==-2)  /*Case of Right High*/  
                    {
						/*here we have to rebalance the tree if required*/
						if(balance_factor(T->right)<=0)
							T=RR(T); /*this is the case of a double right rotation*/
						else
							T=RL(T); /*this is the case of a right rotation and then a left rotation*/
					}
            }
            else
            {
                /*the node containing the required data to be deleted is found*/
                if(T->right!=NULL)
                {    
					/*we delete the inorder succesor of the node, i.e. we swap the data fields of the given node
					 and its inorder successor*/
                    p=T->right;
                    while(p->left!= NULL)
                        p=p->left;
                    T->data=p->data;
                    T->right=delete_node(T->right,p->data);
                    if(balance_factor(T)==2) /*we rebalance the tree while winding windup (here it is the case of left high*/
                        {
							if(balance_factor(T->left)>=0)
								T=LL(T);
							else
								T=LR(T);
						}
                }
                else
                    return(T->left); /*If the right subtree is absent then the left child is the inorder successor*/ 
            }
    T->height=height_tree(T); 
    return(T);
}
 
int height_tree(struct node *T) /*This function calculates the height of the tree given a node T*/
{
    int lh,rh;
    if(T==NULL)
        return(0);
    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->height;
    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->height;
    /*lh stores the number of nodes present in the left subtree of the node T and rh stores the number of nodes present 
     in the right subtree. The greater of the two is the height of the tree */
    if(lh>rh)
        return(lh);
    return(rh);
}
 
struct node * rotateright(struct node *x) /*this function right rotates the tree for a given node x*/
{
    struct node *y;
    /*necessary swapping actions are taken for the rotation*/
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->height=height_tree(x);
    y->height=height_tree(y);
    /*y becomes the new node which is returned after the rotation is done*/
    return(y);
}
 
struct node * rotateleft(struct node *x) /*this function left rotates the tree for a given node x*/
{
    struct node *y;
    /*necessary swapping actions are taken for the rotation*/
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->height=height_tree(x);
    y->height=height_tree(y);
    /*y becomes the new node which is returned after the rotation is done*/
    return(y);
}
 
struct node * RR(struct node *T)
{
	/*here two right rotations are achieved by only calling the rotate right function once*/
    T=rotateleft(T);
    return(T);
}
 
struct node * LL(struct node *T)
{
	/*here two left rotations are achieved by only calling the rotate left function once*/
    T=rotateright(T);
    return(T);
}
 
struct node * LR(struct node *T)
{
	/*here first a left rotation and then a right rotation needs to be done. first we apply rotate left function on 
	 the left child of T and then the rotate right function on T itself*/
    T->left=rotateleft(T->left);
    T=rotateright(T);
    return(T);
}
 
struct node * RL(struct node *T)
{
	/*here first a right rotation and then a left rotation needs to be done. first we apply rotate right function on 
	 the right child of T and then the rotate left function on T itself*/
    T->right=rotateright(T->right);
    T=rotateleft(T);
    return(T);
}
 
int balance_factor(struct node *T)
{
	/*the formula for balance factor=height of left subtree - height of right subtree*/
    int lh,rh;
    if(T==NULL)
        return(0); 
    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->height;
    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->height;
     /*after calculatig the height for the left subtree and right subtree of T, we find the difference of 
      the same to calculate the balance factor=lh-rh*/
    return(lh-rh);
}
 
int main()
{
    struct node *root=NULL;
    int x,n,i,op;
    do
    {
        printf("\n1)Create:");
        printf("\n2)Insert:");
        printf("\n3)Delete:");
        printf("\n4)Print:");
        printf("\n5)Quit:");
        printf("\n\nEnter Your Choice:");
        scanf("%d",&op);
        switch(op)
        {
            case 1: printf("\nEnter no. of elements:");
                    scanf("%d",&n);
                    printf("\nEnter tree data:");
                    root=NULL;
                    for(i=0;i<n;i++)
                    {
                        scanf("%d",&x);
                        root=insert_node(root,x);
                    }
                    break;
            case 2: printf("\nEnter a data:");
                    scanf("%d",&x);
                    root=insert_node(root,x);
                    break;
            case 3: printf("\nEnter a data:");
                    scanf("%d",&x);
                    root=delete_node(root,x);
                    break;
            case 4: 
                    print2D(root);
                    break;            
        }
    }while(op!=5);
    return 1;
}

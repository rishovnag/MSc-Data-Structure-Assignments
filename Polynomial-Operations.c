/*Implementation of Polynomial operations using Linked Lists*/
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int coefficient;
	int exponent;
	struct node *next;
};

struct node *start[6];

void disp(struct node *temp)
{
	if(temp->coefficient!=0) /*first we print the first term of the polynomial to avoid any sign in the beginning*/
	{
		if(temp->exponent==0)
			printf("\n%d ",temp->coefficient);
		else
			printf("\n%d X^%d ",temp->coefficient,temp->exponent);
	}
	temp=temp->next;
	while(temp!=NULL) /*this loop prints the rest of the polynomial*/
	{
		if(temp->coefficient!=0) /*if the coefficient term is zero then only we print the terms*/
		{
			if(temp->coefficient<0) /*if coefficient is less than zero we do not have to print the negative sign, which we have to do for 
			                  positive values*/
			{
				if(temp->exponent==0) /*if exponent is equal to zero only the coefficient is printed*/
					printf("%d ",temp->coefficient);
				else
					printf("%d X^%d ",temp->coefficient,temp->exponent); /*here the coefficients along with the exponents are printed*/
			}
			else if(temp->coefficient>0) /*if coefficient is greater than zero we do have to print the positive sign ahead of every coefficient*/
			{
				if(temp->exponent==0) /*if exponent is equal to zero only the coeffiient is printed along with the preceeding plus sign*/
					printf("+%d ",temp->coefficient);
				else
					printf("+%d X^%d ",temp->coefficient,temp->exponent); /*here the coefficients along with the exponents are printed along
															 with the preceeding plus sign*/
			}
		}       
		temp=temp->next;
	}
}

void add()
{
	int p,q;
	struct node *temp,*temp1,*temp2,*ptr;
	temp1=(struct node *)malloc(sizeof(struct node));
	temp2=(struct node *)malloc(sizeof(struct node));
	/*temp1 stores the head node for the first polynomial while temp2 stores 
	 the head node for the second polynomial and the head node of the resultant 
	 polynomial is stored in start[2]*/
	temp1=start[0];
	temp2=start[1];
	while(temp1!=NULL || temp2!=NULL)
	{
		/*temp is a temporary node which is used for manipulation purpose*/
	    temp=(struct node *)malloc(sizeof(struct node));
		ptr=start[2];
		if(temp1!=NULL && temp2!=NULL)
		{
			/*p and q stores the exponents of the nodes of the first and second polynomials respectively*/
			p=temp1->exponent;
			q=temp2->exponent;
			if(p>q)
			{
				/*here the final polynomial stores the node of the first polynomial as the
				 exponent field of p is greater than that of q*/
				temp->coefficient=temp1->coefficient;
				temp->exponent=temp1->exponent;
				temp->next=NULL;
				temp1=temp1->next;
			}
			else if(p<q)
			{
				/*here the final polynomial stores the node of the second polynomial as the
				 exponent field of p is less than that of q*/
				temp->coefficient=temp2->coefficient;
				temp->exponent=temp2->exponent;
				temp->next=NULL;
				temp2=temp2->next;
			}
			else if(p==q)
			{
				/*here the coefficients of the two nodes of both the polynomials are added
				 as the exponents for both the nodes are same*/
				temp->coefficient=temp2->coefficient+temp1->coefficient;
				temp->exponent=temp2->exponent;
				temp->next=NULL;
				temp2=temp2->next;
				temp1=temp1->next;
			}
			/*the value of temp which stores the final resultant node after a given iteration
			 is concatenated to the final list of polynomial */
			if(start[2]==NULL)
			{
				start[2]=temp; /*this case occurs when the first node is entered into the finalpolynomial*/
			}
			else
			{
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;
			}
		}
		else if(temp1!=NULL)
		{
			/*entry into the final list is made when the second polynomial is exhausted but
			 elements of from the first polynomial are still left*/
			while(temp1!=NULL)
			{
				ptr=start[2];
				temp=temp1;
				temp1=temp1->next;
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;
			}
		}
		else if(temp2!=NULL)
		{
			/*entry into the final list is made when the first polynomial is exhausted but
			 elements of from the second polynomial are still left*/
			while(temp2!=NULL)
			{
				temp=temp2;
				temp2=temp2->next;
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;
			}
		}
	}
}

void sub()
{
	int p,q,j=-1;
	struct node *temp,*temp1,*temp2,*ptr;
	temp2=(struct node *)malloc(sizeof(struct node));
	temp1=(struct node *)malloc(sizeof(struct node));
	/*temp1 stores the head node for the first polynomial while temp2 stores 
	 the head node for the second polynomial and the head node of the resultant 
	 polynomial is stored in start[3]*/
	temp1=start[0];
	temp2=start[1];
	while(temp1!=NULL || temp2!=NULL)
	{
		/*temp is a temporary node which is used for manipulation purpose*/
	    temp=(struct node *)malloc(sizeof(struct node));
		ptr=start[3];
		if(temp1!=NULL && temp2!=NULL)
		{
			/*p and q stores the exponents of the nodes of the first and second polynomials respectively*/
			p=temp1->exponent;
			q=temp2->exponent;
			if(p>q)
			{
				/*here the final polynomial stores the node of the first polynomial as the
				 exponent field of p is greater than that of q*/
				temp->coefficient=temp1->coefficient;
				temp->exponent=temp1->exponent;
				temp->next=NULL;
				temp1=temp1->next;
			}
			else if(p<q)
			{
				/*here the final polynomial stores the node of the second polynomial as the
				 exponent field of p is less than that of q*/
				temp->coefficient=(temp2->coefficient)*j; /*j helps us to keep the negative sign for the resultant polynomial*/
				temp->exponent=temp2->exponent;
				temp->next=NULL;
				temp2=temp2->next;
			}
			else if(p==q)
			{
				/*here the coefficients of the two nodes of both the polynomials are subtracted
				 as the exponents for both the nodes are same*/
				temp->coefficient=temp2->coefficient-temp1->coefficient;
				temp->exponent=temp2->exponent;
				temp->next=NULL;
				temp2=temp2->next;
				temp1=temp1->next;
			}
			/*the value of temp which stores the final resultant node after a given iteration
			 is concatenated to the final list of polynomial */
			if(start[3]==NULL)
			{
				start[3]=temp; /*this case occurs when the first node is entered into the finalpolynomial*/
			}
			else
			{
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;
			}
		}
		else if(temp1!=NULL)
		{
			/*entry into the final list is made when the second polynomial is exhausted but
			 elements of from the first polynomial are still left*/
			while(temp1!=NULL)
			{
				ptr=start[3];
				temp=temp1;
				temp1=temp1->next;
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;
			}
		}
		else if(temp2!=NULL)
		{
			/*entry into the final list is made when the first polynomial is exhausted but
			 elements of from the second polynomial are still left*/
			while(temp2!=NULL)
			{
				temp=temp2;
				temp->coefficient=j*(temp->coefficient);
				ptr=start[3];
				temp2=temp2->next;
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=temp;
			}
		}
	}
}

void mul()
{
	int p=0;
	struct node *temp,*temp1,*temp2,*temp11,*temp21;
	/*temp1 stores the head node for the first polynomial while temp2 stores 
	 the head node for the second polynomial and the head node of the resultant 
	 polynomial is stored in start[4]*/
	temp1=start[0];
	while(temp1!=NULL)
	{
	    temp2=start[1];
	    while(temp2!=NULL) /*With every term of the first polynomial every term of the second polynomial is multiplied*/
	    {
			/*temp, temp11 and temp21 are temporary nodes which are used for manipulation purpose*/
			temp=(struct node *)malloc(sizeof(struct node));
			temp->coefficient=temp1->coefficient*temp2->coefficient; /*coefficients are multiplied*/
			temp->exponent=temp1->exponent+temp2->exponent; /*exponents are added*/
			temp->next=NULL;
			temp2=temp2->next;
			/*here we implement the logic where the polynomial is stored in a sorted order, i.e the node with the highest exponent value is stored 
			 at the beginning and corresponding nodes follow. accordingly the value of the head node changes*/
			if(start[4]==NULL)
			{
				/*the first term of the resultant polynomial is stored*/
				start[4]=temp;
			}
			else
			{
				temp11=start[4]; /*temp11 stores the first node of the resultant polynomial*/
				p=0;
				while(temp11!=NULL && ((temp11->exponent)>(temp->exponent)))
				{
					/*comparing the exponents in the final polynomial, this is used to place the exponent is decreasing order*/
					p++;
					temp21=temp11;
					temp11=temp11->next;
				}
				if(temp11==NULL)
				{
					/*this case is used only to avoid null point exception as in some compilers the null comparison cannot me made*/
					temp21->next=temp;
				}
				else
					if(temp->exponent==temp11->exponent)
					{
						/*case if we have two nodes with same exponents*/
						temp11->coefficient=temp11->coefficient+temp->coefficient;
					}
				else
				{			
					if(p==0)
					{
						/*this case occurs when incoming node has highest exponent value*/
						temp->next=start[4];
						start[4]=temp;
					}	
					else
					{
						/*here we go to the next node for p=0*/
						temp21->next=temp; 
						temp->next=temp11;
					}
				}
			}
	    }
		temp1=temp1->next;
	}
}

void diff()
{
	struct node *temp,*ptr,*temp1;
	int ch;
	/*a choice is asked from the user that which polynomial he wants to differentiate*/
	do
		{
			printf("\nWhich polynomial do you want to differentiate: 1 or 2	");
			scanf("%d",&ch);
			if(ch==1)
				temp1=start[0];
			else if(ch==2)
				temp1=start[1];
			else 
				printf("\nWrong input.Try Again!!!!");
		}while(ch>2 || ch<=0);
	/*the head node of the polynomial which the user wants to diiferentiate is stored in temp1*/
	while(temp1!=NULL)
	{
		/*the normal process of differentiation is followed where x^n yields n*x^(n-1)*/
		temp=(struct node *)malloc(sizeof(struct node));
		temp->coefficient=temp1->coefficient*temp1->exponent;
		temp->exponent=(temp1->exponent)-1;
		temp->next=NULL;
		temp1=temp1->next;
		if(start[5]==NULL)
		{
			/*the head node of the resultant polynomial is stored in start[5]*/
			start[5]=temp;
		}
		else
		{
			/*we continue storing rest of the polynomial if the head node is full*/
			ptr=start[5];
			while(ptr->next!=NULL)
			{
				ptr=ptr->next;
			}
			ptr->next=temp;
		}
	}
}

void input()
{
	int i,ch,f;
	struct node *temp,*temp1,*temp2;
	/*temp1 stores the input for the first polynomial and temp2 stores the input for the second polynomial while temp is a temporary node*/
	for(i=0;i<2;i++)
	{
		ch=0;
		f=0;
		printf("\nPlease enter the polynomial %d: ",(i+1));
		while(ch!=-1)
		{
			temp=(struct node *)malloc(sizeof(struct node));
			/*the coefficient and exponents are asked to enter for each term of polynomial (i+1)*/
			printf("\nEnter the co-efficient of the polynomial : ");
			scanf("%d",&f);
			temp->coefficient=f;
			printf("\nEnter the exponent : ");
			scanf("%d",&f);
			temp->exponent=f;
			temp->next=NULL;
			if(temp->coefficient==0)
			{
				printf("  ");
			}
			else
			{
				if(start[i]==NULL)
				{
					/*storing the starting node of a polynomial*/
					start[i]=temp;
				}
				else
				{
					/*here we implement the logic where the polynomial is stoed in a sorted order, i.e the node with the highest exponent value is stored 
					 at the beginning and corresponding nodes follow. accordingly the value of the head node changes*/
					temp1=start[i];
					while(temp1!=NULL && ((temp1->exponent)>(temp->exponent)))
					{
						temp2=temp1;
						temp1=temp1->next;
					}
					temp->next=temp1;
					if(temp1==start[i])
						start[i]=temp;
					else
						temp2->next=temp;
				}
				printf("\nEnter -1 to exit : ");
				scanf("%d",&ch);
			}
		}
	}
}

int main()
{
	int i,ch;
	for(i=0;i<6;i++)
	{
		start[i]=(struct node *)malloc(sizeof(struct node));
		start[i]=NULL;
	}
	input();
	disp(start[0]);
	disp(start[1]);
	i=1;
	while(i==1)
	{
		printf("\nPlease enter your choice :\nPress 1 for ADDITION\nPress 2 for SUBTRACTION\nPress 3 for MULTIPLICATION\nPress 4 for DIFFERENCIATION\n");
		scanf("%d" ,&ch);
		switch(ch)
		{	
			case 1:add();
				printf("\nSUM:\n");
				disp(start[2]);
				break;
			case 2:sub();
				printf("\nSUBTRACTION:\n");
				disp(start[3]);
				break;
			case 3:mul();
				printf("\nMULTIPLICATION:");
				disp(start[4]);
				break;
			case 4:diff();
				printf("\nDIFFERENTIATION:");
				disp(start[5]);
				start[5]=NULL;
				break;
			default:printf("\nWrong Input");
		}
		printf("\nPlease enter 1 to continue\t");  
		scanf("%d",&i);
	}
	return 1;
}

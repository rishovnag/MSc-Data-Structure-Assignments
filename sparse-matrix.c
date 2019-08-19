/*Implementation of Sparse Matrix*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/*we define the structure of the sparse matrix*/
struct sparse
{
    int I;
    int J;
    double val;
};

struct sparse* accept();      /*accepts the non-zero field coordinates and non-zero values*/
struct sparse* transpose(struct sparse *);       /*finds the transpose of a the sparse matrix */
void display(struct sparse *);          /*displays the matrices */
struct sparse* sorting(struct sparse *);        /*sorts the matrix*/

int main()
{
	struct sparse *matrix,*transposed_matrix;
	matrix=accept();        /*here we accept the original sparse matrix values*/
    transposed_matrix=transpose(matrix);       /* we find the transpose of the original matrix */
    printf("\n The Original Matrix : \n");
    display(matrix);
    printf("\n The Transposed Matrix before sorting : \n");
    display(transposed_matrix);
    transposed_matrix=sorting(transposed_matrix);         /*sorting the transposed matrix*/
    printf("\n The Transposed Matrix after sorting :  \n");
    display(transposed_matrix);
    return 0;
}

struct sparse* accept()
{
    struct sparse * matrix;
    int row,column,number_of_values,i;
    printf("\n Enter the number of rows in the sparse matrix : ");
    scanf("%d",&row);
    printf("\n Enter the number of columns in the sparse matrix : ");
    scanf("%d",&column);
    printf("\n Enter the number of non-zero values in the sparse matrix : ");
    scanf("%d",&number_of_values);
    /*we are checking whether the number of non-zero terms is valid or not*/
    while(1)
    {
        if(number_of_values<0)
        {
			printf("\n Invalid Value - Enter Again : ");
			scanf("%d",&number_of_values);
        }
        else if(number_of_values>=((row*column)/3))
		{		
			printf("\n Invalid Value - Enter Again : ");
			scanf("%d",&number_of_values);
		}
		else
			break;
    }
    matrix=(struct sparse *)(calloc((number_of_values+1),sizeof(struct sparse)));
    matrix[0].I=row;
    matrix[0].J=column;
    matrix[0].val=number_of_values;
    for(i=1;i<=number_of_values;i++)
    {
        printf("\n Enter the non-zero element %d, i.e entry for row %d in the new matrix",i,i);
        printf(" \n Enter the row number of the non-zero value : ");
        scanf("%d",&matrix[i].I);
        printf(" \n Enter the column number of the non-zero value : ");
        scanf("%d",&matrix[i].J);
        /*checking whether the coordinates being provided are valid or not */
        while(1)
     	{
        	if((matrix[i].I>=row  || matrix[i].I<0) && (matrix[i].J>=column  || matrix[i].J<0))
        	   {
        		    printf("\n Invalid Value - Enter Again : ");
        		    printf(" \n Enter the row number of the non-zero value : ");
					scanf("%d",&matrix[i].I);
					printf(" \n Enter the column number of the non-zero value : ");
					scanf("%d",&matrix[i].J);
        	   }
        	else if(matrix[i].I>=row || matrix[i].I<0)
            	   {
						printf("\n Row Field Invalid - Enter Again : ");
						printf(" \n Enter the row number of the non-zero value : ");
						scanf("%d",&matrix[i].I);
						printf(" \n Enter the column number of the non-zero value : ");
						scanf("%d",&matrix[i].J);
            	   }
        	else if(matrix[i].J>=column  || matrix[i].J<0)
            	   {
						printf(" \n Enter the row number of the non-zero value : ");
						scanf("%d",&matrix[i].I);
						printf(" \n Enter the column number of the non-zero value : ");
						scanf("%d",&matrix[i].J);
            	   }
       		else
			{
				printf(" \n Enter the non-zero value : ");
        		scanf("%lf",&matrix[i].val);
        		break;
		    } 
		}
	}
	return matrix;
}

/* function to find the transpose of the original matrix*/
struct sparse* transpose(struct sparse *matrix)
{
    struct sparse *transposed_matrix=(struct sparse *)(calloc(((int)(matrix[0].val)+1),sizeof(struct sparse)));
    int i;
    transposed_matrix[0].val=matrix[0].val;
    for(i=0;i<=matrix[0].val;i++)
    {
        transposed_matrix[i].J=matrix[i].I; /* storing the row value of the original matrix into the column field of the transpose matrix*/
        transposed_matrix[i].I=matrix[i].J; /* storing the column value of the original matrix into the row field of the transpose matrix*/
        transposed_matrix[i].val=matrix[i].val;
    }
    return transposed_matrix; /* returning the transposed matrix*/
}

/* function to display the matrices */
void display(struct sparse *matrix)
{
        int i;
        printf("\nRows\tColumns\tValues");
        for(i=0;i<=matrix[0].val;i++)
        {
            printf("\n%d\t%d\t%lf",matrix[i].I,matrix[i].J,matrix[i].val);
        }
}

/*function to sort the transposed matrix*/
struct sparse* sorting(struct sparse *transposed_matrix)
{
     int temp,i,j;
     double tmp;
     for(i=1;i<transposed_matrix[0].val;i++)
	{
	  for(j=i+1;j<=transposed_matrix[0].val;j++)
          {
			/*Here the sorting takes place while giving the row number 
			 priority over the column number, i.e the I values are only 
			 compared and not the J values such that an element stored in 
			 row 2 and column 3 gets preference over an element stored in
			 row 4 and column 5. If the row numbers are same, the columns
			 are only sorted.*/
            if(transposed_matrix[i].I>transposed_matrix[j].I)
			{ /*If the row numbers are unequal*/
				temp=transposed_matrix[i].I;
                transposed_matrix[i].I=transposed_matrix[j].I;
				transposed_matrix[j].I=temp; /*Swapping row values*/
				temp=transposed_matrix[i].J;
                transposed_matrix[i].J=transposed_matrix[j].J;
                transposed_matrix[j].J=temp; /*Swapping column values*/
				tmp=transposed_matrix[i].val;
                transposed_matrix[i].val=transposed_matrix[j].val;
                transposed_matrix[j].val=tmp; /*Swapping the data values*/
            }
            else if(transposed_matrix[i].I==transposed_matrix[j].I)
			{ /*If the row numbers are equal*/	
				if(transposed_matrix[i].J>transposed_matrix[j].J)
				{ /*Column values are compared*/
					temp=transposed_matrix[i].J;
					transposed_matrix[i].J=transposed_matrix[j].J;
					transposed_matrix[j].J=temp;/*Swapping column values*/
					tmp=transposed_matrix[i].val;
					transposed_matrix[i].val=transposed_matrix[j].val;
					transposed_matrix[j].val=tmp; /*Swapping the data values*/
				}	
			}
        }
    }
    return transposed_matrix;
}

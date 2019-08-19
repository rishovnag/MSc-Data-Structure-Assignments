/*Implementation of Heap Sort*/
#include<stdio.h>
#include<stdlib.h>
void heapsort(int *,int); /*this function sorts the given array*/
void adjustheap(int *,int); /*this function helps in creating the max heap*/
int main()
{
	int a[100],n,element,i,ch;
	/*elements are entered into the array by the user*/
	do
	{
		printf("\nEnter element %d into the array ",n+1);
		scanf("%d",&element);
		a[n]=element;
		n++;
		printf("\nDo you want to continue entering into the list? If Yes Press 1\t");
		scanf("%d",&ch);
	}while(ch==1);
	/*the array is printed before sorting*/
	printf("\nThe elements before sorting : ");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	heapsort(a,n); /*the heapsort function is called to sort the array*/
	/*the sorted list is peinted*/
	printf("\nThe elements after sorting : ");
		for(i=0;i<n;i++)
			printf("%d ",a[i]);
	printf("\n");
	return 0;
}

void heapsort(int *a,int h)
{	
	/*this function takes the array and the number of elements of the array as input*/
	int i,parent,child,temp;
	/*here we start creating the Max Heap*/
	/*it is to be noted that for array representation of trees if a node is placed at position i
	 its child will be placed at position 2*i+1*/
	for(i=1;i<h;i++)					
	{	parent=(i-1)/2;
		child=i;
		while(parent>=0)
		{	
			if(a[parent]<a[child])
			{	
				/*the fundamental condition of a max heap is being violated*/
				temp=a[child];
				a[child]=a[parent];
				a[parent]=temp;
				child=parent;
				parent=(child-1)/2;
			}
			else
				break;
		}
	}
	/*After the previous segment the max heap is created and we have the largest element at the top of the heap*/
	printf("\nThe Created Max Heap : "); 
	/*the created max heap is printed*/
	for(i=0;i<h;i++)
		printf("%d ",a[i]);
	/*after that max heap is created the largest element is sent to its appropriate position and then the 
	 heapify algorithm is applied to the remaining elements to get their appropriate positions in the array*/
	for(i=h-1;i>0;i--)
	{	temp=a[0];
		a[0]=a[i];
		a[i]=temp;
		adjustheap(a,i-1);
	}
}

void adjustheap(int *a,int h)			
{	
	/*this function adjusting the max heap applying the heapify algorithm. it takes the array and 
	 number of elements in the array as input*/
	int child,parent,temp;
	/*it is yo be noted that for array representation of trees if a node is placed at position i
	 its child will be placed at position 2*i+1*/
	parent=0;
	child=2*parent+1;
	while(child<=h)
	{	
		/*the job of this loop is to find the largest element in the array and bring it to the top*/
		if((child+1)<=h) /*here we check for the greatest child*/
		{	
			if(a[child]<a[child+1])
				child++;
		}
		if(a[parent]<a[child]) 
		{	
			/*we swap if the root node is smaller than its child*/
			temp=a[parent];
			a[parent]=a[child];
			a[child]=temp;
			parent=child;
			child=2*parent+1;
		}
		else
			break;
	}
}

/*Assignment 10 : Problem of incrementing n digit binary integers and compute amortized cost of the algorithm in terms of n*/

#include<stdio.h>
#include<math.h>

double log(double x); /*this function computes the logarithm of a number x to the base 10*/
double pow(double x, double y); /*this function calculates the value x^y*/

int count(unsigned long int x)
{	/*this function calculates the number of ones in the binary representation of an integer*/
	int r=0;
	while(x>0)
	{	if((x%2)==1)
			r++;
		x/=2;
	}
	return r;
}

int main()
{	
	/*n:- number of bits
	  t:- actual cost foreach operation, i.e number of bits which need to be altered
	  c:- number of 1's present in the binary representation of a given integer
	  a:- amortized cost for every operation */
	int n,t,c1=0,c2,a,j;
	unsigned long int i,l,r,s; /*these elements store decimal equivalent for the binary digits generated
								i.e if n=4 it may store values from 0 to 15*/
	/*we ask the number of bits as inputs*/
	printf("\nEnter the no. of bits : ");
	scanf("%d",&n);
	/*we calculate the largest integer for input n */
	l=pow(2,n)-1;
	/*the first element is 0 and hence we print n number of zeroes at the beginning*/
	for(j=1;j<=n;j++)
		printf("0");
	printf("\t\t0\n");
	for(i=1;i<=l;i++)
	{	
		s=i;
		r=s^(s-1); /*this stores bitwise xor of one number and its previous number*/
		t=count(r); /*counts number of ones in r thus computing the bit changes from one number to the next*/
		c2=count(s); /*counts number of ones in the present number*/
		j=log(s)/log(2); /*this calculates number of bits to represent s*/
		for(r=j+1;r<n;r++)
			printf("0"); /*this prints the extra zeroes to the left number bits to represent s is less than that of n*/
		r=0;
		while(j>=0)
		{	
			/*this loop starts from j and continues till r becomes equal to 0*/
			if((r+pow(2,j))<=s)
			{	
				/*here the main logic is that if number of bits increase a one will be printed.
				 here r is first assigned to zero and pow(2,j) is the maximum integer number which the 
				 j bits can represent. if the sum of this two is less than or equal to s we print 1*/
				printf("1");
				/*now r is incremented by the max integer number obtained from j*/
				r=r+pow(2,j);
				if(r==s)
				{	
					/*as r becomes equals to s j is decremented to compute the lower bit segment*/
					j--;	
					break;
				}
			}
			else
				printf("0");
			/*j is decremented to compute the lower bit segment*/
			j--;
		}
		while(j>=0)			
		{	
			/*this condition is checked for consecutive 0s at the end, */
			printf("0");
			j--;
		}
		/*the amortized cost is calculated*/
		a=t+c2-c1;
		/*c1 takes the value for c2 as it will be required in the next iteration*/
		c1=c2;
		printf("\t%d\t%d\t%d\n",t,c2,a);
	}
			
	return 0;
}

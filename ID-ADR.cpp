#include<stdio.h>


int i,j, difference;
int SIR=-15;

int main (void)
{
	
	// The matrix for  
	int SIR_Matrix [6][6] = { 
	 {1,-8,-9,-9,-9,-9},
	 {-11,1,-11,-12,-13,-13}, 
	 {-15,-13,1,-13,-14,-15}, 
	 {-19,-18,-17,1,-17,-18},
	 {-22,-22,-21,-20,1,-20}, 
	 {-25,-25,-25,-24,-23,1}};

	for (i =0; i<=5 ; i++)
	{
		for (j=0; j<=5; j++)
		{
			difference = SIR-SIR_Matrix[i][j];
			
			printf("%d ",difference);
			if(j==5)
			printf("\n");
		}
	}

	return 0;
}

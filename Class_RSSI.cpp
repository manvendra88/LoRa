#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//node1

int x_1[10],y_1[10],buildings1,ptx1=0;

//gateway1
int g1_x,g1_y;	


float RandomBetween(float smallNumber, float bigNumber)
{
    float diff = bigNumber - smallNumber;
    return (((float) rand() / RAND_MAX) * diff) + smallNumber;
}

float distx[10],disty[10],dist[10];
	float lambda=(3.8*10E8)/(868*10E6);
	float d_min=100;
	float n=2.7; //pathloss-exponent
	float Lc_prop1[10];
	float RSSI[10];
			
int main (void)
{
	srand((unsigned int)time(NULL));
	/**************************************Node1*************************************************/
	//&&&&printf("Enter the node environment and PHY param x_1 :: y_1 :: buildings1 :: ptx1\n");
	//&&&&scanf("%d %d %d %d",&x_1,&y_1,&buildings1,&ptx1);
	

	
	for(int m=0; m<=9;m++)
	{
	g1_x = 0;
	g1_y = 0;	
	x_1[m] = RandomBetween(-500,500);
	y_1[m] = RandomBetween(-500,500);
	x_1[1]=500;
	y_1[1]=500;
	distx[m]=pow((g1_x-x_1[m]),2);
	disty[m] = pow((g1_y-y_1[m]),2);
	
	dist[m] = sqrt(distx[m]+disty[m]);
	//dist[1]=
	printf("Distance %d:: %0.0f  ",m,dist[m]);
	

	
	Lc_prop1[m]= 20*log10(4*3.14*d_min/lambda) + 10*n*log10(dist[m]/d_min);
	RSSI[m]=ptx1-Lc_prop1[m];
	printf("RSSI %d :: %0.0f\n",m,RSSI[m]);
	
	}

	
	
	
}

float SIRThreshold(int SF2, int SF1)
{
	
switch (SF2)
{
	float SIR_Threshold;
	case 7:
		if (SF1==7)
		{
		SIR_Threshold=1;
		return SIR_Threshold;
		break;
		}
		else if (SF1==8)
		{
		SIR_Threshold=-8;
		return SIR_Threshold;
		break;
		}
		else if (SF1==9)
		{
		SIR_Threshold=-9;
		return SIR_Threshold;
		break;
		}
		else if (SF1==10)
		{
		SIR_Threshold=-9;
		return SIR_Threshold;
		break;
		}
		else if (SF1==11)
		{
		SIR_Threshold=-9;
		return SIR_Threshold;
		break;
		}
		else if (SF1==12)
		{
		SIR_Threshold=-9;
		return SIR_Threshold;
		break;
		}
	
	case 8:
		if (SF1==7)
		{
		SIR_Threshold=-11;
		return SIR_Threshold;
		break;
		}
		else if (SF1==8)
		{
		SIR_Threshold=1;
		return SIR_Threshold;
		break;
		}
		else if (SF1==9)
		{
		SIR_Threshold=-11;
		return SIR_Threshold;
		break;
		}
		else if (SF1==10)
		{
		SIR_Threshold=-12;
		return SIR_Threshold;
		break;
		}
		else if (SF1==11)
		{
		SIR_Threshold=-13;
		return SIR_Threshold;
		break;
		}
		else if (SF1==12)
		{
		SIR_Threshold=-13;
		return SIR_Threshold;
		break;
		}
	
	case 9:
		if (SF1==7)
		{
		SIR_Threshold=-15;
		return SIR_Threshold;
		break;
		}
		else if (SF1==8)
		{
		SIR_Threshold=-13;
		return SIR_Threshold;
		break;
		}
		else if (SF1==9)
		{
		SIR_Threshold=1;
		return SIR_Threshold;
		break;
		}
		else if (SF1==10)
		{
		SIR_Threshold=-13;
		return SIR_Threshold;
		break;
		}
		else if (SF1==11)
		{
		SIR_Threshold=-14;
		return SIR_Threshold;
		break;
		}
		else if (SF1==12)
		{
		SIR_Threshold=-15;
		return SIR_Threshold;
		break;
		}
		
	case 10:
		if (SF1==7)
		{
		SIR_Threshold=-19;
		return SIR_Threshold;
		break;
		}
		else if (SF1==8)
		{
		SIR_Threshold=-18;
		return SIR_Threshold;
		break;
		}
		else if (SF1==9)
		{
		SIR_Threshold=-17;
		return SIR_Threshold;
		break;
		}
		else if (SF1==10)
		{
		SIR_Threshold=1;
		return SIR_Threshold;
		break;
		}
		else if (SF1==11)
		{
		SIR_Threshold=-17;
		return SIR_Threshold;
		break;
		}
		else if (SF1==12)
		{
		SIR_Threshold=-20;
		return SIR_Threshold;
		break;
		}	
	
	case 11:
		if (SF1==7)
		{
		SIR_Threshold=-22;
		return SIR_Threshold;
		break;
		}
		else if (SF1==8)
		{
		SIR_Threshold=-22;
		return SIR_Threshold;
		break;
		}
		else if (SF1==9)
		{
		SIR_Threshold=-21;
		return SIR_Threshold;
		break;
		}
		else if (SF1==10)
		{
		SIR_Threshold=-20;
		return SIR_Threshold;
		break;
		}
		else if (SF1==11)
		{
		SIR_Threshold=1;
		return SIR_Threshold;
		break;
		}
		else if (SF1==12)
		{
		SIR_Threshold=-20;
		return SIR_Threshold;
		break;
		}	
		
	case 12:
		if (SF1==7)
		{
		SIR_Threshold=-25;
		return SIR_Threshold;
		break;
		}
		else if (SF1==8)
		{
		SIR_Threshold=-25;
		return SIR_Threshold;
		break;
		}
		else if (SF1==9)
		{
		SIR_Threshold=-25;
		return SIR_Threshold;
		break;
		}
		else if (SF1==10)
		{
		SIR_Threshold=-24;
		return SIR_Threshold;
		break;
		}
		else if (SF1==11)
		{
		SIR_Threshold=-23;
		return SIR_Threshold;
		break;
		}
		else if (SF1==12)
		{
		SIR_Threshold=1;
		return SIR_Threshold;
		break;	
		}	
		
}
}








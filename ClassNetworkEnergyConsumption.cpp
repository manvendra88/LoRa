#include<stdio.h>
#include<math.h>
float EnergyConsumptionADR(int,int,int,int);

int SFi=7,TxPi=2,SFf=10,TxP=4;
int DRi=0,TxPi_index=2,DRf=3,TxPf_index=8;
int NEC;
//As under SIR=-19 dBm environment with interferer as SF8, this is the best configuration

float Columbs[6][10]={
		{754,754.7,823,823.3,857,857.6,1063,1166,1509,2915},
		{1509,1509.4,1646,1646.4,1715,1715.2,2126.8,2332.7,3018,5831},
		{3018,3018.8,3293,3293.2,3430,3430.4,4253,4665,6037,11663},
		{5136,5136.4,5603,5603.3,5836.8,7237.6,7938,10272.2,19845.1},
		{10272,10272.8,11206,11206.7,11673,11673.6,11475.3,15876,20545,39690.2},
		{20545,20545.5,22413,22413.3,23347,23347.2,28950,31752.2,41091,79380.5}};
		
int main ()
{
	float NEC_mJ_Final = EnergyConsumptionADR(DRi,TxPi_index,DRf,TxPf_index);
	printf("%f mJ",NEC_mJ_Final);
	return 0;
}

float EnergyConsumptionADR (int DRi, int TxPi_index, int DRf, int TxPf_index )
{
	int i,j;

	//for(i=DRi;i<=DRf;i++)
	//{
	//	for(j=0;j<=9;j++)
	//		{
	//	printf("Till DR:%d TxP:%d", i, j);
	//	printf("NEC: %d",NEC);
		for(i=DRi;i<=DRf;i++)
		{
			for(j=TxPi_index;j<=TxPf_index;j++)
			{
			//i=	DRi;
			//j= TxPi_index;
			printf("%f ",Columbs[i][j]);
			float done=
			printf("%f ",Columbs[i][j]*3.3*64);
			NEC=NEC+Columbs[i][j]*3.3*64;
			printf(" NEC: %d\n",NEC);	
			if(i==DRf && j==TxPf_index)
			goto label;
			}	
		}
		
label: float NEC_mJ=NEC/pow(10,6);	

return NEC_mJ;		
	
}


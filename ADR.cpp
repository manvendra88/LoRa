#include <stdio.h>
#include <math.h> 

/**********************************Variables********************************/


float array_SNR[99], maximum, SNRMax, requiredSNR;
int  size, c, location = 1,currentSF,currentTxP,index,UsedDR, UsedTxP;
 
 
float SNRMargin, installationMargin;
int NStep;
int DR;
/************************************Functions*************************************/


float maxSNR (float *);
get20SNR ();
getUsedSF () ;
getUsedTxP ();
getInstallationMargin();
float RequiredSNRTable (int);
int  getIdealTXPowerOffsetAndDR (int, int, int);

/*************************************Main*****************************************/

int main()
{
  get20SNR();
  printf("Maximum SNR %f\n",SNRMax=maxSNR(&array_SNR[0]));
  
  getUsedSF();
  printf("%f\n",RequiredSNRTable(currentSF));
  
  getUsedTxP();

  
  getInstallationMargin();
  
  printf("Margin : %f\n",SNRMargin = SNRMax - requiredSNR - installationMargin);
  float Marginby3 = SNRMargin/3;
  printf("Marginby3 = %f\n",Marginby3);
  NStep = round(SNRMargin / 3);
  printf("Current NStep : %d\n",NStep);
  
  
  getIdealTXPowerOffsetAndDR(NStep, UsedDR, index);
  
  
  return 0;
}

/**********************************Function Declarations*********************************/

getIdealTXPowerOffsetAndDR(int NStep, int UsedDR, int UsedTxP)
{
	printf("Before ADR, settings are: NStep: %d | DR: %d (SF=%d) | TxPIndex: %d (TxP=%d)\n", NStep, UsedDR,currentSF, index, currentTxP);
	
	while(NStep!=0)
	{
		if(NStep>0)
		{
		
		if(UsedDR<5)
			{
			UsedDR=UsedDR+1;
			currentSF--;
			NStep--;
			}
			else
			{
			index=index+1;
			currentTxP=currentTxP-3;
			NStep--;
			}
		
		if(index>=6)
		goto label;
		}
		
		else
		{
			if(index>0)
			{
			index=index-1;
			currentTxP=currentTxP+3;
			NStep++;
			 }
			else
			goto label;
		}
	}
	label: printf("After ADR, settings are: NStep: %d | DR: %d (SF=%d) | TxPIndex: %d (TxP=%d)\n", NStep, UsedDR,currentSF, index, currentTxP);
	
}
void get20SNR()
{
  printf("Enter the number of elements in array :");
  scanf("%d", &size);
 
  printf("Enter %d SNRs\n", size);
  
    for (c = 0; c < size; c++)
    scanf("%f", &array_SNR[c]);
  
}
void getUsedSF(void)
{

  printf("Enter the SF in Use : ");
  scanf("%d",&currentSF);
  printf("for which Required SNR is ");
  switch (currentSF)
  {
  	case 7 :
  		UsedDR=5;
  		break;
  	case 8:
  		UsedDR=4;
  		break;
  	case 9:
  		UsedDR=3;
  		break;
  	case 10:
  		UsedDR=2;
  		break;
  	case 11:
  		UsedDR=1;
  		break;
  	case 12:
  		UsedDR=0;
  		break;		    	
  }
}
void getUsedTxP(void)
{
	
  printf("Enter the TxP ");
  scanf("%d",&currentTxP);
  
  switch (currentTxP)
  {
  	case 20:
  	index =0;
  	break;
  	
  	case 14:
  	index=1;
  	break;
  	
  	case 10:
  	index=2;
  	break;
  	
  	case 8:
	index=3;
	break;
	
	case 5:
	index=4;
	break;
	
	case 2:
	index=5;
	break;
	
	case 0:
	index=6;
	break;
  }
  printf("for which the index is %d\n",index);
  
}

void getInstallationMargin(void)
{

  printf("Enter the desired Margin ");
  scanf("%f",&installationMargin);
  
}

 float maxSNR(float *)
 {
 
  maximum = array_SNR[0];
 
  for (c = 1; c < size; c++)
  {
    if (array_SNR[c] > maximum)
    {
       maximum  = array_SNR[c];
       location = c+1;
    }
  }
  
  return maximum;
}

float RequiredSNRTable (int n)
{
switch (n)
{
    case 6: 
    return requiredSNR= -5;
        break;
    case 7: 
    return requiredSNR = -7.5;
    
        break;
    case 8: 
    return requiredSNR = -10;
        break;
    case 9: 
    return requiredSNR = -12.5;
        break;
    case 10: 
    return requiredSNR = -15;
        break;
    case 11: 
    return requiredSNR = -17.5;
        break;
    case 12: 
    return requiredSNR = -20;
        break;   
    default: 
    return requiredSNR = -7.5;
}
}

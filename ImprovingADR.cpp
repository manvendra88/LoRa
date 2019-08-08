#include<stdio.h>
#include<math.h>
//node1
int x_1,y_1,buildings1,ptx1;
float Lc_prop1,Lc_building1;
//gateway1
int g1_x,g1_y;

//node2
int x_2,y_2,buildings2,ptx2;
float Lc_prop2,Lc_building2;
//gateway2
int g2_x,g2_y;

float SIRThreshold(int SF2, int SF1);
int main (void)
{
	/**************************************Node1*************************************************/
	printf("Enter the node environment and PHY param x_1 :: y_1 :: buildings1 :: ptx1\n");
	scanf("%d %d %d %d",&x_1,&y_1,&buildings1,&ptx1);
	
	printf("Please enter the gateway location g1_x :: g1_y\n");
	scanf("%d %d",&g1_x,&g1_y);
	

	
	/** Calculating distance **/
	int b = pow((g1_x-x_1),2);
	int c = pow((g1_y-y_1),2);
	float d1 = sqrt(b+c);
	
	/**Calculating Free-spce Channel Gain**/
	float lambda=(3.8*10E8)/(868*10E6);
	float Lc_prop1=(10*log10((lambda*lambda)/(4*3.14*3.14)))-20*log10(d1);
	printf("Free Space Channel Loss :");
	printf("%f\n",Lc_prop1);
	
	/**Calculating building loss**/
	float alpha=4;
	printf("Penetration loss :");
	Lc_building1=alpha*buildings1;
	printf("%f\n",-Lc_building1);
	
	/**Calculating Received Signal Power**/
	float Prx=ptx1+Lc_prop1-Lc_building1;
	printf("Received Power from node1");
	printf("%0.2f\n",Prx);
	
	
	printf("*********************************************************\n");
	/*****************************************Node2*******************************************/
	printf("Enter the node environment and PHY param x_2 :: y_2 :: buildings2 :: ptx2\n");
	scanf("%d %d %d %d",&x_2,&y_2,&buildings2,&ptx2);
	
	printf("Please enter the gateway location g2_x :: g2_y\n");
	scanf("%d %d",&g2_x,&g2_y);
	
	
	/** Calculating distance **/
	int b2 = pow((g2_x-x_2),2);
	int c2 = pow((g2_y-y_2),2);
	float d2 = sqrt(b2+c2);
	printf("%0.2f\n",d2);
	
	/**Calculating Free-spce Channel Gain**/
	float lambda2=(3.8*10E8)/(868*10E6);
	float Lc_prop2=(10*log10((lambda2*lambda2)/(4*3.14*3.14)))-20*log10(d2);
	printf("Free Space Channel Loss :");
	printf("%f\n",Lc_prop2);
	
	/**Calculating building loss**/
	float alpha2=6;
	printf("Penetration loss :");
	Lc_building2=alpha*buildings2;
	printf("%f\n",-Lc_building2);
	
	/**Calculating Received Signal Power**/
	float Prx2=ptx2+Lc_prop2-Lc_building2;
	printf("Received Power from node1");
	printf("%0.2f\n",Prx2);
	
	/** After programming this far and running the node for the analysis where gateway is at 35,50. Interferer is at 50,50 while ref is at 0,0
	we realize that due to heavy buildings, the signal power of SF10 reaching to the gateway is -60 dbm while it is -50 dBm for the interferer **/
	/** In the real scenario, however the RSSI was recorded out to be -95 dBm for the reference node, while for the interferer, the RSSI was recorded
	out to be -60 dBm. And **/


	/** After assigning the alpha as 6 for node-2 and giving 5 walls as an input, we get S=-68dBm and I=-50 dBm which gives SIR for reference node**/
	printf("Enter the SF for reference and interference node");
	int SFref, SFint;
	
	scanf("%d %d",&SFref,&SFint);

	float SIR=Prx2-Prx;
	printf("SIR for this configuration : %0.2f\n",SIR);
	
	float SIR_Threshold = SIRThreshold(SFref,SFint);
	printf("SIR Threshold : %0.2f\n",SIR_Threshold);
	
	/** This is computed when the two nodes are comm at different channel, we measured signal power when reference node was alone and when 
	interference node was alone, which will also be there when both of them talk together. Thus, we calculated individual RSSIs when they had
	different channel, that gave us the SIR the reference node will face when both of them are together. On this basis, the power prediction
	algorithm is run, how? Let's see **/
	
	if(SIR-SIR_Threshold<0)
	printf("Inter SF Interference Detected, Pow dec ADR needs to run to get SIR>SIR_Threshold!");
	
	/** If we don't dec the power of the interferer node which is happening due to the current ADR, the reference node will start to do its
	own ADR and end up increasing the DR which is power inefficient. **/
	
	/** The following algorithm is checking if the gateway_diversity for the interferer node is > 1. If so, and its current SF>7, then the gateway
	other than the reference node gateway would perform its power ADR so that it is not able to send sufficient power which is acting as an 
	interference to the reference node gateway **/
	 
	/*************************************************Interferer with gateway 2 *****************************************/
	
	/** Assuming that the gateway 2 equidistant from the interferer node as it is from gateway 1 **/
	/**Therefore, the path-loss comes out to be -50 dBm, and SF8 is must in its scenario. My algorithm is saying that it is not mandatory that
	only the maximum one does the ADR, depending upon the packet loss and gw_diveristy, we can change the gateway for the node.**/

	/** By not dec TxP, you are wasting TxP of your interferer node as well as not providing room for the other nodes. It simply does not look,
	if at SF>7, can the node send with a lesser power which thereby gives higher SF to them which makes hard for other nodes. So, a prov of 
	pow decerement for the nodes with higher SF is introduced by us. It helps the reference not increase its TxP when it isn't able to talk.
	With earlier ADR, the node will inc TxP, than for sometime the signal would reach and thus it will have a SINR, thus ADR reduces its
	PHY to the same value again and then again it will face interference and starts to inc TxP. So a ping-pong loop is demolished to save power.**/
	
	
	while(SIR-SIR_Threshold<=0)
	{
	int a=SIR-SIR_Threshold;
	printf("%d\n",a);
	if(ptx1>=0)
	{
	ptx1=ptx1-2;
	SIR=SIR+2;
	}
	else
	{
	ptx2=ptx2+2;
	SIR=SIR+2;
	}
		
	}
	
	printf("Final Configuration after computing the power dec algorithm, gives the output : Ref node ; Interferer node\n");
	printf("SF and Power of Ref Node %d %d\n", SFref, ptx2);
	printf("SF and Power of Int Node %d %d\n",SFint,ptx1);
	
/**********************************************************Done*********************************************************************/
}

float SIRThreshold(int SF2, int SF1)
{
	float SIR_Threshold;
switch (SF2)
{
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








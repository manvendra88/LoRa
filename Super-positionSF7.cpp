//Comparing ID-ADR with others
//On line 66, you need to comment first and see if the perfect two packets arrving at the same time are considered collided or not
//On commenting, you will shift the second node time of arrival by some value which is greater than the preamble time of the first packet
//There, you will see how the CRC of the first packet is affected due to this.


/** YOU ARE BOUND TO USE SOME HIGHER ORDER SF IN THE SIMULATOR PROVE IT & THUS PUT ID-ADR **/

//input : N (number of transmitters) , n (number of packets to send), SF, Channel, RSSI matrix for each tx, Start-timeKO-matrix,
//Preamble+Header timeKO matrix 

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int i,j,k,l; 							//For loop
#define NODE 50
#define NUM 100
#define SF_TEST_REF 7
#define SF_TEST_INT 7

#define RSSI_TEST_REF -70
#define RSSI_TEST_INT -70

int SF[NODE+1];							//Matrix to defining the SFs to each Node //Default Spreading-Factor : https://www.microchip.com/forums/m974487.aspx //Sandeep's library's default is SF7.
float RSSI[NODE+1];			//Will do the total channel coding for this today

int N=NODE; 								//Total number of Nodes
int n=NUM; 								//Total number of packets sent by each node

					

//int CHAN[4]={0,0,0,0};

int collision_counter_interSF[NODE][NUM],collision_counter_intraSF[NODE][NUM],badCRC_counter[NODE][NUM],badCRC_counter_interSF[NODE][NUM],packetrcvd_counter[NODE][NUM];
/*Some Aiding Fucntions */

float SIRThreshold(int SF2, int SF1);		//Function for returning correct SIR_Threshold for two colliding SFs.



float SIR_Threshold;						//to hold the returning value of SIRThreshold function

float ToA[NODE]={0}; 							//For timeKO-on-air. To do : covert it into matrix
float offtime[NODE]={0};						//For timeKO-interval
float Start_time[NODE][NUM]={0};					//timeKO is start timeKO matrix for which [i][j] are i=1,1,2...N and 0<j<N
float ToPH_Mat[NODE][NUM]={0};					//Preamble+Header time
float ToPH3_Mat[NODE][NUM]={0};					//3symbol time

float dutycycle=0.1;				 		//For 1% duty-cycle, 0.01

float fr;

float sum_coll,sum_crc,avg_loop_coll;

int delta=5;								//For randomizing timings. To do: Find a random delay 


float RandomBetween(float smallNumber, float bigNumber)
{
    float diff = bigNumber - smallNumber;
    return (((float) rand() / RAND_MAX) * diff) + smallNumber;
}
int loop=1;
int main(void)
{
srand((unsigned int)time(NULL));


for(i=1;i<=NODE;i++)
{
			
		
		if(i%2==0)
		{
		SF[i]=SF_TEST_INT;
		//RSSI[i]=RSSI_TEST_INT;
		}
		else
		{
		SF[i]=SF_TEST_REF;
		//RSSI[i]=RSSI_TEST_REF ;
		}
		//SF[2]=12;
		if(i<=50)
		RSSI[i]=RandomBetween(0,-92);
		else
		RSSI[i]=RandomBetween(-94,-102);

		
		//&&&&printf("RSSI[%d] : %f\n",i,RSSI[i]);
		
		if(SF[i]==7)
		ToA[i]=0.04122;
		
		else if (SF[i]==8)
		ToA[i]=0.07219;


		else if (SF[i]==9)
		ToA[i]=0.1438;

		
		else if(SF[i]==10)
		ToA[i]=0.28877;

		else if(SF[i]==11)
		ToA[i]=0.57744;

		
		else
		ToA[i]=0.99123;	//

		
		//dutycycle=0.1;
		offtime[i] = (ToA[i]/dutycycle)- ToA[i] ;	

		//offtime[i] = 0.08;
		
		
		if(i!=0)
		//&&&&&printf("Node :%d | ToA :%0.3f | Offtime :%0.3f\n",i,ToA[i],offtime[i]);
	
		for(j=1;j<=NUM;j++)
		{
			if(SF[i]==7)
			ToPH_Mat[i][j]=0.01254;
	
			else if (SF[i]==8)
			ToPH_Mat[i][j]=0.02509;
	
	
			else if (SF[i]==9)
			ToPH_Mat[i][j]=0.05018;
	
			
			else if(SF[i]==10)
			ToPH_Mat[i][j]=0.10035;
	
			
			else if(SF[i]==11)
			ToPH_Mat[i][j]=0.20070;

			else
			ToPH_Mat[i][j]=0.40141;
		}
		
		for(j=1;j<=NUM;j++)
		{
			if(SF[i]==7)
			ToPH3_Mat[i][j]=3*0.00102;
	
			else if (SF[i]==8)
			ToPH3_Mat[i][j]=3*0.00205;
	
	
			else if (SF[i]==9)
			ToPH3_Mat[i][j]=3*0.00410;
	
			
			else if(SF[i]==10)
			ToPH3_Mat[i][j]=3*0.00819;
	
			
			else if(SF[i]==11)
			ToPH3_Mat[i][j]=3*0.01638;

			else
			ToPH3_Mat[i][j]=3*0.03277;
		}
		float rb;
		//srand(time(0)); 

		fr= RandomBetween(0,5);
		
		Start_time[i][1]=fr;
		//Start_time[1][1]=0.45;
/*
		Start_time[1][1]=0.00;
		Start_time[2][1]=0.10;
		Start_time[3][1]=0.20;
		Start_time[4][1]=0.15;
		Start_time[5][1]=0.16;
		Start_time[6][1]=0.25;
		Start_time[7][1]=0.105;
		Start_time[8][1]=0.17;
		Start_time[9][1]=0.23; */
		
		//&&&&&printf("First Packet : %0.3f\n",Start_time[i][1]);
		
		for(j=2;j<=NUM;j++)
		{
		fr= (float)rand()/RAND_MAX;	

		Start_time[i][j] =Start_time[i][j-1]+offtime[i]*(j-1)+RandomBetween(0,ToA[i]);
		//&&&&&printf("Packet: %0.3f sum of %0.3f + %0.3f + %0.3f \n",Start_time[i][j],Start_time[i][j-1],offtime[i]*(j-1),RandomBetween(0,ToA[i]));

		}
		
		
		for(j=1;j<=NUM;j++)
		{
		if(i!=0)
		{
		//&&&&&&printf("Start-time [%d][%d]: %0.3f |",i,j,Start_time[i][j]);
		//printf("Preamble-Time [%d][%d] :%0.3f |",i,j,ToPH_Mat[i][j]);
		}
		}

		printf("\n\n");

}

printf("**************************Network Starts****************************\n\n");
for (i=1;i<=NODE;i++)
{
	for(j=1;j<=NUM;j++)
	{
		for(k=1;k<=NODE;k++)
		{
			for (l=1;l<=NUM;l++)
			{
				if(k!=i)
				{
					if(SF[i]==SF[k])									// k!=i for not taking the same node
					{
							if(Start_time[i][j]<=Start_time[1][NUM])
							{
							
								if( (((Start_time[k][l] <= Start_time[i][j]+ToPH_Mat[i][j] ) && (Start_time[i][j]+ToPH_Mat[i][j] <= Start_time[k][l]+ToA[k]) ) ||
								 ( (Start_time[k][l] <= Start_time[i][j]+ToPH3_Mat[i][j]) && (Start_time[i][j]+ToPH3_Mat[i][j] <=Start_time[k][l]+ToA[k] )) )&& (RSSI[k]>=RSSI[i]))
								{

								if(collision_counter_intraSF[i][j]==0)
								{
								collision_counter_intraSF[i][j]=collision_counter_intraSF[i][j]+1;
								if(j<=40 && i>=50)
								{
								
								//&&&&&&printf("Interfered :i ; Packet :j ; Interferer :k ; Packet :l\n");
								//&&&&&&printf("Interfered[%d,%d] : Interferer[%d,%d] : COLLISION\n",i,j,k,l);
								//&&&&&&printf("Because, Vulnerable time of Interfered %0.3f lies between Start %0.3f and end time of Interferer %0.3f. Also RSSI of interferer %0.3f is greater than interfered %0.3f\n",Start_time[i][j]+ToPH_Mat[i][j] ,Start_time[k][l],Start_time[k][l]+ToA[k],RSSI[k],RSSI[i]);
								
								//&&&&&&printf("Interfered :i ; Packet :j ; Interferer :k ; Packet :l\n");
								printf("%d :%d : %d : %d : Collision :",i,j,k,l);
								printf("%0.3f : %0.3f\n",RSSI[k],RSSI[i]);
																
							
								}
								//&&&&&&printf("ccollision_counter_intraSF[%d] [%d] : %d \n\n\n",i,j,collision_counter_intraSF[i][j]);
								}
								
		
								}
								else if (  (((Start_time[i][j]+ToA[i])>Start_time[k][l]) && (Start_time[k][l]>=Start_time[i][j]+ToPH_Mat[i][j])) && RSSI[k]>=RSSI[i])
								{

								if((badCRC_counter[i][j]==0) && (collision_counter_intraSF[i][j]==0))
								{
								badCRC_counter[i][j]++;
								
								if(j<=40 && i>=50)
								{
								//&&&&&printf("Interfered[%d,%d] : Interferer[%d,%d] : BAD CRC\n",i,j,k,l);	
								//&&&&&printf("Because, Interferer time %0.3f lies between after Preamble %0.3f and end time of Interfererd %0.3f.Also RSSI of interferer %0.3f is greater than interfered %0.3f \n",Start_time[k][l],Start_time[i][j]+ToPH_Mat[i][j],Start_time[i][j]+ToA[i],RSSI[k],RSSI[i]);				
								
								printf("%d :%d : %d :%d : CRC :",i,j,k,l);
								printf("%0.3f : %0.3f\n",RSSI[k],RSSI[i]);
								}
								
								//&&&&&printf("badCRC_counter[%d][%d] %d \n\n",i,j,badCRC_counter[i][j]);
								}
								
								}
							}
					}
					else
					{
						if(Start_time[i][j]<=Start_time[1][NUM])
						{
		
							SIR_Threshold = SIRThreshold(SF[i],SF[k]);
							//printf("%0.2f\n",SIR_Threshold);
							
							if( (((Start_time[k][l] <= Start_time[i][j]+ToPH_Mat[i][j] ) && (Start_time[i][j]+ToPH_Mat[i][j] <= Start_time[k][l]+ToA[k]) ) ||
							 ( (Start_time[k][l] <= Start_time[i][j]+ToPH3_Mat[i][j]) && (Start_time[i][j]+ToPH3_Mat[i][j] <=Start_time[k][l]+ToA[k] )) ))
							{
							
							printf("Interfered :i ; Packet :j ; Interferer :k ; Packet :l\n");
							printf("Interfered[%d,%d] : Interferer[%d,%d] : Inter-SF-COLLISION\n",i,j,k,l);
							printf("Because, Vulnerable time of Interfered %0.3f lies between Start %0.3f and end time of Interferer %0.3f. Also RSSI Int %d - RSSI Ref %d \n\n",Start_time[i][j]+ToPH_Mat[i][j] ,Start_time[k][l],Start_time[k][l]+ToA[k],RSSI[k],RSSI[i]);
							
							if(collision_counter_interSF[i][j]==0)
							collision_counter_interSF[i][j]++;
							}
	
							
							else if (  ((  ((Start_time[i][j]+ToA[i])>Start_time[k][l]) && (Start_time[k][l]>=Start_time[i][j]+ToPH_Mat[i][j]) ) )&& ((RSSI[i]-RSSI[k])<=SIR_Threshold))
							{
							printf("%0.2f\n",SIR_Threshold);	
							printf("SIR_Threshold : %0.2f\n",SIR_Threshold);	
							printf("Interfered[%d,%d] : Interferer[%d,%d] : Inter-SF BAD CRC\n",i,j,k,l);	
							printf("Because, Interferer time %0.3f lies between after Preamble %0.3f and end time of Interfererd %0.3f \n\n",Start_time[k][l],Start_time[i][j]+ToPH_Mat[i][j],Start_time[i][j]+ToA[i]);				
							
							if(badCRC_counter_interSF[i][j]==0)
							badCRC_counter_interSF[i][j]++;
							
							printf("badCRC_counter_interSF[%d][%d] %d \n",i,j,badCRC_counter_interSF[i][j]);
		
							}
						
						}
					}
					
				}
				
			}
		}
	}
}



//float ThroughPutNode_Collision[NODE]={0};
//float ThroughPutNode_BadCRC[NODE]={0};
float ThroughPut[NODE]={0};
float AvgThroughPut=0, AvgBadCRC_intraSF=0, AvgBadCRC_interSF=0;

float sum_coll_intraSF[NODE]={0};
float sum_coll_interSF[NODE]={0};

float sum_badcrc[NODE]={0};
float sum_badcrc_interSF[NODE]={0};

printf("max time node 1 :%0.3f\n",Start_time[1][NUM]);
printf("max time node 2 :%0.3f\n",Start_time[2][NUM]);


for(i=1;i<=NODE;i++)
{
	
	for(j=1;j<=NUM;j++)
	{
		if(collision_counter_intraSF[i][j]==1)
		sum_coll_intraSF[i]++;	
		
		//if(collision_counter_interSF[i][j]==1)
		//sum_coll_interSF[i]++;	
		
		else if(badCRC_counter[i][j]==1)
		sum_badcrc[i]++;
		
		//if(badCRC_counter_interSF[i][j]==1)
		//sum_badcrc_interSF[i]++;
		
	}
	
	printf("Intra SF Collision [%d]: %0.0f\n",i,sum_coll_intraSF[i]);
	//&&&&&&printf("Inter SF Collision [%d]: %0.0f\n",i,sum_coll_interSF[i]);
	
	printf("Intra SF Bad CRC [%d]: %0.0f\n",i,sum_badcrc[i]);
	//&&&&&&printf("Inter-SF Bad CRC [%d]: %0.0f\n",i,sum_badcrc_interSF[i]);
}



printf("***********************Network Time Ends*************************\n\n");

float DER[NODE]={0};
float PER_interSF[NODE]={0}, PER_intraSF[NODE]={0};
float sum;
for(i=1;i<=NODE;i++)
{
//&&&&&&printf("Intra-SF Collision [%d] : %0.0f %%\n",i,((sum_coll_intraSF[i])/(NUM)*100));


sum_coll += ((sum_coll_intraSF[i])/(NUM)*100);
sum_crc +=  ((sum_badcrc[i])/(NUM)*100);


//printf("Inter-SF Collision [%d] : %0.0f %%\n",i,((sum_coll_interSF[i])/(NUM)*100));

//printf("Total Collisions [%d] : %0.2f %%\n",i,((sum_coll_intraSF[i]+sum_coll_interSF[i])/NUM)*100);


//&&&&&&printf("Intra-SF CRC_Error [%d] : %0.0f %%\n",i,((sum_badcrc[i])/(NUM)*100));

//printf("Inter-SF CRC_Error [%d] :&& %0.0f %%\n",i,((sum_badcrc_interSF[i])/(NUM)*100));


//DER[i]=100-((sum_coll_interSF[i]+sum_coll_intraSF[i])/(NUM)*100);


PER_interSF[i]=((sum_badcrc_interSF[i])/NUM)*100;

PER_intraSF[i]=((sum_badcrc[i])/NUM)*100;

//printf("DER [%d] : %0.2f %%\n",i,DER[i]);

//printf("Intra-SF CRC_Error [%d] : %0.2f %%\n",i,PER_interSF[i]);

//printf("Inter-SF CRC_Error [%d] : %0.2f %%\n",i,PER_intraSF[i]);

//AvgThroughPut=AvgThroughPut+DER[i];
AvgBadCRC_intraSF=AvgBadCRC_intraSF + ((sum_badcrc[i])/(NUM)*100);
AvgBadCRC_interSF=AvgBadCRC_interSF + ((sum_badcrc_interSF[i])/(NUM)*100);

}


printf("Collision %0.2f %%\n",(sum_coll/NODE));
printf("Bad CRC %0.2f %%\n",(sum_crc/NODE));

//printf("Avg DER    %0.3f\n",AvgThroughPut/(NODE));
//printf("Avg PER Intra-SF %0.3f\n",AvgBadCRC_intraSF/(NODE));
//printf("Avg PER Inter-SF %0.3f\n",AvgBadCRC_intraSF/(NODE));



//printf("%0.3f\n",sum_coll[1]/NODE);
//printf("%0.3f",sum_coll[2]/NODE);


//printf("ran once %d",loop);
return 0;
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


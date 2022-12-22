#include<stdio.h>
#define bucketsize 1000
#define n 5 // user defined function to output the contents of bucket at a constant rate
void bucketoutput(int *bucket,int op)
{
if(*bucket > 0 && *bucket > op) // if the no. of bytes in thebucket >output rate
{
*bucket= *bucket-op; //no. of bytes in bucket – output rate
printf("\n%d-outputed remaining is %d",op,*bucket);
}
else if(*bucket > 0) // if the bucket is not empty
{
printf("\n remaining data output = %d",*bucket);
*bucket=0;
}
}
int main()
{
int op,newpack,oldpack=0,wt,i,j,bucket=0; // op – ouput rate, wt- waitingtime, bucket- no.of bytes in the bucket at any point of time
printf("enter output rate"); // input the output rate
scanf("%d",&op);
for(i=1;i<=n;i++)
{
newpack=rand()%500; //new packet with random size is generated
printf("\n\n new packet size = %d",newpack);
newpack=oldpack+newpack;
wt=rand()%5; // random waiting time is generated
if(newpack<bucketsize)
bucket=newpack;
else
{
printf("\n%d = the newpacket and old pack is greater than bucketsize reject",newpack);
bucket=oldpack;
}
printf("\nthe data in bucket = %d",bucket);
printf("\n the next packet will arrive after = %d sec",wt);
// calling output rate function with wait time
for(j=0;j<wt;j++)
{
bucketoutput(&bucket,op);
sleep(1);
}
oldpack=bucket;
}
while(bucket>0)
bucketoutput(&bucket,op);
return 0;
}


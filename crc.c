#include<stdio.h>
#include<string.h>
#define N strlen(g)
char t[28],cs[28],g[]="10001000000100001";
int a,i,j;
void xor(){
	for(j = 1;j < N; j++)
	cs[j] = (( cs[j] == g[j])?'0':'1');
}


void crc(){
	for(i=0;i<N;i++)
	cs[i]=t[i];
	do{
	if(cs[0]=='1') // if first bit is 1 do xor, othwise directly go for shifting
	xor();
	for(j=0;j<N-1;j++)
	cs[j]=cs[j+1]; //shifting
	cs[j]=t[i++]; //droping next bit for division
}while(i<=a+N-1);
}
int main()
{
	printf("\nMessage to be send is: ");
	scanf("%s",t);
	printf("\n-------------------------- ");
	printf("\nGeneratng polynomial : %s",g);
	a=strlen(t);
	// printf("a=%d",a); a=4
	//printf("N=%d",N); N=17
	for(i=a;i<a+N-1;i++)
			t[i]='0';
	printf("\n---------------------------- ");
	printf("\nAfter appending zero's to message : %s",t);
	printf("\n----------------------------- ");
	crc();
	printf("\nChecksum is : %s",cs);
	for(i=a;i<a+N-1;i++) //data+checksum
		t[i]=cs[i-a];
	printf("\n------------------------------");
	printf("\nFinal codeword (message+checksum) to be transmitted is : %s",t);
	printf("\n--------------------------------");
	printf("\nEnter received message ");
	scanf("%s",t);
	crc();
	printf("\nRemainder : %s",cs);
	for(i=0;(i<N-1) && (cs[i]!='1');i++); //if 1 is encounter than the for loop will
	if(i<N-1)
		printf("\n\nError detected\n\n");
	else{
		printf("\n\nNo error detected\n\n");
		printf("\n---------------------------- \n");
	}
	

	return 0;

}

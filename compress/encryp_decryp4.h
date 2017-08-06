#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
#ifndef encryp_decryp4_H_
#define encryp_decryp4_H_

void encrypt(char *source,char *dest,int totfreq)
{
   FILE *file =fopen(source,"r");
   FILE *file5=fopen(dest,"w");
   char *result=(char*)malloc(sizeof(char));
	printf("total frequency recieved is %d",totfreq);
  // char line[8];
   int i=0,j=0;
   int extrabits=totfreq%8;
   int iterations=totfreq/8;
   printf("extrabits bits %d\n",extrabits);
   printf("total iterations %d\n",iterations);	
   int flag=0,flag1=0;
   while(flag<=(iterations+1))
	{
	   if(flag==(iterations+1))
	   {
		 for(;i<extrabits;i++)
	   	{
	       		char get = (char)getc(file);
			
			//if(get==EOF)
			//exit(1);
	      	     if	(get == '0')
	        		 *result <<= 1;
	             else if(get == '1')
	        	 *result = ((*result<<1)|0x1) ;
			flag1++;
	 	}
		for(j=0;j<(8-extrabits);j++)
		{
		       *result <<= 1;//padding the extra bits with 0's;
		       flag1++;
		}
		fprintf(file5,"%c",*result);
		flag++;
	   }
	else
	{	  
	
	   for(;i<8;i++)
	   {
	      char get = (char)getc(file);
		
		flag1++;
	      if(get == '0')
	         *result <<= 1;
	      else if(get == '1')
	         *result = ((*result<<1)|0x1) ;
		//flag1++;
	   }
	   i=0;
	   fprintf(file5,"%c",*result);
	   flag++;	
	//   printf("->%c\n",*result);
	}
      }		
	fclose(file);
	fclose(file5);
	printf("flag1 =%d",flag1);
  
}
void decrypt(char *source,char *dest)
{
		printf("source %s",source);
		printf("dest %s",dest);
		int charnum=0;
		//printf("source = %s",source);
  	 	FILE *f1=fopen(source,"r");
		while(fgetc(f1)!=EOF)
		{
			charnum++;
		}
		printf("Number of characters read %d\n",charnum);
		fclose(f1);
		f1=fopen(source,"r");
		FILE *f2=fopen(dest,"w");
		int k=0,n;
		int i=7;
		char ch;
		int flag=1;
		while(1)
		{
			ch=fgetc(f1);
			flag++;
			if(flag==(charnum+2))
			break;
			//printf("%c",ch);
			//if(ch==EOF)
			//	break;
			//else
			//{
				
				
					
				k=(int)ch;
				//printf("k=  %d",k);
				for (i = 7; i >= 0; i--)
				  {
				    n = k >> i;
				 
				    if (n & 1)
					{
				      	fprintf(f2,"%d",1);
					//printf("1");
					}
				    else
					{
				     	fprintf(f2,"%d",0);
					//printf("0");
					}

				  }
				//}
			}
		//printf("Number of character read %d",flag);
		
		fclose(f1);
		fclose(f2);
}
#endif

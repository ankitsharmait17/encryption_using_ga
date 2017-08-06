#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <cstdlib>
#include <iomanip>

using namespace std;
int ckey[4],mkey[3],pf,dev=0,devmax=0,generations=0,keycount,nchar=0;
char p1[16],p2[16],key[9],p[32],buffer[1041024];

void printing()
{
	for(int i=0;i<=15;i++)
		cout<<p1[i];
	cout<<endl;
	for(int i=0;i<=15;i++)
		cout<<p2[i];
	cout<<endl;
}
int ascii_count()
{
	int a_count=0;
	for(int i=0;i<=15;i++)
	{
		a_count=a_count+(int)p1[i]+(int)p2[i];
	}
	return a_count;
	
}

	
int randomInclusive(int max)
{
	
	return ((int)rand()%max);
}
void gen_cross_key()
{
	int i=0,j=0;
	for(i=0;i<4;i++)
	{
		ckey[i]=randomInclusive(15);
		for(j=0;j<i;j++)
		{
			if(ckey[i]==ckey[j])
			{
				ckey[i]=randomInclusive(15);
				j=-1;
			}
		}
	}
	sort(ckey,ckey+4);
}

void gen_mutate_key()
{
	int i=0,j=0;
	for(i=0;i<3;i++)
	{
		mkey[i]=randomInclusive(15);
		for(j=0;j<i;j++)
		{
			if(mkey[i]==mkey[j])
			{
				mkey[i]=randomInclusive(15);
				j=-1;
			}
		}
	}
	sort(mkey,mkey+3);
}

void crossover()
{
	int s1,s2,e1,e2;char temp;
	s1=ckey[0];
	e1=ckey[1];
	s2=ckey[2];
	e2=ckey[3];

	
	//printing();

	for(int i=s1;i<=e1;i++)
	{	temp=p1[i];
		p1[i]=p2[i];
		p2[i]=temp;
	}
	for(int i=s2;i<=e2;i++)
	{	temp=p1[i];
		p1[i]=p2[i];
		p2[i]=temp;
	}

	//printing();
}

void mutation()
{
	for(int i=0;i<3;i++)
	{
		p1[mkey[i]]=128-p1[mkey[i]];
		p2[mkey[i]]=128-p2[mkey[i]];
	}
	//cout<<"AFTER MUTATION"<<endl;
	//printing();
}

void permute()
{	
	int i;char temp[8];
	pf=randomInclusive(7);
	//cout<<"P.F."<<pf<<endl;//permutation factor
	for(i=0;i<4;i++)
	{
		sprintf(key+i,"%x",ckey[i]); 
	}
	for(int j=0;j<3;j++,i++)
	{
		sprintf(key+i,"%x",mkey[j]);
	}
	sprintf(key+i,"%d",pf);
	
	/*
	cout<<"KEY ARRAY: ";
	for(i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;
	*/
	
	memcpy(temp,key+pf,7-pf);
	memcpy(temp+7-pf,key,pf);
	memcpy(key,temp,7);
	
	/*
	cout<<"NEW KEY ARRAY: ";
	for(i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;
	*/
}

void no_of_chars()
{
	int i;
	for(i=0;i<16;i++)
	{
		nchar++;	
		if(p1[i]<0)
		{
			p1[i]=' ';
			nchar--;
		}
	}
	for(i=0;i<16;i++)
	{
		nchar++;	
		if(p2[i]<0)
		{
			p2[i]=' ';
			nchar--;
		}
	}

}

int main ()
{
	int i=0,j=0,len1;
	srand((unsigned int)time(NULL));
	int dev=0;
	char in_file[100],out_file[100];
	ifstream infile;
	printf("enter the input file location \n");
	cin >> in_file; 
	
	//ofstream en;
	//printf("enter the location where you want to encrypt the file\n");
	//cin >> out_file;
	
	while(generations!=10000)
	{	keycount=0;
		infile.open(in_file); 
		//en.open(out_file);
		ofstream keys;
		keys.open("keys.txt");
		
		while(!infile.eof())
		{
			int k1,k2;
			infile.read(p1,16);
			//cout<<p1<<endl;
			infile.read(p2,16);
			//cout<<p2<<endl;

			for(i=0;i<16;i++)
			{	if(p1[i]>0)
					i=i;
				else
					p1[i]=' ';
			}
			for(i=0;i<16;i++)
			{	if(p2[i]>0)
					i=i;
				else
					p2[i]=' ';
			}

			k1=ascii_count();
	
			no_of_chars();

			gen_cross_key();

			/*cout<<"CROSSOVER KEYS : ";
			for(i=0;i<4;i++)
			{	printf("%d\t",ckey[i]);
			}
			cout<<endl;*/

			crossover();
			gen_mutate_key();

			/*cout<<"MUTATION KEYS : ";
			for(i=0;i<3;i++)
			{	printf("%d\t",mkey[i]);
			}
			cout<<endl;*/

			mutation();
			permute();
			k2=ascii_count();
			dev=dev+abs(k2-k1);

			keys<<key;//writing key in the file
			keycount++;
			memset(key, 0, 8);
			memset(p1, 0, 16);
			memset(p2, 0, 16);
		}

		keys.close();
		infile.close();
		nchar=0;

		if(dev>devmax)
		{	
			ifstream keys;
			ofstream keysfinale;
			keysfinale.open("keysfinale.txt");
			keys.open("keys.txt");

			devmax=dev;

			keys.read(buffer,(keycount*8));
			keysfinale<<buffer;
			keys.close();
			keysfinale.close();
	
			cout<<"~~~~DEVIATION MAX : "<<devmax<<"  Generations : "<<generations<<endl;
			generations=0;
		}
		else
		{
			generations++;
		}
		dev=0;
	}
	
	cout<<"FINALE~~~~DEVIATION MAX : "<<devmax<<"  Generations : "<<generations<<endl;

	ifstream keysfinale;
	keysfinale.open("keysfinale.txt");
	
	

	//en.close();
	/*
	memcpy(p,p1,16);
	memcpy(p+16,p2,16);// concatinating both encrypted parent of 16 -->32 
	en<<p;//writing it in the file
	*/
	return 0;
}

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
int ckey[4],mkey[3],pf;
char p1[16],p2[16],key[9],p[32];

void printing()
{
	for(int i=0;i<=15;i++)
		cout<<p1[i];
	cout<<endl;
	for(int i=0;i<=15;i++)
		cout<<p2[i];
	cout<<endl;
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

	
	printing();

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

	printing();
}

void mutation()
{
	for(int i=0;i<3;i++)
	{
		p1[mkey[i]]=128-p1[mkey[i]];
		p2[mkey[i]]=128-p2[mkey[i]];
	}
	cout<<"AFTER MUTATION"<<endl;
	printing();
}

void permute()
{	
	int i;char temp[8];
	pf=randomInclusive(7);
	cout<<"P.F."<<pf<<endl;
	for(i=0;i<4;i++)
	{
		sprintf(key+i,"%x",ckey[i]); 
	}
	for(int j=0;j<3;j++,i++)
	{
		sprintf(key+i,"%x",mkey[j]);
	}
	sprintf(key+i,"%d",pf);
	cout<<"KEY ARRAY: ";
	for(i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;
	
	memcpy(temp,key+pf,7-pf);
	memcpy(temp+7-pf,key,pf);
	memcpy(key,temp,7);
	
	cout<<"NEW KEY ARRAY: ";
	for(i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;
}

int main ()
{
	int i=0,j=0,len1;
	srand((unsigned int)time(NULL));

	ifstream infile; 
	infile.open("file.txt"); 
	
	ofstream en;
	en.open ("file3.txt");
	
	ofstream keys;
	keys.open ("keys.txt");
	 
	cout << "Reading from the file" << endl; 
   
	while(!infile.eof())
	{
		infile.read(p1,16);
		cout<<p1<<endl;
		infile.read(p2,16);
		cout<<p2<<endl;
		
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

		gen_cross_key();
		cout<<"CROSSOVER KEYS : ";
		for(i=0;i<4;i++)
		{	printf("%d\t",ckey[i]);
		}
		cout<<endl;
		crossover();
		gen_mutate_key();
		cout<<"MUTATION KEYS : ";
		for(i=0;i<3;i++)
		{	printf("%d\t",mkey[i]);
		}
		cout<<endl;
		mutation();
		permute();

		memcpy(p,p1,16);
		memcpy(p+16,p2,16);
		en<<p;
		
		keys<<key;
	
		memset(key, 0, 8);
		memset(p1, 0, 16);
		memset(p2, 0, 16);
	}
	
	keys.close();
	en.close();
	infile.close();

	return 0;
}

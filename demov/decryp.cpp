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
int ckey[4],mkey[3],keycount=0;unsigned int pf;
char p1[16],p2[16],key[8],p[32];

void printing()
{
	for(int i=0;i<=15;i++)
		cout<<p1[i];
	cout<<endl;
	for(int i=0;i<=15;i++)
		cout<<p2[i];
	cout<<endl;
}

void gen_keys()
{	
	int i;
	for(i=0;i<4;i++)
	{
		if((key[i]>='0')&&(key[i]<='9'))
			ckey[i]=(int)(key[i]-'0');
		else
		{	int temp=key[i];
			ckey[i]=temp-87;
		}
	}
	for(int j=0;j<3;i++,j++)
	{
		if((key[i]>='0')&&(key[i]<='9'))
			mkey[j]=(int)(key[i]-'0');
		else
			mkey[j]=key[i]-87;
	}

	cout<<"Ckey : ";
	cout<<ckey<<endl;
	cout<<"Mkey : ";
	cout<<mkey<<endl;
}

void rev_crossover()
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

void rev_mutation()
{
	for(int i=0;i<3;i++)
	{
		p1[mkey[i]]=128-p1[mkey[i]];
		p2[mkey[i]]=128-p2[mkey[i]];
	}
	cout<<"AFTER DEMUTATION"<<endl;
	printing();
}

void rev_permute()
{	
	char temp[8];
	pf=(int)key[7]-'0';
	//cout<<"P.F."<<pf<<endl;

	/*cout<<"KEY ARRAY: ";
	for(int i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;*/

	memcpy(temp,key+7-pf,pf);
	memcpy(temp+pf,key,7-pf);
	memcpy(key,temp,7);

	/*cout<<"NEW KEY ARRAY: ";
	for(int i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;*/
}

int main ()
{
	int i=0,j=0;
	srand((unsigned int)time(NULL));

	ifstream infile; 
	infile.open("file3.txt"); 
	
	ifstream keys;
	keys.open ("keysfinale.txt");

	ofstream en;
	en.open ("f1.txt");
		 
	cout << "Reading from the file" << endl; 
   
	while((!infile.eof())&&(!keys.eof()))
	{
		infile.read(p1,16);
		cout<<p1<<endl;
		
		infile.read(p2,16);
		cout<<p2<<endl;

		keys.read(key,8);

		if(key[0]=='\0')
			break;
		
		printing();
		
		rev_permute();

		gen_keys();
		
		cout<<"KEYS : "<<key<<endl;
		keycount++;
		rev_mutation();
		
		rev_crossover();

		memcpy(p,p1,16);
		memcpy(p+16,p2,16);
	
		en<<p;
	
		memset(key, 0, 8);
		memset(p1, 0, 16);
		memset(p2, 0, 16);
	}
	cout<<keycount<<endl;
	keys.close();
	en.close();
	infile.close();

	return 0;
}

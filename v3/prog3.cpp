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
int ckey[4],mkey[3],pf,dev=0,devmax=0,generations=0,keycount,no_chars,flag=0;
char p1[16],p2[16],key[8],p[32],buffer[1041024];

void printing()
{
	flag++;
	cout<<"p1-->"<<endl;
	for(int i=0;i<=15;i++)
		cout<<p1[i];
	cout<<endl;
	cout<<"p2-->"<<endl;
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
	int s1,s2,e1,e2;char temp;  //crossover points
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
		p1[mkey[i]]=128-p1[mkey[i]];//mutation points
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
		no_chars++;	
		if(p1[i]<0)
		{
			p1[i]=' ';
			no_chars--;
		}
	}
	for(i=0;i<16;i++)
	{
		no_chars++;	
		if(p2[i]<0)
		{
			p2[i]=' ';
			no_chars--;
		}
	}
}

void rev_permute()
{	
	char temp[8];
	pf=(int)key[7]-'0';
	//cout<<"P.F."<<pf<<endl;

	/*
	cout<<"KEY ARRAY: ";
	for(int i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;
	*/

	memcpy(temp,key+7-pf,pf);
	memcpy(temp+pf,key,7-pf);
	memcpy(key,temp,7);

	/*
	cout<<"NEW KEY ARRAY: ";
	for(int i=0;i<8;i++)
		cout<<key[i];
	cout<<endl;
	*/
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
			ckey[i]=temp-87; //in order to convert the hex back to normal digits
		}
	}
	for(int j=0;j<3;i++,j++)
	{
		if((key[i]>='0')&&(key[i]<='9'))
			mkey[j]=(int)(key[i]-'0');
		else
			mkey[j]=key[i]-87;
	}

	/*
	cout<<"Ckey : ";
	cout<<ckey<<endl;
	cout<<"Mkey : ";
	cout<<mkey<<endl;
	*/
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
	
	ofstream en;
	
	while(generations!=10000)
	{	keycount=0;
		infile.open(in_file);
		
		ofstream keys;
		keys.open("keys.txt");
		
		while(!infile.eof())
		{
			int k1,k2;
			infile.read(p1,16);
			//cout<<p1<<endl;
			infile.read(p2,16);
			//cout<<p2<<endl;
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
			keycount++; // counting the number of keys

			memset(key, 0, 8);
			memset(p1, 0, 16);
			memset(p2, 0, 16);
		}

		keys.close();
		infile.close();
		no_chars=0;

		if(dev>devmax)
		{	
			ifstream keys;
			ofstream keysfinale;
			keysfinale.open("keysfinale.txt");
			keys.open("keys.txt");

			devmax=dev;

			keys.read(buffer,(keycount*8));//keycount=number of keys*8 = total size of keys;
			keysfinale<<buffer;//writing the keys of max deviation in the file key finale
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
	memset(p, 0, 32);
	cout<<"FINALE~~~~DEVIATION MAX : "<<devmax<<"  Generations : "<<generations<<endl;

	ifstream keysfinale;
	keysfinale.open("keysfinale.txt");

	infile.open(in_file);

	printf("Enter the location where you want to encrypt the file\n");
	cin >> out_file;
	en.open(out_file);
	
	while((!keysfinale.eof())&&(!infile.eof()))
	{
		keysfinale.read(key,8);
		//cout<<key<<endl;
		infile.read(p1,16);
		//cout<<p1<<endl;
		infile.read(p2,16);//now we need to encrypt this p1 p2 according to the keys extracted
		//cout<<p2<<endl;
		
		no_of_chars();
		
		rev_permute();// so that we can get back the crossover and the mutation keys according ti which it will be wriiten in keyfinale for max deviation
		gen_keys();
		
		crossover();
		mutation();
		printf("p1-->%s\n",p1);
		printf("p2-->%s",p2);
		cout<<"KEYS : "<<key<<endl;
				memset(key, 0, 8);
	
		//memcpy(p,p1,16);
		//memcpy(p+16,p2,16);// concatinating both encrypted parent of 16 -->32
		//printf("p1-->%s\n",p1);
		//printf("p2-->%s\n",p2);
		//snprintf(p,32,"%s",p1);
		//snprintf(p+16,16,"%s",p2);
		printf("p1-->%s\n",p1);
		printf("p2-->%s",p2);
		//memcpy(p,p1,16);
		//memcpy(p+16,p2,16);
		en<<p1;
		en<<p2;

		//memset(p,0,32);
		//memset(key, 0, 8);
		memset(p1, 0, 16);
		memset(p2, 0, 16);
	}
	cout<<"number of keys "<<flag;
	keysfinale.close();
	infile.close();
	en.close();

	return 0;
}

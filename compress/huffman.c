#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>
#include "encryp_decryp4.h"
#include<time.h>
#define MAX_NODES 100
int sum1=0,charnum,flag=0;
int codes[256]={0};
FILE *dread,*dwrite;
//-------------------------------------------------------------------------------------------------------------->Structure Declaration
struct HeapNode  //content of each node
{
	char data;
	unsigned freq;
	struct HeapNode *left, *right;
};
struct arrchar
{
	char abc[256];
	
};
struct arrchar **str;//string array to store the representation of each character
struct Heap //collection of nodes
{
	unsigned size; 
	unsigned capacity;
	struct HeapNode **array; 
};
struct HeapNode* newNode(char data, unsigned freq) //function to initialize a new node
{
	struct HeapNode* temp =
		(struct HeapNode*) malloc(sizeof(struct HeapNode)); 
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}
struct arrchar* newCode(char c,int n,char cc[])
{
	struct arrchar* temp=(struct arrchar*)malloc(sizeof(struct arrchar));
	strncpy(temp->abc,cc,n);
	return temp;
}
//------------------------------------------------------------------------------------------------------------------------->Utility Functions
void swapHeapNode(struct HeapNode** a, struct HeapNode** b) 				
{
	struct HeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct Heap* minHeap, int pos)  //performing heap sort since the data taken as input is unsorted
{
	int smallest = pos;
	int left = 2 * pos + 1;	//linearly only its checking that which one will be its left and right nodes							 													 
	int right = 2 * pos + 2;
                                                                                        													
	if (left < minHeap->size &&
		minHeap->array[left]->freq < minHeap->array[smallest]->freq)
	smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->freq < minHeap->array[smallest]->freq)
	smallest = right;

	if (smallest != pos)
	{
		swapHeapNode(&minHeap->array[smallest], &minHeap->array[pos]); 
		minHeapify(minHeap, smallest);
	}
}
int isSizeOne(struct Heap* minHeap) //if size of the heap left=1 then it is completely processed nomore extractration has to be done and last noe will be the root node
{
	return (minHeap->size == 1);
}
struct HeapNode* extractMin(struct Heap* minHeap) //always the 1st element of the minheap is the minimum which is extracted after extraction the last node is assigned as 1st and again heapification is 								done
{
	struct HeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
	--minHeap->size; 
	minHeapify(minHeap, 0);

	return temp;
}
void printArr(int arr[], int n,char c)  //prints a given array
{
	int i;
	
	char str1[n];
	for (i = 0; i < n; ++i)
	{
		printf("%d", arr[i]);
		str1[i]=arr[i] + '0';
	}
	str[c]=newCode(c,n,str1);
	//codes[c]=(int) strtol(str, (char **)NULL, 10);
	
	printf("\n");
}

void insertHeap(struct Heap* minHeap, struct HeapNode* minHeapNode)  //inserts the new node at the last position and again heapification is done comparing it with is immidiate root
{
	int j;
	int i = minHeap->size; //present size index  is one greater than the index of last hence inserting here only
	minHeap->array[i] = minHeapNode; 
	++minHeap->size;
	minHeapify(minHeap,(i-1)/2);
}


int isLeaf(struct HeapNode* root) //if left and right of a node is NULL then its a leaf
{
	return !(root->left) && !(root->right) ; 
}
struct Heap* createHeap(unsigned capacity) //allocates memory to the heap
{
	struct Heap* minHeap =
		(struct Heap*) malloc(sizeof(struct Heap)); 
	minHeap->capacity = capacity;
	minHeap->array =
	(struct HeapNode**)malloc(minHeap->capacity * sizeof(struct HeapNode*));//(capacity*size of each structure of a node)
	return minHeap;
}
void buildHeap(struct Heap* minHeap) //it will heapify the heap in minimum order
{
	int n = minHeap->size - 1;
	int i;
	
	for (i = (n - 1) / 2; i >= 0; --i)  
		minHeapify(minHeap, i);


}
struct Heap* createAndBuildHeap(char data[], int freq[], int size) //func to allocate space ,initialize each node and heapifying it
{
	struct Heap* minHeap = createHeap(size);
	int i;
	for (i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);
	minHeap->size = size;
	buildHeap(minHeap);
	return minHeap;
}
struct HeapNode* HuffmanTree(char data[], int freq[], int size)
{
	struct HeapNode *left, *right, *top; //for making a new node with summation of 2 frequencies

	int j;
	struct Heap* minHeap = createAndBuildHeap(data, freq, size);  //minHeap will have the heapifies heap

	
	while (!isSizeOne(minHeap))
	{
		
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		
		top = newNode('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertHeap(minHeap, top);  //inserting the new node in the heap
	}
	
	return extractMin(minHeap); //returns the root node so that this root can be sent to printcodes
}
void printCodes(struct HeapNode* root, int arr[], int size1) //recursive function to assign 0 to left nodes and 1 to right nodes //initially size1=1;
{
	
	if (root->left)
	{
		arr[size1] = 0;
		printCodes(root->left, arr, size1 + 1);
	}
	if (root->right)
	{
		arr[size1] = 1;
		printCodes(root->right, arr, size1 + 1);
	}

	
	if (isLeaf(root)) 
	{
		printf("%c: ", root->data);
		printArr(arr, size1,root->data);
		sum1+=size1*root->freq; //to calculate the sum of total bits req. 
	}
}
struct HeapNode* root2;
struct HeapNode* root1;
int count=0;
void Dcodes()
{
	char ch;
	//printf("data decrypted successfully\n");
	while(1)
	{
		ch=fgetc(dread);
		count++;
		if(ch==EOF)
		break;
		else
		{
		
			if(ch=='0')
			{
				if (root1->left)
				{

					root1=root1->left;
				
				}
			}
			else if(ch=='1')
			{
				if (root1->right)
				{

					root1=root1->right;
				}
		
			}			
			if (isLeaf(root1))
			{
				
					
				fprintf(dwrite,"%c",root1->data);
				root1=(struct HeapNode*)malloc(sizeof(struct HeapNode));
				root1->data=root2->data;
				root1->left=root2->left;
				root1->right=root2->right;

			}
		}
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------->Building huffman tree
void HuffmanCodes(char data[], int freq[], int size)
{
	struct HeapNode* root = HuffmanTree(data, freq, size);  //last node it will return will be the root node
	int arr[MAX_NODES], top = 0;
	root1=(struct HeapNode*)malloc(sizeof(struct HeapNode));
	root2=(struct HeapNode*)malloc(sizeof(struct HeapNode));
	root1->data=root->data;
	root1->left=root->left;
	root1->right=root->right;
	root2->data=root->data;
	root2->left=root->left;
	root2->right=root->right;
	printCodes(root, arr, top); //will assign codes -->0 and 1 to the HuffanTree build

}
int main()
{
	int bits=0;
	int i,sum=0,k=0,f=0;
	clock_t start,stop;
	
	FILE *fptr,*fptr1,*fptr2;
	char ch,inpu[256],inpu1[256],oup[256]={0};
	int index, frequency[256] = {0},freq[256]={0};
	char ch1[256],arr[256];
	printf("enter the input filepath\n");
	scanf("%s",inpu);
	start = clock();
	fptr=fopen(inpu,"r");
	if(fptr==NULL)
	{
		fclose(fptr);
		exit(0);
	}
//----------------------------------------------------------------------------------------------------------------------------------->Histogram Calculation
	while(1)
	{
		ch=fgetc(fptr);
		if(ch==EOF)
		break;
		else
		{
			frequency[(int)ch]++;                     //frequency calcaulation
			ch1[(int)ch]=ch;
		}
		
	}
	stop = clock();
	int t=stop-start;
	printf("Time taken by CPU to calculate histogram %dmsec  \n",t); 
	fptr1=fopen("abc.txt","w");                            //writing the huffman tree at the top of the encrypted file
	if(fptr==NULL)
	{
		fclose(fptr);
		exit(0);
	}
	
 	for(index=0; index < 256; index++)
	{
 	       if(frequency[index] != 0)
		{
		  
 	           arr[k]=ch1[index];//holds all the letters in the file adn store linearly
		   freq[k++]=frequency[index];//freq holds all corresponding frequencies linearly
	     	   	 
		}
	
 	}

	str =(struct arrchar**)malloc(256*sizeof(struct arrchar*));
	printf("Input is\n");
	printf("Data \t frequency \t \n");
	int size = k;
	for(i=0;i<size;i++)
	{
		printf("%c \t %d \t \n",arr[i],freq[i]);
	}
	printf("size of the input array is %d\n",size);
	bits=(int)ceil(log2(size));
	printf("Number of bits required for representing each symbol is %d \n",(int)(bits));
	
	
	
	for(i=0;i<size;i++)
	{
		sum+=freq[i];
	}
	sum=sum*bits;
	
	
	printf("Total number of bits required without compression of data is %d \n",sum);
	printf("OUTPUT AFTER COMPRESSION \n");
	start = clock();
	HuffmanCodes(arr, freq, size);
	stop = clock();
	t=stop-start;
	printf("Time taken for building the huffman tree in CPU %dms \n",t);
	printf("Total number of bits required after compression of data is %d  \n",sum1);
	printf("Number of memory saved in bits %d\n",(sum-sum1));
	fptr=fopen(inpu,"r");
	char *result=(char*)malloc(sizeof(char));
	char get;
	k=1;
	int flag=0;
	start = clock();
//---------------------------------------------------------------------------------------------------------------------------------------->Encryption Part
	while(1)
	{
		ch=fgetc(fptr);
		
		if(ch==EOF)
		break;
		else
		{
			for(i=0;str[ch]->abc[i]!=NULL;i++)
			{
				flag++;
				get=str[ch]->abc[i];
				if(get == '0')
	                	 *result <<= 1;
	                	 else if(get == '1')
	        		 *result = ((*result<<1)|0x1) ;
				 if(flag%8==0)
				fprintf(fptr1,"%c",*result);
			}
			


		}//writing each character in the encoded format
	}
	fclose(fptr1);
	stop = clock();
	t=stop-start;
        int totfreq=0;
	printf("Time taken by CPU to encrypt the file %dms\n",t);
   	printf("File is compressed to abc.txt\n");
	printf("enter 1 to decrypt the file\n");
//------------------------------------------------------------------------------------------------------------------------------------------->Decryption Part
	scanf("%d",&k);
	if(k==1)
	{
		printf("Enter the filename where you want to decrypt\n");
		scanf("%s",inpu1);
		char dest2[256];
		strcpy(dest2,"xyz.txt");//stores the huffman codes from the encrypted file
		printf("dest %s",dest2);
		char dest1[]="abc.txt";
		decrypt(dest1,dest2);//decrypts using the huffman tree
		dwrite=fopen(inpu1,"w");
		dread=fopen(dest2,"r");
		start=clock();
		Dcodes();
		stop = clock();
		t=stop-start;
		printf("Time taken by CPU to decrypt the file %dms\n",t);
		printf("data decrypted successfully to %s\n",inpu1);
	}
		
	remove("xyz.txt");
	
				
return 0;
}


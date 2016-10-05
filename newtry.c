#define SIZENO 10
#define MAX_RESP 3
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


// FUNCTION DECLARATIONS
int find( char* str);
void initallocator();
char* puncrmv (char *str);
char *result();
char* UPPER(char *str);
int keyword(char* input, char *wrd);
void categorize(char* input);
void analyze(inputb *que[qi]);
void stack();
void filewriter();
void filereader();

// GLOBALS DECL
int qi;
enum keytyp { OBJ , ACTION ,EMO, QUE , SYS , USR , CONNECT , NEGATE , JOIN};

/*typedef struct {
	char *assoc;
}as;*/

typedef struct {	//for the stored questions and answers.
	char *input;
	char *responses[MAX_RESP];
	int lind;
	int val;
	enum keytyp *pat;
	node *asso;
}io;

typedef struct{
	enum keytyp *pat;
	node* n;
	int val;
	inputb *next;
}inputb;
inputb *que;

int arr[8]={0,0,0,0,0,0,0,0};

typedef struct {// this will be used in both context.. for stored data too 
	char * key;
	enum keytyp type;
	node* ptr;
} node;


//FUNCTIONS START
int keyword(char* input, char *wrd)// do it using word by word scanning from beginning itself// or use strtok for this
{ 	
	static int i = 0;
	int c = 0;
	wrd = (char *) malloc(10);// can improve memory management by mallocing and reallocing where required
	int prev;
	for(;i < strlen(input); i++)
	{	if(input[i] == ' ')
			{
			wrd[c] ='\0'; c++;
			return 0;
		}
		else {
			wrd[c] = input[i]; c++;
		}

	}
	i=0;
	return 1;	
}		
				
void categorize(char* input)
{
	char *str, cat;
	int c, d;
	static int e = 0;
	// is realloc syntax right?:
	que[qi].n[que[qi].val]= (node * )realloc(n,sizeof(node*));
	que[qi].n[que[qi].val].ptr= NULL;
	que[qi]->n[que[qi].val-1]->ptr= que[qi]->n[que[qi].val];
	que[qi].pattype=(enum keytyp *)realloc(sizeof(enum keytyp));
	keyword(input, str);
	for(c=0;c<7;c++) {
		for(d=0;d<arr[c];d++){
			
			if(strcmp(str, readdata(c*7+d))==0)// readdata() to read throught the data of individual keywords
			{
				strcpy(que[qi]->n[que[qi].val]->key, str);
				que[qi].n[que[qi].val].type=c;
				que[qi].pat[que[qi].val]=c;
				break;
				
			}
		}
	}
	if(d==arr[c-1] && c==7)
			{	printf("This word is out of my bounds of knowledge. Please help me understand it.")
				printf("Which category is the keyword");
				scanf("%c",&cat); 
				writefunc(cat,str);
				// write a write function
				
				//will have to take in more information
	}

}
info* analyze() {	
	info tmp;
	// CAN USE CONTEXT SEARCH WITH 
	FILE fp = fopen("strctdata.txt","r");
	
	// depends on how the questions are stored ... handles sall the situations to chack whether an answer is to that set.
	int i; 
       	char *str, *pat/*pattern of particular statement stored in database*/; 
	
	for(i=0;i<count;i++)// check for count variable
	{	
		tmp
		fread(&tmp, sizeof(info),fp);				
		//read file for pattern part parti
		for(j=0;j<que[qi].val;j++)
		{
			if( )// char presence in the sentence.. and checking if objects of the sentence are the same. and where the negation is present.GO in order of 
		//GO IN ORDER OF OBJECTS, ACTIONS, QUESTIONS, SYS, USR.
		
		}
	}
	for( i=0; i<)
	return //pointer to info that has correct question.
}
int output( char* str)
{
	int c=2, n,i;
	char ch;
	info *tmp;
	tmp = analyze();
	if (tmp!= NULL){
		c = 0;
		n = rand()%info[i]->val;
		if(info[i].val > 1)	{	
				if(n==info[i].lind)// to prevent output responses from repeating 
					{	
					n=(n+1)%info[i].val; info[i].lind= n;
				}
			}
			printf("%s\n", info[i].responses[n]);
			if(i==2)// 2nd response space specially reserved for bye
				{
					c=1;
					return c;//specially reserved for breaking out main infinite loop
				}
			if(c==2)
				{
				printf(" couldnt understand you. Would you like to save this for future usage. Press y for yes or anypther key for No");
				scanf(%c,ch);	
				if(ch=='y'){
					filewriter();
				
				}
				c=0;
			}
			
	}
return c;
}

	
void stack()
{
	char* str;
	for(i)
}
void filewriter()
{ 
	char *str;
	int c,d,f;
	io tmp;
	FILE *fp= fopen("structdata.txt", "w+");
	printf("Enter /e at end of total input and /r to end response earlier than 3. "); 
	while (1){	
		printf("Please enter data to be entered");// how to show end of input ?
		gets(tmp.input);// read through all input methods 
		if(!strcmp("/e",tmp)){
			for(i=0;i<3;i++)
			{
				gets(tmp.resposes[i]);	
				if(strcmp(tmp.responses[i], "/r")==0)
					break;
			}
		tmp.val=i;
		printf("Next value");
	}

}
void filereader()
{
	
}
char* UPPER(char *str)// to convert given string pointer into lower case
{
	int i=0;
	while(i<strlen(str)){ 
		if(str[i]>='a'&& str[i]<='z'){
			str[i]=str[i]-22;
		}
	}
	return str;
	
}
char* puncrmv (char *str)// for removing basic punctuation.. can improve for spaces
{ 
	int i, j = 0;
	int size=strlen(str);
	char ch1; 
	for (i = 0; i < size; i++) {
     		 if (str[i] != ','&&str[i] != ';'&& str[i] != '.'&& str[i] != '!'&&str[i] != '?') {
        		 str[j] = str[i];
        		 j++;
     		}
  	}
	str[j] = '\0';
}








/*

#define SIZENO 10
#define MAX_RESP 3

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
m#include<ctype.h>
int find( char* str);
void initallocator();
char* puncrmv (char *str);
char *result;
char* UPPER(char *str);

typedef struct {
	char *input;
	char *responses[MAX_RESP];
	int lind;
	int val;
}io;
typedef struct inputb
{
char *s ;
io **info;
inputb *next;
}
inputb **que;
int ninfo = sizeof(info)/sizeof(info[0]);
int main()
{
result = (char *)malloc(45);
info= (io **)malloc(sizeof(io *)*SIZENO);

	char sinput[15]="" , *sresponse=(char *)malloc(15),*name=(char *)malloc(15);
	int d=4;
	for(;;)
	{ 	fgets(name, 100,stdin);
		d=find(UPPER(puncrmv(name)));
		if(d==1)//  1 refers to end of execution
			break;
	
	}
}
int find( char* str)
{ int c=2, n,i;
	for( i=0; i<ninfo; i++)
	{
		if(strcmp(UPPER(info[i]->input),str)==0)
/
		{
			c=0	;
			n=rand()%info[i]->val;
			if(info[i]->val > 1)	{	
			if(n==info[i]->lind)// to prevent output responses from repeating 
				{	n=(n+1)%info[i]->val; info[i]->lind= n;}}
			printf("%s\n", info[i]->responses[n]);}}
		if(i==2)// 2nd response space specially reserved for bye
			{
				c=1;
				return c;//specially reserved for breaking out main infinite loop
			}
		if(c==2)
		{
			printf(" couldnt understand you ");}
	return c;
}

char* UPPER(char *str)// to convert given string pointer into lower case
	{ 	int i=0;
	while(i<strlen(str)){ 
		if(str[i]>='a'&& str[i]<='z'){
			str[i]=str[i]-22;}
	}
	return str;
	
}


/*void initallocator()// function to allocate space for input and responses
	{	int i=0; 
	for(i=0;i<SIZENO;i++)
	{		
		info[i]= (io *) malloc(sizeof(io));
		info[i]->input = (char* )malloc (sizeof(char)* 45);
		info[i]->responses[0] = (char* )malloc (sizeof(char)* 45);
		info[i]->responses[1] = (char* )malloc (sizeof(char)* 45);
		info[i]->responses[2] = (char* )malloc (sizeof(char)* 45);
		info[i]->lind = 0;
		info[i]->val=3;
	}
} THOUGHT TO BE UNNECESARY RIGHT NOW!
*//*
char* puncrmv (char *str)// for removing basic punctuation.. can improve for spaces
{ 
   int i, j = 0;
   int size=strlen(str);
   char ch1; 
   for (i = 0; i < size; i++) {
      if (str[i] != ','&&str[i] != ';'&& str[i] != '.'&& str[i] != '!'&&str[i] != '?') {
         str[j] = str[i];
         j++;
      }
   }
   str[j] = '\0';
}
*/

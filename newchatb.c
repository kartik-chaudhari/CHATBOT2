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
char *readdata(int , int); // TO BE REMOVED AND REPLACED BY hashtry.c
// GLOBALS DECL
int qi;//question index
enum keytyp { OBJ , ACTION , EMO , QUE , SYS, USR , NEGATE , JOIN , CONNECT };

//stored structures


typedef struct io {	//for the stored common questions and answers.
	char *input;// this will be an input question 
	char *responses[MAX_RESP];// responses for that,
	int lind;// last index of response used for the question
	int val;// the number of responses stored for a question. SHOULD REMOVED BEFORE COMPLETION
	enum keytyp *pat;//pattern of categories for the words in the project.
	node *asso;// we can associate different words to a word in this that will give me the same outputs for a change in a particular word in the question
}io;
io *info;

typedef struct node{// this will be used in both context.. for stored data too 
	char* key;
	enum keytyp type;
	struct node* ptr;
} node;

typedef struct{
	enum keytyp *pat;
	node* n;
	int val;
	inputb *next;
}inputb;
inputb *que, *answer;// que is used to create series of questions asked/ statement enetered by the user to create IN THE PRESENT CONVERSATION. 
//answer is for storing set of responses from the system IN THE PRESENT CONVERSATION.
typedef struct hashnode{// this will be used in both context.. for stored data too 
	char* key;
	struct hashnode* next;
	struct hashnode* assonext;
	struct hashnode* assoprev;
} hashnode;
int arr[9]={0,0,0,0,0,0,0,0,0};// THIS IS FOR STORING THE NUMBER OF WORDS IN THE DATABASE UNDER A CATEGORY OF WORD.	
hashnode *WordDatabase[9];

//FUNCTIONS START
int keyword(char* input, char *wrd)// THIS ACTS AS A TOKENIZER// do it using word by word scanning from beginning itself// or use strtok for this
{ 	
	static int i = 0;
	int c = 0;
	int prev;
	for(;i < strlen(input); i++)
	{	if(input[i] == ' ')
			{
			wrd[c] ='\0'; 
			c++;
			i++;
			return 0;
		}
		else {
			wrd[c] = input[i];
			c++;
		}

	}
	wrd[c] ='\0'; 
	i=0;
	return 1;	
}		
				
void categorize(char* input)
{
	char *str, cat;
	int c, d, n , k, check = 0, j;
	static int e = 0;
	str = (char *) malloc(15);
	for ( j=0; j< 10 ; j++){
		que[qi].n[i] = (node * )realloc(n,sizeof(node));	
		que[qi].n[i].ptr = NULL;
		que[qi].n[que[qi].val-1].ptr = que[qi].n[que[qi].val];
		que[qi].pattype = (enum keytyp *)realloc(n,sizeof(enum keytyp));
	// INSTEAD MALLOC 10 WORDS PER INPUT TO EASE PROCESSING
	}
	do {
		d= keyword(input, str);
		for(c = 0; c < 9; c++) {// takes care if word is present in database
			check = search(str,c);
			if(check == 1){
				strcpy(que[qi].n[que[qi].val].key, str);
				que[qi].n[que[qi].val].type=c;
				que[qi].pat[que[qi].val]=c;
				break;
			}
			
		}
		/*
			for(d = 0; d < arr[c]; d++) {
				// REPLACE WITH HASH FUNCTION IN hashtry.cafter its complete
				if(strcmp(str, readdata(c, d)) == 0){// readdata() to read throught the data of individual keywords
					strcpy(que[qi].n[que[qi].val].key, str);
					que[qi].n[que[qi].val].type=c;
					que[qi].pat[que[qi].val]=c;
					break;
				}
			}
		}*/
		if(check ==0){// take care if word is not present in database
			printf("This word is out of my bounds of knowledge. Please help me understand it.")
			printf("Which category is the keyword");
			scanf("%c",&cat); 
			store(str,cat);
			// writefunc(cat,str); write writefunc in store for storing in txt
		}
		
	}while(d == 0)
}


int hashfunc1(char d){
	return (d-'A'-1)%26;
	
}

int search(char *str,int c ) {
	int h = hashfunc1(*str);
	hashnode *p = WordDatabase[c][h];
	while(p) {
		if(strcmp(p->key,str) == 0) {
			return 1;
		}
		p = p->next;
	}
	/* Not found */
	return  0;
}

int hashcom(){
	que[qi].
}
void store( char *str, int c) {
	int h, j;
	h = hashfunc1(*str);
	hashnode *d;
	d = (hashnode *)malloc(sizeof(hashnode));
	d->key= (char *)malloc(sizeof(char )*15);
	d->next = WordDatabase[c][h];// Could be chained at end to increase search speed as it may be the lowest used word in the chain
	WordDatabase[c][h]= d;
	// will have to rewrite the whole txt file containing database every time the program is the terminate to save changes in database
}

// when the base gets big \/
/*unsigned long hashstring(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; 

    return hash;
}*/



void analyze() {	
	info tmp;
	int score=0;
	int c=0;
	node* baseref;
	// CAN USE CONTEXT SEARCH WITH 
	if(searchcom()){//hash function for stored questions
		return; 
	}// THIS TAKES CARE OF THE STORED QUESTIONS and matching
	// depends on how the questions are stored ... handles sall the situations to chack whether an answer is to that set.
     // char presence in the sentence.. and checking if objects of the sentence are the same. and where the negation is present.GO in order of 
		//GO IN ORDER OF OBJECTS, ACTIONS, QUESTIONS, SYS, USR.
	for(i=0;i<9;i++){
		for (j=0;j< que[qi].val; j++){
			if (que[qi].pat[j]== i){
				if (c == 0) {
					baseref= node 		
			 
				
	
	 
	return; //pointer to info that has correct question.
}
int output( char* str){
	
	int c = 2, n, i;
	char ch;
	info *tmp;
	tmp = analyze();
	if (tmp!= NULL){
		c = 0;
		n = random()%MAXRESP;
		//if(info[i].val > 1) {	
				if(n==info[i].lind) {// to prevent output responses from repeating 
					
					n = (n + 1)%info[i].val; info[i].lind= n;
				}
		//	}
			printf("%s\n", info[i].responses[n]);
			if(i==2){// 2nd response space specially reserved for bye	
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
	while(i < strlen(str)){ 
		if(str[i] >= 'a' && str[i] <= 'z'){
			str[i] = str[i] - 22;
		}
	}
	return str;
	
}
char* puncrmv (char *str)// for removing basic punctuation.. can improve for spaces
{ 
	int i, j = 0;
	int size = strlen(str);
	char ch1; 
	for (i = 0; i < size; i++) {
     		 if (str[i] != ','&&str[i] != ';'&& str[i] != '.'&& str[i] != '!'&&str[i] != '?') {
        		 str[j] = str[i];
        		 j++;
     		}
  	}
  	if(str[j - 1]==' '){
		str[j] = '\0';
	}
}
int main() {
	while(1){
		
	







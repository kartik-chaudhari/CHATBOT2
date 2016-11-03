/*Copyright (C) Kartik Chaudhari <chaudhariks15.it@coep.ac.in> This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#define MAX_RESP 4
#define MAX 128
typedef struct {
	char *input;
	char *responses[MAX_RESP];
	int lastindex;
	int val;
}record;
typedef struct categ{
	char *key;
	int cat;
	struct categ *next;
}categ;

typedef struct {
	char *from;
	char *to;
} trans;
typedef struct wordnode{ 
	char* key;
	int cat;
	int index;
	struct wordnode *next;
} wordnode;
typedef struct categwords{
	wordnode *head;
	int length;
}categwords;
typedef struct rank{
	int cat;
	int index;
}rank;

categ catlist;
int find_match(char* input);
void UPPER( char *str );
char * insertspace(char * str);
char *stringreplace(char *str, char *orig, char *rep);
void input();
int output();
char * convert();
void inclink(rank temp1,rank temp2);
int categorize(char* str, wordnode* temp);
void printcateg(categwords temp);
wordnode* wordlearn(char *word);
char * trim(char *str);
int max(int j);
char *sInput,*sPreviousInput,*sResponse;
int nselection, baseno, prevnselection;
enum botstate {UNDER,NUNDER,PROGEND,REPEAT,NOINPUT,CONVER};
enum botstate state,prevstate;
enum ststate {ON,OFF};
enum ststate speechs;
enum keytyp { OBJ , ACTION , EMO , QUE , SYS, USR , NEGATE , JOIN , CONNECT };
enum inp {QUERY,QUESTION,STATEMENT,OBJDOM,ACTDOM,NONE};
enum inp inpstate; 
int WordDatasize[9];
char **points[9],*tempOut;
double sum[MAX*9]={0};
int a[MAX*9][MAX*9];
categwords categinput, categoutput, categprev;
record *KnowledgeBase;
categwords stack[16][2];// for previous question and ininput to understand if present is out of context.
trans conversion[] = {
	{" I'M ", " YOU'RE "},
	{" AM ", " ARE "},
	{" WERE ", " WAS "},
	{" ME ", " YOU "},
	{" YOURS ", " MINE "},
	{" YOUR ", " MY "},
	{" I'VE ", " YOU'VE "},
	{" I ", " YOU "},
	{" AREN'T ", " AM NOT "},
	{" WEREN'T ", " WASN'T " },
	{" I'D ", " YOU'D "},
	{" DAD ", " FATHER "},
	{" MOM ", " MOTHER "},
	{" DREAMS ", " DREAM "},
	{" MYSELF ", " YOURSELF "}
};
size_t nconv = sizeof(conversion) / sizeof(conversion[0]);

int nKnowledgeBaseSize;
/*void wordloader(){
	points[0] = objects;
	points[1] = actions;
	points[2] = emotions;
	points[3] = questions;
	points[4] = syst;
	points[5] = user;
	points[6] = negate;
	points[7] = join;
	points[8] = connectors;
	
}
*/
//for storing file functions
//************************************************************************************************************************


void wordfilewri() {
// for storing the words it collects in its dictionary categorically over different conversations	
	FILE *fp;
	fp = fopen("wordbase1.txt","w+");
	int i, j;

	for(i = 0; i < 9; i++)
		fprintf(fp,"%d ", WordDatasize[i]);
	for(i = 0; i < 9; i++)
		for(j = 0;j < WordDatasize[i]; j++){
			fprintf(fp,"%s ", points[i][j]);
			printf("%s ", points[i][j]);
		}
}



void wordfilere(){
// for reading the database every time the function is run
	FILE *fp;
	fp= fopen("wordbase1.txt","r");
	int i,j;
	for(i=0;i<9;i++){
		fscanf(fp,"%d ", &WordDatasize[i]);
	}
	for(i=0;i<9;i++){
		points[i]= (char ** )malloc(sizeof(char *));
		for(j=0;j<WordDatasize[i];j++){
			points[i][j]=(char * )malloc(sizeof(char )*15);
			fscanf(fp,"%s", points[i][j]);	
		}
	}
}



void Knowledgefileread(){
// for storing common sentences used in conversations that are very repetetive to give a high degree of accuracy and faster response time
	FILE *fp;  
	fp = fopen( "file1.txt" , "r" );
	int i,j;
	fscanf(fp,"%d\n",&nKnowledgeBaseSize);
	KnowledgeBase= (record *)malloc(sizeof(record)*nKnowledgeBaseSize);
	for(i = 0; i< nKnowledgeBaseSize;i++){
		fscanf(fp,"%d ",&KnowledgeBase[i].val );
		fscanf(fp,"%d ",&KnowledgeBase[i].lastindex );
		KnowledgeBase[i].input= (char *)malloc(sizeof(char)*64);
		fscanf(fp,"%[^\n]s\n",KnowledgeBase[i].input);
		fgetc(fp);
		for(j=0; j<KnowledgeBase[i].val;j++){
			KnowledgeBase[i].responses[j]= (char *)malloc(sizeof(char)*64);
			fscanf(fp,"%[^\n]s\n",KnowledgeBase[i].responses[j]);
			fgetc(fp);
		}
	}
	fclose(fp);
}



void matfilew() {
// for writing the matrix into a file everytime it is called
	FILE *fp;
	int i,j;
	fp= fopen("matrix.txt", "w+");
	for(i=0;i<MAX*9;i++)
		for(j=0;j<MAX*9; j++)
			fprintf(fp, "%d " , a[i][j]);
			
}


void matfiler() {
// for reading the matrix file every time to have a continuous flow of conversation
	FILE *fp;
	int i,j;
	fp= fopen("matrix.txt", "r");
	for(i=0;i<MAX*9;i++)
		for(j=0;j<MAX*9; j++)
			fscanf(fp, "%d " ,&a[i][j]);			
}



//*********************************************************************************************************************
void input(){
/* function responsible for the input of a file
	*trimming the input of excessive initial or terminal spaces
	*converting input into upper case to generalize operations on it
*/
	printf("\nUSER >");
    	fgets(sInput,30,stdin);
    	trim(sInput);
    	printf("\nBOT >");
    	UPPER(sInput);
}
void speech(char *str){
// responsible for voice while outputing
	if(speechs==ON){
	
		char temp[80];
		sprintf(temp,"espeak \"%s\"",str);
		system(temp);
	}
}
int output() {// FIX THE FIRST FEW NUMBERS AT SPECIFIC INPUTS LIKE SIGN ON AND NO INPUT TO MAKE IT EASIER TO HANDLE
	char *temp;
	if(strncmp(sPreviousInput, sInput,strlen(sInput)-1)==0){
		temp="Youre repeating yourself";
		speech(temp);
		printf("%s",temp);
		state= REPEAT;
		return 0;
	}
   	
    	else if ( baseno ==-1){
    		temp="I DONT UNDERSTAND";
    		speech(temp);
		printf("%s",temp);
    		state = NUNDER;
    		return 0;
    	}
    	else {
    		nselection= random()% KnowledgeBase[baseno].val;
    		if(KnowledgeBase[baseno].val >1){
    			if(nselection ==  KnowledgeBase[baseno].lastindex) 
    				nselection= (nselection + 1)%MAX_RESP;
    		}
    		KnowledgeBase[baseno].lastindex = nselection;
    		printf("%s", KnowledgeBase[baseno].responses[nselection]);
    		speech(KnowledgeBase[baseno].responses[nselection]);
    		strcpy(sPreviousInput,sInput);
    		state=UNDER;
    		return 0;
	}
}

int keyword(char* input, char *wrd)// THIS ACTS AS A TOKENIZER// do it using word by word scanning from beginning itself// or use strtok for this
{ 	
	static int i = 0;
	int c = 0;
	int prev;
	for(;i < strlen(input); i++){
		if(input[i] == ' '){
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
char * trim(char *str) {
	int beg=0, end;
	
	while(1){
		if(str[0]== ' '){
			str[0]='\0';
			str= &str[1];
		}
		else{ 
			break;
		}
	}
	end= strlen(str)-1;
	if(str[end]=='\n'){
		str[end]='\0';
		end--;
	}
	while(1){
		if(str[end]==' '){
			str[end]='\0';
			end--;
			
		}
		else {	
			break;
		}
	}
	return str;
}
void UPPER( char *str ) {
// for converting all input into upper case
	int len = strlen(str);
	//printf("%s\n",str);
	for( int i = 0; i < len; i++ ) {
		if ( str[i] >= 'a' && str[i] <= 'z' ) {
			str[i] -= 'a' - 'A';
		}
	}//printf("%s\n",str);
}

int find_match(char* input) {
//for finding a match in the strings of the most frequent stements passed
	int result=-1, len;
	len=strlen(input);
	char * temp1, *temp2, *temp3;
	temp3= (char *)malloc(sizeof(char)*300);
	temp2= insertspace(input);
	for(int i = 0; i < nKnowledgeBaseSize;  i++) { 
	    	temp1=insertspace(KnowledgeBase[i].input);
	    	if(strstr(temp2,temp1)!=NULL){
	    		if(strlen(temp1)>strlen(temp3)){
	    			strcpy(temp3,temp1);
	    			result =i;
   			
    			}
    		}
        	if(strncmp(KnowledgeBase[i].input,input,len-1)==0&& strlen(KnowledgeBase[i].input)==len-1) { 
	        	result =i; 
	        	return result;
	    	}
	}
	return result;
}

char * convert(){
	//for manipulation of string to convert from one user to system and vice versa
	char * newstr= (char *)malloc(sizeof(char)*45);
	int i;
	strcpy(newstr, sInput);
	for(i=0;i<nconv; i++) {
		newstr= insertspace(newstr);
		if(strstr(newstr,conversion[i].from)!= NULL) {
			newstr=stringreplace( newstr,conversion[i].from,conversion [i].to);// have to write string replace
			break;
		}
	}
	printf("%s\n",newstr);
	return newstr;
}


char *stringreplace(char *str, char *orig, char *rep){
// a normal string replace function
	static char buffer[4096];
	char *p;
    
	if(!(p = strstr(str, orig)))
	   	return str;
	printf("%s\n",p);
	strncpy(buffer, str, p-str);
	buffer[p-str] = '\0';
	printf("IN replace");
	sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));
	printf("%s",buffer);
	return buffer;
}
char * insertspace(char * str){
	int i;
	char temp;
	char * newstr= (char *)malloc(sizeof(char )*20);
	for(i=0;i<strlen(str);i++ ) {
		
		newstr[i+1]= str[i];
	}
	newstr[0]=' ';
	newstr[i+1]=' ';
	newstr[i+2]='\0';
	return newstr;
}


void printcateg(categwords temp) {
// for printing the whole list of words.
	wordnode *p = temp.head;
	while(p!= NULL){
		printf("%s ", p->key);
		p=p->next;
	}
}
void findavailable(){
/* for finding available options with highest summation value 
	*a new list is created containg the prospective outputs
	*/
	wordnode *p,*p1,*p2,*temp1;
	p = categinput.head;
	//temp1= (wordnode *)malloc(sizeof(wordnode));
	int index1, j, i, index2;
	printf("\n");
	while(p!= NULL) {
		index1 = p->cat*128 + p->index;
		for(j=0; j < MAX*9 ; j++){
			sum[j] += a[index1][j];
		}
		p = p->next;
	}
	p2= categoutput.head;
	for(j=0;j<9;j++){
		temp1= (wordnode *)malloc(sizeof(wordnode));
		
		if(j==0){
			 categoutput.head = temp1;
			 p2= temp1;
		}
		if(j>0){
			p2->next=temp1;
		}		
		index2 = max(j);
		temp1->index = index2;
		temp1->cat = j;
		temp1->key= (char *)malloc(sizeof(char )*15);
		temp1->next =NULL;
		strcpy(temp1->key,points[j][index2]);
		
	}
	printcateg(categoutput);
}
int categorize(char* str, wordnode* temp){
//a function used to categorize the word entered and return it back
	char cat;
	int c, d, n , k, check , j;
	static int e = 0;
	//printf("In categorize");
	for(c = 0; c < 9; c++) {// takes care if word is present in database
		for(j=0;j < WordDatasize[c];j++){
			if(strcmp(points[c][j],str)==0){
				temp->cat= c;
				temp->index= j;
				return c;
			}
		}
	}
	return -1;
}



void inputanalyze(){
/*creates a linked list from input string
	*  if the word is not present in database then , it callls the respective function
	*/
	char *word = (char*)malloc(sizeof(char)*15);
	int count=0,check=0;
	wordnode *p;
	int d=0,cat;
	while(1){
		wordnode *temp;
		temp = (wordnode *)malloc(sizeof(wordnode));
		d = keyword(sInput,word); 
		cat=categorize(word,temp);
		if(count == 0){
			categinput.head = temp;
			p = temp;
		}
		else 
			p->next= temp;
		if(cat ==-1){
			if(count == 0){
				free(temp);
				p= categinput.head = wordlearn(word);
				temp= p;
			}
			else	{
				p->next = wordlearn(word);
				temp= p->next; 
			}//MEANS THE WORD DOESNT EXIST IN DATABASE AND IS TO BE ADDED TO THE DATABASE WITH THE 
		}
		else{
			temp->key= (char *)malloc(sizeof(char)*15);
			temp->next =NULL;
			strcpy(temp->key,word);
		}
		count++ ;
		if(d == 1)
			break; 
		p = temp;
			
	}	
}

void inputstate() {
//to categorize given input on the basis of different structures of sentences (function not in use)
 
	wordnode *p;
	p = categinput.head;
	int c;
	inpstate= NONE;
	while(p!=NULL){
		if(p->cat== QUE ){
			c = 0;
			inpstate = QUE;
			break;
		}		
		else if(p->cat == JOIN) 
			c = 1;
		else if(c == 1 && (p->cat == USR||p->cat == SYS )){
			c = 0;
			inpstate = QUERY;
			break;
		}	
		else if(p->cat )
			printf("%d",inpstate);	
	}
}


void sentcat() {
// for creating output based on type of structure of sentence.(only one case handled here) 
	int i,flag;
	wordnode *p;
	p= categinput.head;
	char* temp= (char *)malloc(sizeof(char)*15);
	if( inpstate = QUE) {
		while(p!= NULL){// can hadle only yes /no questions
			if(p->cat== CONNECT && flag ==0 ){
				strcat( temp ,p->key );
				strcat(temp," ");
			}
			else if(p->cat == QUE)
				continue;
			else {
				flag=1;
				strcat(tempOut,p->key);
				strcat(tempOut ," ");
			}
		}
	// set structures of sentence in here		
	}
}

void addlink(){
//to create a link in the adjacency matrix between the words (function not in use)
	int h1, h2;
	wordnode *p, *p1;
	rank temp1, temp2;
	p1 = categinput.head;
	while(p1->next != NULL){
		temp1.index = p1->index;
		p = p1->next;
		temp1.cat= p1->cat;
		while (p != NULL){
			temp2.cat = p->cat;
			temp2.index = p->index;
			inclink(temp1,temp2);
			p=p->next;
		}
		p1= p1->next;	
	}
}


double costfunction(rank temp1, rank temp2, double sum1, double sum2) {
//for finding out how far given output is from desired output while training
	// calls in restructuring to adapt to desired output
	double temp;
	temp= (sum1-sum2)*(sum1-sum2);
	if(a[temp1.cat*128+ temp1.index][temp2.cat*128+ temp2.index]>0){
		//restruct(temp1 ,temp2);
	}
	else{
		inclink(temp1,temp2);
		//restruct(temp1,temp2);
	}
}



void inclink(rank temp1,rank temp2){
//presently chosen to be a linear function for a link in the adjacency matrix
	a[temp1.cat*128+ temp1.index][temp2.cat*128+ temp2.index]+=1;
	a[temp2.cat*128+ temp2.index][temp1.cat*128+ temp1.index]+=1;
}



wordnode* wordlearn(char *word){
/*function responsible for learning the new words.
	* it inputs the category
	* stores appropriately in struct
	*/
	int cat;
	wordnode *temp;
	printf("%s -> ", word);
	printf("This word is not within my knowledge bounds. Please help me understand it.\n");
	printf("what category does this word be long in\n");
	scanf("%d",&cat);
	while (1){
		if(cat > 8){
			printf("invalid index .please reenter category\n");
			scanf("%d",&cat);
		}
		else 
			break;
	}
	temp= (wordnode *)malloc(sizeof(wordnode));
	temp->cat= cat;
	temp->key= (char *)malloc(sizeof(char)*15);
	temp->index=WordDatasize[cat];
	temp->next =NULL;
	strcpy(temp->key,word);
	points[cat][WordDatasize[cat]]= (char *)malloc(sizeof(char)*15);
	strcpy(points[cat][WordDatasize[cat]],word);
	WordDatasize[cat]++;
	return temp;
}	



int max(int j) {
//for finding the maximum element in an array
	double max1;
	int indexmax=0, i;
	max1 = sum[ j*128];
	for(i = 0; i < 128; i++){
		if(max1 > sum[j*128 + i]) {
			indexmax = i;
			max1 = sum[j*128 + i];
		}
	}
	return indexmax;
}



void neuralinit(){
//for clearing the adjacenecy matrix of any present links
	int i, j;
	for(i = 0; i < MAX*9; i++){
		for(j = 0;j < MAX*9; j++) {
			a[i][j] = 0;
		}
	}	
}


int main(int argc, char *argv[]) {
	if(argc==2){
		if(strcmp(argv[1],"-l")==0){
			wordfilere();
			matfiler();
			while(1){
				printf("Please enter the sentence to be learned\n");
				sInput = (char*) malloc(sizeof(char)*45);
				fgets(sInput,45,stdin);
				UPPER(sInput);
				trim(sInput);
				if(strncmp(sInput, "END",3)==0) {
					matfilew();
					wordfilewri();
					return 0;	
				}
				inputanalyze();
				printcateg( categinput);
				addlink();
				printf("\nSUCCESSFULLY ADDED\n");
				getchar();
				free(sInput);
			}
		}
		if(strcmp(argv[1],"-h")==0){
			printf("Usage :./helpbot \n\t'-l' learning new statements. \n-ck to clear the adjacency matrix. ");
		}
		if(strcmp(argv[1],"-ck")==0){
			neuralinit();
			matfilew();
		}
		/*if(strcmp(argv[1],"-cw")==0){
			wordclear();
			matfilew();
		}*/
		
	}
	sInput=(char *)malloc(sizeof(char)*64);
	pthread_t thread1;
	sPreviousInput= (char *)malloc(sizeof(char)*64);
   // responses=(char *)malloc(sizeof(char)*30);
   	speechs =ON;
   	Knowledgefileread();
   	wordfilere();
   	matfiler();
   	state = NONE;
   	prevstate = NONE;
   	system("clear");
   	
	char *temp = "HI";
	speech(temp);
	printf("%s",temp);
	int randm;
	while(1){
		input();
	    	if (strcmp(sInput,"\0")==0) {
		
			temp = "DID I LEAVE YOU SPEECHLESS";
			speech(temp);
			printf("%s",temp);
			state=NOINPUT;
			continue;
		}
		else if(strncmp(sInput, "BYE",3)==0){
   			state = PROGEND;
   			matfilew();
			wordfilewri();
			temp="BYE";
			speech(temp);
			printf("%s",temp);
			return 0;
    		
    		}
		
		baseno = find_match(sInput);
	    	if(baseno ==-1){
	    		inputanalyze();
			findavailable();
			
	    		categprev.head= categoutput.head;// so that program does not loose context when dependent question is asked
	     	}	
	    	else 
	    		output();
	    	prevstate = state;
	    	if(state==PROGEND){
	    		matfilew();
			wordfilewri();
			return 0;
	    	}
    	}
}
	


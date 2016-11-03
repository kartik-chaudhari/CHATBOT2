#include<stdio.h>
int WordDatasize[9]={6,3,3,4,2,2,2,3,3};
char *objects[]= {"DUMMY","CAR","BOTTLE","PEN","MOVIES","BARS"};
char *actions[]={"CALCULATE", "PLAY","MUTE"};
char *emotions[]={"SAD","HAPPY","LIKE"};
char* questions[]={"WHAT","WHERE","WHY","HOW"};
char* syst[]={"YOU","YOUR"};
char * user[]={"MY","IM"};
char* negate[]={"DONT","NOT" };
char* join[] ={"AND","BECAUSE","OR"};
char *connectors[]={"IS", "ARE","WITH"};
char **points[9];

void wordloader(){
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
void wordfilewri(){
FILE *fp;
	fp= fopen("wordbase1.txt","w+");
	int i,j;
	wordloader();
	for(i=0;i<9;i++)
		fprintf(fp,"%d ", WordDatasize[i]);
	for(i=0;i<9;i++)
		for(j=0;j<WordDatasize[i];j++)
			fprintf(fp,"%s ", points[i][j]);			

}
int main() {
	wordfilewri();			
}

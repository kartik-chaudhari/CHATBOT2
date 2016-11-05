#include<stdio.h>
int WordDatasize[9]={6,5,4,5,3,3,3,4,4};
char *objects[]= {"DUMMY","CAR","BOTTLE","PEN","MOVIES","BARS"};
char *actions[]={"DUMMY","CALCULATE","BROWSER", "PLAY","MUTE"};
char *emotions[]={"DUMMY","SAD","HAPPY","LIKE"};
char* questions[]={"DUMMY","WHAT","WHERE","WHY","HOW"};
char* syst[]={"DUMMY","YOU","YOUR"};
char * user[]={"DUMMY","MY","IM"};
char* negate[]={"DUMMY","DONT","NOT" };
char* join[] ={"DUMMY","AND","BECAUSE","OR"};
char *connectors[]={"DUMMY","IS", "ARE","WITH"};
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

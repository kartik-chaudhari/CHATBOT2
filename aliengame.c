#include<stdio.h>
#include <stdlib.h>
#include"SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <SDL/SDL_ttf.h>
#define INUSE 1
#define AVAIL 0
int collision(SDL_Rect user);
int collidefind(SDL_Rect r1,SDL_Rect r2);
int number;
int LEVEL,ALIENMAX,ASTERMAX,BULLETMAX,HEALTH,SPEEDREF;
typedef struct item {
	SDL_Rect a;
	int usage;
	int speed;
} item;
item alien[4], asteroid[3], bullet[50];
int collision(SDL_Rect user) {
	int i = 0,n=0;
	while (i<ALIENMAX){
		n = collidefind(alien[i++].a,user);
		if(n == 0)
			return 1;
		}
	i=0;
	while (i<ASTERMAX){
		n = collidefind(asteroid[i++].a,user);
		if(n == 0)
			return 1;
		}
	i=0; 	
	while (i<BULLETMAX){
		n = collidefind(bullet[i++].a, user);
		if(n == 0)
			return 1;
		}
	i=0;
	return 0;
}
void objectinit(){
	int i=0;
	int i = 0,n=0;
	while (i<ALIENMAX){
		if(alien[i].a.y >= 700) 
			alien[i].a.y = 0;
			alien[i].speed= random%(LEVEL)+1;
		}
	i=0;
	while (i<ASTERMAX){
		if(asteroid[i].a.y >= 700) 
			asteroid[i].a.y = 0;
			asteroid[i].speed= random%(LEVEL)+1;
		}
	i=0; 	
	while (i<BULLETMAX){
		if(bullet[i].a.y >= 700) 
			// BULLET DISAPPEAR 
		}
	i=0;
		
int collidefind(SDL_Rect obj1, SDL_Rect obj2){
	int l1, r1, t1,b1;
	l1 = obj1.x; 
	r1 = obj1.x + obj1.w;
	t1 = obj1.y;
	b1 = obj1.y + obj1.h;

	int l2,r2,t2,b2;
	l2 = obj2.x; 
	r2 = obj2.x + obj2.w;
	t2 = obj2.y;
	b2 = obj2.y + obj2.h;

	if(t1 >= b2)
		return 1;
	else if(b1 <= t2)
		return 1;
	else if(l1 >= r2)
		return 1;
	else if(r1 <= l2)
		return 1; 
	else 
		return 0;
}



int main(int argc, char *argv[]) {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL error: %s\n", SDL_GetError());
		exit(1);
	}
	LEVEL =1
	SDL_Surface* screen = SDL_SetVideoMode(640,600,0,SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_Surface* user = SDL_LoadBMP("icon.bmp");
	SDL_Surface* alien1 = SDL_LoadBMP("img1.bmp");
	SDL_Surface* alien2 = SDL_LoadBMP("img2.bmp");
	SDL_Surface* asteroid3 = SDL_LoadBMP("img3.bmp");
	SDL_Surface* bgimage = SDL_LoadBMP("bg.bmp");
	SDL_SetColorKey(player,SDL_SRCCOLORKEY,SDL_MapRGB(player->format,0,0,0));
	SDL_SetColorKey(img1,SDL_SRCCOLORKEY,SDL_MapRGB(car1->format,255,255,255));
	SDL_SetColorKey(img2,SDL_SRCCOLORKEY,SDL_MapRGB(car2->format,255,255,255));
	SDL_SetColorKey(img3,SDL_SRCCOLORKEY,SDL_MapRGB(car3->format,255,255,255));
	SDL_WM_SetCaption("game",0);
	SDL_Event event;
	SDL_Rect usr;
	usr.x = 320;
	usr.y = 480;
	usr.w = user->w;
	usr.h = user->h;
	SDL_Rect bgdest;
	bgdest.x = 0;
	bgdest.y = -50;

	alien[1].a.y = 0;
	alien[1].a.w = alien1->w;
	alien[1].a.h = alien1->h;

	alien[2].a.y = 0;
	alien[2].a.w = alien2->w;
	alien[2].a.h = alien2->h;

	asteroid.a.y = 0;
	asteroid.a.w = asteroid3->w;
	asteroid.a.h = asteroid3->h;
	int v1=0,v2=0,v3=0;	
	int keyheld[323] = {0};
	while (1)
	{
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				SDL_Quit();
				exit(0);
			}
			if(event.type == SDL_KEYDOWN) {
				if(event.type == SDLK_ESCAPE) {
					SDL_Quit();
					exit(0);
				}
				else
					keyheld[event.key.keysym.sym] = 1;
			}
			if(event.type == SDL_KEYUP) {
					keyheld[event.key.keysym.sym] = 0;
			}
		}
		if(keyheld[SDLK_LEFT] == 1) {
			usr.x -= 1;
			if(usr.x<70)
				destination.x = 70; 				      	
		}
		if(keyheld[SDLK_RIGHT] == 1) {
			usr.x += 1;
			if((usr.x + user.w)>570) 
				usr.x = 570 - usr.w;
		}	
		if(destination1.y == 0) {
			destination1.x = rand1();
			v1 = rand2();
		}
		if(destination2.y == 0) {
			destination2.x = rand1();
			v2 = rand2();
		}
		if(destination3.y == 0) {
			destination3.x = rand1();
			v3 = rand2();
		}
		if(collision(usr))
			break;
		objectinit();
		gameplay();
		SCORE+=1; 
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(player,NULL, screen,&destination);
		SDL_BlitSurface(car1,NULL, screen,&destination1);
		SDL_BlitSurface(car2,NULL, screen,&destination2);
		SDL_BlitSurface(car3,NULL, screen,&destination3);
		SDL_Flip(screen);
		SDL_Delay(1);
	}
	SDL_FreeSurface(player);
	SDL_FreeSurface(bgimage);
	SDL_FreeSurface(car1);
	SDL_FreeSurface(car2);
	SDL_FreeSurface(car3);	
	SDL_Quit();
	return 0;
}

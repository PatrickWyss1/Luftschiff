/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <stdlib.h>
#include <ncurses.h>
#include "SIMPLESOCKET.H"
#include <SDL2/SDL.h>

using namespace std;

int main() {
	srand(time(nullptr));
	TCPclient c;
	string host = "";
	string msg,ch;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;
	SDL_Window* window = nullptr;

	window = SDL_CreateWindow("Test",0,0,640,480,SDL_WINDOW_SHOWN);

	//connect to host
	while(true){
		cout <<"IP-Adresse:"<<endl;
		cin >> host;
		if(c.conn(host , 2022)==true){
			break;
		}
	}

	bool run = 1;
	while(run){
		c.sendData("run\0");
		SDL_Event event;
		SDL_Delay(60);
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_KEYDOWN){
				/*
				cout <<"Key gedrückt!"<<endl;
				c.sendData("Key gedrückt!\0");
				*/
				if(event.key.keysym.sym == SDLK_0){
					cout <<"0 gedrückt!"<<endl;
					run = false;
				}
				switch(event.key.keysym.sym){
				case SDLK_w:
					c.sendData("w\0");
					break;
				case SDLK_a:
					c.sendData("a\0");
					break;
				case SDLK_d:
					c.sendData("d\0");
					break;
				case SDLK_UP:
					c.sendData("hoch\0");
					break;
				case SDLK_DOWN:
					c.sendData("runter\0");
					break;
				case SDLK_u:
					c.sendData("powerup\0");
					break;
				case SDLK_j:
					c.sendData("powerdown\0");
					break;
				case SDLK_SPACE:
					c.sendData("stopp\0");
					break;
				case SDLK_ESCAPE:
					c.sendData("BYEBYE\0");
					run =false;
					break;
				default:
					cout<<"Unknown Command!\n";
				}
			}
		}
		msg = c.receive(32);
		if(msg.compare("unknown")!= 0){
			cout<< msg << endl;
		}

	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	/*
	initscr();
	int i=0;
	bool goOn=1;
	noecho();
	while(goOn){ // send and receive data
		msg = string("hello\0");
		printw("\nclient sends: %s",msg.c_str());
		c.sendData(msg);
		i=getch();
		switch (i){
		case 119:
			msg = string("w\0");
			break;
		case 97:
			msg = string("a\0");
			break;
		case 100:
			msg = string("d\0");
			break;
		case 115:
			msg = string("s\0");
			break;
		case 56:
			msg =string("hoch\0");
			break;
		case 53:
			msg=string("runter\0");
			break;
		case 32:
			msg=string("stopp\0");
			break;
		case 42:
			msg = string("BYEBYE\0");
			goOn = 0;
			break;
		case 105:							//i
			msg=string("powerup\0");
			break;
		case 107:
			msg=string("powerdown\0");
			break;
		default :
			cout<<"\nUnknown Command!"<<endl;
			break;
		}

		printw("\nclient sends: %s",msg.c_str());
		//cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		printw("\ngot response: %s",msg.c_str());
		//cout << "got response:" << msg << endl;
	}
	endwin();
	sleep(2);
	*/
	 return 0;
}



#pragma once
#include "GameConstants.h"
#include "player.h"
#include "wall.h"
#include "cSoundMgr.h"
#include "rock.h"
#include <Windows.h>
#include <functional>

class gameScene
{
private:
	bool menu;
	bool replay;
	player* player1;
	player* player2;
	wall* spriteWall;
	cSoundMgr* theSoundMgr;
	int windowWidth;
	int windowHeight;
	std::function<void()> playButton;

public:
	gameScene();
	gameScene(player* P1, player* P2, wall* curWall, cSoundMgr* soundMgr, int winWid, int winHei, std::function<void()> playBut);
	~gameScene();
	
	//gameloop
	bool mainMenu();
	bool ReplyMenu();
	void checkPlayer();
	void setMain();
	void setReplay();

	//message loop 
	string getWinner();

};


#include "gameScene.h"

//default constructor not called
gameScene::gameScene()
{
}

//custome constructor containing the player and wall sprites, the soundMgr and the window sizes
gameScene::gameScene(player* P1, player* P2, wall* curWall, cSoundMgr* soundMgr, int winWid, int winHei)
{
	player1 = P1;
	player2 = P2;
	spriteWall = curWall;
	theSoundMgr = soundMgr;
	windowWidth = winWid;
	windowHeight = winHei;
	menu = true;
	replay = false;
}

//default constructor
gameScene::~gameScene()
{
}

//if true it will keep the main menu rendering in the main
bool gameScene::mainMenu()
{
	if (menu == true)
	{
		//show menu
		return true;
	}
	else
	{
		return false;
	}
}

//if true wil will keep rendering the replay menu rendering in the main
bool gameScene::ReplyMenu()
{
	if (replay == true)
	{
		//show menu
		return true;
	}
	else
	{
		return false;
	}
}

//this is the game loop and is checking for player throws and collisions 
void gameScene::checkPlayer()
{
	//do game stuff here
	//check the player 1 rock
	if (player1->getRockThrown() == true)
	{
		rock* TRock = player1->getRock();
		//lock the player position
		player1->setActive(false);
		//see if the rock has collided with the other player 
		if (TRock->collidedWith(TRock->getBoundingRect(), player2->getBoundingRect()))
		{
			//pixel collision
			if (TRock->pixelCheck(TRock, player2) == true)
			{
				//send player been hit message
				theSoundMgr->getSnd("hitPlayer")->playAudio(AL_TRUE);
				player2->messagePlayerHit(player1->getName());
				TRock->setActive(false);
				player1->setThrownRock(false);
				player2->setActive(true);
			}

		}
		//see if rock has collided with wall
		else if (TRock->collidedWith(TRock->getBoundingRect(), spriteWall->getBoundingRect()))
		{
			if (TRock->pixelCheck(TRock, spriteWall) == true)
			{
				//destroy rock 
				theSoundMgr->getSnd("hitWall")->playAudio(AL_TRUE);
				TRock->setActive(false);
				player1->setThrownRock(false);
				player2->setActive(true);
			}
		}
		//see if the rock has gone off screen
		else if (TRock->getSpritePos().y >= windowHeight + 100 || TRock->getSpritePos().x <= -100 || TRock->getSpritePos().x >= windowWidth + 100)
		{
			TRock->setActive(false);
			player1->setThrownRock(false);
			player2->setActive(true);
		}
	}
	else if (player2->getRockThrown() == true)
	{
		rock* TRock = player2->getRock();
		//lock the player position
		player2->setActive(false);
		//see if the rock has collided with the other player 
		if (TRock->collidedWith(TRock->getBoundingRect(), player1->getBoundingRect()))
		{
			if (TRock->pixelCheck(TRock, player1) == true)
			{
				//send player been hit message
				theSoundMgr->getSnd("hitPlayer")->playAudio(AL_TRUE);
				player1->messagePlayerHit(player2->getName());
				TRock->setActive(false);
				player2->setThrownRock(false);
				player1->setActive(true);
			}

		}
		//see if rock has collided with wall
		else if (TRock->collidedWith(TRock->getBoundingRect(), spriteWall->getBoundingRect()))
		{
			if (TRock->pixelCheck(TRock, spriteWall) == true)
			{
				//destroy rock 
				theSoundMgr->getSnd("hitWall")->playAudio(AL_TRUE);
				TRock->setActive(false);
				player2->setThrownRock(false);
				player1->setActive(true);
			}

		}
		//see if the rock has gone off screen
		else if (TRock->getSpritePos().y >= windowHeight + 100 || TRock->getSpritePos().x <= -100 || TRock->getSpritePos().x >= windowWidth + 100)
		{
			TRock->setActive(false);
			player2->setThrownRock(false);
			player1->setActive(true);
		}
	}
	//if either player is dead
	if (player1->getDead() == true || player2->getDead() == true)
	{
		//render the replay menu
		setReplay();
	}

}

//change the the bool main
void gameScene::setMain()
{
	if (menu == true)
	{
		menu = false;
	}
	else
	{
		menu = true;
	}
}

//change the bool replay
void gameScene::setReplay()
{
	if (replay == true)
	{
		replay = false;
	}
	else
	{
		replay = true;
	}
}

//return the winner in the replay menu
string gameScene::getWinner()
{
	if (player1->getDead() == true)
	{
		return player2->getName() + " is the winner! with a score of " + player1->getScore();
	}
	else if (player2->getDead() == true)
	{
		return player1->getName() + " is the winner! with a score of " + player2->getScore();
	}
	else
	{
		return "ERROR in winner";
	}
}
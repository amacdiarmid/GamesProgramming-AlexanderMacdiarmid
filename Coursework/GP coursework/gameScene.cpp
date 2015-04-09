#include "gameScene.h"

gameScene::gameScene()
{
}

gameScene::gameScene(player* P1, player* P2, wall* curWall, cSoundMgr* soundMgr, int winWid, int winHei, std::function<void()> playBut)
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

gameScene::~gameScene()
{
}

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

	if (player1->getDead() == true || player2->getDead() == true)
	{
		
		setReplay();
	}

}

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

string gameScene::getWinner()
{
	if (player1->getDead() == true)
	{
		return player2->getName() + " is the winner!";
	}
	else if (player2->getDead() == true)
	{
		return player1->getName() + " is the winner!";
	}
	else
	{
		return "ERROR in winner";
	}
}
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "player.h"
#include "wall.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	//main variables
	int difficulty = 1;
	LPCSTR wallToUse[] = { "Images\\wall texture easy.png", "Images\\wall texture medium.png", "Images\\wall texture hard.png" };

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
	const int windowBPP = 16;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	

    //The example OpenGL code
    windowOGL theOGLWnd;	

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails
        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	//create textures
	//background
	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\background.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

	//wall
	cTexture textureWall;
	textureWall.createTexture("Images\\wall texture easy.png");
	wall spriteWall;
	spriteWall.setSpritePos(glm::vec2((windowWidth / 2) - (textureWall.getTWidth() / 2), windowHeight - textureWall.getTHeight()));
	spriteWall.setTexture(textureWall.getTexture());
	spriteWall.setTextureDimensions(textureWall.getTWidth(), textureWall.getTHeight());
	spriteWall.setMdlRadius();

	//create textures	
	//player
	cTexture playerText;
	playerText.createTexture("Images\\man texture.png");

	//create player 1
	player player1 = player::player("alex");
	player1.attachInputMgr(theInputMgr);
	player1.setSpritePos(glm::vec2(windowWidth * 0.25, windowHeight - (playerText.getTHeight() / 2)));
	player1.setTexture(playerText.getTexture());
	player1.setTextureDimensions(playerText.getTWidth(), playerText.getTHeight());
	player1.setSpriteCentre();
	player1.attachArrowSprite();
	player1.setActive(true);
	player1.setMdlRadius();
	

	player player2 = player::player("not alex");
	player2.attachInputMgr(theInputMgr);
	player2.setSpritePos(glm::vec2(windowWidth * 0.75, windowHeight - (playerText.getTHeight() / 2)));
	player2.setTexture(playerText.getTexture());
	player2.setTextureDimensions(playerText.getTWidth(), playerText.getTHeight());
	player2.setSpriteCentre();
	player2.attachArrowSprite();
	player2.setActive(false);
	player2.setMdlRadius();
	
	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		spriteBkgd.render();

		spriteWall.update(elapsedTime);
		spriteWall.render();
		
		//player 1
		player1.update(elapsedTime);
		player1.render();

		//player 2
		player2.update(elapsedTime);
		player2.render();

		//do game stuff here
		//check the player 1 rock
		if (player1.getRockThrown() == true)
		{
			//lock the player position
			player1.setActive(false);
			//see if the rock has collided with the other player 
			if (player1.getRock().collidedWith(player1.getRock().getBoundingRect(), player2.getBoundingRect()))
			{
				//send player been hit message
				player2.messagePlayerHit(player1.getName());
				player1.getRock().setActive(false);
				player1.setThrownRock(false);
				player2.setActive(true);
			}
			//see if rock has collided with wall
			else if (player1.getRock().collidedWith(player1.getRock().getBoundingRect(), spriteWall.getBoundingRect()))
			{
				//destroy rock 
				player1.getRock().setActive(false);
				player1.setThrownRock(false);
				player2.setActive(true);
			}
			//see if the rock has gone off screen
			else if (player1.getRock().getSpritePos().y >= windowHeight+100 || player1.getRock().getSpritePos().x <= -100 || player1.getRock().getSpritePos().x >= windowWidth+100)
			{
				player1.getRock().setActive(false);
				player1.setThrownRock(false);
				player2.setActive(true);
			}
		}
		else if (player2.getRockThrown() == true)
		{
			//lock the player position
			player2.setActive(false);
			//see if the rock has collided with the other player 
			if (player2.getRock().collidedWith(player2.getRock().getBoundingRect(), player1.getBoundingRect()))
			{
				//send player been hit message
				player1.messagePlayerHit(player2.getName());
				player2.getRock().setActive(false);
				player2.setThrownRock(false);
				player1.setActive(true);
			}
			//see if rock has collided with wall
			else if (player2.getRock().collidedWith(player2.getRock().getBoundingRect(), spriteWall.getBoundingRect()))
			{
				//destroy rock 
				player2.getRock().setActive(false);
				player2.setThrownRock(false);
				player1.setActive(true);
			}
			//see if the rock has gone off screen
			else if (player2.getRock().getSpritePos().y >= windowHeight + 100 || player2.getRock().getSpritePos().x <= -100 || player2.getRock().getSpritePos().x >= windowWidth + 100)
			{
				player1.getRock().setActive(false);
				player2.setThrownRock(false);
				player1.setActive(true);
			}
		}

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

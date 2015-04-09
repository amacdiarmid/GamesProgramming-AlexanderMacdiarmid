#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "cBkGround.h"
#include "player.h"
#include "wall.h"
#include "gameScene.h"
#include "Button.h"
#include <functional>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
	
	//for debug
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
	const int windowBPP = 16;

    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

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

	//main variables
	int difficulty = 1;
	LPCSTR walls[] = { "Images\\wall texture easy.png", "Images\\wall texture medium.png", "Images\\wall texture hard.png" };
	LPCSTR fonts[] = { "Fonts\\micross.ttf" };
	LPCSTR sounds[] = { "Audio\\Kalimba", "Audio\\Rock on wall", "Audio\\bone break" };

	// Load Sound
	theSoundMgr->add("Theme", sounds[0]);
	theSoundMgr->add("hitWall", sounds[1]);
	theSoundMgr->add("hitPlayer", sounds[2]);
	theSoundMgr->getSnd("Theme")->playAudio(AL_TRUE);

	// Load Fonts
	theFontMgr->addFont("micross", fonts[0], 24);

	//create textures
	//create buttons
	//play button
	cTexture *playTxt = new cTexture();
	playTxt->createTexture("Images\\PlayButton.png");
	Button playButton;
	playButton.setSpritePos(glm::vec2(windowWidth / 2, windowHeight / 2));
	playButton.setTexture(playTxt->getTexture(), playTxt);
	playButton.setTextureDimensions(playTxt->getTWidth(), playTxt->getTHeight());
	playButton.attachInputMgr(theInputMgr);

	//Replay button
	cTexture *replayTxt = new cTexture();
	replayTxt->createTexture("Images\\ReplayButton.png");
	Button replayButton;
	replayButton.setSpritePos(glm::vec2(windowWidth / 2, windowHeight / 2));
	replayButton.setTexture(replayTxt->getTexture(), replayTxt);
	replayButton.setTextureDimensions(replayTxt->getTWidth(), replayTxt->getTHeight());
	replayButton.attachInputMgr(theInputMgr);

	//quit button
	cTexture *quitTxt = new cTexture();
	quitTxt->createTexture("Images\\QuitButton.png");
	Button quitButton;
	quitButton.setSpritePos(glm::vec2(windowWidth / 2, windowHeight / 2 + 40));
	quitButton.setTexture(quitTxt->getTexture(), quitTxt);
	quitButton.setTextureDimensions(quitTxt->getTWidth(), quitTxt->getTHeight());
	quitButton.attachInputMgr(theInputMgr);

	//background
	cTexture *textureBkgd = new cTexture();
	textureBkgd->createTexture("Images\\background.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(windowWidth / 2, windowHeight / 2));
	spriteBkgd.setTexture(textureBkgd->getTexture(), textureBkgd);
	spriteBkgd.setTextureDimensions(textureBkgd->getTWidth(), textureBkgd->getTHeight());

	//wall
	cTexture *textureWall = new cTexture();
	textureWall->createTexture("Images\\wall texture easy.png");
	wall spriteWall;
	spriteWall.setSpritePos(glm::vec2((windowWidth / 2), windowHeight - textureWall->getTHeight() / 2));
	spriteWall.setTexture(textureWall->getTexture(), textureWall);
	spriteWall.setTextureDimensions(textureWall->getTWidth(), textureWall->getTHeight());
	spriteWall.setMdlRadius();
	spriteWall.updateBoundingRect();

	//create textures	
	//player
	cTexture *playerText = new cTexture();
	playerText->createTexture("Images\\man texture.png");

	//create player 1
	player player1("player 1");
	player1.attachInputMgr(theInputMgr);
	player1.attachSoundMgr(theSoundMgr);
	player1.attatchFontmgr(theFontMgr);
	player1.setSpritePos(glm::vec2(windowWidth * 0.25, windowHeight - (playerText->getTHeight() / 2)));
	player1.setTexture(playerText->getTexture(), playerText);
	player1.setTextureDimensions(playerText->getTWidth(), playerText->getTHeight());
	player1.setSpriteCentre();
	player1.attachArrowSprite();
	player1.setActive(true);
	player1.setMdlRadius();
	player1.setLimits(0, (windowWidth / 2) - (textureWall->getTWidth() / 2));

	cTexture *playerText2 = new cTexture();
	playerText2->createTexture("Images\\man texture.png");
	player player2("player 2");
	player2.attachInputMgr(theInputMgr);
	player2.attachSoundMgr(theSoundMgr);
	player2.attatchFontmgr(theFontMgr);
	player2.setSpritePos(glm::vec2(windowWidth * 0.75, windowHeight - (playerText2->getTHeight() / 2)));
	player2.setTexture(playerText2->getTexture(), playerText2);
	player2.setTextureDimensions(playerText2->getTWidth(), playerText2->getTHeight());
	player2.setSpriteCentre();
	player2.attachArrowSprite();
	player2.setActive(false);
	player2.setMdlRadius();
	player2.setLimits((windowWidth / 2) + (textureWall->getTWidth() / 2), windowWidth);

	gameScene theGameMgr(&player1, &player2, &spriteWall, theSoundMgr, windowWidth, windowHeight, []() { cout << "test"; });
	
	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {

		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		spriteBkgd.render();

		

		if (theGameMgr.mainMenu() == true)
		{
			//show menu
			if (playButton.getPressed() == true)
			{
				theGameMgr.setMain();
			}
			else
			{
				playButton.update(elapsedTime);
				playButton.render();
			}
			
		}
		else if (theGameMgr.ReplyMenu() == true)
		{
			theFontMgr->getFont("micross")->printText(theGameMgr.getWinner().c_str(), FTPoint(400.0f, -45.0f, 0.0f));
			if (replayButton.getPressed() == true)
			{
				theGameMgr.setReplay();
				player1.reset();
				player2.reset();
			}
			else if (quitButton.getPressed() == true)
			{
				return 0;
			}
			else
			{
				replayButton.update(elapsedTime);
				replayButton.render();
			}
		}
		else
		{
			spriteWall.update(elapsedTime);
			spriteWall.render();
		
			//player 1
			player1.update(elapsedTime);
			player1.render();

			//player 2
			player2.update(elapsedTime);
			player2.render();

			theGameMgr.checkPlayer();

			theFontMgr->getFont("micross")->printText(player1.getInfo().c_str(), FTPoint(0.0f, -25.0f, 0.0f));
			theFontMgr->getFont("micross")->printText(player2.getInfo().c_str(), FTPoint(windowWidth - 410.0f, -25.0f, 0.0f));

		}	

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}

/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	wall(RectF::FromCenter(Graphics::GetScreenRect().GetCenter(), fieldWidth / 2.0f, fieldHeight / 2.0f),
		 wallThickness, wallColor),
	ball(Graphics::GetScreenRect().GetCenter(), Vec2(-0.5f, -1.0f)),
	pad(Vec2(400.0f, 550.0f), 32.0f, 6.0f),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav")
{
	const Vec2 gridTopLeft(wall.GetInnerBounds().left, wall.GetInnerBounds().top + topSpace);

	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = brickColors[y];
		for (int x = 0; x < nBricksCol; x++)
		{
			bricks[i] = Brick(RectF(gridTopLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), c);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	if (gameState == 1)
	{


		pad.Update(wnd.kbd, dt);
		pad.DoWallCollision(wall.GetInnerBounds());
		if (pad.CheckBallColision(ball))
		{
			pad.ExcuteBallCollision(ball);
			soundPad.Play();
		}

		ball.Update(dt);

		bool collisionHappened = false;
		float curColDistSq;
		int curColIndex;
		for (int i = 0; i < nBricks; i++)
		{
			if (bricks[i].CheckBallCollision(ball))
			{
				const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();
				if (collisionHappened)
				{
					if (newColDistSq < curColDistSq)
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
					}
				}
				else
				{
					curColDistSq = newColDistSq;
					curColIndex = i;
					collisionHappened = true;
				}
			}
		}

		if (collisionHappened)
		{
			bricks[curColIndex].ExcuteBallCollision(ball);
			soundBrick.Play();
			pad.ResetCooldown();
		}

		const int ballWallColResult = ball.DoWallcollision(wall.GetInnerBounds());
		if (ballWallColResult == 1)
		{
			soundPad.Play();
			pad.ResetCooldown();
		}
		else if (ballWallColResult == 2)
		{
			gameState = 2;
			isGameOver = true;
		}
	}
	else if (gameState == 0)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			StartRound();
		}
	}
	else if (gameState == 3)
	{
		// check to see if ready wait period is over
		if ((curWaitTime += dt) > readyWaitTime)
		{
			gameState = 1;
		}
	}
}

void Game::StartRound()
{
	curWaitTime = 0.0f;
	gameState = 3;
}

void Game::ComposeFrame()
{
	if (gameState == 1 || gameState == 3)
	{
		ball.Draw(gfx);
		pad.Draw(gfx);
	}

	if (gameState != 0)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		wall.Draw(gfx);
	}

	if (gameState == 0)
	{
		SpriteCodex::DrawTitle(Graphics::GetScreenRect().GetCenter(), gfx);
	}

	else if (gameState == 2)
	{
		SpriteCodex::DrawGameOver(Graphics::GetScreenRect().GetCenter(), gfx);
	}
}

/*******************************************************************************************
*
*   raylib - Simple Game template
*
*   Snaaaaake
*   Simple Snake Game
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------


void move_rectangle(Rectangle *rect, int screenWidth, int screenHeight){

  int x = GetRandomValue(20, screenWidth - 20);
  int y = GetRandomValue(20, screenHeight - 20);
  rect->x = x;
  rect->y = y;
}
//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int fontSize = 10;

    InitWindow(screenWidth, screenHeight, "Snaaaaake");

    // TODO: Initialize all required variables and load all required data here!
    int currentScore = 0;
    float speed = 1.0;

    Vector2 position = { (float) screenWidth / 2, (float) screenHeight / 2 };
    Vector2 velocity = { speed, 0 };
    float circleSize = 5.0;

    Rectangle targetSquare = {0, 0, 10, 10};
    move_rectangle(&targetSquare, screenWidth, screenHeight);

    bool gameOver = false;
    const char* gameOverText = "Game Over\nSpace to restart";
    int gameOverTextLength = MeasureText(gameOverText, fontSize * 2);

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        const char* scoreString = TextFormat("%d Points!", currentScore);
        int scoreStringLength = MeasureText(scoreString, fontSize);

        if(IsKeyDown(KEY_D)){
          velocity.x = speed;
          velocity.y = 0;
        }
        if(IsKeyDown(KEY_A)){
          velocity.x = -speed;
          velocity.y = 0;
        }
        if(IsKeyDown(KEY_W)){
          velocity.x = 0;
          velocity.y = -speed;
        }
        if(IsKeyDown(KEY_S)){
          velocity.x = 0;
          velocity.y = speed;
        }

        position.x = position.x + velocity.x;
        position.y = position.y + velocity.y;

        if(CheckCollisionCircleRec(position, circleSize, targetSquare)) {
          currentScore++;
          speed += 1;
          move_rectangle(&targetSquare, screenWidth, screenHeight);
        }

        if( position.x < 0 ||
            position.x > screenWidth ||
            position.y < 0 ||
            position.y > screenHeight){
          speed = 0;
          gameOver = true;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(position, circleSize, BLACK);
            DrawRectangleRec(targetSquare, RED);

            DrawText( scoreString,
                      (screenWidth - scoreStringLength) - 10,
                      10,
                      fontSize,
                      DARKPURPLE);

            if(gameOver){
              DrawText( gameOverText,
                        (screenWidth/2) - (gameOverTextLength/2),
                        screenHeight / 2,
                        fontSize * 2,
                        DARKPURPLE);

              if(IsKeyDown(KEY_SPACE)){
                currentScore = 0;
                speed = 1.0;
                position.x = (float) screenWidth / 2;
                position.y = (float) screenHeight / 2;
                velocity.x = speed;
                velocity.y = 0;
                move_rectangle(&targetSquare, screenWidth, screenHeight);
                gameOver = false;
              }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

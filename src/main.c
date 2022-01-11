/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

//compile:
//gcc  main.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm
#include <raylib.h>
//#include <math.h>
//#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Hex Game");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    //load textures
    Texture2D hex = LoadTexture("../assets/1-2hexW.png");

    //test color grid
    Color grid[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            grid[i][j].a = 50;
            grid[i][j].r = rand()%256;
            grid[i][j].g = rand()%256;
            grid[i][j].b = rand()%256;
        }

    
    // create camera
    Camera2D camera = {0}; 
    // set camera data
    float xTarget = 0;
    float yTarget = 0;
    camera.target = (Vector2){xTarget, yTarget};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;




    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // inpput
        if (IsKeyDown(KEY_RIGHT))
            xTarget++;
        if (IsKeyDown(KEY_LEFT))
            xTarget--;
        if (IsKeyDown(KEY_UP))
            yTarget--;
        if (IsKeyDown(KEY_DOWN))
            yTarget++;

        // camera adjust
        camera.target = (Vector2){xTarget, yTarget};

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                // spacing for a hex triplet: (0,0), (60,0), (30,49)
                for (int i = 0; i < 10; i++)
                    for (int j = 0; j < 10; j++){
                        DrawTexture(hex, ((60 * i) + (j * 30)), (49 * j), grid[i][j]);
                    }
            EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
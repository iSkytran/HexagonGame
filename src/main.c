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
#include <math.h>
#include <stdio.h>

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


    // create camera
    // set camera data

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawPixel(10, 10, BLACK);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
// add dev names
// add copyright info

//compile windows:
//gcc  main.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

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
    
    // create camera and set data 
    Camera2D camera = {0};
    float xTarget = screenWidth/2;
    float yTarget = screenHeight/2;
    camera.target = (Vector2){xTarget, yTarget};
    camera.offset = (Vector2){screenWidth/2, screenHeight/2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    // Main game loop
    while (!WindowShouldClose())
    {
        // inpput move camera (add arrow speed modifer)
        if (IsKeyDown(KEY_RIGHT))
            xTarget += 1 / camera.zoom;
        if (IsKeyDown(KEY_LEFT))
            xTarget -= 1 / camera.zoom;
        if (IsKeyDown(KEY_UP))
            yTarget -= 1 / camera.zoom;
        if (IsKeyDown(KEY_DOWN))
            yTarget += 1 / camera.zoom;

        // drag map (all zoom levels, no bounds)
        Vector2 mouseDeltaData = GetMouseDelta();
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            
            xTarget -= mouseDeltaData.x / camera.zoom;
            yTarget -= mouseDeltaData.y / camera.zoom;
        }

        // camera offset
        camera.offset = GetMousePosition();
        xTarget += mouseDeltaData.x/camera.zoom;
        yTarget += mouseDeltaData.y/camera.zoom;
        // change camera pos
        camera.target.x = xTarget;
        camera.target.y = yTarget;
        // zoom adjust
        camera.zoom *= powf(1.05f, GetMouseWheelMove());


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
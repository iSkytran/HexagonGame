// add dev names
// add copyright info

// compile windows:
// gcc  main.c -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Vector2 getHexCoords(Camera2D camera, Vector2 mousePositionData)
{
    // Convert raw mouse coords to overworld coords.
    Vector2 worldCoords = (Vector2){
        (camera.target.x + camera.offset.x - mousePositionData.x) / camera.zoom,
        (camera.target.y + camera.offset.y - mousePositionData.y) /
            camera.zoom};
    Vector2 hexCoords =
        (Vector2){floor(worldCoords.x / 60 - worldCoords.y / 30),
                  floor(worldCoords.y / 49)};
    printf("%lf and %lf and %lf\n", camera.zoom, hexCoords.x, hexCoords.y);
    return worldCoords;
}

int main(void)
{
    // Initialization
    // establish final minimum resolution
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Hex Game");
    SetWindowMinSize(screenWidth, screenHeight);
    SetTargetFPS(120);

    // load textures
    Texture2D hex = LoadTexture("../assets/1-2hexW.png");

    // test color grid
    Color grid[10][10];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            grid[i][j].a = 50;
            grid[i][j].r = rand() % 256;
            grid[i][j].g = rand() % 256;
            grid[i][j].b = rand() % 256;
        }

    // loop vars
    Vector2 mouseDeltaData = {};
    Vector2 mousePositionData = {};
    // create camera and set data
    Camera2D camera = {0};
    float xTarget = screenWidth / 2;  // deprecate for camera.target.x?
    float yTarget = screenHeight / 2; // deprecate for camera.target.y?
    camera.target = (Vector2){xTarget, yTarget};
    camera.offset = (Vector2){screenWidth / 2, screenHeight / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Main game loop
    while (!WindowShouldClose()) {
        // set varibles
        mouseDeltaData = GetMouseDelta();
        mousePositionData = GetMousePosition();

        // fullscreen toggle (change hotkeys)
        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) &&
            IsKeyPressed(KEY_SPACE)) {
            if (!IsWindowFullscreen()) {
                int display = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(display),
                              GetMonitorHeight(display));
                ToggleFullscreen();
            } else {
                ToggleFullscreen();
                SetWindowSize(screenWidth, screenHeight);
            }
        }

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
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {

            xTarget -= mouseDeltaData.x / camera.zoom;
            yTarget -= mouseDeltaData.y / camera.zoom;
        }

        // camera offset
        camera.offset = mousePositionData;
        xTarget += mouseDeltaData.x / camera.zoom;
        yTarget += mouseDeltaData.y / camera.zoom;
        // change camera pos
        camera.target.x = xTarget;
        camera.target.y = yTarget;
        // zoom adjust
        camera.zoom *= powf(1.05f, GetMouseWheelMove());

        getHexCoords(camera, mousePositionData);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        // spacing for a hex triplet: (0,0), (60,0), (30,49)
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++) {
                DrawTexture(hex, ((60 * i) + (j * 30)), (49 * j), grid[i][j]);
            }

        EndMode2D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}

#include <raylib.h>
#include <time.h>
#include <stdio.h>

int main(void){
    const int screenWidth = 400;
    const int screenHeight = 400;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "TimeC - Built with Raylib");

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        // Update
        char tmstr[25];
        time_t result = time(NULL);
        struct tm *lt;
        lt = localtime(&result);
        sprintf(tmstr, "%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(tmstr, 120, 185, 50, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseWindow();
    return 0;
}
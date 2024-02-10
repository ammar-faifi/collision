#include "raylib.h"
#include <stdlib.h>

#define BALL_NUM 100
#define BALL_RADIUS 5

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight,
             "raylib [shapes] example - bouncing ball");

  Vector2 balls_speed[BALL_NUM];
  Vector2 balls_position[BALL_NUM];

  srand(111);
  for (int i = 0; i < BALL_NUM; i++) {
    balls_speed[i].x = (float)rand() / RAND_MAX * 50.0f;
    balls_speed[i].y = (float)rand() / RAND_MAX * 50.0f;

    balls_position[i].x = (float)rand() / RAND_MAX * 100 + BALL_RADIUS;
    balls_position[i].y = (float)rand() / RAND_MAX * 100 + BALL_RADIUS;
  }

  bool pause = 0;
  int framesCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    if (IsKeyPressed(KEY_SPACE))
      pause = !pause;

    if (!pause) {
      for (int i = 0; i < BALL_NUM; i++) {
        balls_position[i].x += balls_speed[i].x * GetFrameTime();
        balls_position[i].y += balls_speed[i].y * GetFrameTime();

        // Check walls collision for bouncing
        if ((balls_position[i].x >= (GetScreenWidth() - 10 - BALL_RADIUS)) ||
            (balls_position[i].x <= BALL_RADIUS))
          balls_speed[i].x *= -1.0f;
        if ((balls_position[i].y >= (GetScreenHeight() - 10 - BALL_RADIUS)) ||
            (balls_position[i].y <= BALL_RADIUS))
          balls_speed[i].y *= -1.0f;
      }
    } else
      framesCounter++;

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int i = 0; i < BALL_NUM; i++) {
      DrawCircleV(balls_position[i], (float)BALL_RADIUS, MAROON);
    }

    // On pause, we draw a blinking message
    if (pause && ((framesCounter / 30) % 2))
      DrawText("PAUSED", 350, 200, 30, GRAY);

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
  return EXIT_SUCCESS;
}

#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

#define BALL_NUM 10
#define BALL_RADIUS 40

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight,
             "raylib [shapes] example - bouncing ball");

  Vector2 balls_speed[BALL_NUM];
  Vector2 balls_position[BALL_NUM];
  Vector2 accel = {0.f, 200.0f};

  srand(time(NULL));
  for (int i = 0; i < BALL_NUM; i++) {
    balls_speed[i].x = (float)rand() / RAND_MAX * 200.0f;
    balls_speed[i].y = (float)rand() / RAND_MAX * 200.0f;

    balls_position[i].x = (float)rand() / RAND_MAX * 800 + BALL_RADIUS;
    balls_position[i].y = (float)rand() / RAND_MAX * 500 + BALL_RADIUS;
  }

  bool pause = 0;
  int framesCounter = 0;

  SetTargetFPS(100);

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    if (IsKeyPressed(KEY_SPACE))
      pause = !pause;

    if (!pause) {
      for (int i = 0; i < BALL_NUM; i++) {
        // apply acceleration
        balls_speed[i].x += accel.x * GetFrameTime();
        balls_speed[i].y += accel.y * GetFrameTime();

        balls_position[i].x += balls_speed[i].x * GetFrameTime();
        balls_position[i].y += balls_speed[i].y * GetFrameTime();

        // Check walls collision for bouncing
        if ((balls_position[i].x >= (GetScreenWidth() - 10 - BALL_RADIUS)) ||
            (balls_position[i].x <= BALL_RADIUS))
          balls_speed[i].x *= -1.0f;
        if ((balls_position[i].y >= (GetScreenHeight() - 10 - BALL_RADIUS)) ||
            (balls_position[i].y <= BALL_RADIUS))
          balls_speed[i].y *= -1.0f;
        for (int j = i; j < BALL_NUM; j++) {
          if (CheckCollisionCircles(balls_position[i], BALL_RADIUS,
                                    balls_position[j], BALL_RADIUS)) {
            Vector2 tmp = balls_speed[i];
            balls_speed[i] = balls_speed[j];
            balls_speed[j] = tmp;

            // seprate the two intersect circles
            float overlap =
                2 * BALL_RADIUS -
                Vector2Distance(balls_position[j], balls_position[i]);
            Vector2 normal = Vector2Normalize(
                Vector2Subtract(balls_position[j], balls_position[i]));
            normal = Vector2Scale(normal, overlap / 2);

            balls_position[i] = Vector2Subtract(balls_position[i], normal);
            balls_position[j] = Vector2Add(balls_position[j], normal);
          }
        }
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

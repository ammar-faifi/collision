#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BALL_NUM 500
#define BALL_RADIUS 10
#define SUBSTEPS 60

int main(void) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib - particles collision");

  Vector2 ballsSpeed[BALL_NUM];
  Vector2 ballsPosition[BALL_NUM];
  Color ballsColor[BALL_NUM];
  Vector2 accel = {0.0f, 500.0f};

  srand(time(NULL));
  for (int i = 0; i < BALL_NUM; i++) {
    ballsSpeed[i] =
        (Vector2){GetRandomValue(100, 200), GetRandomValue(100, 200)};
    ballsPosition[i] =
        (Vector2){GetRandomValue(BALL_RADIUS, SCREEN_WIDTH - BALL_RADIUS),
                  GetRandomValue(BALL_RADIUS, SCREEN_HEIGHT - BALL_RADIUS)};
    ballsColor[i] = ColorFromHSV(GetRandomValue(0, 360), 0.5f, 0.7f);
  }

  bool pause = false;
  int framesCounter = 0;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE))
      pause = !pause;

    if (!pause) {
      float dt = GetFrameTime() / SUBSTEPS;

      for (int step = 0; step < SUBSTEPS; step++) {
        for (int i = 0; i < BALL_NUM; i++) {
          // ballsSpeed[i].x += accel.x * dt;
          // ballsSpeed[i].y += accel.y * dt;

          ballsPosition[i].x += ballsSpeed[i].x * dt + accel.x * dt * dt * 0.5f;
          ballsPosition[i].y += ballsSpeed[i].y * dt + accel.y * dt * dt * 0.5f;

          // Check walls collision for bouncing
          if (ballsPosition[i].x >= (GetScreenWidth() - BALL_RADIUS)) {
            ballsPosition[i].x = GetScreenWidth() - BALL_RADIUS;
            // ballsSpeed[i].x *= -0.0f;
          }
          if (ballsPosition[i].x <= BALL_RADIUS) {
            ballsPosition[i].x = BALL_RADIUS;
            // ballsSpeed[i].x *= -0.0f;
          }

          if (ballsPosition[i].y >= (GetScreenHeight() - BALL_RADIUS)) {
            ballsPosition[i].y = GetScreenHeight() - BALL_RADIUS;
            // ballsSpeed[i].y *= -0.0f;
          }
          if (ballsPosition[i].y <= BALL_RADIUS) {
            ballsPosition[i].y = BALL_RADIUS;
            // ballsSpeed[i].y *= -0.0f;
          }

          for (int j = i; j < BALL_NUM; j++) {
            if (i != j &&
                CheckCollisionCircles(ballsPosition[i], BALL_RADIUS,
                                      ballsPosition[j], BALL_RADIUS)) {
              // Vector2 tmp = ballsSpeed[i];
              // ballsSpeed[i] = ballsSpeed[j];
              // ballsSpeed[j] = tmp;

              // Separate the two intersecting circles
              Vector2 normal = Vector2Normalize(
                  Vector2Subtract(ballsPosition[j], ballsPosition[i]));
              float overlap =
                  2 * BALL_RADIUS -
                  Vector2Distance(ballsPosition[j], ballsPosition[i]);
              normal = Vector2Scale(normal, overlap / 2);

              ballsPosition[i] = Vector2Subtract(ballsPosition[i], normal);
              ballsPosition[j] = Vector2Add(ballsPosition[j], normal);
            }
          }
        }
      }
    } else {
      framesCounter++;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < BALL_NUM; i++) {
      DrawCircleV(ballsPosition[i], (float)BALL_RADIUS, ballsColor[i]);
    }

    // On pause, draw a blinking message
    if (pause && ((framesCounter / 30) % 2))
      DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 30) / 2,
               SCREEN_HEIGHT / 2 - 15, 30, GRAY);

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
  return EXIT_SUCCESS;
}

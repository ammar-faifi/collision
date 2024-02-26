#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BALL_NUM 1000
#define BALL_RADIUS 4
#define SUBSTEPS 40

int main(void) {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib - particles collision");

  Vector2 ballsPos[BALL_NUM];
  Vector2 ballsVel[BALL_NUM];
  Vector2 ballsAcc[BALL_NUM] = {0.0f, 0.0f};
  Color ballsColor[BALL_NUM];
  Vector2 gravity = {0.0f, 500.0f};

  srand(time(NULL));
  for (int i = 0; i < BALL_NUM; i++) {
    ballsVel[i] = (Vector2){GetRandomValue(100, 200), GetRandomValue(10, 100)};
    ballsPos[i] =
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
          // Update position
          ballsPos[i].x += ballsVel[i].x * dt + ballsAcc[i].x * dt * dt * 0.5f;
          ballsPos[i].y += ballsVel[i].y * dt + ballsAcc[i].y * dt * dt * 0.5f;

          // Update acceleration
          ballsAcc[i].x = gravity.x;
          ballsAcc[i].y = gravity.y;

          // Update velocity
          ballsVel[i].x += gravity.x * dt;
          ballsVel[i].y += gravity.y * dt;

          // Check walls collision for bouncing
          if (ballsPos[i].x >= (GetScreenWidth() - BALL_RADIUS)) {
            ballsPos[i].x = GetScreenWidth() - BALL_RADIUS;
            ballsVel[i].x = 0.0f;
          }
          if (ballsPos[i].x <= BALL_RADIUS) {
            ballsPos[i].x = BALL_RADIUS;
            ballsVel[i].x = 0.0f;
          }

          if (ballsPos[i].y >= (GetScreenHeight() - BALL_RADIUS)) {
            ballsPos[i].y = GetScreenHeight() - BALL_RADIUS;
            ballsVel[i].y = 0.0f;
          }
          if (ballsPos[i].y <= BALL_RADIUS) {
            ballsPos[i].y = BALL_RADIUS;
            ballsVel[i].y = 0.0f;
          }

          for (int j = i; j < BALL_NUM; j++) {
            if (i != j && CheckCollisionCircles(ballsPos[i], BALL_RADIUS,
                                                ballsPos[j], BALL_RADIUS)) {
              Vector2 tmp = ballsVel[i];
              ballsVel[i] = ballsVel[j];
              ballsVel[j] = tmp;

              // Separate the two intersecting circles
              Vector2 normal =
                  Vector2Normalize(Vector2Subtract(ballsPos[j], ballsPos[i]));
              float overlap =
                  2 * BALL_RADIUS - Vector2Distance(ballsPos[j], ballsPos[i]);
              normal = Vector2Scale(normal, overlap / 2);

              ballsPos[i] = Vector2Subtract(ballsPos[i], normal);
              ballsPos[j] = Vector2Add(ballsPos[j], normal);
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
      DrawCircleV(ballsPos[i], (float)BALL_RADIUS, ballsColor[i]);
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

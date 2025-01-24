#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

#define SCREEN_WIDTH 1080 / 2
#define SCREEN_HEIGHT 1920 / 2
#define CIRC_RADIUS 8
#define CIRC_NUM 2000
#define SUB_STEPS 30

int draw_limit;
int frames_counter;

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My collision sim");
  SetTargetFPS(60);

  Vector2 gravity = {0.f, 1000.f};
  Vector2 circPos[CIRC_NUM];
  Vector2 circVel[CIRC_NUM];
  Vector2 circAcc[CIRC_NUM] = {{gravity.x, gravity.y}};
  Color circColor[CIRC_NUM];

  for (int i = 0; i < CIRC_NUM; i++) {
    circPos[i] = (Vector2){GetRandomValue(4 * CIRC_RADIUS, 10 * CIRC_RADIUS),
                           CIRC_RADIUS * 10};
    circVel[i] = (Vector2){GetRandomValue(200, 300), GetRandomValue(1, 100)};
    circColor[i] = ColorFromHSV(GetRandomValue(0, 360), 0.5f, 0.7f);
  }

  while (!WindowShouldClose()) {

    if (draw_limit < CIRC_NUM && frames_counter % 4)
      draw_limit++;

    float dt = GetFrameTime() / SUB_STEPS;

    for (int step = 0; step < SUB_STEPS; step++) {
      for (int i = 0; i < draw_limit; i++) {
        // Update Positions
        circPos[i].x += circVel[i].x * dt + circAcc[i].x * dt * dt * 0.5f;
        circPos[i].y += circVel[i].y * dt + circAcc[i].y * dt * dt * 0.5f;

        // Update Vellocities
        circVel[i].x += gravity.x * dt;
        circVel[i].y += gravity.y * dt;

        // Check walls collision for bouncing
        if (circPos[i].x >= GetScreenWidth() - CIRC_RADIUS) {
          circPos[i].x = GetScreenWidth() - CIRC_RADIUS;
          circVel[i].x = circVel[i].x * 0.6f;
        } else if (circPos[i].x < CIRC_RADIUS) {
          circPos[i].x = CIRC_RADIUS;
          circVel[i].x = 0.f;
        }

        if (circPos[i].y >= GetScreenHeight() - CIRC_RADIUS) {
          circPos[i].y = GetScreenHeight() - CIRC_RADIUS;
          circVel[i].y = -0.6f * circVel[i].y;
        } else if (circPos[i].y < CIRC_RADIUS) {
          circPos[i].y = CIRC_RADIUS;
          circVel[i].y = 0.f;
        }

        // Check and solve collision
        for (int j = i; j < draw_limit; j++) {
          if (i != j && CheckCollisionCircles(circPos[i], CIRC_RADIUS,
                                              circPos[j], CIRC_RADIUS)) {
            Vector2 tmp = circVel[i];
            circVel[i] = circVel[j];
            circVel[j] = tmp;

            // Separate the two intersecting circles
            Vector2 normal =
                Vector2Normalize(Vector2Subtract(circPos[j], circPos[i]));
            float overlap =
                2.f * CIRC_RADIUS - Vector2Distance(circPos[j], circPos[i]);
            normal = Vector2Scale(normal, overlap / 2.f);

            circPos[i] = Vector2Subtract(circPos[i], normal);
            circPos[j] = Vector2Add(circPos[j], normal);
          }
        }
      }
    }

    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < draw_limit; i++) {
      DrawCircleV(circPos[i], CIRC_RADIUS, circColor[i]);
    }

    DrawFPS(10, 10);
    EndDrawing();
    frames_counter++;
  }

  CloseWindow();
  return EXIT_SUCCESS;
}

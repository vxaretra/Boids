#include <vector>

#include "config.h"
#include "flock.h"

int main()
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boids Simulation");


  Flock flock(75);

  while (!WindowShouldClose())
  {
    flock.update();

    BeginDrawing();
    ClearBackground(WHITE);
    DrawFPS(0, 0);

    flock.draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

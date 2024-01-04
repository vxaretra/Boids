#pragma once

#include "raylib.h"
#include "raymath.h"

class Boid
{
public:
  Boid();
  Boid(Vector2 position, Vector2 velocity, float speed, Color color);

  Vector2 getPosition();
  Vector2 getVelocity();
  void setVelocity(Vector2 velocity);

  void update();
  void draw();

  ~Boid() = default;

  int id;

private:
  Vector2 position;
  Vector2 velocity;
  float size;
  float speed;
  Color color;
  static int counter;
};

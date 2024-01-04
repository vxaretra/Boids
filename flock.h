#pragma once

#include <vector>

#include "boid.h"

class Flock
{
public:
  Flock();
  Flock(int count);
  ~Flock() = default;

  void update();
  void draw();
  void separate(Boid& currentBoid);
  void align(Boid& currentBoid);
  void cohere(Boid& currentBoid);
  std::vector<Boid>& getBoids();

private:
  std::vector<Boid> boids;
  float neighborDistance = 60.0f;
  float separateMultiplier = 0.05f;
  float alignMultiplier = 0.03f;
  float cohereMultiplier = 0.02f;
};

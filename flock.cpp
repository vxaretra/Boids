#include "Flock.h"

#include "config.h"

Flock::Flock()
{
  for (int i = 0; i < NUM_OF_BOIDS; i++)
  {
    Boid boid = {
      { SCREEN_CENTER_X, SCREEN_CENTER_Y },
      Vector2Normalize({ (float)GetRandomValue(-800, 800), (float)GetRandomValue(-800, 800) }),
      (float)GetRandomValue(100, 300),
      MAROON
    };

    this->boids.push_back(boid);
  }
  //for (int i = 0; i < 50; i++)
  //{
  //  boids[i] = Boid(
  //    { SCREEN_CENTER_X, SCREEN_CENTER_Y },
  //    Vector2Normalize({ (float)GetRandomValue(-800, 800), (float)GetRandomValue(-800, 800) }),
  //    (float)GetRandomValue(100, 300),
  //    MAROON
  //  );
  //}
}

Flock::Flock(int count)
{
  for (int i = 0; i < count; i++)
  {
    Boid boid = {
      { SCREEN_CENTER_X, SCREEN_CENTER_Y },
      Vector2Normalize({ (float)GetRandomValue(-800, 800), (float)GetRandomValue(-800, 800) }),
      (float)GetRandomValue(100, 300),
      MAROON
    };

    this->boids.push_back(boid);
  }
}

void Flock::update()
{
  for (Boid& boid : boids)
  {
    separate(boid);
    align(boid);
    cohere(boid);
  }

  for (Boid& boid : boids)
  {
    boid.update();
  }
}

void Flock::draw()
{
  for (Boid& boid : boids)
  {
    boid.draw();
  }
}

void Flock::separate(Boid& currentBoid)
{
  Vector2 totalSeparation = Vector2Zero();
  Vector2 currentPosition = currentBoid.getPosition();

  for (Boid& other : this->boids)
  {
    if (currentBoid.id == other.id) continue;

    Vector2 otherPosition = other.getPosition();
    if (Vector2Distance(currentPosition, otherPosition) > this->neighborDistance) continue;

    totalSeparation.x += currentPosition.x - otherPosition.x;
    totalSeparation.y += currentPosition.y - otherPosition.y;
  }

  totalSeparation = Vector2Scale(totalSeparation, this->separateMultiplier);
  currentBoid.setVelocity(Vector2Add(currentBoid.getVelocity(), totalSeparation));
}

void Flock::align(Boid& currentBoid)
{
  Vector2 totalAlignment = Vector2Zero();
  int totalNeighbours = 0;
  Vector2 currentPosition = currentBoid.getPosition();

  for (Boid& other : this->boids)
  {
    if (currentBoid.id == other.id) continue;

    Vector2 otherPosition = other.getPosition();
    if (Vector2Distance(currentPosition, otherPosition) > this->neighborDistance) continue;

    totalNeighbours++;
    totalAlignment = Vector2Add(totalAlignment, other.getVelocity());
  }

  if (totalNeighbours == 0) return;

  totalAlignment = Vector2Scale(totalAlignment, 1.0f / totalNeighbours);
  totalAlignment = Vector2Scale(Vector2Subtract(totalAlignment, currentBoid.getVelocity()), this->alignMultiplier);
  currentBoid.setVelocity(Vector2Add(currentBoid.getVelocity(), totalAlignment));
}

void Flock::cohere(Boid& currentBoid)
{
  Vector2 totalCohesion = Vector2Zero();
  int totalNeighbours = 0;
  Vector2 currentPosition = currentBoid.getPosition();

  for (Boid& other : this->boids)
  {
    if (currentBoid.id == other.id) continue;

    Vector2 otherPosition = other.getPosition();
    if (Vector2Distance(currentPosition, otherPosition) > this->neighborDistance) continue;

    totalNeighbours++;
    totalCohesion = Vector2Add(totalCohesion, otherPosition);
  }

  if (totalNeighbours == 0) return;

  totalCohesion = Vector2Scale(totalCohesion, 1.0f / totalNeighbours);
  totalCohesion = Vector2Scale(Vector2Subtract(totalCohesion, currentPosition), this->cohereMultiplier);
  currentBoid.setVelocity(Vector2Add(currentBoid.getVelocity(), totalCohesion));
}

std::vector<Boid>& Flock::getBoids()
{
  return this->boids;
}

#include "boid.h"
#include "raymath.h"

#include "config.h"

int Boid::counter = 0;

Boid::Boid()
{
  this->id = ++counter;
  this->position = Vector2Zero();
  this->velocity = Vector2Zero();
  this->size = 20;
  this->speed = 100;
  this->color = BLACK;
}

Boid::Boid(Vector2 position, Vector2 velocity, float speed, Color color)
{
  this->id = ++counter;
  this->position = position;
  this->velocity = velocity;
  this->size = 20;
  this->speed = speed;
  this->color = color;
}

Vector2 Boid::getPosition()
{
  return this->position;
}

Vector2 Boid::getVelocity()
{
  return this->velocity;
}

void Boid::setVelocity(Vector2 velocity)
{
  this->velocity = velocity;
  return;
}

void Boid::update()
{
  if (this->position.x < 0)
  {
    this->velocity.x += 4.0f;
  }
  if (this->position.x > SCREEN_WIDTH)
  {
    this->velocity.x -= 4.0f;
  }
  if (this->position.y < 0)
  {
    this->velocity.y += 4.0f;
  }
  if (this->position.y > SCREEN_HEIGHT)
  {
    this->velocity.y -= 4.0f;
  }

  this->velocity = Vector2ClampValue(this->velocity, 400.0f, 1000.0f);
  this->position = Vector2Add(this->position, Vector2Scale(this->velocity, GetFrameTime()));

  return;
}

void Boid::draw()
{
  float angle = atan2f(-this->velocity.y, this->velocity.x);
  DrawPoly(this->position, 3, this->size, angle * RAD2DEG - 30, this->color);
  DrawCircle((int)this->position.x + (int)(this->size * cos(angle)), (int)this->position.y + (int)(this->size * -sin(angle)), 10.f, ORANGE);

  return;
}

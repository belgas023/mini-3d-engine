#include "cmath"
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

Vector3 vertices[8]{
    {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1},

    {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1},
};

int edges[12][2]{
    {0, 1}, {1, 2}, {2, 3}, {3, 0},

    {4, 5}, {5, 6}, {6, 7}, {7, 4},

    {0, 4}, {1, 5}, {2, 6}, {3, 7},
};

Vector3 rotationSin(Vector3 vertex, float angle) {

  Vector3 positionPostRotationXaxis = {
      vertex.x, vertex.z * sinf(angle) + vertex.y * cosf(angle),
      vertex.z * cosf(angle) - vertex.y * sinf(angle)};

  vertex = positionPostRotationXaxis;

  Vector3 positionPostRotationYaxis = {
      vertex.x * cosf(angle) - vertex.z * sinf(angle), vertex.y,
      vertex.x * sinf(angle) + vertex.z * cosf(angle)};

  vertex = positionPostRotationYaxis;

  Vector3 positionPostRotationZaxis = {
      vertex.x * cosf(angle) - vertex.y * sinf(angle),
      vertex.x * sinf(angle) + vertex.y * cosf(angle), vertex.z};

  vertex = positionPostRotationZaxis;

  return vertex;
};

Vector3 project(Vector3 vertex, float angle) {
  // 1. rotation
  // vertex = rotationSin(vertex, angle);

  // 2. z translation
  int distance = 3;
  vertex.z += distance;

  // 3. perspective
  float focal = 200.0f;
  vertex = {vertex.x * focal / vertex.z, vertex.y * focal / vertex.z, vertex.z};

  // 4. scaled
  vertex = {vertex.x + screenWidth / 2.0f, vertex.y + screenHeight / 2.0f,
            vertex.z};

  return vertex;
};

int main(void) {

  InitWindow(screenWidth, screenHeight, "Test raylib");

  SetTargetFPS(60);
  float power = 0.0;

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground({84, 84, 84});
    // std::cout << GetTime() << "\n";

    // vertices loop
    for (int i = 0; i < 8; i++) {
      float angle = GetTime();
      Vector3 vertex = project(vertices[i], power);

      DrawCircle(vertex.x, vertex.y, 3, GREEN);
    };

    // edges loop
    for (int i = 0; i < 12; i++) {
      float angle = GetTime();
      Vector3 vertexA = project(vertices[edges[i][0]], angle);
      Vector3 vertexB = project(vertices[edges[i][1]], angle);

      DrawLine(vertexA.x, vertexA.y, vertexB.x, vertexB.y, GREEN);
    };

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

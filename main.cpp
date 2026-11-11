#include "cmath"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 450;

// Vector3 vertices[8]{
//     {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1},
//
//     {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1},
// };

// std::vector auto manage memory
// + relative to size (.size())
// std::vector<Vector3> vertices{
//    {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1},
//
//    {1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1},
//
//};

// struct Object {
// 	std::vector<Vector3> vertices;
// 	std::vector<std::vector<int>> edges;
// };

int edges[12][2]{
    {0, 1}, {1, 2}, {2, 3}, {3, 0},

    {4, 5}, {5, 6}, {6, 7}, {7, 4},

    {0, 4}, {1, 5}, {2, 6}, {3, 7},
};

std::vector<Vector3> loadObj(string filename) {
  std::vector<Vector3> vertices;
  ifstream inputFile(filename);
  string line;

  while (getline(inputFile, line)) {
    char firstChar = line[0];

    if (firstChar == 'v') { // vertices
      stringstream ss(line);
      char firstChar2;
      float x, y, z;
      std::cout << line << "\n";
      ss >> firstChar2 >> x >> y >> z;
      vertices.push_back({x, y, z});

      // } else if (firstChar == 'f') { // edges
      // stringstream ss(line);
    };
  };

  std::cout << filename << " loaded\n";
  inputFile.close();

  return vertices;
};

Vector3 rotation(Vector3 vertex, Vector3 angle) {

  Vector3 positionPostRotationXaxis = {
      vertex.x, vertex.z * sinf(angle.x) + vertex.y * cosf(angle.x),
      vertex.z * cosf(angle.x) - vertex.y * sinf(angle.x)};

  vertex = positionPostRotationXaxis;

  Vector3 positionPostRotationYaxis = {
      vertex.x * cosf(angle.y) - vertex.z * sinf(angle.y), vertex.y,
      vertex.x * sinf(angle.y) + vertex.z * cosf(angle.y)};

  vertex = positionPostRotationYaxis;

  Vector3 positionPostRotationZaxis = {
      vertex.x * cosf(angle.z) - vertex.y * sinf(angle.z),
      vertex.x * sinf(angle.z) + vertex.y * cosf(angle.z), vertex.z};

  vertex = positionPostRotationZaxis;

  return vertex;
};

Vector3 project(Vector3 vertex, Vector3 angle) {
  // 1. rotation
  vertex = rotation(vertex, angle);

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
  //   Object cube = {
  //   	cube.vertices, cube.edges = loadObj("obj/cube.obj")
  //   };

  std::vector<Vector3> vertices = loadObj("obj/cube.obj");
  Vector3 angle = {0, 0, 0};

  for (int i; i < vertices.size(); i++) {
    std::cout << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z
              << "\n";
  };

  while (!WindowShouldClose()) {

    float rotationSpeed = 5;
    float dt = GetFrameTime();

    // step1: update
    if (IsKeyDown(KEY_RIGHT))
      angle.y += rotationSpeed * dt;
    if (IsKeyDown(KEY_LEFT))
      angle.y -= rotationSpeed * dt;
    if (IsKeyDown(KEY_UP))
      angle.x += rotationSpeed * dt;
    if (IsKeyDown(KEY_DOWN))
      angle.x -= rotationSpeed * dt;

    // std::cout << "x: " << angle.x << "\n";
    // std::cout << "y: " << angle.y << "\n";
    // std::cout << "z: " << angle.z << "\n";

    // step2: draw
    BeginDrawing();

    ClearBackground({84, 84, 84});

    // vertices loop
    for (int i = 0; i < vertices.size(); i++) {
      Vector3 vertex = project(vertices[i], angle);

      DrawCircle(vertex.x, vertex.y, 3, GREEN);
    };

    // edges loop
    for (int i = 0; i < 12; i++) {
      Vector3 vertexA = project(vertices[edges[i][0]], angle);
      Vector3 vertexB = project(vertices[edges[i][1]], angle);

      DrawLine(vertexA.x, vertexA.y, vertexB.x, vertexB.y, GREEN);
    };

    DrawText(TextFormat("angle x: %f", angle.x), 0, 0, 25, BLACK);
    DrawText(TextFormat("angle y: %f", angle.y), 0, 20, 25, BLACK);
    DrawText(TextFormat("angle z: %f", angle.z), 0, 40, 25, BLACK);
    DrawText(TextFormat("sizeof vertices: %d", vertices.size()), 0, 60, 25,
             BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

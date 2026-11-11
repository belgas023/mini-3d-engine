#pragma once

// data types
struct Vec2 {
  float x;
  float y;
};

struct Vec3 {
  float x;
  float y;
  float z;
};

struct Mat2 {
  float m[2][2];
  int rows = 2;
  int cols = 2;
};

struct Mat4 {
  float m[4][4];
  int rows = 4;
  int cols = 4;
};

// functions
Mat4 operator+(Mat4 mA, Mat4 mB);
Mat4 operator*(Mat4 mA, Mat4 mB);

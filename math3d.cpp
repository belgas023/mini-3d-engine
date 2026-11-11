#include "math3d.h"

// addition matrices
Mat4 operator+(Mat4 mA, Mat4 mB) {
  Mat4 m;
  for (int rows; rows < 4; rows++) {

    for (int col; col < 4; col++) {
      m.m[rows][col] = {
          mA.m[rows][col] + mB.m[rows][col],
      };
    };
  };
  return m;
};

// multiplication matrices
Mat4 operator*(Mat4 mA, Mat4 mB) {
  Mat4 m;
  for (int rows; rows < 4; rows++) {

    for (int col; col < 4; col++) {
      m.m[rows][col] = {
          mA.m[rows][col] * mB.m[col][rows],
      };
    };
  };
  return m;
};

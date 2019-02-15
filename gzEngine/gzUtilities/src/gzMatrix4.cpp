/****************************************************************************
/* @filename gzMatrix4.cpp
/* @author Gazelle
/* @date 2019/02/06
/* @brief 
/*****************************************************************************/

#include "gzMatrix4.h"

namespace gzEngineSDK {
  
  //TODO fix the constructors

  Matrix4::Matrix4(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) {

    matrix.m00 = m00;
    matrix.m01 = m01;
    matrix.m02 = m02;
    matrix.m03 = m03;

    matrix.m10 = m10;
    matrix.m11 = m11;
    matrix.m12 = m12;
    matrix.m13 = m13;

    matrix.m20 = m20;
    matrix.m21 = m21;
    matrix.m22 = m22;
    matrix.m23 = m23;

    matrix.m30 = m30;
    matrix.m31 = m31;
    matrix.m32 = m32;
    matrix.m33 = m33;
  }

  Matrix4::Matrix4(
    Vector4f VectorA,
    Vector4f VectorB,
    Vector4f VectorC,
    Vector4f VectorD) {

    matrix.m00 = VectorA.x;
    matrix.m01 = VectorA.y;
    matrix.m02 = VectorA.z;
    matrix.m03 = VectorA.w;

    matrix.m10 = VectorB.x;
    matrix.m11 = VectorB.y;
    matrix.m12 = VectorB.z;
    matrix.m13 = VectorB.w;

    matrix.m20 = VectorC.x;
    matrix.m21 = VectorC.y;
    matrix.m22 = VectorC.z;
    matrix.m23 = VectorC.w;

    matrix.m30 = VectorD.x;
    matrix.m31 = VectorD.y;
    matrix.m32 = VectorD.z;
    matrix.m33 = VectorD.w;
  }


  Matrix4::Matrix4(const Matrix4& Matrix) {
    matrix = Matrix.matrix;
  }

  FORCEINLINE Matrix4
  Matrix4::operator+(const Matrix4& Matrix) {
    Matrix4 res;
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        res.m[i][j] = m[i][j] + Matrix.m[i][j];
      }
    }
    return res;
  }

  FORCEINLINE Matrix4
  Matrix4::operator-(const Matrix4& Matrix) {
    Matrix4 res;
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        res.m[i][j] = m[i][j] - Matrix.m[i][j];
      }
    }
    return res;
  }

  FORCEINLINE Matrix4
  Matrix4::operator*(const Matrix4& Matrix) {
    Matrix4 res;
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        res.m[i][j] = m[i][j] * Matrix.m[i][j];
      }
    }
    return res;
  }

  FORCEINLINE Matrix4
  Matrix4::operator*(const float& Sacalar) {
    Matrix4 res;
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        res.m[i][j] = m[i][j] * Sacalar;
      }
    }
    return res;
  }

  Matrix4&
  Matrix4::operator+=(const Matrix4& Matrix) {
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        m[i][j] += Matrix.m[i][j];
      }
    }
  }

  Matrix4&
  Matrix4::operator-=(const Matrix4& Matrix) {
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        m[i][j] -= Matrix.m[i][j];
      }
    }
  }

  Matrix4&
  Matrix4::operator*=(const Matrix4& Matrix) {
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        m[i][j] *= Matrix.m[i][j];
      }
    }
  }

  void
  Matrix4::identity() {

    Vector4f VectorA(1.0f, 0.0f, 0.0f, 0.0f);
    Vector4f VectorB(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4f VectorC(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4f VectorD(0.0f, 0.0f, 0.0f, 1.0f);
    
    matrix.m00 = VectorA.x;
    matrix.m01 = VectorA.y;
    matrix.m02 = VectorA.z;
    matrix.m03 = VectorA.w;

    matrix.m10 = VectorB.x;
    matrix.m11 = VectorB.y;
    matrix.m12 = VectorB.z;
    matrix.m13 = VectorB.w;

    matrix.m20 = VectorC.x;
    matrix.m21 = VectorC.y;
    matrix.m22 = VectorC.z;
    matrix.m23 = VectorC.w;

    matrix.m30 = VectorD.x;
    matrix.m31 = VectorD.y;
    matrix.m32 = VectorD.z;
    matrix.m33 = VectorD.w;

  }

  void
  Matrix4::transposed() {
    Matrix4 temporal = *this;
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        m[i][j] = temporal.m[j][i];
      }
    }
  }

  
}
/****************************************************************************
/* @filename gzMatrix4.cpp
/* @author Victor Flores
/* @date 2019/02/06
/* @brief 
/*****************************************************************************/

#include "gzMatrix4.h"

namespace gzEngineSDK {

  Matrix4::Matrix4()
  {
    this->zeroMatrix();
  }

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
    return *this;
  }

  Matrix4&
  Matrix4::operator-=(const Matrix4& Matrix) {
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        m[i][j] -= Matrix.m[i][j];
      }
    }
    return *this;
  }

  Matrix4&
  Matrix4::operator*=(const Matrix4& Matrix) {
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        m[i][j] *= Matrix.m[i][j];
      }
    }
    return *this;
  }

  bool 
  Matrix4::operator==( const Matrix4 & Matrix ) const
  {
    for ( int32 i = 0; i < 4; i++ ) {
      for ( int32 j = 0; j < 4; j++ ) {
        if ( m[i][j] != Matrix.m[i][j] ) {
          return false;
        }
      }
    }
    return true;
  }

  bool Matrix4::operator!=( const Matrix4& Matrix ) const
  {
    for ( int32 i = 0; i < 4; i++ ) {
      for ( int32 j = 0; j < 4; j++ ) {
        if ( m[i][j] == Matrix.m[i][j] ) {
          return false;
        }
      }
    }
    return true;
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
  Matrix4::transpose() {
    Matrix4 temporal = *this;
    for (int32 i = 0; i < 4; i++) {
      for (int32 j = 0; j < 4; j++) {
        m[i][j] = temporal.m[j][i];
      }
    }
  }

  void 
  Matrix4::zeroMatrix() {
    matrix.m00 = 0;
    matrix.m01 = 0;
    matrix.m02 = 0;
    matrix.m03 = 0;

    matrix.m10 = 0;
    matrix.m11 = 0;
    matrix.m12 = 0;
    matrix.m13 = 0;

    matrix.m20 = 0;
    matrix.m21 = 0;
    matrix.m22 = 0;
    matrix.m23 = 0;

    matrix.m30 = 0;
    matrix.m31 = 0;
    matrix.m32 = 0;
    matrix.m33 = 0;
  }

  
  Matrix4
  Matrix4::matrixLookAtLH( Vector3f eyePosition, 
                           Vector3f atPosition, 
                           Vector3f upDirection )
  {
    Vector3f Xaxis;
    Vector3f Yaxis;
    Vector3f Zaxis;

    Zaxis = (atPosition - eyePosition).getNormalized();
    Xaxis = ( upDirection.crossProduct( Zaxis ) ).getNormalized();
    Yaxis = Zaxis.crossProduct( Xaxis );

    Matrix4 lookAt;
    lookAt.identity();

    lookAt.matrix.m00 = Xaxis.x; 
    lookAt.matrix.m10 = Xaxis.y; 
    lookAt.matrix.m20 = Xaxis.z; 

    lookAt.matrix.m01 = Yaxis.x;
    lookAt.matrix.m11 = Yaxis.y;
    lookAt.matrix.m21 = Yaxis.z;

    lookAt.matrix.m02 = Zaxis.x;
    lookAt.matrix.m12 = Zaxis.y;
    lookAt.matrix.m22 = Zaxis.z;

    lookAt.matrix.m30 = -(Xaxis.dot( eyePosition ));
    lookAt.matrix.m31 = -(Yaxis.dot( eyePosition ));
    lookAt.matrix.m32 = -(Zaxis.dot( eyePosition ));

    return lookAt;
    
  }

  Matrix4
  Matrix4::matrixPerspectiveFovLH( float fovy, 
                                   float aspect, 
                                   float znear, 
                                   float zfar )
  {
    float YScale = Math::cot( fovy / 2 );
    float XScale = YScale / aspect;

    Matrix4 matrixPerspective;

    matrixPerspective.matrix.m00 = XScale;
    matrixPerspective.matrix.m11 = YScale;
    matrixPerspective.matrix.m22 = zfar / ( zfar - znear);

    matrixPerspective.matrix.m32 = -( znear * zfar / ( zfar - znear ) );

    matrixPerspective.matrix.m23 = 1;

    return matrixPerspective;

  }

  void 
  Matrix4::matrixRotationY( float angle )
  {
    float CosT = cosf( angle );
    float SinT = sinf( angle );

    //CMatrix4 Result = CMatrix4::Identity;
    m[0][0] = CosT;
    m[0][2] = SinT;
    m[2][0] = -SinT;
    m[2][2] = CosT;
  }

}
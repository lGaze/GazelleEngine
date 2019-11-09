#pragma warning(push, 0)
#include <gtest/gtest.h>
#pragma warning(pop)
#include <gzMath.h>
#include <gzVector2f.h>
#include <gzVector3f.h>
#include <gzVector4f.h>
#include <gzMatrix4.h>

using namespace gzEngineSDK;

TEST( gzUtilities, BasicTypeSize )
{
  EXPECT_EQ( sizeof( unsigned char ), 1 );
  EXPECT_EQ( sizeof( uint8 ), 1 );
  EXPECT_EQ( sizeof( uint16 ), 2 );
  EXPECT_EQ( sizeof( uint32 ), 4 );
  EXPECT_EQ( sizeof( uint64 ), 8 );

  EXPECT_EQ( sizeof( char ), 1 );
  EXPECT_EQ( sizeof( int8 ), 1 );
  EXPECT_EQ( sizeof( int16 ), 2 );
  EXPECT_EQ( sizeof( int32 ), 4 );
  EXPECT_EQ( sizeof( int64 ), 8 );

}

TEST( gzUtilities, Matrix4Test )
{

  Matrix4 a;
  Matrix4 b;

  a.identity();

  EXPECT_EQ( a, Matrix4( 1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1 ) );
 
  a = Matrix4( 1, 5, 9, 13,
               2, 6, 10, 14,
               3, 7, 11, 15,
               4, 8, 12, 16 );
  
  a.transpose();

  EXPECT_EQ( a, Matrix4( 1, 2, 3, 4,
                         5, 6, 7, 8,
                         9, 10, 11, 12,
                         13, 14, 15, 16 ) );

  a.zeroMatrix();

  a = Matrix4( 2, 2, 2, 2,
               2, 2, 2, 2,
               2, 2, 2, 2,
               2, 2, 2, 2 );

  b = Matrix4( 1, 1, 1, 1,
               1, 1, 1, 1,
               1, 1, 1, 1,
               1, 1, 1, 1 );
  
  b *= a;
  EXPECT_EQ( a, b ) ;

  Vector3f Eye( 0.0f, 3.0f, -175.0f );
  Vector3f At( 0.0f, 1.0f, 0.0f );
  Vector3f Up( 0.0f, 1.0f, 0.0f );

  Matrix4 lookAt;
  lookAt = lookAt.matrixLookAtLH( Eye, At, Up );

  Matrix4 perspective;
  perspective = perspective.matrixPerspectiveFovLH( 0.785398163f,
                                                    600.0f /  (float)480.0f,
                                                    0.001f,
                                                    500.0f );
  
}

int main( int32 argc, char** argv )
{
  int32 stop;
  ::testing::InitGoogleTest( &argc, argv );
  RUN_ALL_TESTS();
  std::cin >> stop;
  return 0;
}
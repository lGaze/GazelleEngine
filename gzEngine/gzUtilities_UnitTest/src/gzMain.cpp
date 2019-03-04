#include <gtest/gtest.h>

#include <gzPrerequisitesUtilities.h>
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

int main( int32 argc, char** argv )
{
  int32 stop;
  ::testing::InitGoogleTest( &argc, argv );
  RUN_ALL_TESTS();
  std::cin >> stop;
  return 0;
}
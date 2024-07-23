#include "../app/Model/Components/AffineTransformations/Rotate/Rotate.h"
#include "tests.h"

using namespace s21;

class RotateTransformTest : public testing::Test {
protected:
  RotateStrategy strategy;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(RotateTransformTest, _30degreeRotationXTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> v = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  strategy.executeTransformation(v, Axes::X, 30.0, x);

  // // Assert
  std::vector<float> expected = {0.0,     -0.133975, 2.23205, 3.0,    0.964102,
                                 6.33013, 6.0,       2.06218, 10.4282};
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], expected[i], 1e-5);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(RotateTransformTest, _180degreeRotationYTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> v = {1.0, -1.0, -2.0, 1.0, -4.0, 0.5, 1.0, -1.0, 1.0};
  strategy.executeTransformation(v, Axes::Y, 180.0, x);

  // // Assert
  std::vector<float> expected = {-1.0, -1.0, 2.0,  -1.0, -4.0,
                                 -0.5, -1.0, -1.0, -1.0};
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], expected[i], 1e-5);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(RotateTransformTest, _360degreeRotationZTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> v = {-0.0, -1.0, 2.0, 1.0, -1.0, -5.0, 2.0, -1.0, -2.0};
  strategy.executeTransformation(v, Axes::Z, 360.0, x);

  // // Assert
  std::vector<float> expected = {-0.0, -1.0, 2.0,  1.0, -1.0,
                                 -5.0, 2.0,  -1.0, -2.0};
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], expected[i], 1e-5);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}
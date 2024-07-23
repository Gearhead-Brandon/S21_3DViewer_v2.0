#include "../app/Model/Components/AffineTransformations/Scale/Scale.h"
#include "tests.h"

using namespace s21;

class ScaleTransformTest : public testing::Test {
protected:
  ScaleStrategy strategy;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ScaleTransformTest, firstScaleTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> v = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  strategy.executeTransformation(v, Axes::X, 0.1, x);

  // Assert
  std::vector<float> expected = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], expected[i], 1e-6);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(ScaleTransformTest, secondScaleTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> v = {1.0, -1.0, -2.0, 1.0, -4.0, 0.5, 1.0, -1.0, 1.0};
  strategy.executeTransformation(v, Axes::Y, 0.5, x);

  // Assert
  std::vector<float> expected = {0.5,  -0.5, -1.0, 0.5, -2.0,
                                 0.25, 0.5,  -0.5, 0.5};
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], expected[i], 1e-7);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(ScaleTransformTest, thirdScaleTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> v = {-0.0, -1.0, 2.0, 1.0, -1.0, -5.0, 2.0, -1.0, -2.0};
  strategy.executeTransformation(v, Axes::Z, 0.375, x);

  // Assert
  std::vector<float> expected = {-0.0,   -0.375, 0.75,   0.375, -0.375,
                                 -1.875, 0.75,   -0.375, -0.75};
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], expected[i], 1e-7);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}
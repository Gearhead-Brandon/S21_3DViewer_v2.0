#include "../app/Model/Components/AffineTransformations/Move/Move.h"
#include "tests.h"

using namespace s21;

class MoveTransformTest : public testing::Test {
 protected:
  MoveStrategy strategy;
  std::vector<float> v;

  void SetUp() override {
    v.reserve(9);
    v = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  }
  void TearDown() override {}
};

TEST_F(MoveTransformTest, MoveXTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  strategy.executeTransformation(v, Axes::X, 10, x);

  // Assert
  std::vector<float> expected = {10.0, 1.0,  2.0, 13.0, 4.0,
                                 5.0,  16.0, 7.0, 8.0};
  EXPECT_EQ(v, expected);

  Point<float> y = {10.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(MoveTransformTest, MoveYTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  strategy.executeTransformation(v, Axes::Y, 10, x);

  // Assert
  std::vector<float> expected = {0.0, 11.0, 2.0,  3.0, 14.0,
                                 5.0, 6.0,  17.0, 8.0};
  EXPECT_EQ(v, expected);

  Point<float> y = {0.0, 10.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(MoveTransformTest, MoveZTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  strategy.executeTransformation(v, Axes::Z, 10, x);

  // Assert
  std::vector<float> expected = {0.0,  1.0, 12.0, 3.0, 4.0,
                                 15.0, 6.0, 7.0,  18.0};
  EXPECT_EQ(v, expected);

  Point<float> y = {0.0, 0.0, 10.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}
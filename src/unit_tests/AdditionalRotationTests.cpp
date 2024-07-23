#include "../app/Model/Components/AffineTransformations/Rotate/Rotate.h"
#include "../app/Model/Components/FileReader/FileReader.h"
#include "tests.h"

using namespace s21;

class AdditionalRotateTransformTest : public testing::Test {
protected:
  RotateStrategy strategy;
  Figure original;
  Figure figure;

  void SetUp() override {
    FileReader reader;
    reader.readScene(original, "./obj/cube.txt");
    reader.readScene(figure, "./obj/cube.txt");
  }
  void TearDown() override {}
};

TEST_F(AdditionalRotateTransformTest, _4on90degreeRotationXTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> &v = figure.getVertices();

  strategy.executeTransformation(v, Axes::X, 90.0, x);
  strategy.executeTransformation(v, Axes::X, 90.0, x);
  strategy.executeTransformation(v, Axes::X, 90.0, x);
  strategy.executeTransformation(v, Axes::X, 90.0, x);

  // Assert
  std::vector<float> original_v = original.getVertices();
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-6);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(AdditionalRotateTransformTest, _4on90degreeRotationYTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> &v = figure.getVertices();

  strategy.executeTransformation(v, Axes::Y, 90.0, x);
  strategy.executeTransformation(v, Axes::Y, 90.0, x);
  strategy.executeTransformation(v, Axes::Y, 90.0, x);
  strategy.executeTransformation(v, Axes::Y, 90.0, x);

  // Assert
  std::vector<float> original_v = original.getVertices();
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-6);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(AdditionalRotateTransformTest, _4on90degreeRotationZTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> &v = figure.getVertices();

  strategy.executeTransformation(v, Axes::Z, 90.0, x);
  strategy.executeTransformation(v, Axes::Z, 90.0, x);
  strategy.executeTransformation(v, Axes::Z, 90.0, x);
  strategy.executeTransformation(v, Axes::Z, 90.0, x);

  // Assert
  std::vector<float> original_v = original.getVertices();
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-6);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(AdditionalRotateTransformTest, _1on360degreeRotationXTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> &v = figure.getVertices();

  for (int i = 0; i < 360; i++)
    strategy.executeTransformation(v, Axes::X, 1, x);

  // Assert
  std::vector<float> original_v = original.getVertices();
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-5);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);

  // Act
  for (int i = 0; i < 360; i++)
    strategy.executeTransformation(v, Axes::X, -1, x);

  // Assert
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-5);

  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(AdditionalRotateTransformTest, _1on360degreeRotationYTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> &v = figure.getVertices();

  for (int i = 0; i < 360; i++)
    strategy.executeTransformation(v, Axes::Y, 1, x);

  // Assert
  std::vector<float> original_v = original.getVertices();
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-5);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);

  // Act
  for (int i = 0; i < 360; i++)
    strategy.executeTransformation(v, Axes::Y, -1, x);

  // Assert
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-5);

  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}

TEST_F(AdditionalRotateTransformTest, _1on360degreeRotationZTest) {
  // Act
  Point<float> x = {0.0, 0.0, 0.0};
  std::vector<float> &v = figure.getVertices();

  for (int i = 0; i < 360; i++)
    strategy.executeTransformation(v, Axes::Z, 1, x);

  // Assert
  std::vector<float> original_v = original.getVertices();
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-5);

  Point<float> y = {0.0, 0.0, 0.0};
  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);

  // Act
  for (int i = 0; i < 360; i++)
    strategy.executeTransformation(v, Axes::Z, -1, x);

  // Assert
  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], original_v[i], 1e-5);

  EXPECT_EQ(x.x, y.x);
  EXPECT_EQ(x.y, y.y);
  EXPECT_EQ(x.z, y.z);
}
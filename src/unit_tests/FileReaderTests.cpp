#include "../app/Model/Components/FileReader/FileReader.h"
#include "tests.h"

using namespace s21;

class FileReaderTest : public testing::Test {
protected:
  FileReader reader;
  Figure figure;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FileReaderTest, NormalFileReaderTest) {
  // Act
  reader.readScene(figure, "./obj/cube.txt");
  std::vector<float> &v = figure.getVertices();
  std::vector<unsigned> &in = figure.getIndices();

  // Assert
  std::vector<float> expectedVertices = {
      0.5, -0.5, -0.5, 0.5,  -0.5, 0.5,  -0.5,      -0.5,
      0.5, -0.5, -0.5, -0.5, 0.5,  0.5,  -0.499999, 0.499999,
      0.5, 0.5,  -0.5, 0.5,  0.5,  -0.5, 0.5,       -0.5};

  for (int i = 0, size = v.size(); i < size; i++)
    EXPECT_NEAR(v[i], expectedVertices[i], 1e-6);

  std::vector<unsigned> expectedIndices = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0, size = in.size(); i < size; i++)
    EXPECT_EQ(in[i], expectedIndices[i]);
}

TEST_F(FileReaderTest, MoreIndicesFileReaderTest) {
  // Act
  reader.readScene(figure, "./obj/cube2.txt");
  std::vector<unsigned> &in = figure.getIndices();

  // Assert
  std::vector<unsigned> expectedIndices = {
      1,  2,  2,  3, 3, 1,  7,  6, 6, 5,  5,  13, 13, 7,  4,  5, 5, 1,  1,  13,
      13, 10, 10, 4, 5, 6,  6,  2, 2, 12, 12, 5,  2,  6,  6,  7, 7, 13, 13, 2,
      0,  3,  3,  7, 7, 13, 13, 0, 0, 1,  1,  3,  3,  13, 13, 0, 4, 7,  7,  5,
      5,  13, 13, 4, 0, 4,  4,  1, 1, 13, 13, 0,  1,  5,  5,  2, 2, 13, 13, 1,
      3,  2,  2,  7, 7, 7,  7,  3, 4, 0,  0,  7,  7,  6,  6,  4};

  for (int i = 0, size = in.size(); i < size; i++)
    EXPECT_EQ(in[i], expectedIndices[i]);
}

TEST_F(FileReaderTest, NegativeIndicesFileReaderTest) {
  // Act
  reader.readScene(figure, "./obj/negative.txt");
  std::vector<unsigned> &in = figure.getIndices();

  // Assert
  std::vector<unsigned> expectedIndices = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 6, 6, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0, size = in.size(); i < size; i++)
    EXPECT_EQ(in[i], expectedIndices[i]);
}

TEST_F(FileReaderTest, ZeroIndicesFileReaderTest) {
  // Act
  reader.readScene(figure, "./obj/zero.txt");
  std::vector<unsigned> &in = figure.getIndices();

  // Assert
  std::vector<unsigned> expectedIndices = {
      1, 0, 0, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0, size = in.size(); i < size; i++)
    EXPECT_EQ(in[i], expectedIndices[i]);
}

TEST_F(FileReaderTest, WrongFileFormatFileReaderTest) {
  // Act
  FacadeOpResult result = reader.readScene(figure, "./obj/test_cube.txt");

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Is invalid obj file");

  // Act
  result = reader.readScene(figure, "./obj/test_cube2.txt");

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Is invalid obj file");
}

TEST_F(FileReaderTest, FileDoesntExistFileReaderTest) {
  // Act
  FacadeOpResult result = reader.readScene(figure, "./obj/not_exist.txt");

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Could not open file");
}
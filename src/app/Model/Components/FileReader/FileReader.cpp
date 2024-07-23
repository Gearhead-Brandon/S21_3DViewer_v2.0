/**
 * @file FileReader.cpp
 * @brief The source file with the implementation of the class FileReader
 */

#include "FileReader.h"
#include "fstream"
#include <iostream>
#include <sstream>

namespace s21 {

/**
 * @brief The method reads the .obj file
 * @param figure The figure
 * @param fileName The name of the .obj file
 * @returns FacadeOpResult
 */
FacadeOpResult FileReader::readScene(Figure &figure, const std::string &path) {
  FacadeOpResult result = fileValidation(figure, path);
  if (!result.IsSuccess())
    return result;

  figure.reset();

  std::ifstream file(path);
  std::string line("");
  NormParams normParams;

  const char *occurrences = "0123456789-";

  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ') {
      size_t pos = line.find_first_of(occurrences, 2);
      readVertex(figure, &line[pos], normParams);
    }

    if (line[0] == 'f') {
      size_t pos = line.find_first_of(occurrences, 1);
      std::istringstream iss(&line[pos]);
      std::string token;
      int count = 0, first_index = 0;

      while (std::getline(iss, token, ' ')) {
        // if (!token.empty() && token.find_first_of(occurrences) !=
        // std::string::npos) {
        if (token.find_first_of(occurrences) != std::string::npos) {
          readFacet(figure, &first_index, count, std::stoi(token));
          count++;
        }
      }

      figure.getIndices().push_back(first_index);
    }
  }

  file.close();

  Normalization(figure, normParams);

  return FacadeOpResult(true, "Success");
}

/**
 * @brief The method validates the file
 * @param figure The figure
 * @param fileName The name of the .obj file
 * @returns FacadeOpResult
 */
FacadeOpResult FileReader::fileValidation(Figure &figure,
                                          const std::string &file_name) {
  std::ifstream file(file_name);

  if (!file.is_open())
    return FacadeOpResult(false, "Could not open file");

  std::string line("");

  std::size_t countV = 0, countF = 0;

  while (std::getline(file, line)) {
    if (line[0] == 'v' && line[1] == ' ')
      countV++;
    if (line[0] == 'f')
      countF++;
  }

  file.close();

  if (countV < 1 || countF < 1)
    return FacadeOpResult(false, "Is invalid obj file");

  figure.setFacetsCount(countF);

  if (figure.getVertices().capacity() < countV * 3)
    figure.getVertices().reserve(countV * 3);

  if (figure.getIndices().capacity() < countF * 4)
    figure.getIndices().reserve(countF * 4);

  return FacadeOpResult(true, "Success");
}

/**
 * @brief The method performs the normalization
 * @param figure The figure
 * @param normParams The normParams
 */
void FileReader::Normalization(Figure &figure, NormParams &normParams) {
  float centerX = (normParams.max.x + normParams.min.x) / 2.0;
  float centerY = (normParams.max.y + normParams.min.y) / 2.0;
  float centerZ = (normParams.max.z + normParams.min.z) / 2.0;

  float max = std::max(std::max(normParams.max.x - normParams.min.x,
                                normParams.max.y - normParams.min.y),
                       normParams.max.z - normParams.min.z);

  float scale = (0.5 - (0.5 * (-1))) / max;

  std::vector<float> &vertices = figure.getVertices();
  std::vector<unsigned> &indices_vertices = figure.getIndicesVertices();
  indices_vertices.reserve(vertices.size() / 3);

  for (std::size_t i = 0, j = 0; i < vertices.size(); i += 3, j++) {
    vertices[i] = (vertices[i] - centerX) * scale;
    vertices[i + 1] = (vertices[i + 1] - centerY) * scale;
    vertices[i + 2] = (vertices[i + 2] - centerZ) * scale;

    indices_vertices.push_back(j);
  }

  figure.getMaxPoint() = normParams.max;
  figure.getMinPoint() = normParams.min;
}

/**
 * @brief The method reads the facet
 * @param figure The figure
 * @param first_index The first index value
 * @param count The count
 * @param number The number
 */
void FileReader::readFacet(Figure &figure, int *first_index, int count,
                           int number) {
  if (number < 0)
    number = (figure.getVertices().size() / 3) + (number + 1);

  if (number > 0)
    --number;

  std::vector<uint> &indices = figure.getIndices();

  if (!count) {
    indices.push_back(number);
    *first_index = number;
  } else {
    indices.push_back(number);
    indices.push_back(number);
  }
}

/**
 * @brief The method reads the vertex
 * @param figure The figure
 * @param line The line
 * @param normParams The normParams
 */
void FileReader::readVertex(Figure &figure, const char *line,
                            NormParams &normParams) {
  std::vector<float> &vertices = figure.getVertices();

  float x = 0, y = 0, z = 0;

  sscanf(line, "%f %f %f", &x, &y, &z);

  vertices.insert(vertices.end(), {x, y, z});
  // vertices.push_back(x);
  // vertices.push_back(y);
  // vertices.push_back(z);

  readMinMax(figure, normParams);
}

/**
 * @brief The method reads the min and max values
 * @param figure The figure
 * @param normParams The normParams
 */
void FileReader::readMinMax(Figure &figure, NormParams &normParams) {
  std::vector<float> &vertices = figure.getVertices();
  std::size_t size = vertices.size() - 1;

  float x = vertices[size - 2], y = vertices[size - 1], z = vertices[size];

  Point<float> &max = normParams.max;
  Point<float> &min = normParams.min;

  if (size / 3 == 1) {
    max = Point(x, y, z);
    min = Point(x, y, z);
  } else {
    max = Point(std::max(x, max.x), std::max(y, max.y), std::max(z, max.z));
    min = Point(std::min(x, min.x), std::min(y, min.y), std::min(z, min.z));
  }
}
} // namespace s21
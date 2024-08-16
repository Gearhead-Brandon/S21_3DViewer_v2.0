/**
 * @file FileReader.h
 * @brief The header file describes the class FileReader
 */

#ifndef FILE_READER_H
#define FILE_READER_H

#include "../NormParams/NormParams.h"
#include "../Scene/Scene.h"
#include "./IFileReader/IFileReader.h"

namespace s21 {

/**
 * @brief The class FileReader is used to read the .obj file
 * @details FileReader implements the interface IFileReader
 */
class FileReader : public IFileReader {
 public:
  /**
   * @brief The default constructor
   */
  FileReader() = default;

  /**
   * @brief The virtual destructor
   */
  ~FileReader() override {}

  /**
   * @brief The method reads the .obj file
   * @param figure The figure
   * @param fileName The name of the .obj file
   * @returns FacadeOpResult
   */
  FacadeOpResult readScene(Figure &figure, const std::string &path) override;

 private:
  /**
   * @brief The method validates the file
   * @param figure The figure
   * @param fileName The name of the .obj file
   * @returns FacadeOpResult
   */
  FacadeOpResult fileValidation(Figure &figure, const std::string &file_name);

  /**
   * @brief The method reads the vertex
   * @param figure The figure
   * @param line The line
   * @param normParams The normParams
   */
  void readVertex(Figure &figure, const char *line, NormParams &normParams);

  /**
   * @brief The method reads the facet
   * @param figure The figure
   * @param first_index The first index value
   * @param count The count
   * @param number The number
   */
  void readFacet(Figure &figure, int *first_index, int count, int number);

  /**
   * @brief The method reads the min and max values
   * @param figure The figure
   * @param normParams The normParams
   */
  void readMinMax(Figure &figure, NormParams &normParams);

  /**
   * @brief The method performs the normalization
   * @param figure The figure
   * @param normParams The normParams
   */
  void Normalization(Figure &figure, NormParams &normParams);
};
}  // namespace s21

#endif
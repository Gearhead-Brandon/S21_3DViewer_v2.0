/**
 * @file IFileReader.h
 * @brief The header file describes the interface of the IFileReader class
 */

#ifndef IFILE_READER_H
#define IFILE_READER_H

#include "../../../../Common/FacadeOpResult/FacadeOpResult.h"
#include "../../Scene/Scene.h"

namespace s21 {

/**
 * @brief Class describes the interface IFileReader
 * @details IFileReader is used to read the .obj file
 */
class IFileReader {
 public:
  /**
   * @brief The destructor of the IFileReader class
   */
  virtual ~IFileReader() = default;

  /**
   * @brief The method reads the .obj file
   * @param figure The figure
   * @param fileName The name of the .obj file
   * @returns FacadeOpResult
   */
  virtual FacadeOpResult readScene(Figure &figure,
                                   const std::string &fileName) = 0;
};
}  // namespace s21

#endif
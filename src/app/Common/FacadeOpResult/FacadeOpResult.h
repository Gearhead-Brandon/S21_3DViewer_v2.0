/**
 * @file FacadeOpResult.h
 * @brief Header file describing the class FacadeOpResult
 */

#ifndef FACADE_OPERATION_RESULT_H
#define FACADE_OPERATION_RESULT_H

#include <string>

namespace s21 {

/**
 * @brief The class FacadeOpResult is used to check the success of the facade
 * operations
 */
class FacadeOpResult {
  //! Operation success flag
  bool isSuccess_;

  //! Operation result message
  std::string errorMessage_;

 public:
  /**
   * @brief The constructor of the class FacadeOpResult
   * @param isSuccess Operation success flag
   * @param errorMessage Operation result message
   */
  FacadeOpResult(bool isSuccess, std::string errorMessage);

  /**
   * @brief The destructor of the class FacadeOpResult
   */
  ~FacadeOpResult() = default;

  /**
   * @brief Getter of the success flag
   * @return Operation success flag
   */
  bool IsSuccess();

  /**
   * @brief Getter of the result message
   * @return Operation result message
   */
  std::string getErrorMessage();
};
}  // namespace s21

#endif
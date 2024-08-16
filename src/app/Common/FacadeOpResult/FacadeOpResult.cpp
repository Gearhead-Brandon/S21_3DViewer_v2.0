/**
 * @file FacadeOpResult.cpp
 * @brief Source file with implementing the class FacadeOpResult
 */

#include "FacadeOpResult.h"

namespace s21 {

/**
 * @brief The constructor of the class FacadeOpResult
 * @param isSuccess Operation success flag
 * @param errorMessage Operation result message
 */
FacadeOpResult::FacadeOpResult(bool isSuccess, std::string errorMessage)
    : isSuccess_(isSuccess), errorMessage_(std::move(errorMessage)) {}

/**
 * @brief Getter of the success flag
 * @return Operation success flag
 */
bool FacadeOpResult::IsSuccess() { return isSuccess_; }

/**
 * @brief Getter of the result message
 * @return Operation result message
 */
std::string FacadeOpResult::getErrorMessage() { return errorMessage_; }
}  // namespace s21
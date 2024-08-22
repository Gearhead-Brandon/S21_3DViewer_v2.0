/**
 * @file NormParams.h
 * @brief Header file describing the structure normalization parameters
 */

#ifndef NORMPARAMS_H
#define NORMPARAMS_H

#include "../../../Common/Structures/Point.h"

namespace s21 {

/**
 * @brief The structure NormParams
 * @details The structure describes the normalization parameters for the figure
 */
struct NormParams {
  //! The maximum points
  Point<float> max = {0.0, 0.0, 0.0};

  //! The minimum points
  Point<float> min = {0.0, 0.0, 0.0};
};
}  // namespace s21

#endif
/**
 * @file LineType.h
 * @brief Header file describing enum of LineType
 */

#ifndef LINETYPE_H
#define LINETYPE_H

namespace s21 {

/**
 * @brief Enum of LineType
 */
enum class LineType : bool {
  Solid,  ///< Solid line
  Stipple ///< Dotted line
};
} // namespace s21

#endif
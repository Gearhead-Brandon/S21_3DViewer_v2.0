/**
 * @file ProjectionType.h
 * @brief Header file describing the enum of ProjectionType
 */

#ifndef PROJECTION_H
#define PROJECTION_H

namespace s21 {

/**
 * @brief Enum class describing the type of projection
 */
enum class ProjectionType : bool {
  Parallel, ///< Parallel/Orthographic projection
  Central   ///< Central/Perspective projection
};
} // namespace s21

#endif
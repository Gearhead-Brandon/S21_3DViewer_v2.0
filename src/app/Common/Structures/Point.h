/**
 * @file Point.h
 * @brief Header file describing the struct Point
 */

#ifndef POINT_H
#define POINT_H

namespace s21 {

/**
 * @brief Point with x, y, z coordinates
 * @tparam T type of coordinates
 */
template <typename T>
struct Point {
  T x;
  T y;
  T z;
};
}  // namespace s21

#endif
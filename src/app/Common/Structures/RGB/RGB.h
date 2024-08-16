/**
 * @file RGB.h
 * @brief Header file describing the structure RGB
 */

#ifndef RGB_H
#define RGB_H

namespace s21 {

/**
 * @brief The structure RGB
 */
struct RGB {
  //! Red color
  int red;

  //! Green color
  int green;

  //! Blue color
  int blue;

  /**
   * @brief The default constructor of the structure RGB
   */
  RGB();

  /**
   * @brief The constructor of the structure RGB from three integer values
   */
  RGB(int red, int green, int blue);

  /**
   * @brief The constructor of the structure RGB from three float values
   */
  RGB(float red, float green, float blue);
};
}  // namespace s21

#endif
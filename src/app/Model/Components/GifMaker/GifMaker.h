/**
 * @file GifMaker.h
 * @brief Header file with the class GifMaker for creating .gif files
 */

#ifndef GIFMAKER_H
#define GIFMAKER_H

#include "qgifimage/qgifimage.h"

namespace s21 {

/**
 * @brief The class GifMaker for creating .gif files
 */
class GifMaker {
  //! Pointer to QGifImage object
  QGifImage *gifImage_;

  //! Name of the .gif file
  QString gifName_;

  //! Count of frames
  std::size_t framesCount_ = 0;

 public:
  /**
   * @brief Constructor
   */
  GifMaker();

  /**
   * @brief Destructor
   */
  ~GifMaker();

  /**
   * @brief Add the frame to the .gif file
   * @param frame
   *
   */
  void addFrame(const QImage &frame);

  /**
   * @brief Set the name of the .gif file
   * @param name
   */
  void gifName(QString &name);

  /**
   * @brief The method tells whether the gif is complete
   * @return true if the gif is complete, false otherwise
   */
  bool gifComplete();
};
}  // namespace s21

#endif
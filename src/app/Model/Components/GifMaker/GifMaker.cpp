/**
 * @file GifMaker.cpp
 * @brief Source file with implementing the class GifMaker
 */

#include "GifMaker.h"

namespace s21 {

/**
 * @brief Constructor
 */
GifMaker::GifMaker() : gifImage_(nullptr), gifName_(""), framesCount_(0) {}

/**
 * @brief Destructor
 */
GifMaker::~GifMaker() {
  // if(gifImage_)
  delete gifImage_;
}

/**
 * @brief Add the frame to the .gif file
 * @param frame
 *
 */
void GifMaker::addFrame(const QImage &frame) {
  if (!gifImage_) {
    framesCount_ = 0;
    gifImage_ = new QGifImage();
    gifImage_->setDefaultDelay(10);
  }

  gifImage_->addFrame(frame);

  framesCount_++;

  if (framesCount_ == 50) {
    gifImage_->save(gifName_);
    gifName_.clear();
    delete gifImage_;
    gifImage_ = nullptr;
  }
}

/**
 * @brief Set the name of the .gif file
 * @param name
 */
void GifMaker::gifName(QString &name) { gifName_ = std::move(name); }

/**
 * @brief The method tells whether the gif is complete
 * @return true if the gif is complete, false otherwise
 */
bool GifMaker::gifComplete() { return framesCount_ >= 50; }
} // namespace s21
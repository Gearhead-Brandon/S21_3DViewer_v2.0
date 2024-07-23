/**
 * @file Figure.cpp
 * @brief Source file with implementing the class Figure
 */

#include "Figure.h"

namespace s21 {

/**
 * @brief The default constructor
 */
Figure::Figure()
    : vertices_(), indices_(),
      facetsCount_(0), max_{0.0, 0.0, 0.0}, min_{0.0, 0.0, 0.0}, center_{0.0,
                                                                         0.0,
                                                                         0.0},
      strategy_(nullptr) {}

/**
 * @brief The method returns the vector of vertices
 * @returns std::vector<float>
 */
auto Figure::getVertices() -> std::vector<float> & { return vertices_; }

/**
 * @brief The method returns the vector of indices
 * @returns std::vector<unsigned>
 */
auto Figure::getIndices() -> std::vector<unsigned> & { return indices_; }

/**
 * @brief The method returns the vector of indices vertices
 * @returns std::vector<unsigned>
 */
auto Figure::getIndicesVertices() -> std::vector<unsigned> & {
  return indicesVertices_;
}

/**
 * @brief The method returns the number of facets
 * @returns std::size_t
 */
auto Figure::getFacetsCount() -> std::size_t { return facetsCount_; }

/**
 * @brief The method returns the minimum point
 * @returns Point<float>
 */
auto Figure::getMinPoint() -> Point<float> & { return min_; }

/**
 * @brief The method returns the maximum point
 * @returns Point<float>
 */
auto Figure::getMaxPoint() -> Point<float> & { return max_; }

/**
 * @brief Set the number of facets
 * @param facetsCount
 */
void Figure::setFacetsCount(std::size_t facetsCount) {
  facetsCount_ = facetsCount;
}

/**
 * @brief The method resets the figure
 */
void Figure::reset() {
  vertices_.clear();
  indicesVertices_.clear();
  indices_.clear();
  max_ = Point<float>{0.0, 0.0, 0.0};
  min_ = Point<float>{0.0, 0.0, 0.0};
  center_ = Point<float>{0.0, 0.0, 0.0};
}

/**
 * @brief Set the transformation strategy
 */
void Figure::setTransformStrategy(ITransformationStrategy *newStrategy) {
  delete strategy_;
  strategy_ = newStrategy;
}

/**
 * @brief The method executes the transformation strategy
 * @param axis
 * @param value
 */
void Figure::executeTransformStrategy(Axes axis, float value) {
  strategy_->executeTransformation(vertices_, axis, value, center_);
}
} // namespace s21
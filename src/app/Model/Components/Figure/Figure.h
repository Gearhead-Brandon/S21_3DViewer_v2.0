/**
 * @file Figure.h
 * @brief Header file describing the class Figure
 */

#ifndef FIGURE_H
#define FIGURE_H

#include "../../../Common/Enum/Axes.h"
#include "../../../Common/Structures/Point.h"
#include "../AffineTransformations/ITransformation/ITransformation.h"
#include <vector>

namespace s21 {

/**
 * @brief The class Figure describes the structure of the 3D figure
 */
class Figure {

  //! The vector of vertices
  std::vector<float> vertices_;

  //! The vector of indices
  std::vector<unsigned> indices_;

  //! The vector of indices of vertices
  std::vector<unsigned> indicesVertices_;

  //! The number of facets
  std::size_t facetsCount_;

  //! The maximum points of the figure
  Point<float> max_;

  //! The minimum points of the figure
  Point<float> min_;

  //! The center point of the figure
  Point<float> center_;

  //! The pointer to the transformation strategy
  ITransformationStrategy *strategy_;

public:
  /**
   * @brief The default constructor
   */
  Figure();

  /**
   * @brief The destructor
   */
  ~Figure() = default;

  /**
   * @brief The method returns the vector of vertices
   * @returns std::vector<float>
   */
  std::vector<float> &getVertices();

  /**
   * @brief The method returns the vector of indices
   * @returns std::vector<unsigned>
   */
  std::vector<uint> &getIndices();

  /**
   * @brief The method returns the vector of indices vertices
   * @returns std::vector<unsigned>
   */
  std::vector<unsigned> &getIndicesVertices();

  /**
   * @brief The method returns the number of facets
   * @returns std::size_t
   */
  std::size_t getFacetsCount();

  /**
   * @brief The method returns the maximum point
   * @returns Point<float>
   */
  Point<float> &getMaxPoint();

  /**
   * @brief The method returns the minimum point
   * @returns Point<float>
   */
  Point<float> &getMinPoint();

  /**
   * @brief Set the number of facets
   * @param facetsCount
   */
  void setFacetsCount(std::size_t facetsCount);

  /**
   * @brief The method resets the figure
   */
  void reset();

  /**
   * @brief Set the transformation strategy
   */
  void setTransformStrategy(ITransformationStrategy *newStrategy);

  /**
   * @brief The method executes the transformation strategy
   * @param axis
   * @param value
   */
  void executeTransformStrategy(Axes axis, float value);
};
} // namespace s21

#endif
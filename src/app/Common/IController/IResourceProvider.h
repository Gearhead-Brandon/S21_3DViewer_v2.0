/**
 * @file IResourceProvider.h
 * @brief Interface for class IResourceProvider
 */

#ifndef IRESOURCE_PROVIDERR_H
#define IRESOURCE_PROVIDERR_H

#include <vector>

#include "../Settings/SettingsPackage/SettingsPackage.h"
#include "../Structures/Point.h"

namespace s21 {

/**
 * @brief The interface class IResourceProvider is used to get resources
 */
class IResourceProvider {
 public:
  /**
   * @brief Virtual destructor
   */
  virtual ~IResourceProvider() = default;

  /**
   * @brief The method returns the vector of vertices
   * @return std::vector<float>
   */
  virtual const std::vector<float> &getVertices() const = 0;

  /**
   * @brief The method returns the vector of indices
   * @return std::vector<unsigned>
   */
  virtual const std::vector<unsigned> &getIndices() const = 0;

  /**
   * @brief The method returns the vector of indices vertices
   * @return std::vector<unsigned>
   */
  virtual const std::vector<unsigned> &getIndicesVertices() const = 0;

  /**
   * @brief The method returns the max point
   * @return Point<float>
   */
  virtual const Point<float> &getMaxPoint() const = 0;

  /**
   * @brief Getter of facets count
   * @return std::size_t
   * @details The method returns the number of polygons in the model
   */
  virtual size_t getFacetsCount() const = 0;

  /**
   * @brief The method returns the settings package
   * @return SettingsPackage
   */
  virtual const SettingsPackage &getSettingsPackage() const = 0;
};
}  // namespace s21

#endif
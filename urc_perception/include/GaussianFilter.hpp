#ifndef GAUSSIANFILTER_HPP_
#define GAUSSIANFILTER_HPP_

#include <filters/filter_base.hpp>

#include <vector>
#include <string>

namespace urc_perception
{
template<typename T>
class GaussianFilter : public filters::FilterBase<T>
{
public:
  GaussianFilter();
  virtual ~GaussianFilter();

  virtual bool configure();
  /**
       * Uses a Gaussian kernel to inflate the values of the input layer.
       *
       * @param mapIn grid map containing input layer
       * @param mapOut grid map containing mapIn and inpainted input layer.
       */
  virtual bool update(const T & mapIn, T & mapOut);

private:
  double radius_;
  double gaussian_coeff_;

  std::string inputLayer_;
  std::string outputLayer_;
};

} // namespace urc_perception
#endif // GAUSSIANFILTER_HPP_

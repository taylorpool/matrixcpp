#include "sabai/dynamic.hpp"

namespace sabai {
DynamicVector<size_t> ARange(size_t N) {
  DynamicVector<size_t> range(N);
  for (size_t index = static_cast<size_t>(0); index < N; ++index) {
    range(index) = index;
  }
  return range;
}
} // namespace sabai
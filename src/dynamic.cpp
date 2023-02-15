#include "matrix/dynamic.hpp"

namespace sabai {
DynamicVector<uint64_t> ARange(uint64_t N) {
  DynamicVector<uint64_t> range(N);
  for (uint64_t index = 0; index < N; ++index) {
    range(index) = index;
  }
  return range;
}
} // namespace sabai
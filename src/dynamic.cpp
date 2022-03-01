#include "matrix/dynamic.hpp"

namespace math
{
DynamicVectori ARange(int N)
{
    DynamicVectori range(N);
    for(int index = 0; index < N; ++index)
    {
        range(index) = index;
    }
    return range;
}
}
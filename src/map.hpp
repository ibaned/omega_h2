#ifndef MAP_HPP
#define MAP_HPP

#include "internal.hpp"

namespace Omega_h {

template <typename T>
void map_into(Read<T> a_data, LOs a2b, Write<T> b_data, Int width);

template <typename T>
Read<T> map_onto(Read<T> a_data, LOs a2b, LO nb, T init_val, Int width);

template <typename T>
Read<T> unmap(LOs a2b, Read<T> b_data, Int width);

template <typename T>
Read<T> expand(Read<T> a_data, LOs a2b, Int width);

LOs multiply_fans(LOs a2b, LOs a2c);

LOs compound_maps(LOs a2b, LOs b2c);

LOs invert_permutation(LOs a2b);

Read<I8> invert_marks(Read<I8> marks);

Read<I8> mark_image(LOs a2b, LO nb);

LOs invert_injective_map(LOs a2b, LO nb);

LOs invert_funnel(LOs ab2a, LO na);

Graph invert_map_by_sorting(LOs a2b, LO nb);

Graph invert_map_by_atomics(LOs a2b, LO nb);

LOs get_degrees(LOs offsets);

LOs invert_fan(LOs a2b);

template <typename T>
Read<T> fan_sum(LOs a2b, Read<T> b_data);
template <typename T>
Read<T> fan_max(LOs a2b, Read<T> b_data);
template <typename T>
Read<T> fan_min(LOs a2b, Read<T> b_data);
template <typename T>
Read<T> fan_reduce(LOs a2b, Read<T> b_data, Int width, Omega_h_Op op);

#define INST_T(T)                                                              \
  extern template void map_into(                                               \
      Read<T> a_data, LOs a2b, Write<T> b_data, Int width);                    \
  extern template Read<T> map_onto(                                            \
      Read<T> a_data, LOs a2b, LO nb, T, Int width);                           \
  extern template Read<T> unmap(LOs a2b, Read<T> b_data, Int width);           \
  extern template Read<T> expand(Read<T> a_data, LOs a2b, Int width);          \
  extern template Read<T> permute(Read<T> a_data, LOs a2b, Int width);         \
  extern template Read<T> fan_reduce(                                          \
      LOs a2b, Read<T> b_data, Int width, Omega_h_Op op);
INST_T(I8)
INST_T(I32)
INST_T(I64)
INST_T(Real)
#undef INST_T

}  // end namespace Omega_h

#endif

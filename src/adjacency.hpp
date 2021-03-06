#ifndef ADJACENCY_HPP
#define ADJACENCY_HPP

#include "internal.hpp"

namespace Omega_h {

LOs order_by_globals(LOs a2ab, LOs ab2b, Read<GO> b_global);

Adj invert_adj(Adj down, Int nlows_per_high, LO nlows, Read<GO> high_globals);

/* given the vertex lists for high entities,
   create vertex lists for all uses of low
   entities by high entities */
LOs form_uses(LOs hv2v, Int high_dim, Int low_dim);

LOs find_unique(LOs hv2v, Int high_dim, Int low_dim);

/* for each entity (or entity use), sort its vertex list
   and express the sorting transformation as an alignment code */
template <typename T>
Read<I8> get_codes_to_canonical(Int deg, Read<T> ev2v);

Read<I8> find_canonical_jumps(Int deg, LOs canon, LOs e_sorted2e);

/* given entity uses and unique entities,
   both defined by vertex lists, match
   uses to unique entities and derive their
   respective alignment codes.

   even though this is a downward adjacency, we'll
   define the code as describing how to transform
   the boundary entity into the entity use,
   since typically data is being pulled into an element
   from its boundary
*/
template <Int deg, typename T>
void find_matches_deg(LOs a2fv, Read<T> av2v, Read<T> bv2v, Adj v2b,
    LOs* a2b_out, Read<I8>* codes_out);
template <typename T>
void find_matches_ex(Int deg, LOs a2fv, Read<T> av2v, Read<T> bv2v, Adj v2b,
    LOs* a2b_out, Read<I8>* codes_out);

/* for testing only, internally computes upward
   adjacency */
Adj reflect_down(LOs hv2v, LOs lv2v, LO nv, Int high_dim, Int low_dim);

Adj transit(Adj h2m, Adj m2l, Int high_dim, Int low_dim);

Graph verts_across_edges(Adj e2v, Adj v2e);
Graph edges_across_tris(Adj f2e, Adj e2f);
Graph edges_across_tets(Adj r2e, Adj e2r);
Graph elements_across_sides(
    Int dim, Adj elems2sides, Adj sides2elems, Read<I8> side_is_exposed);

#define INST_DECL(T)                                                           \
  extern template Read<I8> get_codes_to_canonical(Int deg, Read<T> ev2v);      \
  extern template void find_matches_ex(Int deg, LOs a2fv, Read<T> av2v,        \
      Read<T> bv2v, Adj v2b, LOs* a2b_out, Read<I8>* codes_out);
INST_DECL(LO)
INST_DECL(GO)
#undef INST_DECL

}  // end namespace Omega_h

#endif

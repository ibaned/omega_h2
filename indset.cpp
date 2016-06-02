namespace indset {

Read<I8> local_iteration(
    LOs xadj, LOs adj,
    Reals quality,
    Read<GO> global,
    Read<I8> old_state) {
  auto n = global.size();
  Write<I8> new_state(old_state.size());
  auto f = LAMBDA(LO v) {
    if (old_state[v] != UNKNOWN) return;
    auto begin = xadj[v];
    auto end = xadj[v + 1];
    // nodes adjacent to chosen ones are rejected
    for (auto j = begin; j < end; ++j) {
      auto u = adj[j];
      if (old_state[u] == IN) {
        new_state[v] = NOT_IN;
        return;
      }
    }
    // check if node is a local maximum
    auto v_qual = quality[v];
    for (auto j = begin; j < end; ++j) {
      auto u = adj[j];
      // neighbor was rejected, ignore its presence
      if (old_state[u] == NOT_IN) continue;
      auto u_qual = quality[u];
      // neighbor has higher quality
      if (u_qual > v_qual) return;
      // neighbor has equal quality, tiebreaker by global ID
      if (u_qual == v_qual && global[u] > global[v]) return;
    }
    // only local maxima reach this line
    new_state[v] = IN;
  };
  parallel_for(n, f);
  return new_state;
}

Read<I8> iteration(
    Dist owners2copies,
    LOs xadj, LOs adj,
    Reals quality,
    Read<GO> global,
    Read<I8> old_state) {
  auto local_state = local_iteration(xadj, adj, quality, global, old_state);
  auto synced_state = owners2copies.exch(local_state, 1);
  return synced_state;
}

Read<I8> find(
    Dist owners2copies,
    LOs xadj, LOs adj,
    Reals quality,
    Read<GO> global,
    Read<I8> candidates) {
  auto n = global.size();
  CHECK(quality.size() == n);
  CHECK(candidates.size() == n);
  auto initial_state = Write<I8>(n);
  auto f = LAMBDA(LO i) {
    if (candidates[i]) initial_state[i] = UNKNOWN;
    else initial_state[i] = NOT_IN;
  };
  auto comm = owners2copies.parent_comm();
  auto state = Read<I8>(initial_state);
  while (comm->allreduce(max(state), MAX) == UNKNOWN) {
    state = iteration(owners2copies, xadj, adj, quality, global, state);
  }
  return state;
}

}

Read<I8> find_indset(
    Mesh& mesh,
    Int ent_dim,
    Reals quality,
    Read<I8> candidates) {
  auto graph = mesh.ask_star(ent_dim);
  auto xadj = graph.a2ab;
  auto adj = graph.ab2b;
  auto globals = mesh.ask_globals(ent_dim);
  auto owners2copies = mesh.ask_dist(ent_dim).invert();
  return indset::find(owners2copies, xadj, adj, quality, globals, candidates);
}

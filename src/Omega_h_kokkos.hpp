#ifndef OMEGA_H_KOKKOS_HPP
#define OMEGA_H_KOKKOS_HPP

#include <Omega_h_c.h>

#ifdef OMEGA_H_USE_KOKKOS

OMEGA_H_SYSTEM_HEADER

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <Kokkos_Core.hpp>

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif  // OMEGA_H_USE_KOKKOS

#ifdef OMEGA_H_USE_KOKKOS
#define OMEGA_H_INLINE KOKKOS_INLINE_FUNCTION
#else
#define OMEGA_H_INLINE inline
#endif  // OMEGA_H_USE_KOKKOS

#ifdef OMEGA_H_USE_CUDA
#define OMEGA_H_DEVICE __device__ inline
#define OMEGA_H_LAMBDA [=] __device__
#else
#define OMEGA_H_DEVICE inline
#define OMEGA_H_LAMBDA [=]
#endif  // OMEGA_H_USE_CUDA

#endif

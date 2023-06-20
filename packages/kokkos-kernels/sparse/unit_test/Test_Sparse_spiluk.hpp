//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

#include <gtest/gtest.h>
#include <Kokkos_Core.hpp>

#include <string>
#include <stdexcept>

#include "KokkosSparse_Utils.hpp"
#include "KokkosSparse_CrsMatrix.hpp"
#include <KokkosKernels_IOUtils.hpp>
#include "KokkosBlas1_nrm2.hpp"
#include "KokkosSparse_spmv.hpp"
#include "KokkosSparse_spiluk.hpp"

#include <gtest/gtest.h>

using namespace KokkosSparse;
using namespace KokkosSparse::Experimental;
using namespace KokkosKernels;
using namespace KokkosKernels::Experimental;

// #ifndef kokkos_complex_double
// #define kokkos_complex_double Kokkos::complex<double>
// #define kokkos_complex_float Kokkos::complex<float>
// #endif

typedef Kokkos::complex<double> kokkos_complex_double;
typedef Kokkos::complex<float> kokkos_complex_float;

namespace Test {

template <typename scalar_t, typename lno_t, typename size_type,
          typename device>
void run_test_spiluk() {
  typedef Kokkos::View<size_type *, device> RowMapType;
  typedef Kokkos::View<lno_t *, device> EntriesType;
  typedef Kokkos::View<scalar_t *, device> ValuesType;
  typedef Kokkos::ArithTraits<scalar_t> AT;

  const size_type nrows = 9;
  const size_type nnz   = 21;

  RowMapType row_map("row_map", nrows + 1);
  EntriesType entries("entries", nnz);
  ValuesType values("values", nnz);

  auto hrow_map = Kokkos::create_mirror_view(row_map);
  auto hentries = Kokkos::create_mirror_view(entries);
  auto hvalues  = Kokkos::create_mirror_view(values);

  scalar_t ZERO = scalar_t(0);
  scalar_t ONE  = scalar_t(1);
  scalar_t MONE = scalar_t(-1);

  hrow_map(0) = 0;
  hrow_map(1) = 3;
  hrow_map(2) = 5;
  hrow_map(3) = 6;
  hrow_map(4) = 9;
  hrow_map(5) = 11;
  hrow_map(6) = 13;
  hrow_map(7) = 15;
  hrow_map(8) = 18;
  hrow_map(9) = nnz;

  hentries(0)  = 0;
  hentries(1)  = 2;
  hentries(2)  = 5;
  hentries(3)  = 1;
  hentries(4)  = 6;
  hentries(5)  = 2;
  hentries(6)  = 0;
  hentries(7)  = 3;
  hentries(8)  = 4;
  hentries(9)  = 0;
  hentries(10) = 4;
  hentries(11) = 1;
  hentries(12) = 5;
  hentries(13) = 2;
  hentries(14) = 6;
  hentries(15) = 3;
  hentries(16) = 4;
  hentries(17) = 7;
  hentries(18) = 3;
  hentries(19) = 4;
  hentries(20) = 8;

  hvalues(0)  = 10;
  hvalues(1)  = 0.3;
  hvalues(2)  = 0.6;
  hvalues(3)  = 11;
  hvalues(4)  = 0.7;
  hvalues(5)  = 12;
  hvalues(6)  = 5;
  hvalues(7)  = 13;
  hvalues(8)  = 1;
  hvalues(9)  = 4;
  hvalues(10) = 14;
  hvalues(11) = 3;
  hvalues(12) = 15;
  hvalues(13) = 7;
  hvalues(14) = 16;
  hvalues(15) = 6;
  hvalues(16) = 5;
  hvalues(17) = 17;
  hvalues(18) = 2;
  hvalues(19) = 2.5;
  hvalues(20) = 18;

  Kokkos::deep_copy(row_map, hrow_map);
  Kokkos::deep_copy(entries, hentries);
  Kokkos::deep_copy(values, hvalues);

  typedef KokkosKernels::Experimental::KokkosKernelsHandle<
      size_type, lno_t, scalar_t, typename device::execution_space,
      typename device::memory_space, typename device::memory_space>
      KernelHandle;

  KernelHandle kh;

  // SPILUKAlgorithm::SEQLVLSCHD_RP
  {
    kh.create_spiluk_handle(SPILUKAlgorithm::SEQLVLSCHD_RP, nrows, 4 * nrows,
                            4 * nrows);

    auto spiluk_handle = kh.get_spiluk_handle();

    // Allocate L and U as outputs
    RowMapType L_row_map("L_row_map", nrows + 1);
    EntriesType L_entries("L_entries", spiluk_handle->get_nnzL());
    ValuesType L_values("L_values", spiluk_handle->get_nnzL());
    RowMapType U_row_map("U_row_map", nrows + 1);
    EntriesType U_entries("U_entries", spiluk_handle->get_nnzU());
    ValuesType U_values("U_values", spiluk_handle->get_nnzU());

    typename KernelHandle::const_nnz_lno_t fill_lev = 2;

    spiluk_symbolic(&kh, fill_lev, row_map, entries, L_row_map, L_entries,
                    U_row_map, U_entries);

    Kokkos::fence();

    Kokkos::resize(L_entries, spiluk_handle->get_nnzL());
    Kokkos::resize(L_values, spiluk_handle->get_nnzL());
    Kokkos::resize(U_entries, spiluk_handle->get_nnzU());
    Kokkos::resize(U_values, spiluk_handle->get_nnzU());

    spiluk_handle->print_algorithm();
    spiluk_numeric(&kh, fill_lev, row_map, entries, values, L_row_map,
                   L_entries, L_values, U_row_map, U_entries, U_values);

    Kokkos::fence();

    // Checking
    typedef CrsMatrix<scalar_t, lno_t, device, void, size_type> crsMat_t;
    crsMat_t A("A_Mtx", nrows, nrows, nnz, values, row_map, entries);
    crsMat_t L("L_Mtx", nrows, nrows, spiluk_handle->get_nnzL(), L_values,
               L_row_map, L_entries);
    crsMat_t U("U_Mtx", nrows, nrows, spiluk_handle->get_nnzU(), U_values,
               U_row_map, U_entries);

    // Create a reference view e set to all 1's
    ValuesType e_one("e_one", nrows);
    Kokkos::deep_copy(e_one, 1.0);

    // Create two views for spmv results
    ValuesType bb("bb", nrows);
    ValuesType bb_tmp("bb_tmp", nrows);

    // Compute norm2(L*U*e_one - A*e_one)/norm2(A*e_one)
    KokkosSparse::spmv("N", ONE, A, e_one, ZERO, bb);

    typename AT::mag_type bb_nrm = KokkosBlas::nrm2(bb);

    KokkosSparse::spmv("N", ONE, U, e_one, ZERO, bb_tmp);
    KokkosSparse::spmv("N", ONE, L, bb_tmp, MONE, bb);

    typename AT::mag_type diff_nrm = KokkosBlas::nrm2(bb);

    EXPECT_TRUE((diff_nrm / bb_nrm) < 1e-4);

    kh.destroy_spiluk_handle();
  }

  // SPILUKAlgorithm::SEQLVLSCHD_TP1
  {
    kh.create_spiluk_handle(SPILUKAlgorithm::SEQLVLSCHD_TP1, nrows, 4 * nrows,
                            4 * nrows);

    auto spiluk_handle = kh.get_spiluk_handle();

    // Allocate L and U as outputs
    RowMapType L_row_map("L_row_map", nrows + 1);
    EntriesType L_entries("L_entries", spiluk_handle->get_nnzL());
    ValuesType L_values("L_values", spiluk_handle->get_nnzL());
    RowMapType U_row_map("U_row_map", nrows + 1);
    EntriesType U_entries("U_entries", spiluk_handle->get_nnzU());
    ValuesType U_values("U_values", spiluk_handle->get_nnzU());

    typename KernelHandle::const_nnz_lno_t fill_lev = 2;

    spiluk_symbolic(&kh, fill_lev, row_map, entries, L_row_map, L_entries,
                    U_row_map, U_entries);

    Kokkos::fence();

    Kokkos::resize(L_entries, spiluk_handle->get_nnzL());
    Kokkos::resize(L_values, spiluk_handle->get_nnzL());
    Kokkos::resize(U_entries, spiluk_handle->get_nnzU());
    Kokkos::resize(U_values, spiluk_handle->get_nnzU());

    spiluk_handle->print_algorithm();
    spiluk_numeric(&kh, fill_lev, row_map, entries, values, L_row_map,
                   L_entries, L_values, U_row_map, U_entries, U_values);

    Kokkos::fence();

    // Checking
    typedef CrsMatrix<scalar_t, lno_t, device, void, size_type> crsMat_t;
    crsMat_t A("A_Mtx", nrows, nrows, nnz, values, row_map, entries);
    crsMat_t L("L_Mtx", nrows, nrows, spiluk_handle->get_nnzL(), L_values,
               L_row_map, L_entries);
    crsMat_t U("U_Mtx", nrows, nrows, spiluk_handle->get_nnzU(), U_values,
               U_row_map, U_entries);

    // Create a reference view e set to all 1's
    ValuesType e_one("e_one", nrows);
    Kokkos::deep_copy(e_one, 1.0);

    // Create two views for spmv results
    ValuesType bb("bb", nrows);
    ValuesType bb_tmp("bb_tmp", nrows);

    // Compute norm2(L*U*e_one - A*e_one)/norm2(A*e_one)
    KokkosSparse::spmv("N", ONE, A, e_one, ZERO, bb);

    typename AT::mag_type bb_nrm = KokkosBlas::nrm2(bb);

    KokkosSparse::spmv("N", ONE, U, e_one, ZERO, bb_tmp);
    KokkosSparse::spmv("N", ONE, L, bb_tmp, MONE, bb);

    typename AT::mag_type diff_nrm = KokkosBlas::nrm2(bb);

    EXPECT_TRUE((diff_nrm / bb_nrm) < 1e-4);

    kh.destroy_spiluk_handle();
  }
}

template <typename scalar_t, typename lno_t, typename size_type,
          typename device>
void run_test_spiluk_streams(int test_algo, int nstreams) {
  using RowMapType             = Kokkos::View<size_type *, device>;
  using EntriesType            = Kokkos::View<lno_t *, device>;
  using ValuesType             = Kokkos::View<scalar_t *, device>;
  using RowMapType_hostmirror  = typename RowMapType::HostMirror;
  using EntriesType_hostmirror = typename EntriesType::HostMirror;
  using ValuesType_hostmirror  = typename ValuesType::HostMirror;
  using execution_space        = typename device::execution_space;
  using memory_space           = typename device::memory_space;
  using KernelHandle = KokkosKernels::Experimental::KokkosKernelsHandle<
      size_type, lno_t, scalar_t, execution_space, memory_space, memory_space>;
  using crsMat_t = CrsMatrix<scalar_t, lno_t, device, void, size_type>;
  using AT       = Kokkos::ArithTraits<scalar_t>;

  // Workaround for OpenMP: skip tests if concurrency < nstreams because of
  // not enough resource to partition
  bool run_streams_test = true;
#ifdef KOKKOS_ENABLE_OPENMP
  if (std::is_same<typename device::execution_space, Kokkos::OpenMP>::value) {
    int exec_concurrency = execution_space().concurrency();
    if (exec_concurrency < nstreams) {
      run_streams_test = false;
      std::cout << "  Skip stream test: concurrency = " << exec_concurrency
                << std::endl;
    }
  }
#endif
  if (!run_streams_test) return;

  const size_type nrows = 9;
  const size_type nnz   = 21;

  std::vector<execution_space> instances;
  if (nstreams == 1)
    instances = Kokkos::Experimental::partition_space(execution_space(), 1);
  else if (nstreams == 2)
    instances = Kokkos::Experimental::partition_space(execution_space(), 1, 1);
  else if (nstreams == 3)
    instances =
        Kokkos::Experimental::partition_space(execution_space(), 1, 1, 1);
  else
    instances =
        Kokkos::Experimental::partition_space(execution_space(), 1, 1, 1, 1);

  std::vector<KernelHandle> kh_v(nstreams);
  std::vector<KernelHandle *> kh_ptr_v(nstreams);
  std::vector<RowMapType> A_row_map_v(nstreams);
  std::vector<EntriesType> A_entries_v(nstreams);
  std::vector<ValuesType> A_values_v(nstreams);
  std::vector<RowMapType> L_row_map_v(nstreams);
  std::vector<EntriesType> L_entries_v(nstreams);
  std::vector<ValuesType> L_values_v(nstreams);
  std::vector<RowMapType> U_row_map_v(nstreams);
  std::vector<EntriesType> U_entries_v(nstreams);
  std::vector<ValuesType> U_values_v(nstreams);

  RowMapType_hostmirror hrow_map("hrow_map", nrows + 1);
  EntriesType_hostmirror hentries("hentries", nnz);
  ValuesType_hostmirror hvalues("hvalues", nnz);

  scalar_t ZERO = scalar_t(0);
  scalar_t ONE  = scalar_t(1);
  scalar_t MONE = scalar_t(-1);

  hrow_map(0) = 0;
  hrow_map(1) = 3;
  hrow_map(2) = 5;
  hrow_map(3) = 6;
  hrow_map(4) = 9;
  hrow_map(5) = 11;
  hrow_map(6) = 13;
  hrow_map(7) = 15;
  hrow_map(8) = 18;
  hrow_map(9) = nnz;

  hentries(0)  = 0;
  hentries(1)  = 2;
  hentries(2)  = 5;
  hentries(3)  = 1;
  hentries(4)  = 6;
  hentries(5)  = 2;
  hentries(6)  = 0;
  hentries(7)  = 3;
  hentries(8)  = 4;
  hentries(9)  = 0;
  hentries(10) = 4;
  hentries(11) = 1;
  hentries(12) = 5;
  hentries(13) = 2;
  hentries(14) = 6;
  hentries(15) = 3;
  hentries(16) = 4;
  hentries(17) = 7;
  hentries(18) = 3;
  hentries(19) = 4;
  hentries(20) = 8;

  hvalues(0)  = 10;
  hvalues(1)  = 0.3;
  hvalues(2)  = 0.6;
  hvalues(3)  = 11;
  hvalues(4)  = 0.7;
  hvalues(5)  = 12;
  hvalues(6)  = 5;
  hvalues(7)  = 13;
  hvalues(8)  = 1;
  hvalues(9)  = 4;
  hvalues(10) = 14;
  hvalues(11) = 3;
  hvalues(12) = 15;
  hvalues(13) = 7;
  hvalues(14) = 16;
  hvalues(15) = 6;
  hvalues(16) = 5;
  hvalues(17) = 17;
  hvalues(18) = 2;
  hvalues(19) = 2.5;
  hvalues(20) = 18;

  typename KernelHandle::const_nnz_lno_t fill_lev = 2;

  for (int i = 0; i < nstreams; i++) {
    // Allocate A as input
    A_row_map_v[i] = RowMapType("A_row_map", nrows + 1);
    A_entries_v[i] = EntriesType("A_entries", nnz);
    A_values_v[i]  = ValuesType("A_values", nnz);

    // Copy from host to device
    Kokkos::deep_copy(A_row_map_v[i], hrow_map);
    Kokkos::deep_copy(A_entries_v[i], hentries);
    Kokkos::deep_copy(A_values_v[i], hvalues);

    // Create handle
    kh_v[i] = KernelHandle();
    if (test_algo == 0)
      kh_v[i].create_spiluk_handle(SPILUKAlgorithm::SEQLVLSCHD_RP, nrows,
                                   4 * nrows, 4 * nrows);
    else if (test_algo == 1)
      kh_v[i].create_spiluk_handle(SPILUKAlgorithm::SEQLVLSCHD_TP1, nrows,
                                   4 * nrows, 4 * nrows);
    kh_ptr_v[i] = &kh_v[i];

    auto spiluk_handle = kh_v[i].get_spiluk_handle();
    std::cout << "  Stream " << i << ": ";
    spiluk_handle->print_algorithm();

    // Allocate L and U as outputs
    L_row_map_v[i] = RowMapType("L_row_map", nrows + 1);
    L_entries_v[i] = EntriesType("L_entries", spiluk_handle->get_nnzL());
    L_values_v[i]  = ValuesType("L_values", spiluk_handle->get_nnzL());
    U_row_map_v[i] = RowMapType("U_row_map", nrows + 1);
    U_entries_v[i] = EntriesType("U_entries", spiluk_handle->get_nnzU());
    U_values_v[i]  = ValuesType("U_values", spiluk_handle->get_nnzU());

    // Symbolic phase
    spiluk_symbolic(kh_ptr_v[i], fill_lev, A_row_map_v[i], A_entries_v[i],
                    L_row_map_v[i], L_entries_v[i], U_row_map_v[i],
                    U_entries_v[i], nstreams);

    Kokkos::fence();

    Kokkos::resize(L_entries_v[i], spiluk_handle->get_nnzL());
    Kokkos::resize(L_values_v[i], spiluk_handle->get_nnzL());
    Kokkos::resize(U_entries_v[i], spiluk_handle->get_nnzU());
    Kokkos::resize(U_values_v[i], spiluk_handle->get_nnzU());
  }  // Done handle creation and spiluk_symbolic on all streams

  // Numeric phase
  spiluk_numeric_streams(instances, kh_ptr_v, fill_lev, A_row_map_v,
                         A_entries_v, A_values_v, L_row_map_v, L_entries_v,
                         L_values_v, U_row_map_v, U_entries_v, U_values_v);

  for (int i = 0; i < nstreams; i++) instances[i].fence();

  // Checking
  for (int i = 0; i < nstreams; i++) {
    auto spiluk_handle = kh_v[i].get_spiluk_handle();
    crsMat_t A("A_Mtx", nrows, nrows, nnz, A_values_v[i], A_row_map_v[i],
               A_entries_v[i]);
    crsMat_t L("L_Mtx", nrows, nrows, spiluk_handle->get_nnzL(), L_values_v[i],
               L_row_map_v[i], L_entries_v[i]);
    crsMat_t U("U_Mtx", nrows, nrows, spiluk_handle->get_nnzU(), U_values_v[i],
               U_row_map_v[i], U_entries_v[i]);

    // Create a reference view e set to all 1's
    ValuesType e_one("e_one", nrows);
    Kokkos::deep_copy(e_one, 1.0);

    // Create two views for spmv results
    ValuesType bb("bb", nrows);
    ValuesType bb_tmp("bb_tmp", nrows);

    // Compute norm2(L*U*e_one - A*e_one)/norm2(A*e_one)
    KokkosSparse::spmv("N", ONE, A, e_one, ZERO, bb);

    typename AT::mag_type bb_nrm = KokkosBlas::nrm2(bb);

    KokkosSparse::spmv("N", ONE, U, e_one, ZERO, bb_tmp);
    KokkosSparse::spmv("N", ONE, L, bb_tmp, MONE, bb);

    typename AT::mag_type diff_nrm = KokkosBlas::nrm2(bb);

    EXPECT_TRUE((diff_nrm / bb_nrm) < 1e-4);

    kh_v[i].destroy_spiluk_handle();
  }
}

}  // namespace Test

template <typename scalar_t, typename lno_t, typename size_type,
          typename device>
void test_spiluk() {
  Test::run_test_spiluk<scalar_t, lno_t, size_type, device>();
}

template <typename scalar_t, typename lno_t, typename size_type,
          typename device>
void test_spiluk_streams() {
  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_RP: 1 stream" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(0, 1);

  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_RP: 2 streams" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(0, 2);

  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_RP: 3 streams" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(0, 3);

  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_RP: 4 streams" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(0, 4);

  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_TP1: 1 stream" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(1, 1);

  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_TP1: 2 streams" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(1, 2);

  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_TP1: 3 streams" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(1, 3);

  std::cout << "SPILUKAlgorithm::SEQLVLSCHD_TP1: 4 streams" << std::endl;
  Test::run_test_spiluk_streams<scalar_t, lno_t, size_type, device>(1, 4);
}

#define KOKKOSKERNELS_EXECUTE_TEST(SCALAR, ORDINAL, OFFSET, DEVICE)        \
  TEST_F(TestCategory,                                                     \
         sparse##_##spiluk##_##SCALAR##_##ORDINAL##_##OFFSET##_##DEVICE) { \
    test_spiluk<SCALAR, ORDINAL, OFFSET, DEVICE>();                        \
    test_spiluk_streams<SCALAR, ORDINAL, OFFSET, DEVICE>();                \
  }

#define NO_TEST_COMPLEX

#include <Test_Common_Test_All_Type_Combos.hpp>

#undef KOKKOSKERNELS_EXECUTE_TEST
#undef NO_TEST_COMPLEX

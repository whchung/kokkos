/*
//@HEADER
// ************************************************************************
// 
//                        Kokkos v. 2.0
//              Copyright (2014) Sandia Corporation
// 
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact  H. Carter Edwards (hcedwar@sandia.gov)
// 
// ************************************************************************
//@HEADER
*/

#include <gtest/gtest.h>

#include <Kokkos_Core.hpp>

//----------------------------------------------------------------------------

#include <TestViewImpl.hpp>
#include <TestAtomic.hpp>

#include <TestViewAPI.hpp>
#include <TestViewSubview.hpp>

#include <TestRange.hpp>
#include <TestTeam.hpp>
#include <TestReduce.hpp>
#include <TestScan.hpp>
#include <TestAggregate.hpp>
#include <TestAggregateReduction.hpp>
#include <TestCompilerMacros.hpp>
#include <TestCXX11.hpp>
#include <TestCXX11Deduction.hpp>
#include <TestTeamVector.hpp>
#include <TestMemorySpaceTracking.hpp>
#include <TestTemplateMetaFunctions.hpp>

namespace Test {

class kalmar : public ::testing::Test {
protected:
  static void SetUpTestCase()
  {
    Kokkos::initialize();
  }

  static void TearDownTestCase()
  {
    Kokkos::finalize();
  }
};


TEST_F( kalmar, view_impl) {
  test_view_impl< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_api) {
  TestViewAPI< double , Kokkos::Kalmar >();
}


TEST_F( kalmar, view_subview_auto_1d_left ) {
  TestViewSubview::test_auto_1d< Kokkos::LayoutLeft,Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_auto_1d_right ) {
  TestViewSubview::test_auto_1d< Kokkos::LayoutRight,Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_auto_1d_stride ) {
  TestViewSubview::test_auto_1d< Kokkos::LayoutStride,Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_assign_strided ) {
  TestViewSubview::test_1d_strided_assignment< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_left_0 ) {
  TestViewSubview::test_left_0< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_left_1 ) {
  TestViewSubview::test_left_1< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_left_2 ) {
  TestViewSubview::test_left_2< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_left_3 ) {
  TestViewSubview::test_left_3< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_right_0 ) {
  TestViewSubview::test_right_0< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_right_1 ) {
  TestViewSubview::test_right_1< Kokkos::Kalmar >();
}

TEST_F( kalmar, view_subview_right_3 ) {
  TestViewSubview::test_right_3< Kokkos::Kalmar >();
}

TEST_F( kalmar , range_tag )
{
  TestRange< Kokkos::Kalmar >::test_for(1000);
  // TestRange< Kokkos::Kalmar >::test_reduce(1000);
  // TestRange< Kokkos::Kalmar >::test_scan(1000);
}

#if 0

TEST_F( kalmar , team_tag )
{
  TestTeamPolicy< Kokkos::Kalmar >::test_for(1000);
  TestTeamPolicy< Kokkos::Kalmar >::test_reduce(1000);
}

TEST_F( kalmar, long_reduce) {
  TestReduce< long ,   Kokkos::Kalmar >( 1000000 );
}

TEST_F( kalmar, double_reduce) {
  TestReduce< double ,   Kokkos::Kalmar >( 1000000 );
}

TEST_F( kalmar, long_reduce_dynamic ) {
  TestReduceDynamic< long ,   Kokkos::Kalmar >( 1000000 );
}

TEST_F( kalmar, double_reduce_dynamic ) {
  TestReduceDynamic< double ,   Kokkos::Kalmar >( 1000000 );
}

TEST_F( kalmar, long_reduce_dynamic_view ) {
  TestReduceDynamicView< long ,   Kokkos::Kalmar >( 1000000 );
}

TEST_F( kalmar, team_long_reduce) {
  TestReduceTeam< long ,   Kokkos::Kalmar >( 100000 );
}

TEST_F( kalmar, team_double_reduce) {
  TestReduceTeam< double ,   Kokkos::Kalmar >( 100000 );
}

TEST_F( kalmar, team_shared_request) {
  TestSharedTeam< Kokkos::Kalmar >();
}
#endif

TEST_F( kalmar , atomics )
{
  const int loop_count = 1e4 ;

  ASSERT_TRUE( ( TestAtomic::Loop<int,Kokkos::Kalmar>(loop_count,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<int,Kokkos::Kalmar>(loop_count,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<int,Kokkos::Kalmar>(loop_count,3) ) );

  ASSERT_TRUE( ( TestAtomic::Loop<unsigned int,Kokkos::Kalmar>(loop_count,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<unsigned int,Kokkos::Kalmar>(loop_count,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<unsigned int,Kokkos::Kalmar>(loop_count,3) ) );

  ASSERT_TRUE( ( TestAtomic::Loop<long int,Kokkos::Kalmar>(loop_count,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<long int,Kokkos::Kalmar>(loop_count,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<long int,Kokkos::Kalmar>(loop_count,3) ) );

  ASSERT_TRUE( ( TestAtomic::Loop<unsigned long int,Kokkos::Kalmar>(loop_count,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<unsigned long int,Kokkos::Kalmar>(loop_count,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<unsigned long int,Kokkos::Kalmar>(loop_count,3) ) );

  ASSERT_TRUE( ( TestAtomic::Loop<long long int,Kokkos::Kalmar>(loop_count,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<long long int,Kokkos::Kalmar>(loop_count,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<long long int,Kokkos::Kalmar>(loop_count,3) ) );

  ASSERT_TRUE( ( TestAtomic::Loop<double,Kokkos::Kalmar>(loop_count,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<double,Kokkos::Kalmar>(loop_count,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<double,Kokkos::Kalmar>(loop_count,3) ) );

  ASSERT_TRUE( ( TestAtomic::Loop<float,Kokkos::Kalmar>(100,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<float,Kokkos::Kalmar>(100,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<float,Kokkos::Kalmar>(100,3) ) );

#if defined( KOKKOS_ENABLE_ASM )
  ASSERT_TRUE( ( TestAtomic::Loop<Kokkos::complex<double> ,Kokkos::Kalmar>(100,1) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<Kokkos::complex<double> ,Kokkos::Kalmar>(100,2) ) );
  ASSERT_TRUE( ( TestAtomic::Loop<Kokkos::complex<double> ,Kokkos::Kalmar>(100,3) ) );
#endif
}

#if 0
TEST_F( kalmar , view_remap )
{
  enum { N0 = 3 , N1 = 2 , N2 = 8 , N3 = 9 };

  typedef Kokkos::View< double*[N1][N2][N3] ,
                             Kokkos::LayoutRight ,
                             Kokkos::Kalmar > output_type ;

  typedef Kokkos::View< int**[N2][N3] ,
                             Kokkos::LayoutLeft ,
                             Kokkos::Kalmar > input_type ;

  typedef Kokkos::View< int*[N0][N2][N3] ,
                             Kokkos::LayoutLeft ,
                             Kokkos::Kalmar > diff_type ;

  output_type output( "output" , N0 );
  input_type  input ( "input" , N0 , N1 );
  diff_type   diff  ( "diff" , N0 );

  int value = 0 ;
  for ( size_t i3 = 0 ; i3 < N3 ; ++i3 ) {
  for ( size_t i2 = 0 ; i2 < N2 ; ++i2 ) {
  for ( size_t i1 = 0 ; i1 < N1 ; ++i1 ) {
  for ( size_t i0 = 0 ; i0 < N0 ; ++i0 ) {
    input(i0,i1,i2,i3) = ++value ;
  }}}}

  // Kokkos::deep_copy( diff , input ); // throw with incompatible shape
  Kokkos::deep_copy( output , input );

  value = 0 ;
  for ( size_t i3 = 0 ; i3 < N3 ; ++i3 ) {
  for ( size_t i2 = 0 ; i2 < N2 ; ++i2 ) {
  for ( size_t i1 = 0 ; i1 < N1 ; ++i1 ) {
  for ( size_t i0 = 0 ; i0 < N0 ; ++i0 ) {
    ++value ;
    ASSERT_EQ( value , ((int) output(i0,i1,i2,i3) ) );
  }}}}
}

//----------------------------------------------------------------------------


TEST_F( kalmar , view_aggregate )
{
  TestViewAggregate< Kokkos::Kalmar >();
  TestViewAggregateReduction< Kokkos::Kalmar >();
}

//----------------------------------------------------------------------------

TEST_F( kalmar , scan )
{
  TestScan< Kokkos::Kalmar >::test_range( 1 , 1000 );
  TestScan< Kokkos::Kalmar >( 1000000 );
  TestScan< Kokkos::Kalmar >( 10000000 );
  Kokkos::Kalmar::fence();
}


TEST_F( kalmar , team_scan )
{
  TestScanTeam< Kokkos::Kalmar >( 10000 );
  TestScanTeam< Kokkos::Kalmar >( 10000 );
}

//----------------------------------------------------------------------------

TEST_F( kalmar , compiler_macros )
{
  ASSERT_TRUE( ( TestCompilerMacros::Test< Kokkos::Kalmar >() ) );
}

//----------------------------------------------------------------------------

TEST_F( kalmar , memory_space )
{
  TestMemorySpace< Kokkos::Kalmar >();
}

//----------------------------------------------------------------------------

TEST_F( kalmar , template_meta_functions )
{
  TestTemplateMetaFunctions<int, Kokkos::Kalmar >();
}

//----------------------------------------------------------------------------

#if defined( KOKKOS_HAVE_CXX11 ) && defined( KOKKOS_HAVE_DEFAULT_DEVICE_TYPE_OPENMP )
TEST_F( kalmar , cxx11 )
{
  if ( Kokkos::Impl::is_same< Kokkos::DefaultExecutionSpace , Kokkos::Kalmar >::value ) {
    ASSERT_TRUE( ( TestCXX11::Test< Kokkos::Kalmar >(1) ) );
    ASSERT_TRUE( ( TestCXX11::Test< Kokkos::Kalmar >(2) ) );
    ASSERT_TRUE( ( TestCXX11::Test< Kokkos::Kalmar >(3) ) );
    ASSERT_TRUE( ( TestCXX11::Test< Kokkos::Kalmar >(4) ) );
  }
}
#endif

#if defined (KOKKOS_HAVE_CXX11)
TEST_F( kalmar , reduction_deduction )
{
  TestCXX11::test_reduction_deduction< Kokkos::Kalmar >();
}

TEST_F( kalmar , team_vector )
{
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(0) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(1) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(2) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(3) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(4) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(5) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(6) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(7) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(8) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(9) ) );
  ASSERT_TRUE( ( TestTeamVector::Test< Kokkos::Kalmar >(10) ) );
}
#endif

#endif

} // namespace test


// @HEADER
// ************************************************************************
//
//                           Intrepid Package
//                 Copyright (2007) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
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
// Questions? Contact Pavel Bochev  (pbboche@sandia.gov)
//                    Denis Ridzal  (dridzal@sandia.gov), or
//                    Kara Peterson (kjpeter@sandia.gov)
//
// ************************************************************************
// @HEADER

/** \file   Intrepid_HCURL_HEX_I1_FEM.hpp
    \brief  Header file for the Intrepid::HCURL_HEX_I1_FEM class.
    \author Created by P. Bochev, D. Ridzal and K. Peterson.
 */

#ifndef INTREPID_HCURL_HEX_I1_FEM_HPP
#define INTREPID_HCURL_HEX_I1_FEM_HPP
#include "Intrepid_Basis.hpp"

namespace Intrepid {
  
/** \class  Intrepid::Basis_HCURL_HEX_I1_FEM
    \brief  Implementation of the default H(curl)-compatible FEM basis of degree 1 on Hexahedron cell 
  
            Implements Nedelec basis of degree 1 on the reference Hexahedron cell. The basis has
            cardinality 12 and spans an INCOMPLETE tri-linear polynomial space. Basis functions are dual 
            to a unisolvent set of degrees-of-freedom (DoF) defined and enumerated as follows:
  
  \verbatim
  ===================================================================================================
  |         |           degree-of-freedom-tag table                    |                            |
  |   DoF   |----------------------------------------------------------|       DoF definition       |
  | ordinal |  subc dim    | subc ordinal | subc DoF ord |subc num DoF |                            |
  |=========|==============|==============|==============|=============|============================|
  |    0    |       1      |       0      |       0      |      1      |   L_0(u) = (u.t)(0,-1,-1)  |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    1    |       1      |       1      |       0      |      1      |   L_1(u) = (u.t)(1,0,-1)   |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    2    |       1      |       2      |       0      |      1      |   L_2(u) = (u.t)(0,1,-1)   |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    3    |       1      |       3      |       0      |      1      |   L_3(u) = (u.t)(-1,0,-1)  |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    4    |       1      |       4      |       0      |      1      |   L_4(u) = (u.t)(0,-1,1)   |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    5    |       1      |       5      |       0      |      1      |   L_5(u) = (u.t)(1,0,1)    |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    6    |       1      |       6      |       0      |      1      |   L_6(u) = (u.t)(0,1,1)    |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    7    |       1      |       7      |       0      |      1      |   L_7(u) = (u.t)(-1,0,1)   |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    8    |       1      |       8      |       0      |      1      |   L_8(u) = (u.t)(-1,-1,0)  |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |    9    |       1      |       9      |       0      |      1      |   L_9(u) = (u.t)(1,-1,0)   |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |   10    |       1      |      10      |       0      |      1      |   L_10(u) = (u.t)(1,1,0)   |
  |---------|--------------|--------------|--------------|-------------|----------------------------|
  |   11    |       1      |      11      |       0      |      1      |   L_11(u) = (u.t)(-1,1,0)  |
  |=========|==============|==============|==============|=============|============================|
  |   MAX   |  maxScDim=1  |  maxScOrd=11 |  maxDfOrd=0  |      -      |                            |
  |=========|==============|==============|==============|=============|============================|
  \endverbatim
  
    \remarks
    \li     In the DoF functional \f${\bf t}\f$ is an edge tangent. Direction of edge  
            tangents follows the vertex order of the edges in the cell topology and runs from 
            edge vertex 0 to edge vertex 1, whereas their length is set equal to edge length. For 
            example, edge 8 of all Hexahedron reference cells has vertex order {0,4}, i.e., its tangent 
            runs from vertex 0 of the reference Hexahedron to vertex 4 of that cell. On the reference 
            Hexahedron the coordinates of these vertices are (-1,-1,-1) and (-1,-1,1), respectively. 
            Therefore, the tangent to edge 8 is (-1,-1, 1) - (-1,-1,-1) = (0, 0, 2). Because its length
            already equals edge length, no further rescaling of the edge tangent is needed. 
  
  \li       The length of the edge tangent equals the edge length. As a result, the DoF functional 
            is the value of the tangent component of a vector field at the edge midpoint times the 
            edge length. The resulting basis is equivalent to a basis defined by using the edge 
            circulation as a DoF functional. Note that all edges of reference Hexahedron<> cells 
            have length 2.  
  
 */
  
template<class Scalar, class ArrayScalar> 
class Basis_HCURL_HEX_I1_FEM : public Basis<Scalar, ArrayScalar>, public DofCoordsInterface<ArrayScalar> {
private:
  
  /** \brief  Initializes <var>tagToOrdinal_</var> and <var>ordinalToTag_</var> lookup arrays.
   */
  void initializeTags();
  
public:

  /** \brief  Constructor.
    */
  Basis_HCURL_HEX_I1_FEM();
  
    
  /** \brief  Evaluation of a FEM basis on a <strong>reference Hexahedron</strong> cell. 
    
              Returns values of <var>operatorType</var> acting on FEM basis functions for a set of
              points in the <strong>reference Hexahedron</strong> cell. For rank and dimensions of
              I/O array arguments see Section \ref basis_md_array_sec.
  
      \param  outputValues      [out] - rank-3 array with the computed basis values
      \param  inputPoints       [in]  - rank-2 array with dimensions (P,D) containing reference points  
      \param  operatorType      [in]  - operator applied to basis functions    
   */
  void getValues(ArrayScalar &          outputValues,
                 const ArrayScalar &    inputPoints,
                 const EOperator        operatorType) const;
  
  
  /**  \brief  FVD basis evaluation: invocation of this method throws an exception.
   */
  void getValues(ArrayScalar &          outputValues,
                 const ArrayScalar &    inputPoints,
                 const ArrayScalar &    cellVertices,
                 const EOperator        operatorType = OPERATOR_VALUE) const;

  /** \brief  Returns spatial locations (coordinates) of degrees of freedom on a
              <strong>reference Quadrilateral</strong>.

      \param  DofCoords      [out] - array with the coordinates of degrees of freedom,
                                     dimensioned (F,D)
  */
  void getDofCoords(ArrayScalar & DofCoords) const;
};
}// namespace Intrepid

#include "Intrepid_HCURL_HEX_I1_FEMDef.hpp"

#endif

#if defined(Intrepid_SHOW_DEPRECATED_WARNINGS)
#ifdef __GNUC__
#warning "The Intrepid package is deprecated"
#endif
#endif


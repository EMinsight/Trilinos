// @HEADER
//
// ***********************************************************************
//
//        MueLu: A package for multigrid based preconditioning
//                  Copyright 2012 Sandia Corporation
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
// Questions? Contact
//                    Jonathan Hu       (jhu@sandia.gov)
//                    Andrey Prokopenko (aprokop@sandia.gov)
//                    Ray Tuminaro      (rstumin@sandia.gov)
//
// ***********************************************************************
//
// @HEADER
#ifndef MUELU_SAPFACTORY_DECL_HPP
#define MUELU_SAPFACTORY_DECL_HPP

#include <string>

#include "MueLu_ConfigDefs.hpp"
#include "MueLu_SaPFactory_fwd.hpp"

#include "MueLu_Level_fwd.hpp"
#include "MueLu_ParameterListAcceptor.hpp"
#include "MueLu_PerfUtils_fwd.hpp"
#include "MueLu_PFactory.hpp"
#include "MueLu_TentativePFactory_fwd.hpp"
#include "MueLu_Utilities_fwd.hpp"

namespace MueLu {

  /*!
    @class SaPFactory class.
    @ingroup MueLuTransferClasses
    @brief Factory for building Smoothed Aggregation prolongators.

    ## Input/output of SaPFactory ##

    ### User parameters of SaPFactory ###
    Parameter | type | default | master.xml | validated | requested | description
    ----------|------|---------|:----------:|:---------:|:---------:|------------
    | sa: damping factor                     | double  | 1.33  | * | * |   | Damping factor for smoothed aggregation transfer operators |
    | sa: calculate eigenvalue estimate      | bool    | false | * | * |   | Force calculation of eigenvalue estimate during prolongator smoothing |
    | sa: eigenvalue estimate num iterations | int     | 10    | * | * |   | Number of power iterations to estimate max eigenvalue |
    | A                                      | Factory | null  |   | * | * | Generating factory of the matrix A used during the prolongator smoothing process |
    | P                                      | Factory | null  |   | * | * | Tentative prolongator factory (should be a TentativePFactory object). Note that if "P" is not provided the FactoryManager tries the factory which is generating the variable "Ptent" as input for "P". In the standard case using the default settings this is the non-smoothed tentative prolongation operator. |

    The * in the @c master.xml column denotes that the parameter is defined in the @c master.xml file.<br>
    The * in the @c validated column means that the parameter is declared in the list of valid input parameters (see SaPFactory::GetValidParameters).<br>
    The * in the @c requested column states that the data is requested as input with all dependencies (see SaPFactory::DeclareInput).

    ### Variables provided by SaPFactory ###

    After SaPFactory::Build the following data is available (if requested)

    Parameter | generated by | description
    ----------|--------------|------------
    | P       | SaPFactory   | Smoothed prolongator


  */

template <class Scalar = DefaultScalar,
          class LocalOrdinal = DefaultLocalOrdinal,
          class GlobalOrdinal = DefaultGlobalOrdinal,
          class Node = DefaultNode>
  class SaPFactory : public PFactory {
#undef MUELU_SAPFACTORY_SHORT
#include "MueLu_UseShortNames.hpp"

  public:

    //! @name Constructors/Destructors.
    //@{

    /*! @brief Constructor.
      User can supply a factory for generating the tentative prolongator.
    */
    SaPFactory() { }

    //! Destructor.
    virtual ~SaPFactory() { }

    RCP<const ParameterList> GetValidParameterList() const;

    //@}

    //! Input
    //@{

    void DeclareInput(Level &fineLevel, Level &coarseLevel) const;

    //@}

    //! @name Build methods.
    //@{

    /*!
      @brief Build method.

      Builds smoothed aggregation prolongator and returns it in <tt>coarseLevel</tt>.
      //FIXME what does the return code mean (unclear in MueMat)?
      */
    void Build(Level& fineLevel, Level &coarseLevel) const;

    void BuildP(Level &fineLevel, Level &coarseLevel) const; //Build()

    /*!
      @brief Enforce constraints on prolongator

      Modifies the prolongator so that all entries lie between 0 and 1. It also
      ensures that the row sum is between 0 and 1. This option only makes
      sense in the SA constext if the tentative prolgonator does not use
      the QR factorization.
      */
    void SatisfyPConstraints(RCP<Matrix> A, RCP<Matrix>& P) const;
    void optimalSatisfyPConstraintsForScalarPDEs(RCP<Matrix>& P) const;

    bool constrainRow(Scalar *orig, LocalOrdinal nEntries, Scalar leftBound, Scalar rghtBound,Scalar rsumTarget, Scalar *fixedUnsorted, Scalar *scalarData) const;



    //@}

  }; //class SaPFactory

} //namespace MueLu

#define MUELU_SAPFACTORY_SHORT
#endif // MUELU_SAPFACTORY_DECL_HPP

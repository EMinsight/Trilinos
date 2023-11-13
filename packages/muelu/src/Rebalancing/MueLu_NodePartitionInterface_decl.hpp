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
#ifndef MUELU_NODEPARTITIONINTERFACE_DECL_HPP
#define MUELU_NODEPARTITIONINTERFACE_DECL_HPP

#include "MueLu_ConfigDefs.hpp"

#if defined(HAVE_MPI)

#include <Xpetra_Matrix_fwd.hpp>
#include <Xpetra_VectorFactory_fwd.hpp>

#include "MueLu_SingleLevelFactoryBase.hpp"
#include "MueLu_NodePartitionInterface_fwd.hpp"

#include "MueLu_Level_fwd.hpp"
#include "MueLu_FactoryBase_fwd.hpp"

namespace MueLu {

  /*!
    @class NodePartitionInterface
    @brief Partitioning within a node only
    @ingroup Rebalancing

    This interface provides partitioning within a node

    ## Input/output of NodePartitionInterface ##

    ### User parameters of NodePartitionInterface ###
    Parameter | type | default | master.xml | validated | requested | description
    ----------|------|---------|:----------:|:---------:|:---------:|------------
    | A                                      | Factory | null  |   | * | * | Generating factory of the matrix A used during the prolongator smoothing process |
    | Coordinates                            | Factory | null  |   | * | (*) | Factory generating coordinates vector used for rebalancing. The coordinates are only needed when the chosen algorithm is 'multijagged' or 'rcb'.
    | ParameterList                          | ParamterList | null |  | * |  | NodePartition parameters
    | number of partitions                   | GO      | - |  |  |  | Short-cut parameter set by RepartitionFactory. Avoid repartitioning algorithms if only one partition is necessary (see details below)
    | NodeComm                               | Factory | null  |   | * | (*) | Factory generating NodeComm.

    The * in the @c master.xml column denotes that the parameter is defined in the @c master.xml file.<br>
    The * in the @c validated column means that the parameter is declared in the list of valid input parameters (see NodePartitionInterface::GetValidParameters).<br>
    The * in the @c requested column states that the data is requested as input with all dependencies (see NodePartitionInterface::DeclareInput).

    ### Variables provided by NodePartitionInterface ###

    After NodePartitionInterface::Build the following data is available (if requested)

    Parameter | generated by | description
    ----------|--------------|------------
    | Partition       | NodePartitionInterface   | GOVector based on the Row map of A (DOF-based) containing the process id the DOF should be living in after rebalancing/repartitioning

    The "Partition" vector is used as input for the RepartitionFactory class.
    If Re-partitioning/rebalancing is necessary it uses the "Partition" variable to create the corresponding Xpetra::Import object which then is used
    by the RebalanceFactory classes (e.g., RebalanceAcFactory, RebalanceTransferFactory,...) to rebalance the coarse level operators.

    The RepartitionHeuristicFactory calculates how many partitions are to be built when performing rebalancing.
    It stores the result in the "number of partitions" variable on the current level (type = GO).
    If it is "number of partitions=1" we skip the NodePartition call and just create an dummy "Partition" vector containing zeros only.
    If no repartitioning is necessary (i.e., just keep the current partitioning) we return "Partition = Teuchos::null".
    If "number of partitions" > 1, the algorithm tries to find the requested number of partitions.

  */

  //FIXME: this class should not be templated
  template <class Scalar,
            class LocalOrdinal = DefaultLocalOrdinal,
            class GlobalOrdinal = DefaultGlobalOrdinal,
            class Node = DefaultNode>
  class NodePartitionInterface : public SingleLevelFactoryBase {
#undef MUELU_NODEPARTITIONINTERFACE_SHORT
#include "MueLu_UseShortNames.hpp"

  public:

    //! @name Constructors/Destructors
    //@{

    //! Constructor
    NodePartitionInterface();

    //! Destructor
    virtual ~NodePartitionInterface() { }
    //@}

    RCP<const ParameterList> GetValidParameterList() const;

    //! @name Input
    //@{
    void DeclareInput(Level& currentLevel) const;
    //@}

    //! @name Build methods.
    //@{
    void Build(Level& currentLevel) const;

    //@}

  private:
    RCP<ParameterList> defaultNodePartitionParams;

  };  //class NodePartitionInterface

} //namespace MueLu

#define MUELU_NODEPARTITIONINTERFACE_SHORT
#endif //if defined(HAVE_MPI)

#endif // MUELU_NODEPARTITIONINTERFACE_DECL_HPP

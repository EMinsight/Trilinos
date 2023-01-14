// @HEADER
//
// ***********************************************************************
//
//             Xpetra: A linear algebra interface package
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
#ifndef XPETRA_ROWGRAPH_HPP
#define XPETRA_ROWGRAPH_HPP

/* this file is automatically generated - do not edit (see script/interfaces.py) */

#include <Teuchos_Describable.hpp>
#include <KokkosCompat_DefaultNode.hpp>
#include "Xpetra_ConfigDefs.hpp"
#include "Xpetra_Map.hpp"
#include "Xpetra_Import.hpp"
#include "Xpetra_Export.hpp"

namespace Xpetra {

  template<class LocalOrdinal,
           class GlobalOrdinal,
           class Node = KokkosClassic::DefaultNode::DefaultNodeType>
  class RowGraph
    : virtual public Teuchos::Describable
  {
  public:
    typedef LocalOrdinal local_ordinal_type;
    typedef GlobalOrdinal global_ordinal_type;
    typedef Node node_type;

    //! @name Constructor/Destructor Methods
    //@{

    //! Destructor.
    virtual ~RowGraph() { }

   //@}

    //! @name Graph Query Methods
    //@{

    //! Returns the communicator.
    virtual const Teuchos::RCP< const Teuchos::Comm< int > >  getComm() const = 0;


    //! Returns the Map that describes the row distribution in this graph.
    virtual const Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getRowMap() const = 0;

    //! Returns the Map that describes the column distribution in this graph.
    virtual const Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getColMap() const = 0;

    //! Returns the Map associated with the domain of this graph.
    virtual const Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getDomainMap() const = 0;

    //! Returns the Map associated with the domain of this graph.
    virtual const Teuchos::RCP< const Map< LocalOrdinal, GlobalOrdinal, Node > >  getRangeMap() const = 0;

    //! Returns the importer associated with this graph.
    virtual Teuchos::RCP< const Import< LocalOrdinal, GlobalOrdinal, Node > > getImporter() const = 0;

    //! Returns the exporter associated with this graph.
    virtual Teuchos::RCP< const Export< LocalOrdinal, GlobalOrdinal, Node > > getExporter() const = 0;

    //! Returns the number of global rows in the graph.
    virtual global_size_t getGlobalNumRows() const = 0;

    //! Returns the number of global columns in the graph.
    virtual global_size_t getGlobalNumCols() const = 0;

    //! Returns the number of rows owned on the calling node.
    virtual size_t getLocalNumRows() const = 0;

    //! Returns the number of columns connected to the locally owned rows of this graph.
    virtual size_t getLocalNumCols() const = 0;

    //! Returns the index base for global indices for this graph.
    virtual GlobalOrdinal getIndexBase() const = 0;

    //! Returns the global number of entries in the graph.
    virtual global_size_t getGlobalNumEntries() const = 0;

    //! Returns the local number of entries in the graph.
    virtual size_t getNodeNumEntries() const = 0;

    //! Returns the current number of entries on this node in the specified global row.
    virtual size_t getNumEntriesInGlobalRow(GlobalOrdinal globalRow) const = 0;

    //! Returns the current number of entries on this node in the specified local row.
    virtual size_t getNumEntriesInLocalRow(LocalOrdinal localRow) const = 0;

    //! Returns the maximum number of entries across all rows/columns on all nodes.
    virtual size_t getGlobalMaxNumRowEntries() const = 0;

    //! Returns the maximum number of entries across all rows/columns on this node.
    virtual size_t getLocalMaxNumRowEntries() const = 0;

    //! Indicates whether the graph has a well-defined column map.
    virtual bool hasColMap() const = 0;

    //! If graph indices are in the local range, this function returns true. Otherwise, this function returns false. */.
    virtual bool isLocallyIndexed() const = 0;

    //! If graph indices are in the global range, this function returns true. Otherwise, this function returns false. */.
    virtual bool isGloballyIndexed() const = 0;

    //! Returns true if fillComplete() has been called.
    virtual bool isFillComplete() const = 0;

    //@}

    //! @name Extraction Methods
    //@{

    //! Extract a list of entries in a specified global row of the graph. Put into pre-allocated storage.
    virtual void getGlobalRowCopy(GlobalOrdinal GlobalRow, const Teuchos::ArrayView< GlobalOrdinal > &Indices, size_t &NumIndices) const = 0;

    //! Extract a list of entries in a specified local row of the graph. Put into storage allocated by calling routine.
    virtual void getLocalRowCopy(LocalOrdinal LocalRow, const Teuchos::ArrayView< LocalOrdinal > &Indices, size_t &NumIndices) const = 0;


    //@}

  }; // RowGraph class

} // Xpetra namespace

#define XPETRA_ROWGRAPH_SHORT
#endif // XPETRA_ROWGRAPH_HPP

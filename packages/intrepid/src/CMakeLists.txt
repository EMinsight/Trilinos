

#
# A) Package-specific configuration options
#

TRIBITS_CONFIGURE_FILE(Intrepid_config.h)

#
# B) Define the header and source files (and directories)
#

#
# src
#

SET(HEADERS "")
SET(SOURCES "")

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

APPEND_SET(HEADERS
  ${CMAKE_CURRENT_BINARY_DIR}/Intrepid_config.h
  )

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

#
# All headers
#

APPEND_SET(HEADERS
  Intrepid_ConfigDefs.hpp
  )

#
# Shared headers
#

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Shared)
APPEND_SET(HEADERS
  Shared/Intrepid_ArrayToolsDefCloneScale.hpp
  Shared/Intrepid_ArrayToolsDefContractions.hpp
  Shared/Intrepid_ArrayToolsDefDot.hpp
  Shared/Intrepid_ArrayToolsDefScalar.hpp
  Shared/Intrepid_ArrayToolsDefTensor.hpp
  Shared/Intrepid_ArrayTools.hpp
  Shared/Intrepid_BurkardtRules.hpp
  Shared/Intrepid_BurkardtRulesDef.hpp
  Shared/Intrepid_FieldContainerDef.hpp
  Shared/Intrepid_FieldContainer.hpp
  Shared/Intrepid_PointToolsDef.hpp
  Shared/Intrepid_PointTools.hpp
  Shared/Intrepid_PolylibDef.hpp
  Shared/Intrepid_Polylib.hpp
  Shared/Intrepid_Rank.hpp
  Shared/Intrepid_RealSpaceToolsDef.hpp
  Shared/Intrepid_RealSpaceTools.hpp
  Shared/Intrepid_Types.hpp
  Shared/Intrepid_Utils.hpp
  )

  APPEND_SET(HEADERS ${HEADERS}
  )

#
# Discretization headers
#

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Discretization/Integration)
TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Discretization/FunctionSpaceTools)
TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Discretization/Basis)
TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Discretization/TensorProductSpaceTools)

APPEND_SET(HEADERS  
  Discretization/Integration/Intrepid_AdaptiveSparseGridInterfaceDef.hpp
  Discretization/Integration/Intrepid_AdaptiveSparseGridInterface.hpp
  Discretization/Integration/Intrepid_AdaptiveSparseGridDef.hpp
  Discretization/Integration/Intrepid_AdaptiveSparseGrid.hpp
  Discretization/Integration/Intrepid_Cubature.hpp
  Discretization/Integration/Intrepid_CubatureControlVolumeDef.hpp
  Discretization/Integration/Intrepid_CubatureControlVolume.hpp
  Discretization/Integration/Intrepid_CubatureControlVolumeSideDef.hpp
  Discretization/Integration/Intrepid_CubatureControlVolumeSide.hpp
  Discretization/Integration/Intrepid_CubatureControlVolumeBoundaryDef.hpp
  Discretization/Integration/Intrepid_CubatureControlVolumeBoundary.hpp
  Discretization/Integration/Intrepid_CubatureDirectDef.hpp
  Discretization/Integration/Intrepid_CubatureDirect.hpp
  Discretization/Integration/Intrepid_CubatureDirectLineGaussDef.hpp
  Discretization/Integration/Intrepid_CubatureDirectLineGauss.hpp
  Discretization/Integration/Intrepid_CubatureDirectLineGaussJacobi20.hpp
  Discretization/Integration/Intrepid_CubatureDirectLineGaussJacobi20Def.hpp
  Discretization/Integration/Intrepid_CubatureDirectTetDefaultDef.hpp
  Discretization/Integration/Intrepid_CubatureDirectTetDefault.hpp
  Discretization/Integration/Intrepid_CubatureDirectTriDefaultDef.hpp
  Discretization/Integration/Intrepid_CubatureDirectTriDefault.hpp
  Discretization/Integration/Intrepid_CubatureCompositeTetDef.hpp
  Discretization/Integration/Intrepid_CubatureCompositeTet.hpp
  Discretization/Integration/Intrepid_CubatureGenSparseDef.hpp
  Discretization/Integration/Intrepid_CubatureGenSparse.hpp
  Discretization/Integration/Intrepid_CubatureLineSortedDef.hpp
  Discretization/Integration/Intrepid_CubatureLineSorted.hpp
  Discretization/Integration/Intrepid_CubatureSparseDef.hpp
  Discretization/Integration/Intrepid_CubatureSparse.hpp
  Discretization/Integration/Intrepid_CubatureSparseHelper.hpp
  Discretization/Integration/Intrepid_CubatureTensorDef.hpp
  Discretization/Integration/Intrepid_CubatureTensor.hpp
  Discretization/Integration/Intrepid_CubatureTensorPyr.hpp
  Discretization/Integration/Intrepid_CubatureTensorPyrDef.hpp
  Discretization/Integration/Intrepid_CubatureTensorSortedDef.hpp
  Discretization/Integration/Intrepid_CubatureTensorSorted.hpp
  Discretization/Integration/Intrepid_CubaturePolygonDef.hpp
  Discretization/Integration/Intrepid_CubaturePolygon.hpp
  Discretization/Integration/Intrepid_CubaturePolylib.hpp
  Discretization/Integration/Intrepid_CubaturePolylibDef.hpp
  Discretization/Integration/Intrepid_DefaultCubatureFactoryDef.hpp
  Discretization/Integration/Intrepid_DefaultCubatureFactory.hpp
  Discretization/FunctionSpaceTools/Intrepid_FunctionSpaceToolsDef.hpp
  Discretization/FunctionSpaceTools/Intrepid_FunctionSpaceTools.hpp
  Discretization/FunctionSpaceTools/Intrepid_FunctionSpaceToolsInPlaceDef.hpp
  Discretization/FunctionSpaceTools/Intrepid_FunctionSpaceToolsInPlace.hpp
  Discretization/Basis/Intrepid_BasisDef.hpp
  Discretization/Basis/Intrepid_Basis.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_C1_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_C2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_C2_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_I2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_I2_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_Cn_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_HEX_Cn_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_LINE_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_LINE_C1_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_LINE_Cn_FEM_JACOBI.hpp
  Discretization/Basis/Intrepid_HGRAD_LINE_Cn_FEM_JACOBIDef.hpp
  Discretization/Basis/Intrepid_HGRAD_LINE_Cn_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_LINE_Cn_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_POLY_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_POLY_C1_FEMDef.hpp  
  Discretization/Basis/Intrepid_HGRAD_QUAD_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_QUAD_C1_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_QUAD_C2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_QUAD_C2_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_QUAD_Cn_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_QUAD_Cn_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_C1_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_C2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_C2_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_COMP12_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_COMP12_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TRI_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_TRI_C1_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TRI_C2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_TRI_C2_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_WEDGE_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_WEDGE_C1_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_WEDGE_C2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_WEDGE_C2_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_WEDGE_I2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_WEDGE_I2_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_PYR_C1_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_PYR_C1_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_PYR_I2_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_PYR_I2_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_HEX_I1_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_HEX_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_HEX_In_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_HEX_In_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_TET_I1_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_TET_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_WEDGE_I1_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_WEDGE_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_TRI_I1_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_TRI_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_QUAD_I1_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_QUAD_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_QUAD_In_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_QUAD_In_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_HEX_I1_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_HEX_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_HEX_In_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_HEX_In_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_TET_I1_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_TET_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_TRI_I1_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_TRI_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_QUAD_I1_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_QUAD_I1_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_QUAD_In_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_QUAD_In_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_WEDGE_I1_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_WEDGE_I1_FEMDef.hpp 
  Discretization/Basis/Intrepid_HGRAD_TRI_Cn_FEM_ORTH.hpp
  Discretization/Basis/Intrepid_HGRAD_TRI_Cn_FEM_ORTHDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_Cn_FEM_ORTH.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_Cn_FEM_ORTHDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TRI_Cn_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_TRI_Cn_FEMDef.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_Cn_FEM.hpp
  Discretization/Basis/Intrepid_HGRAD_TET_Cn_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_TRI_In_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_TRI_In_FEMDef.hpp
  Discretization/Basis/Intrepid_HDIV_TET_In_FEM.hpp
  Discretization/Basis/Intrepid_HDIV_TET_In_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_TRI_In_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_TRI_In_FEMDef.hpp
  Discretization/Basis/Intrepid_HCURL_TET_In_FEM.hpp
  Discretization/Basis/Intrepid_HCURL_TET_In_FEMDef.hpp
  Discretization/Basis/Intrepid_OrthogonalBases.hpp
  Discretization/Basis/Intrepid_OrthogonalBasesDef.hpp
  Discretization/Basis/Intrepid_ProductTopology.hpp
  Discretization/Basis/Intrepid_ProductTopologyDef.hpp
  Discretization/Basis/Intrepid_TensorBasis.hpp
  Discretization/TensorProductSpaceTools/Intrepid_TensorProductSpaceTools.hpp
  Discretization/TensorProductSpaceTools/Intrepid_TensorProductSpaceToolsDef.hpp
  )

#
# Cell headers
#

TRIBITS_INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Cell)
APPEND_SET(HEADERS
  Cell/Intrepid_CellTools.hpp
  Cell/Intrepid_CellToolsDef.hpp
  )

#
# All sources
#

APPEND_SET(SOURCES
  Intrepid_Version.cpp
  Shared/Intrepid_Utils.cpp
  )


IF (TPL_ENABLE_MPI)
ENDIF()


#
# C) Define the targets for package's library(s)
# 

  TRIBITS_ADD_LIBRARY(
    intrepid
    HEADERS ${HEADERS}
    SOURCES ${SOURCES}
    )

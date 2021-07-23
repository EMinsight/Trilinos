// @HEADER
// ****************************************************************************
//                Tempus: Copyright (2017) Sandia Corporation
//
// Distributed under BSD 3-clause license (See accompanying file Copyright.txt)
// ****************************************************************************
// @HEADER

#ifndef Tempus_Stepper_ErrorNorm_decl_hpp
#define Tempus_Stepper_ErrorNorm_decl_hpp

#include "Tempus_config.hpp"

#include "Teuchos_RCPDecl.hpp"
#include "Thyra_VectorBase.hpp"
#include "Thyra_VectorSpaceFactoryBase.hpp"
namespace Tempus {

template<class Scalar>
class Stepper_ErrorNorm
{

  public:

    // ctor
    Stepper_ErrorNorm();

    Stepper_ErrorNorm(const Scalar relTol, const Scalar absTol);

    ~Stepper_ErrorNorm() {};

    Scalar computeErrorNorm(const Teuchos::RCP<const Thyra::VectorBase<Scalar>> &x, const Teuchos::RCP<const Thyra::VectorBase<Scalar>> &errorVector);

    void setRelativeTolerance(const Scalar relTol) { relTol_ = relTol; }
    void setAbsoluteTolerance(const Scalar absTol) { abssTol_ = absTol; }

  
  protected:

    Scalar errorNorm_(const Teuchos::RCP<const Thyra::VectorBase<Scalar>> &x);


    Scalar relTol_;
    Scalar abssTol_;
    Teuchos::RCP<const Thyra::VectorBase<Scalar>> x_;
    Teuchos::RCP<const Thyra::VectorBase<Scalar>> errorWeightVector_;
    Teuchos::RCP<Thyra::VectorBase<Scalar>> scratchVector_;

};

} // namespace Tempus
#endif //Tempus_Stepper_ErrorNorm_decl_hpp

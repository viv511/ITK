/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkNonLinearOptimizer.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef __itkNonLinearOptimizer_h
#define __itkNonLinearOptimizer_h

#include "itkOptimizer.h"


namespace itk
{
  
/** \class NonLinearOptimizer
 * \brief Wrap of the vnl_nonlinear_minimizer to be adapted 
 *
 */
template <class TCostFunction>
class ITK_EXPORT NonLinearOptimizer : public Optimizer<TCostFunction>

{
public:
  /**
   * Standard "Self" typedef.
   */
  typedef NonLinearOptimizer  Self;

  /**
   * Standard "Superclass" typedef.
   */
  typedef  Optimizer<TCostFunction>   Superclass;

  /** 
   * Smart pointer typedef support 
   */
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;


  /**
   *  Parameters type.
   *  it defines a position in the optimization search space
   */
  typedef typename TCostFunction::ParametersType ParametersType;


  /**
   *  Measure type.
   *  it defines a type used to return the cost function value 
   */
  typedef typename TCostFunction::MeasureType MeasureType;


  /**
   *  Derivative type.
   *  it defines a type used to return the cost function derivative 
   */
  typedef typename TCostFunction::DerivativeType DerivativeType;




 /** 
   * Run-time type information (and related methods).
   */
  itkTypeMacro( NonLinearOptimizer, Optimizer );


  /**
   * Method for creation through the object factory.
   */
  itkNewMacro(Self);
  

protected:

  NonLinearOptimizer() {};
  virtual ~NonLinearOptimizer() {};
  NonLinearOptimizer(const Self&) {}
  void operator=(const Self&) {}

};

} // end namespace itk


#endif




/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkCenteredRigid2DTransformTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <iostream>

#include "itkCenteredRigid2DTransform.h"
#include "vnl/vnl_vector_fixed.h"
#include "itkVector.h"


int itkCenteredRigid2DTransformTest(int ,char *[] )
{

  std::cout << "==================================" << std::endl;
  std::cout << "Testing CenteredRigid 2D Transform" << std::endl << std::endl;

  const double epsilon = 1e-10;
  const unsigned int N = 2;
  bool Ok = true;

  typedef itk::CenteredRigid2DTransform<double>  CenteredRigidTransformType;
  CenteredRigidTransformType::Pointer transform = CenteredRigidTransformType::New();
  
  // 15 degrees in radians
  const double angle = 15.0 * atan( 1.0f ) / 45.0; 
  const double sinth = sin( angle );
  const double costh = cos( angle );


  std::cout << "Testing Rotation:";
  transform->SetAngle(angle);

  // Rotate an itk::Point
  CenteredRigidTransformType::InputPointType::ValueType pInit[2] = {10,10};
  CenteredRigidTransformType::InputPointType p = pInit;
  CenteredRigidTransformType::InputPointType q;

  q[0] =  p[0] * costh - p[1] * sinth;
  q[1] =  p[0] * sinth + p[1] * costh;

  CenteredRigidTransformType::OutputPointType r;
  r = transform->TransformPoint( p );
  for(unsigned int i=0; i<N; i++)
  {
     if( fabs( q[i]- r[i] ) > epsilon )
     {
        Ok = false;
        break;    
     }
  }
  if( !Ok )
  { 
    std::cerr << "Error rotating point   : " << p << std::endl;
    std::cerr << "Result should be       : " << q << std::endl;
    std::cerr << "Reported Result is     : " << r << std::endl;
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << " [ PASSED ] " << std::endl;
  }

  
  std::cout << "Testing Translation:";

  transform->SetAngle(0);
  
  CenteredRigidTransformType::OffsetType::ValueType ioffsetInit[2] = {1,4};
  CenteredRigidTransformType::OffsetType ioffset = ioffsetInit;

  transform->SetOffset( ioffset );

  q = p + ioffset;
      
  r = transform->TransformPoint( p );
  for(unsigned int i=0; i<N; i++)
  {
    if( fabs( q[i]- r[i] ) > epsilon )
    {
      Ok = false;
      break;    
    }
  }
  if( !Ok )
  { 
    std::cerr << "Error translating point: " << p << std::endl;
    std::cerr << "Result should be       : " << q << std::endl;
    std::cerr << "Reported Result is     : " << r << std::endl;
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << " [ PASSED ] " << std::endl;
  }

  {
    std::cout << "Testing Inverse:";

    // Populate the transform with some parameters
    CenteredRigidTransformType::Pointer transform = CenteredRigidTransformType::New();
    const double a = 0.175;
    transform->SetAngle( a);

    CenteredRigidTransformType::InputPointType c;
    c[0] = 13.456;
    c[1] = 45.890;
    transform->SetCenter( c );

    CenteredRigidTransformType::OutputVectorType t;
    t[0] = 9.873;
    t[1] = 40.312;
    transform->SetTranslation( t );

    // Transform point p1 to obtain p2
    CenteredRigidTransformType::InputPointType p1;
    p1[0] = 5.63;
    p1[1] = 9.02;

    CenteredRigidTransformType::OutputPointType p2 = 
      transform->TransformPoint( p1 );

    // Get inverse transform and transform point p2 to obtain point p3
    CenteredRigidTransformType::Pointer inverse = transform->Inverse();

    CenteredRigidTransformType::OutputPointType p3 = 
      inverse->TransformPoint( p2 );

    // Check that point p3 is the same as point p1
    Ok = true;
    for ( unsigned int i = 0; i < N; i++ )
      {
      if ( fabs( p1[i] - p3[i] ) > epsilon )
        {
        Ok = false;
        break;
        }
      }
    if( !Ok )
    { 
      std::cerr << "Error in inverse computation" << std::endl;
      std::cerr << "Result should be       : " << p1 << std::endl;
      std::cerr << "Reported Result is     : " << p3 << std::endl;
      return EXIT_FAILURE;
    }
    else
    {
      std::cout << " [ PASSED ] " << std::endl;
    }
    
  }
  return EXIT_SUCCESS;

}

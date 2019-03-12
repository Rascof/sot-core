/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 */

#ifndef __SOT_NeckLimitation_H__
#define __SOT_NeckLimitation_H__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* Matrix */
#include <dynamic-graph/linear-algebra.h>
namespace dg = dynamicgraph;

/* SOT */
#include <dynamic-graph/entity.h>
#include <dynamic-graph/all-signals.h>
#include <sot/core/task-abstract.hh>

/* STD */
#include <string>
#include <map>
#include <list>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32)
#  if defined (neck_limitation_EXPORTS)
#    define NeckLimitation_EXPORT __declspec(dllexport)
#  else
#    define NeckLimitation_EXPORT __declspec(dllimport)
#  endif
#else
#  define NeckLimitation_EXPORT
#endif

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */

namespace dynamicgraph { namespace sot {

namespace dg = dynamicgraph;

class NeckLimitation_EXPORT NeckLimitation
:public dg::Entity
{
 public:
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

 protected:

  unsigned int panRank,tiltRank;
  static const unsigned int PAN_RANK_DEFAULT;
  static const unsigned int TILT_RANK_DEFAULT;


  /* The limitation is: sgn.Tilt >= Pan.alpha + beta, with alpha the linear
  * coefficient and beta the affine one, and sgn is +1 or -1. */
  double coeffLinearPan,coeffAffinePan;
  double signTilt;
  static const double COEFF_LINEAR_DEFAULT;
  static const double COEFF_AFFINE_DEFAULT;
  static const double SIGN_TILT_DEFAULT;

 public: /* --- CONSTRUCTION --- */

  NeckLimitation( const std::string& name );
  virtual ~NeckLimitation( void );

 public: /* --- SIGNAL --- */
  dg::SignalPtr<dg::Vector,int> jointSIN;
  dg::SignalTimeDependent<dg::Vector,int> jointSOUT;

 public: /* --- FUNCTIONS --- */
  dg::Vector& computeJointLimitation( dg::Vector& jointLimited,const int& timeSpec );

 public: /* --- PARAMS --- */
  virtual void display( std::ostream& os ) const;
};


} /* namespace sot */} /* namespace dynamicgraph */



#endif // #ifndef __SOT_NeckLimitation_H__

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      factory.h
 * Project:   SOT
 * Author:    Nicolas Mansard
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#ifndef __SOT_FACTORY_HH__
#define __SOT_FACTORY_HH__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* --- STD --- */
#include <map>
#include <string>

/* --- SOT --- */
#include <sot-core/exception-factory.h>
#include <sot-core/sot-core-api.h>
#include <dynamic-graph/factory.h>

namespace sot {

class sotFeatureAbstract;
class sotTaskAbstract;

/* --------------------------------------------------------------------- */
/* --- FACTORY ---------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/*! @ingroup factory
  \brief This class implements the factory that allows creation of
  objects loaded from dynamic link libraries. Objects are referenced by their
  class names, and can be created by passing this string to one of the three
  public "new" methods (newEntity, newFeature or newTask).
  The factory instance (singleton) is publicly available under the name sotFactory
  (include factory.h).  A task, feature or entity can register itself by
   using the SOT_FACTORY_{ENTITY,TASK,FEATURE}_PLUGIN macro. See sotTask.cpp for
   an example.
*/
class SOT_CORE_EXPORT sotFactoryStorage
{
 public:
  typedef sotFeatureAbstract* (*FeatureConstructor_ptr)( const std::string& );
  typedef sotTaskAbstract* (*TaskConstructor_ptr)( const std::string& );
  
 protected:
  typedef std::map< std::string,TaskConstructor_ptr > TaskMap;
  typedef std::map< std::string,FeatureConstructor_ptr > FeatureMap;

  FeatureMap featureMap;
  TaskMap taskMap;

 public:

  ~sotFactoryStorage( void );

  void registerTask( const std::string& entname,TaskConstructor_ptr ent );
  sotTaskAbstract* newTask( const std::string& name,const std::string& objname );
  bool existTask( const std::string& name, TaskMap::iterator& entPtr );
  bool existTask( const std::string& name );

  void registerFeature( const std::string& entname,FeatureConstructor_ptr ent );
  sotFeatureAbstract* newFeature( const std::string& name,const std::string& objname );
  bool existFeature( const std::string& name, FeatureMap::iterator& entPtr );
  bool existFeature( const std::string& name );

  void  commandLine( const std::string& cmdLine,std::istringstream& cmdArgs,
		     std::ostream& os );


};

SOT_CORE_EXPORT extern sotFactoryStorage sotFactory;

/* --- REGISTERER ----------------------------------------------------------- */
/* --- REGISTERER ----------------------------------------------------------- */
/* --- REGISTERER ----------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* --- ENTITY REGISTERER ---------------------------------------------------- */
/* -------------------------------------------------------------------------- */
typedef dynamicgraph::EntityRegisterer sotEntityRegisterer;

#define SOT_FACTORY_ENTITY_PLUGIN(sotClassType,className) \
	DYNAMICGRAPH_FACTORY_ENTITY_PLUGIN(sotClassType, className)

/* -------------------------------------------------------------------------- */
/* --- FEATURE REGISTERER --------------------------------------------------- */
/* -------------------------------------------------------------------------- */

class SOT_CORE_EXPORT sotFeatureRegisterer
{
 private:
  sotFeatureRegisterer( void );

 public:
  sotFeatureRegisterer( const std::string& featureClassName,
			sotFactoryStorage::FeatureConstructor_ptr maker);
};

#define SOT_FACTORY_FEATURE_PLUGIN(sotFeatureType,className) \
  const std::string sotFeatureType::CLASS_NAME = className;  \
  extern "C" {                                               \
    sotFeatureAbstract *sotFeatureMaker##_##sotFeatureType( const std::string& objname )\
    {                                                        \
      return new sotFeatureType( objname );                  \
    }                                                        \
  sotFeatureRegisterer reg##_##sotFeatureType( className,    \
					       &sotFeatureMaker##_##sotFeatureType );   \
  }                                                          \


/* -------------------------------------------------------------------------- */
/* --- TASK REGISTERER ------------------------------------------------------ */
/* -------------------------------------------------------------------------- */

class SOT_CORE_EXPORT sotTaskRegisterer
{
 private:
  sotTaskRegisterer( void );

 public:
  sotTaskRegisterer( const std::string& taskClassName,
		     sotFactoryStorage::TaskConstructor_ptr maker);
};


#define SOT_FACTORY_TASK_PLUGIN(sotTaskType,className) \
  const std::string sotTaskType::CLASS_NAME = className; \
  extern "C" {                                            \
    sotTaskAbstract *sotTaskMaker##_##sotTaskType( const std::string& objname )    \
    {                                                     \
      return new sotTaskType( objname );                 \
    }                                                     \
  sotTaskRegisterer reg##_##sotTaskType( className,&sotTaskMaker##_##sotTaskType );   \
  }                                                       \

} // namespace sot

#endif /* #ifndef __SOT_FACTORY_HH__ */




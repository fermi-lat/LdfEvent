#ifndef LSF_METAEVENT_H
#define LSF_METAEVENT_H 1

#include <iostream>
#include "GaudiKernel/StreamBuffer.h"

#include "Event/TopLevel/Definitions.h"

#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/IInterface.h"

#include "lsfData/LsfMetaEvent.h"

/** @class MetaEvent
*
* $Header: /nfs/slac/g/glast/ground/cvs/LdfEvent/LdfEvent/LsfMetaEvent.h,v 1.6 2006/04/14 16:38:52 heather Exp $
*/

static const CLID& CLID_MetaEvent = InterfaceID("MetaEvent", 1, 0);

namespace LsfEvent {
  
  class MetaEvent : public DataObject {
    
  public:
    
    /// Default c'tor.  Assigns sentinel or null values to all fields
    MetaEvent()
      :m_config(0),
       m_type(enums::Lsf::NoRunType),
       m_keys(0),
       m_ktype(enums::Lsf::NoKeysType) {
    }

    /// Standard c'tor.  Takes input values for all fields
    MetaEvent( const lsfData::RunInfo& run, 
               const lsfData::DatagramInfo& datagram, 
	       const lsfData::GemScalers& scalers,
	       const lsfData::Time& time,
	       const lsfData::Configuration& configuration,
               const lsfData::LsfKeys& keys )
      :m_run(run),m_datagram(datagram),
       m_scalers(scalers),
       m_time(time),
       m_config(configuration.clone()),
       m_type(configuration.type()),
       m_keys(keys.clone()),
       m_ktype(keys.type()) {
    }

    /// Copy c'tor.  Just copy all values.  
    /// Does a deep copy of the configuration and uses the configuration type to deduce the run type
    MetaEvent( const MetaEvent& other )
      :DataObject(other),
       m_run(other.run()),
       m_datagram(other.datagram()),
       m_scalers(other.scalers()),
       m_time(other.time()),
       m_config(0),
       m_type(enums::Lsf::NoRunType),
       m_keys(0),
       m_ktype(enums::Lsf::NoKeysType) {
      if ( other.configuration() != 0 ) {
	m_config = other.configuration()->clone();
	m_type = other.configuration()->type();
      }
      if ( other.keys() != 0) {
          m_keys = other.keys()->clone();
          m_ktype = other.keys()->type();
      }
    }
    
    MetaEvent( const lsfData::MetaEvent& other )
       :m_run(other.run()),
       m_datagram(other.datagram()),
       m_scalers(other.scalers()),
       m_time(other.time()),
       m_config(0),
       m_type(enums::Lsf::NoRunType),
       m_keys(0),
       m_ktype(enums::Lsf::NoKeysType) {

       if ( other.configuration() != 0 ) {
	m_config = other.configuration()->clone();
	m_type = other.configuration()->type();
       }
       if (other.keys() != 0) {
            m_keys = other.keys()->clone();
            m_ktype = other.keys()->type();
       }
    }

    /// D'tor.  Delete the configuration, which had been deep-copied
    virtual ~MetaEvent(){
      if (m_config) {
          delete m_config;
        m_config = 0;
      }
      if (m_keys) {
          delete m_keys;
          m_keys = 0;
      }
    }

    /// Retrieve reference to class definition structure
    virtual const CLID& clID() const   { return MetaEvent::classID(); }
    static const CLID& classID()       { return CLID_MetaEvent; }
    
    /// Information about the run this event is from
    inline const lsfData::RunInfo& run() const { return m_run; };

    /// Information about the datagram this event came in
    inline const lsfData::DatagramInfo& datagram() const { return m_datagram; }

    /// The extended context records
    inline const lsfData::GemScalers& scalers() const { return m_scalers; }

    /// Information about the time markers associated with this event
    inline const lsfData::Time& time() const { return m_time; } 

    /// Information about the configuration keys associated with this event
    inline const lsfData::Configuration* configuration() const { return m_config; }

    inline const enums::Lsf::RunType runType() const { return m_type; }

    inline const lsfData::LsfKeys* keys() const { return m_keys; }
    inline const enums::Lsf::KeysType keyType() const { return m_ktype; }

    /// set everything at once
    inline void set(const lsfData::RunInfo& run, 
                    const lsfData::DatagramInfo& datagram, 
		    const lsfData::GemScalers& scalers,
		    const lsfData::Time& time,
		    const lsfData::Configuration& configuration,
                    const lsfData::LsfKeys& keys) {
      m_run = run;
      m_datagram = datagram;
      m_scalers = scalers;
      m_time = time;
      if (m_config) delete m_config;
      m_type = enums::Lsf::NoRunType;
      m_config = configuration.clone();
      m_type = configuration.type();
      if (m_keys) delete m_keys;
      m_keys = keys.clone();
      m_ktype = keys.type();
    }

    /// set everything except configuration
    inline void set(const lsfData::RunInfo& run, 
                    const lsfData::DatagramInfo& datagram, 
		    const lsfData::GemScalers& scalers,
		    const lsfData::Time& time) {
      m_run = run;
      m_datagram = datagram;
      m_scalers = scalers;
      m_time = time;
    }

    // set the individual data members
    inline void setRun( const lsfData::RunInfo& val) { m_run = val; };
    inline void setDatagram( const lsfData::DatagramInfo& val) { m_datagram = val; };
    inline void setScalers( const lsfData::GemScalers& val) { m_scalers = val; };
    inline void setTime( const lsfData::Time& val) { m_time = val; }; 
    inline void setConfiguration( const lsfData::Configuration& configuration )
    {
      if (m_config) delete m_config;
      m_type = enums::Lsf::NoRunType;
      m_config = configuration.clone();
      m_type = configuration.type();
    }

    inline void setKeys( const lsfData::LsfKeys& keys) {
        if (m_keys) delete m_keys;
        m_keys = keys.clone();
        m_ktype = keys.type();
    }

    /// Output operator (ASCII)
    friend std::ostream& operator<< ( std::ostream& s, const MetaEvent& obj )    {
      return obj.fillStream(s);
    }
    /// Fill the output stream (ASCII)
    std::ostream& fillStream( std::ostream& s ) const {
      s << "class MetaEvent : \n"
	<< EventField( EventFormat::field12 )
	<< m_run << "\n"
	<< m_datagram << "\n"
	<< m_scalers << "\n"
	<< m_time << "\n"
	<< m_type << "\n";
      if ( m_config != 0 ) {
          if (m_type == enums::Lsf::LPA)
              s << *(m_config->castToLpaConfig());
          else if (m_type == enums::Lsf::AcdLCI)
              s << *(m_config->castToLciAcdConfig());
          else if (m_type == enums::Lsf::CalLCI)
              s << *(m_config->castToLciCalConfig());
          else if (m_type == enums::Lsf::TkrLCI)
              s << *(m_config->castToLciTkrConfig());
      }
/*
      if (m_keys != 0) {
          if (m_ktype == enums::Lsf::LpaKeys)
              s << *(m_keys->castToLpaKeys());
          else if (m_ktype == enums::Lsf::LciKeys)
              s << *(m_keys->castToLciKeys());
      }
*/
      return s;
    }
    
  private:
    
    /// Information about the run this event is from
    lsfData::RunInfo m_run;
    
    /// Information about the datagram this event came in
    lsfData::DatagramInfo m_datagram;
    
    /// The extended context records
    lsfData::GemScalers m_scalers;

    /// Information about the time markers associated with this event  
    lsfData::Time m_time;
    
    /// Information about the configuration keys associated with this event
    lsfData::Configuration* m_config;    //-> 
    
    /// Which type of run was this, particle data or charge injection 
    enums::Lsf::RunType m_type;

    lsfData::LsfKeys* m_keys;
    enums::Lsf::KeysType m_ktype;

  };

}


#endif    // LSF_METAEVENT

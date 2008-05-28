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
* $Header: /nfs/slac/g/glast/ground/cvs/LdfEvent/LdfEvent/LsfMetaEvent.h,v 1.9 2008/05/23 01:54:32 heather Exp $
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
       m_ktype(enums::Lsf::NoKeysType),
       m_gamma(0), m_pass(0), m_mip(0), m_hip(0), m_dgn(0), m_lpaHandler(0) {

       //m_lpaHandlerCol.clear();
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
       m_ktype(keys.type()),
       m_gamma(0), m_pass(0), m_mip(0), m_hip(0), m_dgn(0), m_lpaHandler(0) {

       //m_lpaHandlerCol.clear();
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
       m_ktype(enums::Lsf::NoKeysType), 
       m_gamma(0), m_pass(0), m_mip(0), m_hip(0), m_dgn(0), m_lpaHandler(0) {

       //m_lpaHandlerCol(other.m_lpaHandlerCol) {
      if ( other.configuration() != 0 ) {
	m_config = other.configuration()->clone();
	m_type = other.configuration()->type();
      }
      if ( other.keys() != 0) {
          m_keys = other.keys()->clone();
          m_ktype = other.keys()->type();
      }
      /*std::map<enums::Lsf::HandlerId, lsfData::ILpaHandler*>::const_iterator it;
      for (it = other.m_lpaHandlerCol.begin(); it != other.m_lpaHandlerCol.end(); it++) {
          m_lpaHandlerCol[it->first] = it->second->clone();
      }*/

      if (other.gammaFilter()) m_gamma = new lsfData::GammaHandlerRsdV0(*(other.gammaFilter()));
      if (other.mipFilter()) m_mip = new lsfData::MipHandlerRsdV0(*(other.mipFilter()));
      if (other.hipFilter()) m_hip = new lsfData::HipHandlerRsdV0(*(other.hipFilter()));
      if (other.dgnFilter()) m_dgn = new lsfData::DgnHandlerRsdV0(*(other.dgnFilter()));
      if (other.passthruFilter()) m_pass = new lsfData::PassthruHandlerRsdV0(*(other.passthruFilter()));
      if (other.lpaHandler()) m_lpaHandler = new lsfData::LpaHandler(*(other.lpaHandler()));

      
    }
    
    MetaEvent( const lsfData::MetaEvent& other )
       :m_run(other.run()),
       m_datagram(other.datagram()),
       m_scalers(other.scalers()),
       m_time(other.time()),
       m_config(0),
       m_type(enums::Lsf::NoRunType),
       m_keys(0),
       m_ktype(enums::Lsf::NoKeysType), 
       m_gamma(0), m_pass(0), m_mip(0), m_hip(0), m_dgn(0), m_lpaHandler(0) {

       if ( other.configuration() != 0 ) {
	m_config = other.configuration()->clone();
	m_type = other.configuration()->type();
       }
       if (other.keys() != 0) {
            m_keys = other.keys()->clone();
            m_ktype = other.keys()->type();
       }
       //m_lpaHandlerCol = other.lpaHandlerCol();
//       std::map<enums::Lsf::HandlerId, lsfData::ILpaHandler*>::const_iterator it;
//       for (it = other.lpaHandlerCol().begin(); it != other.lpaHandlerCol().end(); it++) {
//                m_lpaHandlerCol[it->first] = it->second->clone();
//         }
/*
        if (other.gammaFilter()) 
            m_lpaHandlerCol[enums::Lsf::GAMMA] = other.gammaFilter()->clone();
        if (other.passthruFilter())
            m_lpaHandlerCol[enums::Lsf::PASS_THRU] = other.passthruFilter()->clone();
        if (other.mipFilter()) 
            m_lpaHandlerCol[enums::Lsf::MIP] = other.mipFilter()->clone();
        if (other.hipFilter()) 
            m_lpaHandlerCol[enums::Lsf::HIP] = other.hipFilter()->clone();
        if (other.dgnFilter()) 
            m_lpaHandlerCol[enums::Lsf::DGN] = other.dgnFilter()->clone();
        if (other.lpaHandler()) 
            m_lpaHandlerCol[other.lpaHandler()->id()] = other.lpaHandler()->clone();*/
      if (other.gammaFilter()) m_gamma = new lsfData::GammaHandlerRsdV0(*(other.gammaFilter()));
      if (other.mipFilter()) m_mip = new lsfData::MipHandlerRsdV0(*(other.mipFilter()));
      if (other.hipFilter()) m_hip = new lsfData::HipHandlerRsdV0(*(other.hipFilter()));
      if (other.dgnFilter()) m_dgn = new lsfData::DgnHandlerRsdV0(*(other.dgnFilter()));
      if (other.passthruFilter()) m_pass = new lsfData::PassthruHandlerRsdV0(*(other.passthruFilter()));
      if (other.lpaHandler()) m_lpaHandler = new lsfData::LpaHandler(*(other.lpaHandler()));

        
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

      //std::map<enums::Lsf::HandlerId, lsfData::LpaHandler*>::iterator it;
      //for (it = m_lpaHandlerCol.begin(); it != m_lpaHandlerCol.end(); it++) {
      //    delete it->second;
     // }
//      m_lpaHandlerCol.clear();
      if (m_gamma) {
          delete m_gamma;
          m_gamma = 0;
      }
      if (m_mip) {
          delete m_mip;
          m_mip = 0;
      }
      if (m_hip) {
          delete m_hip;
          m_hip = 0;
      }
      if (m_dgn) {
          delete m_dgn;
          m_dgn = 0;
      }
      if (m_pass) {
          delete m_pass;
          m_pass = 0;
      }
      if (m_lpaHandler) {
          delete m_lpaHandler;
          m_lpaHandler = 0;
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

    inline const lsfData::MipHandlerRsdV0* mipFilter() const {
        return m_mip; }
    inline const lsfData::HipHandlerRsdV0* hipFilter() const {
        return m_hip; }
    inline const lsfData::DgnHandlerRsdV0* dgnFilter() const {
        return m_dgn;  }
    inline const lsfData::PassthruHandlerRsdV0* passthruFilter() const {
        return m_pass;  }
    inline const lsfData::GammaHandlerRsdV0* gammaFilter() const {
        return m_gamma;  }
    inline const lsfData::LpaHandler* lpaHandler() const {
        return m_lpaHandler;  }


    /*inline const std::map<enums::Lsf::HandlerId,lsfData::ILpaHandler*>& lpaHandlerCol() const 
    { return m_lpaHandlerCol; }

    inline const lsfData::ILpaHandler* getLpaHandler(const enums::Lsf::HandlerId& id) {
        std::map<enums::Lsf::HandlerId, lsfData::ILpaHandler*>::iterator iter = m_lpaHandlerCol.find(id);
        if (iter != m_lpaHandlerCol.end()) return (m_lpaHandlerCol[id]);
        else return 0;
    } */

/*inline const lsfData::LpaHandler* getLpaHandler(const enums::Lsf::HandlerId &id) {
    if (id == enums::Lsf::GAMMA) return gammaFilter();
    else if (id == enums::Lsf::PASS_THRU) return passthruFilter();
    else if (id == enums::Lsf::HIP) return hipFilter();
    else if (id == enums::Lsf::MIP) return mipFilter();
    else if (id == enums::Lsf::DGN) return dgnFilter();
    else  return lpaHandler();
}*/


/*
    inline void addLpaHandler(const enums::Lsf::HandlerId &id, const lsfData::ILpaHandler &handler) {
        lsfData::ILpaHandler* newHandler;
        if (id == enums::Lsf::GAMMA)
            newHandler = handler.castToGammaRsdV0()->clone();
        else if (id == enums::Lsf::PASS_THRU)
            newHandler = handler.castToPassthruRsdV0()->clone();
        else if (id == enums::Lsf::MIP)
            newHandler = handler.castToMipRsdV0()->clone();
        else if (id == enums::Lsf::HIP)
             newHandler = handler.castToHipRsdV0()->clone();
        else if (id == enums::Lsf::DGN)
             newHandler = handler.castToHipRsdV0()->clone();
        else
             newHandler = handler.castToLpaHandler()->clone();
        m_lpaHandlerCol[id] = newHandler;

        //m_lpaHandlerCol[id] = handler.clone();
    }
*/


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

void addGammaHandler(const lsfData::GammaHandlerRsdV0& gamma) {
    m_gamma = new lsfData::GammaHandlerRsdV0(gamma);
}
void addDgnHandler(const lsfData::DgnHandlerRsdV0& dgn) {
    m_dgn = new lsfData::DgnHandlerRsdV0(dgn);
}
void addPassthruHandler(const lsfData::PassthruHandlerRsdV0& pass) {
    m_pass = new lsfData::PassthruHandlerRsdV0(pass);
}
void addMipHandler(const lsfData::MipHandlerRsdV0& mip) {
    m_mip = new lsfData::MipHandlerRsdV0(mip);
}
void addHipHandler(const lsfData::HipHandlerRsdV0& hip) {
    m_hip = new lsfData::HipHandlerRsdV0(hip);
}
void addLpaHandler(const lsfData::LpaHandler& lpa) {
    m_lpaHandler = new lsfData::LpaHandler(lpa);
}

   /*inline void setLpaHandlerCol ( const std::map<enums::Lsf::HandlerId, lsfData::ILpaHandler*>& vec) {
        std::map<enums::Lsf::HandlerId, lsfData::ILpaHandler*>::const_iterator it;
        for (it = vec.begin(); it != vec.end(); it++) {
            lsfData::ILpaHandler* newHandler;
            if (it->first == enums::Lsf::GAMMA)
               newHandler = it->second->castToGammaRsdV0()->clone();
            else if (it->first == enums::Lsf::PASS_THRU)
               newHandler = it->second->castToPassthruRsdV0()->clone();
            else if (it->first == enums::Lsf::MIP)
               newHandler = it->second->castToMipRsdV0()->clone();
            else if (it->first == enums::Lsf::HIP)
               newHandler = it->second->castToHipRsdV0()->clone();
            else if (it->first == enums::Lsf::DGN)
               newHandler = it->second->castToHipRsdV0()->clone();
            else
               newHandler = it->second->castToLpaHandler()->clone();
            m_lpaHandlerCol[it->first] = newHandler;

          //m_lpaHandlerCol[it->first] = it->second->clone();

        }
    } 
*/
    

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

  //  std::map<enums::Lsf::HandlerId, lsfData::ILpaHandler*> m_lpaHandlerCol;
    lsfData::GammaHandlerRsdV0 *m_gamma;
    lsfData::PassthruHandlerRsdV0 *m_pass;
    lsfData::MipHandlerRsdV0 *m_mip;
    lsfData::HipHandlerRsdV0 *m_hip;
    lsfData::DgnHandlerRsdV0 *m_dgn;
    lsfData::LpaHandler *m_lpaHandler;



  };

}


#endif    // LSF_METAEVENT

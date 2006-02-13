#ifndef LSF_TIME_H
#define LSF_TIME_H 1

#include <iostream>
#include "GaudiKernel/StreamBuffer.h"
#include "Event/TopLevel/Definitions.h"

#include "LdfEvent/LsfTimeTone.h"
#include "LdfEvent/LsfGemTime.h"

/** @class Time
*
* $Header: /nfs/slac/g/glast/ground/cvs/LdfEvent/LdfEvent/LsfTime.h,v 1.2 2006/02/02 22:26:24 echarles Exp $
*/

namespace LsfEvent {

  class Time {
    
  public:

    /// Default c'tor.  Assigns sentinel values to all fields
    Time()
      :m_current(),m_previous(),
       m_timeHack(),m_timeTicks(LSF_INVALID_UINT){
    }
    
    /// Standard c'tor.  Takes input values for all fields
    Time( const TimeTone& current, const TimeTone& previous,
	  const GemTime& timeHack, unsigned int timeTicks)
      :m_current(current),m_previous(previous),
       m_timeHack(timeHack),m_timeTicks(timeTicks){
    }
    
    /// Copy c'tor.  Nothing fancy, just copy all values.
    Time( const Time& other )
      :m_current(other.current()),m_previous(other.previous()),
       m_timeHack(other.timeHack()),m_timeTicks(other.timeTicks()){
    }
    
    /// D'tor.  Nothing special.
    virtual ~Time(){
    }
    
    /// Assignement operator.  Nothing fancy, just copy all values.
    inline Time& operator=( const Time& other ) {
      set(other.current(),other.previous(),
	  other.timeHack(),other.timeTicks());
      return *this;
    }
    
    /// The TimeTone right before the "active" one at event capture time
    inline const TimeTone& current() const { return m_current; } 
    
    /// The TimeTone that was "active" at event capture time
    inline const TimeTone& previous() const { return m_previous; }
    
    /// The value of the GemTime registers at event capture time
    inline const GemTime& timeHack() const { return m_timeHack; } 
    
    /// The number of 50ns ticks since last the last time hack
    inline unsigned int timeTicks() const { return m_timeTicks; }
    
    /// set everything at once
    inline void set(const TimeTone& current, const TimeTone& previous,
		    const GemTime& timeHack, unsigned int timeTicks) {
      m_current = current;
      m_previous = previous;      
      m_timeHack = timeHack; 
      m_timeTicks = timeTicks;
    }
    
    // set the individual data members
    inline void setCurrent( const TimeTone& val) { m_current = val; }; 
    inline void setPrevious( const TimeTone& val) { m_previous = val; };
    inline void setGemTime( const GemTime& val) { m_timeHack = val; }; 
    inline void setTimeTicks( unsigned int val) { m_timeTicks = val; };

    /// Serialize the object for writing
    friend StreamBuffer& operator<< ( StreamBuffer& s, const Time& obj )    {
      s << obj.m_current; 
      s << obj.m_previous;
      s << obj.m_timeHack;
      s << obj.m_timeTicks;
      return s;
    }
    /// Serialize the object for reading
    friend StreamBuffer& operator>> ( StreamBuffer& s, Time& obj )          {
      s >> obj.m_current;
      s >> obj.m_previous;
      s >> obj.m_timeHack;
      s >> obj.m_timeTicks;
      return s;
    }
    
    /// Output operator (ASCII)
    friend std::ostream& operator<< ( std::ostream& s, const Time& obj )    {
      return obj.fillStream(s);
    }
    /// Fill the output stream (ASCII)
    std::ostream& fillStream( std::ostream& s ) const                            {
      return s << "class Time : " << std::endl
	       << EventField( EventFormat::field12 )
	       << m_current << std::endl
	       << m_previous << std::endl
	       << m_timeHack << std::endl
	       << m_timeTicks;
    }
      
    
  private:
    
    /// 
    TimeTone m_current;
    TimeTone m_previous;
    GemTime m_timeHack;
    unsigned int m_timeTicks;
     
  };

}


#endif    // EVENT_TIMETONE_H

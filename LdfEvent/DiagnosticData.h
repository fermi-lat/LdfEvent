#ifndef LDFCONVERTER_DIAGNOSTICDATA_H
#define LDFCONVERTER_DIAGNOSTICDATA_H

#include <iostream>
#include <vector>

#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/StreamBuffer.h"
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/IInterface.h"

#include "Event/TopLevel/Definitions.h"
#include "Event/TopLevel/EventModel.h"

// From EBF Online library
#include "CALdiagnostic.h"
#include "TKRdiagnostic.h"

/**
* @class DiagnosticData
* @brief TDS for storing the diagnostic (trigger primitives)

* Constains 2 local classes for CAL and TKR trigger primitives
*/

static const CLID& CLID_LdfDiagnosticData = InterfaceID("LdfDiagnosticData", 1, 0);

namespace LdfEvent {
    class CalDiagnosticData {
    public:
        CalDiagnosticData(unsigned datum, unsigned tower, unsigned layer) 
            : m_datum(datum), m_tower(tower), m_layer(layer)
        {
        }

        CalDiagnosticData()  {}
        ~CalDiagnosticData() {}

        unsigned dataWord() const { return m_datum; };
        unsigned tower() const { return m_tower; };
        unsigned layer() const { return m_layer; };
        // for overlays
        void setDataWord( unsigned int datum) { m_datum = datum; };

    private:
        unsigned m_datum;
        unsigned m_tower;
        unsigned m_layer;
    };

    class TkrDiagnosticData {
    public:

        TkrDiagnosticData(unsigned datum, unsigned tower, unsigned gtcc) 
            : m_datum(datum), m_tower(tower), m_gtcc(gtcc) {}
            TkrDiagnosticData()  {}
            ~TkrDiagnosticData() {}

            unsigned dataWord() const { return m_datum; };
            unsigned tower() const { return m_tower; }; 
            unsigned gtcc() const { return m_gtcc; };
            // add this access method to make it easier to simulate diagnostic info
            void setDataWord( unsigned int datum) { m_datum = datum; };

    private:
        unsigned m_datum;
        unsigned m_tower;  
        unsigned m_gtcc;
    };

    class DiagnosticData : public DataObject{
    public:
        virtual ~DiagnosticData();
        virtual std::ostream& fillStream(std::ostream &s) const;
        friend std::ostream& operator << (std::ostream &s, const DiagnosticData &obj);

        DiagnosticData();

        /// Retrieve reference to class definition structure
        virtual const CLID& clID() const   { return DiagnosticData::classID(); }
        static const CLID& classID()       { return CLID_LdfDiagnosticData; };

        inline void addCalDiagnostic(const CalDiagnosticData& cal) { m_cal.push_back(cal); };
        inline int getNumCalDiagnostic() const { return m_cal.size(); };
        const CalDiagnosticData& getCalDiagnosticByIndex(unsigned int ind)const { return m_cal[ind]; };
        inline void addTkrDiagnostic(const TkrDiagnosticData& tkr) { m_tkr.push_back(tkr); };
        inline int getNumTkrDiagnostic() const { return m_tkr.size(); };
        const TkrDiagnosticData& getTkrDiagnosticByIndex(unsigned int ind)const { return m_tkr[ind]; };

        // needed for simulating diagnostic data
        void setTkrDataWordByIndex( unsigned int ind, unsigned int datum) {
            m_tkr[ind].setDataWord( datum );
        }
        void setCalDataWordByIndex( unsigned int ind, unsigned int datum) {
            m_cal[ind].setDataWord( datum );
        }

    private:
        std::vector<CalDiagnosticData> m_cal;
        std::vector<TkrDiagnosticData> m_tkr;
    };

    // inline the public get methods for clients besides OnboardFilter.

    // the put methods, here for now
    inline DiagnosticData::DiagnosticData(){
        m_cal.clear();
        m_tkr.clear();
    }

    inline DiagnosticData::~DiagnosticData(){
    }


    inline std::ostream& DiagnosticData::fillStream(std::ostream &s) const{
        int i;
        for (i = 0; i < getNumCalDiagnostic(); i++) {
            s<<"Full CAL Data Word # " << i << " " << m_cal[i].dataWord() <<std::endl;
        }
        for (i = 0; i < getNumTkrDiagnostic(); i++) {
            s<<"Full TKR Data Word # " << i << " " <<m_tkr[i].dataWord()<<std::endl;
        }
        return s;
    }


    inline std::ostream& operator<<(std::ostream &s, const DiagnosticData &obj){
        return obj.fillStream(s);
    }

}//namespace LdfEvent 


#endif

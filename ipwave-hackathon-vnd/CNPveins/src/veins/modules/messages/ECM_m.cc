//
// Generated file, do not edit! Created by nedtool 5.4 from veins/modules/messages/ECM.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "ECM_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(EmergentContextMsg)

EmergentContextMsg::EmergentContextMsg(const char *name, short kind) : ::WaveShortMessage(name,kind)
{
    this->accVehSpeed = 0;
    this->accLInd = 0;
    this->sendingTime = 0;
    this->SeqNum = 0;
    this->emergDrivSpeed = 0;
    this->isForwarded = false;
}

EmergentContextMsg::EmergentContextMsg(const EmergentContextMsg& other) : ::WaveShortMessage(other)
{
    copy(other);
}

EmergentContextMsg::~EmergentContextMsg()
{
}

EmergentContextMsg& EmergentContextMsg::operator=(const EmergentContextMsg& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void EmergentContextMsg::copy(const EmergentContextMsg& other)
{
    this->senderPos = other.senderPos;
    this->accVehSpeed = other.accVehSpeed;
    this->accidentLane = other.accidentLane;
    this->accLInd = other.accLInd;
    this->senderid = other.senderid;
    this->sendingTime = other.sendingTime;
    this->SeqNum = other.SeqNum;
    this->emergVID = other.emergVID;
    this->emergManeuvLane = other.emergManeuvLane;
    this->emergDrivSpeed = other.emergDrivSpeed;
    this->emergVehCurPos = other.emergVehCurPos;
    this->emergStartPos = other.emergStartPos;
    this->EmergEndPos = other.EmergEndPos;
    this->isForwarded = other.isForwarded;
}

void EmergentContextMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->accVehSpeed);
    doParsimPacking(b,this->accidentLane);
    doParsimPacking(b,this->accLInd);
    doParsimPacking(b,this->senderid);
    doParsimPacking(b,this->sendingTime);
    doParsimPacking(b,this->SeqNum);
    doParsimPacking(b,this->emergVID);
    doParsimPacking(b,this->emergManeuvLane);
    doParsimPacking(b,this->emergDrivSpeed);
    doParsimPacking(b,this->emergVehCurPos);
    doParsimPacking(b,this->emergStartPos);
    doParsimPacking(b,this->EmergEndPos);
    doParsimPacking(b,this->isForwarded);
}

void EmergentContextMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->senderPos);
    doParsimUnpacking(b,this->accVehSpeed);
    doParsimUnpacking(b,this->accidentLane);
    doParsimUnpacking(b,this->accLInd);
    doParsimUnpacking(b,this->senderid);
    doParsimUnpacking(b,this->sendingTime);
    doParsimUnpacking(b,this->SeqNum);
    doParsimUnpacking(b,this->emergVID);
    doParsimUnpacking(b,this->emergManeuvLane);
    doParsimUnpacking(b,this->emergDrivSpeed);
    doParsimUnpacking(b,this->emergVehCurPos);
    doParsimUnpacking(b,this->emergStartPos);
    doParsimUnpacking(b,this->EmergEndPos);
    doParsimUnpacking(b,this->isForwarded);
}

Coord& EmergentContextMsg::getSenderPos()
{
    return this->senderPos;
}

void EmergentContextMsg::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

double EmergentContextMsg::getAccVehSpeed() const
{
    return this->accVehSpeed;
}

void EmergentContextMsg::setAccVehSpeed(double accVehSpeed)
{
    this->accVehSpeed = accVehSpeed;
}

const char * EmergentContextMsg::getAccidentLane() const
{
    return this->accidentLane.c_str();
}

void EmergentContextMsg::setAccidentLane(const char * accidentLane)
{
    this->accidentLane = accidentLane;
}

int EmergentContextMsg::getAccLInd() const
{
    return this->accLInd;
}

void EmergentContextMsg::setAccLInd(int accLInd)
{
    this->accLInd = accLInd;
}

const char * EmergentContextMsg::getSenderid() const
{
    return this->senderid.c_str();
}

void EmergentContextMsg::setSenderid(const char * senderid)
{
    this->senderid = senderid;
}

::omnetpp::simtime_t EmergentContextMsg::getSendingTime() const
{
    return this->sendingTime;
}

void EmergentContextMsg::setSendingTime(::omnetpp::simtime_t sendingTime)
{
    this->sendingTime = sendingTime;
}

int EmergentContextMsg::getSeqNum() const
{
    return this->SeqNum;
}

void EmergentContextMsg::setSeqNum(int SeqNum)
{
    this->SeqNum = SeqNum;
}

const char * EmergentContextMsg::getEmergVID() const
{
    return this->emergVID.c_str();
}

void EmergentContextMsg::setEmergVID(const char * emergVID)
{
    this->emergVID = emergVID;
}

const char * EmergentContextMsg::getEmergManeuvLane() const
{
    return this->emergManeuvLane.c_str();
}

void EmergentContextMsg::setEmergManeuvLane(const char * emergManeuvLane)
{
    this->emergManeuvLane = emergManeuvLane;
}

double EmergentContextMsg::getEmergDrivSpeed() const
{
    return this->emergDrivSpeed;
}

void EmergentContextMsg::setEmergDrivSpeed(double emergDrivSpeed)
{
    this->emergDrivSpeed = emergDrivSpeed;
}

Coord& EmergentContextMsg::getEmergVehCurPos()
{
    return this->emergVehCurPos;
}

void EmergentContextMsg::setEmergVehCurPos(const Coord& emergVehCurPos)
{
    this->emergVehCurPos = emergVehCurPos;
}

Coord& EmergentContextMsg::getEmergStartPos()
{
    return this->emergStartPos;
}

void EmergentContextMsg::setEmergStartPos(const Coord& emergStartPos)
{
    this->emergStartPos = emergStartPos;
}

Coord& EmergentContextMsg::getEmergEndPos()
{
    return this->EmergEndPos;
}

void EmergentContextMsg::setEmergEndPos(const Coord& EmergEndPos)
{
    this->EmergEndPos = EmergEndPos;
}

bool EmergentContextMsg::getIsForwarded() const
{
    return this->isForwarded;
}

void EmergentContextMsg::setIsForwarded(bool isForwarded)
{
    this->isForwarded = isForwarded;
}

class EmergentContextMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EmergentContextMsgDescriptor();
    virtual ~EmergentContextMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(EmergentContextMsgDescriptor)

EmergentContextMsgDescriptor::EmergentContextMsgDescriptor() : omnetpp::cClassDescriptor("EmergentContextMsg", "WaveShortMessage")
{
    propertynames = nullptr;
}

EmergentContextMsgDescriptor::~EmergentContextMsgDescriptor()
{
    delete[] propertynames;
}

bool EmergentContextMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EmergentContextMsg *>(obj)!=nullptr;
}

const char **EmergentContextMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EmergentContextMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EmergentContextMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount() : 14;
}

unsigned int EmergentContextMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<14) ? fieldTypeFlags[field] : 0;
}

const char *EmergentContextMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderPos",
        "accVehSpeed",
        "accidentLane",
        "accLInd",
        "senderid",
        "sendingTime",
        "SeqNum",
        "emergVID",
        "emergManeuvLane",
        "emergDrivSpeed",
        "emergVehCurPos",
        "emergStartPos",
        "EmergEndPos",
        "isForwarded",
    };
    return (field>=0 && field<14) ? fieldNames[field] : nullptr;
}

int EmergentContextMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPos")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "accVehSpeed")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "accidentLane")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "accLInd")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderid")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendingTime")==0) return base+5;
    if (fieldName[0]=='S' && strcmp(fieldName, "SeqNum")==0) return base+6;
    if (fieldName[0]=='e' && strcmp(fieldName, "emergVID")==0) return base+7;
    if (fieldName[0]=='e' && strcmp(fieldName, "emergManeuvLane")==0) return base+8;
    if (fieldName[0]=='e' && strcmp(fieldName, "emergDrivSpeed")==0) return base+9;
    if (fieldName[0]=='e' && strcmp(fieldName, "emergVehCurPos")==0) return base+10;
    if (fieldName[0]=='e' && strcmp(fieldName, "emergStartPos")==0) return base+11;
    if (fieldName[0]=='E' && strcmp(fieldName, "EmergEndPos")==0) return base+12;
    if (fieldName[0]=='i' && strcmp(fieldName, "isForwarded")==0) return base+13;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EmergentContextMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "Coord",
        "double",
        "string",
        "int",
        "string",
        "simtime_t",
        "int",
        "string",
        "string",
        "double",
        "Coord",
        "Coord",
        "Coord",
        "bool",
    };
    return (field>=0 && field<14) ? fieldTypeStrings[field] : nullptr;
}

const char **EmergentContextMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EmergentContextMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EmergentContextMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EmergentContextMsg *pp = (EmergentContextMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EmergentContextMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EmergentContextMsg *pp = (EmergentContextMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EmergentContextMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EmergentContextMsg *pp = (EmergentContextMsg *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSenderPos(); return out.str();}
        case 1: return double2string(pp->getAccVehSpeed());
        case 2: return oppstring2string(pp->getAccidentLane());
        case 3: return long2string(pp->getAccLInd());
        case 4: return oppstring2string(pp->getSenderid());
        case 5: return simtime2string(pp->getSendingTime());
        case 6: return long2string(pp->getSeqNum());
        case 7: return oppstring2string(pp->getEmergVID());
        case 8: return oppstring2string(pp->getEmergManeuvLane());
        case 9: return double2string(pp->getEmergDrivSpeed());
        case 10: {std::stringstream out; out << pp->getEmergVehCurPos(); return out.str();}
        case 11: {std::stringstream out; out << pp->getEmergStartPos(); return out.str();}
        case 12: {std::stringstream out; out << pp->getEmergEndPos(); return out.str();}
        case 13: return bool2string(pp->getIsForwarded());
        default: return "";
    }
}

bool EmergentContextMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EmergentContextMsg *pp = (EmergentContextMsg *)object; (void)pp;
    switch (field) {
        case 1: pp->setAccVehSpeed(string2double(value)); return true;
        case 2: pp->setAccidentLane((value)); return true;
        case 3: pp->setAccLInd(string2long(value)); return true;
        case 4: pp->setSenderid((value)); return true;
        case 5: pp->setSendingTime(string2simtime(value)); return true;
        case 6: pp->setSeqNum(string2long(value)); return true;
        case 7: pp->setEmergVID((value)); return true;
        case 8: pp->setEmergManeuvLane((value)); return true;
        case 9: pp->setEmergDrivSpeed(string2double(value)); return true;
        case 13: pp->setIsForwarded(string2bool(value)); return true;
        default: return false;
    }
}

const char *EmergentContextMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(Coord));
        case 10: return omnetpp::opp_typename(typeid(Coord));
        case 11: return omnetpp::opp_typename(typeid(Coord));
        case 12: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *EmergentContextMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EmergentContextMsg *pp = (EmergentContextMsg *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSenderPos()); break;
        case 10: return (void *)(&pp->getEmergVehCurPos()); break;
        case 11: return (void *)(&pp->getEmergStartPos()); break;
        case 12: return (void *)(&pp->getEmergEndPos()); break;
        default: return nullptr;
    }
}



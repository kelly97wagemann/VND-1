//
// Generated file, do not edit! Created by nedtool 5.4 from veins/modules/messages/CCM.msg.
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
#include "CCM_m.h"

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

Register_Class(CooperativeContMsg)

CooperativeContMsg::CooperativeContMsg(const char *name, short kind) : ::WaveShortMessage(name,kind)
{
    this->sendingSpeed = 0;
    this->theta = 0;
    this->isrsu = false;
}

CooperativeContMsg::CooperativeContMsg(const CooperativeContMsg& other) : ::WaveShortMessage(other)
{
    copy(other);
}

CooperativeContMsg::~CooperativeContMsg()
{
}

CooperativeContMsg& CooperativeContMsg::operator=(const CooperativeContMsg& other)
{
    if (this==&other) return *this;
    ::WaveShortMessage::operator=(other);
    copy(other);
    return *this;
}

void CooperativeContMsg::copy(const CooperativeContMsg& other)
{
    this->senderPos = other.senderPos;
    this->senderSpeed = other.senderSpeed;
    this->senderID = other.senderID;
    this->sendingSpeed = other.sendingSpeed;
    this->CurrentLane = other.CurrentLane;
    this->headingLane = other.headingLane;
    this->theta = other.theta;
    this->isrsu = other.isrsu;
}

void CooperativeContMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WaveShortMessage::parsimPack(b);
    doParsimPacking(b,this->senderPos);
    doParsimPacking(b,this->senderSpeed);
    doParsimPacking(b,this->senderID);
    doParsimPacking(b,this->sendingSpeed);
    doParsimPacking(b,this->CurrentLane);
    doParsimPacking(b,this->headingLane);
    doParsimPacking(b,this->theta);
    doParsimPacking(b,this->isrsu);
}

void CooperativeContMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WaveShortMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->senderPos);
    doParsimUnpacking(b,this->senderSpeed);
    doParsimUnpacking(b,this->senderID);
    doParsimUnpacking(b,this->sendingSpeed);
    doParsimUnpacking(b,this->CurrentLane);
    doParsimUnpacking(b,this->headingLane);
    doParsimUnpacking(b,this->theta);
    doParsimUnpacking(b,this->isrsu);
}

Coord& CooperativeContMsg::getSenderPos()
{
    return this->senderPos;
}

void CooperativeContMsg::setSenderPos(const Coord& senderPos)
{
    this->senderPos = senderPos;
}

Coord& CooperativeContMsg::getSenderSpeed()
{
    return this->senderSpeed;
}

void CooperativeContMsg::setSenderSpeed(const Coord& senderSpeed)
{
    this->senderSpeed = senderSpeed;
}

const char * CooperativeContMsg::getSenderID() const
{
    return this->senderID.c_str();
}

void CooperativeContMsg::setSenderID(const char * senderID)
{
    this->senderID = senderID;
}

double CooperativeContMsg::getSendingSpeed() const
{
    return this->sendingSpeed;
}

void CooperativeContMsg::setSendingSpeed(double sendingSpeed)
{
    this->sendingSpeed = sendingSpeed;
}

const char * CooperativeContMsg::getCurrentLane() const
{
    return this->CurrentLane.c_str();
}

void CooperativeContMsg::setCurrentLane(const char * CurrentLane)
{
    this->CurrentLane = CurrentLane;
}

const char * CooperativeContMsg::getHeadingLane() const
{
    return this->headingLane.c_str();
}

void CooperativeContMsg::setHeadingLane(const char * headingLane)
{
    this->headingLane = headingLane;
}

double CooperativeContMsg::getTheta() const
{
    return this->theta;
}

void CooperativeContMsg::setTheta(double theta)
{
    this->theta = theta;
}

bool CooperativeContMsg::getIsrsu() const
{
    return this->isrsu;
}

void CooperativeContMsg::setIsrsu(bool isrsu)
{
    this->isrsu = isrsu;
}

class CooperativeContMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CooperativeContMsgDescriptor();
    virtual ~CooperativeContMsgDescriptor();

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

Register_ClassDescriptor(CooperativeContMsgDescriptor)

CooperativeContMsgDescriptor::CooperativeContMsgDescriptor() : omnetpp::cClassDescriptor("CooperativeContMsg", "WaveShortMessage")
{
    propertynames = nullptr;
}

CooperativeContMsgDescriptor::~CooperativeContMsgDescriptor()
{
    delete[] propertynames;
}

bool CooperativeContMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CooperativeContMsg *>(obj)!=nullptr;
}

const char **CooperativeContMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CooperativeContMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CooperativeContMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int CooperativeContMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *CooperativeContMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderPos",
        "senderSpeed",
        "senderID",
        "sendingSpeed",
        "CurrentLane",
        "headingLane",
        "theta",
        "isrsu",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int CooperativeContMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPos")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderSpeed")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderID")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendingSpeed")==0) return base+3;
    if (fieldName[0]=='C' && strcmp(fieldName, "CurrentLane")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "headingLane")==0) return base+5;
    if (fieldName[0]=='t' && strcmp(fieldName, "theta")==0) return base+6;
    if (fieldName[0]=='i' && strcmp(fieldName, "isrsu")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CooperativeContMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "Coord",
        "Coord",
        "string",
        "double",
        "string",
        "string",
        "double",
        "bool",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **CooperativeContMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *CooperativeContMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CooperativeContMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CooperativeContMsg *pp = (CooperativeContMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *CooperativeContMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CooperativeContMsg *pp = (CooperativeContMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CooperativeContMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CooperativeContMsg *pp = (CooperativeContMsg *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSenderPos(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSenderSpeed(); return out.str();}
        case 2: return oppstring2string(pp->getSenderID());
        case 3: return double2string(pp->getSendingSpeed());
        case 4: return oppstring2string(pp->getCurrentLane());
        case 5: return oppstring2string(pp->getHeadingLane());
        case 6: return double2string(pp->getTheta());
        case 7: return bool2string(pp->getIsrsu());
        default: return "";
    }
}

bool CooperativeContMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CooperativeContMsg *pp = (CooperativeContMsg *)object; (void)pp;
    switch (field) {
        case 2: pp->setSenderID((value)); return true;
        case 3: pp->setSendingSpeed(string2double(value)); return true;
        case 4: pp->setCurrentLane((value)); return true;
        case 5: pp->setHeadingLane((value)); return true;
        case 6: pp->setTheta(string2double(value)); return true;
        case 7: pp->setIsrsu(string2bool(value)); return true;
        default: return false;
    }
}

const char *CooperativeContMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(Coord));
        case 1: return omnetpp::opp_typename(typeid(Coord));
        default: return nullptr;
    };
}

void *CooperativeContMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CooperativeContMsg *pp = (CooperativeContMsg *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSenderPos()); break;
        case 1: return (void *)(&pp->getSenderSpeed()); break;
        default: return nullptr;
    }
}



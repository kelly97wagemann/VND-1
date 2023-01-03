//
// Generated file, do not edit! Created by nedtool 5.4 from veins/modules/messages/WSM_ipwave.msg.
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
#include "WSM_ipwave_m.h"

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

Register_Class(WSM_ipwave)

WSM_ipwave::WSM_ipwave(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->wsmVersion = 0;
    this->securityType = 0;
    this->channelNumber = 0;
    this->dataRate = 1;
    this->userPriority = 7;
    this->psid = 0;
    this->psc = "Service with some Data";
    this->wsmLength = 0;
    this->wsmData = "Some Data";
    this->senderAddress = MacAddress::UNSPECIFIED_ADDRESS;
    this->recipientAddress = MacAddress::UNSPECIFIED_ADDRESS;
    this->serial = 0;
    this->timestamp = 0;
}

WSM_ipwave::WSM_ipwave(const WSM_ipwave& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WSM_ipwave::~WSM_ipwave()
{
}

WSM_ipwave& WSM_ipwave::operator=(const WSM_ipwave& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WSM_ipwave::copy(const WSM_ipwave& other)
{
    this->wsmVersion = other.wsmVersion;
    this->securityType = other.securityType;
    this->channelNumber = other.channelNumber;
    this->dataRate = other.dataRate;
    this->userPriority = other.userPriority;
    this->psid = other.psid;
    this->psc = other.psc;
    this->wsmLength = other.wsmLength;
    this->wsmData = other.wsmData;
    this->senderAddress = other.senderAddress;
    this->recipientAddress = other.recipientAddress;
    this->serial = other.serial;
    this->timestamp = other.timestamp;
}

void WSM_ipwave::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->wsmVersion);
    doParsimPacking(b,this->securityType);
    doParsimPacking(b,this->channelNumber);
    doParsimPacking(b,this->dataRate);
    doParsimPacking(b,this->userPriority);
    doParsimPacking(b,this->psid);
    doParsimPacking(b,this->psc);
    doParsimPacking(b,this->wsmLength);
    doParsimPacking(b,this->wsmData);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->recipientAddress);
    doParsimPacking(b,this->serial);
    doParsimPacking(b,this->timestamp);
}

void WSM_ipwave::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->wsmVersion);
    doParsimUnpacking(b,this->securityType);
    doParsimUnpacking(b,this->channelNumber);
    doParsimUnpacking(b,this->dataRate);
    doParsimUnpacking(b,this->userPriority);
    doParsimUnpacking(b,this->psid);
    doParsimUnpacking(b,this->psc);
    doParsimUnpacking(b,this->wsmLength);
    doParsimUnpacking(b,this->wsmData);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->recipientAddress);
    doParsimUnpacking(b,this->serial);
    doParsimUnpacking(b,this->timestamp);
}

int WSM_ipwave::getWsmVersion() const
{
    return this->wsmVersion;
}

void WSM_ipwave::setWsmVersion(int wsmVersion)
{
    this->wsmVersion = wsmVersion;
}

int WSM_ipwave::getSecurityType() const
{
    return this->securityType;
}

void WSM_ipwave::setSecurityType(int securityType)
{
    this->securityType = securityType;
}

int WSM_ipwave::getChannelNumber() const
{
    return this->channelNumber;
}

void WSM_ipwave::setChannelNumber(int channelNumber)
{
    this->channelNumber = channelNumber;
}

int WSM_ipwave::getDataRate() const
{
    return this->dataRate;
}

void WSM_ipwave::setDataRate(int dataRate)
{
    this->dataRate = dataRate;
}

int WSM_ipwave::getUserPriority() const
{
    return this->userPriority;
}

void WSM_ipwave::setUserPriority(int userPriority)
{
    this->userPriority = userPriority;
}

int WSM_ipwave::getPsid() const
{
    return this->psid;
}

void WSM_ipwave::setPsid(int psid)
{
    this->psid = psid;
}

const char * WSM_ipwave::getPsc() const
{
    return this->psc.c_str();
}

void WSM_ipwave::setPsc(const char * psc)
{
    this->psc = psc;
}

int WSM_ipwave::getWsmLength() const
{
    return this->wsmLength;
}

void WSM_ipwave::setWsmLength(int wsmLength)
{
    this->wsmLength = wsmLength;
}

const char * WSM_ipwave::getWsmData() const
{
    return this->wsmData.c_str();
}

void WSM_ipwave::setWsmData(const char * wsmData)
{
    this->wsmData = wsmData;
}

MacAddress& WSM_ipwave::getSenderAddress()
{
    return this->senderAddress;
}

void WSM_ipwave::setSenderAddress(const MacAddress& senderAddress)
{
    this->senderAddress = senderAddress;
}

MacAddress& WSM_ipwave::getRecipientAddress()
{
    return this->recipientAddress;
}

void WSM_ipwave::setRecipientAddress(const MacAddress& recipientAddress)
{
    this->recipientAddress = recipientAddress;
}

int WSM_ipwave::getSerial() const
{
    return this->serial;
}

void WSM_ipwave::setSerial(int serial)
{
    this->serial = serial;
}

::omnetpp::simtime_t WSM_ipwave::getTimestamp() const
{
    return this->timestamp;
}

void WSM_ipwave::setTimestamp(::omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

class WSM_ipwaveDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WSM_ipwaveDescriptor();
    virtual ~WSM_ipwaveDescriptor();

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

Register_ClassDescriptor(WSM_ipwaveDescriptor)

WSM_ipwaveDescriptor::WSM_ipwaveDescriptor() : omnetpp::cClassDescriptor("WSM_ipwave", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WSM_ipwaveDescriptor::~WSM_ipwaveDescriptor()
{
    delete[] propertynames;
}

bool WSM_ipwaveDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WSM_ipwave *>(obj)!=nullptr;
}

const char **WSM_ipwaveDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WSM_ipwaveDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WSM_ipwaveDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount() : 13;
}

unsigned int WSM_ipwaveDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *WSM_ipwaveDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "wsmVersion",
        "securityType",
        "channelNumber",
        "dataRate",
        "userPriority",
        "psid",
        "psc",
        "wsmLength",
        "wsmData",
        "senderAddress",
        "recipientAddress",
        "serial",
        "timestamp",
    };
    return (field>=0 && field<13) ? fieldNames[field] : nullptr;
}

int WSM_ipwaveDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmVersion")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "securityType")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelNumber")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataRate")==0) return base+3;
    if (fieldName[0]=='u' && strcmp(fieldName, "userPriority")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "psid")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "psc")==0) return base+6;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmLength")==0) return base+7;
    if (fieldName[0]=='w' && strcmp(fieldName, "wsmData")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+9;
    if (fieldName[0]=='r' && strcmp(fieldName, "recipientAddress")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "serial")==0) return base+11;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+12;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WSM_ipwaveDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "string",
        "int",
        "string",
        "MacAddress",
        "MacAddress",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : nullptr;
}

const char **WSM_ipwaveDescriptor::getFieldPropertyNames(int field) const
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

const char *WSM_ipwaveDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WSM_ipwaveDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WSM_ipwave *pp = (WSM_ipwave *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *WSM_ipwaveDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WSM_ipwave *pp = (WSM_ipwave *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string WSM_ipwaveDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WSM_ipwave *pp = (WSM_ipwave *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getWsmVersion());
        case 1: return long2string(pp->getSecurityType());
        case 2: return long2string(pp->getChannelNumber());
        case 3: return long2string(pp->getDataRate());
        case 4: return long2string(pp->getUserPriority());
        case 5: return long2string(pp->getPsid());
        case 6: return oppstring2string(pp->getPsc());
        case 7: return long2string(pp->getWsmLength());
        case 8: return oppstring2string(pp->getWsmData());
        case 9: {std::stringstream out; out << pp->getSenderAddress(); return out.str();}
        case 10: {std::stringstream out; out << pp->getRecipientAddress(); return out.str();}
        case 11: return long2string(pp->getSerial());
        case 12: return simtime2string(pp->getTimestamp());
        default: return "";
    }
}

bool WSM_ipwaveDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WSM_ipwave *pp = (WSM_ipwave *)object; (void)pp;
    switch (field) {
        case 0: pp->setWsmVersion(string2long(value)); return true;
        case 1: pp->setSecurityType(string2long(value)); return true;
        case 2: pp->setChannelNumber(string2long(value)); return true;
        case 3: pp->setDataRate(string2long(value)); return true;
        case 4: pp->setUserPriority(string2long(value)); return true;
        case 5: pp->setPsid(string2long(value)); return true;
        case 6: pp->setPsc((value)); return true;
        case 7: pp->setWsmLength(string2long(value)); return true;
        case 8: pp->setWsmData((value)); return true;
        case 11: pp->setSerial(string2long(value)); return true;
        case 12: pp->setTimestamp(string2simtime(value)); return true;
        default: return false;
    }
}

const char *WSM_ipwaveDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 9: return omnetpp::opp_typename(typeid(MacAddress));
        case 10: return omnetpp::opp_typename(typeid(MacAddress));
        default: return nullptr;
    };
}

void *WSM_ipwaveDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WSM_ipwave *pp = (WSM_ipwave *)object; (void)pp;
    switch (field) {
        case 9: return (void *)(&pp->getSenderAddress()); break;
        case 10: return (void *)(&pp->getRecipientAddress()); break;
        default: return nullptr;
    }
}



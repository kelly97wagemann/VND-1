//
// Generated file, do not edit! Created by nedtool 5.4 from inet/networklayer/icmpv6/Ipv6NdMessage.msg.
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
#include <memory>
#include "Ipv6NdMessage_m.h"

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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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
    for (int i = 0; i < n; i++) {
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

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

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

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::Ipv6NdOptionTypes");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::Ipv6NdOptionTypes"));
    e->insert(IPv6ND_SOURCE_LINK_LAYER_ADDR_OPTION, "IPv6ND_SOURCE_LINK_LAYER_ADDR_OPTION");
    e->insert(IPv6ND_TARGET_LINK_LAYER_ADDR_OPTION, "IPv6ND_TARGET_LINK_LAYER_ADDR_OPTION");
    e->insert(IPv6ND_ADDRESS_REGISTRATION_OPTION, "IPv6ND_ADDRESS_REGISTRATION_OPTION");
)

Register_Class(Ipv6NdPrefixInformation)

Ipv6NdPrefixInformation::Ipv6NdPrefixInformation() : ::omnetpp::cObject()
{
}

Ipv6NdPrefixInformation::Ipv6NdPrefixInformation(const Ipv6NdPrefixInformation& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdPrefixInformation::~Ipv6NdPrefixInformation()
{
}

Ipv6NdPrefixInformation& Ipv6NdPrefixInformation::operator=(const Ipv6NdPrefixInformation& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdPrefixInformation::copy(const Ipv6NdPrefixInformation& other)
{
    this->prefixLength = other.prefixLength;
    this->onlinkFlag = other.onlinkFlag;
    this->autoAddressConfFlag = other.autoAddressConfFlag;
    this->routerAddressFlag = other.routerAddressFlag;
    this->validLifetime = other.validLifetime;
    this->preferredLifetime = other.preferredLifetime;
    this->prefix = other.prefix;
    this->distance = other.distance;
}

void Ipv6NdPrefixInformation::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->prefixLength);
    doParsimPacking(b,this->onlinkFlag);
    doParsimPacking(b,this->autoAddressConfFlag);
    doParsimPacking(b,this->routerAddressFlag);
    doParsimPacking(b,this->validLifetime);
    doParsimPacking(b,this->preferredLifetime);
    doParsimPacking(b,this->prefix);
    doParsimPacking(b,this->distance);
}

void Ipv6NdPrefixInformation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->prefixLength);
    doParsimUnpacking(b,this->onlinkFlag);
    doParsimUnpacking(b,this->autoAddressConfFlag);
    doParsimUnpacking(b,this->routerAddressFlag);
    doParsimUnpacking(b,this->validLifetime);
    doParsimUnpacking(b,this->preferredLifetime);
    doParsimUnpacking(b,this->prefix);
    doParsimUnpacking(b,this->distance);
}

unsigned short Ipv6NdPrefixInformation::getPrefixLength() const
{
    return this->prefixLength;
}

void Ipv6NdPrefixInformation::setPrefixLength(unsigned short prefixLength)
{
    this->prefixLength = prefixLength;
}

bool Ipv6NdPrefixInformation::getOnlinkFlag() const
{
    return this->onlinkFlag;
}

void Ipv6NdPrefixInformation::setOnlinkFlag(bool onlinkFlag)
{
    this->onlinkFlag = onlinkFlag;
}

bool Ipv6NdPrefixInformation::getAutoAddressConfFlag() const
{
    return this->autoAddressConfFlag;
}

void Ipv6NdPrefixInformation::setAutoAddressConfFlag(bool autoAddressConfFlag)
{
    this->autoAddressConfFlag = autoAddressConfFlag;
}

bool Ipv6NdPrefixInformation::getRouterAddressFlag() const
{
    return this->routerAddressFlag;
}

void Ipv6NdPrefixInformation::setRouterAddressFlag(bool routerAddressFlag)
{
    this->routerAddressFlag = routerAddressFlag;
}

unsigned int Ipv6NdPrefixInformation::getValidLifetime() const
{
    return this->validLifetime;
}

void Ipv6NdPrefixInformation::setValidLifetime(unsigned int validLifetime)
{
    this->validLifetime = validLifetime;
}

unsigned int Ipv6NdPrefixInformation::getPreferredLifetime() const
{
    return this->preferredLifetime;
}

void Ipv6NdPrefixInformation::setPreferredLifetime(unsigned int preferredLifetime)
{
    this->preferredLifetime = preferredLifetime;
}

const Ipv6Address& Ipv6NdPrefixInformation::getPrefix() const
{
    return this->prefix;
}

void Ipv6NdPrefixInformation::setPrefix(const Ipv6Address& prefix)
{
    this->prefix = prefix;
}

unsigned int Ipv6NdPrefixInformation::getDistance() const
{
    return this->distance;
}

void Ipv6NdPrefixInformation::setDistance(unsigned int distance)
{
    this->distance = distance;
}

class Ipv6NdPrefixInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_prefixLength,
        FIELD_onlinkFlag,
        FIELD_autoAddressConfFlag,
        FIELD_routerAddressFlag,
        FIELD_validLifetime,
        FIELD_preferredLifetime,
        FIELD_prefix,
        FIELD_distance,
    };
  public:
    Ipv6NdPrefixInformationDescriptor();
    virtual ~Ipv6NdPrefixInformationDescriptor();

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

Register_ClassDescriptor(Ipv6NdPrefixInformationDescriptor)

Ipv6NdPrefixInformationDescriptor::Ipv6NdPrefixInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdPrefixInformation)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ipv6NdPrefixInformationDescriptor::~Ipv6NdPrefixInformationDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NdPrefixInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdPrefixInformation *>(obj)!=nullptr;
}

const char **Ipv6NdPrefixInformationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NdPrefixInformationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NdPrefixInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int Ipv6NdPrefixInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_prefixLength
        FD_ISEDITABLE,    // FIELD_onlinkFlag
        FD_ISEDITABLE,    // FIELD_autoAddressConfFlag
        FD_ISEDITABLE,    // FIELD_routerAddressFlag
        FD_ISEDITABLE,    // FIELD_validLifetime
        FD_ISEDITABLE,    // FIELD_preferredLifetime
        0,    // FIELD_prefix
        FD_ISEDITABLE,    // FIELD_distance
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "prefixLength",
        "onlinkFlag",
        "autoAddressConfFlag",
        "routerAddressFlag",
        "validLifetime",
        "preferredLifetime",
        "prefix",
        "distance",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ipv6NdPrefixInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefixLength") == 0) return base+0;
    if (fieldName[0] == 'o' && strcmp(fieldName, "onlinkFlag") == 0) return base+1;
    if (fieldName[0] == 'a' && strcmp(fieldName, "autoAddressConfFlag") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routerAddressFlag") == 0) return base+3;
    if (fieldName[0] == 'v' && strcmp(fieldName, "validLifetime") == 0) return base+4;
    if (fieldName[0] == 'p' && strcmp(fieldName, "preferredLifetime") == 0) return base+5;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefix") == 0) return base+6;
    if (fieldName[0] == 'd' && strcmp(fieldName, "distance") == 0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_prefixLength
        "bool",    // FIELD_onlinkFlag
        "bool",    // FIELD_autoAddressConfFlag
        "bool",    // FIELD_routerAddressFlag
        "unsigned int",    // FIELD_validLifetime
        "unsigned int",    // FIELD_preferredLifetime
        "inet::Ipv6Address",    // FIELD_prefix
        "unsigned int",    // FIELD_distance
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdPrefixInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdPrefixInformationDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NdPrefixInformationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = (Ipv6NdPrefixInformation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = (Ipv6NdPrefixInformation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdPrefixInformationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = (Ipv6NdPrefixInformation *)object; (void)pp;
    switch (field) {
        case FIELD_prefixLength: return ulong2string(pp->getPrefixLength());
        case FIELD_onlinkFlag: return bool2string(pp->getOnlinkFlag());
        case FIELD_autoAddressConfFlag: return bool2string(pp->getAutoAddressConfFlag());
        case FIELD_routerAddressFlag: return bool2string(pp->getRouterAddressFlag());
        case FIELD_validLifetime: return ulong2string(pp->getValidLifetime());
        case FIELD_preferredLifetime: return ulong2string(pp->getPreferredLifetime());
        case FIELD_prefix: return pp->getPrefix().str();
        case FIELD_distance: return ulong2string(pp->getDistance());
        default: return "";
    }
}

bool Ipv6NdPrefixInformationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = (Ipv6NdPrefixInformation *)object; (void)pp;
    switch (field) {
        case FIELD_prefixLength: pp->setPrefixLength(string2ulong(value)); return true;
        case FIELD_onlinkFlag: pp->setOnlinkFlag(string2bool(value)); return true;
        case FIELD_autoAddressConfFlag: pp->setAutoAddressConfFlag(string2bool(value)); return true;
        case FIELD_routerAddressFlag: pp->setRouterAddressFlag(string2bool(value)); return true;
        case FIELD_validLifetime: pp->setValidLifetime(string2ulong(value)); return true;
        case FIELD_preferredLifetime: pp->setPreferredLifetime(string2ulong(value)); return true;
        case FIELD_distance: pp->setDistance(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Ipv6NdPrefixInformationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6NdPrefixInformationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdPrefixInformation *pp = (Ipv6NdPrefixInformation *)object; (void)pp;
    switch (field) {
        case FIELD_prefix: return toVoidPtr(&pp->getPrefix()); break;
        default: return nullptr;
    }
}

InterfaceIdentifier::InterfaceIdentifier()
{
    this->normal = 0;
    this->low = 0;
    this->len = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const InterfaceIdentifier& a)
{
    doParsimPacking(b,a.normal);
    doParsimPacking(b,a.low);
    doParsimPacking(b,a.len);
}

void __doUnpacking(omnetpp::cCommBuffer *b, InterfaceIdentifier& a)
{
    doParsimUnpacking(b,a.normal);
    doParsimUnpacking(b,a.low);
    doParsimUnpacking(b,a.len);
}

class InterfaceIdentifierDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_normal,
        FIELD_low,
        FIELD_len,
    };
  public:
    InterfaceIdentifierDescriptor();
    virtual ~InterfaceIdentifierDescriptor();

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

Register_ClassDescriptor(InterfaceIdentifierDescriptor)

InterfaceIdentifierDescriptor::InterfaceIdentifierDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::InterfaceIdentifier)), "")
{
    propertynames = nullptr;
}

InterfaceIdentifierDescriptor::~InterfaceIdentifierDescriptor()
{
    delete[] propertynames;
}

bool InterfaceIdentifierDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<InterfaceIdentifier *>(obj)!=nullptr;
}

const char **InterfaceIdentifierDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *InterfaceIdentifierDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int InterfaceIdentifierDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int InterfaceIdentifierDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_normal
        FD_ISEDITABLE,    // FIELD_low
        FD_ISEDITABLE,    // FIELD_len
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *InterfaceIdentifierDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "normal",
        "low",
        "len",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int InterfaceIdentifierDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "normal") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "low") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "len") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *InterfaceIdentifierDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint32",    // FIELD_normal
        "uint32",    // FIELD_low
        "short",    // FIELD_len
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **InterfaceIdentifierDescriptor::getFieldPropertyNames(int field) const
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

const char *InterfaceIdentifierDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int InterfaceIdentifierDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    InterfaceIdentifier *pp = (InterfaceIdentifier *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *InterfaceIdentifierDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InterfaceIdentifier *pp = (InterfaceIdentifier *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string InterfaceIdentifierDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    InterfaceIdentifier *pp = (InterfaceIdentifier *)object; (void)pp;
    switch (field) {
        case FIELD_normal: return ulong2string(pp->normal);
        case FIELD_low: return ulong2string(pp->low);
        case FIELD_len: return long2string(pp->len);
        default: return "";
    }
}

bool InterfaceIdentifierDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    InterfaceIdentifier *pp = (InterfaceIdentifier *)object; (void)pp;
    switch (field) {
        case FIELD_normal: pp->normal = string2ulong(value); return true;
        case FIELD_low: pp->low = string2ulong(value); return true;
        case FIELD_len: pp->len = string2long(value); return true;
        default: return false;
    }
}

const char *InterfaceIdentifierDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *InterfaceIdentifierDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    InterfaceIdentifier *pp = (InterfaceIdentifier *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Ipv6NdVehicularPrefixInformation)

Ipv6NdVehicularPrefixInformation::Ipv6NdVehicularPrefixInformation() : ::omnetpp::cObject()
{
}

Ipv6NdVehicularPrefixInformation::Ipv6NdVehicularPrefixInformation(const Ipv6NdVehicularPrefixInformation& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdVehicularPrefixInformation::~Ipv6NdVehicularPrefixInformation()
{
}

Ipv6NdVehicularPrefixInformation& Ipv6NdVehicularPrefixInformation::operator=(const Ipv6NdVehicularPrefixInformation& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdVehicularPrefixInformation::copy(const Ipv6NdVehicularPrefixInformation& other)
{
    this->type = other.type;
    this->optionLength = other.optionLength;
    this->prefixLength = other.prefixLength;
    this->distance = other.distance;
    this->prefix = other.prefix;
}

void Ipv6NdVehicularPrefixInformation::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->optionLength);
    doParsimPacking(b,this->prefixLength);
    doParsimPacking(b,this->distance);
    doParsimPacking(b,this->prefix);
}

void Ipv6NdVehicularPrefixInformation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->optionLength);
    doParsimUnpacking(b,this->prefixLength);
    doParsimUnpacking(b,this->distance);
    doParsimUnpacking(b,this->prefix);
}

unsigned int Ipv6NdVehicularPrefixInformation::getType() const
{
    return this->type;
}

void Ipv6NdVehicularPrefixInformation::setType(unsigned int type)
{
    this->type = type;
}

unsigned int Ipv6NdVehicularPrefixInformation::getOptionLength() const
{
    return this->optionLength;
}

void Ipv6NdVehicularPrefixInformation::setOptionLength(unsigned int optionLength)
{
    this->optionLength = optionLength;
}

unsigned int Ipv6NdVehicularPrefixInformation::getPrefixLength() const
{
    return this->prefixLength;
}

void Ipv6NdVehicularPrefixInformation::setPrefixLength(unsigned int prefixLength)
{
    this->prefixLength = prefixLength;
}

unsigned int Ipv6NdVehicularPrefixInformation::getDistance() const
{
    return this->distance;
}

void Ipv6NdVehicularPrefixInformation::setDistance(unsigned int distance)
{
    this->distance = distance;
}

const Ipv6Address& Ipv6NdVehicularPrefixInformation::getPrefix() const
{
    return this->prefix;
}

void Ipv6NdVehicularPrefixInformation::setPrefix(const Ipv6Address& prefix)
{
    this->prefix = prefix;
}

class Ipv6NdVehicularPrefixInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_type,
        FIELD_optionLength,
        FIELD_prefixLength,
        FIELD_distance,
        FIELD_prefix,
    };
  public:
    Ipv6NdVehicularPrefixInformationDescriptor();
    virtual ~Ipv6NdVehicularPrefixInformationDescriptor();

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

Register_ClassDescriptor(Ipv6NdVehicularPrefixInformationDescriptor)

Ipv6NdVehicularPrefixInformationDescriptor::Ipv6NdVehicularPrefixInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdVehicularPrefixInformation)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ipv6NdVehicularPrefixInformationDescriptor::~Ipv6NdVehicularPrefixInformationDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NdVehicularPrefixInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdVehicularPrefixInformation *>(obj)!=nullptr;
}

const char **Ipv6NdVehicularPrefixInformationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NdVehicularPrefixInformationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NdVehicularPrefixInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int Ipv6NdVehicularPrefixInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_optionLength
        FD_ISEDITABLE,    // FIELD_prefixLength
        FD_ISEDITABLE,    // FIELD_distance
        0,    // FIELD_prefix
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdVehicularPrefixInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "optionLength",
        "prefixLength",
        "distance",
        "prefix",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ipv6NdVehicularPrefixInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+0;
    if (fieldName[0] == 'o' && strcmp(fieldName, "optionLength") == 0) return base+1;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefixLength") == 0) return base+2;
    if (fieldName[0] == 'd' && strcmp(fieldName, "distance") == 0) return base+3;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefix") == 0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NdVehicularPrefixInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_type
        "unsigned int",    // FIELD_optionLength
        "unsigned int",    // FIELD_prefixLength
        "unsigned int",    // FIELD_distance
        "inet::Ipv6Address",    // FIELD_prefix
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdVehicularPrefixInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdVehicularPrefixInformationDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NdVehicularPrefixInformationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularPrefixInformation *pp = (Ipv6NdVehicularPrefixInformation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NdVehicularPrefixInformationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularPrefixInformation *pp = (Ipv6NdVehicularPrefixInformation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdVehicularPrefixInformationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularPrefixInformation *pp = (Ipv6NdVehicularPrefixInformation *)object; (void)pp;
    switch (field) {
        case FIELD_type: return ulong2string(pp->getType());
        case FIELD_optionLength: return ulong2string(pp->getOptionLength());
        case FIELD_prefixLength: return ulong2string(pp->getPrefixLength());
        case FIELD_distance: return ulong2string(pp->getDistance());
        case FIELD_prefix: return pp->getPrefix().str();
        default: return "";
    }
}

bool Ipv6NdVehicularPrefixInformationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularPrefixInformation *pp = (Ipv6NdVehicularPrefixInformation *)object; (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2ulong(value)); return true;
        case FIELD_optionLength: pp->setOptionLength(string2ulong(value)); return true;
        case FIELD_prefixLength: pp->setPrefixLength(string2ulong(value)); return true;
        case FIELD_distance: pp->setDistance(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Ipv6NdVehicularPrefixInformationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6NdVehicularPrefixInformationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularPrefixInformation *pp = (Ipv6NdVehicularPrefixInformation *)object; (void)pp;
    switch (field) {
        case FIELD_prefix: return toVoidPtr(&pp->getPrefix()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6NdVehicularServiceInformation)

Ipv6NdVehicularServiceInformation::Ipv6NdVehicularServiceInformation() : ::omnetpp::cObject()
{
}

Ipv6NdVehicularServiceInformation::Ipv6NdVehicularServiceInformation(const Ipv6NdVehicularServiceInformation& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdVehicularServiceInformation::~Ipv6NdVehicularServiceInformation()
{
}

Ipv6NdVehicularServiceInformation& Ipv6NdVehicularServiceInformation::operator=(const Ipv6NdVehicularServiceInformation& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdVehicularServiceInformation::copy(const Ipv6NdVehicularServiceInformation& other)
{
    this->type = other.type;
    this->portNumber = other.portNumber;
    this->optionLength = other.optionLength;
    this->protocol = other.protocol;
    this->serviceAddress = other.serviceAddress;
}

void Ipv6NdVehicularServiceInformation::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->portNumber);
    doParsimPacking(b,this->optionLength);
    doParsimPacking(b,this->protocol);
    doParsimPacking(b,this->serviceAddress);
}

void Ipv6NdVehicularServiceInformation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->portNumber);
    doParsimUnpacking(b,this->optionLength);
    doParsimUnpacking(b,this->protocol);
    doParsimUnpacking(b,this->serviceAddress);
}

unsigned int Ipv6NdVehicularServiceInformation::getType() const
{
    return this->type;
}

void Ipv6NdVehicularServiceInformation::setType(unsigned int type)
{
    this->type = type;
}

unsigned int Ipv6NdVehicularServiceInformation::getPortNumber() const
{
    return this->portNumber;
}

void Ipv6NdVehicularServiceInformation::setPortNumber(unsigned int portNumber)
{
    this->portNumber = portNumber;
}

unsigned int Ipv6NdVehicularServiceInformation::getOptionLength() const
{
    return this->optionLength;
}

void Ipv6NdVehicularServiceInformation::setOptionLength(unsigned int optionLength)
{
    this->optionLength = optionLength;
}

unsigned int Ipv6NdVehicularServiceInformation::getProtocol() const
{
    return this->protocol;
}

void Ipv6NdVehicularServiceInformation::setProtocol(unsigned int protocol)
{
    this->protocol = protocol;
}

const Ipv6Address& Ipv6NdVehicularServiceInformation::getServiceAddress() const
{
    return this->serviceAddress;
}

void Ipv6NdVehicularServiceInformation::setServiceAddress(const Ipv6Address& serviceAddress)
{
    this->serviceAddress = serviceAddress;
}

class Ipv6NdVehicularServiceInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_type,
        FIELD_portNumber,
        FIELD_optionLength,
        FIELD_protocol,
        FIELD_serviceAddress,
    };
  public:
    Ipv6NdVehicularServiceInformationDescriptor();
    virtual ~Ipv6NdVehicularServiceInformationDescriptor();

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

Register_ClassDescriptor(Ipv6NdVehicularServiceInformationDescriptor)

Ipv6NdVehicularServiceInformationDescriptor::Ipv6NdVehicularServiceInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdVehicularServiceInformation)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ipv6NdVehicularServiceInformationDescriptor::~Ipv6NdVehicularServiceInformationDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NdVehicularServiceInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdVehicularServiceInformation *>(obj)!=nullptr;
}

const char **Ipv6NdVehicularServiceInformationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NdVehicularServiceInformationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NdVehicularServiceInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int Ipv6NdVehicularServiceInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_portNumber
        FD_ISEDITABLE,    // FIELD_optionLength
        FD_ISEDITABLE,    // FIELD_protocol
        0,    // FIELD_serviceAddress
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdVehicularServiceInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "portNumber",
        "optionLength",
        "protocol",
        "serviceAddress",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ipv6NdVehicularServiceInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "portNumber") == 0) return base+1;
    if (fieldName[0] == 'o' && strcmp(fieldName, "optionLength") == 0) return base+2;
    if (fieldName[0] == 'p' && strcmp(fieldName, "protocol") == 0) return base+3;
    if (fieldName[0] == 's' && strcmp(fieldName, "serviceAddress") == 0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NdVehicularServiceInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_type
        "unsigned int",    // FIELD_portNumber
        "unsigned int",    // FIELD_optionLength
        "unsigned int",    // FIELD_protocol
        "inet::Ipv6Address",    // FIELD_serviceAddress
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdVehicularServiceInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdVehicularServiceInformationDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NdVehicularServiceInformationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularServiceInformation *pp = (Ipv6NdVehicularServiceInformation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NdVehicularServiceInformationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularServiceInformation *pp = (Ipv6NdVehicularServiceInformation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdVehicularServiceInformationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularServiceInformation *pp = (Ipv6NdVehicularServiceInformation *)object; (void)pp;
    switch (field) {
        case FIELD_type: return ulong2string(pp->getType());
        case FIELD_portNumber: return ulong2string(pp->getPortNumber());
        case FIELD_optionLength: return ulong2string(pp->getOptionLength());
        case FIELD_protocol: return ulong2string(pp->getProtocol());
        case FIELD_serviceAddress: return pp->getServiceAddress().str();
        default: return "";
    }
}

bool Ipv6NdVehicularServiceInformationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularServiceInformation *pp = (Ipv6NdVehicularServiceInformation *)object; (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2ulong(value)); return true;
        case FIELD_portNumber: pp->setPortNumber(string2ulong(value)); return true;
        case FIELD_optionLength: pp->setOptionLength(string2ulong(value)); return true;
        case FIELD_protocol: pp->setProtocol(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Ipv6NdVehicularServiceInformationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6NdVehicularServiceInformationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularServiceInformation *pp = (Ipv6NdVehicularServiceInformation *)object; (void)pp;
    switch (field) {
        case FIELD_serviceAddress: return toVoidPtr(&pp->getServiceAddress()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6NdAddressRegistrationOption)

Ipv6NdAddressRegistrationOption::Ipv6NdAddressRegistrationOption() : ::omnetpp::cObject()
{
}

Ipv6NdAddressRegistrationOption::Ipv6NdAddressRegistrationOption(const Ipv6NdAddressRegistrationOption& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdAddressRegistrationOption::~Ipv6NdAddressRegistrationOption()
{
}

Ipv6NdAddressRegistrationOption& Ipv6NdAddressRegistrationOption::operator=(const Ipv6NdAddressRegistrationOption& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdAddressRegistrationOption::copy(const Ipv6NdAddressRegistrationOption& other)
{
    this->type = other.type;
    this->optionLength = other.optionLength;
    this->status = other.status;
    this->registLifeTime = other.registLifeTime;
    this->EUI64 = other.EUI64;
}

void Ipv6NdAddressRegistrationOption::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->optionLength);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->registLifeTime);
    doParsimPacking(b,this->EUI64);
}

void Ipv6NdAddressRegistrationOption::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->optionLength);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->registLifeTime);
    doParsimUnpacking(b,this->EUI64);
}

unsigned int Ipv6NdAddressRegistrationOption::getType() const
{
    return this->type;
}

void Ipv6NdAddressRegistrationOption::setType(unsigned int type)
{
    this->type = type;
}

unsigned int Ipv6NdAddressRegistrationOption::getOptionLength() const
{
    return this->optionLength;
}

void Ipv6NdAddressRegistrationOption::setOptionLength(unsigned int optionLength)
{
    this->optionLength = optionLength;
}

unsigned int Ipv6NdAddressRegistrationOption::getStatus() const
{
    return this->status;
}

void Ipv6NdAddressRegistrationOption::setStatus(unsigned int status)
{
    this->status = status;
}

unsigned int Ipv6NdAddressRegistrationOption::getRegistLifeTime() const
{
    return this->registLifeTime;
}

void Ipv6NdAddressRegistrationOption::setRegistLifeTime(unsigned int registLifeTime)
{
    this->registLifeTime = registLifeTime;
}

const InterfaceIdentifier& Ipv6NdAddressRegistrationOption::getEUI64() const
{
    return this->EUI64;
}

void Ipv6NdAddressRegistrationOption::setEUI64(const InterfaceIdentifier& EUI64)
{
    this->EUI64 = EUI64;
}

class Ipv6NdAddressRegistrationOptionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_type,
        FIELD_optionLength,
        FIELD_status,
        FIELD_registLifeTime,
        FIELD_EUI64,
    };
  public:
    Ipv6NdAddressRegistrationOptionDescriptor();
    virtual ~Ipv6NdAddressRegistrationOptionDescriptor();

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

Register_ClassDescriptor(Ipv6NdAddressRegistrationOptionDescriptor)

Ipv6NdAddressRegistrationOptionDescriptor::Ipv6NdAddressRegistrationOptionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdAddressRegistrationOption)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ipv6NdAddressRegistrationOptionDescriptor::~Ipv6NdAddressRegistrationOptionDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NdAddressRegistrationOptionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdAddressRegistrationOption *>(obj)!=nullptr;
}

const char **Ipv6NdAddressRegistrationOptionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NdAddressRegistrationOptionDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NdAddressRegistrationOptionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int Ipv6NdAddressRegistrationOptionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_optionLength
        FD_ISEDITABLE,    // FIELD_status
        FD_ISEDITABLE,    // FIELD_registLifeTime
        FD_ISCOMPOUND,    // FIELD_EUI64
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdAddressRegistrationOptionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "optionLength",
        "status",
        "registLifeTime",
        "EUI64",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int Ipv6NdAddressRegistrationOptionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+0;
    if (fieldName[0] == 'o' && strcmp(fieldName, "optionLength") == 0) return base+1;
    if (fieldName[0] == 's' && strcmp(fieldName, "status") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "registLifeTime") == 0) return base+3;
    if (fieldName[0] == 'E' && strcmp(fieldName, "EUI64") == 0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NdAddressRegistrationOptionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_type
        "unsigned int",    // FIELD_optionLength
        "unsigned int",    // FIELD_status
        "unsigned int",    // FIELD_registLifeTime
        "inet::InterfaceIdentifier",    // FIELD_EUI64
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdAddressRegistrationOptionDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdAddressRegistrationOptionDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NdAddressRegistrationOptionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdAddressRegistrationOption *pp = (Ipv6NdAddressRegistrationOption *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NdAddressRegistrationOptionDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdAddressRegistrationOption *pp = (Ipv6NdAddressRegistrationOption *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdAddressRegistrationOptionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdAddressRegistrationOption *pp = (Ipv6NdAddressRegistrationOption *)object; (void)pp;
    switch (field) {
        case FIELD_type: return ulong2string(pp->getType());
        case FIELD_optionLength: return ulong2string(pp->getOptionLength());
        case FIELD_status: return ulong2string(pp->getStatus());
        case FIELD_registLifeTime: return ulong2string(pp->getRegistLifeTime());
        case FIELD_EUI64: {std::stringstream out; out << pp->getEUI64(); return out.str();}
        default: return "";
    }
}

bool Ipv6NdAddressRegistrationOptionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdAddressRegistrationOption *pp = (Ipv6NdAddressRegistrationOption *)object; (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2ulong(value)); return true;
        case FIELD_optionLength: pp->setOptionLength(string2ulong(value)); return true;
        case FIELD_status: pp->setStatus(string2ulong(value)); return true;
        case FIELD_registLifeTime: pp->setRegistLifeTime(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Ipv6NdAddressRegistrationOptionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_EUI64: return omnetpp::opp_typename(typeid(InterfaceIdentifier));
        default: return nullptr;
    };
}

void *Ipv6NdAddressRegistrationOptionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdAddressRegistrationOption *pp = (Ipv6NdAddressRegistrationOption *)object; (void)pp;
    switch (field) {
        case FIELD_EUI64: return toVoidPtr(&pp->getEUI64()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6NdVehicularMobilityInformation)

Ipv6NdVehicularMobilityInformation::Ipv6NdVehicularMobilityInformation() : ::omnetpp::cObject()
{
}

Ipv6NdVehicularMobilityInformation::Ipv6NdVehicularMobilityInformation(const Ipv6NdVehicularMobilityInformation& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdVehicularMobilityInformation::~Ipv6NdVehicularMobilityInformation()
{
}

Ipv6NdVehicularMobilityInformation& Ipv6NdVehicularMobilityInformation::operator=(const Ipv6NdVehicularMobilityInformation& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdVehicularMobilityInformation::copy(const Ipv6NdVehicularMobilityInformation& other)
{
    this->length = other.length;
    this->type = other.type;
}

void Ipv6NdVehicularMobilityInformation::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->length);
    doParsimPacking(b,this->type);
}

void Ipv6NdVehicularMobilityInformation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->length);
    doParsimUnpacking(b,this->type);
}

unsigned short Ipv6NdVehicularMobilityInformation::getLength() const
{
    return this->length;
}

void Ipv6NdVehicularMobilityInformation::setLength(unsigned short length)
{
    this->length = length;
}

unsigned int Ipv6NdVehicularMobilityInformation::getType() const
{
    return this->type;
}

void Ipv6NdVehicularMobilityInformation::setType(unsigned int type)
{
    this->type = type;
}

class Ipv6NdVehicularMobilityInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_length,
        FIELD_type,
    };
  public:
    Ipv6NdVehicularMobilityInformationDescriptor();
    virtual ~Ipv6NdVehicularMobilityInformationDescriptor();

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

Register_ClassDescriptor(Ipv6NdVehicularMobilityInformationDescriptor)

Ipv6NdVehicularMobilityInformationDescriptor::Ipv6NdVehicularMobilityInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdVehicularMobilityInformation)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ipv6NdVehicularMobilityInformationDescriptor::~Ipv6NdVehicularMobilityInformationDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NdVehicularMobilityInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdVehicularMobilityInformation *>(obj)!=nullptr;
}

const char **Ipv6NdVehicularMobilityInformationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NdVehicularMobilityInformationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NdVehicularMobilityInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int Ipv6NdVehicularMobilityInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_length
        FD_ISEDITABLE,    // FIELD_type
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdVehicularMobilityInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "length",
        "type",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ipv6NdVehicularMobilityInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "length") == 0) return base+0;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NdVehicularMobilityInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_length
        "unsigned int",    // FIELD_type
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdVehicularMobilityInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdVehicularMobilityInformationDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NdVehicularMobilityInformationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularMobilityInformation *pp = (Ipv6NdVehicularMobilityInformation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NdVehicularMobilityInformationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularMobilityInformation *pp = (Ipv6NdVehicularMobilityInformation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdVehicularMobilityInformationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularMobilityInformation *pp = (Ipv6NdVehicularMobilityInformation *)object; (void)pp;
    switch (field) {
        case FIELD_length: return ulong2string(pp->getLength());
        case FIELD_type: return ulong2string(pp->getType());
        default: return "";
    }
}

bool Ipv6NdVehicularMobilityInformationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularMobilityInformation *pp = (Ipv6NdVehicularMobilityInformation *)object; (void)pp;
    switch (field) {
        case FIELD_length: pp->setLength(string2ulong(value)); return true;
        case FIELD_type: pp->setType(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Ipv6NdVehicularMobilityInformationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6NdVehicularMobilityInformationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdVehicularMobilityInformation *pp = (Ipv6NdVehicularMobilityInformation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Mipv6NdAdvertisementInterval)

Mipv6NdAdvertisementInterval::Mipv6NdAdvertisementInterval() : ::omnetpp::cObject()
{
}

Mipv6NdAdvertisementInterval::Mipv6NdAdvertisementInterval(const Mipv6NdAdvertisementInterval& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Mipv6NdAdvertisementInterval::~Mipv6NdAdvertisementInterval()
{
}

Mipv6NdAdvertisementInterval& Mipv6NdAdvertisementInterval::operator=(const Mipv6NdAdvertisementInterval& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Mipv6NdAdvertisementInterval::copy(const Mipv6NdAdvertisementInterval& other)
{
    this->advertisementInterval = other.advertisementInterval;
}

void Mipv6NdAdvertisementInterval::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->advertisementInterval);
}

void Mipv6NdAdvertisementInterval::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->advertisementInterval);
}

unsigned int Mipv6NdAdvertisementInterval::getAdvertisementInterval() const
{
    return this->advertisementInterval;
}

void Mipv6NdAdvertisementInterval::setAdvertisementInterval(unsigned int advertisementInterval)
{
    this->advertisementInterval = advertisementInterval;
}

class Mipv6NdAdvertisementIntervalDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_advertisementInterval,
    };
  public:
    Mipv6NdAdvertisementIntervalDescriptor();
    virtual ~Mipv6NdAdvertisementIntervalDescriptor();

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

Register_ClassDescriptor(Mipv6NdAdvertisementIntervalDescriptor)

Mipv6NdAdvertisementIntervalDescriptor::Mipv6NdAdvertisementIntervalDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Mipv6NdAdvertisementInterval)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Mipv6NdAdvertisementIntervalDescriptor::~Mipv6NdAdvertisementIntervalDescriptor()
{
    delete[] propertynames;
}

bool Mipv6NdAdvertisementIntervalDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Mipv6NdAdvertisementInterval *>(obj)!=nullptr;
}

const char **Mipv6NdAdvertisementIntervalDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Mipv6NdAdvertisementIntervalDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int Mipv6NdAdvertisementIntervalDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_advertisementInterval
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "advertisementInterval",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Mipv6NdAdvertisementIntervalDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'a' && strcmp(fieldName, "advertisementInterval") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_advertisementInterval
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Mipv6NdAdvertisementIntervalDescriptor::getFieldPropertyNames(int field) const
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

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Mipv6NdAdvertisementIntervalDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = (Mipv6NdAdvertisementInterval *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = (Mipv6NdAdvertisementInterval *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Mipv6NdAdvertisementIntervalDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = (Mipv6NdAdvertisementInterval *)object; (void)pp;
    switch (field) {
        case FIELD_advertisementInterval: return ulong2string(pp->getAdvertisementInterval());
        default: return "";
    }
}

bool Mipv6NdAdvertisementIntervalDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = (Mipv6NdAdvertisementInterval *)object; (void)pp;
    switch (field) {
        case FIELD_advertisementInterval: pp->setAdvertisementInterval(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Mipv6NdAdvertisementIntervalDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Mipv6NdAdvertisementIntervalDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Mipv6NdAdvertisementInterval *pp = (Mipv6NdAdvertisementInterval *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Mipv6HaInformation)

Mipv6HaInformation::Mipv6HaInformation() : ::omnetpp::cObject()
{
}

Mipv6HaInformation::Mipv6HaInformation(const Mipv6HaInformation& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Mipv6HaInformation::~Mipv6HaInformation()
{
}

Mipv6HaInformation& Mipv6HaInformation::operator=(const Mipv6HaInformation& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Mipv6HaInformation::copy(const Mipv6HaInformation& other)
{
    this->homeAgentPreference = other.homeAgentPreference;
    this->homeAgentLifetime = other.homeAgentLifetime;
}

void Mipv6HaInformation::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->homeAgentPreference);
    doParsimPacking(b,this->homeAgentLifetime);
}

void Mipv6HaInformation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->homeAgentPreference);
    doParsimUnpacking(b,this->homeAgentLifetime);
}

unsigned int Mipv6HaInformation::getHomeAgentPreference() const
{
    return this->homeAgentPreference;
}

void Mipv6HaInformation::setHomeAgentPreference(unsigned int homeAgentPreference)
{
    this->homeAgentPreference = homeAgentPreference;
}

unsigned int Mipv6HaInformation::getHomeAgentLifetime() const
{
    return this->homeAgentLifetime;
}

void Mipv6HaInformation::setHomeAgentLifetime(unsigned int homeAgentLifetime)
{
    this->homeAgentLifetime = homeAgentLifetime;
}

class Mipv6HaInformationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_homeAgentPreference,
        FIELD_homeAgentLifetime,
    };
  public:
    Mipv6HaInformationDescriptor();
    virtual ~Mipv6HaInformationDescriptor();

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

Register_ClassDescriptor(Mipv6HaInformationDescriptor)

Mipv6HaInformationDescriptor::Mipv6HaInformationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Mipv6HaInformation)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Mipv6HaInformationDescriptor::~Mipv6HaInformationDescriptor()
{
    delete[] propertynames;
}

bool Mipv6HaInformationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Mipv6HaInformation *>(obj)!=nullptr;
}

const char **Mipv6HaInformationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Mipv6HaInformationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Mipv6HaInformationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int Mipv6HaInformationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_homeAgentPreference
        FD_ISEDITABLE,    // FIELD_homeAgentLifetime
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Mipv6HaInformationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "homeAgentPreference",
        "homeAgentLifetime",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Mipv6HaInformationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "homeAgentPreference") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "homeAgentLifetime") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Mipv6HaInformationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_homeAgentPreference
        "unsigned int",    // FIELD_homeAgentLifetime
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Mipv6HaInformationDescriptor::getFieldPropertyNames(int field) const
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

const char *Mipv6HaInformationDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Mipv6HaInformationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Mipv6HaInformation *pp = (Mipv6HaInformation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Mipv6HaInformationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Mipv6HaInformation *pp = (Mipv6HaInformation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Mipv6HaInformationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Mipv6HaInformation *pp = (Mipv6HaInformation *)object; (void)pp;
    switch (field) {
        case FIELD_homeAgentPreference: return ulong2string(pp->getHomeAgentPreference());
        case FIELD_homeAgentLifetime: return ulong2string(pp->getHomeAgentLifetime());
        default: return "";
    }
}

bool Mipv6HaInformationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Mipv6HaInformation *pp = (Mipv6HaInformation *)object; (void)pp;
    switch (field) {
        case FIELD_homeAgentPreference: pp->setHomeAgentPreference(string2ulong(value)); return true;
        case FIELD_homeAgentLifetime: pp->setHomeAgentLifetime(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Mipv6HaInformationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Mipv6HaInformationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Mipv6HaInformation *pp = (Mipv6HaInformation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Ipv6NdMessage)

Ipv6NdMessage::Ipv6NdMessage() : ::inet::Icmpv6Header()
{
}

Ipv6NdMessage::Ipv6NdMessage(const Ipv6NdMessage& other) : ::inet::Icmpv6Header(other)
{
    copy(other);
}

Ipv6NdMessage::~Ipv6NdMessage()
{
}

Ipv6NdMessage& Ipv6NdMessage::operator=(const Ipv6NdMessage& other)
{
    if (this == &other) return *this;
    ::inet::Icmpv6Header::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdMessage::copy(const Ipv6NdMessage& other)
{
    this->code = other.code;
}

void Ipv6NdMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Icmpv6Header::parsimPack(b);
    doParsimPacking(b,this->code);
}

void Ipv6NdMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Icmpv6Header::parsimUnpack(b);
    doParsimUnpacking(b,this->code);
}

int Ipv6NdMessage::getCode() const
{
    return this->code;
}

void Ipv6NdMessage::setCode(int code)
{
    handleChange();
    this->code = code;
}

class Ipv6NdMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_code,
    };
  public:
    Ipv6NdMessageDescriptor();
    virtual ~Ipv6NdMessageDescriptor();

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

Register_ClassDescriptor(Ipv6NdMessageDescriptor)

Ipv6NdMessageDescriptor::Ipv6NdMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdMessage)), "inet::Icmpv6Header")
{
    propertynames = nullptr;
}

Ipv6NdMessageDescriptor::~Ipv6NdMessageDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NdMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdMessage *>(obj)!=nullptr;
}

const char **Ipv6NdMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NdMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NdMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int Ipv6NdMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_code
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "code",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6NdMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'c' && strcmp(fieldName, "code") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NdMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_code
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NdMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdMessage *pp = (Ipv6NdMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NdMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdMessage *pp = (Ipv6NdMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdMessage *pp = (Ipv6NdMessage *)object; (void)pp;
    switch (field) {
        case FIELD_code: return long2string(pp->getCode());
        default: return "";
    }
}

bool Ipv6NdMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdMessage *pp = (Ipv6NdMessage *)object; (void)pp;
    switch (field) {
        case FIELD_code: pp->setCode(string2long(value)); return true;
        default: return false;
    }
}

const char *Ipv6NdMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6NdMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdMessage *pp = (Ipv6NdMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Ipv6RouterSolicitation)

Ipv6RouterSolicitation::Ipv6RouterSolicitation() : ::inet::Ipv6NdMessage()
{
    this->setType(ICMPv6_ROUTER_SOL);

}

Ipv6RouterSolicitation::Ipv6RouterSolicitation(const Ipv6RouterSolicitation& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6RouterSolicitation::~Ipv6RouterSolicitation()
{
}

Ipv6RouterSolicitation& Ipv6RouterSolicitation::operator=(const Ipv6RouterSolicitation& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6RouterSolicitation::copy(const Ipv6RouterSolicitation& other)
{
    this->sourceLinkLayerAddress = other.sourceLinkLayerAddress;
}

void Ipv6RouterSolicitation::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->sourceLinkLayerAddress);
}

void Ipv6RouterSolicitation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceLinkLayerAddress);
}

const MacAddress& Ipv6RouterSolicitation::getSourceLinkLayerAddress() const
{
    return this->sourceLinkLayerAddress;
}

void Ipv6RouterSolicitation::setSourceLinkLayerAddress(const MacAddress& sourceLinkLayerAddress)
{
    handleChange();
    this->sourceLinkLayerAddress = sourceLinkLayerAddress;
}

class Ipv6RouterSolicitationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_sourceLinkLayerAddress,
    };
  public:
    Ipv6RouterSolicitationDescriptor();
    virtual ~Ipv6RouterSolicitationDescriptor();

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

Register_ClassDescriptor(Ipv6RouterSolicitationDescriptor)

Ipv6RouterSolicitationDescriptor::Ipv6RouterSolicitationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6RouterSolicitation)), "inet::Ipv6NdMessage")
{
    propertynames = nullptr;
}

Ipv6RouterSolicitationDescriptor::~Ipv6RouterSolicitationDescriptor()
{
    delete[] propertynames;
}

bool Ipv6RouterSolicitationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6RouterSolicitation *>(obj)!=nullptr;
}

const char **Ipv6RouterSolicitationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6RouterSolicitationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6RouterSolicitationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int Ipv6RouterSolicitationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_sourceLinkLayerAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6RouterSolicitationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceLinkLayerAddress",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ipv6RouterSolicitationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceLinkLayerAddress") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6RouterSolicitationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_sourceLinkLayerAddress
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6RouterSolicitationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6RouterSolicitationDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6RouterSolicitationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = (Ipv6RouterSolicitation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6RouterSolicitationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = (Ipv6RouterSolicitation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6RouterSolicitationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = (Ipv6RouterSolicitation *)object; (void)pp;
    switch (field) {
        case FIELD_sourceLinkLayerAddress: return pp->getSourceLinkLayerAddress().str();
        default: return "";
    }
}

bool Ipv6RouterSolicitationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = (Ipv6RouterSolicitation *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *Ipv6RouterSolicitationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6RouterSolicitationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterSolicitation *pp = (Ipv6RouterSolicitation *)object; (void)pp;
    switch (field) {
        case FIELD_sourceLinkLayerAddress: return toVoidPtr(&pp->getSourceLinkLayerAddress()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6RouterAdvertisement)

Ipv6RouterAdvertisement::Ipv6RouterAdvertisement() : ::inet::Ipv6NdMessage()
{
    this->setType(ICMPv6_ROUTER_AD);

}

Ipv6RouterAdvertisement::Ipv6RouterAdvertisement(const Ipv6RouterAdvertisement& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6RouterAdvertisement::~Ipv6RouterAdvertisement()
{
    delete [] this->prefixInformation;
}

Ipv6RouterAdvertisement& Ipv6RouterAdvertisement::operator=(const Ipv6RouterAdvertisement& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6RouterAdvertisement::copy(const Ipv6RouterAdvertisement& other)
{
    this->curHopLimit = other.curHopLimit;
    this->managedAddrConfFlag = other.managedAddrConfFlag;
    this->otherStatefulConfFlag = other.otherStatefulConfFlag;
    this->homeAgentFlag = other.homeAgentFlag;
    this->routerLifetime = other.routerLifetime;
    this->reachableTime = other.reachableTime;
    this->retransTimer = other.retransTimer;
    this->sourceLinkLayerAddress = other.sourceLinkLayerAddress;
    this->MTU = other.MTU;
    delete [] this->prefixInformation;
    this->prefixInformation = (other.prefixInformation_arraysize==0) ? nullptr : new Ipv6NdPrefixInformation[other.prefixInformation_arraysize];
    prefixInformation_arraysize = other.prefixInformation_arraysize;
    for (size_t i = 0; i < prefixInformation_arraysize; i++) {
        this->prefixInformation[i] = other.prefixInformation[i];
    }
    this->advInterval = other.advInterval;
    this->haInformation = other.haInformation;
    this->srcGlobalAddress = other.srcGlobalAddress;
    this->isDadRequired_ = other.isDadRequired_;
}

void Ipv6RouterAdvertisement::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->curHopLimit);
    doParsimPacking(b,this->managedAddrConfFlag);
    doParsimPacking(b,this->otherStatefulConfFlag);
    doParsimPacking(b,this->homeAgentFlag);
    doParsimPacking(b,this->routerLifetime);
    doParsimPacking(b,this->reachableTime);
    doParsimPacking(b,this->retransTimer);
    doParsimPacking(b,this->sourceLinkLayerAddress);
    doParsimPacking(b,this->MTU);
    b->pack(prefixInformation_arraysize);
    doParsimArrayPacking(b,this->prefixInformation,prefixInformation_arraysize);
    doParsimPacking(b,this->advInterval);
    doParsimPacking(b,this->haInformation);
    doParsimPacking(b,this->srcGlobalAddress);
    doParsimPacking(b,this->isDadRequired_);
}

void Ipv6RouterAdvertisement::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->curHopLimit);
    doParsimUnpacking(b,this->managedAddrConfFlag);
    doParsimUnpacking(b,this->otherStatefulConfFlag);
    doParsimUnpacking(b,this->homeAgentFlag);
    doParsimUnpacking(b,this->routerLifetime);
    doParsimUnpacking(b,this->reachableTime);
    doParsimUnpacking(b,this->retransTimer);
    doParsimUnpacking(b,this->sourceLinkLayerAddress);
    doParsimUnpacking(b,this->MTU);
    delete [] this->prefixInformation;
    b->unpack(prefixInformation_arraysize);
    if (prefixInformation_arraysize == 0) {
        this->prefixInformation = nullptr;
    } else {
        this->prefixInformation = new Ipv6NdPrefixInformation[prefixInformation_arraysize];
        doParsimArrayUnpacking(b,this->prefixInformation,prefixInformation_arraysize);
    }
    doParsimUnpacking(b,this->advInterval);
    doParsimUnpacking(b,this->haInformation);
    doParsimUnpacking(b,this->srcGlobalAddress);
    doParsimUnpacking(b,this->isDadRequired_);
}

unsigned short Ipv6RouterAdvertisement::getCurHopLimit() const
{
    return this->curHopLimit;
}

void Ipv6RouterAdvertisement::setCurHopLimit(unsigned short curHopLimit)
{
    handleChange();
    this->curHopLimit = curHopLimit;
}

bool Ipv6RouterAdvertisement::getManagedAddrConfFlag() const
{
    return this->managedAddrConfFlag;
}

void Ipv6RouterAdvertisement::setManagedAddrConfFlag(bool managedAddrConfFlag)
{
    handleChange();
    this->managedAddrConfFlag = managedAddrConfFlag;
}

bool Ipv6RouterAdvertisement::getOtherStatefulConfFlag() const
{
    return this->otherStatefulConfFlag;
}

void Ipv6RouterAdvertisement::setOtherStatefulConfFlag(bool otherStatefulConfFlag)
{
    handleChange();
    this->otherStatefulConfFlag = otherStatefulConfFlag;
}

bool Ipv6RouterAdvertisement::getHomeAgentFlag() const
{
    return this->homeAgentFlag;
}

void Ipv6RouterAdvertisement::setHomeAgentFlag(bool homeAgentFlag)
{
    handleChange();
    this->homeAgentFlag = homeAgentFlag;
}

unsigned short Ipv6RouterAdvertisement::getRouterLifetime() const
{
    return this->routerLifetime;
}

void Ipv6RouterAdvertisement::setRouterLifetime(unsigned short routerLifetime)
{
    handleChange();
    this->routerLifetime = routerLifetime;
}

unsigned int Ipv6RouterAdvertisement::getReachableTime() const
{
    return this->reachableTime;
}

void Ipv6RouterAdvertisement::setReachableTime(unsigned int reachableTime)
{
    handleChange();
    this->reachableTime = reachableTime;
}

unsigned int Ipv6RouterAdvertisement::getRetransTimer() const
{
    return this->retransTimer;
}

void Ipv6RouterAdvertisement::setRetransTimer(unsigned int retransTimer)
{
    handleChange();
    this->retransTimer = retransTimer;
}

const MacAddress& Ipv6RouterAdvertisement::getSourceLinkLayerAddress() const
{
    return this->sourceLinkLayerAddress;
}

void Ipv6RouterAdvertisement::setSourceLinkLayerAddress(const MacAddress& sourceLinkLayerAddress)
{
    handleChange();
    this->sourceLinkLayerAddress = sourceLinkLayerAddress;
}

unsigned int Ipv6RouterAdvertisement::getMTU() const
{
    return this->MTU;
}

void Ipv6RouterAdvertisement::setMTU(unsigned int MTU)
{
    handleChange();
    this->MTU = MTU;
}

size_t Ipv6RouterAdvertisement::getPrefixInformationArraySize() const
{
    return prefixInformation_arraysize;
}

const Ipv6NdPrefixInformation& Ipv6RouterAdvertisement::getPrefixInformation(size_t k) const
{
    if (k >= prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size prefixInformation_arraysize indexed by %lu", (unsigned long)k);
    return this->prefixInformation[k];
}

void Ipv6RouterAdvertisement::setPrefixInformationArraySize(size_t newSize)
{
    handleChange();
    Ipv6NdPrefixInformation *prefixInformation2 = (newSize==0) ? nullptr : new Ipv6NdPrefixInformation[newSize];
    size_t minSize = prefixInformation_arraysize < newSize ? prefixInformation_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        prefixInformation2[i] = this->prefixInformation[i];
    delete [] this->prefixInformation;
    this->prefixInformation = prefixInformation2;
    prefixInformation_arraysize = newSize;
}

void Ipv6RouterAdvertisement::setPrefixInformation(size_t k, const Ipv6NdPrefixInformation& prefixInformation)
{
    if (k >= prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->prefixInformation[k] = prefixInformation;
}

void Ipv6RouterAdvertisement::insertPrefixInformation(size_t k, const Ipv6NdPrefixInformation& prefixInformation)
{
    handleChange();
    if (k > prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = prefixInformation_arraysize + 1;
    Ipv6NdPrefixInformation *prefixInformation2 = new Ipv6NdPrefixInformation[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixInformation2[i] = this->prefixInformation[i];
    prefixInformation2[k] = prefixInformation;
    for (i = k + 1; i < newSize; i++)
        prefixInformation2[i] = this->prefixInformation[i-1];
    delete [] this->prefixInformation;
    this->prefixInformation = prefixInformation2;
    prefixInformation_arraysize = newSize;
}

void Ipv6RouterAdvertisement::insertPrefixInformation(const Ipv6NdPrefixInformation& prefixInformation)
{
    insertPrefixInformation(prefixInformation_arraysize, prefixInformation);
}

void Ipv6RouterAdvertisement::erasePrefixInformation(size_t k)
{
    if (k >= prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = prefixInformation_arraysize - 1;
    Ipv6NdPrefixInformation *prefixInformation2 = (newSize == 0) ? nullptr : new Ipv6NdPrefixInformation[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixInformation2[i] = this->prefixInformation[i];
    for (i = k; i < newSize; i++)
        prefixInformation2[i] = this->prefixInformation[i+1];
    delete [] this->prefixInformation;
    this->prefixInformation = prefixInformation2;
    prefixInformation_arraysize = newSize;
}

const Mipv6NdAdvertisementInterval& Ipv6RouterAdvertisement::getAdvInterval() const
{
    return this->advInterval;
}

void Ipv6RouterAdvertisement::setAdvInterval(const Mipv6NdAdvertisementInterval& advInterval)
{
    handleChange();
    this->advInterval = advInterval;
}

const Mipv6HaInformation& Ipv6RouterAdvertisement::getHaInformation() const
{
    return this->haInformation;
}

void Ipv6RouterAdvertisement::setHaInformation(const Mipv6HaInformation& haInformation)
{
    handleChange();
    this->haInformation = haInformation;
}

const Ipv6Address& Ipv6RouterAdvertisement::getSrcGlobalAddress() const
{
    return this->srcGlobalAddress;
}

void Ipv6RouterAdvertisement::setSrcGlobalAddress(const Ipv6Address& srcGlobalAddress)
{
    handleChange();
    this->srcGlobalAddress = srcGlobalAddress;
}

bool Ipv6RouterAdvertisement::isDadRequired() const
{
    return this->isDadRequired_;
}

void Ipv6RouterAdvertisement::setIsDadRequired(bool isDadRequired)
{
    handleChange();
    this->isDadRequired_ = isDadRequired;
}

class Ipv6RouterAdvertisementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_curHopLimit,
        FIELD_managedAddrConfFlag,
        FIELD_otherStatefulConfFlag,
        FIELD_homeAgentFlag,
        FIELD_routerLifetime,
        FIELD_reachableTime,
        FIELD_retransTimer,
        FIELD_sourceLinkLayerAddress,
        FIELD_MTU,
        FIELD_prefixInformation,
        FIELD_advInterval,
        FIELD_haInformation,
        FIELD_srcGlobalAddress,
        FIELD_isDadRequired,
    };
  public:
    Ipv6RouterAdvertisementDescriptor();
    virtual ~Ipv6RouterAdvertisementDescriptor();

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

Register_ClassDescriptor(Ipv6RouterAdvertisementDescriptor)

Ipv6RouterAdvertisementDescriptor::Ipv6RouterAdvertisementDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6RouterAdvertisement)), "inet::Ipv6NdMessage")
{
    propertynames = nullptr;
}

Ipv6RouterAdvertisementDescriptor::~Ipv6RouterAdvertisementDescriptor()
{
    delete[] propertynames;
}

bool Ipv6RouterAdvertisementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6RouterAdvertisement *>(obj)!=nullptr;
}

const char **Ipv6RouterAdvertisementDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6RouterAdvertisementDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6RouterAdvertisementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount() : 14;
}

unsigned int Ipv6RouterAdvertisementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_curHopLimit
        FD_ISEDITABLE,    // FIELD_managedAddrConfFlag
        FD_ISEDITABLE,    // FIELD_otherStatefulConfFlag
        FD_ISEDITABLE,    // FIELD_homeAgentFlag
        FD_ISEDITABLE,    // FIELD_routerLifetime
        FD_ISEDITABLE,    // FIELD_reachableTime
        FD_ISEDITABLE,    // FIELD_retransTimer
        0,    // FIELD_sourceLinkLayerAddress
        FD_ISEDITABLE,    // FIELD_MTU
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_prefixInformation
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_advInterval
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_haInformation
        0,    // FIELD_srcGlobalAddress
        FD_ISEDITABLE,    // FIELD_isDadRequired
    };
    return (field >= 0 && field < 14) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "curHopLimit",
        "managedAddrConfFlag",
        "otherStatefulConfFlag",
        "homeAgentFlag",
        "routerLifetime",
        "reachableTime",
        "retransTimer",
        "sourceLinkLayerAddress",
        "MTU",
        "prefixInformation",
        "advInterval",
        "haInformation",
        "srcGlobalAddress",
        "isDadRequired",
    };
    return (field >= 0 && field < 14) ? fieldNames[field] : nullptr;
}

int Ipv6RouterAdvertisementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'c' && strcmp(fieldName, "curHopLimit") == 0) return base+0;
    if (fieldName[0] == 'm' && strcmp(fieldName, "managedAddrConfFlag") == 0) return base+1;
    if (fieldName[0] == 'o' && strcmp(fieldName, "otherStatefulConfFlag") == 0) return base+2;
    if (fieldName[0] == 'h' && strcmp(fieldName, "homeAgentFlag") == 0) return base+3;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routerLifetime") == 0) return base+4;
    if (fieldName[0] == 'r' && strcmp(fieldName, "reachableTime") == 0) return base+5;
    if (fieldName[0] == 'r' && strcmp(fieldName, "retransTimer") == 0) return base+6;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceLinkLayerAddress") == 0) return base+7;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MTU") == 0) return base+8;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefixInformation") == 0) return base+9;
    if (fieldName[0] == 'a' && strcmp(fieldName, "advInterval") == 0) return base+10;
    if (fieldName[0] == 'h' && strcmp(fieldName, "haInformation") == 0) return base+11;
    if (fieldName[0] == 's' && strcmp(fieldName, "srcGlobalAddress") == 0) return base+12;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isDadRequired") == 0) return base+13;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",    // FIELD_curHopLimit
        "bool",    // FIELD_managedAddrConfFlag
        "bool",    // FIELD_otherStatefulConfFlag
        "bool",    // FIELD_homeAgentFlag
        "unsigned short",    // FIELD_routerLifetime
        "unsigned int",    // FIELD_reachableTime
        "unsigned int",    // FIELD_retransTimer
        "inet::MacAddress",    // FIELD_sourceLinkLayerAddress
        "unsigned int",    // FIELD_MTU
        "inet::Ipv6NdPrefixInformation",    // FIELD_prefixInformation
        "inet::Mipv6NdAdvertisementInterval",    // FIELD_advInterval
        "inet::Mipv6HaInformation",    // FIELD_haInformation
        "inet::Ipv6Address",    // FIELD_srcGlobalAddress
        "bool",    // FIELD_isDadRequired
    };
    return (field >= 0 && field < 14) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6RouterAdvertisementDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6RouterAdvertisementDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6RouterAdvertisementDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = (Ipv6RouterAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_prefixInformation: return pp->getPrefixInformationArraySize();
        default: return 0;
    }
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = (Ipv6RouterAdvertisement *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6RouterAdvertisementDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = (Ipv6RouterAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_curHopLimit: return ulong2string(pp->getCurHopLimit());
        case FIELD_managedAddrConfFlag: return bool2string(pp->getManagedAddrConfFlag());
        case FIELD_otherStatefulConfFlag: return bool2string(pp->getOtherStatefulConfFlag());
        case FIELD_homeAgentFlag: return bool2string(pp->getHomeAgentFlag());
        case FIELD_routerLifetime: return ulong2string(pp->getRouterLifetime());
        case FIELD_reachableTime: return ulong2string(pp->getReachableTime());
        case FIELD_retransTimer: return ulong2string(pp->getRetransTimer());
        case FIELD_sourceLinkLayerAddress: return pp->getSourceLinkLayerAddress().str();
        case FIELD_MTU: return ulong2string(pp->getMTU());
        case FIELD_prefixInformation: {std::stringstream out; out << pp->getPrefixInformation(i); return out.str();}
        case FIELD_advInterval: {std::stringstream out; out << pp->getAdvInterval(); return out.str();}
        case FIELD_haInformation: {std::stringstream out; out << pp->getHaInformation(); return out.str();}
        case FIELD_srcGlobalAddress: return pp->getSrcGlobalAddress().str();
        case FIELD_isDadRequired: return bool2string(pp->isDadRequired());
        default: return "";
    }
}

bool Ipv6RouterAdvertisementDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = (Ipv6RouterAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_curHopLimit: pp->setCurHopLimit(string2ulong(value)); return true;
        case FIELD_managedAddrConfFlag: pp->setManagedAddrConfFlag(string2bool(value)); return true;
        case FIELD_otherStatefulConfFlag: pp->setOtherStatefulConfFlag(string2bool(value)); return true;
        case FIELD_homeAgentFlag: pp->setHomeAgentFlag(string2bool(value)); return true;
        case FIELD_routerLifetime: pp->setRouterLifetime(string2ulong(value)); return true;
        case FIELD_reachableTime: pp->setReachableTime(string2ulong(value)); return true;
        case FIELD_retransTimer: pp->setRetransTimer(string2ulong(value)); return true;
        case FIELD_MTU: pp->setMTU(string2ulong(value)); return true;
        case FIELD_isDadRequired: pp->setIsDadRequired(string2bool(value)); return true;
        default: return false;
    }
}

const char *Ipv6RouterAdvertisementDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_prefixInformation: return omnetpp::opp_typename(typeid(Ipv6NdPrefixInformation));
        case FIELD_advInterval: return omnetpp::opp_typename(typeid(Mipv6NdAdvertisementInterval));
        case FIELD_haInformation: return omnetpp::opp_typename(typeid(Mipv6HaInformation));
        default: return nullptr;
    };
}

void *Ipv6RouterAdvertisementDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6RouterAdvertisement *pp = (Ipv6RouterAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_sourceLinkLayerAddress: return toVoidPtr(&pp->getSourceLinkLayerAddress()); break;
        case FIELD_prefixInformation: return toVoidPtr(&pp->getPrefixInformation(i)); break;
        case FIELD_advInterval: return toVoidPtr(&pp->getAdvInterval()); break;
        case FIELD_haInformation: return toVoidPtr(&pp->getHaInformation()); break;
        case FIELD_srcGlobalAddress: return toVoidPtr(&pp->getSrcGlobalAddress()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6NeighbourSolicitation)

Ipv6NeighbourSolicitation::Ipv6NeighbourSolicitation() : ::inet::Ipv6NdMessage()
{
    this->setType(ICMPv6_NEIGHBOUR_SOL);

}

Ipv6NeighbourSolicitation::Ipv6NeighbourSolicitation(const Ipv6NeighbourSolicitation& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6NeighbourSolicitation::~Ipv6NeighbourSolicitation()
{
}

Ipv6NeighbourSolicitation& Ipv6NeighbourSolicitation::operator=(const Ipv6NeighbourSolicitation& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NeighbourSolicitation::copy(const Ipv6NeighbourSolicitation& other)
{
    this->targetAddress = other.targetAddress;
    this->sourceLinkLayerAddress = other.sourceLinkLayerAddress;
    this->ARO = other.ARO;
    this->isDadMsg_ = other.isDadMsg_;
    this->isRelay_ = other.isRelay_;
    this->relayAddress = other.relayAddress;
    this->linkLocalAddress = other.linkLocalAddress;
    this->hopDistance = other.hopDistance;
}

void Ipv6NeighbourSolicitation::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->targetAddress);
    doParsimPacking(b,this->sourceLinkLayerAddress);
    doParsimPacking(b,this->ARO);
    doParsimPacking(b,this->isDadMsg_);
    doParsimPacking(b,this->isRelay_);
    doParsimPacking(b,this->relayAddress);
    doParsimPacking(b,this->linkLocalAddress);
    doParsimPacking(b,this->hopDistance);
}

void Ipv6NeighbourSolicitation::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->targetAddress);
    doParsimUnpacking(b,this->sourceLinkLayerAddress);
    doParsimUnpacking(b,this->ARO);
    doParsimUnpacking(b,this->isDadMsg_);
    doParsimUnpacking(b,this->isRelay_);
    doParsimUnpacking(b,this->relayAddress);
    doParsimUnpacking(b,this->linkLocalAddress);
    doParsimUnpacking(b,this->hopDistance);
}

const Ipv6Address& Ipv6NeighbourSolicitation::getTargetAddress() const
{
    return this->targetAddress;
}

void Ipv6NeighbourSolicitation::setTargetAddress(const Ipv6Address& targetAddress)
{
    handleChange();
    this->targetAddress = targetAddress;
}

const MacAddress& Ipv6NeighbourSolicitation::getSourceLinkLayerAddress() const
{
    return this->sourceLinkLayerAddress;
}

void Ipv6NeighbourSolicitation::setSourceLinkLayerAddress(const MacAddress& sourceLinkLayerAddress)
{
    handleChange();
    this->sourceLinkLayerAddress = sourceLinkLayerAddress;
}

const Ipv6NdAddressRegistrationOption& Ipv6NeighbourSolicitation::getARO() const
{
    return this->ARO;
}

void Ipv6NeighbourSolicitation::setARO(const Ipv6NdAddressRegistrationOption& ARO)
{
    handleChange();
    this->ARO = ARO;
}

bool Ipv6NeighbourSolicitation::isDadMsg() const
{
    return this->isDadMsg_;
}

void Ipv6NeighbourSolicitation::setIsDadMsg(bool isDadMsg)
{
    handleChange();
    this->isDadMsg_ = isDadMsg;
}

bool Ipv6NeighbourSolicitation::isRelay() const
{
    return this->isRelay_;
}

void Ipv6NeighbourSolicitation::setIsRelay(bool isRelay)
{
    handleChange();
    this->isRelay_ = isRelay;
}

const Ipv6Address& Ipv6NeighbourSolicitation::getRelayAddress() const
{
    return this->relayAddress;
}

void Ipv6NeighbourSolicitation::setRelayAddress(const Ipv6Address& relayAddress)
{
    handleChange();
    this->relayAddress = relayAddress;
}

const Ipv6Address& Ipv6NeighbourSolicitation::getLinkLocalAddress() const
{
    return this->linkLocalAddress;
}

void Ipv6NeighbourSolicitation::setLinkLocalAddress(const Ipv6Address& linkLocalAddress)
{
    handleChange();
    this->linkLocalAddress = linkLocalAddress;
}

int Ipv6NeighbourSolicitation::getHopDistance() const
{
    return this->hopDistance;
}

void Ipv6NeighbourSolicitation::setHopDistance(int hopDistance)
{
    handleChange();
    this->hopDistance = hopDistance;
}

class Ipv6NeighbourSolicitationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_targetAddress,
        FIELD_sourceLinkLayerAddress,
        FIELD_ARO,
        FIELD_isDadMsg,
        FIELD_isRelay,
        FIELD_relayAddress,
        FIELD_linkLocalAddress,
        FIELD_hopDistance,
    };
  public:
    Ipv6NeighbourSolicitationDescriptor();
    virtual ~Ipv6NeighbourSolicitationDescriptor();

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

Register_ClassDescriptor(Ipv6NeighbourSolicitationDescriptor)

Ipv6NeighbourSolicitationDescriptor::Ipv6NeighbourSolicitationDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NeighbourSolicitation)), "inet::Ipv6NdMessage")
{
    propertynames = nullptr;
}

Ipv6NeighbourSolicitationDescriptor::~Ipv6NeighbourSolicitationDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NeighbourSolicitationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NeighbourSolicitation *>(obj)!=nullptr;
}

const char **Ipv6NeighbourSolicitationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NeighbourSolicitationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NeighbourSolicitationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int Ipv6NeighbourSolicitationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_targetAddress
        0,    // FIELD_sourceLinkLayerAddress
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_ARO
        FD_ISEDITABLE,    // FIELD_isDadMsg
        FD_ISEDITABLE,    // FIELD_isRelay
        0,    // FIELD_relayAddress
        0,    // FIELD_linkLocalAddress
        FD_ISEDITABLE,    // FIELD_hopDistance
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "targetAddress",
        "sourceLinkLayerAddress",
        "ARO",
        "isDadMsg",
        "isRelay",
        "relayAddress",
        "linkLocalAddress",
        "hopDistance",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int Ipv6NeighbourSolicitationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "targetAddress") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceLinkLayerAddress") == 0) return base+1;
    if (fieldName[0] == 'A' && strcmp(fieldName, "ARO") == 0) return base+2;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isDadMsg") == 0) return base+3;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isRelay") == 0) return base+4;
    if (fieldName[0] == 'r' && strcmp(fieldName, "relayAddress") == 0) return base+5;
    if (fieldName[0] == 'l' && strcmp(fieldName, "linkLocalAddress") == 0) return base+6;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopDistance") == 0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_targetAddress
        "inet::MacAddress",    // FIELD_sourceLinkLayerAddress
        "inet::Ipv6NdAddressRegistrationOption",    // FIELD_ARO
        "bool",    // FIELD_isDadMsg
        "bool",    // FIELD_isRelay
        "inet::Ipv6Address",    // FIELD_relayAddress
        "inet::Ipv6Address",    // FIELD_linkLocalAddress
        "int",    // FIELD_hopDistance
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NeighbourSolicitationDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NeighbourSolicitationDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NeighbourSolicitationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = (Ipv6NeighbourSolicitation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = (Ipv6NeighbourSolicitation *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NeighbourSolicitationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = (Ipv6NeighbourSolicitation *)object; (void)pp;
    switch (field) {
        case FIELD_targetAddress: return pp->getTargetAddress().str();
        case FIELD_sourceLinkLayerAddress: return pp->getSourceLinkLayerAddress().str();
        case FIELD_ARO: {std::stringstream out; out << pp->getARO(); return out.str();}
        case FIELD_isDadMsg: return bool2string(pp->isDadMsg());
        case FIELD_isRelay: return bool2string(pp->isRelay());
        case FIELD_relayAddress: return pp->getRelayAddress().str();
        case FIELD_linkLocalAddress: return pp->getLinkLocalAddress().str();
        case FIELD_hopDistance: return long2string(pp->getHopDistance());
        default: return "";
    }
}

bool Ipv6NeighbourSolicitationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = (Ipv6NeighbourSolicitation *)object; (void)pp;
    switch (field) {
        case FIELD_isDadMsg: pp->setIsDadMsg(string2bool(value)); return true;
        case FIELD_isRelay: pp->setIsRelay(string2bool(value)); return true;
        case FIELD_hopDistance: pp->setHopDistance(string2long(value)); return true;
        default: return false;
    }
}

const char *Ipv6NeighbourSolicitationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_ARO: return omnetpp::opp_typename(typeid(Ipv6NdAddressRegistrationOption));
        default: return nullptr;
    };
}

void *Ipv6NeighbourSolicitationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourSolicitation *pp = (Ipv6NeighbourSolicitation *)object; (void)pp;
    switch (field) {
        case FIELD_targetAddress: return toVoidPtr(&pp->getTargetAddress()); break;
        case FIELD_sourceLinkLayerAddress: return toVoidPtr(&pp->getSourceLinkLayerAddress()); break;
        case FIELD_ARO: return toVoidPtr(&pp->getARO()); break;
        case FIELD_relayAddress: return toVoidPtr(&pp->getRelayAddress()); break;
        case FIELD_linkLocalAddress: return toVoidPtr(&pp->getLinkLocalAddress()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6NeighbourAdvertisement)

Ipv6NeighbourAdvertisement::Ipv6NeighbourAdvertisement() : ::inet::Ipv6NdMessage()
{
    this->setType(ICMPv6_NEIGHBOUR_AD);

}

Ipv6NeighbourAdvertisement::Ipv6NeighbourAdvertisement(const Ipv6NeighbourAdvertisement& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6NeighbourAdvertisement::~Ipv6NeighbourAdvertisement()
{
    delete [] this->prefixInformation;
}

Ipv6NeighbourAdvertisement& Ipv6NeighbourAdvertisement::operator=(const Ipv6NeighbourAdvertisement& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NeighbourAdvertisement::copy(const Ipv6NeighbourAdvertisement& other)
{
    this->routerFlag = other.routerFlag;
    this->solicitedFlag = other.solicitedFlag;
    this->overrideFlag = other.overrideFlag;
    this->targetAddress = other.targetAddress;
    this->targetLinkLayerAddress = other.targetLinkLayerAddress;
    this->sourceLinkLayerAddress = other.sourceLinkLayerAddress;
    this->ARO = other.ARO;
    delete [] this->prefixInformation;
    this->prefixInformation = (other.prefixInformation_arraysize==0) ? nullptr : new Ipv6NdPrefixInformation[other.prefixInformation_arraysize];
    prefixInformation_arraysize = other.prefixInformation_arraysize;
    for (size_t i = 0; i < prefixInformation_arraysize; i++) {
        this->prefixInformation[i] = other.prefixInformation[i];
    }
    this->routerAddress = other.routerAddress;
}

void Ipv6NeighbourAdvertisement::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->routerFlag);
    doParsimPacking(b,this->solicitedFlag);
    doParsimPacking(b,this->overrideFlag);
    doParsimPacking(b,this->targetAddress);
    doParsimPacking(b,this->targetLinkLayerAddress);
    doParsimPacking(b,this->sourceLinkLayerAddress);
    doParsimPacking(b,this->ARO);
    b->pack(prefixInformation_arraysize);
    doParsimArrayPacking(b,this->prefixInformation,prefixInformation_arraysize);
    doParsimPacking(b,this->routerAddress);
}

void Ipv6NeighbourAdvertisement::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->routerFlag);
    doParsimUnpacking(b,this->solicitedFlag);
    doParsimUnpacking(b,this->overrideFlag);
    doParsimUnpacking(b,this->targetAddress);
    doParsimUnpacking(b,this->targetLinkLayerAddress);
    doParsimUnpacking(b,this->sourceLinkLayerAddress);
    doParsimUnpacking(b,this->ARO);
    delete [] this->prefixInformation;
    b->unpack(prefixInformation_arraysize);
    if (prefixInformation_arraysize == 0) {
        this->prefixInformation = nullptr;
    } else {
        this->prefixInformation = new Ipv6NdPrefixInformation[prefixInformation_arraysize];
        doParsimArrayUnpacking(b,this->prefixInformation,prefixInformation_arraysize);
    }
    doParsimUnpacking(b,this->routerAddress);
}

bool Ipv6NeighbourAdvertisement::getRouterFlag() const
{
    return this->routerFlag;
}

void Ipv6NeighbourAdvertisement::setRouterFlag(bool routerFlag)
{
    handleChange();
    this->routerFlag = routerFlag;
}

bool Ipv6NeighbourAdvertisement::getSolicitedFlag() const
{
    return this->solicitedFlag;
}

void Ipv6NeighbourAdvertisement::setSolicitedFlag(bool solicitedFlag)
{
    handleChange();
    this->solicitedFlag = solicitedFlag;
}

bool Ipv6NeighbourAdvertisement::getOverrideFlag() const
{
    return this->overrideFlag;
}

void Ipv6NeighbourAdvertisement::setOverrideFlag(bool overrideFlag)
{
    handleChange();
    this->overrideFlag = overrideFlag;
}

const Ipv6Address& Ipv6NeighbourAdvertisement::getTargetAddress() const
{
    return this->targetAddress;
}

void Ipv6NeighbourAdvertisement::setTargetAddress(const Ipv6Address& targetAddress)
{
    handleChange();
    this->targetAddress = targetAddress;
}

const MacAddress& Ipv6NeighbourAdvertisement::getTargetLinkLayerAddress() const
{
    return this->targetLinkLayerAddress;
}

void Ipv6NeighbourAdvertisement::setTargetLinkLayerAddress(const MacAddress& targetLinkLayerAddress)
{
    handleChange();
    this->targetLinkLayerAddress = targetLinkLayerAddress;
}

const MacAddress& Ipv6NeighbourAdvertisement::getSourceLinkLayerAddress() const
{
    return this->sourceLinkLayerAddress;
}

void Ipv6NeighbourAdvertisement::setSourceLinkLayerAddress(const MacAddress& sourceLinkLayerAddress)
{
    handleChange();
    this->sourceLinkLayerAddress = sourceLinkLayerAddress;
}

const Ipv6NdAddressRegistrationOption& Ipv6NeighbourAdvertisement::getARO() const
{
    return this->ARO;
}

void Ipv6NeighbourAdvertisement::setARO(const Ipv6NdAddressRegistrationOption& ARO)
{
    handleChange();
    this->ARO = ARO;
}

size_t Ipv6NeighbourAdvertisement::getPrefixInformationArraySize() const
{
    return prefixInformation_arraysize;
}

const Ipv6NdPrefixInformation& Ipv6NeighbourAdvertisement::getPrefixInformation(size_t k) const
{
    if (k >= prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size prefixInformation_arraysize indexed by %lu", (unsigned long)k);
    return this->prefixInformation[k];
}

void Ipv6NeighbourAdvertisement::setPrefixInformationArraySize(size_t newSize)
{
    handleChange();
    Ipv6NdPrefixInformation *prefixInformation2 = (newSize==0) ? nullptr : new Ipv6NdPrefixInformation[newSize];
    size_t minSize = prefixInformation_arraysize < newSize ? prefixInformation_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        prefixInformation2[i] = this->prefixInformation[i];
    delete [] this->prefixInformation;
    this->prefixInformation = prefixInformation2;
    prefixInformation_arraysize = newSize;
}

void Ipv6NeighbourAdvertisement::setPrefixInformation(size_t k, const Ipv6NdPrefixInformation& prefixInformation)
{
    if (k >= prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->prefixInformation[k] = prefixInformation;
}

void Ipv6NeighbourAdvertisement::insertPrefixInformation(size_t k, const Ipv6NdPrefixInformation& prefixInformation)
{
    handleChange();
    if (k > prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = prefixInformation_arraysize + 1;
    Ipv6NdPrefixInformation *prefixInformation2 = new Ipv6NdPrefixInformation[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixInformation2[i] = this->prefixInformation[i];
    prefixInformation2[k] = prefixInformation;
    for (i = k + 1; i < newSize; i++)
        prefixInformation2[i] = this->prefixInformation[i-1];
    delete [] this->prefixInformation;
    this->prefixInformation = prefixInformation2;
    prefixInformation_arraysize = newSize;
}

void Ipv6NeighbourAdvertisement::insertPrefixInformation(const Ipv6NdPrefixInformation& prefixInformation)
{
    insertPrefixInformation(prefixInformation_arraysize, prefixInformation);
}

void Ipv6NeighbourAdvertisement::erasePrefixInformation(size_t k)
{
    if (k >= prefixInformation_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = prefixInformation_arraysize - 1;
    Ipv6NdPrefixInformation *prefixInformation2 = (newSize == 0) ? nullptr : new Ipv6NdPrefixInformation[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        prefixInformation2[i] = this->prefixInformation[i];
    for (i = k; i < newSize; i++)
        prefixInformation2[i] = this->prefixInformation[i+1];
    delete [] this->prefixInformation;
    this->prefixInformation = prefixInformation2;
    prefixInformation_arraysize = newSize;
}

const Ipv6Address& Ipv6NeighbourAdvertisement::getRouterAddress() const
{
    return this->routerAddress;
}

void Ipv6NeighbourAdvertisement::setRouterAddress(const Ipv6Address& routerAddress)
{
    handleChange();
    this->routerAddress = routerAddress;
}

class Ipv6NeighbourAdvertisementDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_routerFlag,
        FIELD_solicitedFlag,
        FIELD_overrideFlag,
        FIELD_targetAddress,
        FIELD_targetLinkLayerAddress,
        FIELD_sourceLinkLayerAddress,
        FIELD_ARO,
        FIELD_prefixInformation,
        FIELD_routerAddress,
    };
  public:
    Ipv6NeighbourAdvertisementDescriptor();
    virtual ~Ipv6NeighbourAdvertisementDescriptor();

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

Register_ClassDescriptor(Ipv6NeighbourAdvertisementDescriptor)

Ipv6NeighbourAdvertisementDescriptor::Ipv6NeighbourAdvertisementDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NeighbourAdvertisement)), "inet::Ipv6NdMessage")
{
    propertynames = nullptr;
}

Ipv6NeighbourAdvertisementDescriptor::~Ipv6NeighbourAdvertisementDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NeighbourAdvertisementDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NeighbourAdvertisement *>(obj)!=nullptr;
}

const char **Ipv6NeighbourAdvertisementDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NeighbourAdvertisementDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NeighbourAdvertisementDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int Ipv6NeighbourAdvertisementDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_routerFlag
        FD_ISEDITABLE,    // FIELD_solicitedFlag
        FD_ISEDITABLE,    // FIELD_overrideFlag
        0,    // FIELD_targetAddress
        0,    // FIELD_targetLinkLayerAddress
        0,    // FIELD_sourceLinkLayerAddress
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_ARO
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_prefixInformation
        0,    // FIELD_routerAddress
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routerFlag",
        "solicitedFlag",
        "overrideFlag",
        "targetAddress",
        "targetLinkLayerAddress",
        "sourceLinkLayerAddress",
        "ARO",
        "prefixInformation",
        "routerAddress",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int Ipv6NeighbourAdvertisementDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routerFlag") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "solicitedFlag") == 0) return base+1;
    if (fieldName[0] == 'o' && strcmp(fieldName, "overrideFlag") == 0) return base+2;
    if (fieldName[0] == 't' && strcmp(fieldName, "targetAddress") == 0) return base+3;
    if (fieldName[0] == 't' && strcmp(fieldName, "targetLinkLayerAddress") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceLinkLayerAddress") == 0) return base+5;
    if (fieldName[0] == 'A' && strcmp(fieldName, "ARO") == 0) return base+6;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefixInformation") == 0) return base+7;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routerAddress") == 0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_routerFlag
        "bool",    // FIELD_solicitedFlag
        "bool",    // FIELD_overrideFlag
        "inet::Ipv6Address",    // FIELD_targetAddress
        "inet::MacAddress",    // FIELD_targetLinkLayerAddress
        "inet::MacAddress",    // FIELD_sourceLinkLayerAddress
        "inet::Ipv6NdAddressRegistrationOption",    // FIELD_ARO
        "inet::Ipv6NdPrefixInformation",    // FIELD_prefixInformation
        "inet::Ipv6Address",    // FIELD_routerAddress
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NeighbourAdvertisementDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NeighbourAdvertisementDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = (Ipv6NeighbourAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_prefixInformation: return pp->getPrefixInformationArraySize();
        default: return 0;
    }
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = (Ipv6NeighbourAdvertisement *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NeighbourAdvertisementDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = (Ipv6NeighbourAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_routerFlag: return bool2string(pp->getRouterFlag());
        case FIELD_solicitedFlag: return bool2string(pp->getSolicitedFlag());
        case FIELD_overrideFlag: return bool2string(pp->getOverrideFlag());
        case FIELD_targetAddress: return pp->getTargetAddress().str();
        case FIELD_targetLinkLayerAddress: return pp->getTargetLinkLayerAddress().str();
        case FIELD_sourceLinkLayerAddress: return pp->getSourceLinkLayerAddress().str();
        case FIELD_ARO: {std::stringstream out; out << pp->getARO(); return out.str();}
        case FIELD_prefixInformation: {std::stringstream out; out << pp->getPrefixInformation(i); return out.str();}
        case FIELD_routerAddress: return pp->getRouterAddress().str();
        default: return "";
    }
}

bool Ipv6NeighbourAdvertisementDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = (Ipv6NeighbourAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_routerFlag: pp->setRouterFlag(string2bool(value)); return true;
        case FIELD_solicitedFlag: pp->setSolicitedFlag(string2bool(value)); return true;
        case FIELD_overrideFlag: pp->setOverrideFlag(string2bool(value)); return true;
        default: return false;
    }
}

const char *Ipv6NeighbourAdvertisementDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_ARO: return omnetpp::opp_typename(typeid(Ipv6NdAddressRegistrationOption));
        case FIELD_prefixInformation: return omnetpp::opp_typename(typeid(Ipv6NdPrefixInformation));
        default: return nullptr;
    };
}

void *Ipv6NeighbourAdvertisementDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NeighbourAdvertisement *pp = (Ipv6NeighbourAdvertisement *)object; (void)pp;
    switch (field) {
        case FIELD_targetAddress: return toVoidPtr(&pp->getTargetAddress()); break;
        case FIELD_targetLinkLayerAddress: return toVoidPtr(&pp->getTargetLinkLayerAddress()); break;
        case FIELD_sourceLinkLayerAddress: return toVoidPtr(&pp->getSourceLinkLayerAddress()); break;
        case FIELD_ARO: return toVoidPtr(&pp->getARO()); break;
        case FIELD_prefixInformation: return toVoidPtr(&pp->getPrefixInformation(i)); break;
        case FIELD_routerAddress: return toVoidPtr(&pp->getRouterAddress()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6Redirect)

Ipv6Redirect::Ipv6Redirect() : ::inet::Ipv6NdMessage()
{
    this->setType(ICMPv6_REDIRECT);

}

Ipv6Redirect::Ipv6Redirect(const Ipv6Redirect& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6Redirect::~Ipv6Redirect()
{
}

Ipv6Redirect& Ipv6Redirect::operator=(const Ipv6Redirect& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6Redirect::copy(const Ipv6Redirect& other)
{
    this->targetAddress = other.targetAddress;
    this->destinationAddress = other.destinationAddress;
    this->targetLinkLayerAddress = other.targetLinkLayerAddress;
}

void Ipv6Redirect::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->targetAddress);
    doParsimPacking(b,this->destinationAddress);
    doParsimPacking(b,this->targetLinkLayerAddress);
}

void Ipv6Redirect::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->targetAddress);
    doParsimUnpacking(b,this->destinationAddress);
    doParsimUnpacking(b,this->targetLinkLayerAddress);
}

const Ipv6Address& Ipv6Redirect::getTargetAddress() const
{
    return this->targetAddress;
}

void Ipv6Redirect::setTargetAddress(const Ipv6Address& targetAddress)
{
    handleChange();
    this->targetAddress = targetAddress;
}

const Ipv6Address& Ipv6Redirect::getDestinationAddress() const
{
    return this->destinationAddress;
}

void Ipv6Redirect::setDestinationAddress(const Ipv6Address& destinationAddress)
{
    handleChange();
    this->destinationAddress = destinationAddress;
}

const MacAddress& Ipv6Redirect::getTargetLinkLayerAddress() const
{
    return this->targetLinkLayerAddress;
}

void Ipv6Redirect::setTargetLinkLayerAddress(const MacAddress& targetLinkLayerAddress)
{
    handleChange();
    this->targetLinkLayerAddress = targetLinkLayerAddress;
}

class Ipv6RedirectDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_targetAddress,
        FIELD_destinationAddress,
        FIELD_targetLinkLayerAddress,
    };
  public:
    Ipv6RedirectDescriptor();
    virtual ~Ipv6RedirectDescriptor();

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

Register_ClassDescriptor(Ipv6RedirectDescriptor)

Ipv6RedirectDescriptor::Ipv6RedirectDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6Redirect)), "inet::Ipv6NdMessage")
{
    propertynames = nullptr;
}

Ipv6RedirectDescriptor::~Ipv6RedirectDescriptor()
{
    delete[] propertynames;
}

bool Ipv6RedirectDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6Redirect *>(obj)!=nullptr;
}

const char **Ipv6RedirectDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6RedirectDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6RedirectDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int Ipv6RedirectDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_targetAddress
        0,    // FIELD_destinationAddress
        0,    // FIELD_targetLinkLayerAddress
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6RedirectDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "targetAddress",
        "destinationAddress",
        "targetLinkLayerAddress",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ipv6RedirectDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 't' && strcmp(fieldName, "targetAddress") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destinationAddress") == 0) return base+1;
    if (fieldName[0] == 't' && strcmp(fieldName, "targetLinkLayerAddress") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6RedirectDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_targetAddress
        "inet::Ipv6Address",    // FIELD_destinationAddress
        "inet::MacAddress",    // FIELD_targetLinkLayerAddress
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6RedirectDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6RedirectDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6RedirectDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6Redirect *pp = (Ipv6Redirect *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6RedirectDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6Redirect *pp = (Ipv6Redirect *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6RedirectDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6Redirect *pp = (Ipv6Redirect *)object; (void)pp;
    switch (field) {
        case FIELD_targetAddress: return pp->getTargetAddress().str();
        case FIELD_destinationAddress: return pp->getDestinationAddress().str();
        case FIELD_targetLinkLayerAddress: return pp->getTargetLinkLayerAddress().str();
        default: return "";
    }
}

bool Ipv6RedirectDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6Redirect *pp = (Ipv6Redirect *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *Ipv6RedirectDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6RedirectDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6Redirect *pp = (Ipv6Redirect *)object; (void)pp;
    switch (field) {
        case FIELD_targetAddress: return toVoidPtr(&pp->getTargetAddress()); break;
        case FIELD_destinationAddress: return toVoidPtr(&pp->getDestinationAddress()); break;
        case FIELD_targetLinkLayerAddress: return toVoidPtr(&pp->getTargetLinkLayerAddress()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6DuplicateAddrReq)

Ipv6DuplicateAddrReq::Ipv6DuplicateAddrReq() : ::inet::Ipv6NdMessage()
{
    this->setType(ICMPv6_NEIGHBOUR_DAR);

}

Ipv6DuplicateAddrReq::Ipv6DuplicateAddrReq(const Ipv6DuplicateAddrReq& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6DuplicateAddrReq::~Ipv6DuplicateAddrReq()
{
}

Ipv6DuplicateAddrReq& Ipv6DuplicateAddrReq::operator=(const Ipv6DuplicateAddrReq& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6DuplicateAddrReq::copy(const Ipv6DuplicateAddrReq& other)
{
    this->sourceAddress = other.sourceAddress;
    this->destinationAddress = other.destinationAddress;
    this->curHopLimit = other.curHopLimit;
    this->registeredAddress = other.registeredAddress;
    this->registLifetime = other.registLifetime;
    this->status = other.status;
    this->EUI64 = other.EUI64;
}

void Ipv6DuplicateAddrReq::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->sourceAddress);
    doParsimPacking(b,this->destinationAddress);
    doParsimPacking(b,this->curHopLimit);
    doParsimPacking(b,this->registeredAddress);
    doParsimPacking(b,this->registLifetime);
    doParsimPacking(b,this->status);
    doParsimPacking(b,this->EUI64);
}

void Ipv6DuplicateAddrReq::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceAddress);
    doParsimUnpacking(b,this->destinationAddress);
    doParsimUnpacking(b,this->curHopLimit);
    doParsimUnpacking(b,this->registeredAddress);
    doParsimUnpacking(b,this->registLifetime);
    doParsimUnpacking(b,this->status);
    doParsimUnpacking(b,this->EUI64);
}

const Ipv6Address& Ipv6DuplicateAddrReq::getSourceAddress() const
{
    return this->sourceAddress;
}

void Ipv6DuplicateAddrReq::setSourceAddress(const Ipv6Address& sourceAddress)
{
    handleChange();
    this->sourceAddress = sourceAddress;
}

const Ipv6Address& Ipv6DuplicateAddrReq::getDestinationAddress() const
{
    return this->destinationAddress;
}

void Ipv6DuplicateAddrReq::setDestinationAddress(const Ipv6Address& destinationAddress)
{
    handleChange();
    this->destinationAddress = destinationAddress;
}

unsigned short Ipv6DuplicateAddrReq::getCurHopLimit() const
{
    return this->curHopLimit;
}

void Ipv6DuplicateAddrReq::setCurHopLimit(unsigned short curHopLimit)
{
    handleChange();
    this->curHopLimit = curHopLimit;
}

const Ipv6Address& Ipv6DuplicateAddrReq::getRegisteredAddress() const
{
    return this->registeredAddress;
}

void Ipv6DuplicateAddrReq::setRegisteredAddress(const Ipv6Address& registeredAddress)
{
    handleChange();
    this->registeredAddress = registeredAddress;
}

unsigned short Ipv6DuplicateAddrReq::getRegistLifetime() const
{
    return this->registLifetime;
}

void Ipv6DuplicateAddrReq::setRegistLifetime(unsigned short registLifetime)
{
    handleChange();
    this->registLifetime = registLifetime;
}

unsigned int Ipv6DuplicateAddrReq::getStatus() const
{
    return this->status;
}

void Ipv6DuplicateAddrReq::setStatus(unsigned int status)
{
    handleChange();
    this->status = status;
}

const InterfaceIdentifier& Ipv6DuplicateAddrReq::getEUI64() const
{
    return this->EUI64;
}

void Ipv6DuplicateAddrReq::setEUI64(const InterfaceIdentifier& EUI64)
{
    handleChange();
    this->EUI64 = EUI64;
}

class Ipv6DuplicateAddrReqDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_sourceAddress,
        FIELD_destinationAddress,
        FIELD_curHopLimit,
        FIELD_registeredAddress,
        FIELD_registLifetime,
        FIELD_status,
        FIELD_EUI64,
    };
  public:
    Ipv6DuplicateAddrReqDescriptor();
    virtual ~Ipv6DuplicateAddrReqDescriptor();

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

Register_ClassDescriptor(Ipv6DuplicateAddrReqDescriptor)

Ipv6DuplicateAddrReqDescriptor::Ipv6DuplicateAddrReqDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6DuplicateAddrReq)), "inet::Ipv6NdMessage")
{
    propertynames = nullptr;
}

Ipv6DuplicateAddrReqDescriptor::~Ipv6DuplicateAddrReqDescriptor()
{
    delete[] propertynames;
}

bool Ipv6DuplicateAddrReqDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6DuplicateAddrReq *>(obj)!=nullptr;
}

const char **Ipv6DuplicateAddrReqDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6DuplicateAddrReqDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6DuplicateAddrReqDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int Ipv6DuplicateAddrReqDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_sourceAddress
        0,    // FIELD_destinationAddress
        FD_ISEDITABLE,    // FIELD_curHopLimit
        0,    // FIELD_registeredAddress
        FD_ISEDITABLE,    // FIELD_registLifetime
        FD_ISEDITABLE,    // FIELD_status
        FD_ISCOMPOUND,    // FIELD_EUI64
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6DuplicateAddrReqDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceAddress",
        "destinationAddress",
        "curHopLimit",
        "registeredAddress",
        "registLifetime",
        "status",
        "EUI64",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int Ipv6DuplicateAddrReqDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddress") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destinationAddress") == 0) return base+1;
    if (fieldName[0] == 'c' && strcmp(fieldName, "curHopLimit") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "registeredAddress") == 0) return base+3;
    if (fieldName[0] == 'r' && strcmp(fieldName, "registLifetime") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "status") == 0) return base+5;
    if (fieldName[0] == 'E' && strcmp(fieldName, "EUI64") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6DuplicateAddrReqDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_sourceAddress
        "inet::Ipv6Address",    // FIELD_destinationAddress
        "unsigned short",    // FIELD_curHopLimit
        "inet::Ipv6Address",    // FIELD_registeredAddress
        "unsigned short",    // FIELD_registLifetime
        "unsigned int",    // FIELD_status
        "inet::InterfaceIdentifier",    // FIELD_EUI64
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6DuplicateAddrReqDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6DuplicateAddrReqDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6DuplicateAddrReqDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrReq *pp = (Ipv6DuplicateAddrReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6DuplicateAddrReqDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrReq *pp = (Ipv6DuplicateAddrReq *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6DuplicateAddrReqDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrReq *pp = (Ipv6DuplicateAddrReq *)object; (void)pp;
    switch (field) {
        case FIELD_sourceAddress: return pp->getSourceAddress().str();
        case FIELD_destinationAddress: return pp->getDestinationAddress().str();
        case FIELD_curHopLimit: return ulong2string(pp->getCurHopLimit());
        case FIELD_registeredAddress: return pp->getRegisteredAddress().str();
        case FIELD_registLifetime: return ulong2string(pp->getRegistLifetime());
        case FIELD_status: return ulong2string(pp->getStatus());
        case FIELD_EUI64: {std::stringstream out; out << pp->getEUI64(); return out.str();}
        default: return "";
    }
}

bool Ipv6DuplicateAddrReqDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrReq *pp = (Ipv6DuplicateAddrReq *)object; (void)pp;
    switch (field) {
        case FIELD_curHopLimit: pp->setCurHopLimit(string2ulong(value)); return true;
        case FIELD_registLifetime: pp->setRegistLifetime(string2ulong(value)); return true;
        case FIELD_status: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Ipv6DuplicateAddrReqDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_EUI64: return omnetpp::opp_typename(typeid(InterfaceIdentifier));
        default: return nullptr;
    };
}

void *Ipv6DuplicateAddrReqDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrReq *pp = (Ipv6DuplicateAddrReq *)object; (void)pp;
    switch (field) {
        case FIELD_sourceAddress: return toVoidPtr(&pp->getSourceAddress()); break;
        case FIELD_destinationAddress: return toVoidPtr(&pp->getDestinationAddress()); break;
        case FIELD_registeredAddress: return toVoidPtr(&pp->getRegisteredAddress()); break;
        case FIELD_EUI64: return toVoidPtr(&pp->getEUI64()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6DuplicateAddrConfirm)

Ipv6DuplicateAddrConfirm::Ipv6DuplicateAddrConfirm() : ::inet::Ipv6NdMessage()
{
    this->setType(ICMPv6_NEIGHBOUR_DAC);

}

Ipv6DuplicateAddrConfirm::Ipv6DuplicateAddrConfirm(const Ipv6DuplicateAddrConfirm& other) : ::inet::Ipv6NdMessage(other)
{
    copy(other);
}

Ipv6DuplicateAddrConfirm::~Ipv6DuplicateAddrConfirm()
{
}

Ipv6DuplicateAddrConfirm& Ipv6DuplicateAddrConfirm::operator=(const Ipv6DuplicateAddrConfirm& other)
{
    if (this == &other) return *this;
    ::inet::Ipv6NdMessage::operator=(other);
    copy(other);
    return *this;
}

void Ipv6DuplicateAddrConfirm::copy(const Ipv6DuplicateAddrConfirm& other)
{
    this->sourceAddress = other.sourceAddress;
    this->destinationAddress = other.destinationAddress;
    this->curHopLimit = other.curHopLimit;
    this->registeredAddress = other.registeredAddress;
    this->registLifetime = other.registLifetime;
    this->EUI64 = other.EUI64;
    this->status = other.status;
}

void Ipv6DuplicateAddrConfirm::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::Ipv6NdMessage::parsimPack(b);
    doParsimPacking(b,this->sourceAddress);
    doParsimPacking(b,this->destinationAddress);
    doParsimPacking(b,this->curHopLimit);
    doParsimPacking(b,this->registeredAddress);
    doParsimPacking(b,this->registLifetime);
    doParsimPacking(b,this->EUI64);
    doParsimPacking(b,this->status);
}

void Ipv6DuplicateAddrConfirm::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::Ipv6NdMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceAddress);
    doParsimUnpacking(b,this->destinationAddress);
    doParsimUnpacking(b,this->curHopLimit);
    doParsimUnpacking(b,this->registeredAddress);
    doParsimUnpacking(b,this->registLifetime);
    doParsimUnpacking(b,this->EUI64);
    doParsimUnpacking(b,this->status);
}

const Ipv6Address& Ipv6DuplicateAddrConfirm::getSourceAddress() const
{
    return this->sourceAddress;
}

void Ipv6DuplicateAddrConfirm::setSourceAddress(const Ipv6Address& sourceAddress)
{
    handleChange();
    this->sourceAddress = sourceAddress;
}

const Ipv6Address& Ipv6DuplicateAddrConfirm::getDestinationAddress() const
{
    return this->destinationAddress;
}

void Ipv6DuplicateAddrConfirm::setDestinationAddress(const Ipv6Address& destinationAddress)
{
    handleChange();
    this->destinationAddress = destinationAddress;
}

unsigned short Ipv6DuplicateAddrConfirm::getCurHopLimit() const
{
    return this->curHopLimit;
}

void Ipv6DuplicateAddrConfirm::setCurHopLimit(unsigned short curHopLimit)
{
    handleChange();
    this->curHopLimit = curHopLimit;
}

const Ipv6Address& Ipv6DuplicateAddrConfirm::getRegisteredAddress() const
{
    return this->registeredAddress;
}

void Ipv6DuplicateAddrConfirm::setRegisteredAddress(const Ipv6Address& registeredAddress)
{
    handleChange();
    this->registeredAddress = registeredAddress;
}

unsigned short Ipv6DuplicateAddrConfirm::getRegistLifetime() const
{
    return this->registLifetime;
}

void Ipv6DuplicateAddrConfirm::setRegistLifetime(unsigned short registLifetime)
{
    handleChange();
    this->registLifetime = registLifetime;
}

const InterfaceIdentifier& Ipv6DuplicateAddrConfirm::getEUI64() const
{
    return this->EUI64;
}

void Ipv6DuplicateAddrConfirm::setEUI64(const InterfaceIdentifier& EUI64)
{
    handleChange();
    this->EUI64 = EUI64;
}

unsigned int Ipv6DuplicateAddrConfirm::getStatus() const
{
    return this->status;
}

void Ipv6DuplicateAddrConfirm::setStatus(unsigned int status)
{
    handleChange();
    this->status = status;
}

class Ipv6DuplicateAddrConfirmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_sourceAddress,
        FIELD_destinationAddress,
        FIELD_curHopLimit,
        FIELD_registeredAddress,
        FIELD_registLifetime,
        FIELD_EUI64,
        FIELD_status,
    };
  public:
    Ipv6DuplicateAddrConfirmDescriptor();
    virtual ~Ipv6DuplicateAddrConfirmDescriptor();

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

Register_ClassDescriptor(Ipv6DuplicateAddrConfirmDescriptor)

Ipv6DuplicateAddrConfirmDescriptor::Ipv6DuplicateAddrConfirmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6DuplicateAddrConfirm)), "inet::Ipv6NdMessage")
{
    propertynames = nullptr;
}

Ipv6DuplicateAddrConfirmDescriptor::~Ipv6DuplicateAddrConfirmDescriptor()
{
    delete[] propertynames;
}

bool Ipv6DuplicateAddrConfirmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6DuplicateAddrConfirm *>(obj)!=nullptr;
}

const char **Ipv6DuplicateAddrConfirmDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6DuplicateAddrConfirmDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6DuplicateAddrConfirmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int Ipv6DuplicateAddrConfirmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_sourceAddress
        0,    // FIELD_destinationAddress
        FD_ISEDITABLE,    // FIELD_curHopLimit
        0,    // FIELD_registeredAddress
        FD_ISEDITABLE,    // FIELD_registLifetime
        FD_ISCOMPOUND,    // FIELD_EUI64
        FD_ISEDITABLE,    // FIELD_status
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6DuplicateAddrConfirmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceAddress",
        "destinationAddress",
        "curHopLimit",
        "registeredAddress",
        "registLifetime",
        "EUI64",
        "status",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int Ipv6DuplicateAddrConfirmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 's' && strcmp(fieldName, "sourceAddress") == 0) return base+0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destinationAddress") == 0) return base+1;
    if (fieldName[0] == 'c' && strcmp(fieldName, "curHopLimit") == 0) return base+2;
    if (fieldName[0] == 'r' && strcmp(fieldName, "registeredAddress") == 0) return base+3;
    if (fieldName[0] == 'r' && strcmp(fieldName, "registLifetime") == 0) return base+4;
    if (fieldName[0] == 'E' && strcmp(fieldName, "EUI64") == 0) return base+5;
    if (fieldName[0] == 's' && strcmp(fieldName, "status") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6DuplicateAddrConfirmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_sourceAddress
        "inet::Ipv6Address",    // FIELD_destinationAddress
        "unsigned short",    // FIELD_curHopLimit
        "inet::Ipv6Address",    // FIELD_registeredAddress
        "unsigned short",    // FIELD_registLifetime
        "inet::InterfaceIdentifier",    // FIELD_EUI64
        "unsigned int",    // FIELD_status
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6DuplicateAddrConfirmDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6DuplicateAddrConfirmDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6DuplicateAddrConfirmDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrConfirm *pp = (Ipv6DuplicateAddrConfirm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6DuplicateAddrConfirmDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrConfirm *pp = (Ipv6DuplicateAddrConfirm *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6DuplicateAddrConfirmDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrConfirm *pp = (Ipv6DuplicateAddrConfirm *)object; (void)pp;
    switch (field) {
        case FIELD_sourceAddress: return pp->getSourceAddress().str();
        case FIELD_destinationAddress: return pp->getDestinationAddress().str();
        case FIELD_curHopLimit: return ulong2string(pp->getCurHopLimit());
        case FIELD_registeredAddress: return pp->getRegisteredAddress().str();
        case FIELD_registLifetime: return ulong2string(pp->getRegistLifetime());
        case FIELD_EUI64: {std::stringstream out; out << pp->getEUI64(); return out.str();}
        case FIELD_status: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool Ipv6DuplicateAddrConfirmDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrConfirm *pp = (Ipv6DuplicateAddrConfirm *)object; (void)pp;
    switch (field) {
        case FIELD_curHopLimit: pp->setCurHopLimit(string2ulong(value)); return true;
        case FIELD_registLifetime: pp->setRegistLifetime(string2ulong(value)); return true;
        case FIELD_status: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *Ipv6DuplicateAddrConfirmDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_EUI64: return omnetpp::opp_typename(typeid(InterfaceIdentifier));
        default: return nullptr;
    };
}

void *Ipv6DuplicateAddrConfirmDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6DuplicateAddrConfirm *pp = (Ipv6DuplicateAddrConfirm *)object; (void)pp;
    switch (field) {
        case FIELD_sourceAddress: return toVoidPtr(&pp->getSourceAddress()); break;
        case FIELD_destinationAddress: return toVoidPtr(&pp->getDestinationAddress()); break;
        case FIELD_registeredAddress: return toVoidPtr(&pp->getRegisteredAddress()); break;
        case FIELD_EUI64: return toVoidPtr(&pp->getEUI64()); break;
        default: return nullptr;
    }
}

Register_Class(Ipv6NdControlInfo)

Ipv6NdControlInfo::Ipv6NdControlInfo() : ::omnetpp::cObject()
{
}

Ipv6NdControlInfo::Ipv6NdControlInfo(const Ipv6NdControlInfo& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ipv6NdControlInfo::~Ipv6NdControlInfo()
{
}

Ipv6NdControlInfo& Ipv6NdControlInfo::operator=(const Ipv6NdControlInfo& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ipv6NdControlInfo::copy(const Ipv6NdControlInfo& other)
{
    this->nextHop = other.nextHop;
    this->interfaceId = other.interfaceId;
    this->fromHL = other.fromHL;
}

void Ipv6NdControlInfo::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->nextHop);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->fromHL);
}

void Ipv6NdControlInfo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->nextHop);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->fromHL);
}

const Ipv6Address& Ipv6NdControlInfo::getNextHop() const
{
    return this->nextHop;
}

void Ipv6NdControlInfo::setNextHop(const Ipv6Address& nextHop)
{
    this->nextHop = nextHop;
}

int Ipv6NdControlInfo::getInterfaceId() const
{
    return this->interfaceId;
}

void Ipv6NdControlInfo::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

bool Ipv6NdControlInfo::getFromHL() const
{
    return this->fromHL;
}

void Ipv6NdControlInfo::setFromHL(bool fromHL)
{
    this->fromHL = fromHL;
}

class Ipv6NdControlInfoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_nextHop,
        FIELD_interfaceId,
        FIELD_fromHL,
    };
  public:
    Ipv6NdControlInfoDescriptor();
    virtual ~Ipv6NdControlInfoDescriptor();

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

Register_ClassDescriptor(Ipv6NdControlInfoDescriptor)

Ipv6NdControlInfoDescriptor::Ipv6NdControlInfoDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ipv6NdControlInfo)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ipv6NdControlInfoDescriptor::~Ipv6NdControlInfoDescriptor()
{
    delete[] propertynames;
}

bool Ipv6NdControlInfoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ipv6NdControlInfo *>(obj)!=nullptr;
}

const char **Ipv6NdControlInfoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ipv6NdControlInfoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ipv6NdControlInfoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int Ipv6NdControlInfoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_nextHop
        FD_ISEDITABLE,    // FIELD_interfaceId
        FD_ISEDITABLE,    // FIELD_fromHL
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *Ipv6NdControlInfoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nextHop",
        "interfaceId",
        "fromHL",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int Ipv6NdControlInfoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nextHop") == 0) return base+0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interfaceId") == 0) return base+1;
    if (fieldName[0] == 'f' && strcmp(fieldName, "fromHL") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ipv6NdControlInfoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv6Address",    // FIELD_nextHop
        "int",    // FIELD_interfaceId
        "bool",    // FIELD_fromHL
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **Ipv6NdControlInfoDescriptor::getFieldPropertyNames(int field) const
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

const char *Ipv6NdControlInfoDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ipv6NdControlInfoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdControlInfo *pp = (Ipv6NdControlInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ipv6NdControlInfoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdControlInfo *pp = (Ipv6NdControlInfo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ipv6NdControlInfoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdControlInfo *pp = (Ipv6NdControlInfo *)object; (void)pp;
    switch (field) {
        case FIELD_nextHop: return pp->getNextHop().str();
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_fromHL: return bool2string(pp->getFromHL());
        default: return "";
    }
}

bool Ipv6NdControlInfoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdControlInfo *pp = (Ipv6NdControlInfo *)object; (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); return true;
        case FIELD_fromHL: pp->setFromHL(string2bool(value)); return true;
        default: return false;
    }
}

const char *Ipv6NdControlInfoDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *Ipv6NdControlInfoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ipv6NdControlInfo *pp = (Ipv6NdControlInfo *)object; (void)pp;
    switch (field) {
        case FIELD_nextHop: return toVoidPtr(&pp->getNextHop()); break;
        default: return nullptr;
    }
}

} // namespace inet


//
// Generated file, do not edit! Created by nedtool 5.4 from inet/linklayer/common/Ieee802Ctrl.msg.
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
#include "Ieee802Ctrl_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::Ieee802MessageKind");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::Ieee802MessageKind"));
    e->insert(IEEE802CTRL_DATA, "IEEE802CTRL_DATA");
    e->insert(IEEE802CTRL_REGISTER_DSAP, "IEEE802CTRL_REGISTER_DSAP");
    e->insert(IEEE802CTRL_DEREGISTER_DSAP, "IEEE802CTRL_DEREGISTER_DSAP");
    e->insert(IEEE802CTRL_SENDPAUSE, "IEEE802CTRL_SENDPAUSE");
)

Register_Class(Ieee802RegisterDsapCommand)

Ieee802RegisterDsapCommand::Ieee802RegisterDsapCommand() : ::omnetpp::cObject()
{
}

Ieee802RegisterDsapCommand::Ieee802RegisterDsapCommand(const Ieee802RegisterDsapCommand& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ieee802RegisterDsapCommand::~Ieee802RegisterDsapCommand()
{
}

Ieee802RegisterDsapCommand& Ieee802RegisterDsapCommand::operator=(const Ieee802RegisterDsapCommand& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ieee802RegisterDsapCommand::copy(const Ieee802RegisterDsapCommand& other)
{
    this->dsap = other.dsap;
}

void Ieee802RegisterDsapCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->dsap);
}

void Ieee802RegisterDsapCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->dsap);
}

int Ieee802RegisterDsapCommand::getDsap() const
{
    return this->dsap;
}

void Ieee802RegisterDsapCommand::setDsap(int dsap)
{
    this->dsap = dsap;
}

class Ieee802RegisterDsapCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_dsap,
    };
  public:
    Ieee802RegisterDsapCommandDescriptor();
    virtual ~Ieee802RegisterDsapCommandDescriptor();

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

Register_ClassDescriptor(Ieee802RegisterDsapCommandDescriptor)

Ieee802RegisterDsapCommandDescriptor::Ieee802RegisterDsapCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ieee802RegisterDsapCommand)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ieee802RegisterDsapCommandDescriptor::~Ieee802RegisterDsapCommandDescriptor()
{
    delete[] propertynames;
}

bool Ieee802RegisterDsapCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee802RegisterDsapCommand *>(obj)!=nullptr;
}

const char **Ieee802RegisterDsapCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ieee802RegisterDsapCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ieee802RegisterDsapCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int Ieee802RegisterDsapCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dsap
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee802RegisterDsapCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dsap",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee802RegisterDsapCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "dsap") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ieee802RegisterDsapCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_dsap
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee802RegisterDsapCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee802RegisterDsapCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ieee802RegisterDsapCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ieee802RegisterDsapCommand *pp = (Ieee802RegisterDsapCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ieee802RegisterDsapCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ieee802RegisterDsapCommand *pp = (Ieee802RegisterDsapCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee802RegisterDsapCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ieee802RegisterDsapCommand *pp = (Ieee802RegisterDsapCommand *)object; (void)pp;
    switch (field) {
        case FIELD_dsap: return long2string(pp->getDsap());
        default: return "";
    }
}

bool Ieee802RegisterDsapCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ieee802RegisterDsapCommand *pp = (Ieee802RegisterDsapCommand *)object; (void)pp;
    switch (field) {
        case FIELD_dsap: pp->setDsap(string2long(value)); return true;
        default: return false;
    }
}

const char *Ieee802RegisterDsapCommandDescriptor::getFieldStructName(int field) const
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

void *Ieee802RegisterDsapCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ieee802RegisterDsapCommand *pp = (Ieee802RegisterDsapCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Ieee802DeregisterDsapCommand)

Ieee802DeregisterDsapCommand::Ieee802DeregisterDsapCommand() : ::omnetpp::cObject()
{
}

Ieee802DeregisterDsapCommand::Ieee802DeregisterDsapCommand(const Ieee802DeregisterDsapCommand& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ieee802DeregisterDsapCommand::~Ieee802DeregisterDsapCommand()
{
}

Ieee802DeregisterDsapCommand& Ieee802DeregisterDsapCommand::operator=(const Ieee802DeregisterDsapCommand& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ieee802DeregisterDsapCommand::copy(const Ieee802DeregisterDsapCommand& other)
{
    this->dsap = other.dsap;
}

void Ieee802DeregisterDsapCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->dsap);
}

void Ieee802DeregisterDsapCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->dsap);
}

int Ieee802DeregisterDsapCommand::getDsap() const
{
    return this->dsap;
}

void Ieee802DeregisterDsapCommand::setDsap(int dsap)
{
    this->dsap = dsap;
}

class Ieee802DeregisterDsapCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_dsap,
    };
  public:
    Ieee802DeregisterDsapCommandDescriptor();
    virtual ~Ieee802DeregisterDsapCommandDescriptor();

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

Register_ClassDescriptor(Ieee802DeregisterDsapCommandDescriptor)

Ieee802DeregisterDsapCommandDescriptor::Ieee802DeregisterDsapCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ieee802DeregisterDsapCommand)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ieee802DeregisterDsapCommandDescriptor::~Ieee802DeregisterDsapCommandDescriptor()
{
    delete[] propertynames;
}

bool Ieee802DeregisterDsapCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee802DeregisterDsapCommand *>(obj)!=nullptr;
}

const char **Ieee802DeregisterDsapCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ieee802DeregisterDsapCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ieee802DeregisterDsapCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int Ieee802DeregisterDsapCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dsap
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *Ieee802DeregisterDsapCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dsap",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int Ieee802DeregisterDsapCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "dsap") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ieee802DeregisterDsapCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_dsap
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee802DeregisterDsapCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee802DeregisterDsapCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ieee802DeregisterDsapCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ieee802DeregisterDsapCommand *pp = (Ieee802DeregisterDsapCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ieee802DeregisterDsapCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ieee802DeregisterDsapCommand *pp = (Ieee802DeregisterDsapCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee802DeregisterDsapCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ieee802DeregisterDsapCommand *pp = (Ieee802DeregisterDsapCommand *)object; (void)pp;
    switch (field) {
        case FIELD_dsap: return long2string(pp->getDsap());
        default: return "";
    }
}

bool Ieee802DeregisterDsapCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ieee802DeregisterDsapCommand *pp = (Ieee802DeregisterDsapCommand *)object; (void)pp;
    switch (field) {
        case FIELD_dsap: pp->setDsap(string2long(value)); return true;
        default: return false;
    }
}

const char *Ieee802DeregisterDsapCommandDescriptor::getFieldStructName(int field) const
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

void *Ieee802DeregisterDsapCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ieee802DeregisterDsapCommand *pp = (Ieee802DeregisterDsapCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Ieee802PauseCommand)

Ieee802PauseCommand::Ieee802PauseCommand() : ::omnetpp::cObject()
{
}

Ieee802PauseCommand::Ieee802PauseCommand(const Ieee802PauseCommand& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

Ieee802PauseCommand::~Ieee802PauseCommand()
{
}

Ieee802PauseCommand& Ieee802PauseCommand::operator=(const Ieee802PauseCommand& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void Ieee802PauseCommand::copy(const Ieee802PauseCommand& other)
{
    this->destinationAddress = other.destinationAddress;
    this->pauseUnits = other.pauseUnits;
}

void Ieee802PauseCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->destinationAddress);
    doParsimPacking(b,this->pauseUnits);
}

void Ieee802PauseCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->destinationAddress);
    doParsimUnpacking(b,this->pauseUnits);
}

const MacAddress& Ieee802PauseCommand::getDestinationAddress() const
{
    return this->destinationAddress;
}

void Ieee802PauseCommand::setDestinationAddress(const MacAddress& destinationAddress)
{
    this->destinationAddress = destinationAddress;
}

int Ieee802PauseCommand::getPauseUnits() const
{
    return this->pauseUnits;
}

void Ieee802PauseCommand::setPauseUnits(int pauseUnits)
{
    this->pauseUnits = pauseUnits;
}

class Ieee802PauseCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_destinationAddress,
        FIELD_pauseUnits,
    };
  public:
    Ieee802PauseCommandDescriptor();
    virtual ~Ieee802PauseCommandDescriptor();

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

Register_ClassDescriptor(Ieee802PauseCommandDescriptor)

Ieee802PauseCommandDescriptor::Ieee802PauseCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Ieee802PauseCommand)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

Ieee802PauseCommandDescriptor::~Ieee802PauseCommandDescriptor()
{
    delete[] propertynames;
}

bool Ieee802PauseCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Ieee802PauseCommand *>(obj)!=nullptr;
}

const char **Ieee802PauseCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *Ieee802PauseCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int Ieee802PauseCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int Ieee802PauseCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_destinationAddress
        FD_ISEDITABLE,    // FIELD_pauseUnits
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *Ieee802PauseCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destinationAddress",
        "pauseUnits",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int Ieee802PauseCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'd' && strcmp(fieldName, "destinationAddress") == 0) return base+0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "pauseUnits") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *Ieee802PauseCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::MacAddress",    // FIELD_destinationAddress
        "int",    // FIELD_pauseUnits
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **Ieee802PauseCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *Ieee802PauseCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int Ieee802PauseCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Ieee802PauseCommand *pp = (Ieee802PauseCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *Ieee802PauseCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ieee802PauseCommand *pp = (Ieee802PauseCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string Ieee802PauseCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Ieee802PauseCommand *pp = (Ieee802PauseCommand *)object; (void)pp;
    switch (field) {
        case FIELD_destinationAddress: return pp->getDestinationAddress().str();
        case FIELD_pauseUnits: return long2string(pp->getPauseUnits());
        default: return "";
    }
}

bool Ieee802PauseCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Ieee802PauseCommand *pp = (Ieee802PauseCommand *)object; (void)pp;
    switch (field) {
        case FIELD_pauseUnits: pp->setPauseUnits(string2long(value)); return true;
        default: return false;
    }
}

const char *Ieee802PauseCommandDescriptor::getFieldStructName(int field) const
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

void *Ieee802PauseCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Ieee802PauseCommand *pp = (Ieee802PauseCommand *)object; (void)pp;
    switch (field) {
        case FIELD_destinationAddress: return toVoidPtr(&pp->getDestinationAddress()); break;
        default: return nullptr;
    }
}

} // namespace inet


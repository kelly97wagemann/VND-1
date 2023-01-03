//
// Generated file, do not edit! Created by nedtool 5.4 from inet/networklayer/ipv4/IgmpMessage.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_IGMPMESSAGE_M_H
#define __INET_IGMPMESSAGE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class IgmpMessage;
class IgmpQuery;
class Igmpv1Query;
class Igmpv1Report;
class Igmpv2Query;
class Igmpv2Report;
class Igmpv2Leave;
class Igmpv3Query;
struct GroupRecord;
class Igmpv3Report;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address

#include "inet/transportlayer/common/CrcMode_m.h" // import inet.transportlayer.common.CrcMode


namespace inet {

/**
 * Enum generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:27</tt> by nedtool.
 * <pre>
 * enum IgmpType
 * {
 *     IGMP_MEMBERSHIP_QUERY = 0x11;
 *     IGMPV1_MEMBERSHIP_REPORT = 0x12;
 *     IGMPV2_MEMBERSHIP_REPORT = 0x16;
 *     IGMPV2_LEAVE_GROUP = 0x17;
 *     IGMPV3_MEMBERSHIP_REPORT = 0x22;
 * }
 * </pre>
 */
enum IgmpType {
    IGMP_MEMBERSHIP_QUERY = 0x11,
    IGMPV1_MEMBERSHIP_REPORT = 0x12,
    IGMPV2_MEMBERSHIP_REPORT = 0x16,
    IGMPV2_LEAVE_GROUP = 0x17,
    IGMPV3_MEMBERSHIP_REPORT = 0x22
};

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:36</tt> by nedtool.
 * <pre>
 * class IgmpMessage extends FieldsChunk
 * {
 *     IgmpType type;         // 1 byte
 *     uint16_t crc = 0;                   // 2 bytes
 *     CrcMode crcMode = CRC_MODE_UNDEFINED;  // 0 bytes, inet only
 * }
 * </pre>
 */
class INET_API IgmpMessage : public ::inet::FieldsChunk
{
  protected:
    inet::IgmpType type = static_cast<inet::IgmpType>(-1);
    uint16_t crc = 0;
    inet::CrcMode crcMode = CRC_MODE_UNDEFINED;

  private:
    void copy(const IgmpMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const IgmpMessage&);

  public:
    IgmpMessage();
    IgmpMessage(const IgmpMessage& other);
    virtual ~IgmpMessage();
    IgmpMessage& operator=(const IgmpMessage& other);
    virtual IgmpMessage *dup() const override {return new IgmpMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::IgmpType getType() const;
    virtual void setType(inet::IgmpType type);
    virtual uint16_t getCrc() const;
    virtual void setCrc(uint16_t crc);
    virtual inet::CrcMode getCrcMode() const;
    virtual void setCrcMode(inet::CrcMode crcMode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const IgmpMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, IgmpMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:43</tt> by nedtool.
 * <pre>
 * class IgmpQuery extends IgmpMessage
 * {
 *     type = IGMP_MEMBERSHIP_QUERY;
 *     Ipv4Address groupAddress;
 * }
 * </pre>
 */
class INET_API IgmpQuery : public ::inet::IgmpMessage
{
  protected:
    Ipv4Address groupAddress;

  private:
    void copy(const IgmpQuery& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const IgmpQuery&);

  public:
    IgmpQuery();
    IgmpQuery(const IgmpQuery& other);
    virtual ~IgmpQuery();
    IgmpQuery& operator=(const IgmpQuery& other);
    virtual IgmpQuery *dup() const override {return new IgmpQuery(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const Ipv4Address& getGroupAddress() const;
    virtual Ipv4Address& getGroupAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<IgmpQuery*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const Ipv4Address& groupAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const IgmpQuery& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, IgmpQuery& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:49</tt> by nedtool.
 * <pre>
 * class Igmpv1Query extends IgmpQuery
 * {
 *     chunkLength = B(8);
 * }
 * </pre>
 */
class INET_API Igmpv1Query : public ::inet::IgmpQuery
{
  protected:

  private:
    void copy(const Igmpv1Query& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Igmpv1Query&);

  public:
    Igmpv1Query();
    Igmpv1Query(const Igmpv1Query& other);
    virtual ~Igmpv1Query();
    Igmpv1Query& operator=(const Igmpv1Query& other);
    virtual Igmpv1Query *dup() const override {return new Igmpv1Query(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Igmpv1Query& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Igmpv1Query& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:54</tt> by nedtool.
 * <pre>
 * class Igmpv1Report extends IgmpMessage
 * {
 *     chunkLength = B(8);
 *     type = IGMPV1_MEMBERSHIP_REPORT;
 *     Ipv4Address groupAddress;
 * }
 * </pre>
 */
class INET_API Igmpv1Report : public ::inet::IgmpMessage
{
  protected:
    Ipv4Address groupAddress;

  private:
    void copy(const Igmpv1Report& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Igmpv1Report&);

  public:
    Igmpv1Report();
    Igmpv1Report(const Igmpv1Report& other);
    virtual ~Igmpv1Report();
    Igmpv1Report& operator=(const Igmpv1Report& other);
    virtual Igmpv1Report *dup() const override {return new Igmpv1Report(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const Ipv4Address& getGroupAddress() const;
    virtual Ipv4Address& getGroupAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<Igmpv1Report*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const Ipv4Address& groupAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Igmpv1Report& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Igmpv1Report& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:61</tt> by nedtool.
 * <pre>
 * class Igmpv2Query extends IgmpQuery      //FIXME Igmpv1Query and Igmpv2Query differs only value of code field.
 * {
 *     chunkLength = B(8);
 *     simtime_t maxRespTime;      // stored in `code` in units of 1/10 second, 0.1-25.5s
 * }
 * </pre>
 */
class INET_API Igmpv2Query : public ::inet::IgmpQuery
{
  protected:
    omnetpp::simtime_t maxRespTime = SIMTIME_ZERO;

  private:
    void copy(const Igmpv2Query& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Igmpv2Query&);

  public:
    Igmpv2Query();
    Igmpv2Query(const Igmpv2Query& other);
    virtual ~Igmpv2Query();
    Igmpv2Query& operator=(const Igmpv2Query& other);
    virtual Igmpv2Query *dup() const override {return new Igmpv2Query(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual omnetpp::simtime_t getMaxRespTime() const;
    virtual void setMaxRespTime(omnetpp::simtime_t maxRespTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Igmpv2Query& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Igmpv2Query& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:67</tt> by nedtool.
 * <pre>
 * class Igmpv2Report extends IgmpMessage
 * {
 *     chunkLength = B(8);
 *     type = IGMPV2_MEMBERSHIP_REPORT;
 *     Ipv4Address groupAddress;
 * }
 * </pre>
 */
class INET_API Igmpv2Report : public ::inet::IgmpMessage
{
  protected:
    Ipv4Address groupAddress;

  private:
    void copy(const Igmpv2Report& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Igmpv2Report&);

  public:
    Igmpv2Report();
    Igmpv2Report(const Igmpv2Report& other);
    virtual ~Igmpv2Report();
    Igmpv2Report& operator=(const Igmpv2Report& other);
    virtual Igmpv2Report *dup() const override {return new Igmpv2Report(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const Ipv4Address& getGroupAddress() const;
    virtual Ipv4Address& getGroupAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<Igmpv2Report*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const Ipv4Address& groupAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Igmpv2Report& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Igmpv2Report& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:74</tt> by nedtool.
 * <pre>
 * class Igmpv2Leave extends IgmpMessage
 * {
 *     chunkLength = B(8);
 *     type = IGMPV2_LEAVE_GROUP;
 *     Ipv4Address groupAddress;
 * }
 * </pre>
 */
class INET_API Igmpv2Leave : public ::inet::IgmpMessage
{
  protected:
    Ipv4Address groupAddress;

  private:
    void copy(const Igmpv2Leave& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Igmpv2Leave&);

  public:
    Igmpv2Leave();
    Igmpv2Leave(const Igmpv2Leave& other);
    virtual ~Igmpv2Leave();
    Igmpv2Leave& operator=(const Igmpv2Leave& other);
    virtual Igmpv2Leave *dup() const override {return new Igmpv2Leave(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const Ipv4Address& getGroupAddress() const;
    virtual Ipv4Address& getGroupAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<Igmpv2Leave*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const Ipv4Address& groupAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Igmpv2Leave& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Igmpv2Leave& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:88</tt> by nedtool.
 * <pre>
 * //
 * // Igmpv3Query extends Igmpv2Query, because
 * // Igmpv2 routers must accept Igmpv3Query packets.
 * //
 * // Note: in Igmpv3Query the maxResponseTime field is
 * // renamed to maxResponseCode and it is interpreted
 * // differently than in Igmpv2.
 * class Igmpv3Query extends Igmpv2Query
 * {
 *     // maxRespTime stored in `code` in units of 1/10 second
 *     //     0-127: 0-12.7s
 *     //   128-255: 1eeemmmm : (mant | 0x10) << (exp + 3)
 *     bool suppressRouterProc;
 *     unsigned char robustnessVariable;
 *     unsigned char queryIntervalCode;
 *     Ipv4AddressVector sourceList;
 * }
 * </pre>
 */
class INET_API Igmpv3Query : public ::inet::Igmpv2Query
{
  protected:
    bool suppressRouterProc = false;
    unsigned char robustnessVariable = 0;
    unsigned char queryIntervalCode = 0;
    Ipv4AddressVector sourceList;

  private:
    void copy(const Igmpv3Query& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Igmpv3Query&);

  public:
    Igmpv3Query();
    Igmpv3Query(const Igmpv3Query& other);
    virtual ~Igmpv3Query();
    Igmpv3Query& operator=(const Igmpv3Query& other);
    virtual Igmpv3Query *dup() const override {return new Igmpv3Query(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual bool getSuppressRouterProc() const;
    virtual void setSuppressRouterProc(bool suppressRouterProc);
    virtual unsigned char getRobustnessVariable() const;
    virtual void setRobustnessVariable(unsigned char robustnessVariable);
    virtual unsigned char getQueryIntervalCode() const;
    virtual void setQueryIntervalCode(unsigned char queryIntervalCode);
    virtual const Ipv4AddressVector& getSourceList() const;
    virtual Ipv4AddressVector& getSourceListForUpdate() { handleChange();return const_cast<Ipv4AddressVector&>(const_cast<Igmpv3Query*>(this)->getSourceList());}
    virtual void setSourceList(const Ipv4AddressVector& sourceList);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Igmpv3Query& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Igmpv3Query& obj) {obj.parsimUnpack(b);}

/**
 * Enum generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:99</tt> by nedtool.
 * <pre>
 * enum GroupRecordType
 * {
 *     MODE_IS_INCLUDE = 1;
 *     MODE_IS_EXCLUDE = 2;
 *     CHANGE_TO_INCLUDE_MODE = 3;
 *     CHANGE_TO_EXCLUDE_MODE = 4;
 *     ALLOW_NEW_SOURCES = 5;
 *     BLOCK_OLD_SOURCE = 6;
 * }
 * </pre>
 */
enum GroupRecordType {
    MODE_IS_INCLUDE = 1,
    MODE_IS_EXCLUDE = 2,
    CHANGE_TO_INCLUDE_MODE = 3,
    CHANGE_TO_EXCLUDE_MODE = 4,
    ALLOW_NEW_SOURCES = 5,
    BLOCK_OLD_SOURCE = 6
};

/**
 * Struct generated from inet/networklayer/ipv4/IgmpMessage.msg:109 by nedtool.
 */
struct INET_API GroupRecord
{
    GroupRecord();
    int recordType;
    Ipv4Address groupAddress;
    Ipv4AddressVector sourceList;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const GroupRecord& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, GroupRecord& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GroupRecord& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GroupRecord& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>inet/networklayer/ipv4/IgmpMessage.msg:116</tt> by nedtool.
 * <pre>
 * class Igmpv3Report extends IgmpMessage
 * {
 *     type = IGMPV3_MEMBERSHIP_REPORT;
 *     GroupRecord groupRecord[];
 * }
 * </pre>
 */
class INET_API Igmpv3Report : public ::inet::IgmpMessage
{
  protected:
    GroupRecord *groupRecord = nullptr;
    size_t groupRecord_arraysize = 0;

  private:
    void copy(const Igmpv3Report& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Igmpv3Report&);

  public:
    Igmpv3Report();
    Igmpv3Report(const Igmpv3Report& other);
    virtual ~Igmpv3Report();
    Igmpv3Report& operator=(const Igmpv3Report& other);
    virtual Igmpv3Report *dup() const override {return new Igmpv3Report(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setGroupRecordArraySize(size_t size);
    virtual size_t getGroupRecordArraySize() const;
    virtual const GroupRecord& getGroupRecord(size_t k) const;
    virtual GroupRecord& getGroupRecordForUpdate(size_t k) { handleChange();return const_cast<GroupRecord&>(const_cast<Igmpv3Report*>(this)->getGroupRecord(k));}
    virtual void setGroupRecord(size_t k, const GroupRecord& groupRecord);
    virtual void insertGroupRecord(const GroupRecord& groupRecord);
    virtual void insertGroupRecord(size_t k, const GroupRecord& groupRecord);
    virtual void eraseGroupRecord(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Igmpv3Report& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Igmpv3Report& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_IGMPMESSAGE_M_H


//
// Generated file, do not edit! Created by nedtool 5.4 from veins/modules/messages/WSM_ipwave.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __WSM_IPWAVE_M_H
#define __WSM_IPWAVE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0504
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "inet/linklayer/common/MacAddress.h"
using namespace inet;
// }}

/**
 * Class generated from <tt>veins/modules/messages/WSM_ipwave.msg:29</tt> by nedtool.
 * <pre>
 * packet WSM_ipwave
 * {
 *     //Version of the Wave Short Message
 *     int wsmVersion = 0;
 *     //Determine which security mechanism was used
 *     int securityType = 0;
 *     //Channel Number on which this packet was sent
 *     int channelNumber;
 *     //Data rate with which this packet was sent
 *     int dataRate = 1;
 *     //User priority with which this packet was sent (note the AC mapping rules in Mac1609_4::mapUserPriority)
 *     int userPriority = 7;
 *     //Unique number to identify the service
 *     int psid = 0;
 *     //Provider Service Context
 *     string psc = "Service with some Data";
 *     //Length of Wave Short Message
 *     int wsmLength;
 *     //Data of Wave Short Message
 *     string wsmData = "Some Data";
 * 
 *     MacAddress senderAddress = MacAddress::UNSPECIFIED_ADDRESS;
 *     MacAddress recipientAddress = MacAddress::UNSPECIFIED_ADDRESS;
 *     int serial = 0;
 *     simtime_t timestamp = 0;
 * }
 * </pre>
 */
class WSM_ipwave : public ::omnetpp::cPacket
{
  protected:
    int wsmVersion;
    int securityType;
    int channelNumber;
    int dataRate;
    int userPriority;
    int psid;
    ::omnetpp::opp_string psc;
    int wsmLength;
    ::omnetpp::opp_string wsmData;
    MacAddress senderAddress;
    MacAddress recipientAddress;
    int serial;
    ::omnetpp::simtime_t timestamp;

  private:
    void copy(const WSM_ipwave& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const WSM_ipwave&);

  public:
    WSM_ipwave(const char *name=nullptr, short kind=0);
    WSM_ipwave(const WSM_ipwave& other);
    virtual ~WSM_ipwave();
    WSM_ipwave& operator=(const WSM_ipwave& other);
    virtual WSM_ipwave *dup() const override {return new WSM_ipwave(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getWsmVersion() const;
    virtual void setWsmVersion(int wsmVersion);
    virtual int getSecurityType() const;
    virtual void setSecurityType(int securityType);
    virtual int getChannelNumber() const;
    virtual void setChannelNumber(int channelNumber);
    virtual int getDataRate() const;
    virtual void setDataRate(int dataRate);
    virtual int getUserPriority() const;
    virtual void setUserPriority(int userPriority);
    virtual int getPsid() const;
    virtual void setPsid(int psid);
    virtual const char * getPsc() const;
    virtual void setPsc(const char * psc);
    virtual int getWsmLength() const;
    virtual void setWsmLength(int wsmLength);
    virtual const char * getWsmData() const;
    virtual void setWsmData(const char * wsmData);
    virtual MacAddress& getSenderAddress();
    virtual const MacAddress& getSenderAddress() const {return const_cast<WSM_ipwave*>(this)->getSenderAddress();}
    virtual void setSenderAddress(const MacAddress& senderAddress);
    virtual MacAddress& getRecipientAddress();
    virtual const MacAddress& getRecipientAddress() const {return const_cast<WSM_ipwave*>(this)->getRecipientAddress();}
    virtual void setRecipientAddress(const MacAddress& recipientAddress);
    virtual int getSerial() const;
    virtual void setSerial(int serial);
    virtual ::omnetpp::simtime_t getTimestamp() const;
    virtual void setTimestamp(::omnetpp::simtime_t timestamp);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const WSM_ipwave& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, WSM_ipwave& obj) {obj.parsimUnpack(b);}


#endif // ifndef __WSM_IPWAVE_M_H


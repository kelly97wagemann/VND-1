//
// Generated file, do not edit! Created by nedtool 5.4 from inet/applications/base/ApplicationPacket.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_APPLICATIONPACKET_M_H
#define __INET_APPLICATIONPACKET_M_H

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

class ApplicationPacket;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/applications/base/ApplicationPacket.msg:28</tt> by nedtool.
 * <pre>
 * //
 * // Generic application packet
 * //
 * // TODO: rename to ApplicationHeader and remove ByteCountChunk from ApplicationHeaderSerializer
 * class ApplicationPacket extends FieldsChunk
 * {
 *     uint32_t sequenceNumber;
 * }
 * </pre>
 */
class INET_API ApplicationPacket : public ::inet::FieldsChunk
{
  protected:
    uint32_t sequenceNumber = 0;

  private:
    void copy(const ApplicationPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ApplicationPacket&);

  public:
    ApplicationPacket();
    ApplicationPacket(const ApplicationPacket& other);
    virtual ~ApplicationPacket();
    ApplicationPacket& operator=(const ApplicationPacket& other);
    virtual ApplicationPacket *dup() const override {return new ApplicationPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual uint32_t getSequenceNumber() const;
    virtual void setSequenceNumber(uint32_t sequenceNumber);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ApplicationPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ApplicationPacket& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_APPLICATIONPACKET_M_H


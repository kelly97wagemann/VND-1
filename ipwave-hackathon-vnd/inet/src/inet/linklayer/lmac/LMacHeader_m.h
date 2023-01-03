//
// Generated file, do not edit! Created by nedtool 5.4 from inet/linklayer/lmac/LMacHeader.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_LMACHEADER_M_H
#define __INET_LMACHEADER_M_H

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

class LMacHeader;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/linklayer/base/MacHeaderBase_m.h" // import inet.linklayer.base.MacHeaderBase


namespace inet {

/**
 * Enum generated from <tt>inet/linklayer/lmac/LMacHeader.msg:12</tt> by nedtool.
 * <pre>
 * //TODO split to 2 enums: for packets / for self messages
 * enum LMacType
 * {
 *     LMAC_CONTROL = 167;     // packet type
 *     LMAC_TIMEOUT = 168;
 *     LMAC_WAKEUP = 169;
 *     LMAC_SEND_DATA = 170;
 *     LMAC_SETUP_PHASE_END = 171;
 *     LMAC_CHECK_CHANNEL = 172;
 *     LMAC_SOMEBODY = 173;
 *     LMAC_DATA = 174;     // packet type
 *     LMAC_START_LMAC = 175;
 *     LMAC_SEND_CONTROL = 176;
 * }
 * </pre>
 */
enum LMacType {
    LMAC_CONTROL = 167,
    LMAC_TIMEOUT = 168,
    LMAC_WAKEUP = 169,
    LMAC_SEND_DATA = 170,
    LMAC_SETUP_PHASE_END = 171,
    LMAC_CHECK_CHANNEL = 172,
    LMAC_SOMEBODY = 173,
    LMAC_DATA = 174,
    LMAC_START_LMAC = 175,
    LMAC_SEND_CONTROL = 176
};

/**
 * Class generated from <tt>inet/linklayer/lmac/LMacHeader.msg:26</tt> by nedtool.
 * <pre>
 * class LMacHeader extends MacHeaderBase
 * {
 *     LMacType type;
 *     int mySlot; // the node's current slot number
 *     MacAddress occupiedSlots[]; // currently known occupied slots
 * }
 * </pre>
 */
class INET_API LMacHeader : public ::inet::MacHeaderBase
{
  protected:
    inet::LMacType type = static_cast<inet::LMacType>(-1);
    int mySlot = 0;
    MacAddress *occupiedSlots = nullptr;
    size_t occupiedSlots_arraysize = 0;

  private:
    void copy(const LMacHeader& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LMacHeader&);

  public:
    LMacHeader();
    LMacHeader(const LMacHeader& other);
    virtual ~LMacHeader();
    LMacHeader& operator=(const LMacHeader& other);
    virtual LMacHeader *dup() const override {return new LMacHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::LMacType getType() const;
    virtual void setType(inet::LMacType type);
    virtual int getMySlot() const;
    virtual void setMySlot(int mySlot);
    virtual void setOccupiedSlotsArraySize(size_t size);
    virtual size_t getOccupiedSlotsArraySize() const;
    virtual const MacAddress& getOccupiedSlots(size_t k) const;
    virtual MacAddress& getOccupiedSlotsForUpdate(size_t k) { handleChange();return const_cast<MacAddress&>(const_cast<LMacHeader*>(this)->getOccupiedSlots(k));}
    virtual void setOccupiedSlots(size_t k, const MacAddress& occupiedSlots);
    virtual void insertOccupiedSlots(const MacAddress& occupiedSlots);
    virtual void insertOccupiedSlots(size_t k, const MacAddress& occupiedSlots);
    virtual void eraseOccupiedSlots(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LMacHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LMacHeader& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_LMACHEADER_M_H


#pragma once

#include <cstdint>
#include <vector>
#include <limits>
#include <string>

namespace Pacer
{
    typedef uint32_t TimelineId;
    constexpr TimelineId INVALID_TIMELINE_ID = std::numeric_limits<TimelineId>::max();

    typedef std::vector<uint8_t> MESSAGE_BUFFER;

    enum class Version : uint8_t
    {
        kPrototype = 0,
        kCurrent = kPrototype
    };

    enum class MessageType : uint8_t
    {
        kTimelineStatus = 0,
        kTimelineName = 1,
        kPing = 2,
        kPong = 3,
        kCount
    };

    enum class TimelineStatus : uint8_t
    {
        kStopped = 0,
        kStandby = 1,
        kRunning = 2,
        kPaused = 3,
        kCount
    };

    struct Timestamp
    {
        Timestamp() = default;
        Timestamp(uint8_t hour, uint8_t minute, uint8_t second, uint16_t value, uint16_t scale)
            : hour_(hour)
            , minute_(minute)
            , second_(second)
            , subsecondValue_(value)
            , subsecondScale_(scale)
        {}

        uint8_t hour_ = 0;
        uint8_t minute_ = 0;
        uint8_t second_ = 0;
        uint16_t subsecondValue_ = 0;
        uint16_t subsecondScale_ = 1000;
    };

    struct TimelineStatusPacket
    {
        Version version_ = Version::kPrototype;
        TimelineId timelineId_ = INVALID_TIMELINE_ID;
        uint32_t sequenceNumber_ = 0;
        TimelineStatus status_ = TimelineStatus::kStopped;
        Timestamp referenceClock;
        Timestamp referenceTimeOffset;
        Timestamp timestamp_;
        std::string name_;
        uint8_t timelineHint_ = 0;
    };
    void PackTimelineStatusPacket(const TimelineStatusPacket & message, MESSAGE_BUFFER & buf);
    bool UnpackTimelineStatusPacket(const MESSAGE_BUFFER & buf, TimelineStatusPacket & message);

    struct TimelineName
    {
        Version version_ = Version::kPrototype;
        TimelineId timelineId_;
        std::string name_;
    };
    void PackTimelineStatus(const TimelineName & message, MESSAGE_BUFFER & buf);
    bool UnpackTimelineStatus(const MESSAGE_BUFFER & buf, TimelineName & message);

    struct Ping
    {
        Version version_ = Version::kPrototype;
        uint16_t pingId = 0;
        uint64_t originatingTime = 0;
        uint64_t responseTime = 0;
    };
    void PackPing(const Ping & ping, MESSAGE_BUFFER & buf);
    void UnpackPing(const MESSAGE_BUFFER & buf, Ping & ping);

    struct Pong
    {
        Version version_ = Version::kPrototype;
        uint16_t pingId = 0;
        Timestamp referenceTimestamp_;
    };
    void PackPong(const Pong & ping, MESSAGE_BUFFER & buf);
    void UnpackPong(const MESSAGE_BUFFER & buf, Pong & ping);
}

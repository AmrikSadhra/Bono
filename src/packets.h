#pragma once

#include <cstdint>

namespace Bono
{
#pragma pack(push, 1)
    constexpr int kMaxCars        = 20;
    constexpr int kNumMashalZones = 21;

    enum class PacketType : uint8_t
    {
        Motion       = 0, // Contains all motion data for player’s car – only sent while player is in control
        Session      = 1, // Data about the session – track, time left
        LapData      = 2, //  Data about all the lap times of cars in the session
        Event        = 3, // Various notable events that happen during a session
        Participants = 4, // List of participants in the session, mostly relevant for multiplayer
        CarSetups    = 5, // Packet detailing car setups for cars in the race
        CarTelemetry = 6, // Telemetry data for all cars
        CarStatus    = 7  //  Status data for all cars such as damage
    };

    enum class TeamID : uint8_t
    {
        Mercedes      = 0,
        Ferrari       = 1,
        RedBullRacing = 2,
        Williams      = 3,
        RacingPoint   = 4,
        Renaut        = 5,
        TorroRosso    = 6,
        Haas          = 7,
        McLaren       = 8,
        AlfaRomeo     = 9
    };

    enum class DriverID : uint8_t
    {
        CarlosSainz       = 0,
        DaniilKvyat       = 1,
        DanielRicciardo   = 2,
        KimiRaikkonen     = 6,
        LewisHamilton     = 7,
        MaxVerstappen     = 9,
        NicoHulkenburg    = 10,
        KevinMagnussen    = 11,
        RomainGrosjean    = 12,
        SebastianVettel   = 13,
        SergioPerez       = 14,
        ValtteriBottas    = 15,
        LanceStroll       = 19,
        GeorgeRussell     = 50,
        LandoNorris       = 54,
        CharlesLeclerc    = 58,
        PierreGasly       = 59,
        AlexAlbon         = 62,
        AntonioGiovinazzi = 74,
        RobertKubica      = 75
    };

    enum class TrackID : int8_t
    {
        Unknown          = -1,
        Melbourne        = 0,
        PaulRicard       = 1,
        Shanghai         = 2,
        Sakhir           = 3,
        Catalunya        = 4,
        Monaco           = 5,
        Montreal         = 6,
        Silverstone      = 7,
        Hockenheim       = 8,
        Hungaroring      = 9,
        Spa              = 10,
        Monza            = 11,
        Singapore        = 12,
        Suzuka           = 13,
        AbuDhabi         = 14,
        Texas            = 15,
        Brazil           = 16,
        Austria          = 17,
        Sochi            = 18,
        Mexico           = 19,
        Baku             = 20,
        SakhirShort      = 21,
        SilverstoneShort = 22,
        TexasShort       = 23,
        SuzukaShort      = 24
    };

    enum class NationalityID : uint8_t
    {
        American      = 1,
        Argentinean   = 2,
        Australian    = 3,
        Austrian      = 4,
        Azerbaijani   = 5,
        Bahraini      = 6,
        Belgian       = 7,
        Bolivian      = 8,
        Brazilian     = 9,
        British       = 10,
        Bulgarian     = 11,
        Cameroonian   = 12,
        Canadian      = 13,
        Chilean       = 14,
        Chinese       = 15,
        Colombian     = 16,
        CostaRican    = 17,
        Croatian      = 18,
        Cypriot       = 19,
        Czech         = 20,
        Danish        = 21,
        Dutch         = 22,
        Ecuadorian    = 23,
        English       = 24,
        Emirian       = 25,
        Estonian      = 26,
        Finnish       = 27,
        French        = 28,
        German        = 29,
        Ghanaian      = 30,
        Greek         = 31,
        Guatemalan    = 32,
        Honduran      = 33,
        HongKonger    = 34,
        Hungarian     = 35,
        Icelander     = 36,
        Indian        = 37,
        Indonesian    = 38,
        Irish         = 39,
        Israeli       = 40,
        Italian       = 41,
        Jamaican      = 42,
        Japanese      = 43,
        Jordanian     = 44,
        Kuwaiti       = 45,
        Latvian       = 46,
        Lebanese      = 47,
        Lithuanian    = 48,
        Luxembourger  = 49,
        Malaysian     = 50,
        Maltese       = 51,
        Mexican       = 52,
        Monegasque    = 53,
        NewZealander  = 54,
        Nicaraguan    = 55,
        NorthKorean   = 56,
        NorthernIrish = 57,
        Norwegian     = 58,
        Omani         = 59,
        Pakistani     = 60,
        Panamanian    = 61,
        Paraguayan    = 62,
        Peruvian      = 63,
        Polish        = 64,
        Portuguese    = 65,
        Qatari        = 66,
        Romanian      = 67,
        Russian       = 68,
        Salvadoran    = 69,
        Saudi         = 70,
        Scottish      = 71,
        Serbian       = 72,
        Singaporean   = 73,
        Slovakian     = 74,
        Slovenian     = 75,
        SouthKorean   = 76,
        SouthAfrican  = 77,
        Spanish       = 78,
        Swedish       = 79,
        Swiss         = 80,
        Thai          = 81,
        Turkish       = 82,
        Uruguayan     = 83,
        Ukrainian     = 84,
        Venezuelan    = 85,
        Welsh         = 86
    };

    // Packet Header
    // Size: 23 Bytes
    struct PacketHeader
    {
        uint16_t packetFormat;    // 2019
        uint8_t gameMajorVersion; // Game major version - "X.00"
        uint8_t gameMinorVersion; // Game minor version - "1.XX"
        uint8_t packetVersion;    // Version of this packet type, all start from 1
        PacketType packetId;      // Identifier for the packet type, see below
        uint64_t sessionUID;      // Unique identifier for the session
        float sessionTime;        // Session timestamp
        uint32_t frameIdentifier; // Identifier for the frame the data was retrieved on
        uint8_t playerCarIndex;   // Index of player's car in the array
    };

    struct CarMotionData
    {
        float worldPositionX;     // World space X position
        float worldPositionY;     // World space Y position
        float worldPositionZ;     // World space Z position
        float worldVelocityX;     // Velocity in world space X
        float worldVelocityY;     // Velocity in world space Y
        float worldVelocityZ;     // Velocity in world space Z
        int16_t worldForwardDirX; // World space forward X direction (normalised)
        int16_t worldForwardDirY; // World space forward Y direction (normalised)
        int16_t worldForwardDirZ; // World space forward Z direction (normalised)
        int16_t worldRightDirX;   // World space right X direction (normalised)
        int16_t worldRightDirY;   // World space right Y direction (normalised)
        int16_t worldRightDirZ;   // World space right Z direction (normalised)
        float gForceLateral;      // Lateral G-Force component
        float gForceLongitudinal; // Longitudinal G-Force component
        float gForceVertical;     // Vertical G-Force component
        float yaw;                // Yaw angle in radians
        float pitch;              // Pitch angle in radians
        float roll;               // Roll angle in radians
    };

    struct PacketMotionData
    {
        PacketHeader header; // Header

        CarMotionData carMotionData[20]; // Data for all cars on track

        // Extra player car ONLY data
        float suspensionPosition[4];     // Note: All wheel arrays have the following order:
        float suspensionVelocity[4];     // RL, RR, FL, FR
        float suspensionAcceleration[4]; // RL, RR, FL, FR
        float wheelSpeed[4];             // Speed of each wheel
        float wheelSlip[4];              // Slip ratio for each wheel
        float localVelocityX;            // Velocity in local space
        float localVelocityY;            // Velocity in local space
        float localVelocityZ;            // Velocity in local space
        float angularVelocityX;          // Angular velocity x-component
        float angularVelocityY;          // Angular velocity y-component
        float angularVelocityZ;          // Angular velocity z-component
        float angularAccelerationX;      // Angular velocity x-component
        float angularAccelerationY;      // Angular velocity y-component
        float angularAccelerationZ;      // Angular velocity z-component
        float frontWheelsAngle;          // Current front wheels angle in radians
    };

    struct MarshalZone
    {
        float zoneStart; // Fraction (0..1) of way through the lap the marshal zone starts
        int8_t zoneFlag; // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
    };

    struct PacketSessionData
    {
        PacketHeader header; // Header

        uint8_t weather; // Weather - 0 = clear, 1 = light cloud, 2 = overcast
        // 3 = light rain, 4 = heavy rain, 5 = storm
        int8_t trackTemperature; // Track temp. in degrees celsius
        int8_t airTemperature;   // Air temp. in degrees celsius
        uint8_t totalLaps;       // Total number of laps in this race
        uint16_t trackLength;    // Track length in metres
        uint8_t sessionType;     // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P
        // 5 = Q1, 6 = Q2, 7 = Q3, 8_t= Short Q, 9 = OSQ
        // 10 = R, 11 = R2, 12 = Time Trial
        int8_t trackId;               // -1 for unknown, 0-21 for tracks, see appendix
        uint8_t formula;              // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2,
                                      // 3 = F1 Generic
        uint16_t sessionTimeLeft;     // Time left in session in seconds
        uint16_t sessionDuration;     // Session duration in seconds
        uint8_t pitSpeedLimit;        // Pit speed limit in kilometres per hour
        uint8_t gamePaused;           // Whether the game is paused
        uint8_t isSpectating;         // Whether the player is spectating
        uint8_t spectatorCarIndex;    // Index of the car being spectated
        uint8_t sliProNativeSupport;  // SLI Pro support, 0 = inactive, 1 = active
        uint8_t numMarshalZones;      // Number of marshal zones to follow
        MarshalZone marshalZones[21]; // List of marshal zones – max 21
        uint8_t safetyCarStatus;      // 0 = no safety car, 1 = full safety car
        // 2 = virtual safety car
        uint8_t networkGame; // 0 = offline, 1 = online
    };

    typedef struct
    {
        float lastLapTime;    // Last lap time in seconds
        float currentLapTime; // Current time around the lap in seconds
        float bestLapTime;    // Best lap time of the session in seconds
        float sector1Time;    // Sector 1 time in seconds
        float sector2Time;    // Sector 2 time in seconds
        float lapDistance;    // Distance vehicle is around current lap in metres – could
        // be negative if line hasn’t been crossed yet
        float totalDistance; // Total distance travelled in session in metres – could
        // be negative if line hasn’t been crossed yet
        float safetyCarDelta;      // Delta in seconds for safety car
        uint8_t carPosition;       // Car race position
        uint8_t currentLapNum;     // Current lap number
        uint8_t pitStatus;         // 0 = none, 1 = pitting, 2 = in pit area
        uint8_t sector;            // 0 = sector1, 1 = sector2, 2 = sector3
        uint8_t currentLapInvalid; // Current lap invalid - 0 = valid, 1 = invalid
        uint8_t penalties;         // Accumulated time penalties in seconds to be added
        uint8_t gridPosition;      // Grid position the vehicle started the race in
        uint8_t driverStatus;      // Status of driver - 0 = in garage, 1 = flying lap
                                   // 2 = in lap, 3 = out lap, 4 = on track
        uint8_t resultStatus;      // Result status - 0 = invalid, 1 = inactive, 2 = active
                                   // 3 = finished, 4 = disqualified, 5 = not classified
                                   // 6 = retired
    } LapData;

    struct PacketLapData
    {
        PacketHeader header; // Header

        LapData lapData[20]; // Lap data for all cars on track
    };

    // The event details packet is different for each type of event.
    // Make sure only the correct type is interpreted.
    union EventDataDetails
    {
        struct
        {
            uint8_t vehicleIdx; // Vehicle index of car achieving fastest lap
            float lapTime;      // Lap time is in seconds
        } FastestLap;

        struct
        {
            uint8_t vehicleIdx; // Vehicle index of car retiring
        } Retirement;

        struct
        {
            uint8_t vehicleIdx; // Vehicle index of team mate
        } TeamMateInPits;

        struct
        {
            uint8_t vehicleIdx; // Vehicle index of the race winner
        } RaceWinner;
    };

    struct PacketEventData
    {
        PacketHeader header; // Header

        uint8_t eventStringCode[4];    // Event string code, see below
        EventDataDetails eventDetails; // Event details - should be interpreted differently
                                       // for each type
    };

    struct ParticipantData
    {
        uint8_t aiControlled; // Whether the vehicle is AI (1) or Human (0) controlled
        uint8_t driverId;     // Driver id - see appendix
        uint8_t teamId;       // Team id - see appendix
        uint8_t raceNumber;   // Race number of the car
        uint8_t nationality;  // Nationality of the driver
        char name[48];        // Name of participant in UTF-8_tformat – null terminated
        // Will be truncated with … (U+2026) if too long
        uint8_t yourTelemetry; // The player's UDP setting, 0 = restricted, 1 = public
    };

    struct PacketParticipantsData
    {
        PacketHeader header; // Header

        uint8_t numActiveCars; // Number of active cars in the data – should match number of
                               // cars on HUD
        ParticipantData participants[20];
    };

    struct CarSetupData
    {
        uint8_t frontWing;             // Front wing aero
        uint8_t rearWing;              // Rear wing aero
        uint8_t onThrottle;            // Differential adjustment on throttle (percentage)
        uint8_t offThrottle;           // Differential adjustment off throttle (percentage)
        float frontCamber;             // Front camber angle (suspension geometry)
        float rearCamber;              // Rear camber angle (suspension geometry)
        float frontToe;                // Front toe angle (suspension geometry)
        float rearToe;                 // Rear toe angle (suspension geometry)
        uint8_t frontSuspension;       // Front suspension
        uint8_t rearSuspension;        // Rear suspension
        uint8_t frontAntiRollBar;      // Front anti-roll bar
        uint8_t rearAntiRollBar;       // Front anti-roll bar
        uint8_t frontSuspensionHeight; // Front ride height
        uint8_t rearSuspensionHeight;  // Rear ride height
        uint8_t brakePressure;         // Brake pressure (percentage)
        uint8_t brakeBias;             // Brake bias (percentage)
        float frontTyrePressure;       // Front tyre pressure (PSI)
        float rearTyrePressure;        // Rear tyre pressure (PSI)
        uint8_t ballast;               // Ballast
        float fuelLoad;                // Fuel load
    };

    struct PacketCarSetupData
    {
        PacketHeader header; // Header

        CarSetupData carSetups[20];
    };

    struct CarTelemetryData
    {
        uint16_t speed;                      // Speed of car in kilometres per hour
        float throttle;                      // Amount of throttle applied (0.0 to 1.0)
        float steer;                         // Steering (-1.0 (full lock left) to 1.0 (full lock right))
        float brake;                         // Amount of brake applied (0.0 to 1.0)
        uint8_t clutch;                      // Amount of clutch applied (0 to 100)
        int8_t gear;                         // Gear selected (1-8, N=0, R=-1)
        uint16_t engineRPM;                  // Engine RPM
        uint8_t drs;                         // 0 = off, 1 = on
        uint8_t revLightsPercent;            // Rev lights indicator (percentage)
        uint16_t brakesTemperature[4];       // Brakes temperature (celsius)
        uint16_t tyresSurfaceTemperature[4]; // Tyres surface temperature (celsius)
        uint16_t tyresInnerTemperature[4];   // Tyres inner temperature (celsius)
        uint16_t engineTemperature;          // Engine temperature (celsius)
        float tyresPressure[4];              // Tyres pressure (PSI)
        uint8_t surfaceType[4];              // Driving surface, see appendices
    };

    struct PacketCarTelemetryData
    {
        PacketHeader header; // Header

        CarTelemetryData carTelemetryData[20];

        uint32_t buttonStatus; // Bit flags specifying which buttons are being pressed
        // currently - see appendices
    };

    struct CarStatusData
    {
        uint8_t tractionControl;    // 0 (off) - 2 (high)
        uint8_t antiLockBrakes;     // 0 (off) - 1 (on)
        uint8_t fuelMix;            // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
        uint8_t frontBrakeBias;     // Front brake bias (percentage)
        uint8_t pitLimiterStatus;   // Pit limiter status - 0 = off, 1 = on
        float fuelInTank;           // Current fuel mass
        float fuelCapacity;         // Fuel capacity
        float fuelRemainingLaps;    // Fuel remaining in terms of laps (value on MFD)
        uint16_t maxRPM;            // Cars max RPM, point of rev limiter
        uint16_t idleRPM;           // Cars idle RPM
        uint8_t maxGears;           // Maximum number of gears
        uint8_t drsAllowed;         // 0 = not allowed, 1 = allowed, -1 = unknown
        uint8_t tyresWear[4];       // Tyre wear percentage
        uint8_t actualTyreCompound; // F1 Modern - 16_t= C5, 17 = C4, 18_t= C3, 19 = C2, 20 = C1
        // 7 = inter, 8_t= wet
        // F1 Classic - 9 = dry, 10 = wet
        // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
        // 15 = wet
        uint8_t tyreVisualCompound; // F1 visual (can be different from actual compound)
        // 16_t= soft, 17 = medium, 18_t= hard, 7 = inter, 8_t= wet
        // F1 Classic – same as above
        // F2 – same as above
        uint8_t tyresDamage[4];       // Tyre damage (percentage)
        uint8_t frontLeftWingDamage;  // Front left wing damage (percentage)
        uint8_t frontRightWingDamage; // Front right wing damage (percentage)
        uint8_t rearWingDamage;       // Rear wing damage (percentage)
        uint8_t engineDamage;         // Engine damage (percentage)
        uint8_t gearBoxDamage;        // Gear box damage (percentage)
        int8_t vehicleFiaFlags;       // -1 = invalid/unknown, 0 = none, 1 = green
        // 2 = blue, 3 = yellow, 4 = red
        float ersStoreEnergy;  // ERS energy store in Joules
        uint8_t ersDeployMode; // ERS deployment mode, 0 = none, 1 = low, 2 = medium
        // 3 = high, 4 = overtake, 5 = hotlap
        float ersHarvestedThisLapMGUK; // ERS energy harvested this lap by MGU-K
        float ersHarvestedThisLapMGUH; // ERS energy harvested this lap by MGU-H
        float ersDeployedThisLap;      // ERS energy deployed this lap
    };

    struct PacketCarStatusData
    {
        PacketHeader header; // Header

        CarStatusData carStatusData[20];
    };

    struct UInt16Quad
    {
        uint16_t A;
        uint16_t B;
        uint16_t C;
        uint16_t D;
    };

    struct SingleQuad
    {
        float A;
        float B;
        float C;
        float D;
    };

    struct ByteQuad
    {
        uint8_t A;
        uint8_t B;
        uint8_t C;
        uint8_t D;
    };
#pragma pack(pop)
} // namespace Bono
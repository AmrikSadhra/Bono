#pragma once

#include <cstdint>

namespace Bono
{
    constexpr int kMaxCars        = 20;
    constexpr int kNumMashalZones = 21;

    enum PacketType : uint8_t
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

    enum TeamID : uint8_t
    {
        Mercedes     = 0,
        Ferrari      = 1,
        Red_Bull     = 2,
        Williams     = 3,
        Racing_Point = 4,
        Renaut       = 5,
        Torro_Rosso  = 6,
        Haas         = 7,
        McLaren      = 8,
        Alfa_Romeo   = 9
    };

    enum DriverID : uint8_t
    {
        Carlos_Sainz       = 0,
        Daniil_Kvyat       = 1,
        Daniel_Ricciardo   = 2,
        Kimi_Raikkonen     = 6,
        Lewis_Hamilton     = 7,
        Max_Verstappen     = 9,
        Nico_Hulkenburg    = 10,
        Kevin_Magnussen    = 11,
        Romain_Grosjean    = 12,
        Sebastian_Vettel   = 13,
        Sergio_Perez       = 14,
        Valtteri_Bottas    = 15,
        Lance_Stroll       = 19,
        George_Russell     = 50,
        Lando_Norris       = 54,
        Charles_Leclerc    = 58,
        Pierre_Gasly       = 59,
        Alex_Albon         = 62,
        Antonio_Giovinazzi = 74,
        Robert_Kubica      = 75
    };

    enum TrackID : int8_t
    {
        Unknown           = -1,
        Melbourne         = 0,
        Paul_Ricard       = 1,
        Shanghai          = 2,
        Sakhir            = 3,
        Catalunya         = 4,
        Monaco            = 5,
        Montreal          = 6,
        Silverstone       = 7,
        Hockenheim        = 8,
        Hungaroring       = 9,
        Spa               = 10,
        Monza             = 11,
        Singapore         = 12,
        Suzuka            = 13,
        Abu_Dhabi         = 14,
        Texas             = 15,
        Brazil            = 16,
        Austria           = 17,
        Sochi             = 18,
        Mexico            = 19,
        Baku              = 20,
        Sakhir_Short      = 21,
        Silverstone_Short = 22,
        Texas_Short       = 23,
        Suzuka_Short      = 24
    };

    enum NationalityID : uint8_t
    {
        American       = 1,
        Argentinean    = 2,
        Australian     = 3,
        Austrian       = 4,
        Azerbaijani    = 5,
        Bahraini       = 6,
        Belgian        = 7,
        Bolivian       = 8,
        Brazilian      = 9,
        British        = 10,
        Bulgarian      = 11,
        Cameroonian    = 12,
        Canadian       = 13,
        Chilean        = 14,
        Chinese        = 15,
        Colombian      = 16,
        Costa_Rican    = 17,
        Croatian       = 18,
        Cypriot        = 19,
        Czech          = 20,
        Danish         = 21,
        Dutch          = 22,
        Ecuadorian     = 23,
        English        = 24,
        Emirian        = 25,
        Estonian       = 26,
        Finnish        = 27,
        French         = 28,
        German         = 29,
        Ghanaian       = 30,
        Greek          = 31,
        Guatemalan     = 32,
        Honduran       = 33,
        Hong_Konger    = 34,
        Hungarian      = 35,
        Icelander      = 36,
        Indian         = 37,
        Indonesian     = 38,
        Irish          = 39,
        Israeli        = 40,
        Italian        = 41,
        Jamaican       = 42,
        Japanese       = 43,
        Jordanian      = 44,
        Kuwaiti        = 45,
        Latvian        = 46,
        Lebanese       = 47,
        Lithuanian     = 48,
        Luxembourger   = 49,
        Malaysian      = 50,
        Maltese        = 51,
        Mexican        = 52,
        Monegasque     = 53,
        New_Zealander  = 54,
        Nicaraguan     = 55,
        North_Korean   = 56,
        Northern_Irish = 57,
        Norwegian      = 58,
        Omani          = 59,
        Pakistani      = 60,
        Panamanian     = 61,
        Paraguayan     = 62,
        Peruvian       = 63,
        Polish         = 64,
        Portuguese     = 65,
        Qatari         = 66,
        Romanian       = 67,
        Russian        = 68,
        Salvadoran     = 69,
        Saudi          = 70,
        Scottish       = 71,
        Serbian        = 72,
        Singaporean    = 73,
        Slovakian      = 74,
        Slovenian      = 75,
        South_Korean   = 76,
        South_African  = 77,
        Spanish        = 78,
        Swedish        = 79,
        Swiss          = 80,
        Thai           = 81,
        Turkish        = 82,
        Uruguayan      = 83,
        Ukrainian      = 84,
        Venezuelan     = 85,
        Welsh          = 86
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
} // namespace Bono
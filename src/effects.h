#pragma once

#include <vector>
#include <stdint.h>

struct Note
{
    float begin_timestamp; // in seconds
    float length; // in seconds
    uint16_t instrument_index;
    uint8_t key;
    uint8_t velocity;
};

typedef int16_t (*NoteCallback)(const Note *note, float time, float volume); // function that processes the final sample based on the note, the current time in seconds, and volume

struct Instrument
{
    float volume;
    NoteCallback callback;
};

struct PatternBlueprint
{
    std::vector<Note> notes;
};

struct Pattern
{
    float begin_timestamp; // in seconds
    float length;
    uint16_t blueprint_index;
};

struct Track
{
    std::vector<Pattern> patterns;
};

static std::vector<Track> tracks;
static std::vector<PatternBlueprint> patterns;
static std::vector<Instrument> instruments;
#pragma once

#include <cstdint>

namespace weather {

struct Vec3 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
};

struct WeatherId {
    std::uint32_t value{0};
};

enum class WeatherType : std::uint8_t {
    Clear,
    Cloudy,
    LightRain,
    HeavyRain,
    Storm,
    Fog,
    Snow,
    Blizzard,
    Heat,
    Sandstorm,
};

enum class PrecipitationType : std::uint8_t {
    None,
    Rain,
    Snow,
    Hail,
    Ash,
    Sand,
    AcidRain,
};

struct PrecipitationProperties {
    PrecipitationType type{PrecipitationType::None};
    float intensity{0.0f};
    float accumulationRate{0.0f};
    float surfaceWetnessRate{0.0f};
    float visibilityPenalty{0.0f};
};

struct WindProperties {
    Vec3 direction{1.0f, 0.0f, 0.0f};
    float strength{0.0f};
    float gustStrength{0.0f};
    float gustFrequency{0.0f};
    float turbulence{0.0f};
};

struct WeatherProfile {
    WeatherId id{};
    WeatherType type{WeatherType::Clear};
    PrecipitationProperties precipitation{};
    WindProperties wind{};
    float targetTemperature{20.0f};
    float humidity{0.5f};
    float fogDensity{0.0f};
};

struct WeatherState {
    WeatherId profileId{};
    float intensity{0.0f};
    float precipitation{0.0f};
    Vec3 windDirection{1.0f, 0.0f, 0.0f};
    float windStrength{0.0f};
    float temperature{20.0f};
    float humidity{0.5f};
    float fogDensity{0.0f};
    float timeInState{0.0f};
};

struct WeatherSample {
    PrecipitationType precipitationType{PrecipitationType::None};
    float precipitationAmount{0.0f};
    float wetnessRate{0.0f};
    float accumulationRate{0.0f};
    Vec3 windDirection{1.0f, 0.0f, 0.0f};
    float windStrength{0.0f};
    float temperature{20.0f};
    float humidity{0.5f};
    float dryingRate{0.0f};
    float visibility{1.0f};
    float fogDensity{0.0f};
};

} // namespace weather

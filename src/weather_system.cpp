#include "weather/weather_system.hpp"

namespace weather {

void WeatherSystem::setGlobalWeather(WeatherState targetState, float transitionTimeSeconds) {
    transitionStart_ = current_;
    target_ = targetState;
    transitionDuration_ = transitionTimeSeconds > 0.0f ? transitionTimeSeconds : 0.0f;
    transitionT_ = transitionDuration_ > 0.0f ? 0.0f : 1.0f;

    if (transitionT_ >= 1.0f) {
        current_ = target_;
    }
}

void WeatherSystem::update(float dt) {
    current_.timeInState += dt;

    if (transitionT_ >= 1.0f || transitionDuration_ <= 0.0f) {
        return;
    }

    transitionT_ = clamp01(transitionT_ + dt / transitionDuration_);

    current_.intensity = lerp(transitionStart_.intensity, target_.intensity, transitionT_);
    current_.precipitation = lerp(transitionStart_.precipitation, target_.precipitation, transitionT_);
    current_.windStrength = lerp(transitionStart_.windStrength, target_.windStrength, transitionT_);
    current_.windDirection = {
        lerp(transitionStart_.windDirection.x, target_.windDirection.x, transitionT_),
        lerp(transitionStart_.windDirection.y, target_.windDirection.y, transitionT_),
        lerp(transitionStart_.windDirection.z, target_.windDirection.z, transitionT_),
    };
    current_.temperature = lerp(transitionStart_.temperature, target_.temperature, transitionT_);
    current_.humidity = lerp(transitionStart_.humidity, target_.humidity, transitionT_);
    current_.fogDensity = lerp(transitionStart_.fogDensity, target_.fogDensity, transitionT_);
    current_.profileId = target_.profileId;
}

WeatherSample WeatherSystem::sample(const Vec3& /*worldPosition*/) const {
    WeatherSample sample{};

    sample.precipitationAmount = current_.precipitation * current_.intensity;
    sample.wetnessRate = sample.precipitationAmount;
    sample.accumulationRate = sample.precipitationAmount;

    sample.windDirection = current_.windDirection;
    sample.windStrength = current_.windStrength;

    sample.temperature = current_.temperature;
    sample.humidity = current_.humidity;

    sample.dryingRate = current_.windStrength * (1.0f - current_.humidity);

    sample.fogDensity = current_.fogDensity;
    sample.visibility = 1.0f - current_.fogDensity;

    return sample;
}

const WeatherState& WeatherSystem::getGlobalState() const {
    return current_;
}

float WeatherSystem::clamp01(float value) {
    if (value < 0.0f) {
        return 0.0f;
    }
    if (value > 1.0f) {
        return 1.0f;
    }
    return value;
}

float WeatherSystem::lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

} // namespace weather

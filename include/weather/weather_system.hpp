#pragma once

#include "weather/weather_types.hpp"

namespace weather {

class WeatherSystem {
public:
    void setGlobalWeather(WeatherState targetState, float transitionTimeSeconds);
    void update(float dt);

    WeatherSample sample(const Vec3& worldPosition) const;
    const WeatherState& getGlobalState() const;

private:
    static float clamp01(float value);
    static float lerp(float a, float b, float t);

    WeatherState current_{};
    WeatherState transitionStart_{};
    WeatherState target_{};

    float transitionT_{1.0f};
    float transitionDuration_{0.0f};
};

} // namespace weather

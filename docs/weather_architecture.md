# Weather as an Environment Simulation Layer

This repository now defines a render-agnostic weather model with a minimal API surface:

- `WeatherProfile`: configuration/asset for weather behavior.
- `WeatherState`: interpolable runtime values.
- `WeatherSample`: compact per-position environmental effects.
- `WeatherSystem`: transitions + `sample(position)` contract for downstream systems.

## Design Boundary

Weather should not modify movement/controller logic directly.

`WeatherSystem -> SurfaceEnvironmentSystem -> SurfaceState -> Movement/Physics`

## MVP Scope

1. `WeatherProfile` and `WeatherState` data models.
2. Global transition support in `WeatherSystem`.
3. `WeatherSystem::sample(position)` to expose effects.
4. Initial knobs:
   - precipitation/wetness
   - humidity + wind drying
   - temperature
   - fog/visibility

This keeps weather decoupled from rendering and surface material implementation details.

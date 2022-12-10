#pragma once

#include <change_callback.h>

#include <math.h>
#include <atomic>

#include "sensor_id.h"

class sensor_definition_display
{
public:
    sensor_definition_display(double range_min, double range_max, sensor_level level) : range_min(range_min), range_max(range_max), level(level)
    {
    }

    double get_range_min() const { return range_min; }
    double get_range_max() const { return range_max; }
    sensor_level get_level() const { return level; }

    bool is_in_range(double value) const
    {
        return range_min <= value && value < range_max;
    }

private:
    const double range_min;
    const double range_max;
    const sensor_level level;
};

class sensor_definition
{
public:
    sensor_definition(const char *name, const char *unit, const sensor_definition_display *display_definitions, size_t display_definitions_count)
        : name(name), unit(unit), display_definitions(display_definitions), display_definitions_count(display_definitions_count)
    {
    }

    sensor_level calculate_level(double value_p) const
    {
        for (uint8_t i = 0; i < display_definitions_count; i++)
        {
            if (display_definitions[i].is_in_range(value_p))
            {
                return display_definitions[i].get_level();
            }
        }
        return display_definitions[0].get_level();
    }

    const char *get_unit() const { return unit; }
    const char *get_name() const { return name; }

private:
    const char *name;
    const char *unit;
    const sensor_definition_display *display_definitions;
    const uint8_t display_definitions_count;
};

extern const std::array<sensor_definition, total_sensors> sensor_definitions;

class sensor_value : public change_callback
{
public:
    typedef int32_t value_type;

    value_type get_value() const { return value.load(); }

    template <class T>
    void set_value(T value_)
    {
        const auto new_value = static_cast<value_type>(value_);
        if (value.exchange(new_value) != new_value)
        {
            call_change_listeners();
        }
    }

private:
    std::atomic<value_type> value{0};
};

 

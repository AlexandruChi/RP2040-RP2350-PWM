#ifndef PWM_H
#define PWM_H

#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define limit(value, min, max) ((value) < (min) ? (min) : (value) > (max) ? (max) : (value))

static inline float pwm_get_clkdiv(float target_freq_hz, uint32_t wrap) {
    return (float)clock_get_hz(clk_sys) / (target_freq_hz * (wrap + 1));
}

static inline uint16_t pwm_get_wrap(uint32_t divisions) {
    return limit(divisions - 1, 0, UINT16_MAX);
}

static inline float pwm_period_us_to_freq_hz(uint64_t us) {
    return 1e6f / us;
}

static inline float pwm_period_ms_to_freq_hz(float ms) {
    return pwm_period_us_to_freq_hz(ms * 1e3f);
}

static inline uint64_t pwm_freq_hz_to_period_us(float freq_hz) {
    return 1e6f / freq_hz;
}

static inline float pwm_freq_hz_to_period_ms(float freq_hz) {
    return pwm_freq_hz_to_period_us(freq_hz) / 1e3f;
}

static inline uint16_t pwm_pulse_us_to_level(uint64_t pulse_us, uint64_t period_us, uint16_t wrap) {
    return limit((pulse_us * (wrap + 1)) / period_us, 0, wrap);
}

static inline uint16_t pwm_pulse_ms_to_level(float pulse_ms, float period_ms, uint16_t wrap) {
    return pwm_pulse_us_to_level(pulse_ms * 1e3f, period_ms * 1e3f, wrap);
}

static inline uint16_t pwm_duty_cycle_to_level(float duty_cycle, uint16_t wrap) {
    return limit((uint16_t)(duty_cycle * wrap), 0, wrap);
}

static inline float pwm_pulse_us_to_duty_cycle(uint64_t pulse_us, uint64_t period_us) {
    return (float)pulse_us / (float)period_us;
}

static inline float pwm_pulse_ms_to_duty_cycle(float pulse_ms, float period_ms) {
    return pwm_pulse_us_to_duty_cycle(pulse_ms * 1e3f, period_ms * 1e3f);
}

static inline uint64_t pwm_duty_cycle_to_pulse_us(float duty_cycle, float freq_hz) {
    return (uint64_t)(duty_cycle * pwm_freq_hz_to_period_us(freq_hz));
}

static inline float pwm_duty_cycle_to_pulse_ms(float duty_cycle, float freq_hz) {
    return pwm_duty_cycle_to_pulse_us(duty_cycle, freq_hz) / 1e3f;
}

static inline pwm_config pwm_get_config_us(uint64_t period_us, uint16_t wrap) {
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, pwm_get_clkdiv(pwm_period_us_to_freq_hz(period_us), wrap));
    pwm_config_set_wrap(&config, wrap);
    return config;
}

static inline pwm_config pwm_get_config_ms(float period_ms, uint16_t wrap) {
    return pwm_get_config_us(period_ms * 1e3f, wrap);
}

static inline pwm_config pwm_get_config_freq(float freq_hz, uint16_t wrap) {
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, pwm_get_clkdiv(freq_hz, wrap));
    pwm_config_set_wrap(&config, wrap);
    return config;
}

#undef limit

#endif /* PWM_H */

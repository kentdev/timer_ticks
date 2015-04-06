#ifndef TIMER_TICKS_H_
#define TIMER_TICKS_H_

// the timing resolution can go down to a couple dozen microseconds if you need it to, though
// you'll probably have to change the prescaler from /64 to /8

// give our timer code 2ms resolution as a default
#define US_PER_TIMER_TICK 2000
#define CYCLES_PER_US (F_CPU / 1000000)

// the timing system uses an 8-bit timer (timer0)
#if (CYCLES_PER_US * US_PER_TIMER_TICK / 64 >= 256)
#error US_PER_TIMER_TICK value too high, will not fit in OCR0A
#endif
#if (CYCLES_PER_US * US_PER_TIMER_TICK / 64 <= 1)
#error US_PER_TIMER_TICK value is too small
#endif
#if (CYCLES_PER_US * US_PER_TIMER_TICK % 64 != 0)
#warning US_PER_TIMER_TICK * CYCLES_PER_US does not divide cleanly by 64, which might cause timer inaccuracy
#endif

void init_timer (void);

uint64_t get_timer_ticks (void);
uint64_t us_elapsed (void);
uint64_t us_since (const uint64_t timer_tick);
void clear_timer (void);


#endif

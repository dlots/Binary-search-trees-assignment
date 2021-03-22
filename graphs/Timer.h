//
//  https://ravesli.com/urok-129-tajming-koda-vremya-vypolneniya-programmy/
//

#ifndef SEMINAR_LAB2_TIMER_H
#define SEMINAR_LAB2_TIMER_H

#include <chrono>


class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(clock_t::now() - m_beg).count();
    }
};

#endif //SEMINAR_LAB2_TIMER_H

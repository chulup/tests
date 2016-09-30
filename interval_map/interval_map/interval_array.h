#pragma once

#include <vector>

template<class V, int Start=0, int End=10>
class interval_array {
private:
    std::vector<V> m_vector;
public:
    interval_array(V const& val) :
        m_vector(End - Start) {
        assign(Start, End, val);
    }

    void assign(size_t keyBegin, size_t keyEnd, const V& val) {
        auto current = keyBegin - Start,
            end = keyEnd - Start;
        for (; current < end; ++current) {
            m_vector[current] = val;
        }
    }

    V const& operator[](size_t key) const {
        return m_vector[key];
    }
};

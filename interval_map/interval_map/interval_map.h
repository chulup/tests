#pragma once

#include <limits>
#include <map>

template<class K, class V>
class interval_map {
private:
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map(V const& val) {
        m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
    };

    // Assign value val to interval [keyBegin, keyEnd). 
    // Overwrite previous values in this interval. 
    // Do not change values outside this interval.
    // Conforming to the C++ Standard Library conventions, the interval 
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval, 
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, const V& val) {
        if (!(keyBegin < keyEnd)) {
            return;
        }
        // First search
        // Try to insert end of interval. Value doesn't matter here
        auto end_pair = m_map.insert(std::pair<K, V>(keyEnd, val));
        if (end_pair.second) {
            // End-of-interval was not in the map: set the value of predecessor
            auto before_end = end_pair.first;
            --before_end;
            end_pair.first->second = before_end->second;
        } // other case: we had already value set here -> do not change it

          // Second search
          // Try to insert start of the interval
        auto start_pair = m_map.insert(std::pair<K, V>(keyBegin, val));
        if (!start_pair.second) {
            // We already had smth here. Just set the value now
            start_pair.first->second = val;
        }

        // Remove everything inside the interval
        ++start_pair.first;
        m_map.erase(start_pair.first, end_pair.first);
    }

    // look-up of the value associated with key
    V const& operator[](K const& key) const {
        return (--m_map.upper_bound(key))->second;
    }
};
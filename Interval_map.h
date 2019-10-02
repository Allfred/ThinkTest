#pragma once
template<typename K, typename V>
class interval_map
{
public:
	std::map<K, V> m_map;
public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val)
	{
		m_map.insert(m_map.end(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	// Assign value val to interval [keyBegin, keyEnd).
   // Overwrite previous values in this interval.
   // Conforming to the C++ Standard Library conventions, the interval
   // includes keyBegin, but excludes keyEnd.
   // If !( keyBegin < keyEnd ), this designates an empty interval,
   // and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val)
	{

		//I am not sure but i did it because the first key has value -2147483648 in constructor

		static bool isFirst = true;
		if (isFirst)
		{
			V v = m_map.begin()->second;
			m_map.erase(m_map.begin());
			m_map.insert(m_map.end(), std::make_pair(0, v));
			isFirst = false;
		}


		// Assign value val to interval [keyBegin, keyEnd).
		if (keyBegin > keyEnd) return;

		if (keyBegin < std::numeric_limits<K>::lowest())
		{
			throw "keyBegin out of keys";
		}
		/*The representation in the std::map must be canonical, that is, consecutive map entries must not have the
		same value : ..., (0, 'A'), (3, 'A'), ... is not allowed.Initially, the whole range of K is associated with a given initial
		value, passed to the constructor of the interval_map<K, V> data structure.*/

		auto lower_bound_throw_it = m_map.lower_bound(keyBegin);

		if (lower_bound_throw_it == m_map.end())
		{
			--lower_bound_throw_it;
		}

		if (lower_bound_throw_it->second == val)
		{

			throw "You can't add this value to the map because this value is already there before";
		}


		K maxKey = m_map.rbegin()->first;

		if (keyBegin > maxKey)
		{
			V element = m_map.rbegin()->second;
			for (K i = maxKey; i < keyBegin; ++i)
			{
				m_map.insert(m_map.end(), std::make_pair(i, element));
			}
			for (K i = keyBegin; i < keyEnd; ++i)
			{
				m_map.insert(m_map.end(), std::make_pair(i, val));
			}

		}
		else
		{
			if (keyEnd >= m_map.begin()->first)
			{
				auto lower_bound_it = m_map.lower_bound(keyBegin);

				std::map<K, V> map_helper_tail;

				map_helper_tail.insert(lower_bound_it, m_map.end());
				m_map.erase(lower_bound_it, m_map.end());

				for (K i = keyBegin; i < keyEnd; ++i)
				{
					m_map.insert(m_map.end(), std::make_pair(i, val));
				}
				K key = keyEnd;
				for (auto it = map_helper_tail.begin(); it != map_helper_tail.end(); ++it)
				{
					m_map.insert(m_map.end(), std::make_pair(key++, it->second));
				}
			}
			else
			{

				std::map<K, V> map_helper_tail;
				map_helper_tail.insert(m_map.begin(), m_map.end());
				m_map.clear();

				K end_i = map_helper_tail.begin()->first;

				for (K i = keyBegin; i < end_i; ++i)
				{
					m_map.insert(m_map.end(), std::make_pair(i, val));
				}
				m_map.insert(map_helper_tail.begin(), map_helper_tail.end());
			}
		}
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const
	{
		return (--m_map.upper_bound(key))->second;
	}
	// Many solutions we receive are incorrect. Consider using a randomized test
	// to discover the cases that your implementation does not handle correctly.
	// We recommend to implement a test function that tests the functionality of
	// the interval_map, for example using a map of unsigned int intervals to char.
};


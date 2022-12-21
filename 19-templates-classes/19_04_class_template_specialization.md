# 19.4 - Class template specialization

Specialize a template class for a particular data type (or data types, if there are
multiple template parameters).

Class template specializations are treated as completely independent classes, even though
they are allocated in the same way as the templated class. This means that we can change
anything and everything about our specialization class, including the way it's and even
the functions it makes public, just as if it were an independent class.

```c++
#include <cstdint>

template <typename T>
class Storage8
{
private:
    T m_array[8];

public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }

    const T& get(int index) const
    {
        return m_array[index];
    }
};

// Optimized to store 8 bools in one byte
template <> // the following is a template class with no templated parameters
class Storage8<bool> // we're specializing Storage8 for bool
{
private:
    std::uint8_t m_data { };

public:
    void set(int index, bool value)
    {
        // Figure out which bit we're setting/unsetting
        // This will put a 1 in the bit we're interested in turning on/off
        auto mask { 1 << index };

        if (value) // if we're setting the bit
        {
            m_data |= mask; // use bitwise-or to turn that bit on
        }
        else
        {
            m_data &= ~mask; // bitwise-and the inverse mask to turn that bit off
        }
    }

    bool get(int index)
    {
        auto mask { 1 << index };
        return (m_data & mask);
    }
};
```

Keeping the public interface between your template class and all of the specializations
similar is generally a good idea, as it makes them easier to use -- however, it is not
strictly necessary.

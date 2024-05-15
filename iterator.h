#pragma once

/* Abstract data type */
template <typename type>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual type nextObject() = 0;
};
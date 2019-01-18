#pragma once
#include "pch.h"
#include <stdexcept>

template<typename T>class optional
{
    bool mHasValue;
    T mValue;

public:
    optional() :
        mHasValue(false) {}

    optional(decltype(nullptr)) :
        mHasValue(false) {}

    optional(const T &value) :
        mHasValue(true), mValue(value) {}

    optional<T>& operator=(decltype(nullptr)) 
    {
        mHasValue = false;
        return *this;
    }
    optional<T>& operator=(const T &value)
    {
        mHasValue = true;
        mValue = value; 
        return *this;
    }

    bool operator ==(decltype(nullptr) x)const { return !mHasValue; }
    bool operator !=(decltype(nullptr))const { return mHasValue; }
    bool operator ==(const T &other)const
    {
        return mHasValue && mValue == other;
    }
    bool operator !=(const T &other)const
    {
        return !mHasValue || mValue != other;
    }
    bool operator ==(const optional<T> &other)const
    {
        return mHasValue == other.mHasValue && (!mHasValue || mValue == other.mValue);
    }
    bool operator !=(const optional<T> &other)const
    {
        return mHasValue != other.mHasValue || (mHasValue && mValue != other.mValue);
    }

    bool has_value()const { return mHasValue; }
    const T& value()const
    {
        if (!mHasValue)throw std::runtime_error("this is null, brah!");
        return mValue;
    }
    T& value()
    {
        if (!mHasValue)throw std::runtime_error("this is null, brah!");
        return mValue;
    }
};
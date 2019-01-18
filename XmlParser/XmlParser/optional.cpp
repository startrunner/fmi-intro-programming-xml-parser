#include "pch.h"
#include "optional.h"
using namespace std;

template<typename T>
inline optional<T>& optional<T>::operator=(decltype(nullptr))
{
    mHasValue = false;
}

template<typename T>
inline optional<T>& optional<T>::operator=(const T & value)
{
    mHasValue = true;
    mValue = value;
}

template<typename T>
inline bool optional<T>::operator==(decltype(nullptr) x)const
{
    return !mHasValue;
}

template<typename T>
inline bool optional<T>::operator!=(decltype(nullptr))const
{
    return mHasValue;
}

template<typename T>
inline bool optional<T>::operator==(const T & other)const
{
    return mHasValue && mValue == other;
}

template<typename T>
inline bool optional<T>::operator!=(const T & other)const
{
    return !mHasValue || mValue != other;
}

template<typename T>
bool optional<T>::operator==(const optional<T> &other)const
{
    return mHasValue == other.mHasValue && (mHasValue == false || mValue == other.value);
}

template<typename T>
bool optional<T>::operator!=(const optional<T>& other)const
{
    return mHasValue != other.mHasValue || (mHasValue && mValue != other.mValue);
}


template<typename T>
inline bool optional<T>::has_value() const
{
    return mHasValue;
}

template<typename T>
inline const T & optional<T>::value() const
{
    if (!mHasValue)throw runtime_error("Optional has no value!");
    return mValue;
}

template<typename T>
T & optional<T>::value()
{
    if (!mHasValue)throw runtime_error("Optional has no value!");
    return mValue;
}

template class optional<int>;
template class optional<bool>;
template class optional<string>;
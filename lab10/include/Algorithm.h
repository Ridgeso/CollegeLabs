#pragma once


template<typename T>
void swap(T& left, T& right)
{
    T temp = std::move(left);
    left = std::move(right);
    right = std::move(temp);
}

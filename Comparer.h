#pragma once
template <typename Type> static bool lt(Type* a, Type* b);//less than
template <typename Type> static bool lt(Type& a, Type& b);//less than
template <typename Type> static bool eq(Type* a, Type* b);//equal
template <typename Type> static bool eq(Type& a, Type& b);//equal
template <typename Type> static bool mt(Type* a, Type* b);//more than
template <typename Type> static bool mt(Type& a, Type& b);//more than
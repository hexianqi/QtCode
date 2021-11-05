/***************************************************************************************************
**      2021-11-01  宏定义
***************************************************************************************************/

#pragma once

#define ToVariant(Value)            QVariant::fromValue(static_cast<void *>(Value))
#define FromVariant(Class, Value)   static_cast<Class *>(Value.value<void *>())

#define H_DECLARE_PRIVATE(Class, T) \
    inline Class##Private<T> *d_func() { return reinterpret_cast<Class##Private<T> *>(qGetPtrHelper(this->d_ptr)); } \
    inline const Class##Private<T> *d_func() const { return reinterpret_cast<const Class##Private<T> *>(qGetPtrHelper(this->d_ptr)); } \
    friend class Class##Private<T>;

#define H_D(Class, T) Class##Private<T> * const d = d_func()

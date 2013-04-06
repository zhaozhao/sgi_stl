/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new>

__STL_BEGIN_NAMESPACE

// construct and destroy.  These functions are not part of the C++ standard,
// and are provided for backward compatibility with the HP STL.  We also
// provide internal names _Construct and _Destroy that can be used within
// the library, so that standard-conforming pieces don't have to rely on
// non-standard extensions.

// Internal names
//本文件中，construct,destroy为全局函数接口

/* __p指向申请的内存的指针,目标构造类型为_T1，__value表示初始化式
 * construct为_Construct函数的封装
 */
template <class _T1, class _T2>
inline void _Construct(_T1* __p,const _T2& __value)
{
	new ((void*) __p) _T1(__value);
}
template <class _T1>
inline void _Construct(_T1* __p)
{
	new((void*) __p) _T1();
}
template <class _T1, class _T2>
inline void construct(_T1* __p, const _T2& __value)
{
	_Construct(__p, __value);
}
template <class _T1>
inline void construct(_T1* __p)
{
	_Construct(__p);
}

/* __pointer指向被释放的对象的指针
 * 前一个函数为后一个函数的包装
 * __pointer必须为指针 外部调用时 
 * destroy(&* iterator)可以确保这一点
 */
template <class _Tp>
inline void _Destroy(_Tp* __pointer)
{
	__pointer->~_Tp();
}
template <class _Tp>
inline void destroy(_Tp* __pointer)
{
	_Destroy(__pointer);
}

template <class _ForwardIterator>
void
__destroy_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type)
{
	for( ; __first!=__last ; ++__first )
		destroy(&*__first);
}
	
/* destroy为外包装
 * _Destroy重载特化 char int long float double
 * __destroy选择是否有析构函数
 * __destroy_aux根据是否有析构函数来特化
 */
template <class _ForwardIterator>
inline void __destroy_aux(_ForwardIterator, _ForwardIterator,__true_type) {}
template <class _ForwardIterator, class _Tp>
inline void
__destroy(_ForwardIterator __first, _ForwardIterator __last, _Tp*)
{
	typedef typename __type_traits<_Tp>::has_trivial_destructor
		_Trivial_destructor;
	__destroy_aux(__first, __last, _Trivial_destructor());
}

template <class _ForwardIterator>
inline void _Destroy(_ForwardIterator __first,_ForwardIterator __last)
{
	__destroy(__first, __last, __VALUE_TYPE(__first));
}
inline void _Destroy(char*, char*) {}
inline void _Destroy(int*, int*) {}
inline void _Destroy(long*, long*) {}
inline void _Destroy(float*, float*) {}
inline void _Destroy(double*, double*) {}
#ifdef __STL_HAS_WCHAR_T
inline void _Destroy(wchar_t*, wchar_t*) {}
#endif /* __STL_HAS_WCHAR_T */
template <class _ForwardIterator>
inline void destroy(_ForwardIterator __first,_ForwardIterator __last)
{
	_Destroy(__first, __last);
}
__STL_END_NAMESPACE
#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

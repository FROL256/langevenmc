












#include <kiam.hpp>

#ifndef _KLBC_BASE_HPP_
#define _KLBC_BASE_HPP_

KIAM_NAMESPACE_START


template <class T>
inline void Swap(T &u, T &v);


template <class T>
inline T Min(const T &u, const T &v);


template <class T>
inline T Min3(const T &u, const T &v, const T &w);


template <class T>
inline T Max(const T &u, const T &v);


template <class T>
inline T Max3(const T &u, const T &v, const T &w);








template <class T>
inline void Swap(T &u, T &v)
  {
  T temp = u;
  u = v;
  v = temp;
  }









template <class T>
inline T Min(const T &u, const T &v)
  {
  return (u < v) ? u : v;
  }










template <class T>
inline T Min3(const T &u, const T &v, const T &w)
  {
  return Min(u, Min(v, w));
  }









template <class T>
inline T Max(const T &u, const T &v)
  {
  return (u > v) ? u : v;
  }










template <class T>
inline T Max3(const T &u, const T &v, const T &w)
  {
  return Max(u, Max(v, w));
  }

KIAM_NAMESPACE_END
#endif

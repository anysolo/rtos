#ifndef _anysolo_mclib_carray_h_
#define _anysolo_mclib_carray_h_

#include <anysolo/mclib/base.h>
#include <anysolo/mclib/assert.h>


namespace mclib {

template <typename T>
class CArray
{
  T*      m_data;
  int     m_size;

  void assertIndex(int n) const     {O_ASSERT(n >= 0 && n < m_size);}
  T& ref(int n)                     {assertIndex(n); return m_data[n];}
  const T& ref(int n) const         {assertIndex(n); return m_data[n];}

  // disable copy
  CArray(const CArray&);
  CArray& operator=(const CArray&);

public:
  CArray(T* data, int size);
  CArray(Buf& buf)                  {m_data = buf.buf(); m_size = buf.size() / sizeof(T);}

  int size() const                  {return m_size;}

  T& operator[] (int n)             {return ref(n);}
  const T& operator[] (int n) const {return ref(n);}

  T* rowData()                      {return m_data;}
};

template <typename T>
CArray<T>::CArray(T* data, int size)
{
  O_ASSERT(data != 0 || size == 0);
  m_data = data;
  m_size = size;

#ifdef _DEBUG
  for(int i = 0; i < size; ++i)
    m_data[i] = T();
#endif
}

} // namespace mclib

#endif // _anysolo_mclib_carray_h_

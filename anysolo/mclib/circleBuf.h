#ifndef _olibs_circleBuf_h_
#define _olibs_circleBuf_h_


#include <exception>

#include <olibs/assert.h>
#include <olibs/buf.h>


class ByteCircleBuf
{
public:
  class NoSpaceEx : public std::exception
  {
  public:
    virtual const char* what() const throw() {return "ByteCircleBuf::NoSpaceEx";}
  };

  class NoDataEx : public std::exception
  {
  public:
    virtual const char* what() const throw() {return "ByteCircleBuf::NoDataEx";}
  };

private:
  Olibs::Buf    m_data;
  int           m_usedSize;
  int           m_offsetPut;
  int           m_offsetGet;

public:
  ByteCircleBuf(int size):
    m_data(size)
  {
    clear();
  }

  void clear()
  {
    m_usedSize  = 0;
    m_offsetPut = 0;
    m_offsetGet = 0;
  }

  int getSize() const       {return m_data.size();}
  int getFreeSize() const   {return getSize() - getUsedSize();}
  int getUsedSize() const   {return m_usedSize;}
  bool isEmpty() const      {return getUsedSize() == 0;}
  bool isFull() const       {return getUsedSize() == getSize();}

  void put(Byte b)
  {
    if(isFull())
      throw NoSpaceEx();

    O_ASSERT(m_offsetPut <= getSize() - 1);

    m_data[m_offsetPut ++] = b;
    ++m_usedSize;
    O_ASSERT(m_usedSize <= getSize());

    if(m_offsetPut == getSize())
      m_offsetPut = 0;

    O_ASSERT(m_offsetPut <= getSize() - 1);
  }

  Byte get()
  {
    if(isEmpty())
      throw NoDataEx();

    O_ASSERT(m_offsetGet <= getSize() - 1);

    Byte b = m_data[m_offsetGet ++];
    --m_usedSize;
    O_ASSERT(m_usedSize >= 0);

    if(m_offsetGet == getSize())
      m_offsetGet = 0;

    O_ASSERT(m_offsetGet <= getSize() - 1);

    return b;
  }

  void put(const Byte* data, int size)
  {
    O_ASSERT(size <= getFreeSize());

    for(int i = 0; i < size; ++i)
      put(data[i]);
  }

  int get(Byte* data, int len)
  {
    if(len > getUsedSize())
      len = getUsedSize();

    for(int i = 0; i < len; ++i)
      data[i] = get();

    return len;
  }
};


#endif // _olibs_circleBuf_h_

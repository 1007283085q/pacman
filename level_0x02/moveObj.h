#ifndef CMOVEOBJHEADER
#define CMOVEOBJHEADER
#pragma once
#include "pacMan.h"
#include "gameElement.h"

class CMoveObj :
  public CGameElement
{
public:
  CMoveObj();
  CMoveObj(int nRow , int nCol);
  virtual ~CMoveObj();
  // ����ʱ�䣬������ʱ���Ƿ���ڶ����ٶ�
  virtual int updateClock();
  // �ƶ�
  virtual int move();
protected:
  clock_t m_nSpead;
  clock_t m_nPreMoveClock;
};

#endif // CMOVEOBJHEADER
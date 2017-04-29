#include "moveObj.h"


CMoveObj::CMoveObj()
  : CGameElement() , m_nSpead(0) , m_nPreMoveClock(0)
{
}

CMoveObj::CMoveObj(int nRow , int nCol)
  : CGameElement(nRow, nCol) , m_nSpead(0) , m_nPreMoveClock(0)
{
  m_nPreMoveClock = -1 ^ (1 << (sizeof(clock_t) * 8 - 1));
}

CMoveObj::~CMoveObj()
{
}

// ����ʱ�䣬������ʱ���Ƿ���ڶ����ٶ�
int CMoveObj::updateClock()
{
  return 0;
}


// �ƶ�
int CMoveObj::move()
{
  return 0;
}

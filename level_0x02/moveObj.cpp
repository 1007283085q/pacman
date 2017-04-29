#include "moveObj.h"


CMoveObj::CMoveObj()
  : CGameElement() , m_nSpead(0) , m_nPreMoveClock(0)
{
}

CMoveObj::CMoveObj(int nRow , int nCol)
  : CGameElement(nRow, nCol) , m_nSpead(0) , m_nPreMoveClock(0)
{
  // ���󣬽���ʼ�ٶ���Ϊ���ᵼ���߼�����
  // m_nPreMoveClock = -1 ^ (1 << (sizeof(clock_t) * 8 - 1));
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
  // ����ұ���ץ����ʱ�����Ͳ����ٶ���
  // ������ڽ���ڲ�·��ʱ���⵽��ץ����ң�
  // �����ȴû�м�⵽����ץ��
  // ��Ϊ�߼����ǹ���������ƶ��ģ����Թ��������������
  if(m_nType == CGame::itemPlayer && g_isBeEat == 1)
  {
    return 0;
  }

  if(updateClock() == 0)
  {
    return 0;
  }
  int nCrash = isCrash();
  if(nCrash == CGame::craPass)
  {
    m_postion = m_postion.getActionPostion(m_nAction);
  }
  return 0;
}

// �����ٶ�
void CMoveObj::setSpead(int nSpead)
{
  m_nSpead = nSpead;
}

// ��λ
void CMoveObj::backPos()
{

}

#include "ghost.h"


CGhost::CGhost(int nRow, int nCol)
  : CMoveObj(nRow , nCol) , m_nWhatGhost(0)
{
  static int nNum = CGame::itemGhoRed;
  m_nWhatGhost = nNum++;
  m_nType = CGame::itemGhoNormal;
  m_nAction = CGame::actUp;
  m_nSpead = g_nInitGhoSpead;
}


CGhost::~CGhost()
{
}


IGameElement* CGhost::creatSelf(int nRow, int nCol)
{
  return NULL;
}

// ��ȡ����
const int CGhost::getType()
{
  return (m_nType == CGame::itemGhoNormal) ?
          m_nWhatGhost : m_nType;
}


// ����־�ģʽ
void CGhost::toFear()
{
}

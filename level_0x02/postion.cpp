#include "postion.h"


CPostion::CPostion()
  : m_nRow(0) , m_nCol(0)
{
}

CPostion::CPostion(int nRow , int nCol)
  : m_nRow(nRow) , m_nCol(nCol)
{

}

CPostion::CPostion(CPostion& obj)
{
  m_nRow = obj.m_nRow;
  m_nCol = obj.m_nCol;
}

CPostion::~CPostion()
{
}

// ��ȡ��Ӧ��������
int& CPostion::operator[](int nIndex)
{
  return (nIndex == CGame::posRow) ? m_nRow : m_nCol;
}


// ���긳ֵ
void CPostion::operator=(CPostion& obj)
{
  m_nRow = obj.m_nRow;
  m_nCol = obj.m_nCol;
}


// �ж������Ƿ����
int CPostion::operator==(CPostion& obj)
{
  if(m_nRow == obj.m_nRow)
  {
    if(m_nCol == obj.m_nCol)
    {
      return 1;
    }
  }
  return 0;
}


// ��������
void CPostion::set(int nRow , int nCol)
{
  m_nRow = nRow;
  m_nCol = nCol;
}


// ��ȡ��������¸�����
CPostion CPostion::getActionPostion(int nAction)
{
  CPostion nextPos = *this;
  // ����Ԫ��Rowλ��
  nextPos[ CGame::posRow ] += ((2 & nAction) != 0) ? 0 :
    (((1 & nAction) == 0) ? -1 : 1);

  // ����Ԫ��Colλ��
  nextPos[ CGame::posCol ] += ((2 & nAction) == 0) ? 0 :
    (((1 & nAction) == 0) ? -1 : 1);

  nextPos[ CGame::posRow ] += (nextPos[ CGame::posRow ] < 0) ? g_nMapRow : 0;
  nextPos[ CGame::posCol ] += (nextPos[ CGame::posCol ] < 0) ? g_nMapCol : 0;

  nextPos[ CGame::posRow ] %= g_nMapRow;
  nextPos[ CGame::posCol ] %= g_nMapCol;

  return nextPos;
}

// ���ݷ����޸�����
void CPostion::changePostion(int nAction)
{
  *this = getActionPostion(nAction);
}

#include "gameElement.h"


CGameElement::CGameElement()
  : m_nAction(0) , m_postion() , m_nType(0)
{
}

CGameElement::CGameElement(int nRow , int nCol)
  : m_nAction(0) , m_postion(nRow , nCol) , m_nType(0)
{

}


CGameElement::~CGameElement()
{
}


// ��ȡ��������
int& CGameElement::operator[](int nIndex)
{
  //TODO: insert return statement here
  return m_postion[nIndex];
}

// ����������Ƚ���ײ�ȼ�
const int CGameElement::operator==(IGameElement& obj)
{

  return 0;
}


// ��ȡ����
const int CGameElement::getType()
{
  return m_nType;
}


// �ƶ�
int CGameElement::move()
{
  return 0;
}

// �ı䷽��
int CGameElement::changeAction(int nAct)
{
  return 0;
}

// ��ײ���
const int CGameElement::isCrash()
{
  return 0;
}


// ײ�����Լ���ײ�ȼ��ߵ�
void CGameElement::beHit()
{
}


// ײ�����Լ���ײ�ȼ��͵�
void CGameElement::hitAnthor()
{
}

// ��������
IGameElement* CGameElement::creatSelf(int nRow, int nCol)
{
  return new CGameElement();
}
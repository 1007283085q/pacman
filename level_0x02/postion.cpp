#include "postion.h"


CPostion::CPostion()
  : m_nRow(0) , m_nCol(0)
{
}

CPostion::CPostion(int nRow , int nCol)
  : m_nRow(nRow) , m_nCol(nCol)
{

}

CPostion::~CPostion()
{
}


// ��ʼ����ͼ
void CPostion::initMap()
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
}


// �ж������Ƿ����
int CPostion::operator==(CPostion& obj)
{
  return 0;
}


// ��������
void CPostion::set(int nRow , int nCol)
{
}


// ��ȡ��������¸�����
CPostion& CPostion::getActionPostion(int nAction)
{
  //TODO: insert return statement here
  return *this;
}


// ���ݷ����޸�����
void CPostion::changePostion(int nAction)
{
}

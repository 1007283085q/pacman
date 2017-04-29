#ifndef POSTIONHEADER
#define POSTIONHEADER
#pragma once
#include "game.h"

class CPostion
{
public:
  CPostion();
  CPostion(int nRow , int nCol);
  CPostion(CPostion& obj);
  ~CPostion();
  // ��ȡ��Ӧ��������
  int& operator[](int nIndex);
  // ���긳ֵ
  void operator=(CPostion& obj);
  // �ж������Ƿ����
  int operator==(CPostion& obj);
  // ��������
  void set(int nRow , int nCol);
  // ��ȡ��������¸�����
  CPostion getActionPostion(int nAction);
  // ���ݷ����޸�����
  void changePostion(int nAction);

private:
  int m_nRow;
  int m_nCol;
};

#endif // POSTIONHEADER
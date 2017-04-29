#pragma once
#include "pacMan.h"
#include "moveObj.h"

class CGhost :
  public CMoveObj
{
public:
  CGhost(int nRow, int nCol);
  virtual ~CGhost();
  virtual IGameElement* creatSelf(int nRow, int nCol);
  // ��ȡ����
  virtual const int getType();
  // ����־�ģʽ
  static void toFear();

private:
  int m_nWhatGhost;
};


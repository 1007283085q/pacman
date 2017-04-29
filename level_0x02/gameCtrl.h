#ifndef CGAMECTRLHEADER
#define CGAMECTRLHEADER
#pragma once

#include "pacMan.h"

class CGameCtrl
{
public:
  // �����ഴ������
  SINGLE_INSTANCE_STAT(CGameCtrl);

  void gameStart();
  void gameLoop();

  // ���״̬
  int checkStatus();

  // ����ҳԵ�������
  void whenPlayerEatSuperPean();
  // �������ײ�־�ʱ�Ĺ�
  void whenPlayerEatGhost();
  // �������ײ������
  void whenGhostEatPlayer();

private:
  CGameCtrl();
  virtual ~CGameCtrl();

  CGetCGameUI*   m_getUIObj;
  CGetCGameMap*  m_getMapObj;
  CGameUI*       m_uiObj;
  CGameMap*      m_mapObj;
  IGameElement** m_moveObj;
  CGhost**       m_ghostObj;
  CPlayer*       m_playerObj;
};

// �������������
CREATE_SINGLE_OBJ(CGameCtrl);

#endif // CGAMECTRLHEADER
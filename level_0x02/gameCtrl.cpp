#include "gameCtrl.h"

// �����ഴ������
SINGLE_INSTANCE(CGameCtrl);

CGameCtrl::CGameCtrl()
{
  m_getUIObj = new CGetCGameUI;
  m_getMapObj = new CGetCGameMap;
  m_uiObj = m_getUIObj->get();
  m_mapObj = m_getMapObj->get();
  m_moveObj = m_mapObj->getMoveObj();
  m_ghostObj = (CGhost**)m_mapObj->getMoveObj();
  m_playerObj = (CPlayer*)m_moveObj[ g_nGhost ];

  g_gameMap = m_mapObj;
}


CGameCtrl::~CGameCtrl()
{
  delete m_getUIObj;
  delete m_getMapObj;
  g_gameMap = NULL;
}

void CGameCtrl::gameStart()
{

}

void CGameCtrl::gameLoop()
{
  static clock_t nPreTime = 0;
  static const clock_t nRefreshTime = 200;
  static clock_t nowTime = 0;
  static char ch;

  m_mapObj->show(m_uiObj , &CGameUI::echoMap);
  while(1)
  {
    if(_kbhit())
    {
      ch = _getch();
      switch(ch)
      {
        case 'w':
        case 'W':
          m_playerObj->changeAction(CGame::actUp);
          break;
        case 'a':
        case 'A':
          m_playerObj->changeAction(CGame::actLeft);
          break;
        case 's':
        case 'S':
          m_playerObj->changeAction(CGame::actDown);
          break;
        case 'd':
        case 'D':
          m_playerObj->changeAction(CGame::actRight);
          break;
      }
    }

    nowTime = clock();
    if(nowTime - nRefreshTime < nPreTime)
    {
      continue;
    }
    nPreTime = nowTime;

    if(checkStatus() == 1)
    {
      break;
    }

    for(int i = 0; i < g_nGhost + g_nPlayer; ++i)
    {
      m_moveObj[ i ]->move();
    }

    changeGhostAct();

    m_uiObj->echoGameInfo(m_playerObj->getScore() , g_nGhostLevel , m_playerObj->getlife());

    m_mapObj->show(m_uiObj , &CGameUI::echoMap);
  }
}

// ���״̬
int CGameCtrl::checkStatus()
{
  m_playerObj->addScore(g_nAddScore);
  g_nAddScore = 0;

  if(g_isBeEat == 1)
  {
    whenGhostEatPlayer();
  }
  else if(g_nGhostBeEat > 0)
  {
    whenPlayerEatGhost();
  }
  else if(g_nSuperPeanBeEat > 0)
  {
    whenPlayerEatSuperPean();
  }

  checkPlayerScore();

  if(m_playerObj->getlife() == 0)
  {
    return 1;
  }

  if(g_nEatPeanNum >= g_nPean)
  {
    whenAllPeanBeEat();
    return 1;
  }

  return 0;
}

// ����ҳԵ�������
void CGameCtrl::whenPlayerEatSuperPean()
{
  static clock_t nowTime = 0;
  static const int nSuperPeanNum = 1;
  static int nTimeIsUpdate = 0;

  if(nTimeIsUpdate == 0)
  {
    g_nFearStartTime = clock();
    nTimeIsUpdate = 1;

    for(int i = 0; i < g_nGhost; ++i)
    {
        m_ghostObj[ i ]->toFear();
    }
  }

  if(g_nSuperPeanBeEat > nSuperPeanNum)
  {
    g_nFearStartTime += g_nGhostFearTime;
    --g_nSuperPeanBeEat;
  }

  nowTime = clock();
  if(nowTime - g_nGhostFearTime >= g_nFearStartTime)
  {
    nTimeIsUpdate = 0;
    g_nSuperPeanBeEat = 0;
    for(int i = 0; i < g_nGhost; ++i)
    {
      if(m_ghostObj[ i ]->getType() != CGame::itemGhoDie)
      {
        m_ghostObj[ i ]->changeType(CGame::itemGhoNormal);
      }
    }
  }
}

// �������ײ�־�ʱ�Ĺ�
void CGameCtrl::whenPlayerEatGhost()
{
  static int nScore = PLAYEREATGHOSTSCORE;;
  char szBuff[ 0x20 ] = { 0 };
  sprintf_s(szBuff , 0x20 , "��ҵ÷֣�%d" , nScore);
  m_uiObj->echoGameMessage(szBuff);

  g_nFearStartTime += 1200;

  nScore = (int)(nScore * g_fMagScore);
  
  g_nGhostBeEat -= 1;
}

// �������ײ������
void CGameCtrl::whenGhostEatPlayer()
{
  m_uiObj->echoGameMessage("�Զ��˱�ץ����");

  g_isBeEat = 0;
  g_nGhostBeEat = 0;
  g_nSuperPeanBeEat = 0;

  // ��ҡ����λ
  for(int i = 0; i < g_nGhost + g_nPlayer; ++i)
  {
    ((CMoveObj*)m_moveObj[ i ])->backPos();
  }
}

// ����ҳ������ж���
void CGameCtrl::whenAllPeanBeEat()
{
  m_uiObj->echoGameMessage("�Զ��˳Ա�����");
  // todo ..
}

// �����ҷ�����������
void CGameCtrl::checkPlayerScore()
{
  static int nSpead = g_nInitGhoSpead;
  if(m_playerObj->getScore() > 100 * g_nGhostLevel && g_nGhostLevel < 4)
  {
    nSpead -= 50;
    g_nGhostLevel += 1;
    for(int i = 0; i < g_nGhost; ++i)
    {
      m_ghostObj[ i ]->setSpead(nSpead);
    }
  }
}

// �ı��ķ���
void CGameCtrl::changeGhostAct()
{
  static clock_t nPreTime = 0;
  clock_t nowTime = clock();
  if(nowTime - m_ghostObj[0]->getSpead() < nPreTime)
  {
    return;
  }
  nPreTime = nowTime;
  int nAct = 0;
  CPostion dstPos;
  // ��ͼ���ĸ����䣬������ֻ�������ģʽ�ͻƹ��Ѳ�߽���
  static CPostion mapFourNook[ 4 ];
  mapFourNook[ 0 ].set(5 , 6);
  mapFourNook[ 1 ].set(5, g_nMapCol - 7);
  mapFourNook[ 2 ].set(g_nMapRow - 5 , 6);
  mapFourNook[ 3 ].set(g_nMapRow - 5 , g_nMapCol - 7);
  static int ghostInNook[ 4 ] = { 0 };

  for(int i = 0; i < g_nGhost; ++i)
  {
    // ����ÿ�����׷��Ŀ��
    if(m_ghostObj[i]->getType() == CGame::itemGhoRed)
    {
      // ���׷�����
      nAct = findAction(m_ghostObj[i]->getPos(), m_playerObj->getPos(), m_ghostObj[i]->getAction());
    }
    else if(m_ghostObj[i]->getType() == CGame::itemGhoYell)
    {
      // �ƹ�׷�����
      // ���ж�����Ƿ������׷�ٷ�Χ����ֻ��ԭ���������Զ�˾�׷��ң����˾Ͳ�׷��
      // ��Խ���
      dstPos = m_ghostObj[ i ]->getPos() - m_playerObj->getPos();
      // dstPos.amend();
      if(dstPos[ CGame::posRow ] * dstPos[CGame::posRow] + dstPos[CGame::posCol] * dstPos[CGame::posCol] > 128)
      {
        // ׷�����
        nAct = findAction(m_ghostObj[i]->getPos(), m_playerObj->getPos(), m_ghostObj[i]->getAction()); 
      }
      else
      {
        // �Լ����Լ�������
        nAct = findAction(m_ghostObj[i]->getPos(), mapFourNook[0], m_ghostObj[i]->getAction()); 
      }
    }
    else if(m_ghostObj[ i ]->getType() == CGame::itemGhoPink)
    {
      // �۹�׷�����
      // ��ȡ��ҳ���ĵ�4�����꣬���2������
      dstPos = m_playerObj->getPos();
      for(int j = 0; j < 4; ++j)
      {
        dstPos = dstPos.getActionPostion(m_playerObj->getAction());
      }
      dstPos = dstPos.getActionPostion(CGame::actLeft);
      dstPos = dstPos.getActionPostion(CGame::actLeft);
      nAct = findAction(m_ghostObj[i]->getPos(), dstPos, m_ghostObj[i]->getAction());
    }
    else if(m_ghostObj[i]->getType() == CGame::itemGhoBlue)
    {
      // ����׷�����
      // ��ȡ��ҳ���ĵ�2������
      dstPos = m_playerObj->getPos();
      for(int j = 0; j < 2; ++j)
      {
        dstPos = dstPos.getActionPostion(m_playerObj->getAction());
      }
      // ��ȡ������ҳ����ǰ����������
      dstPos = m_ghostObj[ CGame::itemGhoRed - CGame::itemGhoRed ]->getPos() - dstPos;
      // ����������
      dstPos = dstPos * 2;
      // ��λ��������ҳ����ǰ��������ߵ�2���ӳ��ߵ�����
      dstPos = m_ghostObj[ CGame::itemGhoRed - CGame::itemGhoRed ]->getPos() + dstPos;

      nAct = findAction(m_ghostObj[i]->getPos(), dstPos, m_ghostObj[i]->getAction());
    }
    // ������ʱ���ؼ�
    else if(m_ghostObj[ i ]->getType() == CGame::itemGhoDie)
    {
      // ����ֻ��Ŀ�궨�ڹ���в�ͬλ��
      dstPos.set(g_nFirstGhoRow + (i % 2) , g_nFirstGhoCol + ((i - 1) / 2) * 4);
      nAct = findAction(m_ghostObj[i]->getPos(), dstPos, m_ghostObj[i]->getAction());
    }
    // ��־�״̬ʱ�������ԵĽ���ȥ
    else if(m_ghostObj[ i ]->getType() == CGame::itemGhoFear)
    {
      // �ƹ�����ؼ�
      if(m_ghostObj[ i ]->getWhatGhost() == CGame::itemGhoYell || m_ghostObj[i]->getWhatGhost() == CGame::itemGhoRed)
      {
        dstPos.set(g_nFirstGhoRow + 1, g_nFirstGhoCol + 1);
        nAct = findAction(m_ghostObj[i]->getPos(), dstPos, m_ghostObj[i]->getAction());
      }
      // �����۹��Լ��Ľ���ȥ
      else
      {
        // ����λ��״̬ѡ��Ŀ�����
        if(ghostInNook[ m_ghostObj[ i ]->getWhatGhost() - CGame::itemGhoRed ] == 0)
        {
          dstPos = mapFourNook[ m_ghostObj[ i ]->getWhatGhost() - CGame::itemGhoRed ];
        }
        else
        {
          dstPos = mapFourNook[ m_ghostObj[ i ]->getWhatGhost() - CGame::itemGhoRed - 1 ];
        }
        // ������һ������
        if(dstPos == m_ghostObj[ i ]->getPos())
        {
          // �л�λ��״̬
          ghostInNook[ m_ghostObj[ i ]->getWhatGhost() - CGame::itemGhoRed ] =
            (ghostInNook[ m_ghostObj[ i ]->getWhatGhost() - CGame::itemGhoRed ] == 0) ?
            1 : 0;
        }
        
        nAct = findAction(m_ghostObj[i]->getPos(), dstPos, m_ghostObj[i]->getAction());
      }
    }
    m_ghostObj[ i ]->changeAction(nAct);
  }
}

// Ѱ·�㷨
int CGameCtrl::findAction(CPostion srcPos , CPostion dstPos, int nAct)
{
  /********************************************
  * �����㷨��Ŀ�ľ���Ϊ��֪����һ�������Ǹ�������
  * �������еĲ�����Χ�Ʊ�����ȷ�ķ���Ϊ��
  * ���Ҳ����Ҫ�����߹���·��
  *********************************************/
  
  // �жϴ��������Ƿ���ȷ
  while(true)
  {
    // ���������ݺϷ���
    dstPos.amend();
    // ���������Ƿ���ǽ
    if(((*g_gameMap)[ dstPos[ CGame::posRow ] ][ dstPos[ CGame::posCol ] ])->getType() != CGame::itemWall)
    {
      break;
    }
    // �����ǽ�ͽ��������䷽���ƶ�һ�������ж�
    dstPos = dstPos.getActionPostion(CGame::actDown);
  }

  // ��ͼ���飬���ڱ����߹���·
  int nPassPostion[ MAPROW ][ MAPCOL ] = { 0 };

  // Ѱ·״̬���ṹ�壬���ﲻ��CPostion�����ˣ�Ӱ��Ч��
  typedef struct FindState
  {
    int nRow;
    int nCol;
    enum CGame::gameAction myAction;
    enum CGame::gameAction firstAction;
  } FindState;

  // ����״̬������飬���ڱ���Ѱַ��Ϣ
  FindState* nowStateArr = new FindState[ 300 ];
  FindState* preStateArr = new FindState[ 300 ];
  FindState* pTempArr;
  // ���������±�
  int nNowArrCur = -1;
  int nPreArrCur = -1;

  // ����һֻ������ģ��·��
  CGhost moveGho(srcPos[ CGame::posRow ] , srcPos[ CGame::posCol ]);
  moveGho.changeType(CGame::itemGhoTremble);
  moveGho.setSpead(0);

  // ��ʼ������Ϣ
  ++nPreArrCur;
  preStateArr[ nPreArrCur ].nRow = srcPos[ CGame::posRow ];
  preStateArr[ nPreArrCur ].nCol = srcPos[ CGame::posCol ];
  preStateArr[ nPreArrCur ].myAction = CGame::actUp;
  preStateArr[ nPreArrCur ].firstAction = CGame::actUp;
  nPassPostion[ srcPos[ CGame::posRow ] ][ srcPos[ CGame::posCol ] ] = 1;

  int nFindNum = 0;

  CPostion tempPos;
  int nNewRow;
  int nNewCol;
  int nRet = 0;
  while(true)
  {
    // �ж��Ƿ񵽴�Ŀ�������
    for(int i = 0; i <= nPreArrCur; ++i)
    {
      tempPos.set(preStateArr[ i ].nRow , preStateArr[ i ].nCol);
      if((tempPos == dstPos) == 1)
      {
        nRet = preStateArr[ i ].firstAction;
        delete nowStateArr;
        delete preStateArr;
        // ��ģ����һ�������Ƿ񱻶�̬Ԫ�ص�סȥ· // �����ǹ�͹�����ײ�����ԾͲ���Ҫ��һ����
        // moveGho.getPos() = srcPos;
        // if(moveGho.changeAction(nRet) != 0)
        // {
        //   // ��һ������̬Ԫ�ص�סȥ·�������෴����
        //   nRet = (nAct <= 1) ? (nAct + 1) % 2  : (nAct - 3 + 1) % 2 + 3;
        // }
        return nRet;
      }
    }

    ++nFindNum;
    // �ӵ�ǰ״̬����Ѱ��
    for(int i = 0; i <= nPreArrCur && nPreArrCur >= 0; ++i)
    {
      // ��ȡ״̬����ֵ
      tempPos.set(preStateArr[ i ].nRow , preStateArr[ i ].nCol);
      
      // �����ĸ�����
      for(int j = CGame::actUp; j <= CGame::actRight; ++j)
      {
        // ���¹��������Ϣ��׼��ģ��
        moveGho.getPos() = tempPos;

        // �ж��Ƿ񱻾�̬Ԫ�ص�ס·
        if(moveGho.changeAction(j, 2) != 0)
        {
          // ���ܳ��÷����ƶ�
          continue;
        }

        // �����ƶ�������������Ϣ
        moveGho.getPos() = tempPos.getActionPostion(j);
        
        // ��ȡ�ƶ����������
        nNewRow = moveGho.getPos()[ CGame::posRow ];
        nNewCol = moveGho.getPos()[ CGame::posCol ];

        // ���״�
        if(nFindNum > 1 && nPassPostion[ nNewRow ][ nNewCol ] == 0)
        {
          ++nNowArrCur;
          nowStateArr[ nNowArrCur ].nRow = nNewRow;
          nowStateArr[ nNowArrCur ].nCol = nNewCol;
          nowStateArr[ nNowArrCur ].myAction = (enum CGame::gameAction)j;
          // �ؼ�����һ��������ǰһ״̬�м�¼�ĳ�ʼ����
          nowStateArr[ nNowArrCur ].firstAction = preStateArr[i].firstAction;
          nPassPostion[ nNewRow ][ nNewCol ] = nFindNum;

        }
        // �״�
        else if(nFindNum == 1 && nPassPostion[ nNewRow ][ nNewCol ] == 0)
        {
          ++nNowArrCur;
          nowStateArr[ nNowArrCur ].nRow = nNewRow;
          nowStateArr[ nNowArrCur ].nCol = nNewCol;
          nowStateArr[ nNowArrCur ].myAction = (enum CGame::gameAction)j;
          nowStateArr[ nNowArrCur ].firstAction = (enum CGame::gameAction)j;
          nPassPostion[ nNewRow ][ nNewCol ] = nFindNum;
        }
      }
    }

    // ����Ѱַ״̬����ָ����ָ�ռ䣬�Ӷ����浱ǰ״̬������֮ǰ��״̬
    pTempArr = preStateArr;
    preStateArr = nowStateArr;
    nowStateArr = pTempArr;
    // ���������±�
    nPreArrCur = nNowArrCur;
    nNowArrCur = -1;
  }
}

// �������������
CREATE_SINGLE_OBJ_REALIZE(CGameCtrl);
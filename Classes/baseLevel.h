#ifndef _BASE_LEVEL
#define _BASE_LEVEL

#include "cocos2d.h"
#include"baseBlock.h"
#include"enemy.h"

/*
�ؿ�����
���ܣ�
1���������и��ӵ�λ��
2�����ĸ�������
3���洢����
4���洢����
5���洢�ܲ�Ѫ��
6��ʤ��/ʧ�ܽ���
7����ͣ����
*/
class baseLevel : public cocos2d::Scene
{
public:
//λ����������µ�����
#define BLOCK_X_NUM 14
#define BLOCK_Y_NUM 7
#define BLOCK_LEN 120

	int healthPoint;
	int money;
	int currentMoney;
	int currentWave;
	int maxWave;

	struct Spawn
	{
		int x;
		int y;
	}spawnPoint;

	//ÿһ���ε���Ϣ
	struct WaveList
	{
		//���ּ��ʱ��
		float spawnInterval;
		//����˳��
		Vector<enemy*> sequence;
	};

	Vector<PathBlock*> path;

	//�洢���в��ε���Ϣ
	std::vector<WaveList> wave;
	//ָ��ǰ���εĵ�����
	std::vector<WaveList>::iterator waveIter;
	//ָ�򼴽����ɵĹ���ĵ�����
	Vector<enemy*>::iterator currentIter;

	int coordToTag(int x, int y);

	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();
	//����������ĳ�ʼ��
	virtual void superInit();
	//�Գ������Լ�·����������
	virtual void spawnInit();
	//��ui��������
	virtual void uiInit();
	//�Բ�����Ϣ��������
	virtual void waveInit();
	//��ÿ֡���µ����ݽ�������
	virtual void scheduleInit();
	//�Զ�����һ������·��
	PathBlock* addPath(int x, int y);
	//���µ�ǰ���á����Ρ�Ѫ��
	void uiUpdate(float dt);
	//���³���
	void monsterSpawn(float dt);
	//������������һֻ����
	void spawnOne(float dt);
	//�жϵ�ǰ�Ƿ�ʤ��
	void winCheck(float dt);
	//���Ž��㻭��
	void winDisplay();
	void loseDisplay();
	//�жϵ�ǰ�������й����Ƿ��ѱ�����
	void checkElimination(float dt);
	

	CREATE_FUNC(baseLevel);
};

#endif // _BASE_LEVEL

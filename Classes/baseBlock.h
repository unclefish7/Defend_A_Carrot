#ifndef _BASE_BLOCK_H
#define _BASE_BLOCK_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TestBlock : public cocos2d::Sprite
{
public:
	//virtual bool init();
	static TestBlock* create();
	//virtual Sprite* newInstance();

	void onEnter();
	void onExit();

	//��괥���Ļص�����
	bool clickReact(cocos2d::Touch* touch, cocos2d::Event* event);
};


/*���ӻ���
���ܣ�
1������򿪽������
2�����ý���Ȩ��
3�����㵱ǰλ�õ������۸���������������Է������ʣ���Ǯ

*/
class BaseBlock : public cocos2d::Sprite
{
#define UNSELECTED_OPACITY 30
#define SELECTED_OPACITY 255

public:
	int cost;

	virtual bool init();

	static BaseBlock* create();


	//�볡ʱ����������˳�ʱ�Ƴ�����
	void onEnter();
	void onExit();

	//�ж��Ƿ�Ҫ�����ص�����
	bool judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event);
	//���������Ļص�����
	virtual void clickCallback();
	//��ʾһ������һС��ʱ��
	void scheduleFunc(float dt);
	//���õ�ǰ���ӵĺķ�
	int setCost(int m);
};


class PathBlock : public BaseBlock
{

public:
	PathBlock* link;

	virtual bool init();

	static PathBlock* create();

	//�볡ʱ����������˳�ʱ�Ƴ�����
	void onEnter();

	PathBlock* getNextPath();
};

#endif // _PATH_BLOCK_H

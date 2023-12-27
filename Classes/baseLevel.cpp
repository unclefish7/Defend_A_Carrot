#include"baseBlock.h"
#include "baseLevel.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include"enemy.h"

USING_NS_CC;

int baseLevel::coordToTag(int x, int y)
{
	return (y - 1) * BLOCK_X_NUM + x;
}

cocos2d::Scene* baseLevel::createScene()
{
	return baseLevel::create();
}

bool baseLevel::init()
{
	superInit();

	//设置怪物行走路径、起始点、萝卜位置
	spawnInit();

	//打印ui界面
	uiInit();

	//每帧都要更新的东西进行初始化
	scheduleInit();

	//初始化波次信息
	waveInit();

	monsterSpawn(1);

	return true;
}


void baseLevel::superInit()
{
	//设置各个变量的初始值
	currentMoney = money = 5000;
	healthPoint = 5;
	currentWave = 0;


	//初始化所有格子为空格子
	for (int i = 1; i <= BLOCK_X_NUM; ++i) {
		for (int j = 1; j <= BLOCK_Y_NUM; ++j) {
			auto block = BaseBlock::create();
			block->setTag(coordToTag(i, j));//格子的tag = (y - 1) * BLOCK_X_NUM + x
			block->setAnchorPoint(Vec2(0.5, 0.5));
			block->setPosition(Vec2(i * BLOCK_LEN + 0.5 * BLOCK_LEN, j * BLOCK_LEN + 0.5 * BLOCK_LEN));
			block->setZOrder(1);
			currentMoney -= block->setCost(0);

			this->addChild(block);
		}
	}

	//背景图
	auto background = Sprite::create("BG.png");
	background->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(background);
}

void baseLevel::spawnInit()
{
	//根据关卡不同自己调整怪物的出生位置
	spawnPoint.x = 3;
	spawnPoint.y = 4;

	this->removeChildByTag(coordToTag(spawnPoint.x, spawnPoint.y));

	auto spawn = PathBlock::create();

	spawn->setPosition(Vec2(spawnPoint.x * BLOCK_LEN + 0.5 * BLOCK_LEN, spawnPoint.y * BLOCK_LEN + 0.5 * BLOCK_LEN));
	spawn->setZOrder(0);
	


	path.pushBack(spawn);

	this->addChild(spawn);

	for (int i = 4; i <= 12; i++)
		addPath(i, 4);

	//在终点添加一个萝卜图层
	auto carrot = Sprite::create("carrot.png");
	carrot->setAnchorPoint(Vec2(0.5, 0));
	carrot->setPosition(path.back()->getPosition());
	carrot->setScale(2);
	carrot->setName("carrot");
	this->addChild(carrot);
}

void baseLevel::uiInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//显示剩余金钱
	auto currentMoney = Label::createWithTTF("Current money: " + std::to_string(this->currentMoney), "fonts/Marker Felt.ttf", 50);
	currentMoney->setName("currentMoney");
	currentMoney->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height - 0.5 * BLOCK_LEN));
	currentMoney->setZOrder(0);
	this->addChild(currentMoney);

	//显示当前波次
	auto wave = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	wave->setName("currentWave");
	wave->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height - 0.5 * BLOCK_LEN));
	wave->setZOrder(0);
	this->addChild(wave);

	//显示剩余血量
	auto hp = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 50);
	hp->setName("hp");
	hp->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height - 0.5 * BLOCK_LEN));
	hp->setZOrder(0);
	this->addChild(hp);

	
}

void baseLevel::waveInit()
{
	WaveList wave1;
	wave1.spawnInterval = 2;
	for (int i = 0; i < 3; i++) {
		auto enemy = enemy::create("mike.png");
		enemy->setPosition(path.front()->getPosition());
		wave1.sequence.pushBack(enemy);
	}
	wave.push_back(wave1);

	WaveList wave2;
	wave2.spawnInterval = 3;
	for (int i = 0; i < 3; i++) {
		auto enemy = enemy::create("mike.png");
		enemy->setPosition(path.front()->getPosition());
		wave2.sequence.pushBack(enemy);
	}
	wave.push_back(wave2);

	maxWave = wave.size();
	waveIter = wave.begin();
	currentIter = waveIter->sequence.begin();
}

void baseLevel::scheduleInit()
{
	schedule(schedule_selector(baseLevel::uiUpdate));
	schedule(schedule_selector(baseLevel::winCheck));
}

PathBlock* baseLevel::addPath(int x, int y)
{
	auto ppath = PathBlock::create();

	this->removeChildByTag(coordToTag(x, y));
	ppath->setPosition(Vec2(x * BLOCK_LEN + 0.5 * BLOCK_LEN, y * BLOCK_LEN + 0.5 * BLOCK_LEN));
	ppath->setZOrder(0);
	this->addChild(ppath);

	path.pushBack(ppath);

	return ppath;
}

void baseLevel::uiUpdate(float dt)
{
	currentMoney = money;
	for (int x = 1; x <= BLOCK_X_NUM; ++x) {
		for (int y = 1; y <= BLOCK_Y_NUM; ++y) {
			auto block = this->getChildByTag(coordToTag(x, y));
			if (dynamic_cast<BaseBlock*>(block) != nullptr)
				currentMoney -= dynamic_cast<BaseBlock*>(block)->cost;
		}
	}

	auto label = this->getChildByName("currentMoney");
	if (label) {
		dynamic_cast<Label*>(label)->setString("Current money: " + std::to_string(currentMoney));
	}

	auto wave = this->getChildByName("currentWave");
	if (wave) {
		dynamic_cast<Label*>(wave)->setString("Current wave/Max wave: " + std::to_string(currentWave) + "/" + std::to_string(maxWave));
	}

	auto hp = this->getChildByName("hp");
	if (hp) {
		dynamic_cast<Label*>(hp)->setString("Current hp: " + std::to_string(healthPoint));
	}
}

void baseLevel::monsterSpawn(float dt)
{
	/*auto enemy = *currentIter;
	this->addChild(enemy);
	enemy->setOpacity(255);
	enemy->move();*/
	scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
}

void baseLevel::spawnOne(float dt)
{
	if (currentIter == waveIter->sequence.begin())
		currentWave++;
	auto enemy = *currentIter;
	enemy->setOpacity(255);
	this->addChild(enemy);
	enemy->move();
	currentIter++;
	if (currentIter != waveIter->sequence.end() && waveIter != wave.end())
		scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
	else {
		schedule(schedule_selector(baseLevel::checkElimination));
	}
}

void baseLevel::checkElimination(float dt)
{
	auto iter = waveIter->sequence.begin();
	bool flag = 1;
	while (iter != waveIter->sequence.end()) {
		if ((*iter)->getParent()) {
			flag = 0;
		}
		iter++;
	}
	if (flag == 1) {
		waveIter++;
		this->unschedule(schedule_selector(baseLevel::checkElimination));
		if (waveIter != wave.end())
		{
			currentIter = waveIter->sequence.begin();
			scheduleOnce(schedule_selector(baseLevel::spawnOne), waveIter->spawnInterval);
		}
	}
}

void baseLevel::winCheck(float dt)
{
	if (healthPoint == 0) {
		loseDisplay();
	}
	else if (currentWave > maxWave) {
		winDisplay();
	}
}

void baseLevel::winDisplay()
{
	auto winScene = Scene::create();
	auto tryAgainButton = ui::Button::create("try_again_normal.png", "try_again_selected.png");
	auto returnToMenuButton = ui::Button::create("select_menu_normal.png", "select_menu_selected.png");
	auto winLabel = Label::createWithTTF("You won!", "fonts/Marker Felt.ttf", 150);
	auto backGround = Sprite::create("BG.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	tryAgainButton->setPosition(Vec2(0.3 * visibleSize.width, 0.3 * visibleSize.height));
	returnToMenuButton->setPosition(Vec2(0.7 * visibleSize.width, 0.3 * visibleSize.height));
	winLabel->setPosition(Vec2(0.5 * visibleSize.width, 0.6 * visibleSize.height));
	backGround->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));

	winScene->addChild(tryAgainButton, 1);
	winScene->addChild(returnToMenuButton, 1);
	winScene->addChild(winLabel, 1);
	winScene->addChild(backGround, 0);
	Director::getInstance()->replaceScene(winScene);
}

void baseLevel::loseDisplay()
{
	auto winScene = Scene::create();
	auto tryAgainButton = ui::Button::create("try_again_normal.png", "try_again_selected.png");
	auto returnToMenuButton = ui::Button::create("select_menu_normal.png", "select_menu_selected.png");
	auto winLabel = Label::createWithTTF("You lose!", "fonts/Marker Felt.ttf", 150);
	auto backGround = Sprite::create("BG.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	tryAgainButton->setPosition(Vec2(0.3 * visibleSize.width, 0.3 * visibleSize.height));
	returnToMenuButton->setPosition(Vec2(0.7 * visibleSize.width, 0.3 * visibleSize.height));
	winLabel->setPosition(Vec2(0.5 * visibleSize.width, 0.6 * visibleSize.height));
	backGround->setPosition(Vec2(0.5 * visibleSize.width, 0.5 * visibleSize.height));

	winScene->addChild(tryAgainButton, 1);
	winScene->addChild(returnToMenuButton, 1);
	winScene->addChild(winLabel, 1);
	winScene->addChild(backGround, 0);
	Director::getInstance()->replaceScene(winScene);
}





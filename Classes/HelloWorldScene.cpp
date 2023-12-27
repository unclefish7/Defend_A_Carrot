/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


//�رճ���İ�ť
void HelloWorld::menuCloseCallback(Ref* pSender)
{
   // Close the cocos2d - x game scene and quit the application
        Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    EventCustom customEndEvent("game_scene_close_event");
    _eventDispatcher->dispatchEvent(&customEndEvent);


}



/*================================================================================*/
//ok��
/*================================================================================*/
bool HelloWorld::init()
{


    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��

    // ��ӱ���
    auto background = Sprite::create("FirstBackground.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);

    // ������ť
    auto bounceItemfirst = MenuItemImage::create(
        "startgame-about-normal.png",
        "startgame-about-selected.png",
        CC_CALLBACK_1(HelloWorld::buttonClickCallbackLevelOne, this));
    bounceItemfirst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 9));
    bounceItemfirst->setScale(0.35);
    // �����˵�
    auto menu = Menu::create(bounceItemfirst, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);

    return true;
}

//�˵�
bool Menufirst::init(){
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��

    auto temp = Scene::create();

    auto backgroundfirst = Sprite::create("First-level-background.jpg");
    backgroundfirst->setPosition(Director::getInstance()->getVisibleSize() / 2);
    temp->addChild(backgroundfirst);

    auto backgroundMenu = Sprite::create("operation.png");
    backgroundMenu->setPosition(Director::getInstance()->getVisibleSize() / 2);
    temp->addChild(backgroundMenu);

    auto bottommenu = MenuItemImage::create(
        "quit-normal.png",
        "quit.png",
        CC_CALLBACK_1(Menufirst::buttonClickCallbackLevelOne, this));
    bottommenu->setPosition(Vec2(visibleSize.width / 100 * 49, visibleSize.height / 20 * 5));
    bottommenu->setScale(1.0);

    auto menu = Menu::create(bottommenu, nullptr);
    menu->setPosition(Vec2::ZERO);
    temp->addChild(menu);

    Director::getInstance()->pushScene(temp);
    return true;
}

bool Menusecond::init() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��

    auto temp = Scene::create();

    auto backgroundsecond = Sprite::create("Second-level-background.jpg");
    backgroundsecond->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 20 * 11));
    temp->addChild(backgroundsecond);

    auto backgroundMenu = Sprite::create("operation.png");
    backgroundMenu->setPosition(Director::getInstance()->getVisibleSize() / 2);
    temp->addChild(backgroundMenu);

    auto bottommenu = MenuItemImage::create(
        "quit-normal.png",
        "quit.png",
        CC_CALLBACK_1(Menusecond::buttonClickCallbackLevelTwo, this));
    bottommenu->setPosition(Vec2(visibleSize.width / 100 * 49, visibleSize.height / 20 * 5));
    bottommenu->setScale(1.0);

    auto menu = Menu::create(bottommenu, nullptr);
    menu->setPosition(Vec2::ZERO);
    temp->addChild(menu);

    Director::getInstance()->pushScene(temp);
    return true;
}

void Menufirst::buttonClickCallbackLevelOne(Ref* pSender) {
    auto firstScene = FirstScene::create();
}

void Menusecond::buttonClickCallbackLevelTwo(Ref* pSender) {
    auto secondScene = SecondScene::create();
}

void FirstSceneStart::buttonClickCallbackMenu(Ref* pSender) {
    auto menufirst = Menufirst::create();
}

void SecondSceneStart::buttonClickCallbackMenu(Ref* pSender) {
    auto menusecond = Menusecond::create();
}

//============================================================================================================  1
//�㰴ť֮���л�������level-one
void HelloWorld::buttonClickCallbackLevelOne(Ref* pSender) {
    auto firstScene = FirstScene::create();
}
//�����һ�ص�ͼ
void FirstScene::buttonClickCallbackLevelOneStart(Ref* pSender) {
    auto firstSceneStart = FirstSceneStart::create();
}

void SecondScene::buttonClickCallbackLevelOne(Ref* pSender) {
    auto firstScene = FirstScene::create();
}

void FirstScene::buttonClickCallbackLevelTwo(Ref* pSender) {
    auto secondScene = SecondScene::create();
}

//level-one����
bool  FirstScene::init() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��

    //���ѡ���һ�صı���
    auto firstScene = Scene::create();
    auto backgroundfirst = Sprite::create("First-level.jpg");
    backgroundfirst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 20 * 11));
    firstScene->addChild(backgroundfirst);

    //��ʼ��Ϸ
    auto bottomfirst = MenuItemImage::create(
        "start-about-normal.jpg",
        "start-about-selected.jpg",
        CC_CALLBACK_1(FirstScene::buttonClickCallbackLevelOneStart, this));//��ת��һ����ϸ��ͼ
    bottomfirst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 9));
    bottomfirst->setScale(0.35);

    //ת��ڶ���
    auto bottomright = MenuItemImage::create(
        "right-normal.png",
        "right-selected.png",
        CC_CALLBACK_1(FirstScene::buttonClickCallbackLevelTwo, this));
    bottomright->setPosition(Vec2(visibleSize.width / 10 * 9, visibleSize.height / 2));
    bottomright->setScale(0.1);

    auto menu = Menu::create(bottomfirst, bottomright,nullptr);
    menu->setPosition(Vec2::ZERO);
    firstScene->addChild(menu);
    Director::getInstance()->replaceScene(firstScene);

    return true;
}

//��һ�ص�ͼ
bool FirstSceneStart::init() {
        auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��

    auto firstStartScene = Scene::create();
    auto backgroundfirst = Sprite::create("First-level-background.jpg");
    backgroundfirst->setPosition(Director::getInstance()->getVisibleSize() / 2);
    firstStartScene->addChild(backgroundfirst);

    //�˵���ť
    auto bottommenu = MenuItemImage::create(
        "operation-bottom-normal.png",
        "operation-bottom-selected.png",
        CC_CALLBACK_1(FirstSceneStart::buttonClickCallbackMenu, this));
    bottommenu->setPosition(Vec2(visibleSize.width / 30 * 29, visibleSize.height / 10 * 9));
    bottommenu->setScale(0.6);

    auto menu = Menu::create(bottommenu, nullptr);
    menu->setPosition(Vec2::ZERO);
    firstStartScene->addChild(menu);

    Director::getInstance()->replaceScene(firstStartScene);
    return true;
}


//============================================================================================================  2
//����ڶ��ص�ͼ
void SecondScene::buttonClickCallbackLevelTwoStart(Ref* pSender) {
    auto secondSceneStart = SecondSceneStart::create();
}

bool SecondScene::init() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
        Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��
    
        //���ѡ��ڶ��صı���
        auto secondScene = Scene::create();
        auto backgroundsecond = Sprite::create("Second-level.jpg");
        backgroundsecond->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 20 * 11));
        secondScene->addChild(backgroundsecond);
        //���ѡ��ť
        auto bottomsecond = MenuItemImage::create(
            "start2-about-normal.jpg",
            "start2-about-selected.jpg",
            CC_CALLBACK_1(SecondScene::buttonClickCallbackLevelTwoStart, this));//��ת�ڶ�����ϸ��ͼ
        bottomsecond->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 9));
        bottomsecond->setScale(0.35);
        //ת���һ��
        auto bottomleft = MenuItemImage::create(
            "left-normal.png",
            "left-selected.png",
            CC_CALLBACK_1(SecondScene::buttonClickCallbackLevelOne, this));
        bottomleft->setPosition(Vec2(visibleSize.width / 10 , visibleSize.height / 2));
        bottomleft->setScale(0.1);
    
        auto menu = Menu::create(bottomsecond, bottomleft,nullptr);
        menu->setPosition(Vec2::ZERO);
        secondScene->addChild(menu);
        Director::getInstance()->replaceScene(secondScene);
    return true;
}

//�ڶ��ص�ͼ
bool SecondSceneStart::init() {
    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ��Ļ��С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡԭ��

    auto secondStartScene = Scene::create();
    auto backgroundsecond = Sprite::create("Second-level-background.jpg");
    backgroundsecond->setPosition(Director::getInstance()->getVisibleSize() / 2);
    secondStartScene->addChild(backgroundsecond);
    //�˵���ť
    auto bottommenu = MenuItemImage::create(
        "operation-bottom-normal.png",
        "operation-bottom-selected.png",
        CC_CALLBACK_1(SecondSceneStart::buttonClickCallbackMenu, this));
    bottommenu->setPosition(Vec2(visibleSize.width / 20 * 19, visibleSize.height / 10 * 9));
    bottommenu->setScale(0.6);

    auto menu = Menu::create(bottommenu, nullptr);
    menu->setPosition(Vec2::ZERO);
    secondStartScene->addChild(menu);

    Director::getInstance()->replaceScene(secondStartScene);
    return true;
}



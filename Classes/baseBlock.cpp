
#include "baseBlock.h"
#include"testScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include"baseLevel.h"

USING_NS_CC;


TestBlock* TestBlock::create()
{
    TestBlock* pRet = new (std::nothrow) TestBlock();
    if (pRet && pRet->initWithFile("HelloWorld(2).png"))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }

    return pRet;
}

void TestBlock::onEnter()
{
    Sprite::onEnter();

    auto* disp = Director::getInstance()->getEventDispatcher();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
        };
    listener->onTouchEnded = CC_CALLBACK_2(TestBlock::clickReact, this);

    disp->addEventListenerWithSceneGraphPriority(listener, this);
}

void TestBlock::onExit()
{
    Sprite::onExit();

    auto* disp = Director::getInstance()->getEventDispatcher();
    disp->removeEventListenersForTarget(this);
}

bool TestBlock::clickReact(Touch* touch, Event* event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Vec2 tworld = touch->getLocation();
    Vec2 tlocal = target->convertToNodeSpace(tworld);

    auto size = target->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);

    if (rect.containsPoint(tlocal)) {
        static int turn = 0;
        static auto texture = target->getTexture();

        if (texture == target->getTexture()) {
            target->setTexture("btn-about-normal.png");

            //ͨ��ȫ��layerʵ��
            auto layer = Node::create();
            layer->setName("layer");
            auto* disp = Director::getInstance()->getEventDispatcher();


            auto listener = EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);

            listener->onTouchBegan = [](Touch* touch, Event* event) {
                return true;
                };

            listener->onTouchMoved = [](Touch* touch, Event* event) {

                };

            listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
                this->removeChildByName("layer");
                target->setTexture("HelloWorld(2).png");
            };
            disp->addEventListenerWithSceneGraphPriority(listener, layer);

            this->addChild(layer);


        }


        return true;
    }
    return false;
}





//Sprite* TestBlock::newInstance()
//{
//	return new TestBlock();
//}

//����Ϊ���Դ���
/********************************************************************************/
//����Ϊ��ʽ����

bool BaseBlock::init()
{

    

    return true;
}

BaseBlock* BaseBlock::create()
{
    BaseBlock* sprite = new (std::nothrow) BaseBlock();
    if (sprite && sprite->initWithFile("center_grid_selected.png")) // ͼƬ�ǹ̶���
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void BaseBlock::onEnter()
{
    this->setOpacity(UNSELECTED_OPACITY);

    Sprite::onEnter();

    //����¼��ַ���
    auto* disp = Director::getInstance()->getEventDispatcher();

    //����һ��������
    auto listener = EventListenerTouchOneByOne::create();
    //����û�¼�
    listener->setSwallowTouches(false);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
        };
    listener->onTouchEnded = CC_CALLBACK_2(BaseBlock::judgeListenerCallback, this); //����̧��Żᴥ��

    //�Ѽ�������ӵ�BaseBlock��
    disp->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaseBlock::onExit()
{
    Sprite::onExit();

    //�Ƴ��ö������еļ���
    auto* disp = Director::getInstance()->getEventDispatcher();
    disp->removeEventListenersForTarget(this);
}

bool BaseBlock::judgeListenerCallback(cocos2d::Touch* touch, cocos2d::Event* event)
{
    //��ȡ�¼����󣨾���Block�Լ���
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    //��ȡ���������λ��
    Vec2 tworld = touch->getLocation();
    //������λ��ת��Ϊ����λ�ã�Block�����λ�ã�
    Vec2 tlocal = target->convertToNodeSpace(tworld);

    //��ȡ����ĳߴ�
    auto size = target->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);

    //��������λ������Block�ϣ�������������ص�
    if (rect.containsPoint(tlocal)) {
        clickCallback();
        return true;
    }
    return false;
}

void BaseBlock::clickCallback()
{
    CCLOG("clicked!");
    this->setOpacity(SELECTED_OPACITY);
    auto towerPicOne = ui::Button::create("FireBottle_available.png", "FireBottle_available.png", "FireBottle_available.png");
    auto towerPicTwo = ui::Button::create("FireBottle_locked.png", "FireBottle_locked.png", "FireBottle_locked.png");

    auto myWidth = this->getContentSize().width;
    auto myHeight = this->getContentSize().height;

    auto myPosition = this->getPosition();
    auto myPosY = myPosition.y;
    auto myPosX = myPosition.x;

    CCLOG("my pos::%f %f", myPosX, myPosY);

    towerPicOne->setPosition(Vec2(myPosX + myHeight, myPosY + myWidth));
    towerPicTwo->setPosition(Vec2(myPosX, myPosY + myWidth));

    CCLOG("T1 pos::%f %f", towerPicOne->getPosition().x, towerPicOne->getPosition().y);
    CCLOG("T2 pos::%f %f", towerPicTwo->getPosition().x, towerPicTwo->getPosition().y);

    towerPicOne->setName("T1");
    towerPicTwo->setName("T2");
    towerPicOne->setSwallowTouches(false);
    towerPicTwo->setSwallowTouches(false);

    towerPicOne->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        default:
            break;
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->getParent()->removeChildByName("T1");
                this->getParent()->removeChildByName("T2");


                /*auto successLabel = Label::createWithTTF("Build Success!", "fonts/Marker Felt.ttf", 100);
                successLabel->setAnchorPoint(Vec2(0.5, 0.5));
                successLabel->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 2 * this->getContentSize().height));
                successLabel->setName("s");
                this->getParent()->addChild(successLabel);
                this->scheduleOnce(schedule_selector(BaseBlock::scheduleFunc), 1.0f);*/

                this->cost += 100;

                auto parent = dynamic_cast<baseLevel*>(this->getParent());

                if (parent != nullptr) {
                    
                }

                return true;
                break;
        }

    });

    towerPicTwo->addTouchEventListener([&](Ref* Sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        default:
            break;
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            this->getParent()->removeChildByName("T1");
            this->getParent()->removeChildByName("T2");

            /*auto failLabel = Label::createWithTTF("Not enough money!", "fonts/Marker Felt.ttf", 100);
            failLabel->setAnchorPoint(Vec2(0.5, 0.5));
            failLabel->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 2 * this->getContentSize().height));
            failLabel->setName("f");
            this->getParent()->addChild(failLabel);
            this->scheduleOnce(schedule_selector(BaseBlock::scheduleFunc), 1.0f);*/

            auto parent = dynamic_cast<baseLevel*>(this->getParent());

            if (parent != nullptr) {
                
            }

            return true;
            break;
        }

    });
   

    auto layer = Node::create();
    layer->setName("layer");
    auto* disp = Director::getInstance()->getEventDispatcher();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
        };

    listener->onTouchMoved = [](Touch* touch, Event* event) {

        };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        
        if (towerPicOne)
        {
            this->getParent()->removeChildByName("T1");
            this->getParent()->removeChildByName("T2");
            CCLOG("remove from layer");
        }
        this->getParent()->removeChildByName("layer");

        this->setOpacity(UNSELECTED_OPACITY);
        CCLOG("RETURNED!");
        };

    towerPicOne->setZOrder(3);
    towerPicTwo->setZOrder(3);
    layer->setZOrder(2);

    disp->addEventListenerWithSceneGraphPriority(listener, layer);

    this->getParent()->addChild(towerPicOne);
    this->getParent()->addChild(towerPicTwo);
    this->getParent()->addChild(layer);
    
}

void BaseBlock::scheduleFunc(float dt)
{
    if (this->getParent()->getChildByName("s")) {
        this->getParent()->removeChildByName("s");
    }
    if (this->getParent()->getChildByName("f")) {
        this->getParent()->removeChildByName("f");
    }
}

int BaseBlock::setCost(int m)
{
    cost = m;
    return cost;
}

bool PathBlock::init()
{
    return true;
}

PathBlock* PathBlock::create()
{
    PathBlock* sprite = new (std::nothrow) PathBlock();
    if (sprite && sprite->initWithFile("path_block.png")) // ͼƬ�ǹ̶���
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void PathBlock::onEnter()
{
    Sprite::onEnter();

    this->link = nullptr;
}

PathBlock* PathBlock::getNextPath()
{
    return this->link;
}

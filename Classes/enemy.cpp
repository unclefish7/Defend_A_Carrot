#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include"enemy.h"
#include"baseLevel.h"
USING_NS_CC;

inline bool enemy::init()
{
    return true;
}


enemy* enemy::create(const std::string& filename)
{
    enemy* sprite = new (std::nothrow) enemy();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void enemy::onEnter()
{
    Sprite::onEnter();
    hp = 100;
    speed = 1;
    auto enemyhp = Label::createWithTTF(std::to_string(hp), "fonts/Marker Felt.ttf", 100);
    enemyhp->setAnchorPoint(Vec2(0.5, 0.5));
    enemyhp->setName("enemy_hp");

    //��Ѫ��
    Sprite* Blood = CCSprite::create("xuetiao.png");
    //�������ڱ�ʾ���ﵱǰѪ���Ľ�����
    ProgressTimer* pBloodProGress = ProgressTimer::create(Blood);
    pBloodProGress->setName("enemy_hp1");
    pBloodProGress->setScale(0.5);
    //����Ϊ����
    pBloodProGress->setType(kCCProgressTimerTypeBar);
    //������ʼ��Ϊ�������·�
    pBloodProGress->setMidpoint(ccp(0, 0));
   //����Ϊˮƽ����
    pBloodProGress->setBarChangeRate(ccp(1, 0));
    //���ó�ʼ����Ϊ��Ѫ
    pBloodProGress->setPercentage(100.0f);
    //����λ�ã�������Ŀ�Ѫ���ص����Ҿ�������
    pBloodProGress->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height + 1));
    //�����ﾫ���ϣ�������tagֵ��һ��֮���ȡ����������ͨ��setPercentage�ı䵱ǰѪ��
    pBloodProGress->setZOrder(5);
    this->addChild(pBloodProGress);
    this->addChild(enemyhp);
    
    //this->schedule(schedule_selector(enemy::Move), 0.5f);
    this->scheduleUpdate();
}




void enemy::move()
{
    auto parent =  dynamic_cast<baseLevel*>(this->getParent());
    if (parent) {
        auto curBlock = parent->path.begin();
        Vector<FiniteTimeAction*> actSeq;
        //actSeq.pushBack(MoveTo::create(1.0f, this->getPosition()));
        while (curBlock != parent->path.end()) {
            auto moveTo = MoveTo::create(0.5f, (*curBlock)->getPosition());
            actSeq.pushBack(moveTo);
            curBlock++;
        }
        
        auto runseq = Sequence::create(actSeq);
        this->runAction(runseq);
    }
    else {
        CCLOG("enemy : move error!");
    }
}


void enemy::get_hit(int damage)
{
    auto tintBy1 = TintBy::create(0.05, 120.0f, 232.0f, 254.0f);
    auto tintBy2 = TintBy::create(0.05, -120.0f, -232.0f, -254.0f);
    auto seq = Sequence::create(tintBy2,tintBy1,nullptr);
    this->runAction(seq);
    this->hp = this->hp - damage;
}

void enemy::update(float dt)
{
    this->show();
    this->showhp();
    auto parent = dynamic_cast<baseLevel*>(this->getParent());
    if (hp == 0)
    {
        CCLOG("removed!");
        this->removeFromParent();
    }
    else if (parent && fabs(this->getPosition().x - parent->path.back()->getPosition().x) < 1e-1 && fabs(this->getPosition().y - parent->path.back()->getPosition().y) < 1e-1) {
        CCLOG("removed!");
        this->removeFromParent();
        parent->healthPoint--;
    }
}

void enemy::Move(float dt)
{
    get_hit(20);
}

void enemy::show()
{
    CCLOG("enemy_hp:[%d]", hp);
}

void enemy::showhp()
{
    auto enemy_hp = dynamic_cast<Label*>(getChildByName("enemy_hp"));
    auto enemy_hp1 = dynamic_cast<ProgressTimer*>(getChildByName("enemy_hp1"));
    // position the label on the center of the screen
    if (enemy_hp==nullptr)
    {
        CCLOG("error:enemy_hp is wrong!");
    }
    else
    {
        enemy_hp->setString(std::to_string(this->hp));
        //enemy_hp->setPosition(Vec2(this->getPosition().x*0.05, this->getPosition().y*4));
    }
    enemy_hp1->setPercentage((this->hp / 100.0f)*100.0f);
}
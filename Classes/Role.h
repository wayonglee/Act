#ifndef _ROLE_H_
#define _ROLE_H_
#include"cocos2d.h"

USING_NS_CC;
enum RoleState
{
	STAY,
	WALK,
	PREATTACK,
	ATTACK,
	HURT
};

class Role:public Sprite
{
public:
	Role(void);
	~Role(void);
	CREATE_FUNC(Role);
	CC_SYNTHESIZE(RoleState,curState,CurState);
	CC_SYNTHESIZE(bool,stateChangeable,StateChangeable);
	CC_SYNTHESIZE(bool,stateBreakable,StateBreakable);
	CC_SYNTHESIZE(std::string,name,Name);//��ɫ��
	CC_SYNTHESIZE(float,curtLifevalue,CurtLifeValue);//��ɫѪ
	CC_SYNTHESIZE(float,sumLifevalue,SumLifeValue);//��Ѫ
	CC_SYNTHESIZE(float,speed,Speed);//�ٶ�
	CC_SYNTHESIZE(Vec2,direction,Direction);//�ƶ�����
	CC_SYNTHESIZE(bool,isFlipped,IsFlipped);//�Ƿ�ת
	CC_SYNTHESIZE_RETAIN(Action*, stayAction, StayAction);//ͣ������
    CC_SYNTHESIZE_RETAIN(Action*, walkAction, WalkAction);//�ƶ�����
	CC_SYNTHESIZE_RETAIN(Action*, attackAction, AttackAction);//��������
	CC_SYNTHESIZE_RETAIN(Action*, hurtAction, HurtAction);//���˶���
	void runStayAction();
	void runWalkAction();
	void runAttackAction();
	void runHurtAction();
	Animation* createAnimation(const char*,int frameSize,int fps);
	Animation* createAttackAnimation(const char*,int beginFrame,int endFrame,int fps);
	void move(Vec2 direction,bool isFlipped);
	bool changeState(RoleState,float delay = 0,float roll = 0);
	void attack(float roll,float delay);
	void attackBegin(float);
	void attackFinish(float);
	void hurt(float delay);
	void hurtFinish(float);
};

#endif
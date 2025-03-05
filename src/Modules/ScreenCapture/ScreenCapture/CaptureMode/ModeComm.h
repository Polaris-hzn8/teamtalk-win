
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef MODECOMM_B3B7C7CC_9F99_4B19_B594_3512D01B7D02_H__
#define MODECOMM_B3B7C7CC_9F99_4B19_B594_3512D01B7D02_H__

#include "../Common.h"

class IModeMsgHandler
{
public:
	virtual void onLButtonDown(__in int x, __in int y){}
	virtual void onLButtonUp(__in int x, __in int y){}
	virtual void onLButtonDBClick(__in int x, __in int y){}
	virtual void onMouseMove(__in int x, __in int y){}
};

#endif // MODECOMM_B3B7C7CC_9F99_4B19_B594_3512D01B7D02_H__


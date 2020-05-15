/************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/10/17
**************************************************************/
/***********************************************************
*Problem	:
*Tips:		:
			1.PolyItem另外一种设计思想应该设置为类,而其私有成员用
			方法访问并重置
*************************************************************/
/************************************************************
*History	:

*************************************************************/
#ifndef POLYITEM_H_INCLUDE
#define POLYITEM_H_INCLUDE
struct PolyItem {
	double mCoef;							//命名时用m做前缀以表明其为成员数据

	int mExpn;

	PolyItem();

	PolyItem(double mCoef, int mExpn);
};

PolyItem::PolyItem() {
	this->mExpn = -1;
}

PolyItem::PolyItem(double coef, int expn) {
	this->mCoef = coef;
	this->mExpn = expn;
}


#endif

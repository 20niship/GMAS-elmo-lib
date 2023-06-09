#ifndef EMCHOMECALC_H_
#define EMCHOMECALC_H_


#include "Home/EMBLHome.h"
class CCalculateHomingMethod
{
public:
	CCalculateHomingMethod(void);
	~CCalculateHomingMethod(void);

	static unsigned int CalculateHomingMethodHomeSw(unsigned short usUseIndexPulse,EMBL_DIRECTION_ENUM eDirection, EMBL_SWITCH_MOD_ENUM eHomeSwitchMode);
	static unsigned int CalculateHomingMethodHomeSwAndFLS(unsigned short usUseIndexPulse,EMBL_DIRECTION_ENUM eDirection, EMBL_SWITCH_MOD_ENUM eHomeSwitchMode);
	static unsigned	int CalculateHomingMethodHomeSwAndRLS(unsigned short usUseIndexPulse,EMBL_DIRECTION_ENUM eDirection, EMBL_SWITCH_MOD_ENUM eHomeSwitchMode);
};

#endif

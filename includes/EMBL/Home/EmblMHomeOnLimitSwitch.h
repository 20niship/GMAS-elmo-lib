/*
 * EmblMHomeOnLimitSwitch.h
 *
 *  Created on: 28/04/2015
 *      Author: ilia
 */

#ifndef EMBLMHOMEONLIMITSWITCH_H_
#define EMBLMHOMEONLIMITSWITCH_H_

#include "Home/EmblHomeMultiAxis.h"
#ifdef __cplusplus

class CEmblMHomeOnLimitSwitch: public CEmblHomeMultiAxis {
public:
	CEmblMHomeOnLimitSwitch() {}
	CEmblMHomeOnLimitSwitch(unsigned int uiConn, unsigned short usAxisRef[],unsigned short usCount,EMBL_QUEUEING_RULES_ENUM eQueuedRule);
	virtual ~CEmblMHomeOnLimitSwitch();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
						overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
						usAxisRef[] - axis reference.
						usCount
						eQueuedRule
						MultiAxHomeOnLimitInParam -  pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef[],unsigned short usCount,EMBL_QUEUEING_RULES_ENUM eQueuedRule, EMBL_MULTI_AX_HOME_ON_LIMIT_IN* MultiAxHomeOnLimitInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             MultiAxHomeOnLimitInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_MULTI_AX_HOME_ON_LIMIT_IN* MultiAxHomeOnLimitInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
						Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             homeOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(MMC_HOME_OUT* homeOutParam);

	void  Echo(void);

protected :
	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */
	virtual int Init(void *);

	/**
	 * \fn PostPerform()
	 * \brife: Execution of methods after the preform ended.
	 * \return none.
	 */
	virtual int PostPerform(void *);
};
#endif

/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

unsigned int  HoLimitCreateObjM(unsigned int uiConn, unsigned short usAxisRef[],unsigned short usCount,EMBL_QUEUEING_RULES_ENUM eQueuedRule);
void  HoLimitRmObjM(unsigned int uiHoLimitObj);
int HoLimitInitM(unsigned int uiHoLimitObj, EMBL_MULTI_AX_HOME_ON_LIMIT_IN* pData);
int  HoLimitPostM(unsigned int uiHoLimitObj, void *pData );

#ifdef __cplusplus
}
#endif
#endif /* EMBLMHOMEONLIMITSWITCH_H_ */

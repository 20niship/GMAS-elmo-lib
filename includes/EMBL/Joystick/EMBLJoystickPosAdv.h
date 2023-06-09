/*
 * EMBLJoystickPosition.h
 *
 *  Created on: Jan 29, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickPosAdv_H_
#define EMBLJoystickPosAdv_H_

#include "EMBLJoystick.h"


typedef struct embl_joystick_pos_adv_in
{
	double dPosition;
	float fVelocity;
	float fAcceleration;
	float fJerk;
	float fDeadZone;
	float fOffset;
	float fGain;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_POS_ADV_IN;

typedef struct embl_joystick_pos_adv_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_POS_ADV_OUT;


#ifdef __cplusplus
class CEmblJoystickPosAdv: public CEmblJoystick {
public:
	CEmblJoystickPosAdv(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickPosAdv();

	MMC_MOVEABSOLUTE_IN 	m_stMoveAbsInParams;
	MMC_MOVEABSOLUTE_OUT	m_stMoveAbsOutParams;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and relevant class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    EMBL_JOYSTICK_POS_ADV_IN *joystickPosAdvInParam - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_JOYSTICK_POS_ADV_IN *joystickPosAdvInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             EMBL_JOYSTICK_POS_ADV_IN - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_JOYSTICK_POS_ADV_IN *joystickPosAdvInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickPosAdvInParam - structure of data relevant for Perform function.
	 output:            joystickPosAdvOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_JOYSTICK_POS_ADV_IN* joystickPosAdvInParam, EMBL_JOYSTICK_POS_ADV_OUT *joystickPosAdvOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	 	 	 	 	 	Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:
	 output:            joystickPosOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_JOYSTICK_POS_ADV_OUT* joystickPosAdvOutParam);

	void  Echo(void);
protected:
	EMBL_JOYSTICK_POS_ADV_IN m_stIData; //parameters for Perform(void *) function - (populated in the overloaded Perform function).
	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */
	virtual int Init(void *);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:	    class complete stages.
	 input:             void *pData - void pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(void *);


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

int JoyPosAdvPerform(unsigned int uiJoyObj, EMBL_JOYSTICK_POS_ADV_IN *pInData,EMBL_JOYSTICK_POS_ADV_OUT *pOutData);
unsigned int  JoyPosAdvCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyPosAdvRemoveObj(unsigned int uiJoyObj);
int  JoyPosAdvPost(unsigned int uiJoyObj, void *pData );
int JoyPosAdvInit(unsigned int uiJoyObj, EMBL_JOYSTICK_POS_ADV_IN *pInData);

#ifdef __cplusplus
}
#endif


#endif /* EMBLJoystickPosAdv_H_ */

/*
 * EMBLJoystickPosition.h
 *
 *  Created on: Jan 29, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickPosition_H_
#define EMBLJoystickPosition_H_

#include "EMBLJoystick.h"


typedef struct embl_joystick_pos_in
{
	double dPosition;
	float fVelocity;
	float fAcceleration;
	float fJerk;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_POS_IN;

typedef struct embl_joystick_pos_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_POS_OUT;

#ifdef __cplusplus
class CEmblJoystickPos: public CEmblJoystick {
public:
	CEmblJoystickPos(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickPos();

	MMC_MOVEABSOLUTE_IN 	m_stMoveAbsInParams;
	MMC_MOVEABSOLUTE_OUT	m_stMoveAbsOutParams;


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    EMBL_JOYSTICK_POS_IN - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_JOYSTICK_POS_IN *joystickPosInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get a specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             EMBL_JOYSTICK_POS_IN - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_JOYSTICK_POS_IN *joystickPosInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:
	 output:            joystickPosOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_JOYSTICK_POS_IN* joystickPosInParam, EMBL_JOYSTICK_POS_OUT* joystickPosOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	 	 	 	 	 	Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:
	 output:            joystickPosOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_JOYSTICK_POS_OUT* joystickPosOutParam);

	void  Echo(void);
protected:

	EMBL_JOYSTICK_POS_IN m_stIData;

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
	 input:             void *pOData - pointer to output param MMC_JOYSTICK_POS_OUT(status , error id , fb handle)
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(void*);


	/**
	 * \fn PostPerform()
	 * \brife: Execution of methods after the perform ended.
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

int JoyPosPerform(unsigned int uiJoyObj, EMBL_JOYSTICK_POS_IN *pInData,EMBL_JOYSTICK_POS_OUT *pOutData);
unsigned int  JoyPosCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyPosRemoveObj(unsigned int uiJoyObj);
int  JoyPosPost(unsigned int uiJoyObj, void *pData );
int JoyPosInit(unsigned int uiJoyObj, EMBL_JOYSTICK_POS_IN* data);

#ifdef __cplusplus
}
#endif


#endif /* EMBLJoystickPosition_H_ */

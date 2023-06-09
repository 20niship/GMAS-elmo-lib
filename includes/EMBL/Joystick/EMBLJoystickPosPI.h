/*
 * EMBLJoystickPosition.h
 *
 *  Created on: Jan 29, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickPosPI_H_
#define EMBLJoystickPosPI_H_

#include "EMBLJoystick.h"

typedef struct embl_joystick_pos_pi_in
{
	unsigned int uiIndex;
	float fVelocity;
	float fAcceleration;
	float fJerk;
	float fDeadZone;
	float fOffset;
	float fGain;
	int iPIAxisRef;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_POS_PI_IN;

typedef struct embl_joystick_pos_pi_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_POS_PI_OUT;

#ifdef __cplusplus
class CEmblJoystickPosPI: public CEmblJoystick {
public:
	CEmblJoystickPosPI(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickPosPI();

	MMC_MOVEABSOLUTE_IN 	m_stMoveAbsInParams;
	MMC_MOVEABSOLUTE_OUT	m_stMoveAbsOutParams;



	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    EMBL_JOYSTICK_POS_PI_IN *joystickPosPiInParam - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_JOYSTICK_POS_PI_IN *joystickPosPiInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             EMBL_JOYSTICK_POS_PI_IN - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_JOYSTICK_POS_PI_IN *joystickPosPiInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:             joystickPosPiInParam - structure of data relevant for Perform function.
	output:            joystickPosPiOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_JOYSTICK_POS_PI_IN* joystickPosPiInParam, EMBL_JOYSTICK_POS_PI_OUT *joystickPosPiOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickPosPIOut - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_JOYSTICK_POS_PI_OUT* joystickPosPIOut);

	void  Echo(void);
protected:

	EMBL_JOYSTICK_POS_PI_IN m_stIData;

	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */
	virtual int Init(void *);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:	    function performs the complete required stages.
	 input:
	 output:			*pOData
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

int JoyPosPIPerform(unsigned int uiJoyObj,
					EMBL_JOYSTICK_POS_PI_IN *pInData,
					EMBL_JOYSTICK_POS_PI_OUT *pOutData);

unsigned int  JoyPosPICreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyPosPIRemoveObj(unsigned int uiJoyObj);
int  JoyPosPIPost(unsigned int uiJoyObj, void *pData );
int JoyPosPIInit(unsigned int uiJoyObj,  EMBL_JOYSTICK_POS_PI_IN *pInData);

#ifdef __cplusplus
}
#endif


#endif /* EMBLJoystickPosPI_H_ */

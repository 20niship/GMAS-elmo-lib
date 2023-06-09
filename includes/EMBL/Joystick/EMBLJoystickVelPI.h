/*
 * EMBLJoystickVel.h
 *
 *  Created on: Feb 1, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickVelPI_H_
#define EMBLJoystickVelPI_H_

#include "EMBLJoystick.h"



typedef struct embl_joystick_vel_pi_in
{
	unsigned int uiIndex;
	float fAcceleration;
	float fJerk;
	float fDeadZone;
	float fOffset;
	float fGain;
	int iPIAxisRef;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_VEL_PI_IN;

typedef struct embl_joystick_vel_pi_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_VEL_PI_OUT;

#ifdef __cplusplus
class CEmblJoystickVelPI: public CEmblJoystick {
public:
	CEmblJoystickVelPI(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickVelPI();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    joystickVelPIIn - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_JOYSTICK_VEL_PI_IN * joystickVelPIIn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             joystickVelPIIn - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_JOYSTICK_VEL_PI_IN *joystickVelPIIn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:             joystickVelPIInParam - structure of data relevant for Perform function.
	output:            joystickVelPIOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_JOYSTICK_VEL_PI_IN* joystickVelPIInParam, EMBL_JOYSTICK_VEL_PI_OUT *joystickVelPIOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickVelPIOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_JOYSTICK_VEL_PI_OUT* joystickVelPIOutParam);


	void  Echo(void);

protected:
	EMBL_JOYSTICK_VEL_PI_IN m_stIData;
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
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(void*);

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

unsigned int  JoyVelPICreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyVelPIRemoveObj(unsigned int uiJoyObj);
int  JoyVelPIPost(unsigned int uiJoyObj, void *pData );
int JoyVelPIInit(unsigned int uiJoyObj, EMBL_JOYSTICK_VEL_PI_IN *pInData);
int JoyVelPIPerform(unsigned int uiJoyObj,
						EMBL_JOYSTICK_VEL_PI_IN *pInData,
						EMBL_JOYSTICK_VEL_PI_OUT *pOutData);

#ifdef __cplusplus
}
#endif



#endif /* EMBLJoystickVelPI_H_ */

/*
 * EMBLJoystickVel.h
 *
 *  Created on: Feb 1, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickVel_H_
#define EMBLJoystickVel_H_

#include "EMBLJoystick.h"


typedef struct embl_joystick_vel_in
{
	float fVelocity;
	float fAcceleration;
	float fJerk;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_VEL_IN;


typedef struct embl_joystick_vel_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_VEL_OUT;


#ifdef __cplusplus
class CEmblJoystickVel: public CEmblJoystick {
public:
	CEmblJoystickVel(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickVel();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    EMBL_JOYSTICK_VEL_IN - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_JOYSTICK_VEL_IN *joystickVelInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get a specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             EMBL_JOYSTICK_VEL_IN - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual int Init(EMBL_JOYSTICK_VEL_IN *joystickVelInParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickVelInParam - structure of data relevant for Perform function.
	 output:            joystickVelOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual int Perform(EMBL_JOYSTICK_VEL_IN* joystickVelInParam, EMBL_JOYSTICK_VEL_OUT* joystickVelOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickVelOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int PostPerform(EMBL_JOYSTICK_VEL_OUT* joystickVelOutParam);

	void  Echo(void);

protected:

	EMBL_JOYSTICK_VEL_IN m_stIData;


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

unsigned int  JoyVelCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyVelRemoveObj(unsigned int uiJoyObj);
int  JoyVelPost(unsigned int uiJoyObj, void *pData );

int JoyVelInit(unsigned int uiJoyObj, EMBL_JOYSTICK_VEL_IN *pInData);
int JoyVelPerform(unsigned int uiJoyObj,
					EMBL_JOYSTICK_VEL_IN *pInData,
					EMBL_JOYSTICK_VEL_OUT *pOutData);

#ifdef __cplusplus
}
#endif



#endif /* EMBLJoystickVel_H_ */

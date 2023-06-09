/*
 * EMBLJoystickVel.h
 *
 *  Created on: Feb 1, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickVelAdv_H_
#define EMBLJoystickVelAdv_H_

#include "EMBLJoystick.h"

typedef struct embl_joystick_vel_adv_in
{
	float fVelocity;
	float fAcceleration;
	float fJerk;
	float fDeadZone;
	float fOffset;
	float fGain;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_VEL_ADV_IN;

typedef struct embl_joystick_vel_adv_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_VEL_ADV_OUT;




#ifdef __cplusplus
class CEmblJoystickVelAdv: public CEmblJoystick {
public:
	CEmblJoystickVelAdv(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickVelAdv();


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    JoystickVelAdvInParam - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_JOYSTICK_VEL_ADV_IN* JoystickVelAdvInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get a specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             EMBL_JOYSTICK_VEL_ADV_IN - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_JOYSTICK_VEL_ADV_IN *joystickVelAdvInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:             JoystickVelAdvInParam - structure of data relevant for Perform function.
	output:            JoystickVelAdvOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_JOYSTICK_VEL_ADV_IN* JoystickVelAdvInParam,EMBL_JOYSTICK_VEL_ADV_OUT* JoystickVelAdvOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             JoystickVelAdvOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_JOYSTICK_VEL_ADV_OUT* JoystickVelAdvOutParam);

	void  Echo(void);
protected:

	EMBL_JOYSTICK_VEL_ADV_IN m_stIData;
	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */
	virtual int Init(void*);

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

unsigned int  JoyVelAdvCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyVelAdvRemoveObj(unsigned int uiJoyObj);
int  JoyVelAdvPost(unsigned int uiJoyObj, void *pData );
int JoyVelAdvInit(unsigned int uiJoyObj, EMBL_JOYSTICK_VEL_ADV_IN *pInData);
int JoyVelAdvPerform(unsigned int uiJoyObj,
					EMBL_JOYSTICK_VEL_ADV_IN *pInData,
					EMBL_JOYSTICK_VEL_ADV_OUT *pOutData);

#ifdef __cplusplus
}
#endif



#endif /* EMBLJoystickVelAdv_H_ */

/*
 * EMBLJoystickVel.h
 *
 *  Created on: Feb 1, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickVelExtParam_H_
#define EMBLJoystickVelExtParam_H_

#include "EMBLJoystick.h"


typedef struct embl_joystick_vel_ext_param_in
{
	float fAcceleration;
	float fJerk;
	MMC_PARAMETER_LIST_ENUM eParameterNumber;
	int iParamAxisRef;
	float fDeadZone;
	float fOffset;
	float fGain;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_VEL_EXT_PARAM_IN;

typedef struct embl_joystick_vel_ext_param_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_VEL_EXT_PARAM_OUT;


#ifdef __cplusplus
class CEmblJoystickVelExtParam: public CEmblJoystick {
public:
	CEmblJoystickVelExtParam(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickVelExtParam();

	MMC_READGROUPOFPARAMETERS_IN m_readGruopParamIn;
	MMC_READGROUPOFPARAMETERS_OUT m_readGruopParamOut;


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             joystickVelExtParamIn - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_JOYSTICK_VEL_EXT_PARAM_IN *joystickVelExtParamIn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    joystickVelExtParamIn - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef, EMBL_JOYSTICK_VEL_EXT_PARAM_IN* joystickVelExtParamIn);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:             joystickPosPiInParam - structure of data relevant for Perform function.
	output:            joystickPosPiOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_JOYSTICK_VEL_EXT_PARAM_IN* joystickVelExtParamIn, EMBL_JOYSTICK_VEL_EXT_PARAM_OUT *joystickVelExtParamOut);

	/**
	 * \fn PostPerform()
	 * \brife: Execution of methods after the preform ended.
	 * \return none.
	 */
	virtual int PostPerform(EMBL_JOYSTICK_VEL_EXT_PARAM_OUT* joystickVelExtParamOut);



	void  Echo(void);
protected:
	EMBL_JOYSTICK_VEL_EXT_PARAM_IN m_stIData;
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

unsigned int  JoyVelExtParamCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyVelExtParamRemoveObj(unsigned int uiJoyObj);
int  JoyVelExtParamPost(unsigned int uiJoyObj, void *pData );
int JoyVelExtParamInit(unsigned int uiJoyObj, EMBL_JOYSTICK_VEL_EXT_PARAM_IN *pInData);
int JoyVelExtParamPerform(unsigned int uiJoyObj,
							EMBL_JOYSTICK_VEL_EXT_PARAM_IN *pInData,
							EMBL_JOYSTICK_VEL_EXT_PARAM_OUT *pOutData);

#ifdef __cplusplus
}
#endif



#endif /* EMBLJoystickVelExtParam_H_ */

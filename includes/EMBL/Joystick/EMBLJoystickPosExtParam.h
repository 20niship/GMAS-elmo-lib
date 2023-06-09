/*
 * EMBLJoystickPosition.h
 *
 *  Created on: Jan 29, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystickPosExtParam_H_
#define EMBLJoystickPosExtParam_H_

#include "EMBLJoystick.h"

typedef struct embl_joystick_pos_ext_param_in
{
	float fVelocity;
	float fAcceleration;
	float fJerk;
	MMC_PARAMETER_LIST_ENUM eParameterNumber;
	int iParamAxisRef;
	float fDeadZone;
	float fOffset;
	float fGain;
	unsigned char ucAbortCmd;
	unsigned char ucOffsetMode;
}EMBL_JOYSTICK_POS_EXT_PARAM_IN;

typedef struct mmc_joystick_pos_ext_param_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_JOYSTICK_POS_EXT_PARAM_OUT;

#ifdef __cplusplus
class CEmblJoystickPosExtParam: public CEmblJoystick {
public:
	CEmblJoystickPosExtParam(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystickPosExtParam();

	MMC_MOVEABSOLUTE_IN 	m_stMoveAbsInParams;
	MMC_MOVEABSOLUTE_OUT	m_stMoveAbsOutParams;

	MMC_READGROUPOFPARAMETERS_IN m_readGruopParamIn;
	MMC_READGROUPOFPARAMETERS_OUT m_readGruopParamOut;

	//double m_dPrevReading;


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
                    	usAxisRef - axis reference.
                        EMBL_JOYSTICK_POS_EXT_PARAM_IN* - pointer to the relevant data that should be use the Initialize class members
 	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_JOYSTICK_POS_EXT_PARAM_IN * joystickPosExtInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get a specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             EMBL_JOYSTICK_POS_EXT_PARAM_IN - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_JOYSTICK_POS_EXT_PARAM_IN *joystickPosExtInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickPosExtInParam - structure of data relevant for Perform function.
	 output:            joystickPosExtOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_JOYSTICK_POS_EXT_PARAM_IN *joystickPosExtInParam, EMBL_JOYSTICK_POS_EXT_PARAM_OUT *joystickPosExtOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickPosExtOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_JOYSTICK_POS_EXT_PARAM_OUT *joystickPosExtOutParam);

	void  Echo(void);

protected:
	EMBL_JOYSTICK_POS_EXT_PARAM_IN m_stIData;
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

int JoyPosExtParamPerform(unsigned int uiJoyObj,
							EMBL_JOYSTICK_POS_EXT_PARAM_IN *pInDat,
							EMBL_JOYSTICK_POS_EXT_PARAM_OUT *pOutData);


unsigned int  JoyPosExtParamCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  JoyPosExtParamRemoveObj(unsigned int uiJoyObj);
int  JoyPosExtParamPost(unsigned int uiJoyObj, void *pData );
int JoyPosExtParamInit(unsigned int uiJoyObj,  EMBL_JOYSTICK_POS_EXT_PARAM_IN *pInData);

#ifdef __cplusplus
}
#endif


#endif /* EMBLJoystickPosExtParam_H_ */

/*
 * CEmblHome.h
 *
 *  Created on: Jan 28, 2015
 *      Author: ZivB
 */

#ifndef EMCHOME_H_
#define EMCHOME_H_

#include "EMBLObject.h"
#include <mmc_definitions.h>
#include "MMC_drive_comm_API.h"
#include "EMBLDefinitions.h"
#include "MMC_general_API.h"





typedef enum{eVALIDATE_HOMING_METHOD=0,
			eLOCK_AND_CHANGE_TCH_PROBE_MOD=1,eVALIDATE_NEW_TCH_PROBE_MOD=2,
			eLOCK_AND_CHANGE_OPT_COMP_MOD=3,eVALIDATE_NEW_OPT_COMP_MOD=4,
			eLOCK_AND_CHANGE_POS_CAPT_MOD=5,eVALIDATE_NEW_POS_CAPT_MOD=6,
			eLOCK_AND_CHANGE_OP_MOD=7, eVALIDATE_NEW_OP_MOD=8,
			eENBABLE_AXIS=9, eVALIDATE_STANDSTILL=10,
			eEXECUTE_HOME=11, eHOME_ATTAIN=12,
			eBACK_TO_ORIGI_OP_MOD=13,eVALIDATE_ORIGI_OP_MODE=14,
			eBACK_TO_ORIGI_TCH_PROBE_MOD=15,eVALIDATE_ORIGI_TCH_PROBE_MOD=16,
			eBACK_TO_ORIGI_POS_CAPT_MOD=17,eVALIDATE_ORIGI_POS_CAPT_MOD=18,
			eBACK_TO_ORIGI_OPT_COMP_MOD=19,eVALIDATE_ORIGI_OPT_COMP_MOD=20,
			eFINAL_STATE=21
} eHOME_STATE;


typedef enum
{
  ePOSITIVE_DIR  = 0,
  eNEGATIVE_DIR  = 1
}EMBL_DIRECTION_ENUM;

typedef enum
{
	eHOME_SW		   = 0,
	eHOME_AND_FLS_SW   = 1,
	eHOME_AND_RLS_SW   = 2

}EMBL_HOME_AND_LIMIT_SWITCH_ENUM;

typedef enum
{
  eFLS_SW   = 0,
  eRLS_SW   = 1,
}EMBL_LIMIT_SWITCH_ENUM;


typedef enum
{
  eRISING_EDGE  = 0,
  eFALLING_EDGE = 1
}EMBL_SWITCH_MOD_ENUM;

typedef enum
{
	eQUEUED = 0,
	ePARALLEL = 1
}EMBL_QUEUEING_RULES_ENUM;

typedef struct mmc_home_on_block
{
	unsigned short 	usPowerEnable;
	double 			dbPosition;
	double 			dbDetectionVelocityLimit;
	float 			fAcceleration;
	float 			fVelocity;
	float 			fDistanceLimit;
	float 			fTorqueLimit;
	unsigned int 	uiTimeLimit;
	unsigned int 	uiDetectionTimeLimit;
	int 			uiHomingMethod;
}EMBL_HOME_ON_BLOCK;

typedef struct mmc_home_immediate
{
	unsigned short 	usPowerEnable;
	double 			dbPosition;
	unsigned int 	uiTimeLimit;
}EMBL_HOME_IMMEDIATE;



typedef struct embl_home_on_limit_in
{
	unsigned short 			usPowerEnable;
	unsigned short          usUseIndexPulse;
	EMBL_LIMIT_SWITCH_ENUM  eLimitSw;
	double              	dHomePosition;
	float                	fAcceleration;
	double               	fVelocityHigh;
    double               	fVelocityLow;
	unsigned int         	uiTimeLimit;
}EMBL_HOME_ON_LIMIT_IN;

typedef struct embl_home_on_homesw_in
{
	unsigned short 						usPowerEnable;
	unsigned short          			usUseIndexPulse;
	EMBL_HOME_AND_LIMIT_SWITCH_ENUM		eLimitSw;
	EMBL_SWITCH_MOD_ENUM 				eHomeSwitchMode;
	EMBL_DIRECTION_ENUM     			eDirection;
	double              				dHomePosition;
	float                				fAcceleration;
	double               				fVelocityHigh;
    double               				fVelocityLow;
	unsigned int         				uiTimeLimit;
}EMBL_HOME_ON_HOMESW_IN;

typedef struct embl_home_on_index_in
{
	unsigned short 			usPowerEnable;
	EMBL_DIRECTION_ENUM     eDirection;
	float                   fAcceleration;
	double                  dHomePosition;
	double                  fVelocity;
	unsigned int            uiTimeLimit;
}EMBL_HOME_ON_INDEX_IN;

typedef struct embl_multi_ax_home_on_index_in
{
	unsigned short 			usPowerEnable;
	EMBL_DIRECTION_ENUM     eDirection;
	float                   fAcceleration;
	double                  *pHomePosition;
	double                  fVelocity;
	unsigned int            uiTimeLimit;
}EMBL_MULTI_AX_HOME_ON_INDEX_IN;

typedef struct mmc_multi_ax_home_on_block
{
	unsigned short 	usPowerEnable;
	double 			*pHomePosition;
	double 			dbDetectionVelocityLimit;
	float 			fAcceleration;
	float 			fVelocity;
	float 			fDistanceLimit;
	float 			fTorqueLimit;
	unsigned int 	uiTimeLimit;
	unsigned int 	uiDetectionTimeLimit;
	int 			uiHomingMethod;
}EMBL_MULTI_AX_HOME_ON_BLOCK;

typedef struct mmc_multi_ax_home_immediate
{
	unsigned short 	usPowerEnable;
	double 			*pHomePosition;
	unsigned int 	uiTimeLimit;
}EMBL_MULTI_AX_HOME_IMMEDIATE;

typedef struct embl_multi_ax_home_on_homesw_in
{
	unsigned short 						usPowerEnable;
	unsigned short          			usUseIndexPulse;
	EMBL_HOME_AND_LIMIT_SWITCH_ENUM		eLimitSw;
	EMBL_SWITCH_MOD_ENUM 				eHomeSwitchMode;
	EMBL_DIRECTION_ENUM     			eDirection;
	double              				*pHomePosition;
	float                				fAcceleration;
	double               				fVelocityHigh;
    double               				fVelocityLow;
	unsigned int         				uiTimeLimit;
}EMBL_MULTI_AX_HOME_ON_HOMESW_IN;

typedef struct embl_multi_ax_home_on_limit_in
{
	unsigned short 			usPowerEnable;
	unsigned short          usUseIndexPulse;
	EMBL_LIMIT_SWITCH_ENUM  eLimitSw;
	double              	*pHomePosition;
	float                	fAcceleration;
	double               	fVelocityHigh;
    double               	fVelocityLow;
	unsigned int         	uiTimeLimit;
}EMBL_MULTI_AX_HOME_ON_LIMIT_IN;
/*
typedef enum
{
	eDOWNLOAD = 1,
	eUPLOAD = 2
}SDO_SERVICE;
*/
typedef struct
{
	unsigned int   uiHndl;		///< Returned function block handle.
	short *pErrorID;			///< Returned command error ID.
	unsigned short usStatus;	///< Returned command status.
	unsigned short usAxisRef;
}EMBL_HOME_OUT_MULTI_AXIS;


#define EMBL_VERIFICATION_TIMEOUT 2000000// time  [usec]
#define EMBL_MAX_CYCLE_TIME_COUNTER UINT_MAX //0xffffffff
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

unsigned int CalculateHomingMethodHomeSw(unsigned short usUseIndexPulse,EMBL_DIRECTION_ENUM eDirection, EMBL_SWITCH_MOD_ENUM eHomeSwitchMode);
unsigned int CalculateHomingMethodHomeSwAndFLS(unsigned short usUseIndexPulse,EMBL_DIRECTION_ENUM eDirection, EMBL_SWITCH_MOD_ENUM eHomeSwitchMode);
unsigned int CalculateHomingMethodHomeSwAndRLS(unsigned short usUseIndexPulse,EMBL_DIRECTION_ENUM eDirection, EMBL_SWITCH_MOD_ENUM eHomeSwitchMode);
unsigned short CheckHomingMethodForFeddbackSensor(unsigned short HomingMethod, unsigned short SensorID);

class CEmblHome: public EMBLObject {
public:
	CEmblHome(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblHome();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:
	output:            homeOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(MMC_HOME_OUT *homeOutParam);

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

	short CheckTimeOutElapsed(unsigned int &uiLastTimeOut);
	unsigned short ResetTimeOutCounter();
	CEmblHome(){TRACE("CEmblHome()\n")}// {m_uiX = (unsigned int)this; fprintf(stderr, "X=0x%X\n", m_uiX);}


public:
	MMC_HOMEDS402EX_IN m_HommingData;

//	int WriteCommandViaSdo(char* pCmd, unsigned char ucSubIndex, long lData, unsigned long ulDataLength);
//	int ReadCommandViaSdo (char *pCmd, unsigned char ucSubIndex, long &lOut, unsigned long ulDataLength);
	inline void SetPowerEnable(unsigned short usPowerEnable) {m_usPowerEnable = usPowerEnable;}
	inline void SetState(int iState) {m_iState = iState;}
	inline void SetHandle(unsigned int uiHandle) {m_uiHandle = uiHandle;}

	inline void SetLastCycleTimeCounter(unsigned int uiLastCycleTimeCounter) {m_uiLastCycleTimeCounter = uiLastCycleTimeCounter;}
	inline void SetVerificationTimeCounter(unsigned int uiVerificationTimeCounter) {m_uiVerificationTimeCounter = uiVerificationTimeCounter;}
	inline void SetCycleTime(unsigned int uiCycleTime) {m_uiCycleTime = uiCycleTime;}
	inline unsigned int GetLastCycleTimeCounter() {return m_uiLastCycleTimeCounter;}
	inline unsigned int GetVerificationTimeCounter() {return m_uiVerificationTimeCounter;}
	inline unsigned int GetCycleTime() {return m_uiCycleTime;}
//	inline void SetLastTimeOut(unsigned int uiLastLastTimeOut) {m_uiLastLastTimeOut = uiLastLastTimeOut;}
//	inline unsigned int GetLastTimeOut(){return m_uiLastLastTimeOut;}



protected:

	int m_iOpMode;
	unsigned short m_usTouchProbeMode;
	int m_iOutputCompareMode[2];
	int m_iPositionCaptureMode[2];
	unsigned short m_usPowerEnable;
	unsigned int m_uiLastCycleTimeCounter;
	unsigned int m_uiVerificationTimeCounter;
	unsigned int m_uiCycleTime;
	unsigned int m_uiHomingTimeout;
	//unsigned int m_uiZ;
	int state ;

	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */
	virtual int Init(void *);
	/**
	 * \fn Perform(void *pOData)
	 * \brief this function performs the complete stages, which are required by home task.
	 * \In param :
	 * \void *pOData - pointer to output param MMC_HOME_OUT(status , error id , fb handle)
	 * \return 0 if completed successfully, otherwise error.
	 */
	virtual int Perform(void *);

	/**
	 * \fn PostPerform()
	 * \brife: Execution of methods after the preform ended.
	 * \return none.
	 */
	virtual int PostPerform(void *);

private:
	unsigned short ConvertCmdToIndex(char *pCmd);
};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

int HomePerform(unsigned int uiHomObj, MMC_HOME_OUT *);
void  Echo(unsigned int uiHomObj);

#ifdef __cplusplus
}
#endif



#endif /* EMCHOME_H_ */

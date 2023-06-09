/*
 * EMBLFeedbackEmulation.h
 *
 *  Created on: 28/05/2015
 *      Author: ilia
 */

#ifndef EMBLFEEDBACKEMULATION_H_
#define EMBLFEEDBACKEMULATION_H_

#include "EMBLObject.h"
#include <mmc_definitions.h>
#include "MMC_drive_comm_API.h"
#include "EMBLDefinitions.h"
#include "MMC_general_API.h"
#include "EMBLSendCommandBySDO.h"

typedef enum
{
  eEM_PORTC_A_B = 0,//val for SDO =1,  // GO[14]=5 and GO[15]=5
  eEM_PORTC_A_I = 1,//val for SDO =2,  // GO[14]=5 and GO[16]=5
  eEM_PORTC_B_I = 2,//val for SDO =3,  // GO[15]=5 and GO[16]=5
  eEM_PORTC_A   = 3,//val for SDO =14, // GO[14]=5
  eEM_PORTC_B   = 4,//val for SDO =15, // GO[15]=5
  eEM_PORTC_I   = 5,//val for SDO = 16  // GO[16]=5
}EMBL_EMUL_OUTPUT_ENUM;

typedef enum
{
	eEMULATION_DISABLE 		= 0,
	eQUADRATURE_WAVE_SIGNAL	= 1,
	ePULSE_DIR_WAVE_SIGNAL	= 2,
	eUP_DOWN_WAVE_SIGNAL	= 3,
	eHALL_SIGNAL			= 4,
	ePWM_100_AND_PULSE_DIR	= 5,
	ePWM_50					= 6
}EMBL_EMULATION_OUTPUT_SIGNAL_ENUM;

typedef enum
{
	eVEL_COMMAND		= 1,
	eVEL_SOCKET			= 2,
	eCURRENT_COMMAND	= 4,
	eCURRENT_FEEDBACK	= 5,
	eCURRENT_SOCKET		= 6
}EMBL_PWM_SOURCE_SELECT_ENUM;

typedef enum
{
	e1000Hz = 1,
	e1500Hz = 2,
	e2000Hz = 3,
	e2500Hz = 4,
	e3000Hz = 5,
	e3500Hz = 6,
	e4000Hz = 7,
	e4500Hz = 8,
	e5000Hz = 9,
	e5500Hz = 10,
	e6000Hz = 11,
	e6500Hz = 12,
	e7000Hz = 13,
	e7500Hz = 14,
	e8000Hz = 15,
	e8500Hz = 16,
	e9000Hz = 17,
	e9500Hz = 18,
	e10000Hz = 19,
	e12000Hz = 20,
	e14000Hz = 21,
	e16000Hz = 22,
	e18000Hz = 23,
	e20000Hz = 24,
	e30000Hz = 25,
	e40000Hz = 26,
	e50000Hz = 27,
	e60000Hz = 28,
	e70000Hz = 29,
	e80000Hz = 30,
	e90000Hz = 31,
	e100000Hz = 32,
	e200000Hz = 33
}EMBL_PWM_FREQUENCY_ENUM;

typedef enum
{
	eINTERNAL	= 0,
	eAQB_SOCKET	= 1
}EMBL_FEEDBACK_TYPE_ENUM;

typedef enum
{
	eEM_OUT_AQB_B	= 13,
	eEM_OUT_AQB_A	= 14
}EMBL_EMULATION_OUT_AQB_ENUM;


typedef enum
{
	eSOURCE_PORT_A	= 0,
	eSOURCE_PORT_B	= 1
}EMBL_SOURCE_PORT_ENUM;



//typedef enum
//{
//	eDIR_AS_EMULATED_ENCODER_NOT_BIND		= 0, // bit0 == 0 , bit1 ==0
//	eDIR_INVERSED_EMULATED_ENCODER_NOT_BIND	= 1, // bit0 == 1 , bit1 ==0
//	eDIR_AS_EMULATED_ENCODER_BIND_SO		= 2, // bit0 == 0 , bit1 ==1
//	eDIR_INVERSED_EMULATED_ENCODER_BIND_SO	= 3  // bit0 == 1 , bit1 ==1
//}EMBL_EMU_DIR_AND_BIND_ENUM;

typedef struct embl_feedback_emulation_in
{
	EMBL_SOURCE_PORT_ENUM				eSourcePort;			// eSOURCE_PORT_A or eSOURCE_PORT_B
	EMBL_EMULATION_OUTPUT_SIGNAL_ENUM		eEmulationOutput;	//EA[1]
	unsigned long					ulEmulatedSocketPos; //FP[EmSocketNum]
	EMBL_EMULATION_OUT_AQB_ENUM     eEmulationOutAqB;
	unsigned short					usPulseWidth; 		//EA[2]
	long							lDescription; 		//EA[3] bit 0 - Emulation direction , bit 1 - bind to Servo enable (SO)
	EMBL_SOCKET_ENUM				eEmulatedSocket;	//EA[4] 1-4 for PWM 0
	EMBL_SOCKET_ENUM				eEmulationOutSocket; // CA[40+eEmulationOutSocket]= 13 or 14
	unsigned long					ulMultiplier;		//EA[6] N=0 to 2147483647
	unsigned long					ulScaleFactor;		//EA[7] N=0 to 30
	EMBL_FEEDBACK_TYPE_ENUM			eFeedbackType;		//EA[8] value=0 internal feedback, value=1 AqB feedback
	EMBL_PWM_SOURCE_SELECT_ENUM		ePWMSource;			//EA[9]
	EMBL_PWM_FREQUENCY_ENUM			ePWMFrequency;		//EA[10]
	long							lSpeedMinVal;		//EA[12] //UserUnit/sec
	long							lSpeedMaxVal;		//EA[13] //UserUnit/sec
	long							lCurrentMinVal;		//EA[14]  miliAmpere
	long							lCurrentMaxVal;		//EA[15]  miliAmpere
	long							lPWMMinVal;			//EA[16]  %
	long							lPWMMaxVal;			//EA[17]  %
	EMBL_EMUL_OUTPUT_ENUM			eEmulationOutPort;
}EMBL_FEEDBACK_EMULATION_IN;

typedef struct embl_quad_emulation_in
{
	unsigned short	                     usActivate;           // activate==1/ deactivate==0 emulation
	EMBL_SOURCE_PORT_ENUM				eSourcePort;			// PortA or PortB
	EMBL_SOCKET_ENUM					eEmulatedSocket;	//EA[4] 1-4
	unsigned short						usEmulationDir;     // 0 - similar as encoder; 1 - inverst; bit 0 - Emulation direction
	unsigned short						usBindToServo;      // 0 - NOT bind to SO; 1-Bind to SO;    bit 1 - bind to Servo enable (SO)
	unsigned long						ulMultiplier;		//EA[6] N=1 to 2147483647
	unsigned long						ulScaleFactor;		//EA[7] N=0 to 30
	EMBL_FEEDBACK_TYPE_ENUM		    	eFeedbackType;		//EA[8] value=0 internal feedback, value=1 AqB feedback
	EMBL_EMUL_OUTPUT_ENUM			    eEmulationOutPort;

	//unsigned long						ulEmulatedSocketPos; //FP[EmSocketNum]
	//EMBL_EMULATION_OUT_AQB_ENUM     	eEmulationOutAqB;
}EMBL_QUAD_EMULATION_IN;




typedef enum embl_feedback_em_state_enum
{
	eLOCK_FREE_SOCKET_STATE				= 0,
	eLOCK_EMULATED_SOCKET_POS_STATE		= 1,
	eLOCK_DICRIPTION_VAL_STATE			= 2,
	eINIT_DATA_ARR_STATE				= 3,
	eSEND_EM_DATA_ARRAY_STATE			= 4,
	eEM_FINAL_STATE						= 5
}EMBL_EMULATION_STATE;


#ifdef __cplusplus



class CEmblFeedbackEmulation : public EMBLObject{
public:
	CEmblFeedbackEmulation(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblFeedbackEmulation();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:
	output:            outParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int Perform(EMBL_OUT *outParam);

	void  Echo(void);


	CEmblFeedbackEmulation() {}


public:
	EMBL_FEEDBACK_EMULATION_IN m_FeedbackEmulationDataIn;

	CEMBLSendCommandBySDO* m_pCEMBLSendCommandBySDO;
	unsigned short m_LastEmulationOutSocket;
	CEMBLWriteSdoData* m_pWriteSdoDataArray[MAX_COMMANDS_ARRAY_SIZE];


protected:
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

	int InitSdoDataArrayEmQUAD();
	void DeinitSdoDataArray();
	int PerformEmulationDisable(void *pOData);
	int PerformEmulationQuadWaveSignal(void *pOData);
	int LockEmulationOutSocket();
	int GetDescriptionValue(void);
	int GetEmulatedSocketPos(void);
	long CalcEmulDescription(unsigned short usEmulationDir,unsigned short	usBindToServo);

};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

int FeedbackEmulationPerform(unsigned int uiFeObj, EMBL_OUT *);
void  FeedbackEmulationEcho(unsigned int uiFeObj);

#ifdef __cplusplus
}
#endif

#endif /* EMBLFEEDBACKEMULATION_H_ */

/*
 * EMBLOutputCompare.h
 *
 *  Created on: 12/05/2015
 *      Author: ilia
 */

#ifndef EMBLOUTPUTCOMPARE_H_
#define EMBLOUTPUTCOMPARE_H_
#include "EMBLDefinitions.h"
#include "EMBLObject.h"
#include "Feedback/EMBLFeedbackQuadEmulation.h"

//types for general use

typedef enum
{
	eMODULE_OC1  = 0,  // OC[1 to 12 //PORT B
	eMODULE_OC2  = 1  // OC[21 to 32]  //PORT A
}EMBL_OC_MODULE_ENUM;

typedef enum
{
  eOUTPUT_1  = 0, // GO[1]
  eOUTPUT_2  = 1, // GO[2]
  eOUTPUT_3  = 2, // GO[3]
  eOUTPUT_4  = 3, // GO[4]
  ePORTC_A   = 4, // GO[14]
  ePORTC_B   = 5, // GO[15]
  ePORTC_I   = 6  //  GO[16]
}EMBL_OC_OUTPUT_ENUM;

typedef enum
{
  ePOSITION_FEEDBACK  = 0,
  eSOCKET_1  = 1,
  eSOCKET_2  = 2,
  eSOCKET_3  = 3,
  eSOCKET_4  = 4
}EMBL_OC_SOURCE_SIGNAL_ENUM;
typedef enum
{
   eARRAY_ZX = 0,
   eARRAY_NT = 1,
   eARRAY_ET = 2,
   eARRAY_UI = 3,
   eARRAY_BH = 4,

}EMBL_OC_ARRAY_SELECTION_ENUM;

typedef enum
{
   eBOTH_DIR = 0,
   ePOS_DIR	 = 1,
   eNEG_DIR  = 2
}EMBL_OC_AXIS_DIRECTION_ENUM;

typedef enum
{
  eOC_DISABLE			= 0,
  eOC_ABS_POS			= 1,
  eOC_POS_TAB_BASED		= 3,
  eOC_TIME_TAB_BASED	= 4
 }EMBL_OC_OUTPUT_COMPARE_MODE_ENUM;

typedef enum
 {
 	eNOT_EMULATION		= 0,
 	eWITH_EMULATION		= 1
 } EMBL_REQUESTS_EMULATION_ENUM;

typedef enum
{
	eNEGATIVE_LOGIC = 0,
	ePOSITIVE_LOGIC	= 1
} EMBL_OC_LOGIC_LEVEL_ENUM;


/*
typedef enum
{
	eINIT = 1,
	eACTIVATE	= 2
} EMBL_OC_ACTIVATE_ENUM;
*/

typedef enum
{
	eCONVERT 		= 0,
	eNOT_CONVERT	= 1
} EMBL_OC_CONVERT_TAB_ENUM;


 typedef struct embl_output_compare_in
 {
//	EMBL_OC_ACTIVATE_ENUM 				eActivate;
	EMBL_REQUESTS_EMULATION_ENUM        eEmulationRequests;
	//EMBL_FEEDBACK_SOURCE_PORT_ENUM 		eSourceSignalPort;		// PortA or PortB
	unsigned char  				        ucOCModuleIndex;		//for port A index+20  (1 to 12 <=> 21 to 32)
 	EMBL_OC_OUTPUT_COMPARE_MODE_ENUM 		eOCMode;				//OC[1+ePort]	 - OC[1]==1 & OC[1]==3,4
 	long					    		lStartPosition;			//OC[2+ePort]    - OC[1]==1 only
 	long								lPulsesInterval;		//OC[3+ePort]	 - OC[1]==1 & OC[1]==3,4
 	unsigned int						uiPulseDuration;		//OC[4+ePort]	 - OC[1]==1 & OC[1]==3,4
 	unsigned int						uiPulsesNumber;			//OC[5+ePort]	 - OC[1]==1 only
 	EMBL_OC_SOURCE_SIGNAL_ENUM			    eSourceSignal;			//OC[6+ePort]    - OC[1]==1 & OC[1]==3,4
 	EMBL_OC_ARRAY_SELECTION_ENUM			eArraySelection;		//OC[7+ePort]	 - OC[1]==3,4 only
 	double             	     			*pTableArr;
	unsigned short						usTableArrSize;
 	unsigned int					    uiFirstIndex;			//OC[8+ePort]	 - OC[1]==3,4 only
 	unsigned int					    uiLastIndex;			//OC[9+ePort]	 - OC[1]==3,4 only
 	EMBL_OC_AXIS_DIRECTION_ENUM			eAxisDirection;			//OC[10+ePort]   - OC[1]==3,4 only
 //	unsigned short						eConvertTable;			//OC[11+ePort]   - OC[1]==3,4 only
 	unsigned char				    	ucOutputSource; 		//GO[eOutputSource]==1 for ePORT_B   GO[eOutputSource]==2 for ePORT_A
 	EMBL_OC_LOGIC_LEVEL_ENUM			eLogicLevel;
 }EMBL_OUTPUT_COMPARE_IN;

// types for OC on abs position
typedef struct embl_oc_abs_pos_in
{
	//EMBL_FEEDBACK_SOURCE_PORT_ENUM 		eSourceSignalPort;		// PortA or PortB
	EMBL_OC_MODULE_ENUM	    			eModuleOC;
	long					    		lStartPosition;
	long								lPulsesInterval;
	unsigned int						uiPulseDuration;
	unsigned int						uiPulsesNumber;
	EMBL_OC_SOURCE_SIGNAL_ENUM     		eSourceSignal;
    EMBL_OC_OUTPUT_ENUM					eOutputSource;
    EMBL_OC_LOGIC_LEVEL_ENUM			eLogicLevel;
}EMBL_OC_ABS_POS_INIT_IN;

typedef enum
 {
   eOC_ABS_POS_DEACTIVATE  = 0,
   eOC_ABS_POS_ACTIVATE  = 1,
   eOC_ACTIVATE_POS_UPDATE  = 2,
   eOC_ACTIVATE_PULSE_INTERVAL_UPDATE = 3,
   eOC_ACTIVATE_POS_AND_PULSE_INTERVAL_UPDATE = 4
 }EMBL_OC_ABS_POS_ACTIVATE_ENUM;

typedef struct embl_oc_abs_pos_activate_in
{
	EMBL_OC_MODULE_ENUM	            eModuleOC;
    EMBL_OC_ABS_POS_ACTIVATE_ENUM   eOCActivate;
	long							lStartPosition;
	long				            lPulsesInterval;
} EMBL_OC_ABS_POS_ACTIVATE_IN;

// types for OC on Tab Position
typedef struct embl_oc_pos_tab_init_in
{
	//EMBL_FEEDBACK_SOURCE_PORT_ENUM 		eSourceSignalPort;		// PortA or PortB
	EMBL_OC_MODULE_ENUM			eModuleOC;
	double             	     	*pPosTableArr;
	unsigned short				usTableArrSize;
	EMBL_OC_ARRAY_SELECTION_ENUM	eArraySelection;
	unsigned int				uiFirstIndex;
	unsigned int				uiLastIndex;
	EMBL_OC_AXIS_DIRECTION_ENUM	eAxisDirection;
//	unsigned short				eConvertTable;
	EMBL_OC_SOURCE_SIGNAL_ENUM	eSourceSignal;
    EMBL_OC_OUTPUT_ENUM		    eOutputSource;
    EMBL_OC_LOGIC_LEVEL_ENUM	eLogicLevel;
} EMBL_OC_POS_TAB_INIT_IN;

typedef enum
{
  eOC_POS_TAB_DEACTIVATE  					= 0,
  eOC_POS_TAB_ACTIVATE						= 1,
  eOC_POS_TAB_ACTIVATE_INDEX_UPDATE			= 2,
  eOC_POS_TAB_ACTIVATE_DIR_UPDATE			= 3,
  eOC_POS_TAB_ACTIVATE_INDEX_AND_DIR_UPDATE	= 4
}EMBL_OC_POS_TAB_ACTIVATE_ENUM;

typedef struct embl_oc_pos_tab_active_in
{
	EMBL_OC_MODULE_ENUM         	eModuleOC;
	EMBL_OC_POS_TAB_ACTIVATE_ENUM  	eOCActivate;
	unsigned int					uiFirstIndex;
	unsigned int					uiLastIndex;
	EMBL_OC_AXIS_DIRECTION_ENUM		eAxisDirection;
}EMBL_OC_POS_TAB_ACTIVE_IN;

// types for OC on Tab Time
typedef struct embl_oc_time_tab_in
{
	EMBL_OC_MODULE_ENUM         eModuleOC;
    unsigned int				uiPulseDuration;
    double              	    *pPosTableArr;
	unsigned short				usTableArrSize;
	EMBL_OC_ARRAY_SELECTION_ENUM	eArraySelection;
	unsigned int				uiFirstIndex;
	unsigned int				uiLastIndex;
	EMBL_OC_AXIS_DIRECTION_ENUM	eAxisDirection;
	EMBL_OC_SOURCE_SIGNAL_ENUM	 eSourceSignal;
	EMBL_OC_OUTPUT_ENUM		    eOutputSource;
	EMBL_OC_LOGIC_LEVEL_ENUM	eLogicLevel;
} EMBL_OC_TIME_TAB_INIT_IN;

typedef enum
{
  eOC_TIME_TAB_DEACTIVATE  						= 0,
  eOC_TIME_TAB_ACTIVATE  						= 1,
  eOC_TIME_TAB_ACTIVATE_INDEX_UPDATE 			= 2,
  eOC_TIME_TAB_ACTIVATE_DIR_UPDATE				= 3,
  eOC_TIME_TAB_ACTIVATE_INDEX_AND_DIR_UPDATE	= 4
}EMBL_OC_TIME_TAB_ACTIVATE_ENUM;

typedef struct embl_oc_time_tab_activate_in
{
	EMBL_OC_MODULE_ENUM	             	eModuleOC;
	EMBL_OC_TIME_TAB_ACTIVATE_ENUM		eOCActivate;
	unsigned int						uiFirstIndex;
	unsigned int						uiLastIndex;
	EMBL_OC_AXIS_DIRECTION_ENUM		 	eAxisDirection;
}EMBL_OC_TIME_TAB_ACTIVATE_IN;

//types for OC Single Pulse
typedef enum
{
  eOC_SP_DEACTIVATE				= 0,
  eOC_SP_ACTIVATE				= 1,
  eOC_SP_ACTIVATE_POS_UPDATE	= 2
}EMBL_OC_SINGLE_PULSE_ACTIVATE_ENUM;

typedef struct embl_oc_single_pulse_init_in
{
	EMBL_OC_MODULE_ENUM         eModuleOC;
	long				        lStartPosition;
	long   				        lEndPosition;
	EMBL_OC_AXIS_DIRECTION_ENUM	eAxisDirection;
	EMBL_OC_SOURCE_SIGNAL_ENUM	eSourceSignal;
    EMBL_OC_OUTPUT_ENUM		    eOutputSource;
    EMBL_OC_LOGIC_LEVEL_ENUM	eLogicLevel;
} EMBL_OC_SINGLE_PULSE_INIT_IN;

typedef struct embl_oc_single_pulse_activate_in
{

	EMBL_OC_MODULE_ENUM         		eModuleOC;
	EMBL_OC_SINGLE_PULSE_ACTIVATE_ENUM	eOCActivate;
	long				        		lStartPosition;
	long   				        		lEndPosition;
//	unsigned short						eConvertTable;
} EMBL_OC_SINGLE_PULSE_ACTIVATE_IN;


typedef enum
{
	eMODE 					= 1,
	ePOSITION 				= 2,
	ePULSE_INTERVAL 		= 3,
	ePULSE_DUR				= 4,
	ePULSE_NUM 				= 5,
	eSOURSE_SIGNAL  		= 6,
	eARRAY_SELECT			= 7,
	eFIRST_INDX				= 8,
	eLAST_INDX				= 9,
	eAXIS_DIR				= 10,
	eCONV_TAB				= 11,
	eOUTPUT_SOURCE  		= 17
}EMBL_OC_INDEX;



typedef enum
{
	eVALIDATE_PARAM_STATE		= 0,
	eSTART_EMULATION_STATE     	= 1,
	eINIT_OC_TAB_ARR_STATE		= 2,
	eSEND_OC_DATA_ARRAY_STATE	= 3,
//	eCONV_OC_TAB_ARR_STATE		= 4,
	eOC_FINAL_STATE    			= 100
}EMBL_OC_STATE_MACHINE;


#ifdef __cplusplus
class CEMBLOutputCompare: public EMBLObject {
public:

	EMBL_OUTPUT_COMPARE_IN m_OutputCompareData;
	CEMBLSendCommandBySDO *m_pCEMBLSendCommandBySDO;
	CEMBLWriteSdoData* m_pWriteSdoDataArray[MAX_COMMANDS_ARRAY_SIZE];
	//CEmblFeedbackQuadEmulation *m_pCEmblFeedbackQuadEmulation;
	double m_dOCPointsArr[2];
	unsigned short CalculatePulseDuration(unsigned short usPulseDuratuinTime );
	long CalculateUsedOCModule(EMBL_OC_MODULE_ENUM eModuleOC,unsigned char &ucOCModuleIndex);
	CEMBLOutputCompare(unsigned int uiConn, unsigned short usAxisRef);
	unsigned char CalcGOSubindex( EMBL_OC_OUTPUT_ENUM OutputSource);
	CEMBLOutputCompare() {}
	virtual ~CEMBLOutputCompare();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             outputCompareInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_OUTPUT_COMPARE_IN *outputCompareInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
						overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
						usAxisRef - axis reference.
						outputCompareInParam pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_OUTPUT_COMPARE_IN *outputCompareInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:
	output:            outParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int Perform(EMBL_OUT *outParam);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
						Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             outParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_OUT* outParam);


	void  Echo(void);
protected:
	unsigned short m_usPointsArrayCount;
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
	int DeactivateOC();
	int OCAbsPosInitPerform(void *pOData);
	int PerformOCWithEmulation(void *pOData);
	int PerformOC(void *pOData);
	void DeinitSdoDataArray();
	int CheckArrayConsistency();
	int StartEmulationState();




};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

int OCPerform(unsigned int uiOcObj, EMBL_OUT *);
void  OCEcho(unsigned int uiOcObj);

#ifdef __cplusplus
}
#endif




#endif /* EMBLOUTPUTCOMPARE_H_ */

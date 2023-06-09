/*
 * EMBLECAM.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HanochC
 */

#ifndef EMBLECAM_H_
#define EMBLECAM_H_

#include "EMBLObject.h"
#include <mmc_definitions.h>


#define MAX_SLAVES 99
typedef enum
{
	eCAM_START = 0,
	eCAM_STEP0,
	eCAM_STEP1,
	eCAM_STEP2,
	eCAM_STEP3,
	eCAM_STEP4,
	eCAM_STEP5,
	eCAM_STEP6,
	eCAM_STEP7,
	eCAM_STEP8,
	eCAM_STEP9,
	eCAM_STEP10,
	eCAM_STEP11,
	eCAM_STEP12,
	eCAM_STEP13,
	eCAM_DONE,
	eCAM_ERROR
} eECAM_STATE;


typedef enum
{
	eALL_RELATIVE =0,
	eMASTER_RELATIVE_SLAVE_ABSOLUTE,
	eMASTER_ABSOLUTE_SLAVE_RELATIVE,
	eALL_ABSOLUTE
} ECAM_POS_MODE_ENUM;




#if 1
typedef struct mmc_ecam_in
{

}EMBL_ECAM_IN;

typedef struct mmc_ecam_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_ECAM_OUT;
#endif


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CEmblCam: public EMBLObject {
public:
	CEmblCam() {}
	CEmblCam(unsigned int uiConn);
	virtual ~CEmblCam();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:
	output:            ecamOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_ECAM_OUT* ecamOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             ecamOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_ECAM_OUT* ecamOutParam);

	void  Echo(void);

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
		 * \brief this function performs the complete stages, which are required by Ecam task.
		 * \In param :
		 * \void *pOData -
		 * \return 0 if completed successfully, otherwise error.
		 */
		virtual int Perform(void *);

	/**
	 * \fn PostPerform()
	 * \brife: Execution of methods after the preform ended.
	 * \return none.
	 */
	virtual int PostPerform(void *);


protected:
	int  m_iOpMode;
	unsigned short m_usDimension;
	unsigned short m_usMasterRef;
	unsigned short m_pSlaveRef[MAX_SLAVES];
	bool m_bErrFlag;
	MC_PATH_REF m_hMemHandle;


	MMC_CAMTABLESELECT_IN stCamTableSelectIn;
	MMC_CAMTABLESELECT_OUT stCamTableSelectOut;

	MMC_CAMIN_IN	stCamInParamIn;
	MMC_CAMIN_OUT	stCamInParamOut;

	void* m_pInParam;
	void* m_pOutParam;
};

#endif

/* -------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

int EcamPerform(unsigned int uiEcamObj, EMBL_ECAM_OUT *);
void  EcamEcho(unsigned int uiEcamObj);

#ifdef __cplusplus
}
#endif


#endif /* EMBLECAM_H_ */

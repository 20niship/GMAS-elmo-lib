/*
 * EMBLPPvt.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HanochC
 */

#ifndef EMBLPVT_H_
#define EMBLPVT_H_

#include "EMBLObject.h"
#include <mmc_definitions.h>
//#include "MMC_definitions.h"
//#include "mmcpplib.h"

typedef int (*INIT_FUNC_PTR)(MMC_CONNECT_HNDL,MMC_AXIS_REF_HNDL,void*,void*);

typedef enum
{
	ePVT_START = 0,
	ePVT_STEP0,
	ePVT_STEP1,
	ePVT_STEP2,
	ePVT_STEP3,
	ePVT_STEP4,
	ePVT_STEP5,
	ePVT_STEP6,
	ePVT_STEP7,
	ePVT_STEP8,
	ePVT_STEP9,
	ePVT_STEP10,
	ePVT_STEP11,
	ePVT_STEP12,
	ePVT_STEP13,

	ePVT_DONE,
	ePVT_ERROR
} ePVT_STATE;




#if 1
typedef struct mmc_pvt_in
{

}EMBL_PVT_IN;

typedef struct mmc_pvt_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_PVT_OUT;
#endif


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
class CEmblPvt: public EMBLObject {
public:
	CEmblPvt() {}
	CEmblPvt(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblPvt();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             pvtInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_PVT_IN* pvtInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:
	output:            pvtOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_PVT_OUT* pvtOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             joystickVelPIOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_PVT_OUT* pvtOutParam);

	void  Echo(void);

protected:

	int  m_iOpMode;
	int  m_iDimension;
	unsigned short m_pAxesRef[16];
	bool m_bGrpFlag;

	MC_PATH_REF m_hMemHandle;

	INIT_FUNC_PTR m_pInitFuncPtr;

	MMC_LOADTABLEFROMFILE_IN stLoadTableInParam;
	MMC_LOADTABLE_OUT stLoadTableOutParam;
	MMC_MOVETABLE_IN  stMoveInParam;
    MMC_MOVETABLE_OUT stMoveOutParam;

	void* m_pInParam;
	void* m_pOutParam;
	void* m_pMoveInParam;
	void* m_pMoveOutParam;

	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */
	virtual int Init(void *);

	/**
	 * \fn Perform(void *pOData)
	 * \brief this function performs the complete stages, which are required by pvt task.
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

};

#endif

/* -------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

int PvtPerform(unsigned int uiPvtObj, EMBL_PVT_OUT *);
void  PvtEcho(unsigned int uiPvtObj);

#ifdef __cplusplus
}
#endif


#endif /* EMBLPVT_H_ */

/*
 * CEmblPvtDynamic.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HanochC
 */

#ifndef EMBLPVTDYNAMIC_H_
#define EMBLPVTDYNAMIC_H_

#include "PVT/EMBLPvt.h"

typedef struct embl_pvt_dynamic_in
{
	unsigned short usAxisRef;
	unsigned long ulMaxPoints;
	unsigned long ulUnderFlowThrsh;
	unsigned short usDimesion;
	unsigned char ucPosAbsFlag;
	unsigned char ucCyclicFlag;
	unsigned char ucTimeAbsFlag;
	double* 	 pTableData;
	bool 	bStartcmd;
	bool    bAbortCmd;
	bool    bAppendCmd;
}EMBL_PVT_DYNAMIC_IN;


typedef struct embl_pvt_dynamic_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
	bool bUnderflow;
	bool bOverFlow;
	unsigned int ulPvtIndx;
}EMBL_PVT_DYNAMIC_OUT;



typedef struct
{
	MMC_INITTABLE_IN stInitTableInParam;
	MMC_APPENDPOINTSTOTABLE_IN stAppendTableInParam;
}EMBL_PVT_DYNAMIC_INIT_IN;

typedef struct
{
	MMC_INITTABLE_OUT stInitTableOutParam;
	MMC_APPENDPOINTSTOTABLE_OUT stAppendTableOutParam;
}EMBL_PVT_DYNAMIC_INIT_OUT;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef __cplusplus
class CEmblPvtDynamic: public CEmblPvt
{
public:

	CEmblPvtDynamic(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblPvtDynamic();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             pvtDynamicInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_PVT_DYNAMIC_IN *pvtDynamicInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    pvtDynamicInParam pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_PVT_DYNAMIC_IN *pvtDynamicInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:             pvtDynamicInParam - structure of data relevant for Perform function.
	output:            pvtDynamicOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_PVT_DYNAMIC_IN* pvtDynamicInParam, EMBL_PVT_DYNAMIC_OUT *pvtDynamicOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             pvtDynamicOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_PVT_DYNAMIC_OUT* pvtDynamicOutParam);



	void  Echo(void);



protected:
	EMBL_PVT_DYNAMIC_IN stInMemParam;
	EMBL_PVT_DYNAMIC_OUT stOutMemParam;

	MMC_INITTABLE_IN stInitTableInParam;
	MMC_INITTABLE_OUT stInitTableOutParam;

	MMC_APPENDPOINTSTOTABLE_IN stAppendTableInParam;
	MMC_APPENDPOINTSTOTABLE_OUT stAppendTableOutParam;

	void* pInMemParam;
	void* pOutMemParam;
	EMBL_PVT_DYNAMIC_IN m_stIData;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init()
	 description:	    Initialize values for the class members
	 input:				pData - void pointer to the relevant data that should be
								use the Initialize class members
	 output:			none
	 return:			none
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual int Init(void *);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform()
	 description:	    function performs the complete required stages.
	 input:
	 output:			none
	 return:			none
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int Perform(void *);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform()
	 description:	    Execution of methods after the perform ended.
	 input:
	 output:			none
	 return:			none
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(void *);
};
#endif

/* -------------------------------------------------------------------------
 * Accessory functions are a way to convert that reference we passed
 * to C (the void pointer) back into something usable by C++ .
 ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif

unsigned int  PvtDynamicCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  PvtDynamicRmObj(unsigned int uiPvtObj);
int  PvtDynamicPost(unsigned int uiPvtObj, EMBL_PVT_DYNAMIC_OUT *pData );
int PvtDynamicInit(unsigned int uiPvtObj, EMBL_PVT_DYNAMIC_IN* pData);

#ifdef __cplusplus
}
#endif

#endif /* CEmblPVTDYNAMIC_H_ */



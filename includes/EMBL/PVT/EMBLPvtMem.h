/*
 * EMBLPvtMem.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HanochC
 */

#ifndef EMBLPVTMEM_H_
#define EMBLPVTMEM_H_

#include "PVT/EMBLPvt.h"


typedef struct embl_pvt_mem_in
{
	unsigned short usAxisRef;
	unsigned long ulMaxPoints;
	unsigned short usDimesion;
	MC_COORD_SYSTEM_ENUM eCoordSys;
	unsigned char ucPosAbsFlag;
	unsigned char ucCyclicFlag;
	unsigned char ucTimeAbsFlag;
	unsigned char ucAbortCmd;
	int method;
	double* 	 pTableData;

}EMBL_PVT_MEM_IN;


typedef struct embl_pvt_mem_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_PVT_MEM_OUT;



typedef struct
{
	MMC_INITTABLE_IN stInitTableInParam;
	MMC_APPENDPOINTSTOTABLE_IN stAppendTableInParam;
}EMBL_PVT_INIT_IN;

typedef struct
{
	MMC_INITTABLE_OUT stInitTableOutParam;
	MMC_APPENDPOINTSTOTABLE_OUT stAppendTableOutParam;
}EMBL_PVT_INIT_OUT;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef __cplusplus
class CEmblPvtMem: public CEmblPvt
{
public:

	CEmblPvtMem(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblPvtMem();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             pvtFileInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_PVT_MEM_IN *pvtMemInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
						overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
						usAxisRef - axis reference.
						pvtMemInParam pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_PVT_MEM_IN *pvtMemInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:             pvtMemInParam - structure of data relevant for Perform function.
	output:            pvtMemOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_PVT_MEM_IN* pvtMemInParam, EMBL_PVT_MEM_OUT *pvtMemOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
						Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             pvtMemOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_PVT_MEM_OUT* pvtMemOutParam);


	void  Echo(void);

protected:

	EMBL_PVT_MEM_IN m_stIData;
	MMC_INITTABLE_IN stInitTableInParam;
	MMC_INITTABLE_OUT stInitTableOutParam;

	MMC_APPENDPOINTSTOTABLE_IN stAppendTableInParam;
	MMC_APPENDPOINTSTOTABLE_OUT stAppendTableOutParam;

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
	 name:				Perform
	 description:	    function performs the complete stages, which are required by pvt task.
	 input:
	 output:			*pOData
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(void *);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform()
	 description:	    Execution of methods after the preform ended.
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

unsigned int  PvtMemCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  PvtMemRemoveObj(unsigned int uiPvtObj);
int  PvtMemPost(unsigned int uiPvtObj, void *pData );
int PvtMemInit(unsigned int uiPvtObj, EMBL_PVT_MEM_IN *pDataIn);
int PvtMemPerform(unsigned int uiPvtObj,EMBL_PVT_MEM_IN *pDataIn, EMBL_PVT_MEM_OUT *pDataOut);

#ifdef __cplusplus
}
#endif

#endif /* EMBLPVTMEM_H_ */

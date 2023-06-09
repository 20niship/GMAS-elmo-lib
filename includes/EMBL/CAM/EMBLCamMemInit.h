/*
 * EMBLEcamMem.h
 *
 *  Created on: Mar 11, 2015
 *  Author: HanochC
 */

#ifndef EMBLECAMMEMINIT_H_
#define EMBLECAMMEMINIT_H_

#include "EMBLCam.h"


typedef struct embl_ecam_mem_init_in
{
    unsigned short      usDimension;
	double              dbMasterGap;
	ECAM_POS_MODE_ENUM  ePosMode;
    CURVE_TYPE_ENUM     eCurveType;
    double*             dbECAMdata;
    unsigned int        uiMaxPoint;
} EMBL_ECAM_MEM_INIT_IN;


typedef struct embl_ecam_mem_init_out
{
	MC_PATH_REF   uiHndl[MAX_SLAVES];		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_ECAM_MEM_INIT_OUT;


#if 0
typedef struct
{
	MMC_INITTABLE_IN stInitTableInParam;
	MMC_APPENDPOINTSTOTABLE_IN stAppendTableInParam;
}EMBL_ECAM_INIT_IN;

typedef struct
{
	MMC_INITTABLE_OUT stInitTableOutParam;
	MMC_APPENDPOINTSTOTABLE_OUT stAppendTableOutParam;
}EMBL_ECAM_INIT_OUT;
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef __cplusplus
class CEmblCamMemInit: public CEmblCam
{
public:

	CEmblCamMemInit(unsigned int uiConn);
	virtual ~CEmblCamMemInit();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    ecamMemInitInParam - pointer to the relevant data that should be use the Initialize class members
	 output:			*pOData
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef, EMBL_ECAM_MEM_INIT_IN* ecamMemInitInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get a specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             ecamMemInitInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual int Init(EMBL_ECAM_MEM_INIT_IN *ecamMemInitInParam);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             ecamMemInitInParam - structure of data relevant for Perform function.
	 output:            ecamMemInitOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_ECAM_MEM_INIT_IN* ecamMemInitInParam, EMBL_ECAM_MEM_INIT_OUT* ecamMemInitOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             ecamMemActOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_ECAM_MEM_INIT_OUT* ecamMemInitOutParam);


	void  Echo(void);

protected:

	unsigned int m_uiPointsPerPacket;	//in points
	int m_iPacketSize;
	short m_sPacketCnt;
	unsigned int m_uiTotalPoints; //in points
	unsigned short m_usDelta;
	unsigned short m_ucTableDataColumns ;
	double* m_pTmpTable;

	MMC_CAMTABLEINIT_IN 	stCamTableInitIn;
	MMC_INITTABLE_OUT 		stCamTableInitOut;

	MMC_CAMTABLESELECT_IN  	stCamTableSelectIn;
	MMC_CAMTABLESELECT_OUT 	stCamTableSelectOut;

	MMC_CAMTABLESET_IN 		stCamTableAddIn;
	MMC_CAMTABLESET_OUT 	stCamTableAddOut;

	MMC_CAMIN_IN 			stCamInParamIn;
	MMC_CAMIN_OUT 			stCamInParamOut;

	EMBL_ECAM_MEM_INIT_IN   m_stIData;

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
	 description:	    function performs the complete stages, which are required by Ecam task.
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

unsigned int  EcamMemInitCreateObj(unsigned int uiConn);
void  EcamMemInitRemoveObj(unsigned int uiEcamObj);
int  EcamMemInitPost(unsigned int uiEcamObj, void *pData );
int EcamMemInitInit(unsigned int uiEcamObj,  EMBL_ECAM_MEM_INIT_IN* pDataIn);
int EcamMemInitPerform(unsigned int uiEcamObj,EMBL_ECAM_MEM_INIT_IN *pDataIn, EMBL_ECAM_MEM_INIT_OUT *pDataOut);

#ifdef __cplusplus
}
#endif

#endif /* EMBLECAMMEM_H_ */

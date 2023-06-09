/*
 * EMBLEcamMem.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HanochC
 */

#ifndef EMBLECAMMEMACTIVATE_H_
#define EMBLECAMMEMACTIVATE_H_

#include "EMBLCam.h"
#include "EMBLDefinitions.h"

typedef struct embl_ecam_mem_act_in
{
	unsigned short      usMasterRef;
	unsigned short*     pSlaveRef;
    unsigned char       ucCamActivate;
    unsigned short      usDimension;
    MC_PATH_REF*		pTableHandle;
    ECAM_PERIODIC_ENUM  ePeriodicMode;
    double*             pMasterOffset;
    double*             pSlaveOffset;
    double*		        uiMasterSyncPos;
    CURVE_TYPE_ENUM     eCurveType;
} EMBL_ECAM_MEM_ACT_IN;



typedef struct embl_ecam_mem_act_out
{
	unsigned int   uiHndl;			///< Returned function block handle.
	unsigned short usStatus;		///< Returned command status.
	short sErrorID[MAX_SLAVES]; 	///< Returned command error ID.
	unsigned short usAxisRef;
}EMBL_ECAM_MEM_ACT_OUT;


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
class CEmblCamMemActivate: public CEmblCam
{
public:

	CEmblCamMemActivate(unsigned int uiConn);
	virtual ~CEmblCamMemActivate();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    ecamMemActInParam - pointer to the relevant data that should be use the Initialize class members
	 output:			*pOData
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef, EMBL_ECAM_MEM_ACT_IN* ecamMemActInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get a specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             ecamMemActInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual int Init(EMBL_ECAM_MEM_ACT_IN *ecamMemActInParam);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             ecamMemActInParam - structure of data relevant for Perform function.
	 output:            ecamMemActOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_ECAM_MEM_ACT_IN* ecamMemActInParam, EMBL_ECAM_MEM_ACT_OUT* ecamMemActOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             ecamMemActOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_ECAM_MEM_ACT_OUT* ecamMemActOutParam);


	void  Echo(void);

protected:
	unsigned short m_pTableRef[MAX_SLAVES+1]; //all axes references - master and slaves
	MMC_CAMTABLEINIT_IN 	stCamTableInitIn;
	MMC_INITTABLE_OUT 		stCamTableInitOut;

	MMC_CAMTABLESELECT_IN  	stCamTableSelectIn;
	MMC_CAMTABLESELECT_OUT 	stCamTableSelectOut;

	MMC_CAMTABLESET_IN 		stCamTableAddIn;
	MMC_CAMTABLESET_OUT 	stCamTableAddOut;

	MMC_CAMIN_IN 			stCamInParamIn;
	MMC_CAMIN_OUT 			stCamInParamOut;

	MMC_CAMOUT_IN 			stCamOutParamIn;
	MMC_CAMOUT_OUT 			stCamOutParamOut;

	EMBL_ECAM_MEM_ACT_IN    m_stIData;


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

unsigned int  EcamMemActCreateObj(unsigned int uiConn);
void  EcamMemActRemoveObj(unsigned int uiEcamObj);
int  EcamMemActPost(unsigned int uiEcamObj, void *pData );
int EcamMemActInit(unsigned int uiEcamObj, EMBL_ECAM_MEM_ACT_IN* ecamMemActInParam);
int EcamMemActPerform(unsigned int uiEcamObj,EMBL_ECAM_MEM_ACT_IN *pDataIn, EMBL_ECAM_MEM_ACT_OUT *pDataOut);

#ifdef __cplusplus
}
#endif

#endif /* EMBLECAMMEMACTIVATE_H_ */

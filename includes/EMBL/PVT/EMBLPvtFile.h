/*
 * EMBLPvtFile.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HanochC
 */

#ifndef EMBLPVTFILE_H_
#define EMBLPVTFILE_H_

#include "EMBLPvt.h"



typedef struct mmc_pvt_file_in
{
	char cPvtPath[255];
	unsigned short usAxisRef;
	int dimension;
	MC_COORD_SYSTEM_ENUM eCoordSys;
	unsigned char bAbortCmd;
}EMBL_PVT_FILE_IN;

typedef struct mmc_pvt_file_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_PVT_FILE_OUT;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef __cplusplus
class CEmblPvtFile: public CEmblPvt
{
public:
	CEmblPvtFile(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblPvtFile();


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             pvtFileInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_PVT_FILE_IN *pvtFileInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    pvtFileInParam pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_PVT_FILE_IN *pvtFileInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:             pvtFileInParam - structure of data relevant for Perform function.
	output:            pvtFileOutParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_PVT_FILE_IN* pvtFileInParam, EMBL_PVT_FILE_OUT *pvtFileOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             pvtFileOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_PVT_FILE_OUT* pvtFileOutParam);


	void  Echo(void);
protected:

	EMBL_PVT_FILE_IN m_stIData;

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
	int Perform(void *);

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

unsigned int  PvtFileCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  PvtFileRemoveObj(unsigned int uiPvtObj);
int  PvtFilePost(unsigned int uiPvtObj, void *pData );
int PvtFileInit(unsigned int uiPvtObj, EMBL_PVT_FILE_IN *pDataIn);
int PvtFilePerform(unsigned int uiPvtObj, EMBL_PVT_FILE_IN *pDataIn, EMBL_PVT_FILE_OUT *pDataOut);

#ifdef __cplusplus
}
#endif

#endif /* EMBLPVTFILE_H_ */

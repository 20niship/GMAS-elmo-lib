/*
 * EMBLEcamFile.h
 *
 *  Created on: Mar 11, 2015
 *      Author: HanochC
 */

#ifndef EMBLECAMFILE_H_
#define EMBLECAMFILE_H_

#include "CAM/EMBLCam.h"



typedef struct mmc_ecam_file_in
{
	int iSlaveAxis[MAX_SLAVES];
	int iMaxAxes;
	unsigned short usAxisRef;
	unsigned char bAbortCmd;
	char cEcamPath[255];
}EMBL_ECAM_FILE_IN;

typedef struct mmc_ecam_file_out
{
	unsigned int   uiHndl;		///< Returned function block handle.
	unsigned short usStatus;	///< Returned command status.
	short sErrorID;				///< Returned command error ID.
}EMBL_ECAM_FILE_OUT;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef __cplusplus
class CEmblCamFile: public CEmblCam
{
public:
	CEmblCamFile(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblCamFile();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    ecamFileInParam - pointer to the relevant data that should be use the Initialize class members
	 output:			*pOData
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef, EMBL_ECAM_FILE_IN* ecamFileInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get a specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             EMBL_ECAM_FILE_IN - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	virtual int Init(EMBL_ECAM_FILE_IN *ecamFileInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Perform
	 description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:
	 output:            ecamFileOutParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_ECAM_FILE_OUT* ecamFileOutParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             ecamFileOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_ECAM_FILE_OUT* ecamFileOutParam);


	void  Echo(void);
protected:
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

unsigned int  EcamFileCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  EcamFileRemoveObj(unsigned int uiEcamObj);
int  EcamFilePost(unsigned int uiEcamFileObj, EMBL_ECAM_FILE_OUT* ecamFileOutParam);
int EcamFileInit(unsigned int uiEcamObj, EMBL_ECAM_FILE_IN* ecamFileInParam);
int EcamFilePerform(unsigned int uiEcamObj, EMBL_ECAM_FILE_IN *ecamFileInParam, EMBL_ECAM_FILE_OUT *ecamFileOutParam);

#ifdef __cplusplus
}
#endif

#endif /* EMBLECAMFILE_H_ */

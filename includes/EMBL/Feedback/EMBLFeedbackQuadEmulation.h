/*
 * EMBLFeedbackQuadEmulation.h
 *
 *  Created on: 31/05/2015
 *      Author: ilia
 */

#ifndef EMBLFEEDBACKEMULATIONQUAD_H_
#define EMBLFEEDBACKEMULATIONQUAD_H_

#include "EMBLFeedbackEmulation.h"



#ifdef __cplusplus
class CEmblFeedbackQuadEmulation: public CEmblFeedbackEmulation {
public:
	CEmblFeedbackQuadEmulation(unsigned int uiConn, unsigned short usAxisRef);
	CEmblFeedbackQuadEmulation(){};
	virtual ~CEmblFeedbackQuadEmulation();
	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
	                    overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
	                    usAxisRef - axis reference.
	                    quadEmulationInParam - pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int Init(unsigned int uiConn, unsigned short usAxisRef,EMBL_QUAD_EMULATION_IN * quadEmulationInParam);


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             quadEmulationInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_QUAD_EMULATION_IN * quadEmulationInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	                    Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             quadEmulationOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_OUT * outParam);


	void  Echo(void);

protected:
	/**
	 * \fn Init()
	 * \brife: Initialize values for the class members
	 * \In param:
	 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
	 */
	virtual int Init(void *);

   virtual int PostPerform(void *);


};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

int FbkEmulQuadPerform(unsigned int uiFeObj, EMBL_OUT *outParam);
unsigned int  FbkEmulQuadCreateObj(unsigned int uiConn, unsigned short usAxisRef);
void  FbkEmulQuadRmObj(unsigned int uiFbkEmulQuadObj);
int FbkEmulQuadInit(unsigned int uiFbkEmulQuadObj, EMBL_QUAD_EMULATION_IN* pData);
int  FbkEmulQuadPost(unsigned int uiFbkEmulQuadObj, EMBL_OUT * pData);

#ifdef __cplusplus
}
#endif



#endif /* EMBLFEEDBACKEMULATIONQUAD_H_ */

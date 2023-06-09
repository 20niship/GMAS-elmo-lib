/*
 * EMBLMHomeOnBlock.h
 *
 *  Created on: 28/04/2015
 *      Author: ilia
 */

#ifndef EMBLMHOMEONBLOCK_H_
#define EMBLMHOMEONBLOCK_H_

#include "Home/EmblHomeMultiAxis.h"
/*
 *
 */
#ifdef __cplusplus

class CEMBLMHomeOnBlock: public CEmblHomeMultiAxis {
public:
	CEMBLMHomeOnBlock() {}
	CEMBLMHomeOnBlock(unsigned int uiConn, unsigned short usAxisRef[],unsigned short usCount,EMBL_QUEUEING_RULES_ENUM eQueuedRule);
	virtual ~CEMBLMHomeOnBlock();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    Initialize values for connection handle,axis reference and other class members.
						overloading function to prevent dynamic allocation.
	 input:             unsigned int uiConn - connection handle.
						usAxisRef[] - axis reference.
						usCount
						eQueuedRule
						MultiAxHomeOnBlockInParam -  pointer to the relevant data that should be use the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(unsigned int uiConn, unsigned short usAxisRef[],unsigned short usCount,EMBL_QUEUEING_RULES_ENUM eQueuedRule, EMBL_MULTI_AX_HOME_ON_BLOCK* MultiAxHomeOnBlockInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				Init
	 description:	    get specific data, convert to void* and send to Init(void *pData) function to initialize class members.
	 input:             MultiAxHomeImmdiateInParam - pointer to the relevant data that should be used the Initialize class members
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Init(EMBL_MULTI_AX_HOME_ON_BLOCK* MultiAxHomeOnBlockInParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
						Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             homeOutParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(MMC_HOME_OUT* homeOutParam);



	void  Echo(void);

protected:
/**
 * \fn Init()
 * \brife: Initialize values for the class members
 * \In param:
 * \void *pData - void pointer to the relevant data that should be use the Initialize class members
 */
virtual int Init(void * pData);

/**
 * \fn PostPerform(void *)
 * \brife: Execution of methods after the perform ended.
 * \return none.
 */
virtual int PostPerform(void *pData);
};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

unsigned int  HobCreateObjM(unsigned int uiConn, unsigned short usAxisRef[],unsigned short usCount,EMBL_QUEUEING_RULES_ENUM eQueuedRule);
void  HobRmObjM(unsigned int uiHobObj);
int  HobPostM(unsigned int uiHobObj, void *pData );
int HobInitM(unsigned int uiHobObj, EMBL_MULTI_AX_HOME_ON_BLOCK* pData);

#ifdef __cplusplus
}
#endif
#endif /* EMBLMHOMEONBLOCK_H_ */

/*
 * CEmblHomeMultiAxis.h
 *
 *  Created on: 21/04/2015
 *      Author: ilia
 */

#ifndef CEMBLHOMEMULTIAXIS_H_
#define CEMBLHOMEMULTIAXIS_H_


#include "EMBLHome.h"

#ifdef __cplusplus

typedef CEmblHome* PEmblHome;



class CEmblHomeMultiAxis: public CEmblHome{
public:

	virtual ~CEmblHomeMultiAxis(void);

	PEmblHome* m_pCEmblHome;
	unsigned short m_usCount;
	EMBL_QUEUEING_RULES_ENUM m_eQueuedRule;
	unsigned short m_usQueuedCount;
public:
	CEmblHomeMultiAxis(unsigned int uiConn, unsigned short usAxisRef[],unsigned short usCount, EMBL_QUEUEING_RULES_ENUM eQueuedRule);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	name:			   Perform
	description:       Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	input:
	output:            homeOutMultiAxisParam
	return:		       0 if completed successfully, otherwise error
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int Perform(EMBL_HOME_OUT_MULTI_AXIS *homeOutMultiAxisParam);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
						Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:             homeOutMultiAxisParam - structure of data relevant for PostPerform function.
	 output:
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	virtual int PostPerform(EMBL_HOME_OUT_MULTI_AXIS *homeOutMultiAxisParam);


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
		 * \brief this function performs the complete stages, which are required by home task.
		 * \In param :
		 * \void *pOData - pointer to output param MMC_HOME_OUT(status , error id , fb handle)
		 * \return 0 if completed successfully, otherwise error.
		 */
		virtual int Perform(void *);

		/**
		 * \fn PostPerform()
		 * \brife: Execution of methods after the preform ended.
		 * \return none.
		 */
		virtual int PostPerform(void *);


	CEmblHomeMultiAxis(void) {}
	int PerformParallelStopOnFirtsError(void *pOData);
	int PerformParallelNonStopOnFirtsError(void *pOData);
	int PerformQueued(void *pOData);
int m_iStopOnFirstError;

};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

int HomePerformMultiAxis(unsigned int uiHomObj, EMBL_HOME_OUT_MULTI_AXIS *pData);
void  EchoMultiAxis(unsigned int uiHomObj);

#ifdef __cplusplus
}
#endif

#endif /* CEMBLHOMEMULTIAXIS_H_ */

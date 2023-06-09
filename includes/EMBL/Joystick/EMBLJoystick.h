/*
 * CEmblJoystick.h
 *
 *  Created on: Jan 29, 2015
 *      Author: ZivB
 */

#ifndef EMBLJoystick_H_
#define EMBLJoystick_H_

#include <mmc_definitions.h>
#include "EMBLDefinitions.h"
#include "EMBLObject.h"

#if 0
typedef enum{eJENBABLE_AXIS, eJVALIDATE_STANDSTILL,
	eJREAD_PI_AND_EXECUTE_MOTION, eJFINAL_STATE} eJOYSTICK_STATE;
#endif


typedef union
{
	short sValue;
	unsigned short usValue;
	int iValue;
	unsigned int uiValue;
	long long llValue;
	unsigned long long ullValue;
	float fValue;
	double dValue;
}UNVAL;

typedef int( *READ_PI_FUNC_PTR)(MMC_CONNECT_HNDL,MMC_AXIS_REF_HNDL,void*,void*,UNVAL *VAL);
#if 0
typedef int( *MOVE_FUNC_PTR)(MMC_CONNECT_HNDL,MMC_AXIS_REF_HNDL,void*,void*);
#endif


#ifdef __cplusplus
class CEmblJoystick: public EMBLObject {
public:
	CEmblJoystick() {}//Default Constructor
	CEmblJoystick(unsigned int uiConn, unsigned short usAxisRef);
	virtual ~CEmblJoystick();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 name:				PostPerform
	 description:       Execution of methods after the perform ended.
	 	 	 	 	 	Overloaded function to let the user call by specific value and prevent him send by casting to (void*)
	 input:
	 output:            outParam
	 return:			0 if completed successfully, otherwise error
	 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int PostPerform(EMBL_OUT* outParam);

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
		 * \brief this function performs the complete stages, which are required by PVT task.
		 * \In param :
		 * \void *pOData - pointer to output param MMC_JOYSTICK_OUT(status , error id , fb handle)
		 * \return 0 if completed successfully, otherwise error.
		 */
		virtual int Perform(void *);

		/**
		 * \fn PostPerform()
		 * \brife: Execution of methods after the perform ended.
		 * \return none.
		 */
		virtual int PostPerform(void *);


	unsigned int 		m_uiIndex;
	double 				m_dAutoOffset;
	float 				m_fDeadZone;
	float 				m_fOffset;
	float 				m_fGain;
	READ_PI_FUNC_PTR 	m_pReadPIFunc;	//pointer to pi function
	void* 				m_inParam; 		//pointer to IN param for read PI
	void*				m_outParam; 		// pointer to Out param read PI
	int m_iOpMode;

    union
	{
    	MMC_READPIVARSHORT_IN stInShortParam;
    	MMC_READPIVARUSHORT_IN stInUsShortParam;
    	MMC_READPIVARINT_IN stInIntParam;
    	MMC_READPIVARUINT_IN stInUIntParam;
    	MMC_READPIVARLONGLONG_IN stInLongParam;
    	MMC_READPIVARULONGLONG_IN stInULongParam;
    	MMC_READPIVARFLOAT_IN stInFloatParam;
    	MMC_READPIVARDOUBLE_IN stInDoubleParam;
    	//MMC_READGROUPOFPARAMETERS_IN stINreadGruopOfParam;
	}m_unInParam;

    union
	{
		MMC_READPIVARSHORT_OUT stOutShortParam;
		MMC_READPIVARUSHORT_OUT stOutUsShortParam;
		MMC_READPIVARINT_OUT stOutIntParam;
		MMC_READPIVARUINT_OUT stOutUIntParam;
		MMC_READPIVARLONGLONG_OUT stOutLongParam;
		MMC_READPIVARULONGLONG_OUT stOutULongParam;
		MMC_READPIVARFLOAT_OUT stOutFloatParam;
		MMC_READPIVARDOUBLE_OUT stOutDoubleParam;
    	//MMC_READGROUPOFPARAMETERS_OUT stOutreadGruopOfParam;
	}m_unOutParam;


	UNVAL m_unReadPIValue;
#if 0
	MOVE_FUNC_PTR 	m_pMoveFunc;	//pointer to motion function
#endif
	void*			m_motionInParam;
	void*			m_motionOutParam;
	unsigned int *  m_puiHandler;
	short *m_psErrorId;
	short *m_psPiErrorId;
	bool m_bAbort;
	float m_fPrevData;

	MMC_MOVEVELOCITY_IN		m_stMoveVelInParams;
	MMC_MOVEVELOCITY_OUT    m_stMoveVelOutParams;

};
#endif
/*-------------------------------------------------------------------------
 * accessor functions are a way to convert that reference we passed
 *  to C (the void pointer) back into something usable by C++ .
 */
#ifdef __cplusplus
extern "C" {
#endif

#if 0
int JoystickPerform(unsigned int uiJoyObj, EMBL_JOYSTICK_OUT *);
void  JoystickEcho(unsigned int uiJoyObj);
#endif

int ReadPISHORT(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut, UNVAL *val);
int ReadPIUSSHORT(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut,UNVAL *val);
int ReadPIINIT(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut, UNVAL *val);
int ReadPIUINIT(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut,UNVAL *val);
int ReadPILINT(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut, UNVAL *val);
int ReadPIULINT(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut,UNVAL *val);
int ReadPIFLOAT(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut, UNVAL *val);
int ReadPIDOUBLE(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut, UNVAL *val);
#if 0
int MoveABS(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut);
int MoveVEL(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut);
int READGROUPOFPARAM(MMC_CONNECT_HNDL hConn ,MMC_AXIS_REF_HNDL aRef,void* stParamIn , void* stParamOut , UNVAL *val);
#endif

#ifdef __cplusplus
}
#endif

#endif /* EMBLJoystick_H_ */

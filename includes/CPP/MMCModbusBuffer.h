/*
 * CMMCModbusBuffer.h
 *
 *  Created on: 26/04/2011
 *      Author: yuvall
 */

#ifndef CMMCMODBUSBUFFER_H_
#define CMMCMODBUSBUFFER_H_
#include "mmc_definitions.h"
#include "MMCPPGlobal.h"

class DLLMMCPP_API CMMCModbusBuffer {
public:
	CMMCModbusBuffer();
	CMMCModbusBuffer(int iOffset, int iCount=0);
	virtual ~CMMCModbusBuffer();

	inline void SetOffset(int iOffset) {m_inBuffer.startRef=iOffset;}
	inline void SetRefCount(int iCount) {m_inBuffer.refCnt = iCount;}

	void SetValue (int iIndex, float fValue);
	void SetValue (int iIndex, long lValue);
	void SetValue (int iIndex, short sValue);

	void GetValue (int iIndex, float& fValue);
	void GetValue (int iIndex, long& lValue);
	void GetValue (int iIndex, short& sValue);
	void TypeToModbusShortArr(int iIndex,  float fVal);
	void TypeToModbusShortArr(int iIndex,  long lVal);
	void TypeToModbusShortArr(int iIndex,  short sVal);
	inline MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& GetBuffer() {return m_inBuffer;}

  protected:
	MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN m_inBuffer;
};

#endif /* CMMCMODBUSBUFFER_H_ */

/*
 * CMMCHostComm.h
 *
 *  Created on: 24/03/2011
 *      Author: yuvall
 */

#ifndef CHOSTCOMM_H_
#define CHOSTCOMM_H_

#include "MMCPPGlobal.h"
#include "MMCModbusSwapBuffer.h"


class DLLMMCPP_API CMMCHostComm {
public:
	CMMCHostComm() {m_uiConnHndl= 0 ;}
	~CMMCHostComm() {}

	inline void MbusSetConnection(unsigned int uiConnHndl) {m_uiConnHndl = uiConnHndl;}
	void MbusStartServer(unsigned int uiConnHndl, unsigned short usID) throw (CMMCException);
	void MbusStopServer() throw (CMMCException);
	void MbusReadHoldingRegisterTable(int startRef, int refCnt, MMC_MODBUSREADHOLDINGREGISTERSTABLE_OUT& stOutParams) throw (CMMCException);
	void MbusWriteHoldingRegisterTable(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams) throw (CMMCException);
	bool MbusIsRunning(unsigned int uiConnHndl = 0) throw (CMMCException);
	void MbusReadCoilsTable(int startRef, int refCnt, MMC_MODBUSREADCOILS_OUT& stOutParams) throw (CMMCException);
	void MbusWriteCoilsTable(MMC_MODBUSWRITECOILS_IN& stInParams) throw (CMMCException);
	void MbusReadInputsTable(int startRef, int refCnt, MMC_MODBUSREADINPUTS_OUT& stOutParams) throw (CMMCException);

	void SetModbusLong(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, int iOffset, long lValue) throw (CMMCException);
	void SetModbus(int iOffset, long lValue) throw (CMMCException);
	void SetModbus(int iOffset, float fValue) throw (CMMCException);
	void SetModbus(int iOffset, short sValue) throw (CMMCException);

	void SetModbusLongSwapped(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, int iOffset, long lPos) throw (CMMCException);
	void SetModbusShort(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, int iOffset, short sPos) throw (CMMCException);
	void SetModbusFloat(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, int iOffset, float fPos) throw (CMMCException);
	void SetModbusFloatSwapped(MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& stInParams, int iOffset, float fPos) throw (CMMCException);
	void SetModbus(int iOffset, int iRefCount, CMMCModbusBuffer& stInParams) throw (CMMCException);
	void SetModbus(int iOffset, int iRefCount, CMMCModbusSwapBuffer& stInParams) throw (CMMCException);

	void GetModbus(int iOffset, int iRefCount, CMMCModbusBuffer& stOutParams) throw (CMMCException);
	void GetModbus(int iOffset, int iRefCount, CMMCModbusSwapBuffer& stOutParams) throw (CMMCException);


protected:
	//
    void LongToModbusShortArr(short* spArr, long lVal)
	{
	      *spArr      = (short) (lVal   & 0xFFFF);
	      *(spArr + 1)= (short)((lVal >> 16) & 0xFFFF);
	}
	void SwapLongToModbusShortArr(short* spArr, long lVal)
	{
	      *spArr      = (short)((lVal >> 16) & 0xFFFF);
	      *(spArr + 1)= (short) (lVal & 0xFFFF);
	}

	void FloatToModbusShortArr(short* spArr, float fVal)
	{
		union {
			float fVal;
			long lVal;
		} lfloat;
		lfloat.fVal = fVal;

		*spArr      = (short) (lfloat.lVal & 0xFFFF);
		*(spArr + 1)= (short)((lfloat.lVal >> 16) & 0xFFFF);
	}
	void SwapFloatToModbusShortArr(short* spArr, float fVal)
	{
		union {
			float fVal;
			long lVal;
		} lfloat;
		lfloat.fVal = fVal;
		*spArr      = (short)((lfloat.lVal >> 16) & 0xFFFF);
		*(spArr + 1)= (short) (lfloat.lVal & 0xFFFF);
	}

private:
    unsigned int m_uiConnHndl;
};

#endif /* CHOSTCOMM_H_ */

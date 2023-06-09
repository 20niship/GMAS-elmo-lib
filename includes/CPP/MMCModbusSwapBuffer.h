#ifndef IMMC_MODBUS_SWAPLONG_BUFF_H_
#define IMMC_MODBUS_SWAPLONG_BUFF_H_

#include "MMCModbusBuffer.h"

class DLLMMCPP_API CMMCModbusSwapBuffer
{
public:
	CMMCModbusSwapBuffer();
	CMMCModbusSwapBuffer(int iOffset, int iCount=0);
	virtual ~CMMCModbusSwapBuffer() {};

	inline void SetOffset(int iOffset) {m_inBuffer.startRef = iOffset;}
	inline void SetRefCount(int iCount) {m_inBuffer.refCnt=iCount;}

	void SetValue (int iIndex, long lValue);
	void SetValue (int iIndex, float fValue);
	void GetValue (int iIndex, long& lValue);
	void GetValue (int iIndex, float& fValue);
	template <typename T>
	void TypeToModbusShortArr(int iIndex, T tValue)
	{
		union {
			T tVal;
			unsigned long ulVal;
		} ltype;
		ltype.tVal = tValue;
		m_inBuffer.regArr[iIndex+1]  =  (short) (ltype.ulVal & 0xFFFF);
		m_inBuffer.regArr[iIndex]= (short)((ltype.ulVal >> 16) & 0xFFFF);
	}

	inline MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN& GetBuffer() {return m_inBuffer;}

  private:

	MMC_MODBUSWRITEHOLDINGREGISTERSTABLE_IN m_inBuffer;
};


#endif //IMMC_MODBUS_SWAPLONG_BUFF_H_

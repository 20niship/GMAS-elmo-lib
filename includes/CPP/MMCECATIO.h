/*
 * CMMCECATIO.h
 *
 *  Created on: 27/06/2011
 *      Author: yuvall
 */

#ifndef CMMCECATIO_H_
#define CMMCECATIO_H_
#include "MMCGroupAxis.h"
#include "MMCNode.h"



/*
 *
 */
class DLLMMCPP_API CMMCECATIO : public CMMCNode {
public:
	CMMCECATIO();
	virtual ~CMMCECATIO();

	void ECATIOEnableDIChangedEvent() throw (CMMCException);
	void ECATIODisableDIChangedEvent() throw (CMMCException);
	MMCPPULL_T ECATIOReadDigitalInput() throw (CMMCException);
	void ECATIOWriteDigitalOutput(MMCPPULL_T  ulliDO) throw (CMMCException);
	short ECATIOReadAnalogInput(unsigned char ucIndex) throw (CMMCException);
	void ECATIOWriteAnalogOutput(unsigned char ucIndex, short sAOValue) throw (CMMCException);

};

#endif /* CMMCECATIO_H_ */

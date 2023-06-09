////////////////////////////////////////////////////////////////////////////////
/// \file MMC_ECATIO_API.h
/// Name        : MMC_ECATIO_API.h
/// Author      : Benjamin Spitzer
/// Created on	: June, 2011
/// Version     : 0.0.1
/// Copyright   : Your copyright notice
/// Description : This file contain definitions for ...
////////////////////////////////////////////////////////////////////////////////

#ifndef MMC_ECATIO_API_H
#define MMC_ECATIO_API_H
//
//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
 extern "C" {
#endif
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#endif

typedef struct mmc_readai_in
{
	unsigned char ucIndex;
}MMC_READAI_IN;

typedef struct mmc_readai_out
{
	short sAI;
	unsigned short usStatus;
	short usErrorID;
}MMC_READAI_OUT;

typedef struct mmc_writeao_in
{
	short sAO;
	unsigned char ucIndex;
}MMC_WRITEAO_IN;

typedef struct mmc_writeao_out
{
	unsigned short usStatus;
	short usErrorID;
}MMC_WRITEAO_OUT;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ECATIOEnableDIChangedEvent(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
///				OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ECATIOEnableDIChangedEvent(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_ENABLEDICHANGEDEVENT_IN* pInParam,
		OUT MMC_ENABLEDICHANGEDEVENT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_ECATIODisableDIChangedEvent(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_CONFIGREGULARPARAMEVENTPDO3_IN* pInParam,
///				OUT MMC_CONFIGREGULARPARAMEVENTPDO3_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ECATIODisableDIChangedEvent(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_DISABLEDICHANGEDEVENT_IN* pInParam,
		OUT MMC_DISABLEDICHANGEDEVENT_OUT* pOutParam);

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOReadDigitalInput(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_READDI_IN* pInParam,
///				OUT MMC_READDI_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ECATIOReadDigitalInput(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_READDI_IN* pInParam,
		OUT MMC_READDI_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOWriteDigitalOutput(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_WRITEDO_IN* pInParam,
///				OUT MMC_WRITEDO_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ECATIOWriteDigitalOutput(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_WRITEDO_IN*		pInParam,
		OUT MMC_WRITEDO_OUT*	pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOReadAnalogInput(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_WRITEDO_IN* pInParam,
///				OUT MMC_WRITEDO_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ECATIOReadAnalogInput(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_READAI_IN* pInParam,
		OUT MMC_READAI_OUT* pOutParam) ;

////////////////////////////////////////////////////////////////////////////////
/// \fn int MMC_MMC_ECATIOWriteAnalogOutput(
///				IN MMC_CONNECT_HNDL hConn,
///				IN MMC_AXIS_REF_HNDL hAxisRef,
///				IN MMC_WRITEAO_IN* pInParam,
///				OUT MMC_WRITEAO_OUT* pOutParam)
////////////////////////////////////////////////////////////////////////////////
MMC_LIB_API int MMC_ECATIOWriteAnalogOutput(
		IN MMC_CONNECT_HNDL hConn,
		IN MMC_AXIS_REF_HNDL hAxisRef,
		IN MMC_WRITEAO_IN* pInParam,
		OUT MMC_WRITEAO_OUT* pOutParam) ;

//moving to g++ @YL 4-10-2010
#ifdef __cplusplus
}
#endif

#endif /* MMC_ECATIO_API_H */

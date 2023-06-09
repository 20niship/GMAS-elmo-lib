// MMCSingleAxis.h: interface for the CMMCSingleAxis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMCSINGLEAXIS_H__3E1F67CF_C8B1_40B8_BB29_090EF2A76691__INCLUDED_)
#define AFX_MMCSINGLEAXIS_H__3E1F67CF_C8B1_40B8_BB29_090EF2A76691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined ( WIN32 )
#pragma warning( disable : 4290 )
#endif

#include "mmc_definitions.h"
#include "MMCAxis.h"
#include "MMCNode.h"
#include "MMCMotionAxis.h"
#include "MMCPPGlobal.h"



class DLLMMCPP_API MMC_MOTIONPARAMS_SINGLE
{
public:
	MMC_MOTIONPARAMS_SINGLE();
	//
	double	dbPosition ;
	double	dbDistance ;
	float	fEndVelocity ;
	float	fVelocity ;
	float	fAcceleration ;
 	float	fDeceleration ;
	float	fJerk ;
	MC_DIRECTION_ENUM		eDirection ;
	MC_BUFFERED_MODE_ENUM	eBufferMode ;
	unsigned int 			uiExecDelayMs;
	unsigned char			ucExecute ;
	//
};

class DLLMMCPP_API CMMCSingleAxis : public CMMCMotionAxis
{
public:
	virtual ~CMMCSingleAxis();

	CMMCSingleAxis();
	CMMCSingleAxis(const MMC_MOTIONPARAMS_SINGLE& stParams)
	{
		SetDefaultParams(stParams);
	}

	/*! \fn CMMCSingleAxis(CMMCSingleAxis& mmcAxis)
	*	\brief copy constructor.
	*	\param mmcAxis source reference for which data is copied.
	*/
    CMMCSingleAxis(CMMCSingleAxis& mmcAxis);

	double				m_dbTorqueVelocity;
	double				m_dbTorqueAcceleration;
	float				m_fVelocity ;
	float				m_fAcceleration ;
	float				m_fDeceleration ;
	float				m_fJerk ;
	unsigned char		m_ucExecute ;
	MC_DIRECTION_ENUM	m_eDirection ;
	unsigned int		m_uiExecDelayMs;
	//homing
	double 					m_dbHomePosition;
	float					m_fHomeAcceleration;
	float 					m_fHomeVelocity;
	float					m_fHomeDistanceLimit;
	float 					m_fHomeTorqueLimit;
	MMC_HOME_MODE_ENUM		m_eHomingMode;
	MC_BUFFERED_MODE_ENUM	m_eHomeBufferMode;
	MC_HOME_DIRECTION_ENUM 	m_eHomeDirection;
	MC_SWITCH_MODE_ENUM		m_eHomeSwitchMode;
	unsigned int			m_uiHomeTimeLimit;
	unsigned int			m_uiHomingMethod;
	unsigned char			m_ucHomeExecute;	

	double m_dbDetectionVelocityLimit;    //HomingDS402Ex
	unsigned int m_uiDetectionTimeLimit;  //HomingDS402Ex
	float m_fHomeVelocityLo;              //HomingDS402Ex: Speed during search for zero

	void SetDefaultHomeDS402Params(const MMC_HOMEDS402_IN& stSingleParams);
	void SetDefaultHomeDS402ExParams(const MMC_HOMEDS402EX_IN& stSingleParams);

	/*! \fn int SetDefaultParams MMC_MOTIONPARAMS_SINGLE& stSingleAxisParams)
	*	\brief This function initiates default parameters for motion for specific axis.
	*	\param stSingleAxisParams structure of motion parameters for single axis.
	*	\return	return - 0 if success. error_id in case of error.
	*/
	void SetDefaultParams(const MMC_MOTIONPARAMS_SINGLE& stSingleAxisParams);

	int MoveVelocity(float fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

	/*! \fn int MoveAbsolute(double dPos,.....) 
	*	\brief This function send Move Absolute command to MMC server for specific Axis.
	*	\param dPos target position to move.
	*	\param motion parameters
	*	\return	return - 0 if success. error_id in case of error
	*/
	int MoveAbsolute(double dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAbsolute(double dPos, float fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAbsolute(double dPos, float fVel, float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAbsolute(double dPos, float fVel, float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);



	/*! \fn int MoveAdditive(double dbDistance,.....) 
	*	\brief This function send Move Additive command to MMC server for specific Axis.
	*	\param dbDistance target position to move.
	*	\param motion parameters
	*	\return	return - 0 if success. error_id in case of error
	*/
	int MoveAdditive(double dbDistance, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAdditive(double dbDistance, float fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAdditive(double dbDistance, float fVel, float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAdditive(double dbDistance, float fVel, float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

	/*! \fn int MoveRelative(double dbDistance,.....) 
	*	\brief This function send Move Relitive command to MMC server for specific Axis.
	*	\param dbDistance target position to move.
	*	\param motion parameters
	*	\return	return - 0 if success. error_id in case of error
	*/
	int MoveRelative(double dbDistance, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveRelative(double dbDistance, float fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveRelative(double dbDistance, float fVel, float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveRelative(double dbDistance, float fVel, float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

	/*! \fn int MoveAbsoluteRepetitive(double dPos,.....) 
	*	\brief This function send Move Absolute repetitive command to MMC server for specific Axis.
	*	\param dPos target position to move.
	*	\param motion parameters
	*	\return	return - 0 if success. error_id in case of error
	*/
	int MoveAbsoluteRepetitive(double dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAbsoluteRepetitive(double dPos, float fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAbsoluteRepetitive(double dPos, float fVel, float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAbsoluteRepetitive(double dPos, float fVel, float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAbsoluteRepetitive(double dPos, float fVel, unsigned int uiExecDelayMs, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);


	/*! \fn int MoveRelativeRepetitive(double dPos,.....) 
	*	\brief This function send Move Relitive repetitive command to MMC server for specific Axis.
	*	\param dPos target position to move.
	*	\param motion parameters
	*	\return	return - 0 if success. error_id in case of error
	*/
	int MoveRelativeRepetitive(double dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveRelativeRepetitive(double dPos, float fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveRelativeRepetitive(double dPos, float fVel, float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveRelativeRepetitive(double dPos, float fVel, float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveRelativeRepetitive(double dPos, float fVel, unsigned int uiExecDelayMs, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);


	/*! \fn int MoveAdditiveRepetitive(double dPos,.....) 
	*	\brief This function send Move Additive repetitive command to MMC server for specific Axis.
	*	\param dPos target position to move.
	*	\param motion parameters
	*	\return	return - 0 if success. error_id in case of error
	*/
	int MoveAdditiveRepetitive(double dPos, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAdditiveRepetitive(double dPos, float fVel, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAdditiveRepetitive(double dPos, float fVel, float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAdditiveRepetitive(double dPos, float fVel, float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	int MoveAdditiveRepetitive(double dPos, float fVel, unsigned int uiExecDelayMs, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

	/*! \fn int MoveTorque(double dbTargetTorque,.....) 
	*	\brief This function send Move Torque command to MMC server for specific Axis.
	*	\param dbTargetTorque target torque to move.
	*	\param motion parameters
	*	\return	return - 0 if success. error_id in case of error
	*/
	void MoveTorque(double dbTargetTorque, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	void MoveTorque(double dbTargetTorque, double dbTorqeVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);
	void MoveTorque(double dbTargetTorque, double dbTorqeVelocity, double dbTorqueAcceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);


	int PositionProfile(MC_PATH_REF hMemHandle, MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE) throw (CMMCException);

	int TouchProbeDisable() throw (CMMCException);
	int TouchProbeEnable(unsigned char ucTriggerType) throw (CMMCException);


	/*! \fn int SetOpMode()
	*	\brief This function changes motion mode between NC/Non NC.
	*	\param eMode operational mode.
	*	\return	return - 0 on success, otherwise throws CMMCException.
	*/
	int SetOpMode(OPM402 eMode) throw (CMMCException);

	/*! \fn int SetOpMode(OPM402 eMode, MC_EXECUTION_MODE eExecutionMode)
	*	\brief This function changes motion mode between NC/Non NC.
	*	\param eMode operational mode.
	*	\return	return - 0 on success, otherwise throws CMMCException.
	*/
	void SetOpMode(OPM402 eMode, MC_EXECUTION_MODE eExecutionMode, double dbInitModeValue = 0) throw (CMMCException);


	/*! \fn OPM402 GetOpMode()
	* \brief This function gets motion mode between NC/Non NC.
	* \return	return - 0 on success, otherwise throws CMMCException.
	*/
	OPM402 GetOpMode() throw (CMMCException);

	/*! \fn unsigned int GetStatusRegister()
	* \brief This function returns the status register
	* \return	return - 0 on success, otherwise throws CMMCException.
	*/
	unsigned int GetStatusRegister() throw (CMMCException);
	unsigned int GetStatusRegister(MMC_GETSTATUSREGISTER_OUT& sOutput) throw (CMMCException);

	/*! \fn void AxisLink(unsigned short usAxisRef, unsigned char ucMode = 0)
	* \brief This function link between two axes
	* \return	return - when erro throws CMMCException.
	*/
	void AxisLink(unsigned short usAxisRef, unsigned char ucMode = 0) throw (CMMCException);

	/*! \fn void AxisUnLink()
	* \brief This function unlink the axis
	* \return	return - when erro throws CMMCException.
	*/
	void AxisUnLink() throw (CMMCException);

	/*! \fn void PowerOn()
	* \brief This function sends Power On command to MMC server.
	* \return	return - none. throws CMMCException on error.
	*/
	void PowerOn(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn void PowerOff()
	* \brief This function sends Power Off command to MMC server.
	* \return	return - none. throws CMMCException on error.
	*/
	void PowerOff(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	double GetActualPosition() throw (CMMCException);
	double GetActualVelocity() throw (CMMCException);
	double GetActualTorque() throw (CMMCException);
	void Halt(float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	void Halt(float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	void Halt(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	void Stop(float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	void Stop(float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	void Stop(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);	
	unsigned char GetDigInput(int iInputNumber) throw (CMMCException);
	unsigned long GetDigInputs() throw (CMMCException);
	
	unsigned long GetDigOutputs32bit(int iOutputNumber, unsigned char ucEnable) throw (CMMCException);
	unsigned long GetDigOutputs32bit(int iOutputNumber = 0) throw (CMMCException);	
	unsigned char GetDigOutputs(int iOutputNumber = 0) throw (CMMCException);

	void SetDigOutputs32Bit(const int iOutputNumber, const unsigned long ulValue) throw (CMMCException);
	void SetDigOutputs32Bit( const unsigned long ulValue) throw (CMMCException);
	void SetDigOutputs(const int iOutputNumber, const unsigned char ucValue, unsigned char ucEnable) throw (CMMCException);
	void SetDigOutputs(const int iOutputNumber, const unsigned char ucValue) throw (CMMCException);	
	void SetDigOutputs(const unsigned char ucValue) throw (CMMCException);	
	

	void HomeDS402() throw (CMMCException);
	void HomeDS402(MMC_HOMEDS402_IN stHomeDS402Params) throw (CMMCException);
	void HomeDS402Ex() throw (CMMCException);
	void HomeDS402Ex(MMC_HOMEDS402EX_IN stParams) throw (CMMCException);


	//
	//
	/*! \fn int SetOverride(float fAccFactor, float fJerkFactor, float fVelFactor, unsigned char ucEnable = 1)
	* \brief This function  send Set Override command to MMC server for specific Axis.
	* \return	return - none. throws CMMCException on error.
	*/
	void SetOverride(float fAccFactor, float fJerkFactor, float fVelFactor, unsigned short usUpdateVelFactorIdx = 0) throw (CMMCException);
	void SetDefaultHomeParams(const MMC_HOME_IN& stSingleParams);
	unsigned short Home(short* usErrorID, unsigned int* uiHndl) throw (CMMCException);
	unsigned short Home(MMC_HOME_IN stHomeParams, short* usErrorID, unsigned int* uiHndl) throw (CMMCException);

	void ConfigPDO(PDO_NUMBER_ENUM ePDONum, PDO_PARAM_TYPE_ENUM eParamType,
			unsigned int uiPDOCommParamEvent,
			unsigned short usEventTimer,
			unsigned char ucEventGroup,
			unsigned char ucPDOCommParam,
			unsigned char ucSubIndex,
			unsigned char ucPDOType) throw (CMMCException);
	void CancelPDO(PDO_NUMBER_ENUM ePDONum) throw (CMMCException);
	void ChangeDefaultPDOConfig(unsigned char ucPDONum,	unsigned char ucPDODir,	unsigned char ucPDOCommParam) throw (CMMCException);
	void ElmoSetAsyncParam(char cCmd[3], int& iVal) throw (CMMCException);
	inline void USleep(unsigned long usecs) {
#ifndef _WIN32
		usleep(usecs);
#else

		  LARGE_INTEGER pcfreq;
		  LARGE_INTEGER before, after;

		  if (!QueryPerformanceFrequency (&pcfreq))
		    printf ("QueryPerformanceFrequency failed\n");

		  if (!QueryPerformanceCounter (&before))
		    printf ("QueryPerformanceCounter failed\n");

		  struct timespec t;
		  t.tv_sec = usecs / 1000000;
		  t.tv_nsec = (usecs % 1000000) * 1000;
		  nanosleep (&t);

		  if (!QueryPerformanceCounter (&after))
		    printf ("QueryPerformanceCounter failed\n");

		  printf ("time slept: %g s\n", (double) (after.QuadPart - before.QuadPart) / (double) pcfreq.QuadPart);
#endif
	}
	void ElmoSetAsyncParam(char cCmd[3], float& fVal) throw (CMMCException);

	void ElmoGetAsyncIntParam(char cCmd[3]) throw (CMMCException);
	void ElmoGetAsyncFloatParam(char cCmd[3]) throw (CMMCException);
	void ElmoGetAsyncIntArray(char cCmd[3], short iArrayIdx) throw (CMMCException);
	void ElmoGetAsyncFloatArray(char cCmd[3], short iArrayIdx) throw (CMMCException);

	void ElmoSetAsyncArray(char cCmd[3], short iArrayIdx, float& fVal) throw (CMMCException);
	void ElmoSetAsyncArray(char cCmd[3], short iArrayIdx, int& iVal) throw (CMMCException);
	void ElmoGetSyncParam(char cCmd[3], float& fVal) throw (CMMCException);
	void ElmoGetSyncParam(char cCmd[3], int& iVal) throw (CMMCException);
	void ElmoGetSyncArray(char cCmd[3], short iArrayIdx, float& fVal) throw (CMMCException);
	void ElmoGetSyncArray(char cCmd[3], short iArrayIdx, int& iVal) throw (CMMCException);
	void ElmoCallAsync(char cCmd[3]) throw (CMMCException);
	void ElmoExecute(unsigned char* pData, unsigned char ucLength) throw (CMMCException);
	int ElmoIsReplyAwaiting() throw (CMMCException);
	void ElmoGetReply(float& fVal) throw (CMMCException);
	void ElmoGetReply(int& iVal) throw (CMMCException);

	void ConfigVirtualEncoder(double dbLowPos, double dbHighPos, float fFactor, unsigned char ucMode, unsigned char ucGroupID) throw (CMMCException);
	void CancelVirtualEncoder() throw (CMMCException); 
	void SetPosition(double dbPosition, unsigned char ucPosMode) throw (CMMCException);



	MC_PATH_REF InitPVTTable(unsigned long ulMaxPoints,
						unsigned long ulUnderflowThreshold,
						unsigned char ucIsCyclic,
						unsigned char ucIsPosAbsolute,
			unsigned short usDimension,
			NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_ARRAY)
	throw (CMMCException)
	{
		return InitPVTTable(ulMaxPoints,ulUnderflowThreshold,ucIsCyclic,ucIsPosAbsolute,usDimension,MC_ACS_COORD, eTableMode);
	}
	MC_PATH_REF LoadPVTTableFromFile(char* pFileName,
			NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_FILE) throw (CMMCException)
			{
				return LoadPVTTableFromFile(pFileName, MC_ACS_COORD, eTableMode);
			}
	void MovePVT(MC_PATH_REF hMemHandle) throw (CMMCException){return MovePVT(hMemHandle,MC_ACS_COORD);};


    void SendCmdViaSdoDownload(long   lData, const char* pcCmdIdx, unsigned char ucSubIndex=1) throw (CMMCException);
    void SendCmdViaSdoDownload(float  fData, const char* pcCmdIdx, unsigned char ucSubIndex=1) throw (CMMCException);
    void SendCmdViaSdoUpload  (long&  lData, const char* pcCmdIdx, unsigned char ucSubIndex=1) throw (CMMCException);
    void SendCmdViaSdoUpload  (float& fData, const char* pcCmdIdx, unsigned char ucSubIndex=1) throw (CMMCException);

	private:

	MC_PATH_REF InitPVTTable(unsigned long ulMaxPoints,
						   unsigned long ulUnderflowThreshold,
						   unsigned char ucIsCyclic,
						   unsigned char ucIsPosAbsolute,
						   unsigned short usDimension,
						   MC_COORD_SYSTEM_ENUM eCoordSystem,
						   NC_MOTION_TABLE_TYPE_ENUM eTableMode  = eNC_TABLE_PVT_ARRAY) throw (CMMCException)
						   {
								return CMMCMotionAxis::InitPVTTable(ulMaxPoints,ulUnderflowThreshold,ucIsCyclic,ucIsPosAbsolute,usDimension,eCoordSystem, eTableMode);
						   }
		MC_PATH_REF LoadPVTTableFromFile(char* pFileName,
				MC_COORD_SYSTEM_ENUM eCoordSystem,
				NC_MOTION_TABLE_TYPE_ENUM eTableMode = eNC_TABLE_PVT_FILE) throw (CMMCException)
				{
					return CMMCMotionAxis::LoadPVTTableFromFile(pFileName,eCoordSystem, eTableMode);
				}
		void MovePVT(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException){return CMMCMotionAxis::MovePVT(hMemHandle,eCoordSystem);};
        unsigned short  CalcSdoIdx(const char* pcCmdIdx);

};

#endif // !defined(AFX_MMCSINGLEAXIS_H__3E1F67CF_C8B1_40B8_BB29_090EF2A76691__INCLUDED_)

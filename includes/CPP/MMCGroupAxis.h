/*
 * CMMCGroupAxis.h
 *
 *  Created on: 10/03/2011
 *      Author: yuvall
 */

#ifndef MMCGROUPAXIS_H_
#define MMCGROUPAXIS_H_

#include "mmc_definitions.h"
#include "MMCAxis.h"
#include "MMCMotionAxis.h"

class DLLMMCPP_API MMC_MOTIONPARAMS_GROUP
{
public:
	MMC_MOTIONPARAMS_GROUP();
	//
	double dAuxPoint[NC_MAX_NUM_AXES_IN_NODE];
	double dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	float fVelocity;
	float fAcceleration;
	float fDeceleration;
	float fJerk;
	float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM eCoordSystem;
	NC_TRANSITION_MODE_ENUM eTransitionMode;
	MC_BUFFERED_MODE_ENUM eBufferMode;
	NC_ARC_SHORT_LONG_ENUM eArcShortLong;
	NC_PATH_CHOICE_ENUM ePathChoice;
	NC_CIRC_MODE_ENUM eCircleMode;
	unsigned int m_uiExecDelayMs;
	unsigned char ucSuperimposed;
	unsigned char ucExecute;
	//
};

class DLLMMCPP_API CMMCGroupAxis: public CMMCMotionAxis {
public:
	CMMCGroupAxis();
	virtual ~CMMCGroupAxis();
	CMMCGroupAxis(CMMCGroupAxis& axis);

	/*! \fn void InitAxisData(const char* cName, MMC_CONNECT_HNDL uHandle)
	*	\brief This function initiates axis name and retrieves a session handler.
	*/
	void InitAxisData(const char* cName, MMC_CONNECT_HNDL uHandle) throw (CMMCException);

	/*! \fn int GetGroupAxisByName(const char* cName)
	 * \brief This function return axis index reference by his name.
	 * \param  cName name of the axis.
	 * \return	return - 0 on success, otherwise throws CMMCException.
	 */
	int GetGroupAxisByName(const char* cName) throw (CMMCException);

	double m_dAuxPoint[NC_MAX_NUM_AXES_IN_NODE];
	double m_dEndPoint[NC_MAX_NUM_AXES_IN_NODE];
	float m_fVelocity;
	float m_fAcceleration;
	float m_fDeceleration;
	float m_fJerk;
	float m_fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE];
	MC_COORD_SYSTEM_ENUM m_eCoordSystem;
	NC_TRANSITION_MODE_ENUM m_eTransitionMode;
	NC_ARC_SHORT_LONG_ENUM m_eArcShortLong;
	NC_PATH_CHOICE_ENUM m_ePathChoice;
	NC_CIRC_MODE_ENUM m_eCircleMode;
	unsigned char m_ucSuperimposed;
	unsigned char m_ucExecute;
	unsigned int m_uiExecDelayMs;


public:

	/*! \fn void SetDefaultParams(const MMC_MOTIONPARAMS_GROUP& stGroupAxisParams)
	*	\brief sets axis's default parameters. overwrite class default parameters.
	*	\param stGroupAxisParams reference of structure with default parameters.
	*	\return none. or throws CMMCException on failure.
	*/
	void SetDefaultParams(const MMC_MOTIONPARAMS_GROUP& stGroupAxisParams) throw (CMMCException);

	/*! \fn void SetKinTransform(MMC_SETKINTRANSFORM_IN& stInParam)
	*	\brief sets parameters for group's kinematic transformation (MSC to ACS).
	*	\param stInParam reference of structure with kinematic parameters.
	*	\return none. or throws CMMCException on failure.
	*/
	void SetKinTransform(MMC_SETKINTRANSFORM_IN& stInParam) throw (CMMCException);

	/**! \fn void SetCartesianTransform(MMC_SETCARTESIANTRANSFORM_IN& stInParam)
	*	\brief sets MCS to PCS parameters for group's kinematic transformation.
	*	\param stInParam reference of structure with kinematic parameters.
	*	\return none. or throws CMMCException on failure.
	*/
	int SetCartesianTransform(MMC_SETCARTESIANTRANSFORM_IN* stInParam) throw (CMMCException);

	/**! \fn void SetCartesianTransform(double (&dbOffset)[3], double (&dbRotAngle)[3], 
	*				PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits=PCS_DEGREE,
	*				MC_BUFFERED_MODE_ENUM eBufferMode=MC_BUFFERED_MODE, 
	*				MC_EXECUTION_MODE eExecutionMode=eMMC_EXECUTION_MODE_IMMEDIATE)
	*	\brief sets MCS to PCS parameters for group's kinematic transformation.
	*	\param dbOffset		group of three positions in cartesian system.
	*	\param dbRotAngle	group of three angles around the vector axes (see dbOffsets).
	*	\param eRotAngleUnits degrees (0) or radians (1).
	*	\param eBufferMode one of the buffered modes in the list.
	*	\param eExecutionMode	immediate (0) or queued (1) (currently immediate only).
	*	\return none. or throws CMMCException on failure.
	*/
	int SetCartesianTransform(double (&dbOffset)[3], double (&dbRotAngle)[3], 
		PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits=PCS_DEGREE,
		MC_BUFFERED_MODE_ENUM eBufferMode=MC_BUFFERED_MODE, 
		MC_EXECUTION_MODE eExecutionMode=eMMC_EXECUTION_MODE_IMMEDIATE) throw (CMMCException);

	/*! \fn ReadCartesianTransform()
	 * \brief read parameters, which was previouslly set by SetCartesianTransform (see above) .
	 * \param  .
	 * \return - 0 if completed successfully, otherwise  error or throws CMMCException
	 */
	int ReadCartesianTransform() throw (CMMCException);

	/**
	* \fn
	* \brief	this function block offers an abstraction layer for a conveyor, 
	*			assisting the user with tracking objects moving on a straight line in space.
	*			in short, a dynamic MCS to PCS transition depends on conveyor axis position.
	* \param pInParam	reference of input paramters data structure.
	* \return - 0 if completed successfully, otherwise error or throws CMMCException
	*/
	int TrackConveyorBelt(MMC_TRACKCONVEYORBELT_IN* pInParam) throw (CMMCException);
	/**
	* \fn	int TrackConveyorBelt(unsigned short usRefAxis, ...)
	* \brief	this function block offers an abstraction layer for a conveyor, 
	*			assisting the user with tracking objects moving on a straight line in space.
	*			in short, a dynamic MCS to PCS transition depends on conveyor axis position.
	* \param usRefAxis				conveyor belt axis reference.
	* \param dbConveyorBeltOrigin	positions of conveyor belt relative to MCS.
	* \param dbInitialObjectPosition positions of an object lying on conveyor belt, relative to the conveyor belt.
	* \param dInitialRefAxisPosition 
	* \param dRefAxisScaling 
	* \param eSourceType			position source type from conveyor belt axis.
	* \param eRotAngleUnits			angle units, degrees (0) or radians (1)
	* \param eBufferMode			buffered mode.
	* \param eCoordSystem			for future use (currently PCS only)  
	* \param eExecutionMode			execution mode: immediate (0) or queued (1)  
	* \return - 0 if completed successfully, otherwise error or throws CMMCException
	*/
	int TrackConveyorBelt(unsigned short usRefAxis,	
						double (&dbConveyorBeltOrigin)[6], 
						double (&dbInitialObjectPosition)[6],
						double dInitialRefAxisPosition, 
						double dRefAxisScaling = 1.0,
						PCS_REF_AXIS_SRC_ENUM eSourceType = NC_PCS_TARGET_POS,
						PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits = PCS_RADIAN,
						MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE,
						MC_COORD_SYSTEM_ENUM eCoordSystem = MC_PCS_COORD,
						MC_EXECUTION_MODE eExecutionMode = eMMC_EXECUTION_MODE_QUEUED) throw (CMMCException) ;
	/**
	* \fn	int TrackRotaryTable(MMC_TRACKROTARYTABLE_IN* pInParam)
	* \brief	this function block offers an abstraction layer for a rotary table, 
	*			assisting the user with tracking objects moving on a cyrcle space.
	*			in short, a dynamic MCS to PCS transition depends on rotary table axis position.
	* \param pInParam	reference of input paramters data structure.
	* \return - 0 if completed successfully, otherwise error or throws CMMCException
	*/
	int TrackRotaryTable(MMC_TRACKROTARYTABLE_IN* pInParam) throw (CMMCException);
	/**
	* \fn	int TrackRotaryTable(unsigned short usRefAxis,	...)
	* \brief	this function block offers an abstraction layer for a rotary table, 
	*			assisting the user with tracking objects moving on a cyrcle space.
	*			in short, a dynamic MCS to PCS transition depends on rotary table axis position.
	* \param usRefAxis				rotary table axis reference.
	* \param dbRotaryTableOrigin	positions of conveyor belt relative to MCS.
	* \param dbInitialObjectPosition positions of an object lying on conveyor belt, relative to the conveyor belt.
	* \param dInitialRefAxisPosition 
	* \param dRefAxisScaling 
	* \param eRotAngleUnits			angle units, degrees (0) or radians (1)
	* \param eSourceType			position source type from rotary table axis.
	* \param eBufferMode			buffered mode.
	* \param eCoordSystem			for future use (currently PCS only)  
	* \param eExecutionMode			execution mode: immediate (0) or queued (1)  
	* \return - 0 if completed successfully, otherwise error or throws CMMCException
	*/
	int TrackRotaryTable(unsigned short usRefAxis,	
						double (&dbRotaryTableOrigin)[6], 
						double (&dbInitialObjectPosition)[6],
						double dInitialRefAxisPosition, 
						double dRefAxisScaling = 1.0,
						PCS_REF_AXIS_SRC_ENUM eSourceType = NC_PCS_TARGET_POS,
						PCS_ROTATION_ANGLE_UNITS_ENUM eRotAngleUnits = PCS_RADIAN,
						MC_BUFFERED_MODE_ENUM eBufferMode = MC_BUFFERED_MODE,
						MC_COORD_SYSTEM_ENUM eCoordSystem = MC_PCS_COORD,
						MC_EXECUTION_MODE eExecutionMode = eMMC_EXECUTION_MODE_QUEUED) throw (CMMCException) ;

	/*! \fn RemoveAxisFromGroup(NC_IDENT_IN_GROUP_ENUM eIdentInGroup)
	 * \brief removes axis from axis group.
	 * \param  eIdentInGroup - group identifier.
	 * \return - none on success, otherwise throws CMMCException
	 */
	void RemoveAxisFromGroup(NC_IDENT_IN_GROUP_ENUM eIdentInGroup) throw (CMMCException);

	/*! \fn MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM, NC_PATH_CHOICE_ENUM, NC_CIRC_MODE_ENUM, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Circular Absolute command to MMC server for specific Group.
	 * \param  eArcShortLong - defines the kind of supported arc length.
	 * \param  ePathChoice - defines the kinds of supported path choice.
	 * \param  eCircleMode - defines the kinds of supported circular modes.
	 * \param  eBufferMode - defines options for supported buffered mode(default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, NC_CIRC_MODE_ENUM eCircleMode, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM, NC_PATH_CHOICE_ENUM, NC_CIRC_MODE_ENUM, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Circular Absolute command to MMC server for specific Group.
	 * \param  eArcShortLong - defines the kind of supported arc length.
	 * \param  ePathChoice - defines the kinds of supported path choice.
	 * \param  eCircleMode - defines the kinds of supported circular modes.
	 * \param  dAuxPoint - list of start points.
	 * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, NC_CIRC_MODE_ENUM eCircleMode, double dAuxPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM, NC_PATH_CHOICE_ENUM, NC_CIRC_MODE_ENUM, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Circular Absolute command to MMC server for specific Group.
	 * \param  eArcShortLong - defines the kind of supported arc length.
	 * \param  ePathChoice - defines the kinds of supported path choice.
	 * \param  eCircleMode - defines the kinds of supported circular modes.
	 * \param  dAuxPoint - list of start points.
	 * \param  dEndPoint - list of end points.
	 * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsolute(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, NC_CIRC_MODE_ENUM eCircleMode, double dAuxPoint[NC_MAX_NUM_AXES_IN_NODE], double dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Circular Center command to MMC server for specific Group.
	 * \param  eArcShortLong - defines the kind of supported arc length.
	 * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Circular Center command to MMC server for specific Group.
	 * \param  eArcShortLong - defines the kind of supported arc length.
	 * \param  dCenterPoint - list of start points.
	 * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, double dBorderPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Circular Center command to MMC server for specific Group.
	 * \param  eArcShortLong - defines the kind of supported arc length.
	 * \param  dCenterPoint - list of start points.
	 * \param  dEndPoint - list of end points.
	 * \param  eBufferMode - defines options for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteCenter(NC_ARC_SHORT_LONG_ENUM eArcShortLong, double dCenterPoint[NC_MAX_NUM_AXES_IN_NODE], double dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], double dEndPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Absolute Border command to MMC server for specific Group.
	 * \param  dBorderPoint - list of start points.
	 * \param  dEndPoint - list of end points.
	 * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteBorder(double dBorderPoint[NC_MAX_NUM_AXES_IN_NODE], double dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Absolute Border command to MMC server for specific Group.
	 * \param  dBorderPoint - list of start points.
	 * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteBorder(double dBorderPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Absolute Border command to MMC server for specific Group.
	 * \param  dBorderPoint - list of start points.
	 * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteRadius(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	/*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Absolute Border command to MMC server for specific Group.
	 * \param  dBorderPoint - list of start points.
	 * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteRadius(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, double dSpearHeadPoint[NC_MAX_NUM_AXES_IN_NODE], double dEndPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	/*! \fn MoveCircularAbsoluteBorder(double dBorderPoint[], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE)
	 * \brief sends Move Absolute Border command to MMC server for specific Group.
	 * \param  dBorderPoint - list of start points.
	 * \param  eBufferMode - defines option for supported buffered mode (default MC_ABORTING_MODE).
	 * \return - 0 on success, otherwise throws CMMCException
	 */
	int MoveCircularAbsoluteRadius(NC_ARC_SHORT_LONG_ENUM eArcShortLong, NC_PATH_CHOICE_ENUM ePathChoice, double dSpearHeadPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	int MoveCircularAbsoluteAngle(double dAngle,	MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveCircularAbsoluteAngle(double dAngle, double dCenterPoint[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	
	int MoveLinearAbsolute(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsolute(float fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsolute(float fVelocity, double dbPosition[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsolute(float fVelocity, double dbPosition[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsolute(float fVelocity, double dbPosition[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	
	
	int MoveLinearRelative(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelative(float fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelative(float fVelocity, double dbDistance[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelative(float fVelocity, double dbDistance[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelative(float fVelocity, double dbDistance[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	
	
	int MoveLinearAdditive(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAdditive(float fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAdditive(float fVelocity, double dbDistance[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAdditive(float fVelocity, double dbDistance[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAdditive(float fVelocity, double dbDistance[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	

	int MoveLinearAbsoluteRepetitive(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsoluteRepetitive(float fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsoluteRepetitive(float fVelocity, double dbPosition[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsoluteRepetitive(float fVelocity, double dbPosition[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearAbsoluteRepetitive(float fVelocity, double dbPosition[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);


	int MoveLinearRelativeRepetitive(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelativeRepetitive(float fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelativeRepetitive(float fVelocity, double dDistance[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelativeRepetitive(float fVelocity, double dDistance[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MoveLinearRelativeRepetitive(float fVelocity, double dDistance[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);

	int MovePolynomAbsolute(MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MovePolynomAbsolute(float fVelocity, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MovePolynomAbsolute(float fVelocity,double dbAuxPoint[NC_MAX_NUM_AXES_IN_NODE], double dbPosition[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MovePolynomAbsolute(float fVelocity,double dbAuxPoint[NC_MAX_NUM_AXES_IN_NODE], double dbPosition[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);	
	int MovePolynomAbsolute(float fVelocity,double dbAuxPoint[NC_MAX_NUM_AXES_IN_NODE], double dbPosition[NC_MAX_NUM_AXES_IN_NODE], float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	int MovePolynomAbsolute(float fVelocity, float fAcceleration, float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	

	int GroupSetOverride(float fVelFactor,	float fAccFactor, float fJerkFactor, unsigned short usUpdateVelFactorIdx) throw (CMMCException);
	int GroupSetPosition(double dbPosition[], MC_COORD_SYSTEM_ENUM eCoordSystem, unsigned char ucMode, MC_BUFFERED_MODE_ENUM eBufferMode = MC_ABORTING_MODE) throw (CMMCException);
	unsigned long GroupReadStatus(unsigned short& usGroupErrorID) throw (CMMCException);
	unsigned long GroupReadStatus() throw (CMMCException);
	void GroupEnable() throw (CMMCException);
	void GroupDisable() throw (CMMCException);
	void GroupReset() throw (CMMCException);
    double GroupReadActualVelocity(MC_COORD_SYSTEM_ENUM eCoordSystem, double dVelocity[NC_MAX_NUM_AXES_IN_NODE]) throw (CMMCException);
	double GroupReadActualVelocity(MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);
	unsigned short GroupReadError() throw (CMMCException);
	void AddAxisToGroup(NC_NODE_HNDL_T hNode, NC_IDENT_IN_GROUP_ENUM eIdentInGroup) throw (CMMCException);
    int GroupReadActualPosition(MC_COORD_SYSTEM_ENUM eCoordSystem, double dbPosition[NC_MAX_NUM_AXES_IN_NODE]) throw (CMMCException);
	void GroupStop(float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode) throw (CMMCException);
	void GroupHalt(float fDeceleration, float fJerk, MC_BUFFERED_MODE_ENUM eBufferMode) throw (CMMCException);

	void MovePath(MC_PATH_REF hMemHandle, MC_COORD_SYSTEM_ENUM eCoordSystem) throw (CMMCException);
	void MovePath(MC_PATH_REF hMemHandle, float fTransitionParameter[NC_MAX_NUM_AXES_IN_NODE], MC_BUFFERED_MODE_ENUM eBufferModeeBufferMode = MC_BUFFERED_MODE,  MC_COORD_SYSTEM_ENUM eCoordSystem = MC_MCS_COORD) throw (CMMCException);
	void PathDeselect(MC_PATH_REF hMemHandle) throw (CMMCException);
	unsigned int PathSelect(MC_PATH_DATA_REF pPathToSplineFile) throw (CMMCException);
	unsigned int PathSelect(MC_PATH_DATA_REF pPathToSplineFile, MC_COORD_SYSTEM_ENUM eCoordSystem, unsigned char ucExecute = 1) throw (CMMCException);
	/**
	* \fn	unsigned int PathGetLengths(MC_PATH_REF hMemHandle,....) 
	* \brief	retrieves length values of specifies segments.
				buffer must comply to number of values, which programer expects to get 
				and	cannot be greater than 170 elements.
	* \param	hMemHandle - table handler of offline spline table.
	* \param	uiStartIndex - specifies the table segment from witch to start the length values collection.
	* \param	uiNumOfSegments specifies the number of segments for the length values collection.
	* \param	dbValues - the buffer in which this API stores the collected values.
	* \return	number of returned values if completed successfuly, otherwise throws an error or error (< 0)
	*/
	unsigned int PathGetLengths(MC_PATH_REF hMemHandle,
					unsigned int uiStartIndex,
					unsigned int uiNumOfSegments,
					double *dbValues) throw (CMMCException);

	void SetBoolParameter(long lValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	void SetParameter(double dbValue, MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	long GetBoolParameter(MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);
	double GetParameter(MMC_PARAMETER_LIST_ENUM eNumber, int iIndex) throw (CMMCException);

	void GetMembersInfo(MMC_GETGROUPMEMBERSINFO_OUT* stOutput) throw (CMMCException);
#ifndef WIN32
	void SetCartesianKinematics(MC_KIN_REF_CARTESIAN stCart) throw (CMMCException) __attribute__ ((deprecated));
	void SetDeltaRobotKinematics(MC_KIN_REF_DELTA stDelta) throw (CMMCException) __attribute__ ((deprecated));
	void SetKinematic(MC_KIN_REF stInput,NC_KIN_TYPE eKinType) throw (CMMCException) __attribute__ ((deprecated));

#else
	__declspec(deprecated) void SetCartesianKinematics(MC_KIN_REF_CARTESIAN stCart) throw (CMMCException);
	__declspec(deprecated) void SetDeltaRobotKinematics(MC_KIN_REF_DELTA stDelta) throw (CMMCException);
	__declspec(deprecated) void SetKinematic(MC_KIN_REF stInput,NC_KIN_TYPE eKinType) throw (CMMCException);
#endif

	/*! \fn unsigned int GetStatusRegister()
	* \brief This function returns the status register
	* \return	return - 0 on success, otherwise throws CMMCException.
	*/
	unsigned int GetStatusRegister() throw (CMMCException);
	unsigned int GetStatusRegister(MMC_GETSTATUSREGISTER_OUT& sOutput) throw (CMMCException);

	/*! \fn unsigned int GetMcsLimitRegister()
	* \brief This function returns the MCS limit register
	* \return	return - 0 on success, otherwise throws CMMCException.
	*/
	unsigned int GetMcsLimitRegister() throw (CMMCException);


	void Reset()throw (CMMCException){GroupReset();}
	unsigned long ReadStatus()throw (CMMCException){return GroupReadStatus();}
	unsigned long ReadStatus(unsigned short& usAxisErrorID, unsigned short& usStatusWord)throw (CMMCException){return GroupReadStatus(usAxisErrorID);}

	/*
	 * wrappers for kinematics's transformation API
	 */
	/*! \fn void SetKinTransformDelta(MMC_KINTRANSFORM_DELTA_IN& stInParam)
	*	\brief sets parameters kinematic transformation (MSC to ACS) for DELTA robot.
	*	\param stInParam reference of structure with kinematic parameters.
	*	\return 0 if completed successfully, otherwise error or throws CMMCException.
	*/
	int SetKinTransformDelta(IN MMC_KINTRANSFORM_DELTA_IN& pInParam) throw (CMMCException);
	
	/*! \fn void SetKinTransformCartesian(MMC_KINTRANSFORM_CARTESIAN_IN& stInParam)
	*	\brief sets parameters kinematic transformation (MSC to ACS) for Cartesian system.
	*	\param stInParam reference of structure with kinematic parameters.
	*	\return 0 if completed successfully, otherwise error or throws CMMCException.
	*/
	int SetKinTransformCartesian(IN MMC_KINTRANSFORM_CARTESIAN_IN& pInParam) throw (CMMCException);
	
	/*! \fn void SetKinTransformScara(MMC_KINTRANSFORM_SCARA_IN& stInParam)
	*	\brief sets parameters kinematic transformation (MSC to ACS) for SCARA robot.
	*	\param stInParam reference of structure with kinematic parameters.
	*	\return 0 if completed successfully, otherwise error or throws CMMCException.
	*/
	int SetKinTransformScara(IN MMC_KINTRANSFORM_SCARA_IN& pInParam) throw (CMMCException);
	
	/*! \fn void SetKinTransformThreeLink(MMC_KINTRANSFORM_THREELINK_IN& stInParam)
	*	\brief sets parameters kinematic transformation (MSC to ACS) for THREELINK robot.
	*	\param stInParam reference of structure with kinematic parameters.
	*	\return 0 if completed successfully, otherwise error or throws CMMCException.
	*/
	int SetKinTransformThreeLink(IN MMC_KINTRANSFORM_THREELINK_IN& pInParam) throw (CMMCException);

private:
	void CopyMoveCircularAbsParams(MMC_MOVECIRCULARABSOLUTE_IN& stInParams);
	void CopyMoveCircularAbsCenterParams(MMC_MOVECIRCULARABSOLUTECENTER_IN& stInParams);
	void CopyMoveCircularAbsBorderParams(MMC_MOVECIRCULARABSOLUTEBORDER_IN& stInParams);
	void CopyMoveCircularAbsAngleParams(MMC_MOVECIRCULARABSOLUTEANGLE_IN& stInParams);
	void CopyMoveCircularAbsRadiusParams(MMC_MOVECIRCULARABSOLUTERADIUS_IN& stInParams);
	void CopyMoveLinearAbsParams(MMC_MOVELINEARABSOLUTE_IN& stInParams);
	void CopyMoveLinearRltParams(MMC_MOVELINEARRELATIVE_IN& stInParams);
	void CopyMoveLinearAbsRepParams(MMC_MOVELINEARABSOLUTEREPETITIVE_IN& stInParams);
	void CopyMoveLinearRltRepParams(MMC_MOVELINEARRELATIVEREPETITIVE_IN& stInParams);
	void CopyMoveLinearAddParams(MMC_MOVELINEARADDITIVE_IN& stInParams);
	void CopyMovePolynomAbsParams(MMC_MOVEPOLYNOMABSOLUTE_IN& stInParams);

	void SendSdoCmd(long lData,
			unsigned char ucService,
			unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID)throw (CMMCException){return;}
	void SendSdoDownload(long lData,
			unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID)throw (CMMCException){return;}
	long SendSdoUpload(unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID)throw (CMMCException){return 0;}
	void SendSdoUploadAsync(unsigned char ucSubIndex,
			unsigned long ulDataLength,
			unsigned short usIndex,
			unsigned short usSlaveID)throw (CMMCException){return;}
	void RetreiveSdoUploadAsync(long& lData)throw (CMMCException){return;}
	MMCPPULL_T PDOGeneralRead(unsigned char ucParam)throw (CMMCException){return 0;}
	void PDOGeneralWrite(unsigned char ucParam,MMCPPULL_T ulliVal)throw (CMMCException){return;}
	void PDOGeneralWrite(unsigned char ucParam,unGeneralPDOWriteData DataUnion)throw (CMMCException){return;}
	void GetPDOInfo(unsigned char uiPDONumber,int &iPDOEventMode, unsigned char &ucPDOCommType, unsigned char &ucTPDOCommEventGroup, unsigned char &ucRPDOCommEventGroup)throw (CMMCException){return;}
	unsigned short GetAxisError(unsigned short* usLastEmergencyErrCode)throw (CMMCException){return 0;};
	void ConfigPDOEventMode(unsigned char ucPDOEventMode, PDO_NUMBER_ENUM ePDONum = PDO_NUM_3) throw (CMMCException){return;}


	void EthercatWriteMemoryRange(unsigned short usRegAddr, unsigned char ucLength, unsigned char pData[ETHERCAT_MEMORY_WRITE_MAX_SIZE]) throw (CMMCException){return;}

	void EthercatWritePIVar(unsigned short usIndex, unsigned char ucByteLength,	unsigned char pRawData[PI_REG_VAR_SIZE]) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex,	unsigned short usByteLength, unsigned char pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, bool bData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex,	signed char cData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, unsigned char ucData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, unsigned short usData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, short sData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, unsigned int uiData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, int iData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, float fData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, double dbData) throw (CMMCException){return;}

#ifdef WIN32
	void EthercatWritePIVar(unsigned short usIndex, unsigned __int64 ullData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, __int64 llData) throw (CMMCException){return;}
#else
	void EthercatWritePIVar(unsigned short usIndex, unsigned long long ullData) throw (CMMCException){return;}
	void EthercatWritePIVar(unsigned short usIndex, long long llData) throw (CMMCException){return;}
#endif


	void EthercatReadMemoryRange(unsigned short usRegAddr,	unsigned char ucLength, unsigned char pData[ETHERCAT_MEMORY_READ_MAX_SIZE]) throw (CMMCException){return;}

	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned char ucByteLength, unsigned char pRawData[PI_REG_VAR_SIZE]) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned short usByteLength, unsigned char pRawData[PI_LARGE_VAR_SIZE]) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, bool &bData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, signed char &cData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned char &ucData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned short &usData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, short &sData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned int &uiData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, int &iData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, float &fData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, double &dbData) throw (CMMCException){return;}
	
#ifdef WIN32
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned __int64 &ullData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, __int64 &llData) throw (CMMCException){return;}
#else
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, unsigned long long &ullData) throw (CMMCException){return;}
	void EthercatReadPIVar(unsigned short usIndex, unsigned char ucDirection, long long &llData) throw (CMMCException){return;}
#endif
	
	void EthercatPIVarInfo(unsigned short usPIVarIndex, unsigned char ucDirection, NC_PI_ENTRY &VarInfo) throw (CMMCException){return;}

};

#endif /* MMCGROUPAXIS_H_ */

/*
 * EMBLIncludes.h
 *
 *  Created on: Jun 30, 2015
 *      Author: Orits
 */
#ifndef EMBLINCLUDES_H_
#define EMBLINCLUDES_H_

#include "EMBLDefinitions.h"
#include "EMBLObject.h"
#include "EMBLSendCommandBySDO.h"
//CAM
#include "CAM/EMBLCam.h"
#include "CAM/EMBLCamFile.h"
#include "CAM/EMBLCamMemActivate.h"
#include "CAM/EMBLCamMemInit.h"
//Home
#include "Home/EMBLHome.h"
#include "Home/EMBLHomeImmediate.h"
#include "Home/EmblHomeMultiAxis.h"
#include "Home/EMBLHomeOnBlock.h"
#include "Home/EMBLHomeOnHomeSwitch.h"
#include "Home/EMBLHomeOnIndex.h"
#include "Home/EMBLHomeOnLimitSwitch.h"
//Home multi
#include "Home/EMBLMHomeImmediate.h"
#include "Home/EMBLMHomeOnBlock.h"
#include "Home/EmblMHomeOnHomeSwitch.h"
#include "Home/EmblMHomeOnIndex.h"
#include "Home/EmblMHomeOnLimitSwitch.h"

//Joystick
#include "Joystick/EMBLJoystick.h"
#include "Joystick/EMBLJoystickPos.h"
#include "Joystick/EMBLJoystickPosAdv.h"
#include "Joystick/EMBLJoystickPosExtParam.h"
#include "Joystick/EMBLJoystickPosPI.h"
#include "Joystick/EMBLJoystickVel.h"
#include "Joystick/EMBLJoystickVelAdv.h"
#include "Joystick/EMBLJoystickVelExtParam.h"
#include "Joystick/EMBLJoystickVelPI.h"

//OC
#include "OC/EMBLOutputCompare.h"
#include "OC/EmblOCAbsPosActivate.h"
#include "OC/EmblOCAbsPosInit.h"
#include "OC/EmblOCPosTabActivate.h"
#include "OC/EmblOCPosTabInit.h"
#include "OC/EmblOCTimeTabActivate.h"
#include "OC/EmblOCTimeTabInit.h"

// PVT
#include "PVT/EMBLPvt.h"
#include "PVT/EMBLPvtDynamic.h"
#include "PVT/EMBLPvtMem.h"
#include "PVT/EMBLPvtFile.h"

// FeedBack
#include "Feedback/EMBLFeedbackEmulation.h"
#include "Feedback/EMBLFeedbackQuadEmulation.h"

#endif /* EMBLINCLUDES_H_*/

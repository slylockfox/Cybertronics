/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>
#include <algorithm>  // for min and max

#include <frc/smartdashboard/SmartDashboard.h>

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

void Robot::RobotInit() {
  m_limetable = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
    m_timer.Reset();
    m_timer.Start();
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
    // Drive for 2 seconds
    if (m_timer.Get() < 2.0) {
      // Drive forwards half speed
      m_robotDrive.ArcadeDrive(-0.5, 0.0);
    } else {
      // Stop robot
      m_robotDrive.ArcadeDrive(0.0, 0.0);
    }
  } else {
    // Default Auto goes here
  }
}

#define MOTOR_SCALE 1.7
#define TARGET_TOLERANCE_V 4
using namespace std;
void Robot::TeleopPeriodic() {

  double targetSeen = m_limetable->GetNumber("tv",0.0);
  if (targetSeen != 0.0) {  // tv is true if there is a target detected
    double targetOffsetAngle_Horizontal = m_limetable->GetNumber("tx",0.0);
    double targetOffsetAngle_Vertical = m_limetable->GetNumber("ty",0.0);
    double targetArea = m_limetable->GetNumber("ta",0.0);
    double targetSkew = m_limetable->GetNumber("ts",0.0);
    if (targetOffsetAngle_Vertical > TARGET_TOLERANCE_V) {
      m_limeServoAngle -= 1;
    } else if (targetOffsetAngle_Vertical < -TARGET_TOLERANCE_V) {
      m_limeServoAngle += 1;
    }
    m_limeServoAngle = std::min(m_limeServoAngle, 180.0);
    m_limeServoAngle = std::max(m_limeServoAngle, 0.0);
    //m_limeServoAngle = 90.0 - targetOffsetAngle_Vertical;
    m_limeServo.SetAngle(m_limeServoAngle);
  } else {
    m_limeServo.SetAngle(90);
  }

  // Drive with arcade style (use right stick)    
  m_robotDrive.ArcadeDrive(m_stick.GetY()/MOTOR_SCALE, m_stick.GetX()/MOTOR_SCALE); // MJS: not so fast
}

void Robot::TestPeriodic() {}
void Robot::TeleopInit() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

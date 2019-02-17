/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
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
      m_robotDrive.DriveCartesian(0, 0.5, 0, 0);
    } else {
      // Stop robot
      m_robotDrive.DriveCartesian(0, 0, 0, 0);
    }
  } else {
    // Default Auto goes here
  }
}

#define MOTOR_SCALE 1.7
void Robot::TeleopPeriodic() {
  // On Logitech controller, right stick is direction and speed, right stick is rotate    
  m_robotDrive.DriveCartesian(-m_stick.GetRawAxis(2), m_stick.GetRawAxis(3), -m_stick.GetRawAxis(0), 0);
//  int count = m_leftRearEnc->Get();
  //double distance = m_leftRearEnc->GetDistance();
  frc::SmartDashboard::PutString("DB/String 0", "LR distance: " + std::to_string(m_leftRearEnc->GetDistance()));
  frc::SmartDashboard::PutString("DB/String 1", "LF distance: " + std::to_string(m_leftFrontEnc->GetDistance()));
  frc::SmartDashboard::PutString("DB/String 2", "RR distance: " + std::to_string(m_rightRearEnc->GetDistance()));
  frc::SmartDashboard::PutString("DB/String 3", "RF distance: " + std::to_string(m_rightFrontEnc->GetDistance()));
}

void Robot::TestPeriodic() {}
void Robot::TeleopInit() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <frc/Joystick.h>
#include <frc/Talon.h>
#include <frc/Timer.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/livewindow/LiveWindow.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

  Robot() {    
      m_robotDrive.SetExpiration(0.1);    
      m_timer.Start();  
    }

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;

  // Robot drive system  
  frc::Talon m_leftRear{0};  
  frc::Talon m_leftFront{1};  
  frc::Talon m_rightRear{2};  
  frc::Talon m_rightFront{3};  
  frc::MecanumDrive m_robotDrive{m_leftFront, m_leftRear, m_rightFront, m_rightRear};
  // frc::DifferentialDrive m_robotDrive{m_left, m_right};
  frc::Joystick m_stick{0};  
  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();  
  frc::Timer m_timer;





};

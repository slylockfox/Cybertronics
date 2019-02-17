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
#include <frc/Encoder.h>

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
      m_leftRearEnc->SetMaxPeriod(.1);
      m_leftRearEnc->SetMinRate(10);
      m_leftRearEnc->SetDistancePerPulse(5);
      m_leftRearEnc->SetReverseDirection(false);
      m_leftRearEnc->SetSamplesToAverage(7);
      m_leftRearEnc->Reset();

      m_leftFrontEnc->SetMaxPeriod(.1);
      m_leftFrontEnc->SetMinRate(10);
      m_leftFrontEnc->SetDistancePerPulse(5);
      m_leftFrontEnc->SetReverseDirection(false);
      m_leftFrontEnc->SetSamplesToAverage(7);
      m_leftFrontEnc->Reset();

      m_rightRearEnc->SetMaxPeriod(.1);
      m_rightRearEnc->SetMinRate(10);
      m_rightRearEnc->SetDistancePerPulse(5);
      m_rightRearEnc->SetReverseDirection(true);
      m_rightRearEnc->SetSamplesToAverage(7);
      m_rightRearEnc->Reset();

      m_rightFrontEnc->SetMaxPeriod(.1);
      m_rightFrontEnc->SetMinRate(10);
      m_rightFrontEnc->SetDistancePerPulse(5);
      m_rightFrontEnc->SetReverseDirection(true);
      m_rightFrontEnc->SetSamplesToAverage(7);
      m_rightFrontEnc->Reset();

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

  frc::Encoder *m_leftRearEnc = new frc::Encoder(0, 1, false, frc::Encoder::EncodingType::k4X);
  frc::Encoder *m_leftFrontEnc = new frc::Encoder(2, 3, false, frc::Encoder::EncodingType::k4X);
  frc::Encoder *m_rightRearEnc = new frc::Encoder(4, 5, false, frc::Encoder::EncodingType::k4X);
  frc::Encoder *m_rightFrontEnc = new frc::Encoder(6, 7, false, frc::Encoder::EncodingType::k4X);

  frc::MecanumDrive m_robotDrive{m_leftFront, m_leftRear, m_rightFront, m_rightRear};
 
  frc::Joystick m_stick{0};  
  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();  
  frc::Timer m_timer;





};

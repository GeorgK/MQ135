/**************************************************************************/
/*!
@file     MQ135.h
@author   G.Krocker (Mad Frog Labs)
@license  GNU GPLv3

First version of an Arduino Library for the MQ135 gas sensor
TODO: Review the correction factor calculation. This currently relies on
the datasheet but the information there seems to be wrong.

@section  HISTORY

v1.0 - First release
*/
/**************************************************************************/
#ifndef MQ135_H
#define MQ135_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

/// The load resistance on the board, in KOhms
#define MQ135_RLOAD 10.0
/// Calibration sensor resistance at atmospheric CO2 level, in KOhms
#define MQ135_RZERO 76.63
/// Parameters for calculating ppm of CO2 from sensor resistance
//#define PARA 116.6020682
//#define PARB 2.769034857
#define PARA 117.185
#define PARB 2.65797

/// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

/// Atmospheric CO2 level for calibration purposes, in PPM.
/// See http://co2now.org/
#define MQ135_ATMOCO2 397.16

/// Test voltage applied to the A pins of MQ-135, in volts. Usually, it's equal to power supply voltage.
#define MQ135_VC  5.0
/// analogRead reference voltage, in volts. By default it's a power supply voltage on Arduino. Can be changed with analogReference().
#define MQ135_VREF 5.0

class MQ135 {
 private:
  uint8_t _pin;
  // Calibration sensor resistance at atmospheric CO2 level, in KOhms
  float _rzero;
  // Atmospheric CO2 level for calibration purposes, in PPM, see http://co2now.org/
  float _atmoco2;
  // analogRead reference voltage, in volts
  float _vref;
  // Load resistance on board, in KOhms
  float _rload;
  // Test voltage applied to the A pins of MQ-135, in volts
  float _vc;

 public:
  MQ135(uint8_t pin, float rload = MQ135_RLOAD, float rzero = MQ135_RZERO,
          float atmoco2 = MQ135_ATMOCO2, float vref = MQ135_VREF,
          float vc = MQ135_VC);
  float getCorrectionFactor(float t, float h);
  float getResistance();
  float getCorrectedResistance(float t, float h);
  float getPPM();
  float getCorrectedPPM(float t, float h);
  float getRZero();
  float getCorrectedRZero(float t, float h);
};
#endif

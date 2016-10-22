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

/// To convert readed resistance into ohms
#define RLOAD 10.0
/// R0 for AIR
#define r0Air 1
/// R0 for CO **measured with 24hrs of exposure**
#define r0CO 69.65
/// R0 for CO2 **realized 24 hrs of exposure**
#define r0CO2 553.232
/// R0 for Ethanol **measured with 24hrs of exposure**
#define r0Ethanol 240.293
/// R0 for Ammonium **measured with 24hrs of exposure**
#define r0NH4 164.8282
/// R0 for Toluene **measured with 24hrs of exposure**
#define r0Toluene 130.726
/// R0 for Acetone **measured with 24hrs of exposure**
#define r0Acetone 224.6261
/// Parameters Equation for CO
#define scaleFactorCO 662.9382
#define exponentCO 4.0241
/// Parameters Equation for CO2
#define scaleFactorCO2 116.6020682
#define exponentCO2 2.769034857
///	Paremeters Equation for Ethanol
#define scaleFactorEthanol 75.3103
#define exponentEthanol 3.1459
/// Parameters Equation for NH4
#define scaleFactorNH4 102.694
#define exponentNH4 2.48818
/// Parameters Equation for Toluene
#define scaleFactorToluene 43.7748
#define exponentToluene 3.42936
/// Parameters Equation for Acetone
#define scaleFactorAcetone 33.1197
#define exponentAcetone 3.36587
/// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018
/// Atmospheric CO Level for calibration purposes
#define atmCO 1
/// Atmospheric CO2 level for calibration purposes
#define atmCO2 407.57
/// Atmospheric Ethanol Level for calibration purposes https://www.mathesongas.com/pdfs/msds/00224106.pdf
#define atmEthanol 22.5
/// Atmospheric NH4 level for calibration purposes
#define atmNH4 15
/// Atmospheric Toluene level for calibration purposes
#define atmToluene 2.9
/// Atmospheric Acetone level for calibration purposes
#define atmAcetone 16

class MQ135 {
 private:
  uint8_t _pin;

 public:
  MQ135(uint8_t pin);
  float getResistance();
  
  float getCOPPM();
  float getCO2PPM();
  float getEthanolPPM();
  float getNH4PPM();
  float getToluenePPM();
  float getAcetonePPM();
  
  float getRZeroCO();
  float getRZeroCO2();
  float getRZeroEthanol();
  float getRZeroNH4();
  float getRZeroToluene();
  float getRZeroAcetone();
  
  float getCO(float res);
  float getCO2(float res);
  float getEthanol(float res);
  float getNH4(float res);
  float getToluene(float res);
  float getAcetone(float res);
  
  
  float getCorrectedRZero(float r);
  float getCorrectedRZeroCO(float r);
  float getCorrectedRZeroEthanol(float r);
  float getCorrectedRZeroNH4(float r);
  float getCorrectedRZeroToluene(float r);
  float getCorrectedRZeroAcetone(float r);
  
  float getCorrectedResistance(float t, float h);
  float getCorrectionFactor(float t, float h);
  
  float getCalibratedCO2(float t, float h);
  float getCalibratedCO(float t, float h);
  float getCalibratedEthanol(float t, float h);
  float getCalibratedNH4(float t, float h);
  float getCalibratedToluene(float t, float h);
  float getCalibratedAcetone(float t, float h);


};
#endif

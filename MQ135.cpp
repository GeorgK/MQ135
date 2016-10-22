/**************************************************************************/
/*!
@file     MQ135.cpp
@author   G.Krocker (Mad Frog Labs)
@license  GNU GPLv3

First version of an Arduino Library for the MQ135 gas sensor
TODO: Review the correction factor calculation. This currently relies on
the datasheet but the information there seems to be wrong.

@section  HISTORY

v1.0 - First release
*/
/**************************************************************************/

#include "MQ135.h"

/**************************************************************************/
/*!
@brief  Default constructor

@param[in] pin  The analog input pin for the readout of the sensor
*/
/**************************************************************************/

MQ135::MQ135(uint8_t pin) {
  _pin = pin;
}
/**************************************************************************/
/*!
@brief  Get the resistance of the sensor, ie. the measurement value

@return The sensor resistance in Ohms
*/
/**************************************************************************/
float MQ135::getResistance() {
  int val = analogRead(_pin);
  return ((1024./(float)val) * 5. - 1.)*RLOAD;
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO sensed
@return ppm value of CO in air
*/
/**************************************************************************/
float MQ135::getCOPPM() {
  return scaleFactorCO * pow((getResistance()/r0CO), -exponentCO);
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air)

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getCO2PPM() {
  return scaleFactorCO2 * pow((getResistance()/r0CO2), -exponentCO2);
}
/**************************************************************************/
/*!
@brief  Get the ppm of Ethanol sensed 

@return The ppm of Ethanol in the air
*/
/**************************************************************************/
float MQ135::getEthanolPPM() {
  return scaleFactorEthanol * pow((getResistance()/r0Ethanol), -exponentEthanol);
}
/**************************************************************************/
/*!
@brief  Get the ppm of NH4 sensed 

@return The ppm of NH4 in the air
*/
/**************************************************************************/
float MQ135::getNH4PPM() {
  return scaleFactorNH4 * pow((getResistance()/r0NH4), -exponentNH4);
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air)

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getToluenePPM() {
  return scaleFactorToluene * pow((getResistance()/r0Toluene), -exponentToluene);
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air)

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getAcetonePPM() {
  return scaleFactorAcetone * pow((getResistance()/r0Acetone), -exponentAcetone);
}
/**************************************************************************/
/*!
@brief  Get the resistance RZero of the sensor for calibration purposes

@return The sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getRZeroCO() {
  return getResistance() * pow((atmCO/scaleFactorCO), (1./exponentCO));
}
/**************************************************************************/
/*!
@brief  Get the resistance RZero of the sensor for calibration purposes

@return The sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getRZeroCO2() {
  return getResistance() * pow((atmCO2/scaleFactorCO2), (1./exponentCO2));
}
/**************************************************************************/
/*!
@brief  Get the resistance RZero of the sensor for calibration purposes

@return The sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getRZeroEthanol() {
  return getResistance() * pow((atmEthanol/scaleFactorEthanol), (1./exponentEthanol));
}
/**************************************************************************/
/*!
@brief  Get the resistance RZero of the sensor for calibration purposes

@return The sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getRZeroNH4() {
  return getResistance() * pow((atmNH4/scaleFactorNH4), (1./exponentNH4));
}
/**************************************************************************/
/*!
@brief  Get the resistance RZero of the sensor for calibration purposes

@return The sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getRZeroToluene() {
  return getResistance() * pow((atmToluene/scaleFactorToluene), (1./exponentToluene));
}
/**************************************************************************/
/*!
@brief  Get the resistance RZero of the sensor for calibration purposes

@return The sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getRZeroAcetone() {
  return getResistance() * pow((atmAcetone/scaleFactorAcetone), (1./exponentAcetone));
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO sensed
@return ppm value of CO in air
*/
/**************************************************************************/
float MQ135::getCO(float res) {
  return scaleFactorCO * pow((res/r0CO), -exponentCO);
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air)

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getCO2(float res) {
  return scaleFactorCO2 * pow((res/r0CO2), -exponentCO2);
}
/**************************************************************************/
/*!
@brief  Get the ppm of Ethanol sensed 

@return The ppm of Ethanol in the air
*/
/**************************************************************************/
float MQ135::getEthanol(float res) {
  return scaleFactorEthanol * pow((res/r0Ethanol), -exponentEthanol);
}
/**************************************************************************/
/*!
@brief  Get the ppm of NH4 sensed 

@return The ppm of NH4 in the air
*/
/**************************************************************************/
float MQ135::getNH4(float res) {
  return scaleFactorNH4 * pow((res/r0NH4), -exponentNH4);
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air)

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getToluene(float res) {
  return scaleFactorToluene * pow((res/r0Toluene), -exponentToluene);
}
/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air)

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getAcetone(float res) {
  return scaleFactorAcetone * pow((res/r0Acetone), -exponentAcetone);
}
/* RETURN THE RZERO WITH A PARAMETER OF RESISTANCE*/
float MQ135::getCorrectedRZero(float r) {
  return r * pow((atmCO2/scaleFactorCO2), (1./exponentCO2));
}
float MQ135::getCorrectedRZeroCO(float r) {
  return r * pow((atmCO/scaleFactorCO), (1./exponentCO));
}
float MQ135::getCorrectedRZeroEthanol(float r) {
  return r * pow((atmEthanol/scaleFactorEthanol), (1./exponentEthanol));
}
float MQ135::getCorrectedRZeroNH4(float r) {
  return r * pow((atmNH4/scaleFactorNH4), (1./exponentNH4));
}
float MQ135::getCorrectedRZeroToluene(float r) {
  return r * pow((atmToluene/scaleFactorToluene), (1./exponentToluene));
}
float MQ135::getCorrectedRZeroAcetone(float r) {
  return r * pow((atmAcetone/scaleFactorAcetone), (1./exponentAcetone));
}
/*CORRECTED RESISTANCE*/
float MQ135::getCorrectedResistance(float t, float h) {
  return getResistance()/getCorrectionFactor(t, h);
}
/*CORRECTION FACTOR*/
float MQ135::getCorrectionFactor(float t, float h) {
  return CORA * t * t - CORB * t + CORC - (h-33.)*CORD;
}

float MQ135::getCalibratedCO2(float t, float h){
  return scaleFactorCO2 * pow((getCorrectedResistance(t, h)/getCorrectedRZero(getCorrectedResistance(t, h))), -exponentCO2);
}
float MQ135::getCalibratedCO(float t, float h) {
  return scaleFactorCO * pow((getCorrectedResistance(t, h)/getCorrectedRZeroCO(getCorrectedResistance(t, h))), -exponentCO);
}
float MQ135::getCalibratedEthanol(float t, float h) {
  return scaleFactorEthanol * pow((getCorrectedResistance(t, h)/getCorrectedRZeroEthanol(getCorrectedResistance(t, h))), -exponentEthanol);
}
float MQ135::getCalibratedNH4(float t, float h) {
  return scaleFactorNH4 * pow((getCorrectedResistance(t, h)/getCorrectedRZeroNH4(getCorrectedResistance(t, h))), -exponentNH4);
}
float MQ135::getCalibratedToluene(float t, float h) {
  return scaleFactorToluene * pow((getCorrectedResistance(t, h)/getCorrectedRZeroToluene(getCorrectedResistance(t, h))), -exponentToluene);
}
float MQ135::getCalibratedAcetone(float t, float h) {
  return scaleFactorAcetone * pow((getCorrectedResistance(t, h)/getCorrectedRZeroAcetone(getCorrectedResistance(t, h))), -exponentAcetone);
}

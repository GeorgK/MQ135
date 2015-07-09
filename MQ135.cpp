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

@param[in] pin      The analog input pin for the readout of the sensor
@param[in] rload    Load resistance on board, in KOhms
@param[in] rzero    Calibration sensor resistance at atmospheric CO2 level, in KOhms
@param[in] atmoco2  Atmospheric CO2 level for calibration purposes, in PPM
@param[in] vref     analogRead() reference voltage, in volts
@param[in] vc       Test voltage applied to the A pins of MQ-135, in volts
*/
/**************************************************************************/

MQ135::MQ135(uint8_t pin, float rload, float rzero, float atmoco2, float vref, float vc) {
  _pin = pin;
  _rload = rload;
  _rzero = rzero;
  _atmoco2 = atmoco2;
  _vref = vref;
  _vc = vc;
}


/**************************************************************************/
/*!
@brief  Get the correction factor to correct for temperature and humidity

@param[in] t  The ambient air temperature
@param[in] h  The relative humidity

@return The calculated correction factor
*/
/**************************************************************************/
float MQ135::getCorrectionFactor(float t, float h) {
  //return CORA * t * t - CORB * t + CORC - (h-33.)*CORD;

  // This formula is reduced from temperature and humidity dependency graph,
  // found in this datasheet:
  // http://china-total.com/Product/meter/gas-sensor/MQ135.pdf
  return (1.30732 - 0.0116044 * t) * (2.20591 - 0.296456 * log(h));
}

/**************************************************************************/
/*!
@brief  Get the resistance of the sensor, ie. the measurement value

@return The sensor resistance in kOhm
*/
/**************************************************************************/
float MQ135::getResistance() {
  int val = analogRead(_pin);
  float r;

  //r = ((1023./(float)val) - 1.)*_rload;
  // or taking Vref and Vc into account:
  r = ((1023. * _rload * _vc) / ((float)val * _vref)) - _rload;

  return r;
}

/**************************************************************************/
/*!
@brief  Get the resistance of the sensor, ie. the measurement value corrected
        for temp/hum

@param[in] t  The ambient air temperature
@param[in] h  The relative humidity

@return The corrected sensor resistance kOhm
*/
/**************************************************************************/
float MQ135::getCorrectedResistance(float t, float h) {
  return getResistance()/getCorrectionFactor(t, h);
}

/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air)

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getPPM() {
  return PARA * pow((getResistance()/_rzero), -PARB);
}

/**************************************************************************/
/*!
@brief  Get the ppm of CO2 sensed (assuming only CO2 in the air), corrected
        for temp/hum

@param[in] t  The ambient air temperature
@param[in] h  The relative humidity

@return The ppm of CO2 in the air
*/
/**************************************************************************/
float MQ135::getCorrectedPPM(float t, float h) {
  return PARA * pow((getCorrectedResistance(t, h)/_rzero), -PARB);
}

/**************************************************************************/
/*!
@brief  Get the resistance RZero of the sensor for calibration purposes

@return The sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getRZero() {
  return getResistance() * pow((_atmoco2/PARA), (1./PARB));
}

/**************************************************************************/
/*!
@brief  Get the corrected resistance RZero of the sensor for calibration
        purposes

@param[in] t  The ambient air temperature
@param[in] h  The relative humidity

@return The corrected sensor resistance RZero in kOhm
*/
/**************************************************************************/
float MQ135::getCorrectedRZero(float t, float h) {
  return getCorrectedResistance(t, h) * pow((_atmoco2/PARA), (1./PARB));
}

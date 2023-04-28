



#include "Arduino.h"
#include "QMC5883LCompass.h"
#include <Wire.h>

void QMC5883LCompass::init(){
	Wire.begin();
	_writeReg(0x0B,0x01);
	setMode(0x01,0x0C,0x10,0X00);
}

void QMC5883LCompass::_writeReg(byte r, byte v){
	Wire.beginTransmission(_ADDR);
	Wire.write(r);
	Wire.write(v);
	Wire.endTransmission();
}




void QMC5883LCompass::setMode(byte mode, byte odr, byte rng, byte osr){
	_writeReg(0x09,mode|odr|rng|osr);
}





void QMC5883LCompass::setSmoothing(byte steps, bool adv){
	_smoothUse = true;
	_smoothSteps = ( steps > 10) ? 10 : steps;
	_smoothAdvanced = (adv == true) ? true : false;
}


void QMC5883LCompass::setCalibration(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max){
	_calibrationUse = true;

	_vCalibration[0][0] = x_min;
	_vCalibration[0][1] = x_max;
	_vCalibration[1][0] = y_min;
	_vCalibration[1][1] = y_max;
	_vCalibration[2][0] = z_min;
	_vCalibration[2][1] = z_max;
}




void QMC5883LCompass::read(){
	Wire.beginTransmission(_ADDR);
	Wire.write(0x00);
	int err = Wire.endTransmission();
	if (!err) {
		Wire.requestFrom(_ADDR, (byte)6);
		_vRaw[0] = (int)(int16_t)(Wire.read() | Wire.read() << 8);
		_vRaw[1] = (int)(int16_t)(Wire.read() | Wire.read() << 8);
		_vRaw[2] = (int)(int16_t)(Wire.read() | Wire.read() << 8);

		if ( _calibrationUse ) {
			_applyCalibration();
		}
		
		if ( _smoothUse ) {
			_smoothing();
		}
		
		
		
	}
}


void QMC5883LCompass::_applyCalibration(){
	int x_offset = (_vCalibration[0][0] + _vCalibration[0][1])/2;
	int y_offset = (_vCalibration[1][0] + _vCalibration[1][1])/2;
	int z_offset = (_vCalibration[2][0] + _vCalibration[2][1])/2;
	int x_avg_delta = (_vCalibration[0][1] - _vCalibration[0][0])/2;
	int y_avg_delta = (_vCalibration[1][1] - _vCalibration[1][0])/2;
	int z_avg_delta = (_vCalibration[2][1] - _vCalibration[2][0])/2;

	int avg_delta = (x_avg_delta + y_avg_delta + z_avg_delta) / 3;

	float x_scale = (float)avg_delta / x_avg_delta;
	float y_scale = (float)avg_delta / y_avg_delta;
	float z_scale = (float)avg_delta / z_avg_delta;

	_vCalibrated[0] = (_vRaw[0] - x_offset) * x_scale;
	_vCalibrated[1] = (_vRaw[1] - y_offset) * y_scale;
	_vCalibrated[2] = (_vRaw[2] - z_offset) * z_scale;
}



void QMC5883LCompass::_smoothing(){
	byte max = 0;
	byte min = 0;
	
	if ( _vScan > _smoothSteps - 1 ) { _vScan = 0; }
	
	for ( int i = 0; i < 3; i++ ) {
		if ( _vTotals[i] != 0 ) {
			_vTotals[i] = _vTotals[i] - _vHistory[_vScan][i];
		}
		_vHistory[_vScan][i] = ( _calibrationUse ) ? _vCalibrated[i] : _vRaw[i];
		_vTotals[i] = _vTotals[i] + _vHistory[_vScan][i];
		
		if ( _smoothAdvanced ) {
			max = 0;
			for (int j = 0; j < _smoothSteps - 1; j++) {
				max = ( _vHistory[j][i] > _vHistory[max][i] ) ? j : max;
			}
			
			min = 0;
			for (int k = 0; k < _smoothSteps - 1; k++) {
				min = ( _vHistory[k][i] < _vHistory[min][i] ) ? k : min;
			}
					
			_vSmooth[i] = ( _vTotals[i] - (_vHistory[max][i] + _vHistory[min][i]) ) / (_smoothSteps - 2);
		} else {
			_vSmooth[i] = _vTotals[i]  / _smoothSteps;
		}
	}
	
	_vScan++;
}



int QMC5883LCompass::getX(){
	return _get(0);
}



int QMC5883LCompass::getY(){
	return _get(1);
}



int QMC5883LCompass::getZ(){
	return _get(2);
}


int QMC5883LCompass::_get(int i){
	if ( _smoothUse ) 
		return _vSmooth[i];
	
	if ( _calibrationUse )
		return _vCalibrated[i];

	return _vRaw[i];
}




byte QMC5883LCompass::getBearing(int azimuth){
	unsigned long a = azimuth / 22.5;
	unsigned long r = a - (int)a;
	byte sexdec = 0;	
	sexdec = ( r >= .5 ) ? ceil(a) : floor(a);
	return sexdec;
}



void QMC5883LCompass::getDirection(char* myArray, int azimuth){
	int d = getBearing(azimuth);
	myArray[0] = _bearings[d][0];
	myArray[1] = _bearings[d][1];
	myArray[2] = _bearings[d][2];
}
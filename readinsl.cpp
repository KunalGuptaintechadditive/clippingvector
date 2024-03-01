#pragma once

#include "ReadINSL.h"
#include "IntechHMIutil.h"

#define _scaleFactor 10000

ReadINSL::ReadINSL()
{

}
ReadINSL::~ReadINSL()
{

}

void ReadINSL::readHeader(std::ifstream& inFile)
{
	int _val = 0;

#pragma region _Validate File Version_

	std::getline(inFile, _ambVersion, '\n');   // AM-Builder Version    
	std::getline(inFile, _fileVersion, '\n');   // File Version    
	std::getline(inFile, _creationDate, '\n');   // Created Date Version     

}

void ReadINSL::ReadFile(INSLMemoryManagementClass& memoryobj, std::ifstream& inFile)
{

}

void ReadINSL::ReadPowerSpeed(std::ifstream& inFile, double& _power, double& _speed)
{

	int _val = 0;

	ReadByte(inFile, _val, sizeof(int)); // power
	_power = ((double)_val / _scaleFactor);
	ReadByte(inFile, _val, sizeof(int)); // speed
	_speed = ((double)_val / _scaleFactor);
}

void ReadINSL::SetProgressBar(int _val)
{
	try
	{
		if (_val > ProgressBar)
		{
			if (ProgressBarEvent != NULL)
			{
				if (_val <= 100 && _val >= 1)
				{
					ProgressBarEvent((int)_val);
					ProgressBar = _val;
				}
			}
		}
	}
	catch (std::exception)
	{
		std::string msg = "Exception in ProgressBar";
		////throw ApiException(msg);
	}
}

bool ReadINSL::CheckHatchType(int _in)
{
	switch (_in)
	{
	case Down_Hatch: return true;
		break;
	case Onpart_Hatch: return true;
		break;
	case Up_Hatch: return true;
		break;
	case Support_Hatch: return true;
		break;
	}
	return false;
}

INSLversion_010::INSLversion_010()
{

}

void INSLversion_010::ReadFile(INSLMemoryManagementClass& memoryobj, std::ifstream& inFile)
{
	try
	{
		int _val;

#pragma region LaserInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int));// num of Laser
		int _size = _val;
		for (int _index = 0; _index < _size; ++_index)
		{

			double _value = 0.0;
			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser id
			_laserInf.laserId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser x position
			_laserInf._xPos = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser y position
			_laserInf._yPos = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser angle
			_laserInf._angle = ((double)_val / _scaleFactor);

			memoryobj.pushLaser(_laserInf);
		}
#pragma endregion

#pragma region PartInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of Part
		_size = _val;
		for (int _index = 0; _index < _size; ++_index)
		{

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part id
			ReadINSL::_partInfo.partId = _val;

			std::getline(inFile, ReadINSL::_partInfo._partName, '\0');   // part Name

			ReadByteExceptionHandling(inFile, _val, sizeof(int));// part exposure flag
			ReadINSL::_partInfo._exposureFlag = (bool)_val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part xmin
			ReadINSL::_partInfo._bound.xMin = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part ymin
			ReadINSL::_partInfo._bound.yMin = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part xmax
			ReadINSL::_partInfo._bound.xMax = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part ymax
			ReadINSL::_partInfo._bound.yMax = ((double)_val / _scaleFactor);

			memoryobj.pushPart(ReadINSL::_partInfo);
		}
#pragma endregion

#pragma region ParameterInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of Parameter
		_size = _val;

		for (int _index = 0; _index < _size; ++_index)
		{
			Parameter_Info _paramInfo{};
			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // parameter id
			_paramInfo._paramId = _val;
			int pathtype;

			double _power = 0.0, _speed = 0.0;


			ReadByteExceptionHandling(inFile, _val, sizeof(int)); //Skip Path Type

			ReadPowerSpeed(inFile, _power, _speed);
			_paramInfo._downHatch = std::make_tuple(_power, _speed);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); //Skip Path Type

			ReadPowerSpeed(inFile, _power, _speed);
			_paramInfo._onPartHatch = std::make_tuple(_power, _speed);

			ReadByte(inFile, _val, sizeof(int)); //Skip Path Type

			ReadPowerSpeed(inFile, _power, _speed);
			_paramInfo._upHatch = std::make_tuple(_power, _speed);

			ReadByteExceptionHandling(inFile, _val, sizeof(int));//Skip Path Type

			ReadPowerSpeed(inFile, _power, _speed);
			_paramInfo._supportHatch = std::make_tuple(_power, _speed);

			ReadByteExceptionHandling(inFile, _val, sizeof(int));//Skip Path Type

			ReadPowerSpeed(inFile, _power, _speed);
			_paramInfo._downContour = std::make_tuple(_power, _speed);

			ReadByteExceptionHandling(inFile, _val, sizeof(int));//Skip Path Type

			ReadPowerSpeed(inFile, _power, _speed);
			_paramInfo._onPartContour = std::make_tuple(_power, _speed);

			ReadByteExceptionHandling(inFile, _val, sizeof(int));//Skip Path Type

			ReadPowerSpeed(inFile, _power, _speed);
			_paramInfo._upContour = std::make_tuple(_power, _speed);

			memoryobj.pushParameter(_paramInfo);
		}
#pragma endregion

#pragma region ManagedInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int));// num of Manage
		_size = _val;

		for (int _index = 0; _index < _size; ++_index)
		{
			Managed_Info _mngInfo{};
			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser id
			_mngInfo.laserId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part id
			_mngInfo.partId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // parameter id
			_mngInfo.paramId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // manage id
			_mngInfo.mngId = _val;

			memoryobj.pushManaged(_mngInfo);
		}

#pragma endregion

#pragma region LayerInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of Layer
		int _numOfLayer = _val;

		this->_layerCount = _numOfLayer;

		for (int _layer = 0; _layer < _numOfLayer; ++_layer)
		{
			int _startPosition = 0;

			_startPosition = (int)inFile.tellg();
			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // layer id

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of mid loop
			int _numOfMngLoop = _val;

			for (int _mngloop = 0; _mngloop < _numOfMngLoop; ++_mngloop)
			{
				ReadByteExceptionHandling(inFile, _val, sizeof(int)); // manage id

				ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of paths
				int _numOfPaths = _val;

				for (int _pathLoop = 0; _pathLoop < _numOfPaths; ++_pathLoop)
				{
					ReadByteExceptionHandling(inFile, _val, sizeof(int));// path type
					int _type = _val;

					if (CheckHatchType(_type))
					{
						ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of coord
						int _numOfHatch = _val;

						for (int _hatchLoop = 0; _hatchLoop < _numOfHatch; ++_hatchLoop)
						{
							//ReadByte(inFile, _val, sizeof(int)); // delay value

							//ReadByte(inFile, _val, sizeof(int)); // x1

							//ReadByte(inFile, _val, sizeof(int)); // y1

							//ReadByte(inFile, _val, sizeof(int)); // x2

							//ReadByte(inFile, _val, sizeof(int));// y2 
						}
						int position = 5 * sizeof(int) * _numOfHatch;
						inFile.seekg(position, inFile.cur);
					}
					else
					{
						ReadByteExceptionHandling(inFile, _val, sizeof(int)); // delay value

						ReadByteExceptionHandling(inFile, _val, sizeof(int));// num of coord
						int _numOfContour = _val;

						for (int _contourLoop = 0; _contourLoop < _numOfContour; ++_contourLoop)
						{
							//ReadByte(inFile, _val, sizeof(int)); // x1

							//ReadByte(inFile, _val, sizeof(int)); // y1
						}
						int position = 2 * sizeof(int) * _numOfContour;
						inFile.seekg(position, inFile.cur);
					}
				}
			}
			int perVal = (int)((double)((double)((long long)_layer + 1) / _numOfLayer) * 100);
			SetProgressBar(perVal);
			memoryobj.pushLayerIndex(_layer + 1, _startPosition);
		}
#pragma endregion

		ReadByteExceptionHandling(inFile, _val, sizeof(int)); // Layerthickness

		layerthickness = _val;

	}
	catch (std::exception)
	{
		std::string msg = "Exception in ReadINSL function for INSL version 0.1.0.";
		////throw ApiException(msg);
	}
}


INSLversion_020::INSLversion_020()
{

}

void INSLversion_020::ReadFile(INSLMemoryManagementClass& memoryobj, std::ifstream& inFile, int _layer)
{
	try
	{

		int _val;
		std::string msg = "Exception in ReadINSL function for INSL version 0.1.0.";
		//throw ApiException(msg);
#pragma region LaserInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int));// num of Laser
		int _size = _val;
		for (int _index = 0; _index < _size; ++_index)
		{

			double _value = 0.0;
			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser id
			_laserInf.laserId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser x position
			_laserInf._xPos = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser y position
			_laserInf._yPos = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser angle
			_laserInf._angle = ((double)_val / _scaleFactor);

			memoryobj.pushLaser(_laserInf);
		}
#pragma endregion

#pragma region PartInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of Part
		_size = _val;
		for (int _index = 0; _index < _size; ++_index)
		{

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part id
			ReadINSL::_partInfo.partId = _val;

			std::getline(inFile, ReadINSL::_partInfo._partName, '\0');   // part Name

			ReadByteExceptionHandling(inFile, _val, sizeof(int));// part exposure flag
			ReadINSL::_partInfo._exposureFlag = (bool)_val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part xmin
			ReadINSL::_partInfo._bound.xMin = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part ymin
			ReadINSL::_partInfo._bound.yMin = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part xmax
			ReadINSL::_partInfo._bound.xMax = ((double)_val / _scaleFactor);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part ymax
			ReadINSL::_partInfo._bound.yMax = ((double)_val / _scaleFactor);

			memoryobj.pushPart(ReadINSL::_partInfo);
		}
#pragma endregion


#pragma region ParameterInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of Parameter
		_size = _val;

		for (int _index = 0; _index < _size; ++_index)
		{
			Parameter_Info _paramInfo{};
			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // parameter id
			_paramInfo._paramId = _val;
			int pathtype;
			double _power = 0.0, _speed = 0.0;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of Parameter
			int _laserParamSize = _val;
			for (int i = 0; i < _laserParamSize; i++)
			{

				ReadByteExceptionHandling(inFile, _val, sizeof(int)); //Path Type
				pathtype = _val;
				ReadPowerSpeed(inFile, _power, _speed);

				ReadByteExceptionHandling(inFile, _val, sizeof(int)); //Index
				std::tuple<int, double, double, int> ParamEntity{ pathtype, _power, _speed, _val };
				_paramInfo._parameterList.push_back(ParamEntity);

			}

			memoryobj.pushParameter(_paramInfo);


		}
#pragma endregion

#pragma region ManagedInformation
		ReadByteExceptionHandling(inFile, _val, sizeof(int));// num of Manage
		_size = _val;

		for (int _index = 0; _index < _size; ++_index)
		{
			Managed_Info _mngInfo{};
			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // laser id
			_mngInfo.laserId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // part id
			_mngInfo.partId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // parameter id
			_mngInfo.paramId = _val;

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // manage id
			_mngInfo.mngId = _val;

			memoryobj.pushManaged(_mngInfo);
		}

#pragma endregion

#pragma region LayerInformation

		ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of Layer
		int _numOfLayer = _val;

		this->_layerCount = _numOfLayer;

		for (int layer = 1; layer <= _layer; ++layer) {

			unsigned long long _startPosition = 0;

			_startPosition = inFile.tellg();
			//ReadByteExceptionHandling(inFile, _val, sizeof(int)); // layer id
			//for skipping layer
			int position = sizeof(int);
			inFile.seekg(position, inFile.cur);

			ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of mid loop
			int _numOfMngLoop = _val;

			for (int _mngloop = 0; _mngloop < _numOfMngLoop; ++_mngloop)
			{
				//ReadByteExceptionHandling(inFile, _val, sizeof(int)); // manage id
				position = sizeof(int);
				inFile.seekg(position, inFile.cur);

				ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of paths
				int _numOfPaths = _val;

				for (int _pathLoop = 0; _pathLoop < _numOfPaths; ++_pathLoop)
				{
					ReadByteExceptionHandling(inFile, _val, sizeof(int));// path type
					int _paramIndx = _val;

					if (_paramIndx < 4)
					{
						ReadByteExceptionHandling(inFile, _val, sizeof(int)); // num of coord
						int _numOfHatch = _val;
						if (_layer == layer) {
							HatchInfo hatchinfo;
							hatchinfo.hatchpoints.reserve((int64_t)2 * _numOfHatch);

							//uncommented here
							for (int _hatchLoop = 0; _hatchLoop < _numOfHatch; ++_hatchLoop)
							{
								ReadByte(inFile, _val, sizeof(int)); // delay value

								ReadByte(inFile, _val, sizeof(int)); // x1
								float x = _val;
								x = x / 10000.0f;
								ReadByte(inFile, _val, sizeof(int)); // y1
								float y = _val;
								y = y / 10000.0f;
								hatchinfo.hatchpoints.emplace_back(cv::Point2f(x, y));

								ReadByte(inFile, _val, sizeof(int)); // x2
								x = _val;
								x = x / 10000.0f;
								ReadByte(inFile, _val, sizeof(int)); // y2 
								y = _val;
								y = y / 10000.0f;
								hatchinfo.hatchpoints.emplace_back(cv::Point2f(x, y));
							}
							//assuming taking baseplate center as 0,0
							memoryobj.pushHatchinfo(hatchinfo);

						}
						else {
							position = 5 * sizeof(int) * _numOfHatch;
							inFile.seekg(position, inFile.cur);
						}
					}
					else
					{
						//ReadByteExceptionHandling(inFile, _val, sizeof(int)); // delay value
						position = sizeof(int);
						inFile.seekg(position, inFile.cur);


						ReadByteExceptionHandling(inFile, _val, sizeof(int));// num of coord
						int _numOfContour = _val;
						if (_layer == layer) {
							ContourInfo contourinfo;
							contourinfo.contourpoints.reserve(_numOfContour);

							for (int _contourLoop = 0; _contourLoop < _numOfContour; ++_contourLoop)
							{
								ReadByte(inFile, _val, sizeof(int)); // x1
								float x = _val;
								//
								x = x / 10000.0f;
								ReadByte(inFile, _val, sizeof(int)); // y1
								float y = _val;
								y = y / 10000.0f;
								//point cordinate;
								contourinfo.contourpoints.emplace_back(cv::Point2f(x, y));
							}
							//assuming taking baseplate center as 0,0
							memoryobj.pushContourinfo(contourinfo);
							//contourinfo.contourpoints = _contourpoints
						}
						else {
							position = 2 * sizeof(int) * _numOfContour;
							inFile.seekg(position, inFile.cur);
						}
					}
				}
			}

			//int perVal = (int)((double)((double)((long long)_layer + 1) / _numOfLayer) * 100);
			//SetProgressBar(perVal);

			memoryobj.pushLayerIndex(_layer + 1, _startPosition);
		}

#pragma endregion

		//ReadByteExceptionHandling(inFile, _val, sizeof(int)); // Layerthickness

		//layerthickness = _val;
		int position = sizeof(int);
		inFile.seekg(position, inFile.cur);
	}
	catch (std::exception)
	{
		std::string msg = "Exception in ReadINSL function for INSL version 0.1.0.";
		//throw ApiException(msg);
	}

}

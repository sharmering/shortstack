#pragma once
#include <vector>
#include <string>
#include "AIGCJson/AIGCJson.hpp"

using namespace std;


#define OK	0
#define ERROR (-1)

class MainConf
{
public:
	string name;
	vector<int> masterSerialPorts;

	AIGC_JSON_HELPER(name, masterSerialPorts);
};

class DataType
{
public:
	enum DATATYPE
	{
		dtInt16,
		dtUint16,
		dtInt32,
		dtUint32,
		dtInt64,
		dtUint64,
		dtFloat,
		dtDouble,
		dtCoil,
		dtCustom = 0x80,
		dtJS = 0xA0,
		dtBCD = 0x100,
		dtSigned = 0x200,
		dtLittleEndian = 0x400,
		dtByteOrder = 0x800,
		dtBitReverse = 0x1000,
		dtBit = 0x2000,
		dtHolding2Coil = 0x4000,	   //Convert Short/Int type to BIT type
		dtRegTypeMask = (0xF << 16),   //Modbus Register Type Mask
		dtRegTypeCoil = (1 << 16),	   //Modbus Register RegCoilsCB type
		dtRegTypeDiscrete = (2 << 16), //Modbus Register RegDiscreteCB type
		dtRegTypeInput = (4 << 16),	   //Modbus Register RegInputCB type
		dtRegTypeHolding = (8 << 16)   //Modbus Register RegHoldingCB type
	};
};

class _ifConf
{
public:
	int ipConf;
	std::string ip;
	std::string netmask;
	std::string gateway;
	std::string mac;

	AIGC_JSON_HELPER(ipConf, ip, netmask, gateway, mac);
};

class netConf
{
public:
	std::string stationName; //added on 2019.09.26
	int stationType;		 //0: PSX643G 1U, 1: PSX643G-S DIN Rail
	int useDns;
	std::string dnsIp;
	int defroute;
	_ifConf ei0Conf;
	_ifConf ei1Conf;

	int calibrationMode;
	int calibrationProtocol;
	std::string calibrationSerialPortGuid;
	std::vector<std::string> calibrationIP;
	int calibrationPort;

	AIGC_JSON_HELPER(stationName, stationType, useDns, dnsIp, defroute, ei0Conf, ei1Conf, calibrationMode,
		calibrationProtocol, calibrationIP, calibrationSerialPortGuid, calibrationPort
	);

	netConf()
	{
		stationName = "I love you";
		defroute = 18;
		calibrationMode = 1;
	}
};

class _serialConf
{
public:
	int port;
	int baudrate;
	int dataBits;
	int parity;
	int stopBits;

	enum
	{
		BPS_1200 = 1200,
		BPS_2400 = 2400,
		BPS_4800 = 4800,
		BPS_9600 = 9600,
		BPS_19200 = 19200,
		BPS_38400 = 38400,
		BPS_57600 = 57600,
		BPS_115200 = 115200,
	};

	enum
	{
		PAR_NONE = 'N',
		PAR_ODD = 'O',
		PAR_EVEN = 'E'
	};

	enum
	{
		STOPBIT_1 = 1,
		STOPBIT_2,
	};

	_serialConf()
	{
		port = 0;
		baudrate = BPS_9600;
		parity = PAR_NONE;
		stopBits = STOPBIT_1;
		dataBits = 8;
	}
	AIGC_JSON_HELPER(port, baudrate, dataBits, parity, stopBits);
};

class ModbusDataParse
{
public:
	string name;
	int startAddr;
	int offset;
	int dataType;
	int len;
	int innerId;
	float deviation;
	float coef;
	int indexCode;
	float interval;
	vector<int> h2cInnerIdList;
	vector<string> h2cNameList;
	AIGC_JSON_HELPER(name, startAddr, offset, dataType, len, innerId, deviation, coef, indexCode,
                    interval, h2cInnerIdList, h2cNameList);
};

class ModbusCmdOut
{
public:
	int functionCode;
	vector<ModbusDataParse> vecOutData;
	AIGC_JSON_HELPER(functionCode, vecOutData);
};

class Modbus_TcpDevice
{
public:
	int IsEnabled;
	int stationAddress;
	int deviceId;
	string DeviceName;
	int collectPeriod;   //unit:second
	int collectMode;
	string Ip;
	int Port;
	int InnerIdBase;
	//ABCD, CDAB, ...
	int DataSequence;
	vector<ModbusCmdOut> vecCommands;
	AIGC_JSON_HELPER(IsEnabled, stationAddress, deviceId, DeviceName, collectPeriod, collectMode, Ip, Port, InnerIdBase, DataSequence);
};

class RtuOverTcpDevice
{
public:
	int IsEnabled;
	int stationAddress;
	int deviceId;
	string DeviceName;
	int collectPeriod;   //unit:second
	int collectMode;

	int InnerIdBase;
	//ABCD, CDAB, ...
	int DataSequence;
	vector<ModbusCmdOut> vecCommands;
	AIGC_JSON_HELPER(IsEnabled, stationAddress, deviceId, DeviceName, collectPeriod, collectMode);
};

class PortDev
{
public:
	int Port;
	string Note;
	vector<RtuOverTcpDevice> Devices;
	AIGC_JSON_HELPER(Port, Note, Devices);
};

class Modbus_RtuOverTcpDevice
{
public:
	string Ip;
	string Note;
	vector<PortDev> Portvector;
	AIGC_JSON_HELPER(Ip, Note, Portvector);
};

class RtuDevice
{
public:
	int IsEnabled;
	int stationAddress;
	string DeviceName;
	int collectPeriod;   //unit:second
	int collectMode;    //0:RTU, 1:DLT-645
	int InnerIdBase;
	//ABCD, CDAB, ...
	int DataSequence;
	vector<ModbusCmdOut> vecCommands;
	AIGC_JSON_HELPER(IsEnabled, stationAddress, DeviceName, collectPeriod, collectMode, InnerIdBase, DataSequence, vecCommands);
};

class Modbus_RtuSerialPortConf
{
public:
	int isEnabled;
	int portNum;
	string portName;
	int speed;
	int dataBits;
	string parity;
	int stopbBits;
	vector<RtuDevice> Devices;
	AIGC_JSON_HELPER(isEnabled, portNum, portName, speed, dataBits, parity, stopbBits, Devices);
};

class Iec104_TeleSginaling
{
public:
	string channelName;
	int innerId;
	int indexCode;
	AIGC_JSON_HELPER(channelName, innerId, indexCode);
};

class Iec104_TeleMetry
{
public:
	string channelName;
	int innerId;
	int indexCode;
	AIGC_JSON_HELPER(channelName, innerId, indexCode);
};

class Iec104_TeleControl
{
public:
	string channelName;
	int innerId;
	int indexCode;
	AIGC_JSON_HELPER(channelName, innerId, indexCode);
};

class Iec104Device
{
public:
	int IsEnabled;
	int ca;
	int deviceId;
	string DeviceName;
	string Ip;
	int Port;
	int InnerIdBase;
	int TeleSignalingStartAddr;
	int TeleMetryStartAddr;
	int TeleControlStartAddr;

	vector<Iec104_TeleSginaling> TeleSignalings;
	vector<Iec104_TeleMetry> TeleMetrys;
	vector<Iec104_TeleControl> TeleControls;
	AIGC_JSON_HELPER(IsEnabled, ca, deviceId, DeviceName, Ip, Port, InnerIdBase, TeleSignalingStartAddr,
		TeleMetryStartAddr, TeleControlStartAddr, TeleSignalings, TeleMetrys, TeleControls
	);
};

class MasterConf
{
public:
	string Name;
	vector<Modbus_TcpDevice> ModbusTcpDevices;
	//add other Masters
	vector<Modbus_RtuOverTcpDevice> Modbus_RtuOverTcpDevices;
	vector<Iec104Device> Iec104Devices;
	vector<Modbus_RtuSerialPortConf> ModbusRtuSerialPorts;

	AIGC_JSON_HELPER(Name, ModbusTcpDevices, Modbus_RtuOverTcpDevices, Iec104Devices);
};

class PortConf
{
public:
	int isEnabled;
	int portNum;
	string portName;
	int speed;
	int dataBits;
	string parity;
	int stopbBits;
	int collectPeriod;

	AIGC_JSON_HELPER(isEnabled, portNum, portName, speed, dataBits, parity, stopbBits, collectPeriod);
};



class DatabaseConf
{
public:
	std::vector<int> telesignalings;
	std::vector<int> telemetries;
	std::vector<int> telemecontrols;
	std::vector<int> telemeadjusts;

	AIGC_JSON_HELPER(telesignalings, telemetries, telemecontrols, telemeadjusts);
};

#pragma once

#ifndef Settings_h__
#define Settings_h__

#include "cplus/stdserialize.h"
#include "cplus/stdjson.h"
#include "prjConfig.h"
#include "bLib.h"
#include "sysLib.h"

//#ifdef __cplusplus
//extern "C"
//{
//#endif
//
//	unsigned long crc32(unsigned long init, const unsigned char* buffer, unsigned int length);
//
//#ifdef __cplusplus
//}
//#endif

#pragma diag_suppress 1446

#define FLT_MAX         3.402823466e+38F        /* max value */
#define FLT_MIN         1.175494351e-38F        /* min positive value */

#define FLASH_DISK  ""

const UINT32 crc32_tab[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

unsigned long crc32(unsigned long crc, const unsigned char* buf, unsigned int size) 
{
	crc = crc ^ ~0U;
	while (size--) {
		crc = crc32_tab[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
	}
	return crc ^ ~0U;
}

class CSettings : public Serializable<CSettings>
{
public:
	static CSettings& Current(void)
	{
		static CSettings _current;
		return _current;
	}

	BOOL FromBase64String(const char* base64, int base64len)
	{
		if (base64 && base64len > 0)
		{
			const std::string str(::FromBase64String(base64, base64len));
			std::stringstream strbuf(str);
			CBinaryIstream is(strbuf);
			if (ParseFromIstream(is))
				return TRUE;
		}

		return FALSE;
	}

	std::string ToBase64String(void)
	{
		std::ostringstream strbuf;
		CBinaryOstream os(strbuf);
		if (SerializeToOstream(os))
		{
			const std::string& str = strbuf.str();
			return ::ToBase64String(str.data(), str.size());
		}

		return std::string();
	}

	bool load(void)
	{
		if (access("./PSX643G.bin", O_RDONLY) != ERROR)
		{
			// printf("load bin file(Line 27)\n");
			if (VerifyCheckSum("./PSX643G.bin", FLASH_DISK "./PSX643G.crc"))
			{
				std::ifstream ifs("./PSX643G.bin", std::ios_base::binary);
				// printf("load bin file(Line 31)\n");
				if (ifs.is_open())
				{
					CBinaryIstream is(ifs);
					if (ParseFromIstream(is))
					{
						char szFilePath[64];
						snprintf(szFilePath, NELEMENTS(szFilePath), "./PSX643G.bin");
						kprintf("load bin file: %s\n", szFilePath);
						return true;
					}
				}
			}
		}

		if (access("./PSX643G.json", O_RDONLY) != ERROR)
		{
			if (VerifyCheckSum("./PSX643G.json", FLASH_DISK "./PSX643G.crc"))
			{
				CIstreamOnJSON is;
				if (is.load("./PSX643G.json") &&
					ParseFromIstream(is))
				{
					char szFilePath[64];
					snprintf(szFilePath, NELEMENTS(szFilePath), FLASH_DISK "./PSX643G.json");
					kprintf("load json file: %s\n", szFilePath);
					return true;
				}
			}
		}		
		return false;
	}

	void MakeBackupAndCheckSum(void)
	{
		if (access(FLASH_DISK "./PSX643G.bin", O_RDONLY) != ERROR)
		{
			if (access(FLASH_DISK "./PSX643G.crc", O_RDONLY) == ERROR || !VerifyCheckSum(FLASH_DISK "./PSX643G.bin", FLASH_DISK "/PSX643G.crc"))
			{
				printf("MakeBackupAndCheckSum:found bin file= %s\n", "./PSX643G.bin");
				save();
				return;
			}
		}
		else
		{
			//Once execute here, it means there is no main configuration files existing.
			for (int i = 0; i < 3; i++)
			{
				char szFilePath[64];
				snprintf(szFilePath, NELEMENTS(szFilePath), FLASH_DISK "./PSX643G%d.bin", i);
				if (access(szFilePath, O_RDONLY) == OK)
				{
					printf("MakeBackupAndCheckSum:found bin file= %s\n", szFilePath);
					save();
					return;
				}
			}
		}

		if (access(FLASH_DISK "./PSX643G.json", O_RDONLY) != ERROR)
		{
			if (access(FLASH_DISK "/PSX643G.crc", O_RDONLY) == ERROR || !VerifyCheckSum(FLASH_DISK "./PSX643G.json", FLASH_DISK "./PSX643G.crc"))
			{
				printf("MakeBackupAndCheckSum:found json file= %s\n", "./PSX643G.json");
				save();
				return;
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				char szFilePath[64];
				snprintf(szFilePath, NELEMENTS(szFilePath), FLASH_DISK "./PSX643G%d.json", i);
				if (access(szFilePath, O_RDONLY) == OK)
				{
					printf("MakeBackupAndCheckSum:found json file= %s\n", szFilePath);
					save();
					return;
				}
			}
		}		
	}

	STATUS copyFile(const char* src, const char* dst)
	{
		int fdSrc, fdDst;
		STATUS status = ERROR;

		if ((fdSrc = open(src, O_RDONLY, 0)) != EOF)
		{
			if ((fdDst = creat(dst, O_WRONLY)) != EOF)
			{
				char buf[512];
				int len;
				while ((len = ::read(fdSrc, (u_char*)buf, sizeof(buf))) > 0)
				{
					::write(fdDst, buf, len);
				}
				close(fdDst);
				status = OK;
			}

			close(fdSrc);
		}

		return status;
	}

	void MakeCheckSum(const char* szFilePath, const char* szSumFile)
	{
		int fd;
		int crc = 0;
		if ((fd = open(szFilePath, O_RDONLY, 0)) != EOF)
		{
			int len;
			char buf[512];
			while ((len = ::read(fd, buf, sizeof(buf))) > 0)
			{
				crc = crc32(crc, (u_char*)buf, len);
			}

			close(fd);

			if ((fd = creat(szSumFile, O_WRONLY)) != EOF)
			{
				::write(fd, &crc, sizeof(crc));
				close(fd);
			}
		}
	}

	bool VerifyCheckSum(const char* szFilePath, const char* szSumFile)
	{
		int fd;
		int crc = 0;
		bool result = false;

		if (access(szSumFile, O_RDONLY) == ERROR)
			return true;

		if ((fd = open(szFilePath, O_RDONLY, 0)) != EOF)
		{
			int len;
			char buf[512];
			while ((len = ::read(fd, buf, sizeof(buf))) > 0)
			{
				crc = crc32(crc, (u_char*)buf, len);
			}

			close(fd);

			if ((fd = open(szSumFile, O_RDONLY, 0)) != EOF)
			{
				int readCrc;
				if (::read(fd, &readCrc, sizeof(readCrc)) == sizeof(readCrc) &&
					(crc == readCrc))
				{
					result = true;
				}

				close(fd);
			}
		}
		return result;
	}

	bool save(void)
	{
		//存在bin文件，生成crc文件
		std::ofstream ofs(FLASH_DISK "/PSX643G.bin", std::ios_base::binary);
		if (ofs.is_open())
		{
			CBinaryOstream os(ofs);
			if (SerializeToOstream(os))
			{
				ofs.flush();
				ofs.close();
				MakeCheckSum(FLASH_DISK "./PSX643G.bin", FLASH_DISK "./PSX643G.crc");
				for (int i = 0; i < 3; i++)
				{
					char szFilePath[64];
					snprintf(szFilePath, NELEMENTS(szFilePath), FLASH_DISK "./PSX643G%d.bin", i);
					if (copyFile(FLASH_DISK "./PSX643G.bin", szFilePath) == OK)
					{
						char szSumFile[64];
						snprintf(szSumFile, NELEMENTS(szSumFile), FLASH_DISK "./PSX643G%d.crc", i);
						MakeCheckSum(szFilePath, szSumFile);
					}
				}
				return true;
			}
		}

		//存在json文件
		if (access(FLASH_DISK "./PSX643G.json", 0) != ERROR)
		{
			COstreamOnJSON os;
			if (SerializeToOstream(os))
			{
				if (os.save(FLASH_DISK "./PSX643G.json"))
				{
					MakeCheckSum(FLASH_DISK "./PSX643G.json", FLASH_DISK "./PSX643G.crc");

					for (int i = 0; i < 3; i++)
					{
						char szFilePath[64];
						snprintf(szFilePath, NELEMENTS(szFilePath), FLASH_DISK "./PSX643G%d.json", i);
						if (copyFile(FLASH_DISK "./PSX643G.json", szFilePath) == OK)
						{
							char szSumFile[64];
							snprintf(szSumFile, NELEMENTS(szSumFile), FLASH_DISK "./PSX643G%d.crc", i);
							MakeCheckSum(szFilePath, szSumFile);
						}
					}

					return true;
				}
			}
		}
		//in case PSX643G.json is missing look
		for (int i = 0; i < 3; i++)
		{
			char szFilePath[64];
			snprintf(szFilePath, NELEMENTS(szFilePath), FLASH_DISK "./PSX643G%d.json", i);
			if (access(szFilePath, O_RDONLY) == OK)
			{
				COstreamOnJSON os;
				printf("save json file(Line 293): %s\n", szFilePath);
				if (SerializeToOstream(os))
				{
					if (os.save(FLASH_DISK "./PSX643G.json"))
					{
						MakeCheckSum(FLASH_DISK "./PSX643G.json", FLASH_DISK "./PSX643G.crc");

						for (i = 0; i < 3; i++)
						{
							// char szFilePath[64];
							snprintf(szFilePath, NELEMENTS(szFilePath), FLASH_DISK "./PSX643G%d.json", i);
							if (copyFile(FLASH_DISK "./PSX643G.json", szFilePath) == OK)
							{
								char szSumFile[64];
								snprintf(szSumFile, NELEMENTS(szSumFile), FLASH_DISK "./PSX643G%d.crc", i);
								MakeCheckSum(szFilePath, szSumFile);
							}
						}

						return true;
					}
				}
			}
		}

		return false;
	}

	CSettings()
	{
	}

	~CSettings()
	{
		Dispose();
	}

	class _netConf : public Serializable<_netConf>
	{
	public:
		enum
		{
			defRtNone = 0,
			defRtEi0,
			defRtEi1,
			defRtDm0,
			defRtDm1,
			defRtDm2,
			defRtDm3,
		};

		enum
		{
			useDnsNone = 0,
			useDnsStatic,
			useDnsAuto
		};

		enum
		{
			ifDisabled = 0,
			ifDhcp,
			ifStaticIP,
		};

		class _ifConf : public Serializable<_ifConf>
		{
		public:
			int ipConf;
			std::string ip;
			std::string netmask;
			std::string gateway;
			std::string mac;

			_ifConf()
			{
				ipConf = ifDhcp;
			}

			BEGIN_MEMBER_MAP(_ifConf)
				MEMBER(1, ipConf)
				MEMBER(2, mac)
				MEMBER(3 | MemberDescriptor::HexadecaneTag, ip)
				MEMBER(4 | MemberDescriptor::HexadecaneTag, netmask)
				MEMBER(5 | MemberDescriptor::HexadecaneTag, gateway)
			END_MEMBER_MAP()
		};

		std::string stationName; //added on 2019.09.26
		int stationType;		 //0: PSX643G 1U, 1: PSX643G-S DIN Rail
		int useDns;
		std::string dnsIp;
		int defroute;
		_ifConf ei0Conf;
		_ifConf ei1Conf;
		_ifConf dm0Conf;
		_ifConf dm1Conf;
		_ifConf dm2Conf;
		_ifConf dm3Conf;
		int calibrationMode;
		int calibrationProtocol;
		std::string calibrationSerialPortGuid;
		std::vector<std::string> calibrationIP;
		int calibrationPort;

		BEGIN_MEMBER_MAP(_netConf)
			MEMBER(1, useDns)
			MEMBER(2, dnsIp)
			MEMBER(3, defroute)
			MEMBER_EX(4, ei0Conf)
			MEMBER_EX(5, ei1Conf)
			MEMBER_EX(6, dm0Conf)
			MEMBER_EX(7, dm1Conf)
			MEMBER_EX(8, dm2Conf)
			MEMBER_EX(9, dm3Conf)
			MEMBER(10, stationName)
			MEMBER(11, stationType)
			MEMBER(12, calibrationMode)
			MEMBER(13, calibrationProtocol)
			MEMBER(14, calibrationSerialPortGuid)
			MEMBER(15, calibrationIP)
			MEMBER(16, calibrationPort)
		END_MEMBER_MAP()

		_netConf(void)
		{
			defroute = defRtDm0;
			useDns = useDnsAuto;
			stationName = "出厂默认";
			stationType = 0;
			ei0Conf.ipConf = 2;
			ei0Conf.ip = "192.168.1.100";
			ei0Conf.netmask = "255.255.255.0";
			ei0Conf.gateway = "192.168.1.1";
			ei1Conf.ipConf = 2;
			ei1Conf.ip = "192.168.10.100";
			ei1Conf.netmask = "255.255.255.0";
			ei1Conf.gateway = "192.168.10.1";
			dm0Conf.ipConf = 0;
			dm1Conf.ipConf = 0;
			dm2Conf.ipConf = 0;
			dm3Conf.ipConf = 0;
			useDns = 2;
			dnsIp = "218.2.135.1";
			defroute = 2;
		}
	};

	class _localConf : public Serializable<_localConf>
	{
	public:
		_localConf()
		{
		}

		~_localConf()
		{
			Dispose();
		}

		class _portConf
			: public CObjectBase,
			public Serializable<_portConf>
		{
		public:
			std::string comment;
			std::string Guid;

			_portConf()
			{
			}

			virtual ~_portConf()
			{
				Dispose();
			}

			DECLARE_DYNAMIC(_portConf, "_portConf")
			DECLARE_SERIAL_CLONE(_portConf)

			BEGIN_MEMBER_MAP(_portConf)
				MEMBER(1, Guid)
				MEMBER(2, comment)
			END_MEMBER_MAP()
		};

		class _serialConf : public _portConf
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

			BEGIN_MEMBER_MAP(_serialConf)
				MEMBER(1, Guid)
				MEMBER(2, comment)
				MEMBER(3, port)
				MEMBER(4, baudrate)
				MEMBER(5, parity)
				MEMBER(6, dataBits)
				MEMBER(7, stopBits)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_serialConf, "_serialConf")
			DECLARE_SERIAL_CLONE(_serialConf)
		};

		class _tcpIpConf : public _portConf
		{
		public:
			std::string ip;
			int port;
			int mode; //see PortModeItem
			enum PortModeItem
			{
				InvalidPort,
				Iec104Master,
				Iec103Master,
				Iec104Slave,
				Iec103Slave,
				Modbus_TCP_Standard_Master,
				Modbus_TCP_Transparent_Master,
				Modbus_TCP_Standard_Slave,
				Modbus_TCP_Transparent_Slave
			};
			_tcpIpConf()
			{
				port = 0;
				mode = InvalidPort;
			}

			BEGIN_MEMBER_MAP(_tcpIpConf)
				MEMBER(1, Guid)
				MEMBER(2, comment)
				MEMBER(3, ip)
				MEMBER(4, port)
				MEMBER(5, mode)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_tcpIpConf, "_tcpIpConf")
			DECLARE_SERIAL_CLONE(_tcpIpConf)
		};

		class _diConf : public _portConf
		{
		public:
			int innerId;
			int dioIndex; //0,1,2,3: DI PD.4~PD.7
			int returnInnnerId;
			BEGIN_MEMBER_MAP(_diConf)
				MEMBER(1, Guid)
				MEMBER(2, comment)
				MEMBER(3, innerId)
				MEMBER(4, dioIndex)
				MEMBER(5, returnInnnerId)
				// CHAIN_MEMBER_MAP(_portConf)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_diConf, "_diConf")
			DECLARE_SERIAL_CLONE(_diConf)

			_diConf()
			{
				innerId = 0;
				// debounceTime = 20;
				dioIndex = 0;
			}
			virtual ~_diConf()
			{
				Dispose(); //?
			}
		};

		class _doConf : public _portConf
		{
		public:
			int innerId;
			int dioIndex;	//0,1,2,3: PD.0~PD.3
			int outputMode; //1: pulse(holdTime); 0: level
			int holdTime;
			int logicType; //0:no relation with Id1~Id3; 1:Id1+Id2+...; 2:Id1&Id2&...; 3:Id1(value)>high or Id1(value)<low
			float low;
			float high;
			std::vector<int> in_innerId;
			// int in_innerId1;
			// int in_innerId2;
			// int in_innerId3;

			BEGIN_MEMBER_MAP(_doConf)
				MEMBER(1, Guid)
				MEMBER(2, comment)
				MEMBER(3, innerId)
				MEMBER(4, dioIndex)
				MEMBER(5, outputMode)
				MEMBER(6, holdTime)
				MEMBER(7, logicType)
				MEMBER(8, low)
				MEMBER(9, high)
				MEMBER(10, in_innerId)
				// MEMBER(9, in_innerId2)
				// MEMBER(10, in_innerId3)
				// CHAIN_MEMBER_MAP(_portConf)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_doConf, "_doConf")
			DECLARE_SERIAL_CLONE(_doConf)

			_doConf()
			{
				innerId = 0;
				holdTime = 600;
				logicType = 0;
				low = FLT_MIN;
				high = FLT_MAX;
				// in_innerId1 = 0;
				// in_innerId2 = 0;
				// in_innerId3 = 0;
			}
			virtual ~_doConf()
			{
				Dispose(); //?
			}
		};

		std::vector<CObjectBase*> portsConf;

		BEGIN_MEMBER_MAP(_localConf)
			NAMED_MEMBER_EX(1, "portsConf\0portConf\0", portsConf)
		END_MEMBER_MAP()
	};

	class _serviceConf : public Serializable<_serviceConf>
	{
	public:
		class _wwwConf : public Serializable<_wwwConf>
		{
		public:
			int enabled;
			std::string home;
			int port;

			_wwwConf()
			{
				enabled = 0;
				port = 80;
				home = "/etc/www";
			}

			BEGIN_MEMBER_MAP(_wwwConf)
				MEMBER(1, enabled)
				MEMBER(2, home)
				MEMBER(3, port)
			END_MEMBER_MAP()
		};

		class _ftpdConf : public Serializable<_ftpdConf>
		{
		public:
			int enabled;
			std::string root;
			int port;

			_ftpdConf()
			{
				enabled = 1;
				root = "/";
				port = 21;
			}

			BEGIN_MEMBER_MAP(_ftpdConf)
				MEMBER(1, enabled)
				MEMBER(2, root)
				MEMBER(3, port)
			END_MEMBER_MAP()
		};

		class _telnetdConf : public Serializable<_telnetdConf>
		{
		public:
			int enabled;
			int port;

			_telnetdConf()
			{
				enabled = 1;
				port = 23;
			}

			BEGIN_MEMBER_MAP(_telnetdConf)
				MEMBER(1, enabled)
				MEMBER(2, port)
			END_MEMBER_MAP()
		};

		class _cleanupConf : public Serializable<_cleanupConf>
		{
		public:
			int enabled;
			int timePoint;
			int dataRetain;
			int diskLowThreshold;

			BEGIN_MEMBER_MAP(_cleanupConf)
				MEMBER(1, enabled)
				MEMBER(2, timePoint)
				MEMBER(3, dataRetain)
				MEMBER(4, diskLowThreshold)
			END_MEMBER_MAP()

			DECLARE_SERIAL_CLONE(_cleanupConf)

			_cleanupConf()
			{
				enabled = TRUE;
				timePoint = 0;
				dataRetain = 30;
				diskLowThreshold = 40;
			}
		};

		class _backupConf : public Serializable<_backupConf>
		{
		public:
			int enabled;
			int startTime;
			int dataRetain;
			int extDataRetain;

			_backupConf()
			{
				enabled = TRUE;
				startTime = 4;
				dataRetain = 7;
				extDataRetain = 30;
			}

			BEGIN_MEMBER_MAP(_backupConf)
				MEMBER(1, enabled)
				MEMBER(2, startTime)
				MEMBER(3, dataRetain)
				MEMBER(4, extDataRetain)
			END_MEMBER_MAP()
		};

		class _syslogConf : public Serializable<_syslogConf>
		{
		public:
			int enabled;
			std::string ip;
			int port;
			BEGIN_MEMBER_MAP(_syslogConf)
				MEMBER(1, enabled)
				MEMBER(2, ip)
				MEMBER(3, port)
			END_MEMBER_MAP()

			_syslogConf()
			{
				enabled = FALSE;
				port = 514;
			}
		};

		class _gpsTimeConf : public Serializable<_gpsTimeConf>
		{
		public:
			int enabled;
			int ppsMode;
			int protocol;
			std::string portGuid;
			std::string ppsPortGuid;

			BEGIN_MEMBER_MAP(_gpsTimeConf)
				MEMBER(1, enabled)
				MEMBER(2, ppsMode)
				MEMBER(3, protocol)
				MEMBER(4, portGuid)
				MEMBER(5, ppsPortGuid)
			END_MEMBER_MAP()

			enum
			{
				PPSM_NONE,
				PPSM_RAISE,
				PPSM_FALLING,
			};

			enum
			{
				PROT_NONE,
				PROT_NMEA,
			};
		};

		class _sntpcConf : public Serializable<_sntpcConf>
		{
		public:
			int enabled;
			std::string ip;
			int port;
			int period;

			BEGIN_MEMBER_MAP(_sntpcConf)
				MEMBER(1, enabled)
				MEMBER(2, ip)
				MEMBER(3, port)
				MEMBER(4, period)
			END_MEMBER_MAP()
		};

		class _sntpsConf : public Serializable<_sntpsConf>
		{
		public:
			int enabled;
			int mode;	  //0:passive; 1:active
			int netIndex; //1-6
			int port;

			BEGIN_MEMBER_MAP(_sntpsConf)
				MEMBER(1, enabled)
				MEMBER(2, mode)
				MEMBER(3, netIndex)
				MEMBER(4, port)
			END_MEMBER_MAP()
		};

		class _mqttClientConf : public Serializable<_mqttClientConf>
		{
		public:
			class _controlItem : public Serializable<_controlItem>
			{
			public:
				std::string name;
				int innerId;
				int divider;
				BEGIN_MEMBER_MAP(_controlItem)
					MEMBER(1, name)
					MEMBER(2, innerId)
					MEMBER(3, divider)
				END_MEMBER_MAP()
			};
			int enabled;
			std::string host;
			int port;
			int keepalive;
			std::string serialNum;
			std::string productKey;
			std::string productSecret;
			std::string deviceName;
			std::string deviceSecret;
			std::string userName;
			std::string password;
			std::string clientId;
			int hostType; //0, masqitto mqtt broker; 1: Aliyun mqtt broker; 2: thingsboard mqtt broker; 3: Nanjing South Railway Station Taxi
			std::vector<_controlItem*> controlItems;

			BEGIN_MEMBER_MAP(_mqttClientConf)
				MEMBER(1, enabled)
				MEMBER(2, host)
				MEMBER(3, port)
				MEMBER(4, keepalive)
				MEMBER(5, serialNum)
				MEMBER(6, productKey)
				MEMBER(7, productSecret)
				MEMBER(8, deviceName)
				MEMBER(9, deviceSecret)
				MEMBER(10, userName)
				MEMBER(11, password)
				MEMBER(12, clientId)
				MEMBER(13, hostType)
				NAMED_MEMBER_EX(14, "controlItems\0controlItem\0", controlItems)
			END_MEMBER_MAP()

			_mqttClientConf()
			{
				enabled = 0;
				port = 1883;
				keepalive = 60;
				hostType = 0;
			}
			~_mqttClientConf()
			{
				Dispose();
			}
		};

		class _mqttRTDataConf : public Serializable<_mqttRTDataConf>
		{
		public:
			int enabled;
			std::string host;
			int port;
			int keepalive;
			std::string userName;
			std::string password;

			BEGIN_MEMBER_MAP(_mqttRTDataConf)
				MEMBER(1, enabled)
				MEMBER(2, host)
				MEMBER(3, port)
				MEMBER(4, keepalive)
				MEMBER(5, userName)
				MEMBER(6, password)
			END_MEMBER_MAP()

			_mqttRTDataConf()
			{
				enabled = 0;
				port = 1903;
				keepalive = 60;
			}
			~_mqttRTDataConf()
			{
				Dispose();
			}
		};
		
		_wwwConf wwwConf;
		_ftpdConf ftpdConf;
		_telnetdConf telnetdConf;
		_cleanupConf cleanupConf;
		_backupConf backupConf;
		_syslogConf syslogConf;
		_gpsTimeConf gpsTimeConf;
		_sntpcConf sntpcConf;
		_mqttClientConf mqttClientConf;
		_mqttRTDataConf mqttRTDataConf;
		_sntpsConf sntpsConf;
		// _httpConf httpConf;
		// _mqttAliyunClientConf mqttAliyunClientConf;

		BEGIN_MEMBER_MAP(_serviceConf)
			MEMBER_EX(1, wwwConf)
			MEMBER_EX(2, ftpdConf)
			MEMBER_EX(3, telnetdConf)
			MEMBER_EX(4, cleanupConf)
			MEMBER_EX(5, backupConf)
			MEMBER_EX(6, syslogConf)
			MEMBER_EX(7, gpsTimeConf)
			MEMBER_EX(8, sntpcConf)
			MEMBER_EX(9, mqttClientConf)
			MEMBER_EX(10, mqttRTDataConf)
			MEMBER_EX(11, sntpsConf)
		END_MEMBER_MAP()
	};

	class _masterConf : public Serializable<_masterConf>
	{
	public:
		_masterConf()
		{
		}

		~_masterConf()
		{
			Dispose();
		}
		enum
		{
			dtInt,
			dtReal,
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
		class _serviceConf
			: public Serializable<_serviceConf>,
			public CObjectBase
		{
		public:
			_serviceConf()
			{
				samplingPeriod = 0;
			}

			class _device : public Serializable<_device>
			{
			public:
				std::string portGuid;
				int deviceAddress; //采集设备地址 for Modbus, not used for 103net and 104
				int unitStartAddr; //装置起始地址 for 103 and 104
				int unitNum;	   //装置个数 for 103 and 104
				int tries;
				int maxErrors;
				int innerId; //used for serial communication error flag
				std::vector<char> outData; 	//used for DL/T645
				_device()
				{
					deviceAddress = 0;
					unitStartAddr = 0;
					unitNum = 0;
					tries = 5;
					maxErrors = 5;
					innerId = 0;
				}

				class _sampling : public Serializable<_sampling>
				{
				public:
					int start;
					int stop;
					int delay;

					_sampling()
					{
						start = 0;
						stop = 0;
						delay = 500;
					}

					BEGIN_MEMBER_MAP(_sampling)
						MEMBER(1, start)
						MEMBER(2, stop)
						MEMBER(3, delay)
					END_MEMBER_MAP()
				};

				_sampling sampling;

				BEGIN_MEMBER_MAP(_device)
					MEMBER(1, portGuid)
					MEMBER(2, tries)
					MEMBER(3, maxErrors)
					MEMBER(4, deviceAddress)
					MEMBER(5, unitStartAddr)
					MEMBER(6, unitNum)
					MEMBER(7, innerId)
					MEMBER_EX(8, sampling)
					MEMBER(9, outData)
				END_MEMBER_MAP()
				DECLARE_SERIAL_CLONE(_device)
			};

			DECLARE_DYNAMIC(_serviceConf, "master.serviceConf")

			BEGIN_MEMBER_MAP(_serviceConf)
				MEMBER(201, samplingPeriod)
				MEMBER_EX(202, device)
			END_MEMBER_MAP()

			int samplingPeriod;
			_device device;
		};

		class _modbusService : public _serviceConf
		{
		public:
			_modbusService()
			{
			}

			virtual ~_modbusService()
			{
				Dispose();
			}

			class _cmdOut : public Serializable<_cmdOut>
			{
			public:
				int functionCode;
				int registerStartAddr;
				int byteNum;
				std::vector<char> outData;

				_cmdOut()
				{
					functionCode = 0;
					registerStartAddr = 0;
					byteNum = 0;
				}

				BEGIN_MEMBER_MAP(_cmdOut)
					MEMBER(2, functionCode)
					MEMBER(3 | MemberDescriptor::HexadecaneTag, registerStartAddr)
					MEMBER(4, byteNum)
					MEMBER(5, outData)
				END_MEMBER_MAP()
			};

			class _dataParse : public Serializable<_dataParse>
			{
			public:
				_dataParse()
				{
					offset = 0;
					len = 4;
					innerId = 0;
					coef = 1;
					factor = 1;
					dataType = dtInt;
					byteOrder = 0;
					deviation = 0;
					interval = 0.2;
				}
				std::string name;
				int offset;
				int len;
				int innerId;
				int coef;
				int dataType;
				int factor;
				int byteOrder;
				int deviation; //sample value - deviation = database value
				float interval;
				std::string js;
				std::vector<int> h2cinnerIdList; //holding register to coil registers, used with dtRegTypeHolding2Coil flag
				std::vector<std::string> h2cNameList;
				BEGIN_MEMBER_MAP(_dataParse)
					MEMBER(1, name)
					MEMBER(2, offset)
					MEMBER(3, len)
					MEMBER(4, innerId)
					MEMBER(5, coef)
					MEMBER(7 | MemberDescriptor::HexadecaneTag, dataType)
					MEMBER(8, factor)
					MEMBER(9 | MemberDescriptor::HexadecaneTag, byteOrder)
					MEMBER(10, deviation)
					MEMBER(11, interval)
					MEMBER(12, js)
					MEMBER(13, h2cinnerIdList)
					MEMBER(14, h2cNameList)
				END_MEMBER_MAP()
			};

			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				std::string name;
				int innerId;
				int address;
				int functionCode;
				int dataType; //data type
				int coef;
				int factor;

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(1, name)
					MEMBER(2, innerId)
					MEMBER(3, address)
					MEMBER(4, functionCode)
					MEMBER(5, dataType)
					MEMBER(6, coef)
					MEMBER(7, factor)
				END_MEMBER_MAP()

				DECLARE_SERIAL_CLONE(_itemEntry)
				_itemEntry()
				{
					innerId = 0;
					address = 0;
					functionCode = 0;
				}
			};

			std::string manufacture;
			std::string deviceName;
			_cmdOut cmdOut;
			std::vector<_dataParse*> dataList;
			std::vector<_itemEntry*> controlItems;

			BEGIN_MEMBER_MAP(_modbusService)
				CHAIN_MEMBER_MAP(_serviceConf)
				MEMBER(100, manufacture)
				MEMBER(101, deviceName)
				MEMBER_EX(102, cmdOut)
				MEMBER_EX(103, dataList)
				MEMBER_EX(104, controlItems)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_modbusService, "master.modbusService")
		};

		class _dlt645Service : public _serviceConf
		{
		public:
			_dlt645Service()
			{
			}

			virtual ~_dlt645Service()
			{
				Dispose();
			}

			class _cmdOut : public Serializable<_cmdOut>
			{
			public:
				int functionCode;
				int registerStartAddr;
				int byteNum;
				std::vector<char> outData;

				_cmdOut()
				{
					functionCode = 0;
					registerStartAddr = 0;
					byteNum = 0;
				}

				BEGIN_MEMBER_MAP(_cmdOut)
					MEMBER(2, functionCode)
					MEMBER(3 | MemberDescriptor::HexadecaneTag, registerStartAddr)
					MEMBER(4, byteNum)
					MEMBER(5, outData)
				END_MEMBER_MAP()
			};

			class _dataParse : public Serializable<_dataParse>
			{
			public:
				_dataParse()
				{
					innerId = 0;
					coef = 1;
					ratio = 1;
					interval = 0.5;
				}

				std::string name;
				// int offset;
				int len;
				int innerId;
				int coef;
				// int dataType;
				int ratio;
				// int byteOrder;
				// int deviation;
				float interval;
				std::vector<char> outData;

				BEGIN_MEMBER_MAP(_dataParse)
					MEMBER(1, name)
					// MEMBER(2, offset)
					MEMBER(2, innerId)
					MEMBER(3, coef)
					// MEMBER(7 | MemberDescriptor::HexadecaneTag, dataType)
					MEMBER(4, ratio)
					// MEMBER(9 | MemberDescriptor::HexadecaneTag, byteOrder)
					// MEMBER(10, deviation)
					MEMBER(5, interval)
					MEMBER(6, len)
					MEMBER(7, outData)
				END_MEMBER_MAP()
			};

			std::string manufacture;
			_cmdOut cmdOut;
			std::string meterAddress; //2021.03.25为了不改变modbus那边的地址处理
			std::vector<_dataParse*> dataList;

			BEGIN_MEMBER_MAP(_dlt645Service)
				CHAIN_MEMBER_MAP(_serviceConf)
				MEMBER(100, manufacture)
				MEMBER_EX(101, cmdOut)
				MEMBER(102, meterAddress)
				MEMBER_EX(103, dataList)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_dlt645Service, "master.dlt645Service")
		};

		class _iec104Service : public _serviceConf
		{
		public:
			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				int innerId;
				int address;
				int coef;
				int factor;
				int objType; // "objType":45 or 46 single point control or double point control

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(1, innerId)
					MEMBER(2, address)
					MEMBER(3, coef)
					MEMBER(4, factor)
					MEMBER(5, objType)
				END_MEMBER_MAP()

				DECLARE_SERIAL_CLONE(_itemEntry)
				_itemEntry()
				{
					innerId = 0;
					address = 0;
					coef = 1;
					factor = 1;
					objType = 0;
				}
			};
			class _mapperConf : public Serializable<_mapperConf>
			{
			public:
				int innerId;
				int address;
				int coef;
				int factor;
				int objType;
				unsigned int channelType; //channelType>>16 3U0==2; Combined TeleSignal==1
				float low;
				float high;
				int in_innerId1;
				int in_innerId2;
				std::string name;
				// struct chnType {
				// 	unsigned char validInChannelCnt:8;
				// 	unsigned char inCharnnelType:8;
				// 	unsigned char functionCode:8;	//1:Combined TeleSignal; 2:3U0 Warning
				// 	unsigned char res:8;
				// }

				_mapperConf()
				{
					low = -FLT_MAX; //5.8774717541114375398436826861112e-39f;	//DBL_MIN;
					high = FLT_MAX; //3.3928236692093846346337460743177e+38f;
				}

				BEGIN_MEMBER_MAP(_mapperConf)
					MEMBER(1, innerId)
					MEMBER(2, address)
					MEMBER(3, coef)
					MEMBER(4, factor)
					MEMBER(5, objType)
					MEMBER(6, channelType)
					MEMBER(7, low)
					MEMBER(8, high)
					MEMBER(9, in_innerId1)
					MEMBER(10, in_innerId2)
					MEMBER(11, name)
				END_MEMBER_MAP()
			};

			int erReport2Telesignaling; //故障报告自动产生遥信点
			int erDelaySecond;			//故障报告自动产生遥信点延时清零
			int ca;						//站地址
			int innerId;
			std::string deviceName;
			int recordWaveMode; //0: 0x6B03 summon; 1: 0x6B02~0x6B...
			std::vector<_itemEntry*> items;
			std::vector<_mapperConf*> mappers;

			BEGIN_MEMBER_MAP(_iec104Service)
				CHAIN_MEMBER_MAP(_serviceConf)
				MEMBER(101, erReport2Telesignaling)
				MEMBER(102, ca)
				MEMBER(103, innerId)
				MEMBER(104, deviceName)
				MEMBER(105, recordWaveMode)
				MEMBER(106, erDelaySecond)
				NAMED_MEMBER_EX(107, "items\0item\0", items)
				NAMED_MEMBER_EX(108, "mappers\0mapper\0", mappers)
			END_MEMBER_MAP()
			DECLARE_DYNAMIC(_iec104Service, "master.iec104Service")
			DECLARE_SERIAL_CLONE(_iec104Service)
			_iec104Service()
			{
				ca = 1;
				innerId = 0;
				recordWaveMode = 0;
			}
		};

		class _iec103netService : public _serviceConf
		{
		public:
			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				std::string name;
				int innerId;
				int address; //group = (itemEntry->address) >>8; item = (itemEntry->address) & 0xFF;
				int coef;
				int factor;
				int objType;
				float interval; //步长

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(1, name)
					MEMBER(2, innerId)
					MEMBER(3, address)
					MEMBER(4, coef)
					MEMBER(5, factor)
					MEMBER(6, objType)
					MEMBER(7, interval)
				END_MEMBER_MAP()

				DECLARE_SERIAL_CLONE(_itemEntry)
				_itemEntry()
				{
					innerId = 0;
					address = 0;
					coef = 1;
					factor = 1;
					objType = 56;
					interval = 0.2;
				}
			};

			class _clientConf : public Serializable<_clientConf>
			{
			public:
				std::string ip;
				int deviceAddress;
				int unitStartAddr;
				std::string deviceName;
				int ca;
				float interval;
				int settingCnt;
				int innerId; //used for 103net communication error flag
				std::vector<_itemEntry*> items;

				BEGIN_MEMBER_MAP(_clientConf)
					MEMBER(101, ip)
					MEMBER(102, deviceAddress)
					MEMBER(103, unitStartAddr)
					MEMBER(104, deviceName)
					MEMBER(105, ca)
					MEMBER(106, interval)
					MEMBER(107, settingCnt)
					MEMBER(108, innerId)
					NAMED_MEMBER_EX(109, "items\0item\0", items)
				END_MEMBER_MAP()

				DECLARE_SERIAL_CLONE(_clientConf)

				_clientConf()
				{
					// oa = 0;
					ca = 1;
					interval = 10;
					settingCnt = 15;
					deviceAddress = 0;
					unitStartAddr = 0;
					innerId = 0;
				}
			};

			std::vector<_clientConf*> clients;

			BEGIN_MEMBER_MAP(_iec103netService)
				CHAIN_MEMBER_MAP(_serviceConf)
				NAMED_MEMBER_EX(101, "clients\0client\0", clients)
			END_MEMBER_MAP()
			DECLARE_DYNAMIC(_iec103netService, "master.iec103netService")
			DECLARE_SERIAL_CLONE(_iec103netService)
			_iec103netService()
			{
			}
		};

		class _voltRegulatorService : public _serviceConf
		{
		public:
			_voltRegulatorService()
			{
			}

			virtual ~_voltRegulatorService()
			{
				Dispose();
			}

			class _cmdOut : public Serializable<_cmdOut>
			{
			public:
				int functionCode;
				int registerStartAddr;
				int byteNum;
				_cmdOut()
				{
					functionCode = 0;
					registerStartAddr = 0;
					byteNum = 0;
				}

				BEGIN_MEMBER_MAP(_cmdOut)
					MEMBER(2, functionCode)
					MEMBER(3 | MemberDescriptor::HexadecaneTag, registerStartAddr)
					MEMBER(4, byteNum)
				END_MEMBER_MAP()
			};

			class _dataParse : public Serializable<_dataParse>
			{
			public:
				_dataParse()
				{
					offset = 0;
					len = 4;
					innerId = 0;
					factor = 1; // = divider
					coef = 1;
					dataType = dtInt;
					byteOrder = 0;
					deviation = 0;
				}

				// enum
				// {
				// 	dtInt,
				// 	dtReal,
				// 	dtCustom = 0x80,
				// 	dtJS = 0xA0,
				// 	dtBCD = 0x100,
				// 	dtSigned = 0x200,
				// 	dtLittleEndian = 0x400,
				// 	dtByteOrder = 0x800,
				// 	dtBitReverse = 0x1000,
				// 	dtBit = 0x2000,
				// 	dtRegTypeMask = (0x7 << 16),	//Modbus Register Type Mask
				// 	dtRegTypeCoil = (1 << 16),		//Modbus Register BIT type
				// 	dtRegTypeHolding = (2 << 16),	//Modbus Register SHORT type
				// 	dtRegTypeHolding2Coil = (4 << 16)	//Modbus Register SHORT type to BIT type
				// };

				std::string name;
				int offset;
				int len;
				int innerId;
				int factor;
				int dataType;
				int coef;
				int byteOrder;
				int deviation;
				float interval;

				BEGIN_MEMBER_MAP(_dataParse)
					MEMBER(1, name)
					MEMBER(2, offset)
					MEMBER(3, len)
					MEMBER(4, innerId)
					MEMBER(5, factor)
					MEMBER(7 | MemberDescriptor::HexadecaneTag, dataType)
					MEMBER(8, coef)
					MEMBER(9 | MemberDescriptor::HexadecaneTag, byteOrder)
					MEMBER(10, deviation)
					MEMBER(11, interval)
				END_MEMBER_MAP()
			};

			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				int innerId;
				int address;
				int coef;
				int factor;
				int dataType; //data type
				int functionCode;

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(1, innerId)
					MEMBER(2, address)
					MEMBER(3, coef)
					MEMBER(4, factor)
					MEMBER(5, dataType)
					MEMBER(6, functionCode)
				END_MEMBER_MAP()

				DECLARE_SERIAL_CLONE(_itemEntry)
				_itemEntry()
				{
					innerId = 0;
					address = 0;
					coef = 1;
					factor = 1;
					dataType = 0;
					functionCode = 0;
				}
			};

			std::string manufacture;
			_cmdOut cmdOut;
			std::vector<_dataParse*> dataList;
			std::vector<_itemEntry*> controlItems;

			BEGIN_MEMBER_MAP(_voltRegulatorService)
				CHAIN_MEMBER_MAP(_serviceConf)
				MEMBER(100, manufacture)
				MEMBER_EX(102, cmdOut)
				MEMBER_EX(103, dataList)
				MEMBER_EX(104, controlItems)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_voltRegulatorService, "master.voltRegulatorService")
		};

		std::vector<CObjectBase*> services;

		BEGIN_MEMBER_MAP(_masterConf)
			NAMED_MEMBER_EX(2, "services\0service\0", services)
		END_MEMBER_MAP()
	};

	class _slaveConf : public Serializable<_slaveConf>
	{
	public:
		_slaveConf()
		{
		}

		~_slaveConf()
		{
			Dispose();
		}
		enum
		{
			dtInt,
			dtReal,
			dtCustom = 0x80,
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
		class _serviceConf
			: public Serializable<_serviceConf>,
			public CObjectBase
		{
		public:
			DECLARE_DYNAMIC(_serviceConf, "slave.serviceConf")
			BEGIN_MEMBER_MAP(_serviceConf)

			END_MEMBER_MAP()
		};

		class _modbusService : public _serviceConf
		{
		public:
			int enabled;
			std::string name;
			USHORT address; //Modbus Slave Device Address
			int mode;		//0: RTU; 1: ASCII
			std::string portGuid;
			// unsigned short modbusControlStartAddr;
			// unsigned short modbusControlAddrNum;

			class _dataEncode : public Serializable<_dataEncode>
			{
			public:
				int innerId;
				int len;
				USHORT regAddr;
				int dataType; //通过数据类型来区分是bit寄存器还是byte寄存器 dtRegTypeCoil, dtRegTypeHolding
				int byteOrder;
				int factor;
				int coef;
				std::string name;
				std::string deviceName;
				BEGIN_MEMBER_MAP(_dataEncode)
					MEMBER(1, innerId)
					MEMBER(3, len)
					MEMBER(4, regAddr)
					MEMBER(5, dataType)
					MEMBER(6, byteOrder)
					MEMBER(7, factor)
					MEMBER(8, coef)
					MEMBER(9, name)
					MEMBER(10, deviceName)
				END_MEMBER_MAP()

				_dataEncode()
				{
					dataType = dtReal;
					byteOrder = dtByteOrder;
					factor = 1;
					coef = 1;
				}
			};

			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				std::string name;
				std::string deviceName;
				int innerId;
				int address;
				int functionCode;
				int dataType; //data type
				int coef;
				int factor;

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(1, innerId)
					MEMBER(2, address)
					MEMBER(3, functionCode)
					MEMBER(4, dataType)
					MEMBER(5, coef)
					MEMBER(6, factor)
					MEMBER(7, name)
					MEMBER(8, deviceName)
				END_MEMBER_MAP()

				DECLARE_SERIAL_CLONE(_itemEntry)
				_itemEntry()
				{
					innerId = 0;
					address = 0;
					functionCode = 0;
				}
			};

			std::vector<_dataEncode*> dataList;
			std::vector<_itemEntry*> controlItems;

			BEGIN_MEMBER_MAP(_modbusService)
				CHAIN_MEMBER_MAP(_serviceConf)
				MEMBER(201, enabled)
				MEMBER(202, name)
				MEMBER(203, address)
				MEMBER(204, mode)
				MEMBER(205, portGuid)
				MEMBER_EX(206, dataList)
				MEMBER_EX(207, controlItems)
				// MEMBER(206, modbusControlAddrNum)
				//NAMED_MEMBER_EX(210, "dataLists\0dataList\0", dataList)

				//	NAMED_MEMBER_EX(11, "teleSignalInnerIds\0teleSignalInnerId\0", teleSignalInnerIdList)
			END_MEMBER_MAP()

			DECLARE_DYNAMIC(_modbusService, "slave.modbusService")

			_modbusService()
			{
				enabled = 0;
				address = 0;
				mode = 0;
				//				modbusControlStartAddr = 0;
				//				modbusControlAddrNum = 0;
			}
		};

		class _iec104Service : public _serviceConf
		{
		public:
			enum
			{
				dtReal = 0,
				dtInverse = 0x1000,
				dtNormalized = 0x02, //normalized value 没有用上
			};

			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				std::string name;
				int innerId;
				int dataType;
				std::string deviceName;
				int unitStartAddr;
				int address;
				float delta;

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(51, name)
					MEMBER(52, innerId)
					MEMBER(53, dataType)
					MEMBER(54, deviceName)
					MEMBER(55, unitStartAddr)
					MEMBER(56, address)
					MEMBER(57, delta)
				END_MEMBER_MAP()

				_itemEntry()
				{
					innerId = 0;
					dataType = dtReal;
					delta = 0.0;
				}
			};

			class _teleSignalling : public Serializable<_teleSignalling>
			{
			public:
				int address;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleSignalling)
					MEMBER(1, address)
					NAMED_MEMBER_EX(2, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			class _teleMetry : public Serializable<_teleMetry>
			{
			public:
				int address;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleMetry)
					MEMBER(1, address)
					NAMED_MEMBER_EX(2, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			class _teleControl : public Serializable<_teleControl>
			{
			public:
				int address;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleControl)
					MEMBER(1, address)
					NAMED_MEMBER_EX(2, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			class _teleRegulation : public Serializable<_teleRegulation>
			{
			public:
				int address;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleRegulation)
					MEMBER(1, address)
					NAMED_MEMBER_EX(2, "items\0item\0", items)
				END_MEMBER_MAP()
			};
			int enabled;
			std::string name;
			std::string portGuid;
			int masterAddress;
			int slaveAddress;
			int slaveASDUAddrCmd;
			int seqOrderCheck;
			int teleSignallingType; //单点还是双点
			int teleMetryType;		//浮点还是归一化值

			_teleSignalling teleSignalling;
			_teleMetry teleMetry;
			_teleControl teleControl;
			_teleRegulation teleRegulation;

			int actionReturnTime;
			int warningReturnTime;

			BEGIN_MEMBER_MAP(_iec104Service)
				CHAIN_MEMBER_MAP(_serviceConf)
				MEMBER(101, enabled)
				MEMBER(102, name)
				MEMBER(103, portGuid)
				MEMBER(104, masterAddress)
				MEMBER(105, slaveAddress)
				MEMBER(106, slaveASDUAddrCmd)
				MEMBER(107, seqOrderCheck)
				MEMBER(108, teleSignallingType)
				MEMBER(109, teleMetryType)

				MEMBER_EX(110, teleSignalling)
				MEMBER_EX(111, teleMetry)
				MEMBER_EX(112, teleControl)
				MEMBER_EX(113, teleRegulation)

				MEMBER(114, actionReturnTime)
				MEMBER(115, warningReturnTime)
			END_MEMBER_MAP()
			DECLARE_DYNAMIC(_iec104Service, "slave.iec104Service")
		};

		class _iec103NetService : public _serviceConf
		{
		public:
			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				int innerId;
				int address; //0~1999:TeleSignal,2000~3999:TeleMetry, 4000~5999:TeleControl, 6000~ :TeleMetry
				int coef;
				int factor;
				int objType; //103Net 1:遥信取反
				std::string name;

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(1, innerId)
					MEMBER(2, address)
					MEMBER(3, coef)
					MEMBER(4, factor)
					MEMBER(5, objType)
					MEMBER(6, name)
				END_MEMBER_MAP()

				DECLARE_SERIAL_CLONE(_itemEntry)
				_itemEntry()
				{
					innerId = 0;
					address = 0;
					coef = 1;
					factor = 1;
					objType = 0;
				}
			};

			class _teleSignalling : public Serializable<_teleSignalling>
			{
			public:
				int groupNumber;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleSignalling)
					MEMBER(1, groupNumber)
					NAMED_MEMBER_EX(2, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			class _teleMetry : public Serializable<_teleMetry>
			{
			public:
				int groupNumber;
				int dataType;
				float interval;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleMetry)
					MEMBER(1, groupNumber)
					MEMBER(2, dataType)
					MEMBER(3, interval)
					NAMED_MEMBER_EX(4, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			class _teleControl : public Serializable<_teleControl>
			{
			public:
				int groupNumber;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleControl)
					MEMBER(1, groupNumber)
					NAMED_MEMBER_EX(2, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			class _teleAdjust : public Serializable<_teleAdjust>
			{
			public:
				int groupNumber;
				int dataType;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleAdjust)
					MEMBER(1, groupNumber)
					MEMBER(2, dataType)
					NAMED_MEMBER_EX(4, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			class _teleKwh : public Serializable<_teleKwh>
			{
			public:
				int groupNumber;
				int dataType;
				float interval;
				std::vector<_itemEntry*> items;
				BEGIN_MEMBER_MAP(_teleKwh)
					MEMBER(1, groupNumber)
					MEMBER(2, dataType)
					MEMBER(3, interval)
					NAMED_MEMBER_EX(4, "items\0item\0", items)
				END_MEMBER_MAP()
			};

			int enabled;
			std::string name;
			std::string portGuid;
			int masterAddress;
			int infoAddress;
			int deviceAddress;
			int reportPeriod;
			int udpModifyTime;
			int udpPort;
			int tcpPort;
			int teleSignallingType; //0:单点遥信；1:双点遥信

			_teleSignalling teleSignalling;
			_teleMetry teleMetry;
			_teleControl teleControl;
			_teleAdjust teleAdjust;
			_teleKwh	teleKwh;
			std::vector<int> mstServices;

			BEGIN_MEMBER_MAP(_iec103NetService)
				CHAIN_MEMBER_MAP(_serviceConf)
				MEMBER(101, enabled)
				MEMBER(102, name)
				MEMBER(103, portGuid)
				MEMBER(104, masterAddress)
				MEMBER(105, infoAddress)
				MEMBER(106, deviceAddress)
				MEMBER(107, reportPeriod)
				MEMBER(108, udpModifyTime)
				MEMBER(109, udpPort)
				MEMBER(110, tcpPort)
				MEMBER(111, teleSignallingType)
				MEMBER_EX(112, teleSignalling)
				MEMBER_EX(113, teleMetry)
				MEMBER_EX(114, teleControl)
				MEMBER_EX(115, teleAdjust)
				MEMBER_EX(116, teleKwh)
				MEMBER(117, mstServices)
			END_MEMBER_MAP()
			DECLARE_DYNAMIC(_iec103NetService, "slave.iec103NetService")
			_iec103NetService()
			{
				enabled = 0;
				masterAddress = 1;
				infoAddress = 1;
				deviceAddress = 1;
				reportPeriod = 10;
				udpModifyTime = 0;
				udpPort = 1032;
				tcpPort = 1048;
				teleSignallingType = 1;
			}
		};

		BOOL enabled;
		std::vector<CObjectBase*> slaves;

		BEGIN_MEMBER_MAP(_slaveConf)
			MEMBER(1, enabled)
			NAMED_MEMBER_EX(2, "slaves\0slave\0", slaves)
		END_MEMBER_MAP()
	};

	class _dbaseConf : public Serializable<_dbaseConf>
	{
	public:
		class _dbEntry : public Serializable<_dbEntry>
		{
		public:
			std::string name;
			int innerId;
			int divider; //0x40000000 最高位作为遥信通道的标志
			BEGIN_MEMBER_MAP(_dbEntry)
				MEMBER(1, name)
				MEMBER(2, innerId)
				MEMBER(3, divider)
			END_MEMBER_MAP()
			_dbEntry()
			{
				innerId = 0;
				divider = 1;
			}
		};

		class _dbCatalog : public Serializable<_dbCatalog>
		{
		public:
			std::string name;
			std::vector<_dbEntry*> entries;
			BEGIN_MEMBER_MAP(_dbCatalog)
				MEMBER(1, name)
				NAMED_MEMBER_EX(2, "entries\0entry\0", entries)
			END_MEMBER_MAP()
		};

		class _dbDevice : public Serializable<_dbDevice>
		{
		public:
			std::string name;
			std::vector<_dbCatalog*> cataloges;
			BEGIN_MEMBER_MAP(_dbDevice)
				MEMBER(1, name)
				NAMED_MEMBER_EX(2, "cataloges\0catalog\0", cataloges)
			END_MEMBER_MAP()
		};

		std::vector<_dbDevice*> devices;

		BEGIN_MEMBER_MAP(_dbaseConf)
			NAMED_MEMBER_EX(1, "devices\0device\0", devices)
		END_MEMBER_MAP()
	};

	class _waterSupplyConf : public Serializable<_waterSupplyConf>
	{
	public:
		_waterSupplyConf()
		{
			baudrate = 115200;
			serialPort = 9;
		}

		~_waterSupplyConf()
		{
			Dispose();
		}
		enum
		{
			dtuShort = 0,
			dtuint = 0x01, //normalized value
			dtchar = 0x02,
		};

		class _itemEntry : public Serializable<_itemEntry>
		{
		public:
			std::string name;
			int innerId;
			int dataType;
			int coef;
			int factor;

			BEGIN_MEMBER_MAP(_itemEntry)
				MEMBER(1, name)
				MEMBER(2, innerId)
				MEMBER(3, dataType)
				MEMBER(4, coef)
				MEMBER(5, factor)
			END_MEMBER_MAP()

			_itemEntry()
			{
				innerId = 0;
				dataType = dtuShort;
				coef = 1;
				factor = 1;
			}
		};

		int enabled;
		int serialPort;
		int baudrate;
		int waterPumpNum;  //清水泵个数
		int sewagePumpNum; //污水泵个数
		int updatePeriod;  //更新周期 单位ms
		int version_1;
		int version_2;
		int version_3;
		int version_4;
		std::vector<_itemEntry*> items;
		std::vector<_itemEntry*> controlItems;
		BEGIN_MEMBER_MAP(_waterSupplyConf)
			MEMBER(1, enabled)
			MEMBER(2, serialPort)
			MEMBER(3, baudrate)
			MEMBER(4, waterPumpNum)
			MEMBER(5, sewagePumpNum)
			MEMBER(6, updatePeriod)
			MEMBER(7, version_1)
			MEMBER(8, version_2)
			MEMBER(9, version_3)
			MEMBER(10, version_4)
			NAMED_MEMBER_EX(15, "items\0item\0", items)
			NAMED_MEMBER_EX(16, "controlItems\0controlItem\0", controlItems)
		END_MEMBER_MAP()
		DECLARE_SERIAL_CLONE(_waterSupplyConf)
	};

	class _httpClientNJNSConf : public Serializable<_httpClientNJNSConf>
	{
	public:
		_httpClientNJNSConf()
		{
			enabled = 0;
		}

		class _deviceStatusEntry : public Serializable<_deviceStatusEntry>
		{
		public:
			int subdeviceId;
			std::string name;
			std::vector<int> innerIdEntries;
			std::vector<std::string> channelNameEntries;
			// std::vector<std::string> fieldNameEntries;
			BEGIN_MEMBER_MAP(_deviceStatusEntry)
				MEMBER(1, subdeviceId)
				MEMBER(2, name)
				NAMED_MEMBER(3, "innerIdEntries\0innerIdEntry\0", innerIdEntries)
				NAMED_MEMBER(4, "channelNameEntries\0channelNameEntry\0", channelNameEntries)
				// NAMED_MEMBER(5, "fieldNameEntries\0fieldNameEntry\0", fieldNameEntries)
			END_MEMBER_MAP()
			_deviceStatusEntry()
			{
				Dispose();
			}
		};

		enum
		{
			Elevator = 0,
			Escalator,
			FireFan,
			FirePump,
			PowerRtu,
			FirePipeLine,
			FirePool,
			PowerTemperature,
			FireFlowmeter,
		} SubSystemType;

		class _deviceStatusCatalog : public Serializable<_deviceStatusCatalog>
		{
		public:
			std::string subsystemId;
			std::string key;
			int subsystemType;
			std::vector<_deviceStatusEntry*> deviceStatusEntries;
			BEGIN_MEMBER_MAP(_deviceStatusCatalog)
				MEMBER(1, subsystemId)
				MEMBER(2, key)
				MEMBER(3, subsystemType)
				NAMED_MEMBER_EX(4, "deviceStatusEntries\0deviceStatusEntry\0", deviceStatusEntries)
			END_MEMBER_MAP()
			~_deviceStatusCatalog()
			{
				Dispose();
			}
		};

		class _deviceAlarmEntry : public Serializable<_deviceAlarmEntry>
		{
		public:
			std::string subsystemId;
			std::string key;
			int subdeviceId;
			std::string name;
			int alarmType;
			std::string alarmMsg;
			int innerId;
			BEGIN_MEMBER_MAP(_deviceAlarmEntry)
				MEMBER(1, subsystemId)
				MEMBER(2, key)
				MEMBER(3, subdeviceId)
				MEMBER(4, name)
				MEMBER(5, alarmType)
				MEMBER(6, alarmMsg)
				MEMBER(7, innerId)
				//NAMED_MEMBER(6, "innerIdEntries\0innerIdEntry\0", innerIdEntries)
			END_MEMBER_MAP()
			_deviceAlarmEntry()
			{
				Dispose();
			}
		};

		class _deviceAlarmCatalog : public Serializable<_deviceAlarmCatalog>
		{
		public:
			std::string subsystemId;
			int subsystemType;
			std::vector<_deviceAlarmEntry*> deviceAlarmEntries;
			BEGIN_MEMBER_MAP(_deviceAlarmCatalog)
				MEMBER(1, subsystemId)
				MEMBER(2, subsystemType)
				NAMED_MEMBER_EX(3, "deviceAlarmEntries\0alarmEntry\0", deviceAlarmEntries)
			END_MEMBER_MAP()
			~_deviceAlarmCatalog()
			{
				Dispose();
			}
		};

		int enabled;
		std::string stationName;
		std::string url;  //url/api/v1
		int reportPeriod; //second
		int carDetector;
		std::vector<_deviceStatusCatalog*> deviceStatusCatalogs;
		std::vector<_deviceAlarmCatalog*> deviceAlarmCatalogs;

		BEGIN_MEMBER_MAP(_httpClientNJNSConf)
			MEMBER(1, enabled)
			MEMBER(2, stationName)
			MEMBER(3, url)
			MEMBER(4, reportPeriod)
			MEMBER(5, carDetector)
			NAMED_MEMBER_EX(6, "deviceStatusCatalogs\0deviceStatusCatalog\0", deviceStatusCatalogs)
			NAMED_MEMBER_EX(7, "deviceAlarmCatalogs\0deviceAlarmCatalog\0", deviceAlarmCatalogs)
		END_MEMBER_MAP()

		~_httpClientNJNSConf()
		{
			Dispose();
		}
	};

	class _httpClientConf : public Serializable<_httpClientConf>
	{
	public:
		_httpClientConf()
		{
			enabled = 0;
		}
		class _dataUpdateuEntry : public Serializable<_dataUpdateuEntry>
		{
		public:
			int innerId;
			std::string name;
			std::string type;
			float delta;
			int status;
			BEGIN_MEMBER_MAP(_dataUpdateuEntry)
				MEMBER(1, innerId)
				MEMBER(2, name)
				MEMBER(3, type)
				MEMBER(4, delta)
				MEMBER(5, status)
			END_MEMBER_MAP()
			_dataUpdateuEntry()
			{
				innerId = 0;
				delta = 1.0;
				status = 0;
			}
		};
		class _deviceAlarmEntry : public Serializable<_deviceAlarmEntry>
		{
		public:
			int innerId;
			int alarmtype;
			std::string alarmmsg;
			float threshold;
			//float alarmvalue;
			BEGIN_MEMBER_MAP(_deviceAlarmEntry)
				MEMBER(1, innerId)
				MEMBER(2, alarmtype)
				MEMBER(3, alarmmsg)
				MEMBER(4, threshold)
				//	MEMBER(5, alarmvalue)
			END_MEMBER_MAP()

			_deviceAlarmEntry()
			{
				innerId = 0;
				alarmtype = 0;
				threshold = 0.5;
			}
		};
		class _deviceStatusEntry : public Serializable<_deviceStatusEntry>
		{
		public:
			int innerId;
			std::string name;
			std::string type;
			// int status;
			BEGIN_MEMBER_MAP(_deviceStatusEntry)
				MEMBER(1, innerId)
				MEMBER(2, name)
				MEMBER(3, type)
				// MEMBER(4, status)
			END_MEMBER_MAP()
			_deviceStatusEntry()
			{
				innerId = 0;
				//	status = 0;
			}
		};
		class _dbCatalog : public Serializable<_dbCatalog>
		{
		public:
			std::string stationName;
			int stationMode;
			std::string url; //url/api/v1
			// int subsystemIdFire;
			// std::string keyFire;
			// int subsystemIdElectric;
			// std::string keyElectric;
			// int subsystemIdElevator;
			// std::string keyElevator;

			std::vector<_dataUpdateuEntry*> dataUpdateFireEntries;
			std::vector<_deviceAlarmEntry*> deviceAlarmFireEntries;
			std::vector<_deviceStatusEntry*> deviceStatusFireEntries;
			std::vector<_dataUpdateuEntry*> dataUpdateElectricEntries;
			std::vector<_deviceAlarmEntry*> deviceAlarmElectricEntries;
			std::vector<_deviceStatusEntry*> deviceStatusElectricEntries;
			std::vector<_dataUpdateuEntry*> dataUpdateElevatorEntries;
			std::vector<_deviceAlarmEntry*> deviceAlarmElevatorEntries;
			std::vector<_deviceStatusEntry*> deviceStatusElevatorEntries;
			BEGIN_MEMBER_MAP(_dbCatalog)
				MEMBER(1, stationName)
				MEMBER(2, stationMode)
				MEMBER(3, url)
				// MEMBER(4, subsystemIdFire)
				// MEMBER(5, keyFire)

				NAMED_MEMBER_EX(6, "dataUpdateFireEntries\0dataUpdateEntry\0", dataUpdateFireEntries)
				NAMED_MEMBER_EX(7, "deviceAlarmFireEntries\0deviceAlarmEntry\0", deviceAlarmFireEntries)
				NAMED_MEMBER_EX(8, "deviceStatusFireEntries\0deviceStatusEntry\0", deviceStatusFireEntries)
				NAMED_MEMBER_EX(9, "dataUpdateElectricEntries\0dataUpdateElectricEntry\0", dataUpdateElectricEntries)
				NAMED_MEMBER_EX(10, "deviceAlarmElectricEntries\0deviceAlarmElectricEntry\0", deviceAlarmElectricEntries)
				NAMED_MEMBER_EX(11, "deviceStatusElectricEntries\0deviceStatusElectricEntry\0", deviceStatusElectricEntries)
				NAMED_MEMBER_EX(12, "dataUpdateElevatorEntries\0dataUpdateElevatorEntry\0", dataUpdateElevatorEntries)
				NAMED_MEMBER_EX(13, "deviceAlarmElevatorEntries\0deviceAlarmElevatorEntry\0", deviceAlarmElevatorEntries)
				NAMED_MEMBER_EX(14, "deviceStatusElevatorEntries\0deviceStatusElevatorEntry\0", deviceStatusElevatorEntries)
			END_MEMBER_MAP()
			~_dbCatalog()
			{
				Dispose();
			}
		};

		int enabled;
		std::vector<_dbCatalog*> catalogs;

		BEGIN_MEMBER_MAP(_httpClientConf)
			MEMBER(1, enabled)
			// MEMBER(2, stationName)
			// MEMBER(3, stationMode)	//0:南京南站模式(南京宁登科技主站)
			NAMED_MEMBER_EX(4, "catalogs\0catalog\0", catalogs)
		END_MEMBER_MAP()

		~_httpClientConf()
		{
			Dispose();
		}
	};

	class _gdw1376SlaveConf : public Serializable<_gdw1376SlaveConf>
	{
	public:
		_gdw1376SlaveConf()
		{
			enabled = 0;
		}
		class _fnCatalog : public Serializable<_fnCatalog>
		{
		public:
			int fn;
			std::vector<int> innerIds;
			std::vector<std::string> channelNames;
			BEGIN_MEMBER_MAP(_fnCatalog)
				MEMBER(1, fn)
				MEMBER(2, innerIds)
				MEMBER(3, channelNames)
				//MEMBER_EX(2, "items\0item\0", items)
			END_MEMBER_MAP()
		};

		class _pnCatalog : public Serializable<_pnCatalog>
		{
		public:
			int pn;
			std::string name;
			std::vector<_fnCatalog*> items;
			BEGIN_MEMBER_MAP(_pnCatalog)
				MEMBER(1, pn)
				MEMBER(2, name)
				NAMED_MEMBER_EX(3, "items\0item\0", items)
			END_MEMBER_MAP()
		};

		class _afnCatalog : public Serializable<_afnCatalog>
		{
		public:
			int afn;
			// std::string name;
			std::vector<_pnCatalog*> catalogs;
			BEGIN_MEMBER_MAP(_afnCatalog)
				MEMBER(1, afn)
				// MEMBER(2, name)
				NAMED_MEMBER_EX(3, "catalogs\0catalog\0", catalogs)
			END_MEMBER_MAP()
		};

		int enabled;
		std::string name;
		std::string portGuid;
		int port;
		int A1;
		int A2;
		int A3;
		std::vector<_afnCatalog*> items;

		BEGIN_MEMBER_MAP(_gdw1376SlaveConf)
			MEMBER(101, enabled)
			MEMBER(102, name)
			MEMBER(103, portGuid)
			MEMBER(104, port)
			MEMBER(105, A1)
			MEMBER(106, A2)
			MEMBER(107, A3)
			NAMED_MEMBER_EX(108, "items\0item\0", items)
		END_MEMBER_MAP()
		~_gdw1376SlaveConf()
		{
			Dispose();
		}
	};

	class _gdw1376MasterConf : public Serializable<_gdw1376MasterConf>
	{
	public:
		class _gdwService : public Serializable<_gdwService>
		{
		public:
			_gdwService()
			{
			}

			~_gdwService()
			{
				Dispose();
			}

			class _itemEntry : public Serializable<_itemEntry>
			{
			public:
				int innerId;
				int pn; //da2<<8 + da1
				int fn;
				int param;
				int coef;
				int factor;
				float interval;
				std::string channelName;

				BEGIN_MEMBER_MAP(_itemEntry)
					MEMBER(1, innerId)
					MEMBER(2, pn)
					MEMBER(3, fn)
					MEMBER(4, param)
					MEMBER(5, coef)
					MEMBER(6, factor)
					MEMBER(7, interval)
					MEMBER(8, channelName)
				END_MEMBER_MAP()

				_itemEntry()
				{
				}
			};

			int a1;
			int a2;
			int a3;
			std::string ip;
			int port;
			std::string deviceName;
			int period;
			int warningInnerId;
			std::vector<_itemEntry*> items;

			BEGIN_MEMBER_MAP(_gdwService)
				MEMBER(101, a1)
				MEMBER(102, a2)
				MEMBER(103, a3)
				MEMBER(104, ip)
				MEMBER(105, port)
				MEMBER(106, deviceName)
				MEMBER(107, period)
				MEMBER(108, warningInnerId)
				NAMED_MEMBER_EX(109, "items\0item\0", items)
			END_MEMBER_MAP()
		};

		std::vector<_gdwService*> services;

		BEGIN_MEMBER_MAP(_gdw1376MasterConf)
			NAMED_MEMBER_EX(1, "services\0service\0", services)
		END_MEMBER_MAP()
		_gdw1376MasterConf()
		{
			Dispose();
		}
	};

	class _railwayEnergyConf : public Serializable<_railwayEnergyConf>
	{
	public:
		_railwayEnergyConf()
		{
			enabled = 0;
		}
		class _paramItem : public Serializable<_paramItem>
		{
		public:
			int paramId;
			int innerId;
			int infoAddr;
			std::string channelName;
			BEGIN_MEMBER_MAP(_paramItem)
				MEMBER(1, paramId)
				MEMBER(2, innerId)
				MEMBER(3, infoAddr)
				MEMBER(4, channelName)
			END_MEMBER_MAP()
		};

		class _circuitItem : public Serializable<_circuitItem>
		{
		public:
			std::string deviceName;		//=circuitName
			int circuitId;				//warningId/10000
			std::vector<_paramItem*> paramItems;
			BEGIN_MEMBER_MAP(_circuitItem)
				MEMBER(1, deviceName)
				MEMBER(2, circuitId)
				NAMED_MEMBER_EX(3, "paramItems\0paramItem\0", paramItems)
			END_MEMBER_MAP()
		};

		int enabled;
		std::string name;
		std::string enterpriseId;
		int deviceId;
		std::string ip;
		int port;
		int updatePeriod;
		std::string simCardNum;
		std::vector<_circuitItem*> circuitItems;

		BEGIN_MEMBER_MAP(_railwayEnergyConf)
			MEMBER(101, enabled)
			MEMBER(102, name)
			MEMBER(103, enterpriseId)
			MEMBER(104, deviceId)
			MEMBER(105, ip)
			MEMBER(106, port)
			MEMBER(107, updatePeriod)
			MEMBER(108, simCardNum)
			NAMED_MEMBER_EX(109, "circuitItems\0circuitItem\0", circuitItems)
		END_MEMBER_MAP()
		~_railwayEnergyConf()
		{
			Dispose();
		}
	};

	_netConf netConf;
	_serviceConf serviceConf;
	_localConf localConf;
	_masterConf masterConf;
	_slaveConf slaveConf;
	_dbaseConf dbaseConf;
	_waterSupplyConf waterSupplyConf;
	_httpClientConf httpClientConf;
	_httpClientNJNSConf httpClientNJNSConf;
	_gdw1376SlaveConf gdw1376SlaveConf;
	_gdw1376MasterConf gdw1376MasterConf;
	_railwayEnergyConf railwayEnergyConf;

	BEGIN_MEMBER_MAP(CSettings)
		MEMBER_EX(1, netConf)
		MEMBER_EX(2, serviceConf)
		MEMBER_EX(3, localConf)
		MEMBER_EX(4, masterConf)
		MEMBER_EX(5, slaveConf)
		MEMBER_EX(6, dbaseConf)
		MEMBER_EX(7, waterSupplyConf)
		MEMBER_EX(8, httpClientConf)
		MEMBER_EX(9, httpClientNJNSConf)
		MEMBER_EX(10, gdw1376SlaveConf)
		MEMBER_EX(11, gdw1376MasterConf)
		MEMBER_EX(12, railwayEnergyConf)
	END_MEMBER_MAP()
};

#endif // Settings_h__


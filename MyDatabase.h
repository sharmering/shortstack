#pragma once

#include <map>
#include <mutex>
#include "JsonFileModel.h"
#include "MySerialDAQ.h"

typedef int STATUS;

class CDbService
{
public:
	class DbEntry
	{
	public:
		int innerId;
		short dataType;
		short sDigiValue;
		double dbValue;
		int divider;
		time_t time;
		std::string channelName;

		DbEntry()
		{
		}
		DbEntry(const DbEntry& src)
		{
			*this = src;
		}

		DbEntry& operator=(const DbEntry& src)
		{
			if (this != &src)
			{
				innerId = src.innerId;
				sDigiValue = src.sDigiValue;
				dbValue = src.dbValue;
				divider = src.divider;
				time = src.time;
				channelName = src.channelName;
			}
			return *this;
		}
		//	unsigned char teleType;	//1: teleSignal; 2: teleMetry; 3: teleCommand ; 4: teleAdjusting
	};

	typedef std::vector<DbEntry*> DbEntries;

	static CDbService* m_pCDbSerivce;

	STATUS Initialize();
	void ModbusMasterUpdate(DbEntry* entries, int nentries);
	void ModbusTcpSlaveUpdate(DbEntry* entries, int nentries);
	DbEntry* FindEntry(int innerId);
	double GetInnerIdValue(int innerId);
	float GetInnderIdValue(int innerId, int mode = 0);
	void SetInnerIdValue(int innerId, double value);
	const char* GetInnerIdName(int innerId);
	static CDbService* GetInstance() {	return m_pCDbSerivce;}

	CDbService();
	~CDbService();
private:
    void PrintMasterUpdateValue(DbEntry * entry);
    void UpdateSlaveModbusTable(DbEntry * entry, int nentries);
protected:
	std::map<int, DbEntry*> m_entries;
	std::mutex m_mutex;
	ModbusDatabaseConf m_modbusDbConf;
    std::vector<float> m_modbusTeleMetrySlaveTable;
    std::vector<char> m_modbusTeleSignalSlaveTable;
};

extern CDbService DbService;

#ifdef __cplusplus
extern "C" {
#endif

	extern STATUS usrDbServiceStart(void);

#ifdef __cplusplus
}
#endif

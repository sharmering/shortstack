#include "MyDatabase.h"

CDbService DbService;

STATUS CDbService::Initialize()
{
	//add Modbus-RTU datapoints into the database m_entries
	for(int portNum = 1; portNum < 5; portNum++)
	{
		string strJsonFileName = "Port" + to_string(portNum) + ".json";
		if (MySerialDAQ::conf_file_exist(strJsonFileName))
		{
			ifstream inJson(strJsonFileName);
			string strJson((std::istreambuf_iterator<char>(inJson)),
				std::istreambuf_iterator<char>());
			inJson.close();

			//remove \r & \t
			strJson.erase(std::remove(strJson.begin(), strJson.end(), '\r'), strJson.end());
			strJson.erase(std::remove(strJson.begin(), strJson.end(), '\t'), strJson.end());
			//string to object
			Modbus_RtuSerialPortConf conf;
			bool check = JsonHelper::JsonToObject(conf, strJson);
			if (check == false)
			{
				cout << "convert json file of " << strJsonFileName << " to PortConf object failed." << endl;
				continue;
			}
			for (size_t d = 0; d < conf.Devices.size(); d++)
			{
				RtuDevice device = conf.Devices[d];
				for (size_t c = 0; c < device.vecCommands.size(); c++)
				{
					ModbusCmdOut cmd = device.vecCommands[c];
					for (size_t p = 0; p < cmd.vecOutData.size(); p++)
					{
						ModbusDataParse parse = cmd.vecOutData[p];
						DbEntry* dbEntry = new DbEntry();
						dbEntry->innerId = parse.innerId;
						if (cmd.functionCode == 1 || cmd.functionCode == 2)
							dbEntry->dataType = 1;
						dbEntry->divider = 1;
						dbEntry->channelName = parse.name;
						dbEntry->time = 0;
						m_entries[dbEntry->innerId] = dbEntry;
					}
				}
			}
		}
	}
	return STATUS();
}

void CDbService::ModbusMasterUpdate(DbEntry* entries, int nentries)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);
	// DbEntries* dbEntries = new DbEntries();
	for (int i = 0; i < nentries; i++)
	{
		DbEntry& entry = entries[i];
		std::map<int, DbEntry*>::iterator it = m_entries.find(entry.innerId);
		if (it != m_entries.end())
		{
			DbEntry* dbEntry = it->second;
			assert(dbEntry);
			if(dbEntry->dataType == 0 && dbEntry->dbValue != entry.dbValue) //|| first <= 2)
			{
				dbEntry->dbValue = entry.dbValue;
				dbEntry->divider = entry.divider;
				dbEntry->time = entry.time;
				//Update Modbus Table
				// dbEntries->push_back(dbEntry);
			}
			else if(dbEntry->dataType == 1 && dbEntry->sDigiValue != entry.sDigiValue)
            {
                dbEntry->dbValue = entry.sDigiValue;
                dbEntry->sDigiValue = entry.sDigiValue;
				dbEntry->divider = entry.divider;
				dbEntry->time = entry.time;
				//Update Modbus Table
            }
		}
	}
}

void CDbService::ModbusTcpSlaveUpdate(DbEntry* entries, int nentries)
{
}

CDbService::DbEntry* CDbService::FindEntry(int innerId)
{
	std::map<int, DbEntry*>::iterator it = m_entries.find(innerId);
	if (it != m_entries.end())
		return it->second;
	else
		return nullptr;
}

double CDbService::GetInnerIdValue(int innerId)
{
	std::map<int, DbEntry*>::iterator it = m_entries.find(innerId);
	if (it != m_entries.end())
	{
		return it->second->dbValue;
	}
	return -1.0f;
}

float CDbService::GetInnderIdValue(int innerId, int mode)
{
	if (mode == 0)
	{
		std::map<int, DbEntry*>::iterator it = m_entries.find(innerId);
		if (it != m_entries.end())
		{
			return (float)it->second->dbValue;
		}
	}
	return -1.0f;
}

void CDbService::SetInnerIdValue(int innerId, double value)
{
	std::lock_guard<std::mutex> lockGuard(m_mutex);
	DbEntries* dbEntries = new DbEntries();
	std::map<int, DbEntry*>::iterator it = m_entries.find(innerId);
	if (it != m_entries.end())
	{
		DbEntry* dbEntry = it->second;
		assert(dbEntry);
		time_t now_time = time(NULL);
		//struct tm Tm;
		//localtime_r(&now_time, &Tm);
		dbEntry->time = now_time;
		dbEntry->dbValue = value;
		dbEntry->divider = 1;
		cout << "CDbService::SetInnerIdValue: dbEntry->innerId=" <<dbEntry->innerId << "new value=" <<value << endl;
		dbEntries->push_back(dbEntry);
	}
}

const char* CDbService::GetInnerIdName(int innerId)
{
	std::map<int, DbEntry*>::iterator it = m_entries.find(innerId);
	if (it != m_entries.end())
	{
		return it->second->channelName.c_str();
	}
	return "";
}

CDbService* CDbService::m_pCDbSerivce = NULL;

CDbService::CDbService()
{
	assert(m_pCDbSerivce == NULL);
	if (m_pCDbSerivce == NULL)
		m_pCDbSerivce = this;
}

CDbService::~CDbService()
{
	//m_serialmasters.clear();
	m_entries.clear();
	assert(m_pCDbSerivce == this);
	if (m_pCDbSerivce == this)
		m_pCDbSerivce = NULL;
}


STATUS usrDbServiceStart(void)
{
	DbService.Initialize();
	return OK;
}

#pragma once

#define DATAMANAGER DataManager::GetInstance()

class DataManager
{
public:
	std::vector<DataPacket> data;

	static DataManager* GetInstance()
	{
		static DataManager instance;
		return &instance;
	}

	DataManager();
	~DataManager();
};


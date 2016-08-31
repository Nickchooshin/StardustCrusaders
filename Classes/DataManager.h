#ifndef _DATA_MANAGER_H_
#define _DATA_MANAGER_H_

#include <string>

class DataManager
{
private:
	std::string m_filepath;

	// Save Data
	int m_unlockStageNumber;

	// Unsave Data
	int m_selectedStageNumber;

public:
	static DataManager* GetInstance();

	void LoadData();
	void SaveData();

	void UnlockStage(int stageNumber);
	void SetSelectedStage(int stageNumber);

	int GetUnlockStage() const;
	int GetSelectedStage() const;
private:
	DataManager();
	DataManager(const DataManager&);
	~DataManager();

	void CreateNewData();
};

#endif
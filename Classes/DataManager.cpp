#include "DataManager.h"

#include "cocos2d.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/filewritestream.h"
#include "json/filereadstream.h"

USING_NS_CC;

DataManager::DataManager()
	: m_filepath("")
	, m_unlockStageNumber(0)
{
	m_filepath = FileUtils::getInstance()->getWritablePath();
	m_filepath.append("sc_data.json");
}
DataManager::~DataManager()
{
}

DataManager* DataManager::GetInstance()
{
	static DataManager instance;

	return &instance;
}

void DataManager::LoadData()
{
	FILE *file = fopen(m_filepath.c_str(), "r");
	if (file == nullptr)
	{
		CreateNewData();
		file = fopen(m_filepath.c_str(), "r");
	}

	char buffer[256];
	rapidjson::Document document;
	rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
	document.ParseStream(is);
	fclose(file);

	m_unlockStageNumber = document["Stage"].GetInt();
}

void DataManager::SaveData()
{
	FILE *file = fopen(m_filepath.c_str(), "w");

	char buffer[256];
	rapidjson::Document document;
	rapidjson::FileWriteStream os(file, buffer, sizeof(buffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	document.SetObject();
	document.AddMember("Stage", m_unlockStageNumber, document.GetAllocator());
	document.Accept(writer);

	fclose(file);
}

void DataManager::CreateNewData()
{
	FILE *file = fopen(m_filepath.c_str(), "w");

	char buffer[100];
	rapidjson::Document document;
	rapidjson::FileWriteStream os(file, buffer, sizeof(buffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream> writer(os);

	document.SetObject();
	document.AddMember("Stage", 0, document.GetAllocator());
	document.Accept(writer);

	fclose(file);
}

void DataManager::UnlockStage(int stageNumber)
{
	if (stageNumber > m_unlockStageNumber)
	{
		m_unlockStageNumber = stageNumber;

		SaveData();
	}
}

void DataManager::SetSelectedStage(int stageNumber)
{
	m_selectedStageNumber = stageNumber;
}

int DataManager::GetUnlockStage() const
{
	return m_unlockStageNumber;
}

int DataManager::GetSelectedStage() const
{
	return m_selectedStageNumber;
}
#ifndef DDS_API_INCLUDE
#define DDS_API_INCLUDE

#include "BasicTypes.h"
#include "ReturnCode.h"

#include "dds/DomainManagement.h"
#include "dds/DomainParticipant.h"
#include "dds/DataWriter.h"
#include "dds/DataReader.h"
#include "dds/datawriterlistener.h"
#include "dds/DataReaderListener.h"

#include "dds/StringDataWriter.h"
#include "dds/StringDataReader.h"
#include "dds/StringTypeSupport.h"

//IDL生成的文件
#include "IDL_DataWriter.h"
#include "IDL_DataReader.h"
#include "IDL_TypeSupport.h"

//加入数据域
inline _RETURNCODE_T DomainInit(_DOMAINID_T domainId, char* compName) {
    DomainParticipant *pDomainParticipant = DomainManagement::GetInstance()->DomainInit(domainId, compName);
    if (pDomainParticipant == NULL)
        return RETURNCODE_DOMAIN_INIT_FAILED;

    //IDL编译器生成 注册数据类型
    K5SetInfoTypeSupport::Register_Type(pDomainParticipant, K5SetInfoTypeSupport::Get_Type_Name());
    K4SetInfoTypeSupport::Register_Type(pDomainParticipant, K4SetInfoTypeSupport::Get_Type_Name());
    BigSetInfoTypeSupport::Register_Type(pDomainParticipant, BigSetInfoTypeSupport::Get_Type_Name());
    EquipNumInfoTypeSupport::Register_Type(pDomainParticipant, EquipNumInfoTypeSupport::Get_Type_Name());
    CsBaitNumInfoTypeSupport::Register_Type(pDomainParticipant, CsBaitNumInfoTypeSupport::Get_Type_Name());
    BigBaitInfoTypeSupport::Register_Type(pDomainParticipant, BigBaitInfoTypeSupport::Get_Type_Name());
    TorpedoTacticsTypeSupport::Register_Type(pDomainParticipant, TorpedoTacticsTypeSupport::Get_Type_Name());
    MissileTacticsTypeSupport::Register_Type(pDomainParticipant, MissileTacticsTypeSupport::Get_Type_Name());
    DefenceTacticsTypeSupport::Register_Type(pDomainParticipant, DefenceTacticsTypeSupport::Get_Type_Name());
    CombatTacticsTypeSupport::Register_Type(pDomainParticipant, CombatTacticsTypeSupport::Get_Type_Name());
    RadarMessureInfoTypeSupport::Register_Type(pDomainParticipant, RadarMessureInfoTypeSupport::Get_Type_Name());
    WaterSetTypeSupport::Register_Type(pDomainParticipant, WaterSetTypeSupport::Get_Type_Name());
    TMAInfoTypeSupport::Register_Type(pDomainParticipant, TMAInfoTypeSupport::Get_Type_Name());
    AllTargetInfoTypeSupport::Register_Type(pDomainParticipant, AllTargetInfoTypeSupport::Get_Type_Name());
    NavInfo1TypeSupport::Register_Type(pDomainParticipant, NavInfo1TypeSupport::Get_Type_Name());
    NavInfo2TypeSupport::Register_Type(pDomainParticipant, NavInfo2TypeSupport::Get_Type_Name());
    ZHSonarInfoTypeSupport::Register_Type(pDomainParticipant, ZHSonarInfoTypeSupport::Get_Type_Name());
    SWSonarInfoTypeSupport::Register_Type(pDomainParticipant, SWSonarInfoTypeSupport::Get_Type_Name());
    TYSonarInfoTypeSupport::Register_Type(pDomainParticipant, TYSonarInfoTypeSupport::Get_Type_Name());
    //S//coutInfoTypeSupport::Register_Type(pDomainParticipant, S//coutInfoTypeSupport::Get_Type_Name());
    //RadarS//coutInfoTypeSupport::Register_Type(pDomainParticipant, RadarS//coutInfoTypeSupport::Get_Type_Name());
    SoundSpeedTypeSupport::Register_Type(pDomainParticipant, SoundSpeedTypeSupport::Get_Type_Name());
    Y4TeleInfoTypeSupport::Register_Type(pDomainParticipant, Y4TeleInfoTypeSupport::Get_Type_Name());
    Y4ForSetInfoTypeSupport::Register_Type(pDomainParticipant, Y4ForSetInfoTypeSupport::Get_Type_Name());
    Y4ForReplyInfoTypeSupport::Register_Type(pDomainParticipant, Y4ForReplyInfoTypeSupport::Get_Type_Name());
    Y4RemConInfoTypeSupport::Register_Type(pDomainParticipant, Y4RemConInfoTypeSupport::Get_Type_Name());
    Y12ForSetInfoTypeSupport::Register_Type(pDomainParticipant, Y12ForSetInfoTypeSupport::Get_Type_Name());
    Y12ForReplyInfoTypeSupport::Register_Type(pDomainParticipant, Y12ForReplyInfoTypeSupport::Get_Type_Name());
    Y12RemConInfoTypeSupport::Register_Type(pDomainParticipant, Y12RemConInfoTypeSupport::Get_Type_Name());
    Y12TeleInfoTypeSupport::Register_Type(pDomainParticipant, Y12TeleInfoTypeSupport::Get_Type_Name());
    AttackInfoTypeSupport::Register_Type(pDomainParticipant, AttackInfoTypeSupport::Get_Type_Name());
    TorSatInfoTypeSupport::Register_Type(pDomainParticipant, TorSatInfoTypeSupport::Get_Type_Name());
    TorpedoLoadInfoTypeSupport::Register_Type(pDomainParticipant, TorpedoLoadInfoTypeSupport::Get_Type_Name());
    MissileLoadInfoTypeSupport::Register_Type(pDomainParticipant, MissileLoadInfoTypeSupport::Get_Type_Name());
    TorTarInfoTypeSupport::Register_Type(pDomainParticipant, TorTarInfoTypeSupport::Get_Type_Name());
    TorpedoSystemStateTypeSupport::Register_Type(pDomainParticipant, TorpedoSystemStateTypeSupport::Get_Type_Name());
    CommandState1TypeSupport::Register_Type(pDomainParticipant, CommandState1TypeSupport::Get_Type_Name());
    CommandState4TypeSupport::Register_Type(pDomainParticipant, CommandState4TypeSupport::Get_Type_Name());
    CommandState7TypeSupport::Register_Type(pDomainParticipant, CommandState7TypeSupport::Get_Type_Name());
    CommandState9TypeSupport::Register_Type(pDomainParticipant, CommandState9TypeSupport::Get_Type_Name());
    CommandState18TypeSupport::Register_Type(pDomainParticipant, CommandState18TypeSupport::Get_Type_Name());
    WeaponCommand1TypeSupport::Register_Type(pDomainParticipant, WeaponCommand1TypeSupport::Get_Type_Name());
    WeaponCommand4TypeSupport::Register_Type(pDomainParticipant, WeaponCommand4TypeSupport::Get_Type_Name());
    WeaponCommand7TypeSupport::Register_Type(pDomainParticipant, WeaponCommand7TypeSupport::Get_Type_Name());
    WeaponCommand9TypeSupport::Register_Type(pDomainParticipant, WeaponCommand9TypeSupport::Get_Type_Name());
    WeaponCommand12TypeSupport::Register_Type(pDomainParticipant, WeaponCommand12TypeSupport::Get_Type_Name());
    BaitCommand4TypeSupport::Register_Type(pDomainParticipant, BaitCommand4TypeSupport::Get_Type_Name());
    BaitCommand7TypeSupport::Register_Type(pDomainParticipant, BaitCommand7TypeSupport::Get_Type_Name());
    BaitCommand9TypeSupport::Register_Type(pDomainParticipant, BaitCommand9TypeSupport::Get_Type_Name());
    BaitState4TypeSupport::Register_Type(pDomainParticipant, BaitState4TypeSupport::Get_Type_Name());
    BaitState7TypeSupport::Register_Type(pDomainParticipant, BaitState7TypeSupport::Get_Type_Name());
    BaitState9TypeSupport::Register_Type(pDomainParticipant, BaitState9TypeSupport::Get_Type_Name());
    BigBaitCommand1TypeSupport::Register_Type(pDomainParticipant, BigBaitCommand1TypeSupport::Get_Type_Name());
    BigBaitCommand4TypeSupport::Register_Type(pDomainParticipant, BigBaitCommand4TypeSupport::Get_Type_Name());
    BigBaitCommand7TypeSupport::Register_Type(pDomainParticipant, BigBaitCommand7TypeSupport::Get_Type_Name());
    BigBaitCommand9TypeSupport::Register_Type(pDomainParticipant, BigBaitCommand9TypeSupport::Get_Type_Name());
    BigBaitCommand12TypeSupport::Register_Type(pDomainParticipant, BigBaitCommand12TypeSupport::Get_Type_Name());
    BigBaitState1TypeSupport::Register_Type(pDomainParticipant, BigBaitState1TypeSupport::Get_Type_Name());
    BigBaitState4TypeSupport::Register_Type(pDomainParticipant, BigBaitState4TypeSupport::Get_Type_Name());
    BigBaitState7TypeSupport::Register_Type(pDomainParticipant, BigBaitState7TypeSupport::Get_Type_Name());
    BigBaitState9TypeSupport::Register_Type(pDomainParticipant, BigBaitState9TypeSupport::Get_Type_Name());
    BigBaitState18TypeSupport::Register_Type(pDomainParticipant, BigBaitState18TypeSupport::Get_Type_Name());
    MissileState1TypeSupport::Register_Type(pDomainParticipant, MissileState1TypeSupport::Get_Type_Name());
    MissileState4TypeSupport::Register_Type(pDomainParticipant, MissileState4TypeSupport::Get_Type_Name());
    MissileState7TypeSupport::Register_Type(pDomainParticipant, MissileState7TypeSupport::Get_Type_Name());
    MissileState9TypeSupport::Register_Type(pDomainParticipant, MissileState9TypeSupport::Get_Type_Name());
    MissileState18TypeSupport::Register_Type(pDomainParticipant, MissileState18TypeSupport::Get_Type_Name());
    MissileCommand1TypeSupport::Register_Type(pDomainParticipant, MissileCommand1TypeSupport::Get_Type_Name());
    MissileCommand4TypeSupport::Register_Type(pDomainParticipant, MissileCommand4TypeSupport::Get_Type_Name());
    MissileCommand7TypeSupport::Register_Type(pDomainParticipant, MissileCommand7TypeSupport::Get_Type_Name());
    MissileCommand9TypeSupport::Register_Type(pDomainParticipant, MissileCommand9TypeSupport::Get_Type_Name());
    MissileCommand12TypeSupport::Register_Type(pDomainParticipant, MissileCommand12TypeSupport::Get_Type_Name());
    ComputerDisplayTypeSupport::Register_Type(pDomainParticipant, ComputerDisplayTypeSupport::Get_Type_Name());
    MissileCommand22TypeSupport::Register_Type(pDomainParticipant, MissileCommand22TypeSupport::Get_Type_Name());
    MissionCommandTypeSupport::Register_Type(pDomainParticipant, MissionCommandTypeSupport::Get_Type_Name());

	NodeInfoTypeSupport::Register_Type(pDomainParticipant, NodeInfoTypeSupport::Get_Type_Name());
	CompInfoTypeSupport::Register_Type(pDomainParticipant, CompInfoTypeSupport::Get_Type_Name());
	TopicInfoTypeSupport::Register_Type(pDomainParticipant, TopicInfoTypeSupport::Get_Type_Name());
	RecordInfoSendListTypeSupport::Register_Type(pDomainParticipant, RecordInfoSendListTypeSupport::Get_Type_Name());

    return RETURNCODE_OK;
}

//创建发布者
inline DataWriter *CreateDataWriter(const char *componentName,
                             _DOMAINID_T domainId,
                             const char *strTopic_name,
                             const char *strType_name,
                             DataWriterListener *pListener,
                             const _DATA_WRITER_QOS *pQos) {
    DomainParticipant *pDomainParticipant = DomainManagement::GetInstance()->ParticipantGet(domainId);
    if (pDomainParticipant == NULL) {
        return NULL;
    }

    Topic *topic = pDomainParticipant->CreateTopic(strTopic_name, strType_name);
    if (topic == NULL) {
        return NULL;
    }

    DataWriter *newDataWriter = pDomainParticipant->CreateDataWriter(
        topic, pListener, pQos, STATUS_MASK_ALL);
    newDataWriter->AppSet(componentName);

    return newDataWriter;
}

//删除发布者
inline _RETURNCODE_T DeleteDataWriter(DataWriter *aDataWriter) {
    DomainParticipant *pDomainParticipant = aDataWriter->GetDomainParticipant();
    return pDomainParticipant->Delete_Datawriter(aDataWriter);
}

//创建订阅者
inline DataReader *CreateDataReader(const char *componentName,
                             _DOMAINID_T domainId,
                             const char *strTopic_name,
                             const char *strType_name,
                             DataReaderListener *pListener,
                             const _DATA_READER_QOS *pQos) {
    DomainParticipant *pDomainParticipant = DomainManagement::GetInstance()->ParticipantGet(domainId);
    if (pDomainParticipant == NULL) {
        return NULL;
    }

    Topic *topic = pDomainParticipant->CreateTopic(strTopic_name, strType_name);
    if (topic == NULL) {
        return NULL;
    }

    DataReader *newDataReader = pDomainParticipant->CreateDataReader(
        topic, pListener, pQos, STATUS_MASK_ALL);
    newDataReader->AppSet(componentName);

    return newDataReader;
}

//删除订阅者
inline _RETURNCODE_T DeleteDataReader(DataReader *aDataReader) {
    DomainParticipant *pDomainParticipant = aDataReader->GetDomainParticipant();
    return pDomainParticipant->Delete_Datareader(aDataReader);
}

//退出数据域
inline _RETURNCODE_T DomainRelease(_DOMAINID_T domainId) {
    return DomainManagement::GetInstance()->DomainRelease(domainId);
}

#endif

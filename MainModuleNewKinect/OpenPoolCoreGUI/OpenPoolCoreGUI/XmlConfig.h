#pragma once
#include "AppConfig.h"

using namespace System::IO;
using namespace System::Xml::Serialization;
using namespace System::Runtime::InteropServices;

ref class XmlConfig {
    private: System::String^ configFile;
    public: XmlConfig(System::String^ filename) {
	    this->configFile = filename;
    }

    public: AppConfig^ Load(void) {
        XmlSerializer^ serializer = gcnew XmlSerializer(AppConfig::typeid);
        AppConfig^ ret;
        FileStream^ fs = gcnew FileStream(this->configFile, FileMode::Open);
        ret = (AppConfig^)serializer->Deserialize(fs);
        fs->Close();
        return ret;

    }

    public: System::Void Save(AppConfig^ conf) {
	    XmlSerializer^ serializer = gcnew XmlSerializer(AppConfig::typeid);
	    FileStream^ fs = gcnew FileStream(this->configFile, FileMode::Create);
	    serializer->Serialize(fs, conf);
	    fs->Close();
    }
};
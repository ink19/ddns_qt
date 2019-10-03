#include "ddnssetting.h"

DDnsSetting::DDnsSetting()
{
    QFileInfo settingFileInfo("setting.ini");
    if(settingFileInfo.isFile()) {
        config = new QSettings("setting.ini", QSettings::Format::IniFormat);
        return;
    }
    config = new QSettings("setting.ini", QSettings::Format::IniFormat);
    config->setValue("DDns/ID", 0);
    config->setValue("DDns/Token", 0);
    config->setValue("DDns/domain", 0);
    config->setValue("DDns/record_id", 0);
    config->setValue("DDns/sub_domain", 0);
    config->setValue("DDns/record_type", "A");
    config->setValue("DDns/record_line", "默认");
    config->setValue("DDns/status", "enable");
}

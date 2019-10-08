#include "ddnssetting.h"

DDnsSetting::DDnsSetting()
{
    QString filepath = QCoreApplication::applicationDirPath() +  "/setting.ini";
    QFileInfo settingFileInfo(filepath);
    if(settingFileInfo.isFile()) {
        config = new QSettings(filepath, QSettings::Format::IniFormat);
        return;
    }
    config = new QSettings(filepath, QSettings::Format::IniFormat);
    config->setValue("DDns/ID", "0");
    config->setValue("DDns/Token", "0");
    config->setValue("DDns/domain", "0");
    config->setValue("DDns/record_id", "0");
    config->setValue("DDns/sub_domain", "0");
    config->setValue("DDns/record_type", "A");
    config->setValue("DDns/record_line", "默认");
    config->setValue("DDns/status", "enable");
    config->setValue("DDns/port", "10517");
}

QString DDnsSetting::getValue(QString key)
{
    return config->value("DDns/" + key).toString();
}

QString DDnsSetting::setValue(QString key, QString value)
{
    config->setValue("DDns/" + key, value);
    return value;
}

#include "config.h"

#include <QFileInfo>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>
#include <QVariant>
#include <QDebug>
#include <QDir>

#define PATH_CONFIG_JSON_FILE "C:/Json_Files/BLCD_Testsoftware.json"

Config::Config()
{

}

void Config::Map_To_JsonFile()
{
    QMapIterator<QString, QString> iter_config(config_map);
    QJsonObject dataObject;
    while (iter_config.hasNext())
    {
        iter_config.next();
        dataObject.insert(iter_config.key(),iter_config.value());
    }
    QJsonDocument doc(dataObject);
    json.save(doc, PATH_CONFIG_JSON_FILE);
}

void Config::JsonFile_To_Map()
{
    QJsonDocument doc;
    QJsonObject jObject;
    QVariantMap mainMap;

    doc = json.load(PATH_CONFIG_JSON_FILE);
    jObject = doc.object();
    mainMap = jObject.toVariantMap();
    config_map.clear();
    for(QVariantMap::const_iterator iter = mainMap.begin(); iter != mainMap.end(); ++iter)
    {
        config_map.insert(iter.key(), iter.value().toString());
    }
}

void Config::ini()
{
    if (!QFileInfo::exists(PATH_CONFIG_JSON_FILE))
    {
        // Config anlegen
        QDir dir("C:/Json_Files");
        if (!dir.exists()) {
            dir.mkpath("C:/Json_Files");
        }
        qDebug() << "create and store config file";
        config_map["Baud"] = "115200";
        config_map["Port"] = "COM7";
        Map_To_JsonFile();

        emit sigBaud(config_map["Baud"].toInt());
        emit sigPort(config_map["Port"]);

    }
    else
    {
        // Config laden
        qDebug() << "load existing config file";
        JsonFile_To_Map();

        emit sigBaud(config_map["Baud"].toInt());
        emit sigPort(config_map["Port"]);
    }
}

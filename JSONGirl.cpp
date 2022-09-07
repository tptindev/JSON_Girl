#include "JSONGirl.h"

JSONGirl::JSONGirl()
{
}

bool JSONGirl::loadJSONFile(const QString &p_FilePath, QJsonDocument &p_Document)
{
    QFile file(p_FilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QByteArray data = file.readAll();
    file.close();

    QJsonParseError err;
    p_Document = QJsonDocument::fromJson(data, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug() << "Load JSON File Failed";
        return false;
    };
    qDebug() << "Load JSON File Success";
    return true;
}

void JSONGirl::writeJSONFile(const QString &p_FilePath, QJsonObject &p_Object)
{
    QJsonDocument newDoc;
    newDoc.setObject(p_Object);
    QByteArray bytes =  newDoc.toJson(QJsonDocument::Indented);

    QFile file(p_FilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream out(&file);
    out << bytes;

    file.close();
}

void JSONGirl::updateJSONObject(QJsonObject &p_Object, const QString &p_Query,  QJsonValue &p_Value)
{
    // Address.City
    QStringList query = p_Query.split("."); // Address, City
    foreach (QString key, query)
    {
        QJsonValue subObj = p_Object.value(key);
        QJsonObject tmpObj = subObj.toObject();
        if(subObj.isBool())
        {
            qDebug() << key << "Bool";
            tmpObj[key] = p_Value.toBool();
        }
        else if(subObj.isDouble())
        {
            qDebug() << key << "Double";
            tmpObj[key] = p_Value.toDouble();
        }
        else if(subObj.isString())
        {
            qDebug() << key << "String";
            tmpObj[key] = p_Value.toString();
        }
        else if(subObj.isArray())
        {
            qDebug() << key << "Array";
        }
        else if(subObj.isObject())
        {
            qDebug() << key << "Object";

            foreach (QString subKey, tmpObj.keys()) {
                updateJSONObject(tmpObj, subKey, p_Value);
            }
        }

        p_Object[key] = tmpObj;
    }
}

QHash<QString, QVariant> JSONGirl::parse(QJsonObject &p_Object, const QString &p_ParentKey)
{
    foreach(QString key, p_Object.keys())
    {
        QString newKey = key;
        if(p_ParentKey != "")
        {
            newKey = p_ParentKey + "." + key;
        }
        QJsonValue subObj = p_Object.value(key);

        if(subObj.isBool())
        {
            m_ObjMap[newKey] = subObj.toBool();
        }
        else if(subObj.isDouble())
        {
            m_ObjMap[newKey] = subObj.toDouble();
        }
        else if(subObj.isString())
        {
            m_ObjMap[newKey] = subObj.toString();
        }
        else if(subObj.isArray())
        {
            QList<QJsonValue> list;
            int index = 0;
            /*
                "weather": [
                    {
                    "id": 502,
                    "main": "Rain",
                    "description": "heavy intensity rain",
                    "icon": "10d"
                    }
                ],
            */
            foreach (QJsonValueRef item, subObj.toArray()) {
                if(item.isObject())
                {
                    QString indicator = newKey + "[" + QString::number(index) + "]";
                    QJsonObject tmp = item.toObject();
                    /*
                        {
                        "id": 502,
                        "main": "Rain",
                        "description": "heavy intensity rain",
                        "icon": "10d"
                        }
                    */
                    foreach (QString subKey, tmp.keys()) {
                        m_ObjMap[indicator + "." + subKey] = parse(tmp, indicator);
                    }
                }
                else
                {
                    list += item;
                }
                index++;
            }
            m_ObjMap[newKey] = QVariant::fromValue(list);
        }
        else if(subObj.isObject())
        {
            QJsonObject tmpObj = subObj.toObject();
            m_ObjMap[newKey] = parse(tmpObj, newKey);
        }
    }
    return m_ObjMap;
}

QString JSONGirl::stringify(QJsonDocument &p_Document)
{
    return "";
}

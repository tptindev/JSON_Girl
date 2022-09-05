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
        QJsonObject tmpObj = subObj.toObject();
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
            foreach (QJsonValueRef item, subObj.toArray()) {
                if(item.isObject())
                {
                    m_ObjMap[newKey] = parse(tmpObj, newKey);
                }
                else
                {
                    list += item;
                }
            }
            m_ObjMap[newKey] = QVariant::fromValue(list);
        }
        else if(subObj.isObject())
        {
            m_ObjMap[newKey] = parse(tmpObj, newKey);
        }
    }
    return m_ObjMap;
}

QString JSONGirl::stringify(QJsonDocument &p_Document)
{
    return "";
}

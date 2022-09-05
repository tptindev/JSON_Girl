#ifndef JSONGIRL_H
#define JSONGIRL_H

#include <QFile>
#include <QHash>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "JSONGirl_global.h"

class JSONGIRL_EXPORT JSONGirl
{

private:
    QHash<QString, QVariant> m_ObjMap;
public:
  JSONGirl();

  bool loadJSONFile(const QString &p_FilePath, QJsonDocument &p_Document);
  void writeJSONFile(const QString &p_FilePath, QJsonObject &p_Object);
  QHash<QString, QVariant> parse(QJsonObject &p_Object, const QString &p_ParentKey = "");
  QString stringify(QJsonDocument &p_Document);


};

#endif // JSONGIRL_H

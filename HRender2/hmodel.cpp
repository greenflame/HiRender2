#include "hmodel.h"


void HModel::transform(QMatrix4x4 m)
{
    for (int i = 0; i < polygons.length(); i++)
        polygons[i].transform(m);
}

HModel HModel::transformed(QMatrix4x4 m)
{
    HModel model = *this;
    model.transform(m);
    return model;
}

HModel HModel::loadObj(QString filename)
{
    QFile inputFile(filename);
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);

    QVector<QVector3D> vertexes;
    HModel model;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(' ');

        if (list[0] == "v")
        {
            float a = list[1].toFloat();
            float b = list[2].toFloat();
            float c = list[3].toFloat();
            vertexes.append(QVector3D(a, b, c));
        }

        if (list[0] == "f")
        {
            for (int i = 2; i < list.length() - 1; i++)
            {
                HPolygon polygon;
                polygon.setA(vertexes[list[1].toInt() - 1]);
                polygon.setB(vertexes[list[i].toInt() - 1]);
                polygon.setC(vertexes[list[i + 1].toInt() - 1]);
                model.polygons.append(polygon);
            }
        }
    }

    inputFile.close();

    return model;
}

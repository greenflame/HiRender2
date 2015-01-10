#include "hscene.h"

HScene::HScene()
{

}

HScene::~HScene()
{

}

void HScene::transform(const QMatrix4x4 &matrix)
{
    for (int i = 0; i < polygons.length(); i++)
        polygons[i].transform(matrix);

    for (int i = 0; i < lamps.length(); i++)
        lamps[i] = matrix * lamps[i];
}

QVector<HPolygon> HScene::loadObj(QString filename)
{
    QFile inputFile(filename);
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);

    QVector<QVector3D> vertexes;
    QVector<HPolygon> polygons;

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
                QVector3D p1 = vertexes[list[1].toInt() - 1];
                QVector3D p2 = vertexes[list[i].toInt() - 1];
                QVector3D p3 = vertexes[list[i + 1].toInt() - 1];
                polygons.append(HPolygon(p1, p2, p3));
            }
        }
    }

    inputFile.close();

    return polygons;
}


#include "sscene.h"

SScene::SScene()
{
    materials.insert("default", SMaterial(Qt::gray));
}

SScene::~SScene()
{

}

void SScene::clear()
{
    *this = SScene();
}

bool SScene::loadObj(const QString &fileName)
{
    QFile inputFile(fileName);
    bool isOpenSucces = inputFile.open(QIODevice::ReadOnly);

    if (!isOpenSucces)
    {
        qDebug() << QString("Can not open file: %0").arg(fileName);
        return false;
    }

    QTextStream inputStream(&inputFile);

    QVector<QVector3D> vertexCoordinates;
    QVector<QVector3D> textureCoordinates;
    QVector<QVector3D> normals;

    QString currentMaterialName = "default";

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        line.replace("  ", " ");
        QStringList params = line.split(' ');

        // Loading material library
        if (params[0] == "mtllib")
        {
            bool mtlLoadSucces = loadMtl(QFileInfo(fileName).path() + "/" + params[1]);

            if (!mtlLoadSucces)
            {
                qDebug() << "Cann't load material library.";
//                return false;
            }
        }

        // Set current material
        if (params[0] == "usemtl")
        {
            QString materialName = params[1];
            currentMaterialName = materials.keys().contains(materialName) ? materialName : "default";
        }

        // New vertex coordinate declaration
        if (params[0] == "v")
        {
            float a = params[1].toFloat();
            float b = params[2].toFloat();
            float c = params[3].toFloat();
            vertexCoordinates.append(QVector3D(a, b, c));
        }

        // New texture coordinate declaration
        if (params[0] == "vt")
        {
            float a = params[1].toFloat();
            float b = params[2].toFloat();

            // Third coordinate is optional
            float c = 0;
            if (params.length() > 3)
            {
                c = params[3].toFloat();
            }

            textureCoordinates.append(QVector3D(a, b, c));
        }

        // New normal declaration
        if (params[0] == "vn")
        {
            float a = params[1].toFloat();
            float b = params[2].toFloat();
            float c = params[3].toFloat();
            normals.append(QVector3D(a, b, c).normalized());
        }

        // Face declaration
        if (params[0] == "f")
        {
            // Split face to triangeles
            for (int i = 2; i < params.length() - 1; i++)
            {
                // 3 current vertexes
                QStringList p1 = params[1].split('/');
                QStringList p2 = params[i].split('/');
                QStringList p3 = params[i + 1].split('/');

                int v1, v2, v3, t1, t2, t3, n1, n2, n3;
                bool isTextureSet = false;
                bool isNormalsSet = false;

                v1 = p1[0].toInt();
                v2 = p2[0].toInt();
                v3 = p3[0].toInt();

                if (p1.length() > 1 && p1.at(1).length() != 0)
                {
                    t1 = p1[1].toInt();
                    t2 = p2[1].toInt();
                    t3 = p3[1].toInt();
                    isTextureSet = true;
                }

                if (p1.length() > 2)
                {
                    n1 = p1[2].toInt();
                    n2 = p2[2].toInt();
                    n3 = p3[2].toInt();
                    isNormalsSet = true;
                }

                if (isNormalsSet)
                {
                    polygons.append(SPolygon(
                            vertexCoordinates[v1 - 1],
                            vertexCoordinates[v2 - 1],
                            vertexCoordinates[v3 - 1],

                            normals[n1 - 1],
                            normals[n2 - 1],
                            normals[n3 - 1],

                            currentMaterialName));
                }
                else
                {
                    polygons.append(SPolygon(
                            vertexCoordinates[v1 - 1],
                            vertexCoordinates[v2 - 1],
                            vertexCoordinates[v3 - 1],

                            currentMaterialName));
                }

            }
        }   // Face declaration end



    }

    inputFile.close();
    return true;
}

void SScene::copyToTracer(HTracer3 &tracer)
{
    // Copy maerials
    for (QMap<QString, SMaterial>::iterator i = materials.begin(); i != materials.end(); i++)
    {
        tracer.addPhongShader(i.key(), i.value().diffuseColor());
    }

    // Copy polygons
    for (int i = 0; i < polygons.length(); i++)
    {
        SPolygon polygon = polygons.at(i);

        if (polygon.useNormals())
        {
            tracer.addPolygon(polygon.v1(), polygon.v2(), polygon.v3(),
                              polygon.n1(), polygon.n2(), polygon.n3(), polygon.materialName());
        }
        else
        {
            tracer.addPolygon(polygon.v1(), polygon.v2(), polygon.v3(), polygon.materialName());
        }
    }

    // Copy lamps
    for (int i = 0; i < lights.length(); i++)
    {
        tracer.addPointLight(lights.at(i));
    }
}

void SScene::copyToTracer(HTracer3 &tracer, const QString &shader)
{
    // Copy polygons
    for (int i = 0; i < polygons.length(); i++)
    {
        SPolygon polygon = polygons.at(i);

        if (polygon.useNormals())
        {
            tracer.addPolygon(polygon.v1(), polygon.v2(), polygon.v3(),
                              polygon.n1(), polygon.n2(), polygon.n3(), shader);
        }
        else
        {
            tracer.addPolygon(polygon.v1(), polygon.v2(), polygon.v3(), shader);
        }
    }

    // Copy lamps
    for (int i = 0; i < lights.length(); i++)
    {
        tracer.addPointLight(lights.at(i));
    }
}

bool SScene::loadMtl(const QString &fileName)
{
    QFile inputFile(fileName);
    bool isOpenSucces = inputFile.open(QIODevice::ReadOnly);

    if (!isOpenSucces)
    {
        return false;
        qDebug() << QString("Can not open file: %0").arg(fileName);
    }

    QTextStream inputStream(&inputFile);

    bool isFirstMaterial = true;
    QString materialName;
    QColor diffuseColor;

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        QStringList params = line.split(' ');

        // New material header declaration
        if (params[0] == "newmtl")
        {
            if (!isFirstMaterial)
            {
                materials.insert(materialName, SMaterial(diffuseColor));
            }
            else
            {
                isFirstMaterial = false;
            }

            materialName = params[1];
        }

        // Diffuse color declaration
        if (params[0] == "Kd")
        {
            float r = params[1].toFloat();
            float g = params[2].toFloat();
            float b = params[3].toFloat();
            diffuseColor = QColor::fromRgb(255 * r, 255 * g, 255 * b);
        }
    }

    inputFile.close();
    return true;
}

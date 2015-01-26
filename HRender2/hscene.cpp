//#include "hscene.h"

//HScene::HScene()
//{

//}

//HScene::HScene(const HScene &scene)
//{
//    for (int i = 0; i < scene.colliders.length(); i++)
//        colliders.append(scene.colliders.at(i)->clone());

////    setTreeHead(scene.treeHead()->clone());
//    treeHead_ = scene.treeHead_->clone();
//}

//HScene::~HScene()
//{
//    destructTree();
//    destructColliders();
//}

//HScene &HScene::operator =(const HScene &scene)
//{
//    for (int i = 0; i < scene.colliders.length(); i++)
//        colliders.append(scene.colliders.at(i)->clone());

////    setTreeHead(scene.treeHead()->clone());
//    treeHead_ = scene.treeHead_->clone();
//    lamps = scene.lamps;

//    return *this;
//}

//void HScene::transform(const QMatrix4x4 &matrix)
//{
//    for (int i = 0; i < colliders.length(); i++)
//        colliders[i]->transform(matrix);

//    for (int i = 0; i < lamps.length(); i++)
//        lamps[i] = matrix * lamps[i];
//}

//void HScene::buildTree()
//{
//    QVector<ICollider *> collidersClone;

//    for (int i = 0; i < colliders.length(); i++)
//        collidersClone.append(colliders.at(i)->clone());

//    for (int i = 0; i < collidersClone.length(); i++)
//    {
//        HBoundingSphereCollider *hbsc = new HBoundingSphereCollider();
//        hbsc->addCollider(collidersClone.at(i));
//        collidersClone[i] = hbsc;
//    }

//    while (collidersClone.length() != 1)
//    {
//        int i = qrand() % (collidersClone.length() - 1) + 1;

//        ICollider *first = collidersClone[i], *second = collidersClone[0];
//        float dist = first->getBoundingSphereCenter().distanceToPoint(second->getBoundingSphereCenter());

//        for (int j = 1; j < collidersClone.length(); j++)
//        {
//            if (i != j)
//            {
//                if (dist > collidersClone[i]->getBoundingSphereCenter().distanceToPoint(collidersClone[j]->getBoundingSphereCenter()))
//                {
//                    first = collidersClone[i];
//                    second = collidersClone[j];
//                    dist = first->getBoundingSphereCenter().distanceToPoint(second->getBoundingSphereCenter());
//                }
//            }
//        }

//        collidersClone.removeOne(first);
//        collidersClone.removeOne(second);

//        HBoundingSphereCollider *hbsc = new HBoundingSphereCollider();
//        hbsc->addCollider(first);
//        hbsc->addCollider(second);

//        collidersClone.append(hbsc);
//    }

//    setTreeHead(collidersClone[0]);
////    ICollider * c = treeHead_->clone();
////    delete treeHead_;
////    treeHead_ = c;
//}

//void HScene::destructTree()
//{
//    delete treeHead();
//}

//void HScene::loadObj(QString filename)
//{
//    QFile inputFile(filename);
//    inputFile.open(QIODevice::ReadOnly);
//    QTextStream in(&inputFile);

//    QVector<QVector3D> vertexes;
////    HMaterial *defaultMaterial = new HMaterial();

//    while (!in.atEnd())
//    {
//        QString line = in.readLine();
//        QStringList list = line.split(' ');

//        if (list[0] == "v")
//        {
//            float a = list[1].toFloat();
//            float b = list[2].toFloat();
//            float c = list[3].toFloat();
//            vertexes.append(QVector3D(a, b, c));
//        }

//        if (list[0] == "f")
//        {
//            for (int i = 2; i < list.length() - 1; i++)
//            {
//                QVector3D p1 = vertexes[list[1].toInt() - 1];
//                QVector3D p2 = vertexes[list[i].toInt() - 1];
//                QVector3D p3 = vertexes[list[i + 1].toInt() - 1];
//                colliders.append(new HPolygonCollider(p1, p2, p3));
//            }
//        }
//    }

//    inputFile.close();
//}

//void HScene::destructColliders()
//{
//    for (int i = 0; i < colliders.length(); i++)
//        delete colliders.at(i);

//    colliders.clear();
//}

//ICollider *HScene::treeHead() const
//{
//    return treeHead_;
//}

//void HScene::setTreeHead(ICollider *treeHead)
//{
//    treeHead_ = treeHead;
//}

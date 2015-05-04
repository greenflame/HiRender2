#include "hbvh.h"

HBVH::HBVH()
{
    boundingTreeHead_ = 0;
}

HBVH::~HBVH()
{
    clear();
}

void HBVH::build(const QVector<ICollider *> colliders)
{
    clear();

    QVector<ICollider *> collidersClones;

    for (int i = 0; i < colliders.length(); i++)
    {
        HBoundingSphereCollider *hbsc = new HBoundingSphereCollider();
        hbsc->addCollider(colliders.at(i)->clone());

        collidersClones.append(hbsc);
    }

    while (collidersClones.length() != 1)
    {
        int closestToFirstIndex = 1;

        float dist = collidersClones.at(0)->getBoundingSphere().center()
                .distanceToPoint(collidersClones.at(closestToFirstIndex)->getBoundingSphere().center());

        for (int i = 1; i < collidersClones.length(); i++)
        {
            float currentDist = collidersClones.at(0)->getBoundingSphere().center()
                    .distanceToPoint(collidersClones.at(i)->getBoundingSphere().center());

            if (currentDist < dist)
            {
                closestToFirstIndex = i;
                dist = currentDist;
            }
        }

        HBoundingSphereCollider *hbsc = new HBoundingSphereCollider();
        hbsc->addCollider(collidersClones.at(0));
        hbsc->addCollider(collidersClones.at(closestToFirstIndex));

        collidersClones.removeAt(closestToFirstIndex);
        collidersClones.removeAt(0);

        collidersClones.append(hbsc);
    }

    boundingTreeHead_ = collidersClones.at(0);
}

void HBVH::clear()
{
    if (boundingTreeHead_ != 0)
    {
        delete boundingTreeHead_;
        boundingTreeHead_ = 0;
    }
}

ICollider *HBVH::head() const
{
    return boundingTreeHead_;
}

bool HBVH::isEmpty() const
{
    return boundingTreeHead_ == 0;
}

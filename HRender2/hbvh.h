#ifndef HBVH_H
#define HBVH_H

#include <colliders/hcolliders.h>

class HBVH
{
public:
    HBVH();
    ~HBVH();

    void build(const QVector<ICollider *> colliders);
    void clear();

    ICollider *head() const;
    bool isEmpty() const;

private:
    ICollider *boundingTreeHead_;
};

#endif // HBVH_H

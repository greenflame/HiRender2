/*
 * Tile controller. Divide image into tiles.
 */

#ifndef HTILECONTROLLER_H
#define HTILECONTROLLER_H

#include <QSize>
#include <QRect>
#include <QVector>

#include <cmath>

class HTileController
{
public:
    HTileController();
    HTileController(QSize imageSize, QSize tileSize);
    ~HTileController();

    bool getNextTile(QRect &rect);
    void clearTiles();

    QSize imageSize() const;
    void setImageSize(const QSize &imageSize);

    QSize tileSize() const;
    void setTileSize(const QSize &tileSize);

private:
    QSize imageSize_;
    QSize tileSize_;

    QVector<bool> tileMap_;
    QSize tilesCount_;
    int renderedTiles_;

    static float distance(const QPoint &p1, const QPoint &p2);

};

#endif // HTILECONTROLLER_H

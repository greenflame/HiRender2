#include "htilecontroller.h"

HTileController::HTileController()
{
    setImageSize(QSize(0, 0));
    setTileSize(QSize(0, 0));

    clearTiles();
}

HTileController::HTileController(QSize imageSize, QSize tileSize)
{
    setImageSize(imageSize);
    setTileSize(tileSize);

    clearTiles();
}

HTileController::~HTileController()
{

}

bool HTileController::getNextTile(QRect &rect)
{
    QPoint midleTile(tilesCount_.width() / 2, tilesCount_.height() / 2);
    QPoint closestTile;
    bool isImageFinished = true;

    for (int y = 0; y < tilesCount_.height(); y++)
        for (int x = 0; x < tilesCount_.width(); x++)
        {
            QPoint currentTile(x, y);
            bool isCurrentTileRendered = tileMap_[y * tilesCount_.width() + x];
            if (!isCurrentTileRendered)
            {
                if (isImageFinished)
                {
                    isImageFinished = false;
                    closestTile = currentTile;
                }
                else
                {
                    if (distance(midleTile, currentTile) < distance(midleTile, closestTile))
                    {
                        closestTile = currentTile;
                    }
                }
            }
        }

    if (isImageFinished)
        return false;

    tileMap_[closestTile.y() * tilesCount_.width() + closestTile.x()] = true;

    int x = closestTile.x() * tileSize_.width();
    int y = closestTile.y() * tileSize_.height();

    rect = QRect(x, y,
                 qMin(tileSize_.width(), imageSize_.width() - x),
                 qMin(tileSize_.height(), imageSize_.height() - y));
    return true;
}

void HTileController::clearTiles()
{
    tilesCount_.setWidth(imageSize().width() / tileSize().width() +
            (imageSize().width() % tileSize().width() == 0 ? 0 : 1));

    tilesCount_.setHeight(imageSize().height() / tileSize().height() +
            (imageSize().height() % tileSize().height() == 0 ? 0 : 1));

    renderedTiles_ = 0;

    int n = tilesCount_.width() * tilesCount_.height();
    tileMap_ = QVector<bool>(n);

    for (int i = 0; i < n; i++)
        tileMap_[i] = false;
}

QSize HTileController::imageSize() const
{
    return imageSize_;
}

void HTileController::setImageSize(const QSize &imageSize)
{
    imageSize_ = imageSize;
    clearTiles();
}
QSize HTileController::tileSize() const
{
    return tileSize_;
}

void HTileController::setTileSize(const QSize &tileSize)
{
    tileSize_ = tileSize;
    clearTiles();
}

float HTileController::distance(const QPoint &p1, const QPoint &p2)
{
    float x = p1.x() - p2.x();
    float y = p1.y() - p2.y();
    return sqrt(x * x + y * y);
}

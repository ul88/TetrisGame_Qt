#ifndef BLOCK_H
#define BLOCK_H

#include <QQuickPaintedItem>

class Block : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
    QML_ELEMENT
public:
    explicit Block(QQuickItem* parent = nullptr);

    void paint(QPainter* painter) override;

    QColor color() const {return m_color;}
    void setColor(const QColor& color);
public slots:

signals:
    void colorChanged();
private:
    QColor m_color;
};

#endif // BLOCK_H

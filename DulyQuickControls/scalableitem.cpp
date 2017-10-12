#include "scalableitem.h"

ScalableItem::ScalableItem(QQuickItem *parent) :
    QQuickItem(parent),
    m_scaleFactor(1),
    m_realPos(-100000, -100000)
{

}

QPointF ScalableItem::scalePos() const 
{
	return m_realPos * m_scaleFactor + QPointF((width() * m_scaleFactor - width()) / 2, (height() * m_scaleFactor - height()) / 2);
}

QPointF ScalableItem::realPos() const
{
	return (position() / m_scaleFactor) + QPointF((width() / m_scaleFactor - width()) / 2, (height() / m_scaleFactor - height()) / 2);
}

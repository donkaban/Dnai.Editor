#include <QtQuick/qsgnode.h>
#include <QtMath>
#include <QSGVertexColorMaterial>

#include "io.h"
#include "dulycanvas.h"

BaseIo *Io::CurrentHover = nullptr;

Io::Io(QQuickItem *parent) :
    LinkableBezierItem(parent)
  , m_nbSegments(32)
  , m_type(DulyResources::IOType::Int)

{
	Io::refreshBackendIo();
    setFlag(ItemHasContents, true);
    setAntialiasing(true);
}

Io::~Io()
{
}

void Io::refreshBackendIo()
{
}

QSGNode *Io::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    const char r = m_fillColor.red();
    const char g = m_fillColor.green();
    const char b = m_fillColor.blue();
    const char alpha = m_fillColor.alpha();
    if (m_nbSegments != 0 && m_nbSegments % 2 != 0)
        ++m_nbSegments;

    const char rb = m_borderColor.red();
    const char gb = m_borderColor.green();
    const char bb = m_borderColor.blue();
    const char alphab = m_borderColor.alpha();

    const auto aa = antialiasing();
    QSGGeometryNode *node;
    QSGGeometry *geometry;

    setWidth((m_radius + m_radius / 2.5f) * 2);
    setHeight((m_radius + m_radius / 2.5f) * 2);
    const uint nbVertices = (aa?(m_borderWidth > 0 ? 8.0f * (m_nbSegments + 1):4 * (m_nbSegments + 1)):(m_borderWidth > 0?6 * (m_nbSegments + 1):2.5f * (m_nbSegments + 1))) + 1;
    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(),  nbVertices);
        geometry->setLineWidth(1);
        geometry->setDrawingMode(QSGGeometry::DrawTriangleStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
	    auto material = new QSGVertexColorMaterial;
        material->setFlag(QSGMaterial::Blending);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(nbVertices);
    }
    const auto cx = width() / 2;
    const auto cy = height() / 2;
    const auto a = float(2 * M_PI) / m_nbSegments;
    const qreal aaoffset = 1;
	const auto vertices = geometry->vertexDataAsColoredPoint2D();
	auto idx = -1;
    for (uint i = 0; i <= m_nbSegments; i++)
    {
        if (aa)
        {
            if (i % 2 == 0)
            {
                vertices[++idx].set( cx, cy, r, g, b, alpha);

                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * i), cy +  (m_radius + aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy +  (m_radius + aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * i), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * i), cy + (m_radius + m_borderWidth) * qFastSin(a * i), 0, 0, 0, 0);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
                }
                else
                {
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * i), cy +  (m_radius + aaoffset) * qFastSin(a * i), 0, 0, 0, 0);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy +  (m_radius + aaoffset) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
                }
            }
            else
            {
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), 0, 0, 0, 0);

                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * i), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth - aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth - aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);

                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * i), cy +  (m_radius + aaoffset) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy +  (m_radius + aaoffset) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                }
                else
                {
                    vertices[++idx].set( cx + (m_radius + aaoffset) * qFastCos(a * (i + 1)), cy + (m_radius + aaoffset) * qFastSin(a * (i + 1)), 0, 0, 0, 0);
                }
                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
            }
        }
        else
        {
            if (i % 2 == 0)
            {
                vertices[++idx].set( cx, cy, r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * i), cy + (m_radius + m_borderWidth) * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                }
            }
            else
            {
                if (m_borderWidth > 0)
                {
                    vertices[++idx].set( cx + (m_radius + m_borderWidth) * qFastCos(a * (i + 1)), cy + (m_radius + m_borderWidth) * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), rb, gb, bb, alphab);
                    vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), rb, gb, bb, alphab);
                }
                vertices[++idx].set( cx + m_radius * qFastCos(a * i), cy + m_radius * qFastSin(a * i), r, g, b, alpha);
                vertices[++idx].set( cx + m_radius * qFastCos(a * (i + 1)), cy + m_radius * qFastSin(a * (i + 1)), r, g, b, alpha);
            }
        }
    }

    return node;
}

void Io::setNbSegments(uint n)
{
    if (n == m_nbSegments)
        return;
    m_nbSegments = n;
    emit nbSegmentsChanged(n);
    update();
}

void Io::setType(DulyResources::IOType type)
{
    if (type == m_type)
        return;
    m_type = type;
    refreshBackendIo();
    emit typeChanged(type);
    update();
}

QPointF Io::getCanvasPos() const
{
    return QPointF(parentItem()->parentItem()->parentItem()->parentItem()->parentItem()->position() +
		parentItem()->parentItem()->parentItem()->parentItem()->position() +
		parentItem()->parentItem()->parentItem()->position() +
		parentItem()->parentItem()->position() +
		parentItem()->position() + position() + QPointF(width() / 2, height() / 2));
}

GenericNode* Io::getNode() const
{
	return dynamic_cast<GenericNode *>(parentItem()->parentItem()->parentItem()->parentItem()->parentItem());
}
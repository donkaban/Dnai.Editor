#include "dnai/models/position.h"

namespace dnai {
    namespace models {
		const QList<QString> &Position::m_editableProperties = {
			"position"
		};
        Position::Position(QVector2D const &position) : m_position(position)
        {

        }

        QVector2D Position::position() const
        {
            return m_position;
        }

        void Position::setPosition(const QVector2D &position)
        {
            m_position = position;
        }

        void Position::serialize(QJsonObject &obj) const
        {
            obj["position"] = QJsonObject {
                {"x", static_cast<double>(m_position.x())},
                {"y", static_cast<double>(m_position.y())}
            };
        }

	    const QList<QString>& Position::editableProperties()
	    {
			return m_editableProperties;
	    }

	    void Position::declare() const
        {

        }

        IClone *Position::clone() const
        {
            return new Position(m_position);
        }
    }
}

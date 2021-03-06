#ifndef DNAI_MODELS_DECLARABLE_LISTTYPE_H
#define DNAI_MODELS_DECLARABLE_LISTTYPE_H

#include "dnai/models/gui/data/listtype.h"
#include "entity.h"
#include <QObject>

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				class ListType : public QObject, public Entity<data::ListType, ListType>
				{
                    Q_OBJECT
                    Q_PROPERTY(QUuid storedType READ storedType NOTIFY storedTypeChanged)

				public:
                    explicit ListType() = default;
					//Implementation of ISerializable
					void serialize(QJsonObject& obj) const override;
				protected:
					void _deserialize(const QJsonObject& obj) override;

                public:
                    QUuid storedType() const;
                    void setStoredType(QUuid const &value);

                signals:
                    void storedTypeChanged(QUuid type);
				};
			}
		}
	}
}

#endif //DNAI_MODELS_DECLARABLE_LISTTYPE_H

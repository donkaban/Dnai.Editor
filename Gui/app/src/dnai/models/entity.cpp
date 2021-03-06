#include <QQmlEngine>
#include <QJsonArray>

#include "dnai/utils/random_utils.h"

#include "dnai/models/entity.h"
#include "dnai/models/gui/declarable/variable.h"
#include "dnai/models/gui/declarable/context.h"
#include "dnai/models/gui/entitylist.h"

#include "dnai/core/handlermanager.h"
#include "dnai/utils/random_utils.h"
#include "core.h"

namespace dnai
{
	namespace models
	{
		//EntityList *Entity::m_entities = new EntityList(new QList<models::Entity *>());

        Entity::Entity(gcore::Entity *coremodel, Entity *parent, interfaces::IEntity *guimodel, QUuid const &guid) :
            IModel(parent),
            m_dataCore(coremodel),
            m_dataGUI(guimodel),
            m_guid(guid)
        {
			const QList<QPair<QObject *, QString>> props = {
				{ this, "name" },
				{ this, "description" },
				{ this, "visibility" },
				{ this, "entityType" }
			};
            QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
            if (m_guid.isNull())
                m_guid = utils::generateUid();
        }

		Entity::~Entity()
        {
            qDebug() << "~ Entity: " << name();
			delete m_dataCore;
			delete m_dataGUI;
		}

		bool Entity::isRoot() const
		{
			return m_isRoot;
		}

		void Entity::setIsRoot(bool isRoot)
		{
			if (m_isRoot == isRoot)
				return;
			m_isRoot = isRoot;
			emit isRootChanged(isRoot);
		}

        qint32 Entity::id() const
		{
			return coreModel()->id();
		}

        qint32 Entity::containerId() const
		{
			return coreModel()->containerId();
		}

		qint32 Entity::entityType() const
		{
            return static_cast<qint32>(coreModel()->entityType());
		}

		const QString& Entity::name() const
		{
            return coreModel()->name();
        }

        const QString Entity::fullName() const
        {
            if (parentItem() == nullptr || isRoot())
                return coreModel() ? name() : "";
            return parentItem()->fullName() + "." + name();
        }

        const QString Entity::childFullName(const QString &childName) const
        {
            return fullName() + "." + childName;
        }

        qint32 Entity::visibility() const
		{
			return static_cast<qint32>(coreModel()->visibility());
		}

		int Entity::index() const
		{
			return m_dataGUI->index();
		}

		QString Entity::listIndex() const
		{
			return m_dataGUI->listIndex().toString();
		}

		const QString& Entity::description() const
		{
			return m_dataGUI->description();
		}

        gcore::Entity* Entity::coreModel() const
		{
			return m_dataCore;
		}

        interfaces::IEntity *Entity::guiModel() const
        {
            return m_dataGUI;
        }

		bool Entity::expanded() const
		{
			return m_dataGUI->expanded();
		}

		void Entity::setExpanded(bool exp)
		{
			if (guiModel()->setExpanded(exp))
			{
				emit expandedChanged(exp);
			}
        }

        QUuid Entity::guid() const
        {
            return m_guid;
        }

		Entity* Entity::parentRef() const
		{
			return parentItem();
		}

		const QMap<QUuid, Column*>& Entity::columns()
		{
			return m_columns;
		}

		void Entity::setId(qint32 id)
		{
			if (coreModel()->setId(id))
			{
				emit idChanged(id);
			}
		}

        void Entity::setContainerId(qint32 containerId) const
		{
			if (coreModel()->setContainerId(containerId))
			{
				emit containerIdChanged(containerId);
			}
		}

		void Entity::setEntityType(qint32 type) const
		{
            if (coreModel()->setEntityType(static_cast<::core::ENTITY>(type)))
			{
				emit entityTypeChanged(type);
			}
		}

		void Entity::setName(const QString& name) const
		{
			if (coreModel()->setName(name))
            {
				emit nameChanged(name);
			}
		}

        void Entity::setVisibility(qint32 v) const
        {
            if (coreModel()->setVisibility(static_cast<core::VISIBILITY>(v)))
			{
				
                emit Entity::visibilityChanged(v);
			}
		}

		void Entity::setIndex(int index)
		{
			if (m_dataGUI->setIndex(index))
			{
				emit indexChanged(index);
			}
		}

		void Entity::setListIndex(const QString &listIndex)
		{
			if (m_dataGUI->setListIndex(listIndex))
			{
				emit listIndexChanged(listIndex);
			}
		}

		void Entity::setDescription(const QString& description)
		{
			if (m_dataGUI->setDescription(description))
			{
				emit descriptionChanged(description);
			}
		}

        void Entity::setCoreModel(gcore::Entity* model)
		{
			if (m_dataCore == model)
				return;
			m_dataCore = model;
			emit coreModelChanged(model);
		}

		void Entity::appendChild(Entity* child)
		{
			GenericTreeItem<Entity>::appendChild(child);
			const auto uuid = QUuid(child->guiModel()->listIndex());
			if (m_columns.find(uuid) == m_columns.end())
			{
                const auto c = new Column(this);
				c->setListIndex(uuid.toString());
				m_columslist.append(c);
				m_columns[uuid] = c;
			}
			m_columns[uuid]->append(child);
			emit entityChildrenChanged(child);
		}

		QObject* Entity::guiProperties() const
		{
			return dynamic_cast<QObject*>(m_dataGUI);
		}

		void Entity::setListColumn(const QVariant& column)
		{
			Q_UNUSED(column);
		}

		void Entity::serialize(QJsonObject& obj) const
		{
			QJsonArray ca;
			for (auto c : m_columns)
			{
				QJsonObject tmp;
				c->serialize(tmp);
				ca.append(tmp);
			}
			obj["columns"] = ca;
			if (m_dataCore == nullptr) return;
			m_dataCore->serialize(obj);
			m_dataGUI->serialize(obj);
			QJsonArray ea;
            for (auto child : childrenItem())
			{
				QJsonObject o;
				child->serialize(o);
				ea.append(o);
			}
			obj["entities"] = ea;
            obj["guid"] = m_guid.toString();
		}

		void Entity::_deserialize(const QJsonObject& obj)
		{
            foreach(const auto column, obj["columns"].toArray()) {
                auto p = this;
                const auto col = Column::deserialize(column.toObject(), p);
                m_columns[col->datas().listIndex] = col;
				m_columslist.append(col);
			}
			m_dataCore->setName(obj["name"].toString());
            m_dataCore->setVisibility(static_cast<::core::VISIBILITY>(obj["visibility"].toInt()));
            switch (m_dataCore->entityType())
            {
            case ::core::ENTITY::UNDEFINED: break;
            case ::core::ENTITY::CONTEXT:
            {
                m_dataGUI = gui::declarable::Context::deserialize(obj);
                break;
            }
            case ::core::ENTITY::VARIABLE:
            {
                m_dataGUI = gui::declarable::Variable::deserialize(obj);
                break;
            }
            case ::core::ENTITY::FUNCTION:
            {
                m_dataGUI = gui::declarable::Function::deserialize(obj);
                break;
            }
            case ::core::ENTITY::DATA_TYPE: break;
            case ::core::ENTITY::ENUM_TYPE:
            {
                m_dataGUI = gui::declarable::EnumType::deserialize(obj);
                break;
            }
            case ::core::ENTITY::OBJECT_TYPE:
            {
                m_dataGUI = gui::declarable::ObjectType::deserialize(obj);
                break;
            }
            case ::core::ENTITY::LIST_TYPE:
            {
                m_dataGUI = gui::declarable::ListType::deserialize(obj);
                break;
            }
            default: ;
            }
			
            foreach(const auto classe, obj["entities"].toArray()) {
				QJsonObject o = classe.toObject();
                const auto coreModel = new models::gcore::Entity(static_cast<::core::ENTITY>(o["type"].toInt()));
                Entity *parent = this;
                const auto entity = Entity::deserialize(o, coreModel, parent);
				if (QUuid(entity->listIndex()).isNull() && !m_columns.empty())
					entity->setListIndex(m_columns.keys().first().toString());
				appendChild(entity);
            }

            if (obj.contains("guid"))
                m_guid = obj["guid"].toString();
        }

		int Entity::columnCount() const
		{
			return 1;
		}

		const QVariant &Entity::listColumn()
		{
			m_varcolumns = QVariant::fromValue(m_columslist);
			return m_varcolumns;
        }

		void Entity::addColumn(const QString& name)
		{
            const auto c = new Column(this);
            const auto uuid = utils::generateUid();

			c->setListIndex(uuid.toString());
			c->setName(name);
			m_columslist.append(c);
            m_columns[uuid] = c;

			emit listColumnChanged(listColumn());
		}

		int Entity::row() const
		{
			return IModel<Entity>::row();
		}

        Entity *Entity::findByName(const QString &name) const
        {
            for (Column *curr : m_columns)
            {
                for (models::Entity *entity : curr->getEntities())
                {
                    if (entity->name() == name)
                        return entity;
                }
            }
            return nullptr;
        }

        quint32 Entity::findIdByName(const QString &name) const
        {
            models::Entity *ent = findByName(name);

            if (ent == nullptr)
                return static_cast<quint32>(-1);
            return ent->id();
        }

		QHash<int, QByteArray> Column::roleNames() const
		{
			QHash<int, QByteArray> roles;
			roles[ROLES::ENTITIES] = "entities";
			return roles;
		}

		void Column::serialize(QJsonObject& obj) const
		{
			obj["name"] = m_data.name;
			obj["description"] = m_data.description;
            obj["listIndex"] = m_data.listIndex.toString();
		}

		void Column::_deserialize(const QJsonObject& obj)
		{
			m_data.name = obj["name"].toString();
			m_data.description = obj["description"].toString();
            m_data.listIndex = QUuid(obj["listIndex"].toString());
            if (m_data.listIndex.isNull())
            {
                m_data.listIndex = utils::generateUid();
                qDebug() << "==Entity== List index is null: Generating " << m_data.listIndex;
            }
		}

		const gui::data::EntityColumn& Column::datas() const
		{
			return m_data;
		}

		bool Column::setDatas(const gui::data::EntityColumn& data)
		{
            if (m_data == data)
                return false;
            m_data = data;
            return true;
        }

        const QList<Entity *> &Column::getEntities() const
        {
            return m_entities;
        }

		//EntityList::EntityList(QList<models::Entity*>*l) : QAbstractListModel(nullptr)
		//{
		//	m_list = l;
		//}

		//int EntityList::rowCount(const QModelIndex& parent) const
		//{
		//	return m_list->count();
		//}

		//QVariant EntityList::data(const QModelIndex& index, const int role) const
		//{
		//	if (!index.isValid())
		//		return QVariant();
		//	if (role == Name)
		//		return QVariant::fromValue(m_list->at(index.row())->name());
		//	else if (role == Type)
		//		return QVariant::fromValue(dynamic_cast<gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->varType());
		//	return QVariant();
		//}

		//void EntityList::add(models::Entity *var)
		//{
		//	beginInsertRows(QModelIndex(), m_list->length(), m_list->length());
		//	/*auto input = new gui::declarable::Variable();
		//	auto entity = new models::Entity(new gcore::Entity(::core::ENTITY::VARIABLE));
		//	entity->setGuiModel(input);
		//	input->setVarType(varType);
		//	if (name.isEmpty())
		//	entity->setName(QString("Empty : ") + QString::number(m_list->count()));
		//	else
		//	entity->setName(name);*/
		//	m_list->append(var);
		//	endInsertRows();
		//}

		//void EntityList::moveUp(const int index)
		//{
		//	if (index < 0)
		//		return;
		//	const auto start = index % m_list->length();
		//	const auto end = (start <= 0) ? m_list->length() - 1 : start - 1;
		//	beginMoveRows(QModelIndex(), start, start, QModelIndex(), start == 0 ? m_list->length() : end);
		//	m_list->swap(start, end);
		//	endMoveRows();
		//}

		//void EntityList::moveDown(const int index)
		//{
		//	if (index < 0)
		//		return;
		//	const auto start = index % m_list->length();
		//	const auto end = (start + 1) % m_list->length();
		//	beginMoveRows(QModelIndex(), start, start, QModelIndex(), end == 0 ? 0 : end + 1);
		//	m_list->swap(start, end);
		//	endMoveRows();
		//}

		//void EntityList::remove(const QString& name)
		//{
		//	auto index = 0;
		//	for (auto i : *m_list)
		//	{
		//		if (i->name() == name)
		//			break;
		//		index++;
		//	}
		//	beginRemoveRows(QModelIndex(), index, index);
		//	m_list->removeAt(index);
		//	endRemoveRows();
		//}

		//bool EntityList::setData(const QModelIndex& index, const QVariant& value, int role)
		//{
		//	auto result = false;
		//	if (role == Name)
		//	{
		//		m_list->at(index.row())->setName(value.toString());
		//		result = true;
		//	}
		//	else if (role == Type)
		//		result = dynamic_cast<models::gui::declarable::Variable*>(m_list->at(index.row())->guiModel())->setVarType(value.toInt());
		//	if (result)
		//		emit dataChanged(index, index);

		//	return result;
		//}

		//bool EntityList::setData(const int index, const QVariant& value, int role)
		//{
		//	return setData(createIndex(index, 0), value, role);
		//}

		//QHash<int, QByteArray> EntityList::roleNames() const {
		//	QHash<int, QByteArray> roles;
		//	roles[Name] = "name";
		//	roles[Type] = "varType";
		//	return roles;
		//}


		Column::Column(Entity *e, QObject* parent) : QAbstractListModel(parent), m_target(nullptr)
		{
			m_parent = e;
		}

        int Column::rowCount(const QModelIndex& parent) const
		{
            Q_UNUSED(parent)
			return m_entities.count();
		}

        QVariant Column::data(const QModelIndex& index, int role) const
		{
			if (!index.isValid())
				return QVariant();
			if (role == ENTITIES)
				return QVariant::fromValue(m_entities[index.row()]);
			return QVariant();
		}

        void Column::append(Entity* e, const QModelIndex &parent)
		{
			if (!m_entities.contains(e))
			{
				beginInsertRows(parent, rowCount(), rowCount());
				m_entities.append(e);
				endInsertRows();
			}
		}

        void Column::remove(Entity* e, const QModelIndex &parent)
		{
			if (!m_entities.contains(e))
				return;
			const auto pos = m_entities.indexOf(e);
			beginRemoveRows(parent, pos, pos);
			m_entities.removeOne(e);
			endRemoveRows();
		}

		const QString& Column::name() const
		{
			return m_data.name;
		}

		const QString& Column::description() const
		{
			return m_data.description;
		}

		void Column::setName(const QString& name)
		{
			if (m_data.name == name)
				return;
			m_data.name = name;
			emit nameChanged(name);
		}

		void Column::setDescription(const QString& description)
		{
			if (m_data.description == description)
				return;
			m_data.description = description;
			emit descriptionChanged(description);
		}

		QString Column::listIndex() const
		{
			return m_data.listIndex.toString();
		}

		void Column::setListIndex(const QString& s)
		{
			if (m_data.listIndex.toString() == s)
				return;
			m_data.listIndex = QUuid::fromString(s);
			emit listIndexChanged(s);
		}

		Entity* Column::parentRef() const
        {
            return m_parent;
		}

		void Entity::setGuiModel(interfaces::IEntity* model)
		{
			m_dataGUI = model;
		}
	}
}

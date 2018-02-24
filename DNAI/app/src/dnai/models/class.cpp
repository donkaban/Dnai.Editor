#include <QJsonArray>

#include "dnai/models/class.h"
#include "dnai/controllers/clientcontroller.h"

namespace dnai {
    namespace models {
		QList<QString> Class::m_editableProperties = {};
        Class::Class(const qint32 uid, QString const &name, QString const &description, QVector2D const &position, const int index, const int listindex, QObject *parent)
            : Common(uid, name, description, index, listindex, parent), Position(position)
        {
            m_type = ModelTypes::Class;
        }

        Class::~Class() = default;

	    QList<Variable*> Class::attributes() const
        {
            return m_attributes;
        }
        
        QList<Function*> Class::methods() const
        {
            return m_methods;
        }
        
        QList<Function*> Class::functions() const
        {
            return m_functions;
        }

        QList<Class*> Class::classes() const
        {
            return m_classes;
        }

        void Class::addAttribute(Variable *model)
        {
            m_attributes.push_back(model);
        }

        void Class::addMethod(Function *model)
        {
            m_methods.push_back(model);
        }

        void Class::addFunction(Function *model)
        {
            m_functions.push_back(model);
        }

        void Class::addClass(Class *model)
        {
            m_classes.push_back(model);
        }

        void Class::removeAttribute(Variable *model)
        {
            m_attributes.removeOne(model);
        }

        void Class::removeMethod(Function *model)
        {
            m_methods.removeOne(model);
        }

        void Class::removeFunction(Function *model)
        {
            m_functions.removeOne(model);
        }

        void Class::removeClass(Class *model)
        {
            m_classes.removeOne(model);
        }

        void Class::serialize(QJsonObject &obj) const
        {
            Common::serialize(obj);
            Position::serialize(obj);

            QJsonArray attributes;
            foreach (const Variable *attribute, m_attributes) {
                QJsonObject var;
                attribute->serialize(var);
                attributes.append(var);
            }

            QJsonArray methods;
            foreach (const Function *method, m_methods) {
                QJsonObject var;
                method->serialize(var);
                methods.append(var);
            }

            QJsonArray functions;
            foreach (const Function *function, m_functions) {
                QJsonObject var;
                function->serialize(var);
                functions.append(var);
            }

            QJsonArray classes;
            foreach (const Class *classe, m_classes) {
                QJsonObject var;
                classe->serialize(var);
                classes.append(var);
            }

            obj["attributes"] = attributes;
            obj["methods"] = methods;
            obj["functions"] = functions;
            obj["classes"] = functions;
        }

        void Class::declare() const
        {
            controllers::ClientController::shared().sendDeclareEvent(PackageDataCom::ENTITYCORE::OBJECT_TYPE, 0, name(), PackageDataCom::VISIBILITYCORE::PUBLIC);
        }

	    const QList<QString> &Class::editableProperties()
	    {
			if (m_editableProperties.empty())
				m_editableProperties += Common::m_editableProperties + Position::m_editableProperties;
			return m_editableProperties;
		}

	    IClone *Class::clone() const
        {
            return new Class(uid(),name(), description(), position(), index(), listIndex());
        }
    }
}

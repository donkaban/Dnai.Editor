#include "dnai/models/gui/declarable/function.h"

#include <QJsonArray>
#include <QDebug>
#include "dnai/models/entity.h"
#include "dnai/models/gui/instruction.h"
#include "dnai/models/gui/entitylist.h"

namespace dnai
{
	namespace models
	{
		namespace gui
		{
			namespace declarable
			{
				Function::Function(QObject* parent) : QObject(parent)
				{
					m_finputs = new EntityList(&m_data.inputs);
					m_foutputs = new EntityList(&m_data.outputs);
				}

				void Function::serialize(QJsonObject& obj) const
				{	
					Entity::serialize(obj);
                    QJsonArray instructions;
                    foreach(const auto instruction, m_data.instructions) {
                        QJsonObject var;
                        instruction->serialize(var);
                        instructions.append(var);
                    }
                    obj["inputs"] = serializeList<models::Entity>(m_data.inputs);
                    obj["outputs"] = serializeList<models::Entity>(m_data.outputs);
                    obj["instructions"] = instructions;
				}

				void Function::_deserialize(const QJsonObject& obj)
				{
					Entity::_deserialize(obj);

					foreach(auto input, obj["inputs"].toArray()) {
						const auto core = new gcore::Entity(::core::ENTITY::VARIABLE);
						auto ent = models::Entity::deserialize(input.toObject(), core);
                        m_data.inputs.append(ent);
					}

					foreach(auto output, obj["outputs"].toArray()) {
						const auto core = new gcore::Entity(::core::ENTITY::VARIABLE);
						auto ent = models::Entity::deserialize(output.toObject(), core);
						m_data.outputs.append(ent);
					}

					foreach(auto node, obj["instructions"].toArray()) {
						addInstruction(Instruction::deserialize(node.toObject()));
					}
				}

				const QList<models::Entity*>& Function::inputs() const
				{
					return m_data.inputs;
				}

				bool Function::setInputs(const QList<models::Entity*>& inputs)
				{
					if (m_data.inputs == inputs)
						return false;
					m_data.inputs = inputs;
					return true;
				}

				const QList<models::Entity*> &Function::outputs() const
				{
					return m_data.outputs;
				}

				bool Function::setOutputs(const QList<models::Entity*>& outputs)
				{
					if (m_data.outputs == outputs)
						return false;
					m_data.outputs = outputs;
					return true;
				}

				const QList<models::gui::Instruction*>& Function::instructions() const
				{
					return m_data.instructions;
				}

                void Function::addInput(models::Entity *var)
				{
					for (auto i : m_data.inputs)
					{
                        if (i->name() == var->name())
							return;
					}
                    m_finputs->append(var);
					emit inputModelsChanged(m_finputs);
				}

                void Function::addOutput(models::Entity *var)
				{
					for (auto i : m_data.outputs)
					{
                        if (i->name() == var->name())
							return;
					}
                    m_foutputs->append(var);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::removeInput(const QString& name)
				{
					m_finputs->remove(name);
					emit inputModelsChanged(m_finputs);
				}

				void Function::removeOutput(const QString& name)
				{
					m_foutputs->remove(name);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::moveInputUp(const int index)
				{
					m_finputs->moveUp(index);
					emit inputModelsChanged(m_finputs);
				}

				void Function::moveOutputUp(const int index)
				{
					m_foutputs->moveUp(index);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::moveInputDown(const int index)
				{
					m_finputs->moveDown(index);
					emit inputModelsChanged(m_finputs);
				}

				void Function::moveOutputDown(const int index)
				{
					m_foutputs->moveDown(index);
					emit outputModelsChanged(m_foutputs);
				}

                /*void Function::updateInputName(const int index, const QString& name)
				{
					m_finputs->setData(index, name, FunctionInputs::Name);
					emit inputModelsChanged(m_finputs);
				}

				void Function::updateInputVarType(const int index, const qint32 varType)
				{
					m_finputs->setData(index, varType, FunctionInputs::Type);
					emit inputModelsChanged(m_finputs);
				}

				void Function::updateOutputName(const int index, const QString& name)
				{
					m_foutputs->setData(index, name, FunctionInputs::Name);
					emit outputModelsChanged(m_foutputs);
				}

				void Function::updateOutputVarType(const int index, const qint32 varType)
				{
					m_foutputs->setData(index, varType, FunctionInputs::Type);
					emit outputModelsChanged(m_foutputs);
                }*/

				EntityList *Function::inputModels() const
				{
					return m_finputs;
				}

				EntityList *Function::outputModels() const
				{
					return m_foutputs;
				}

				void Function::setInputModels(EntityList* inputs)
				{
					if (inputs == m_finputs)
						return;
					m_finputs = inputs;
					emit inputModelsChanged(inputs);
				}

				void Function::setOutputModels(EntityList* outputs)
				{
					if (outputs == m_foutputs)
						return;
					m_foutputs = outputs;
					emit outputModelsChanged(outputs);
				}

				void Function::addInstruction(Instruction* instruction)
				{
					m_data.instructions.append(instruction);
				}
                quint32 Function::getInputId(const QString &name) const
                {
                    for (models::Entity *curr : inputs())
                    {
                        if (curr->name() == name)
                            return curr->id();
                    }
                    return core::UNDEFINED_ID;
                }

                quint32 Function::getOutputId(const QString &name) const
                {
                    for (models::Entity *curr : outputs())
                    {
                        if (curr->name() == name)
                            return curr->id();
                    }
                    return core::UNDEFINED_ID;
                }
			}
		}
	}
}

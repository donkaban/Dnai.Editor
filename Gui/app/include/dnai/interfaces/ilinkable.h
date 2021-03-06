#ifndef DNAI_INTERFACES_ILINKABLE_H
#define DNAI_INTERFACES_ILINKABLE_H
#include <QtCore/QList>

namespace dnai {
    namespace views {
        class BezierCurve;
    }

	class Link;
    namespace interfaces {
        class ILinkable
        {
        public:
            virtual ~ILinkable() = default;

            virtual void unlinkAll() = 0;

            virtual bool isLink() = 0;
        };

        class ALinkable : public ILinkable
        {
        public:
            virtual ~ALinkable() {
                m_links.clear();
            }
            /**
            * \brief return all the list of Link
            * \return QList<Link *>
            */
            const QList<Link *> &links() const { return m_links; }

            /**
            * \brief Connect linkable together, create a link, and keep a reference on the visual curve
            * \param linkable
            * \param curve
            * \return Link *
            */
            virtual Link *connect(ALinkable *linkable, views::BezierCurve *curve) = 0;

            virtual Link *asyncConnect(ALinkable *linkable) = 0;

            /**
            * \brief Break a link between linkable
            * \param linkable
            */
            virtual void unlink(ALinkable *linkable) = 0;

            /**
            * \brief Break all the links between linkable
            */
            virtual void unlinkAll() override = 0;

            /**
            * \brief Add a link
            * \param l
            */
            virtual void addLink(Link *l) = 0;

            /**
            * \brief Remove a link
            * \param l
            */
            virtual void removeLink(Link *l) = 0;

            /**
            * \brief is linkable is actually
            * \return bool
            */
            virtual bool isLink() override = 0;

            /**
            * \brief return the link between this and linkable
            * \param linkable
            * \return Link *
            */
            virtual Link *getLink(ALinkable *linkable) const = 0;


        protected:
            QList<Link *> m_links;
        };
    }
}

#endif // ILINKABLE_H

/**
 * Copyright 2013 Truphone
 */
#ifndef LISTCOMMAND_H_
#define LISTCOMMAND_H_

#include <bb/cascades/AbstractPane>
#include <bb/cascades/ListView>

#include "Command.h"
#include "Buffer.h"

namespace truphone
{
namespace test
{
namespace cascades
{
    /*!
     * \brief The List class is used to check and manipulate lists
     *
     * @since test-cascades 1.0.5
     */
    class ListCommand : public Command
    {
    Q_OBJECT
    public:
        /*!
         * \brief getCmd Return the name of this command
         *
         * \return Command name
         *
         * @since test-cascades 1.0.5
         */
        static QString getCmd()
        {
            return CMD_NAME;
        }
        /*!
         * \brief create Create a new instance of this Command
         *
         * \param s The TCP socket associated with the client
         * \param parent The parent object
         * \return Returns a new instance of the Command
         *
         * @since test-cascades 1.0.5
         */
        static Command* create(class Connection * const s,
                               QObject * parent = 0)
        {
            return new ListCommand(s, parent);
        }
        /*!
         * \brief ListCommand Constructor
         *
         * \param socket The TCP socket associated with the client
         * \param parent The parent object
         *
         * @since test-cascades 1.0.5
         */
        ListCommand(class Connection * const socket,
                      QObject* parent = 0);
        /*!
         * \brief ~ListCommand Destructor
         *
         * @since test-cascades 1.0.5
         */
        ~ListCommand();
        /*
         * See super
         */
        bool executeCommand(QStringList * const rguments);
        /*
         * See super
         */
        void cleanUp(void)
        {
            /* do nothing */
        }
        /*
         * See super
         */
        void showHelp(void);
    protected slots:
    private:
        bool findElementByIndex(
                const QString& index,
                QVariantList& elementIndexPath) const;

        bool findElementByName(
                bb::cascades::ListView * const list,
                const QString& index,
                QVariantList& elementIndexPath) const;

        bool checkElement(
                const QVariant element,
                const QString& check = 0) const;

        static void normalisePath(QString& value);

        static QString extractNamedPath(
                QStringList * const arguments,
                const char * const endOfPath);

        bool selectUnselectPath(
                QStringList * const arguments,
                bb::cascades::ListView * const listView,
                const bool select);

        bool scrollToPath(
                QStringList * const arguments,
                bb::cascades::ListView * const listView);

        bool showKeysOnPath(
                QStringList * const arguments,
                bb::cascades::ListView * const listView);

        /*!
         * \brief CMD_NAME The name of this command
         */
        static const QString CMD_NAME;
        /*!
         * \brief client The TCP socket associated with the client
         */
        class Connection * const client;
        /*!
         * \brief scenePane The scene that we're working with
         */
        bb::cascades::AbstractPane * const scenePane;
        /*!
         * @brief namedPathEnd Path end marker
         */
        const Buffer namedPathEnd;
        /*!
         * \brief namedPathSep Path/Index separator
         */
        const Buffer namedPathSep;
        /*!
         * \brief assignSep Assignment separator
         */
        const Buffer assignSep;
    };
}  // namespace cascades
}  // namespace test
}  // namespace truphone

#endif  // LISTCOMMAND_H_

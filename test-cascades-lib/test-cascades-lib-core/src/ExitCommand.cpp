/**
 * Copyright 2013 Truphone
 */
#include "ExitCommand.h"

#include <QString>
#include <QList>
#include <QObject>

#include "Connection.h"

namespace truphone
{
namespace test
{
namespace cascades
{
    const QString ExitCommand::CMD_NAME = "exit";

    ExitCommand::ExitCommand(Connection * const socket,
                             QObject* parent)
        : Command(parent),
          client(socket),
          isHelp(false)
    {
    }

    ExitCommand::~ExitCommand()
    {
    }

    bool ExitCommand::executeCommand(QStringList * const arguments)
    {
        Q_UNUSED(arguments);
        return true;
    }

    void ExitCommand::cleanUp(void)
    {
        if (not isHelp)
        {
            this->client->close();
        }
        else
        {
            this->deleteLater();
        }
    }

    void ExitCommand::showHelp()
    {
        isHelp = true;
        this->client->write(tr("> exit") + "\r\n");
        this->client->write(tr("Terminate this connection to the server") + "\r\n");
    }
}  // namespace cascades
}  // namespace test
}  // namespace truphone

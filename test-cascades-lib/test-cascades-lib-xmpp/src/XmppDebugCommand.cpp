/**
 * Copyright 2014 Truphone
 */
#include "XmppDebugCommand.h"

#include <QString>
#include <QObject>
#include <QXmppClient.h>

#include "Connection.h"
#include "XmppResourceStore.h"

namespace truphone
{
namespace test
{
namespace cascades
{
    bool XMPPDebugCommand::debuggingEnabled = false;
    QList<class Connection*> XMPPDebugCommand::debugClientList;

    const QString XMPPDebugCommand::CMD_NAME = "xmppDebug";

    XMPPDebugCommand::XMPPDebugCommand(Connection * const socket,
                                             QObject* parent)
        : Command(parent),
          client(socket)
    {
    }

    XMPPDebugCommand::~XMPPDebugCommand()
    {
    }

    bool XMPPDebugCommand::executeCommand(QStringList * const arguments)
    {
        bool ret = false;
        if (arguments->length() not_eq 1)
        {
            this->client->write(tr("ERROR: xmppDebug <on | off>") + "\r\n");
        }
        else
        {
            const QString enabled = arguments->first();
            if (enabled == "on")
            {
                debugClientList.append(this->client);
                debuggingEnabled = true;
                ret = true;
            }
            else if (enabled == "off")
            {
                debugClientList.removeAll(this->client);
                debuggingEnabled = false;
                ret = true;
            }
            else
            {
                this->client->write(tr("ERROR: Unable to parse on or off option") + "\r\n");
            }
        }
        return ret;
    }

    bool XMPPDebugCommand::isDebugEnabled()
    {
        return debuggingEnabled;
    }

    QList<class Connection*> XMPPDebugCommand::debugClients()
    {
        return debugClientList;
    }

    void XMPPDebugCommand::showHelp()
    {
        this->client->write(tr("> xmppDebug <on | off>") + "\r\n");
        this->client->write(tr("Enable printing of XMPP XML to network stream.") + "\r\n");
    }
}  // namespace cascades
}  // namespace test
}  // namespace truphone

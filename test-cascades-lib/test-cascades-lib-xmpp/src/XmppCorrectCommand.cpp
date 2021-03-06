/**
 * Copyright 2014 Truphone
 */
#include "XmppCorrectCommand.h"

#include <QString>
#include <QObject>
#include <QXmppClient.h>
#include <QXmppMessage.h>

#include "Connection.h"
#include "XmppResourceStore.h"
#include "XmppDebugCommand.h"
#include "XmppPrintCommand.h"

namespace truphone
{
namespace test
{
namespace cascades
{
    const QString XMPPCorrectCommand::CMD_NAME = "xmppCorrect";

    XMPPCorrectCommand::XMPPCorrectCommand(Connection * const socket,
                                             QObject* parent)
        : Command(parent),
          client(socket)
    {
    }

    XMPPCorrectCommand::~XMPPCorrectCommand()
    {
    }

    bool XMPPCorrectCommand::executeCommand(QStringList * const arguments)
    {
        bool ret = false;
        if (arguments->length() < 1)
        {
            this->client->write(tr("ERROR: xmppCorrect <resource> <optional: message>") + "\r\n");
        }
        else
        {
            QXmppClient * const client =
                    XMPPResourceStore::instance()->getFromStore(arguments->first());
            arguments->removeFirst();
            if (client)
            {
                QSharedPointer<QXmppStanza> lastSentStanza
                        = XMPPResourceStore::instance()->getLastMessageSent(client);
                if (lastSentStanza)
                {
                    QSharedPointer<QXmppMessage> lastSentMessage =
                            lastSentStanza.dynamicCast<QXmppMessage>();
                    if (not (lastSentMessage->body().isNull()
                          or lastSentMessage->body().isEmpty()))
                    {
                        QXmppMessage correctedMessage;
                        // correction fields
                        correctedMessage.setReceiptId(lastSentMessage->id());
                        correctedMessage.setReplace(lastSentMessage->id());
                        correctedMessage.setBody(arguments->join(" "));
                        correctedMessage.setTo(lastSentMessage->to());
                        // normal messaging
                        correctedMessage.setId(QUuid::createUuid().toString());
                        correctedMessage.setThread("");
                        correctedMessage.setState(QXmppMessage::Active);
                        correctedMessage.addHint(QXmppMessage::AllowPermantStorage);
                        if (XMPPDebugCommand::isDebugEnabled())
                        {
                            XMPPPrintCommand::printMessage(
                                        true,
                                        &correctedMessage);
                        }
                        ret = client->sendPacket(correctedMessage);
                        if (not ret)
                        {
                            this->client->write(tr("ERROR: Failed to send packet") + "\r\n");
                        }
                        else
                        {
                            XMPPResourceStore::instance()->setLastMessageSent(
                                        client, correctedMessage);
                        }
                    }
                    else
                    {
                        this->client->write(tr(
                                    "ERROR: The previous message has no body to correct") + "\r\n");
                    }
                }
                else
                {
                    this->client->write(tr("ERROR: No previous sent message to correct") + "\r\n");
                }
            }
            else
            {
                this->client->write(tr("ERROR: Unknown resource") + "\r\n");
            }
        }
        return ret;
    }

    void XMPPCorrectCommand::showHelp()
    {
        this->client->write(tr("> xmppCorrect <resource> <optional: message>") + "\r\n");
        this->client->write(tr("Corrects the last message sent. If <message> is missing")
                            + "\r\n");
        this->client->write(tr("then it's treated as a deletion of the previous message.")
                            + "\r\n");
    }
}  // namespace cascades
}  // namespace test
}  // namespace truphone

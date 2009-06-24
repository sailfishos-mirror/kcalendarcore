/*
    Copyright 2009 Constantin Berzan <exit3219@gmail.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef OUTBOXINTERFACE_SENTCOLLECTIONATTRIBUTE_H
#define OUTBOXINTERFACE_SENTCOLLECTIONATTRIBUTE_H

#include <outboxinterface/outboxinterface_export.h>

#include <akonadi/attribute.h>
#include <akonadi/collection.h>


namespace OutboxInterface
{


/**
 * Attribute storing the id of the sent-mail collection for a message.  The
 * dispatcher agent will move the item to that collection after it is sent.
 */
class OUTBOXINTERFACE_EXPORT SentCollectionAttribute : public Akonadi::Attribute
{
  public:
    explicit SentCollectionAttribute( Akonadi::Collection::Id id = -1 );
    virtual ~SentCollectionAttribute();

    virtual SentCollectionAttribute* clone() const;
    virtual QByteArray type() const;
    virtual QByteArray serialized() const;
    virtual void deserialize( const QByteArray &data );

    Akonadi::Collection::Id sentCollection() const;
    void setSentCollection( Akonadi::Collection::Id id );

  private:
    Akonadi::Collection::Id mId;

};


}


#endif
/*
  This file is part of the kcalcore library.

  SPDX-FileCopyrightText: 2002, 2006, 2010 David Jarvie <djarvie@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
/*
  @file
  This file is part of the API for handling calendar data and
  defines the CustomProperties class.
*/

#ifndef KCALCORE_CUSTOMPROPERTIES_H
#define KCALCORE_CUSTOMPROPERTIES_H

#include "kcalendarcore_export.h"

#include <QMap>
#include <QString>

namespace KCalendarCore
{
/*!
  \class KCalendarCore::CustomProperties
  \inmodule KCalendarCore
  \inheaderfile KCalendarCore/CustomProperties
  \brief
  A class to manage custom calendar properties.

  This class represents custom calendar properties.
  It is used as a base class for classes which represent calendar components.
  A custom property name written by the kcalcore library has the form X-KDE-APP-KEY
  where APP represents the application name, and KEY distinguishes individual
  properties for the application.
  In keeping with RFC2445, property names must be composed only of the
  characters A-Z, a-z, 0-9 and '-'.
*/
class KCALENDARCORE_EXPORT CustomProperties
{
    friend KCALENDARCORE_EXPORT QDataStream &operator<<(QDataStream &s, const KCalendarCore::CustomProperties &properties);
    friend KCALENDARCORE_EXPORT QDataStream &operator>>(QDataStream &s, KCalendarCore::CustomProperties &properties);

public:
    /*!
      Constructs an empty custom properties instance.
    */
    CustomProperties();

    /*!
      Copy constructor.

      \a other is the one to copy.

    */
    CustomProperties(const CustomProperties &other);

    /*!
      Destructor.
    */
    virtual ~CustomProperties();

    /*!
      Compare this with \a properties for equality.

      \a properties is the one to compare.

      \warning The comparison is not polymorphic.

      Returns true if \a properties is equal to this object, or false if not
    */
    bool operator==(const CustomProperties &properties) const;

    /*!
      Create or modify a custom calendar property.

      \a app   Application name as it appears in the custom property name.

      \a key   Property identifier specific to the application.

      \a value The property's value. A call with a value of QString()
      will be ignored.

      \sa removeCustomProperty().
    */
    void setCustomProperty(const QByteArray &app, const QByteArray &key, const QString &value);

    /*!
      Delete a custom calendar property.

      \a app Application name as it appears in the custom property name.

      \a key Property identifier specific to the application.

      \sa setCustomProperty().
    */
    void removeCustomProperty(const QByteArray &app, const QByteArray &key);

    /*!
      Return the value of a custom calendar property.

      \a app Application name as it appears in the custom property name.

      \a key Property identifier specific to the application.

      Returns Property value, or QString() if (and only if) the property
      does not exist.
    */
    Q_REQUIRED_RESULT QString customProperty(const QByteArray &app, const QByteArray &key) const;

    /*!
      Validate and return the full name of a custom calendar property.

      \a app Application name as it appears in the custom property name.

      \a key Property identifier specific to the application.

      Returns Full property name, or empty string if it would contain invalid
              characters
    */
    Q_REQUIRED_RESULT static QByteArray customPropertyName(const QByteArray &app, const QByteArray &key);

    /*!
      Create or modify a non-KDE or non-standard custom calendar property.

      \a name Full property name

      \a value The property's value. A call with a value of QString()
      will be ignored.

      \a parameters The formatted list of parameters for the
      property. They should be formatted as RFC specifies, that is,
      KEY=VALUE;KEY2=VALUE2. We're mostly concerned about passing them
      through as-is albeit they can be of course parsed if need be.

      \sa removeNonKDECustomProperty().
    */
    void setNonKDECustomProperty(const QByteArray &name, const QString &value, const QString &parameters = QString());

    /*!
      Delete a non-KDE or non-standard custom calendar property.

      \a name Full property name

      \sa setNonKDECustomProperty().
    */
    void removeNonKDECustomProperty(const QByteArray &name);

    /*!
      Return the value of a non-KDE or non-standard custom calendar property.

      \a name Full property name

      Returns Property value, or QString() if (and only if) the property
      does not exist.
    */
    Q_REQUIRED_RESULT QString nonKDECustomProperty(const QByteArray &name) const;

    /*!
      Return the parameters of a non-KDE or non-standard custom
      calendar property.

      \a name Full property name

      Returns The parameters for the given property. Empty string is
      returned if none are set.
    */
    Q_REQUIRED_RESULT QString nonKDECustomPropertyParameters(const QByteArray &name) const;

    /*!
      Initialise the alarm's custom calendar properties to the specified
      key/value pairs.

      \a properties is a QMap of property key/value pairs.

      \sa customProperties().
    */
    void setCustomProperties(const QMap<QByteArray, QString> &properties);

    /*!
      Returns all custom calendar property key/value pairs.
      \sa setCustomProperties().
    */
    Q_REQUIRED_RESULT QMap<QByteArray, QString> customProperties() const;

    /*!
      Assignment operator.
      \warning The assignment is not polymorphic.

      \a other is the CustomProperty to assign.

    */
    CustomProperties &operator=(const CustomProperties &other);

protected:
    /*!
      Called before a custom property will be changed.
      The default implementation does nothing: override in derived classes
      to perform change processing.
    */
    virtual void customPropertyUpdate();

    /*!
      Called when a custom property has been changed.
      The default implementation does nothing: override in derived classes
      to perform change processing.
    */
    virtual void customPropertyUpdated();

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};

/*!
  Serializes the \a properties object into the \a stream.
*/
KCALENDARCORE_EXPORT QDataStream &operator<<(QDataStream &stream, const KCalendarCore::CustomProperties &properties);

/*!
  Initializes the \a properties object from the \a stream.
*/
KCALENDARCORE_EXPORT QDataStream &operator>>(QDataStream &stream, KCalendarCore::CustomProperties &properties);

}

#endif

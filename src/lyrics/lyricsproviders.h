/*
 * Strawberry Music Player
 * Copyright 2018-2021, Jonas Kvinge <jonas@jkvinge.net>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LYRICSPROVIDERS_H
#define LYRICSPROVIDERS_H

#include "config.h"

#include <QtGlobal>
#include <QObject>
#include <QMutex>
#include <QList>
#include <QMap>
#include <QString>
#include <QAtomicInt>

class NetworkAccessManager;
class LyricsProvider;

class LyricsProviders : public QObject {
  Q_OBJECT

 public:
  explicit LyricsProviders(QObject *parent = nullptr);
  ~LyricsProviders() override;

  void ReloadSettings();
  LyricsProvider *ProviderByName(const QString &name) const;

  void AddProvider(LyricsProvider *provider);
  void RemoveProvider(LyricsProvider *provider);
  QList<LyricsProvider*> List() const { return lyrics_providers_.keys(); }
  bool HasAnyProviders() const { return !lyrics_providers_.isEmpty(); }
  int NextId();

  NetworkAccessManager *network() const { return network_; }

 private slots:
  void ProviderDestroyed();

 private:
  Q_DISABLE_COPY(LyricsProviders)

  static int NextOrderId;

  NetworkAccessManager *network_;

  QMap<LyricsProvider*, QString> lyrics_providers_;
  QList<LyricsProvider*> ordered_providers_;
  QMutex mutex_;

  QAtomicInt next_id_;
};

#endif  // LYRICSPROVIDERS_H

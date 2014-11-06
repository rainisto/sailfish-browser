/****************************************************************************
**
** Copyright (C) 2014 Jolla Ltd.
** Contact: Raine Makelainen <raine.makelainen@jollamobile.com>
**
****************************************************************************/

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef DECLARATIVEWEBPAGE_H
#define DECLARATIVEWEBPAGE_H

#include <qqml.h>
#include <QPointer>
#include <quickmozview.h>

class DeclarativeWebContainer;

class DeclarativeWebPage : public QuickMozView {
    Q_OBJECT
    Q_PROPERTY(DeclarativeWebContainer* container READ container NOTIFY containerChanged FINAL)
    Q_PROPERTY(int tabId READ tabId NOTIFY tabIdChanged FINAL)
    Q_PROPERTY(bool viewReady MEMBER m_viewReady NOTIFY viewReadyChanged FINAL)
    Q_PROPERTY(bool loaded MEMBER m_loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(bool userHasDraggedWhileLoading MEMBER m_userHasDraggedWhileLoading NOTIFY userHasDraggedWhileLoadingChanged FINAL)
    Q_PROPERTY(bool fullscreen READ fullscreen NOTIFY fullscreenChanged FINAL)
    Q_PROPERTY(bool forcedChrome READ forcedChrome NOTIFY forcedChromeChanged FINAL)
    Q_PROPERTY(QString favicon MEMBER m_favicon NOTIFY faviconChanged FINAL)
    Q_PROPERTY(QVariant resurrectedContentRect READ resurrectedContentRect WRITE setResurrectedContentRect NOTIFY resurrectedContentRectChanged)

    Q_PROPERTY(qreal fullscreenHeight MEMBER m_fullScreenHeight NOTIFY fullscreenHeightChanged FINAL)
    Q_PROPERTY(qreal toolbarHeight MEMBER m_toolbarHeight NOTIFY toolbarHeightChanged FINAL)

public:
    DeclarativeWebPage(QQuickItem *parent = 0);
    ~DeclarativeWebPage();

    DeclarativeWebContainer* container() const;
    void setContainer(DeclarativeWebContainer *container);

    int tabId() const;
    void setTabId(int tabId);

    QVariant resurrectedContentRect() const;
    void setResurrectedContentRect(QVariant resurrectedContentRect);

    bool fullscreen() const;
    bool forcedChrome() const;
    bool domContentLoaded() const;

    bool urlHasChanged() const;
    void setUrlHasChanged(bool urlHasChanged);

    bool backForwardNavigation() const;
    void setBackForwardNavigation(bool backForwardNavigation);

    bool viewReady() const;

    Q_INVOKABLE void loadTab(QString newUrl, bool force);
    Q_INVOKABLE void forceChrome(bool forcedChrome);

public slots:
    void resetHeight(bool respectContentHeight = true);

signals:
    void containerChanged();
    void tabIdChanged();
    void viewReadyChanged();
    void loadedChanged();
    void userHasDraggedWhileLoadingChanged();
    void fullscreenChanged();
    void forcedChromeChanged();
    void domContentLoadedChanged();
    void faviconChanged();
    void resurrectedContentRectChanged();

    void fullscreenHeightChanged();
    void toolbarHeightChanged();

protected:
    void componentComplete();

private slots:
    void setFullscreen(const bool fullscreen);
    void onRecvAsyncMessage(const QString& message, const QVariant& data);
    void onViewInitialized();

private:
    QPointer<DeclarativeWebContainer> m_container;
    int m_tabId;
    bool m_viewReady;
    bool m_loaded;
    bool m_userHasDraggedWhileLoading;
    bool m_fullscreen;
    bool m_forcedChrome;
    bool m_domContentLoaded;
    bool m_urlHasChanged;
    bool m_backForwardNavigation;
    QString m_favicon;
    QVariant m_resurrectedContentRect;

    qreal m_fullScreenHeight;
    qreal m_toolbarHeight;
};

QDebug operator<<(QDebug, const DeclarativeWebPage *);

QML_DECLARE_TYPE(DeclarativeWebPage)

#endif

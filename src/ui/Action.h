/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2017 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_ACTION_H
#define OTTER_ACTION_H

#include "../core/ActionsManager.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QShortcut>

namespace Otter
{

class Action : public QAction
{
	Q_OBJECT

public:
	explicit Action(int identifier, QObject *parent = nullptr);

	void setOverrideText(const QString &text);
	void setState(const ActionsManager::ActionDefinition::State &state);
	void setParameters(const QVariantMap &parameters);
	QString getText() const;
	ActionsManager::ActionDefinition::State getState() const;
	QVariantMap getParameters() const;
	QVector<QKeySequence> getShortcuts() const;
	int getIdentifier() const;
	bool event(QEvent *event) override;
	static bool calculateCheckedState(const QVariantMap &parameters, Action *action = nullptr);
	static bool isLocal(int identifier);

public slots:
	void setup(Action *action = nullptr);

protected:
	void update(bool reset = false);

private:
	QString m_overrideText;
	QVariantMap m_parameters;
	int m_identifier;
	bool m_isOverridingText;
};

class Shortcut : public QShortcut
{
	Q_OBJECT

public:
	explicit Shortcut(int identifier, const QKeySequence &sequence, QWidget *parent = nullptr);

	void setParameters(const QVariantMap &parameters);
	QVariantMap getParameters() const;
	int getIdentifier() const;

private:
	QVariantMap m_parameters;
	int m_identifier;
};

}

#endif
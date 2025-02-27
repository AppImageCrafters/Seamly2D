/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                            *
 *                                                                         *
 ***************************************************************************
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 **************************************************************************

 ************************************************************************
 **
 **  @file   vcommonsettings.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   15 7, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "vcommonsettings.h"

#include <QApplication>
#include <QDate>
#include <QDir>
#include <QLocale>
#include <QMessageLogger>
#include <QStaticStringData>
#include <QStringData>
#include <QStringDataPtr>
#include <QVariant>
#include <QtDebug>
#include <QTextCodec>
#include <QFont>

#include "../vmisc/def.h"
#include "../vmisc/vmath.h"
#include "../vpatterndb/pmsystems.h"

namespace
{
const QString settingPathsIndividualMeasurements         = QStringLiteral("paths/individual_measurements");
const QString settingPathsMultisizeMeasurements          = QStringLiteral("paths/standard_measurements");
const QString settingPathsTemplates                      = QStringLiteral("paths/templates");
const QString settingPathsLabelTemplate                  = QStringLiteral("paths/labels");

const QString settingConfigurationOsSeparator            = QStringLiteral("configuration/osSeparator");
const QString settingConfigurationAutosaveState          = QStringLiteral("configuration/autosave/state");
const QString settingConfigurationAutosaveTime           = QStringLiteral("configuration/autosave/time");
const QString settingConfigurationSendReportState        = QStringLiteral("configuration/send_report/state");
const QString settingConfigurationLocale                 = QStringLiteral("configuration/locale");
const QString settingPMSystemCode                        = QStringLiteral("configuration/pmscode");
const QString settingConfigurationUnit                   = QStringLiteral("configuration/unit");
const QString settingConfigurationConfirmItemDeletion    = QStringLiteral("configuration/confirm_item_deletion");
const QString settingConfigurationConfirmFormatRewriting = QStringLiteral("configuration/confirm_format_rewriting");

const QString settingGraphicsViewToolBarStyle            = QStringLiteral("graphicsview/tool_bar_style");
const QString settingGraphicsViewShowScrollBars          = QStringLiteral("graphicsview/showScrollBars");
const QString settingGraphicsViewScrollBarWidth          = QStringLiteral("graphicsview/scrollBarWidth");
const QString settingGraphicsViewScrollDuration          = QStringLiteral("graphicsview/scrollDuration");
const QString settingGraphicsViewScrollUpdateInterval    = QStringLiteral("graphicsview/scrollUpdateInterval");
const QString settingGraphicsViewScrollSpeedFactor       = QStringLiteral("graphicsview/scrollSpeedFactor");
const QString settingGraphicsViewPixelDelta              = QStringLiteral("graphicsview/pixelDelta");
const QString settingGraphicsViewAngleDelta              = QStringLiteral("graphicsview/angleDelta");
const QString settingGraphicsViewZoomModKey              = QStringLiteral("graphicsview/zoomModKey");
const QString settingGraphicsViewZoomDoubleClick         = QStringLiteral("graphicsview/zoomDoubleClick");
const QString settingGraphicsViewZoomSpeedFactor         = QStringLiteral("graphicsview/zoomSpeedFactor");

const QString settingGraphicsViewZoomRBPositiveColor     = QStringLiteral("graphicsview/zoomRBPositiveColor");
const QString settingGraphicsViewZoomRBNegativeColor     = QStringLiteral("graphicsview/zoomRBNegativeColor");
const QString settingGraphicsViewPointNameColor          = QStringLiteral("graphicsview/pointNameColor");
const QString settingGraphicsViewPointNameHoverColor     = QStringLiteral("graphicsview/pointNameHoverColor");
const QString settingGraphicsViewAxisOrginColor          = QStringLiteral("graphicsview/axisOrginColor");

const QString settingGraphicsViewConstrainValue          = QStringLiteral("graphicsview/constrainValue");
const QString settingGraphicsViewConstrainModKey         = QStringLiteral("graphicsview/constrainModKey");

const QString settingGraphicsViewPointNameSize           = QStringLiteral("graphicsview/pointNameSize");
const QString settingGraphicsViewGuiFontSize             = QStringLiteral("graphicsview/guiFontSize");
const QString settingGraphicsViewHidePointNames          = QStringLiteral("graphicsview/hidePointNames");
const QString settingGraphicsViewShowAxisOrigin          = QStringLiteral("graphicsview/showAxisOrigin");
const QString settingGraphicsViewWireframe               = QStringLiteral("graphicsview/wireframe");
const QString settingGraphicsViewShowControlPoints       = QStringLiteral("graphicsview/showControlPoints");
const QString settingGraphicsViewShowAnchorPoints        = QStringLiteral("graphicsview/showAnchorPoints");
const QString settingGraphicsUseToolColor                = QStringLiteral("graphicsview/useToolColor");

const QString settingPatternUndo                         = QStringLiteral("pattern/undo");
const QString settingPatternForbidFlipping               = QStringLiteral("pattern/forbidFlipping");
const QString settingPatternHideMainPath                 = QStringLiteral("pattern/hideMainPath");

const QString settingDefaultNotchLength                  = QStringLiteral("pattern/defaultNotchLength");
const QString settingDefaultNotchWidth                   = QStringLiteral("pattern/defaultNotchWidth");
const QString settingDefaultNotchType                    = QStringLiteral("pattern/defaultNotchType");
const QString settingDoubleNotch                         = QStringLiteral("pattern/doubleNotch");

const QString settingPatternDefaultSeamAllowance         = QStringLiteral("pattern/defaultSeamAllowance");
const QString settingPatternLabelFont                    = QStringLiteral("pattern/labelFont");
const QString settingPatternGuiFont                      = QStringLiteral("pattern/guiFont");
const QString settingPatternPointNameFont                = QStringLiteral("pattern/pointNameFont");

const QString settingGeneralRecentFileList               = QStringLiteral("recentFileList");
const QString settingGeneralRestoreFileList              = QStringLiteral("restoreFileList");
const QString settingGeneralGeometry                     = QStringLiteral("geometry");
const QString settingGeneralWindowState                  = QStringLiteral("windowState");
const QString settingGeneralToolbarsState                = QStringLiteral("toolbarsState");
const QString settingPreferenceDialogSize                = QStringLiteral("preferenceDialogSize");
const QString settingToolSeamAllowanceDialogSize         = QStringLiteral("toolSeamAllowanceDialogSize");
const QString settingIncrementsDialogSize                = QStringLiteral("toolIncrementsDialogSize");
const QString settingFormulaWizardDialogSize             = QStringLiteral("formulaWizardDialogSize");
const QString settingLatestSkippedVersion                = QStringLiteral("lastestSkippedVersion");
const QString settingDateOfLastRemind                    = QStringLiteral("dateOfLastRemind");

const QString settingCSVWithHeader                       = QStringLiteral("csv/withHeader");
const QString settingCSVCodec                            = QStringLiteral("csv/withCodec");
const QString settingCSVSeparator                        = QStringLiteral("csv/withSeparator");

const QString settingLabelDateFormat                     = QStringLiteral("label/dateFormat");
const QString settingLabelUserDateFormats                = QStringLiteral("label/userDateFormats");
const QString settingLabelTimeFormat                     = QStringLiteral("label/timeFormat");
const QString settingLabelUserTimeFormats                = QStringLiteral("label/userTimeFormats");

int pointNameSize = 0;

//---------------------------------------------------------------------------------------------------------------------
QStringList ClearFormats(const QStringList &predefinedFormats, QStringList formats)
{
    for (int i = 0; i < predefinedFormats.size(); ++i)
    {
        formats.removeAll(predefinedFormats.at(i));
    }
    return formats;
}
}

static const QString commonIniFilename = QStringLiteral("common");

#if !defined(Q_OS_WIN)
const QString VCommonSettings::unixStandardSharePath = QStringLiteral("/usr/share/seamly2d");
#endif

namespace
{
//---------------------------------------------------------------------------------------------------------------------
void SymlinkCopyDirRecursive(const QString &fromDir, const QString &toDir, bool replaceOnConflit)
{
    QDir dir;
    dir.setPath(fromDir);

    foreach (QString copyFile, dir.entryList(QDir::Files))
    {
        const QString from = fromDir + QDir::separator() + copyFile;
        QString to = toDir + QDir::separator() + copyFile;

#ifdef Q_OS_WIN
        {
            // To fix issue #702 check each not symlink if it is actually broken symlink.
            // Also trying to mimic Unix symlink. If a file eaxists do not create a symlink and remove it if exists.
            QFile fileTo(to);
            if (fileTo.exists())
            {
                if (not fileTo.rename(to + QLatin1String(".lnk")))
                {
                    QFile::remove(to + QLatin1String(".lnk"));
                    fileTo.rename(to + QLatin1String(".lnk"));
                }

                QFileInfo info(to + QLatin1String(".lnk"));
                if (info.symLinkTarget().isEmpty())
                {
                    fileTo.copy(to);
                    fileTo.remove();
                    continue; // The file already exists, skip creating shortcut
                }
            }
        }

        to = to + QLatin1String(".lnk");
#endif

        if (QFile::exists(to))
        {
            if (replaceOnConflit)
            {
                QFile::remove(to);
            }
            else
            {
                continue;
            }
        }

        QFile::link(from, to);
    }

    foreach (QString copyDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        const QString from = fromDir + QDir::separator() + copyDir;
        const QString to = toDir + QDir::separator() + copyDir;

        if (dir.mkpath(to) == false)
        {
            return;
        }

        SymlinkCopyDirRecursive(from, to, replaceOnConflit);
    }
}

//---------------------------------------------------------------------------------------------------------------------
QString PrepareStandardFiles(const QString &currentPath, const QString &standardPath, const QString &defPath)
{
    QDir standardPathDir(standardPath);
    QDir currentPathDir(currentPath);
    if ((currentPath == defPath || not currentPathDir.exists()) && standardPathDir.exists())
    {
        const QDir localdata (defPath);
        if (localdata.mkpath("."))
        {
            SymlinkCopyDirRecursive(standardPath, defPath, false);
        }
        return defPath;
    }
    return currentPath;
}
}

//---------------------------------------------------------------------------------------------------------------------
VCommonSettings::VCommonSettings(Format format, Scope scope, const QString &organization,
                            const QString &application, QObject *parent)
    :QSettings(format, scope, organization, application, parent)
{}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::SharePath(const QString &shareItem)
{
#ifdef Q_OS_WIN
    return QCoreApplication::applicationDirPath() + shareItem;
#elif defined(Q_OS_MAC)
    QDir dirBundle(QCoreApplication::applicationDirPath() + QStringLiteral("/../Resources") + shareItem);
    if (dirBundle.exists())
    {
        return dirBundle.absolutePath();
    }
    else
    {
        QDir appDir = QDir(qApp->applicationDirPath());
        appDir.cdUp();
        appDir.cdUp();
        appDir.cdUp();
        QDir dir(appDir.absolutePath() + shareItem);
        if (dir.exists())
        {
            return dir.absolutePath();
        }
        else
        {
            return VCommonSettings::unixStandardSharePath + shareItem;
        }
    }
#else // Unix
#ifdef QT_DEBUG
    return QCoreApplication::applicationDirPath() + shareItem;
#else
    QDir dir(QCoreApplication::applicationDirPath() + shareItem);
    if (dir.exists())
    {
        return dir.absolutePath();
    }
    else
    {
        return VCommonSettings::unixStandardSharePath + shareItem;
    }
#endif
#endif
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::MultisizeTablesPath()
{
    return SharePath(QStringLiteral("/tables/multisize"));
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::StandardTemplatesPath()
{
    return SharePath(QStringLiteral("/tables/templates"));
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::PrepareStandardTemplates(const QString & currentPath)
{
    return PrepareStandardFiles(currentPath, StandardTemplatesPath(), GetDefPathTemplate());
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::PrepareMultisizeTables(const QString &currentPath)
{
    return PrepareStandardFiles(currentPath, MultisizeTablesPath(), GetDefPathMultisizeMeasurements());
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetDefPathIndividualMeasurements()
{
    return QDir::homePath() + QLatin1String("/seamly2d/") + tr("measurements") + QLatin1String("/") + tr("individual");
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetPathIndividualMeasurements() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    return settings.value(settingPathsIndividualMeasurements, GetDefPathIndividualMeasurements()).toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetPathIndividualMeasurements(const QString &value)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    settings.setValue(settingPathsIndividualMeasurements, value);
    settings.sync();
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetDefPathMultisizeMeasurements()
{
    return QDir::homePath() + QLatin1String("/seamly2d/") + tr("measurements") + QLatin1String("/") + tr("multisize");
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetPathMultisizeMeasurements() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    return settings.value(settingPathsMultisizeMeasurements, GetDefPathMultisizeMeasurements()).toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetPathMultisizeMeasurements(const QString &value)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    settings.setValue(settingPathsMultisizeMeasurements, value);
    settings.sync();
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetDefPathTemplate()
{
    return QDir::homePath() + QLatin1String("/seamly2d/") + tr("templates");
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetPathTemplate() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    return settings.value(settingPathsTemplates, GetDefPathTemplate()).toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetPathTemplate(const QString &value)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    settings.setValue(settingPathsTemplates, value);
    settings.sync();
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetDefPathLabelTemplate()
{
    return QDir::homePath() + QLatin1String("/seamly2d/") + tr("label templates");
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetPathLabelTemplate() const
{
    return value(settingPathsLabelTemplate, GetDefPathLabelTemplate()).toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetPathLabelTemplate(const QString &value)
{
    setValue(settingPathsLabelTemplate, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetOsSeparator() const
{
    return value(settingConfigurationOsSeparator, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetOsSeparator(const bool &value)
{
    setValue(settingConfigurationOsSeparator, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetAutosaveState() const
{
    return value(settingConfigurationAutosaveState, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetAutosaveState(const bool &value)
{
    setValue(settingConfigurationAutosaveState, value);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::GetAutosaveTime() const
{
    bool ok = false;
    int val = value(settingConfigurationAutosaveTime, 1).toInt(&ok);
    if (ok == false)
    {
        qDebug()<<"Could not convert value"<<value(settingConfigurationAutosaveTime, 1)
               <<"to int. Return default value for autosave time"<<1<<"minutes.";
        val = 1;
    }
    return val;
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetAutosaveTime(const int &value)
{
    setValue(settingConfigurationAutosaveTime, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetSendReportState() const
{
    return value(settingConfigurationSendReportState, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetSendReportState(const bool &value)
{
    setValue(settingConfigurationSendReportState, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetLocale() const
{
    return value(settingConfigurationLocale, QLocale().name()).toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetLocale(const QString &value)
{
    setValue(settingConfigurationLocale, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetPMSystemCode() const
{
    return value(settingPMSystemCode, "p998").toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetPMSystemCode(const QString &value)
{
    setValue(settingPMSystemCode, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetUnit() const
{
    return value(settingConfigurationUnit,
                 QLocale().measurementSystem() == QLocale::MetricSystem ? unitCM : unitINCH).toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetUnit(const QString &value)
{
    setValue(settingConfigurationUnit, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetConfirmItemDelete() const
{
    return value(settingConfigurationConfirmItemDeletion, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetConfirmItemDelete(const bool &value)
{
    setValue(settingConfigurationConfirmItemDeletion, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetConfirmFormatRewriting() const
{
    return value(settingConfigurationConfirmFormatRewriting, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetConfirmFormatRewriting(const bool &value)
{
    setValue(settingConfigurationConfirmFormatRewriting, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getToolBarStyle() const
{
    return value(settingGraphicsViewToolBarStyle, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setToolBarStyle(const bool &value)
{
    setValue(settingGraphicsViewToolBarStyle, value);
}


//---------------------------------------------------------------------------------------------------------------------
bool  VCommonSettings::getShowScrollBars() const
{
    return value(settingGraphicsViewShowScrollBars, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setShowScrollBars(const bool  &value)
{
    setValue(settingGraphicsViewShowScrollBars, value);
}

//---------------------------------------------------------------------------------------------------------------------
int  VCommonSettings::getScrollBarWidth() const
{
    return value(settingGraphicsViewScrollBarWidth, 10).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setScrollBarWidth(const int  &width)
{
    setValue(settingGraphicsViewScrollBarWidth, width);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::getScrollDuration() const
{
    return value(settingGraphicsViewScrollDuration, 300).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setScrollDuration(const int &duration)
{
    setValue(settingGraphicsViewScrollDuration, duration);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::getScrollUpdateInterval() const
{
    return value(settingGraphicsViewScrollUpdateInterval, 30).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setScrollUpdateInterval(const int &interval)
{
    setValue(settingGraphicsViewScrollUpdateInterval, interval);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::getScrollSpeedFactor() const
{
    return value(settingGraphicsViewScrollSpeedFactor, 10).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setScrollSpeedFactor(const int &factor)
{
    setValue(settingGraphicsViewScrollSpeedFactor, factor);
}


//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getZoomModKey() const
{
    return value(settingGraphicsViewZoomModKey, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setZoomModKey(const bool &value)
{
    setValue(settingGraphicsViewZoomModKey, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::isZoomDoubleClick() const
{
    return value(settingGraphicsViewZoomDoubleClick, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setZoomDoubleClick(const bool &value)
{
    setValue(settingGraphicsViewZoomDoubleClick, value);
}

//---------------------------------------------------------------------------------------------------------------------
int  VCommonSettings::getZoomSpeedFactor() const
{
    return value(settingGraphicsViewZoomSpeedFactor, 16).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setZoomSpeedFactor(const int  &factor)
{
    setValue(settingGraphicsViewZoomSpeedFactor, factor);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::getZoomRBPositiveColor() const
{
    return value(settingGraphicsViewZoomRBPositiveColor, "blue").toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setZoomRBPositiveColor(const QString &value)
{
    setValue(settingGraphicsViewZoomRBPositiveColor, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::getZoomRBNegativeColor() const
{
    return value(settingGraphicsViewZoomRBNegativeColor, "green").toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setZoomRBNegativeColor(const QString &value)
{
    setValue(settingGraphicsViewZoomRBNegativeColor, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::getPointNameColor() const
{
    return value(settingGraphicsViewPointNameColor, "green").toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setPointNameColor(const QString &value)
{
    setValue(settingGraphicsViewPointNameColor, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::getPointNameHoverColor() const
{
    return value(settingGraphicsViewPointNameHoverColor, "green").toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setPointNameHoverColor(const QString &value)
{
    setValue(settingGraphicsViewPointNameHoverColor, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::getAxisOrginColor() const
{
    return value(settingGraphicsViewAxisOrginColor, "magenta").toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setAxisOrginColor(const QString &value)
{
    setValue(settingGraphicsViewAxisOrginColor, value);
}

//---------------------------------------------------------------------------------------------------------------------
qreal VCommonSettings::getConstrainValue() const
{
    return value(settingGraphicsViewConstrainValue, 10.00).toReal();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setConstrainValue(const qreal &value)
{
    setValue(settingGraphicsViewConstrainValue, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getConstrainModKey() const
{
    return value(settingGraphicsViewConstrainModKey, 1).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setConstrainModKey(const bool &value)
{
    setValue(settingGraphicsViewConstrainModKey, value);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::GetUndoCount() const
{
    bool ok = false;
    int val = value(settingPatternUndo, 0).toInt(&ok);
    if (ok == false)
    {
        qDebug()<<"Could not convert value"<<value(settingPatternUndo, 0)
               <<"to int. Return default value for undo counts 0 (no limit).";
        val = 0;
    }
    return val;
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetUndoCount(const int &value)
{
    setValue(settingPatternUndo, value);
}

//---------------------------------------------------------------------------------------------------------------------
QStringList VCommonSettings::GetRecentFileList() const
{
    const QStringList files = value(settingGeneralRecentFileList).toStringList();
    QStringList cleared;

    for (int i = 0; i < files.size(); ++i)
    {
        if (QFileInfo(files.at(i)).exists())
        {
            cleared.append(files.at(i));
        }
    }

    return cleared;
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetRecentFileList(const QStringList &value)
{
    setValue(settingGeneralRecentFileList, value);
}

//---------------------------------------------------------------------------------------------------------------------
QStringList VCommonSettings::GetRestoreFileList() const
{
    return value(settingGeneralRestoreFileList).toStringList();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetRestoreFileList(const QStringList &value)
{
    setValue(settingGeneralRestoreFileList, value);
}

//---------------------------------------------------------------------------------------------------------------------
QByteArray VCommonSettings::GetGeometry() const
{
    return value(settingGeneralGeometry).toByteArray();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetGeometry(const QByteArray &value)
{
    setValue(settingGeneralGeometry, value);
}

//---------------------------------------------------------------------------------------------------------------------
QByteArray VCommonSettings::GetWindowState() const
{
    return value(settingGeneralWindowState).toByteArray();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetWindowState(const QByteArray &value)
{
    setValue(settingGeneralWindowState, value);
}

//---------------------------------------------------------------------------------------------------------------------
QByteArray VCommonSettings::GetToolbarsState() const
{
    return value(settingGeneralToolbarsState).toByteArray();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetToolbarsState(const QByteArray &value)
{
    setValue(settingGeneralToolbarsState, value);
}

//---------------------------------------------------------------------------------------------------------------------
QSize VCommonSettings::getPreferenceDialogSize() const
{
    return value(settingPreferenceDialogSize, QSize(0, 0)).toSize();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setPreferenceDialogSize(const QSize& sz)
{
    setValue(settingPreferenceDialogSize, sz);
}

//---------------------------------------------------------------------------------------------------------------------
QSize VCommonSettings::GetToolSeamAllowanceDialogSize() const
{
    return value(settingToolSeamAllowanceDialogSize, QSize(0, 0)).toSize();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetToolSeamAllowanceDialogSize(const QSize &sz)
{
    setValue(settingToolSeamAllowanceDialogSize, sz);
}

//---------------------------------------------------------------------------------------------------------------------
QSize VCommonSettings::GetFormulaWizardDialogSize() const
{
    return value(settingFormulaWizardDialogSize, QSize(0, 0)).toSize();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetFormulaWizardDialogSize(const QSize &sz)
{
    setValue(settingFormulaWizardDialogSize, sz);
}

//---------------------------------------------------------------------------------------------------------------------
QSize VCommonSettings::GetIncrementsDialogSize() const
{
    return value(settingIncrementsDialogSize, QSize(0, 0)).toSize();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetIncrementsDialogSize(const QSize &sz)
{
    setValue(settingIncrementsDialogSize, sz);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::GetLatestSkippedVersion() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    return settings.value(settingLatestSkippedVersion, 0x0).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetLatestSkippedVersion(int value)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    settings.setValue(settingLatestSkippedVersion, value);
    settings.sync();
}

//---------------------------------------------------------------------------------------------------------------------
QDate VCommonSettings::GetDateOfLastRemind() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    return settings.value(settingDateOfLastRemind, QDate(1900, 1, 1)).toDate();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetDateOfLastRemind(const QDate &date)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    settings.setValue(settingDateOfLastRemind, date);
    settings.sync();
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetForbidWorkpieceFlipping() const
{
    return value(settingPatternForbidFlipping, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetForbidWorkpieceFlipping(bool value)
{
    setValue(settingPatternForbidFlipping, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::IsHideMainPath() const
{
    return value(settingPatternHideMainPath, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetHideMainPath(bool value)
{
    setValue(settingPatternHideMainPath, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::showSecondNotch() const
{
    return value(settingDoubleNotch, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setShowSecondNotch(bool value)
{
    setValue(settingDoubleNotch, value);
}


//---------------------------------------------------------------------------------------------------------------------
qreal VCommonSettings::getDefaultNotchLength() const
{
   return value(settingDefaultNotchLength, .250).toReal();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setDefaultNotchLength(const qreal &value)
{
    setValue(settingDefaultNotchLength, value);
}

//---------------------------------------------------------------------------------------------------------------------
qreal VCommonSettings::getDefaultNotchWidth() const
{
   return value(settingDefaultNotchWidth, .250).toReal();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setDefaultNotchWidth(const qreal &value)
{
    setValue(settingDefaultNotchWidth, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::getDefaultNotchType() const
{
   return value(settingDefaultNotchType, "slit").toString();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setDefaultNotchType(const QString &value)
{
    setValue(settingDefaultNotchType, value);
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetCSVWithHeader(bool withHeader)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    settings.setValue(settingCSVWithHeader, withHeader);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetCSVWithHeader() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    return settings.value(settingCSVWithHeader, GetDefCSVWithHeader()).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::GetDefCSVWithHeader() const
{
    return false;
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetCSVCodec(int mib)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    settings.setValue(settingCSVCodec, mib);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::GetCSVCodec() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    return settings.value(settingCSVCodec, GetDefCSVCodec()).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::GetDefCSVCodec() const
{
    return QTextCodec::codecForLocale()->mibEnum();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetCSVSeparator(const QChar &separator)
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    switch(separator.toLatin1())
    {
        case '\t':
            settings.setValue(settingCSVSeparator, 0);
            break;
        case ';':
            settings.setValue(settingCSVSeparator, 1);
            break;
        case ' ':
            settings.setValue(settingCSVSeparator, 2);
            break;
        default:
            settings.setValue(settingCSVSeparator, 3);
            break;
    }
}

//---------------------------------------------------------------------------------------------------------------------
QChar VCommonSettings::GetCSVSeparator() const
{
    QSettings settings(this->format(), this->scope(), this->organizationName(), commonIniFilename);
    const quint8 separator = static_cast<quint8>(settings.value(settingCSVSeparator, 3).toUInt());
    switch(separator)
    {
        case 0:
            return QChar('\t');
        case 1:
            return QChar(';');
        case 2:
            return QChar(' ');
        default:
            return QChar(',');
    }
}

//---------------------------------------------------------------------------------------------------------------------
QChar VCommonSettings::GetDefCSVSeparator() const
{
    return QChar(',');
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetDefaultSeamAllowance(double value)
{
    setValue(settingPatternDefaultSeamAllowance, UnitConvertor(value, StrToUnits(GetUnit()), Unit::Cm));
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief returns the default seam allowance. The corresponding unit is the default unit.
 * @return the default seam allowance
 */
double VCommonSettings::GetDefaultSeamAllowance()
{
    double defaultValue;

    const Unit globalUnit = StrToUnits(GetUnit());

    switch (globalUnit)
    {
        case Unit::Mm:
            defaultValue = 10;
            break;
        case Unit::Inch:
            defaultValue = 0.25;
            break;
        default:
        case Unit::Cm:
            defaultValue = 1;
            break;
    }

    bool ok = false;
    double val = value(settingPatternDefaultSeamAllowance, -1).toDouble(&ok);
    if (ok == false)
    {
        qDebug()<< "Could not convert value"<<value(settingPatternDefaultSeamAllowance, 0)
                << "to real. Return default value for default seam allowance is "
                << defaultValue << ".";
        val = defaultValue;
    }

    if (val < 0)
    {
        val = defaultValue;
    }
    else
    {
        val = UnitConvertor(val, Unit::Cm, globalUnit);
    }

    return val;
}

//---------------------------------------------------------------------------------------------------------------------
QFont VCommonSettings::getLabelFont() const
{
    return qvariant_cast<QFont>(value(settingPatternLabelFont, QApplication::font()));
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setLabelFont(const QFont &f)
{
    setValue(settingPatternLabelFont, f);
}

//---------------------------------------------------------------------------------------------------------------------
QFont VCommonSettings::getGuiFont() const
{
    return qvariant_cast<QFont>(value(settingPatternGuiFont, QApplication::font()));
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setGuiFont(const QFont &f)
{
    setValue(settingPatternGuiFont, f);
}

//---------------------------------------------------------------------------------------------------------------------
QFont VCommonSettings::getPointNameFont() const
{
    return qvariant_cast<QFont>(value(settingPatternPointNameFont, QApplication::font()));
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setPointNameFont(const QFont &f)
{
    setValue(settingPatternPointNameFont, f);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getHidePointNames() const
{
    return value(settingGraphicsViewHidePointNames, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setHidePointNames(bool value)
{
    setValue(settingGraphicsViewHidePointNames, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getShowAxisOrigin() const
{
    return value(settingGraphicsViewShowAxisOrigin, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setShowAxisOrigin(bool value)
{
    setValue(settingGraphicsViewShowAxisOrigin, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::isWireframe() const
{
    return value(settingGraphicsViewWireframe, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setWireframe(bool value)
{
    setValue(settingGraphicsViewWireframe, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getShowControlPoints() const
{
    return value(settingGraphicsViewShowControlPoints, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setShowControlPoints(bool value)
{
    setValue(settingGraphicsViewShowControlPoints, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getShowAnchorPoints() const
{
    return value(settingGraphicsViewShowAnchorPoints, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setShowAnchorPoints(bool value)
{
    setValue(settingGraphicsViewShowAnchorPoints, value);
}

//---------------------------------------------------------------------------------------------------------------------
bool VCommonSettings::getUseToolColor() const
{
    return value(settingGraphicsUseToolColor, false).toBool();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setUseToolColor(bool value)
{
    setValue(settingGraphicsUseToolColor, value);
}

//---------------------------------------------------------------------------------------------------------------------
int VCommonSettings::getPointNameSize() const
{
    if (pointNameSize <= 0)
    {
        bool ok = false;
        pointNameSize = value(settingGraphicsViewPointNameSize, 32).toInt(&ok);
        if (not ok)
        {
            pointNameSize = 32;
        }
    }
    return pointNameSize;
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setPointNameSize(int value)
{
    setValue(settingGraphicsViewPointNameSize, value);
    pointNameSize = value;
}

int VCommonSettings::getGuiFontSize() const
{
    return value(settingGraphicsViewGuiFontSize, 9).toInt();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::setGuiFontSize(int value)
{
    setValue(settingGraphicsViewGuiFontSize, value);
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetLabelDateFormat() const
{
    const QString format = value(settingLabelDateFormat, VCommonSettings::PredefinedDateFormats().first()).toString();
    const QStringList allFormats = VCommonSettings::PredefinedDateFormats() + GetUserDefinedDateFormats();

    if (allFormats.contains(format))
    {
        return format;
    }
    else
    {
        return VCommonSettings::PredefinedDateFormats().first();
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetLabelDateFormat(const QString &format)
{
    setValue(settingLabelDateFormat, format);
}

//---------------------------------------------------------------------------------------------------------------------
QStringList VCommonSettings::PredefinedDateFormats()
{
    QStringList formats = QStringList() << "MM-dd-yyyy"
                                        << "d/M/yy"
                                        << "ddddMMMM dd, yyyy"
                                        << "dd/MM/yy"
                                        << "dd/MM/yyyy"
                                        << "MMM d, yy"
                                        << "MMM d, yyyy"
                                        << "d. MMM. yyyy"
                                        << "MMMM d, yyyy"
                                        << "d. MMMM yyyy"
                                        << "ddd, MMM d, yy"
                                        << "ddd dd/MMM yy"
                                        << "ddd, MMMM d, yyyy"
                                        << "ddddMMMM d, yyyy"
                                        << "MM-dd"
                                        << "yy-MM-dd"
                                        << "yyyy-MM-dd"
                                        << "MM/yy"
                                        << "MMM dd"
                                        << "MMMM";
    return formats;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList VCommonSettings::GetUserDefinedDateFormats() const
{
    return value(settingLabelUserDateFormats, QStringList()).toStringList();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetUserDefinedDateFormats(const QStringList &formats)
{
    setValue(settingLabelUserDateFormats, ClearFormats(VCommonSettings::PredefinedDateFormats(), formats));
}

//---------------------------------------------------------------------------------------------------------------------
QString VCommonSettings::GetLabelTimeFormat() const
{
    const QString format = value(settingLabelTimeFormat, VCommonSettings::PredefinedTimeFormats().first()).toString();
    const QStringList allFormats = VCommonSettings::PredefinedTimeFormats() + GetUserDefinedTimeFormats();

    if (allFormats.contains(format))
    {
        return format;
    }
    else
    {
        return VCommonSettings::PredefinedTimeFormats().first();
    }
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetLabelTimeFormat(const QString &format)
{
    setValue(settingLabelTimeFormat, format);
}

//---------------------------------------------------------------------------------------------------------------------
QStringList VCommonSettings::PredefinedTimeFormats()
{
    QStringList formats = QStringList() << "hh:mm:ss"
                                        << "hh:mm:ss AP"
                                        << "hh:mm"
                                        << "hh:mm AP";
    return formats;
}

//---------------------------------------------------------------------------------------------------------------------
QStringList VCommonSettings::GetUserDefinedTimeFormats() const
{
    return value(settingLabelUserTimeFormats, QStringList()).toStringList();
}

//---------------------------------------------------------------------------------------------------------------------
void VCommonSettings::SetUserDefinedTimeFormats(const QStringList &formats)
{
    setValue(settingLabelUserTimeFormats, ClearFormats(VCommonSettings::PredefinedTimeFormats(), formats));
}

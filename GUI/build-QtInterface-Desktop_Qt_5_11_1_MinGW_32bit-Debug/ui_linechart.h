/********************************************************************************
** Form generated from reading UI file 'linechart.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINECHART_H
#define UI_LINECHART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_lineChart
{
public:

    void setupUi(QDialog *lineChart)
    {
        if (lineChart->objectName().isEmpty())
            lineChart->setObjectName(QStringLiteral("lineChart"));
        lineChart->resize(400, 300);

        retranslateUi(lineChart);

        QMetaObject::connectSlotsByName(lineChart);
    } // setupUi

    void retranslateUi(QDialog *lineChart)
    {
        lineChart->setWindowTitle(QApplication::translate("lineChart", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lineChart: public Ui_lineChart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINECHART_H

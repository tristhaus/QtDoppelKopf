/*
 * This file is part of QtDoppelKopf.
 *
 * QtDoppelKopf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtDoppelKopf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtDoppelKopf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class MainWindow;
class FrontendTest;

class Ui_MainWindow
{
    friend MainWindow;
    friend FrontendTest;

public:
    const unsigned int maxNumberOfPlayers = 8;

private:
    const QString ScoreStylesheet = "QLabel { font-weight: bold ; font-size: 12pt }";

    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;

    QWidget *topMenu;
    QGridLayout *topMenuLayout;
    QPushButton *changePlayersButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *mandatorySoloButton;
    QSpacerItem *topMenuSpacer;

    QGridLayout *namesLayout;
    QLabel *namenLabel;
    std::vector<QLabel*> names;

    QLabel *letztesLabel;
    std::vector<QLabel*> lastGames;

    QLabel *aktuellesLabel;
    std::vector<QLineEdit*> actuals;

    QWidget *controlWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *bockereignisseLabel;
    QSpinBox *spinBox;
    QLabel *multiplier;
    QPushButton *commitButton;
    QPushButton *resetButton;
    QSpacerItem *controlSpacer0;
    QSpacerItem *controlSpacer1;

    QLabel *spielstandLabel;
    std::vector<QLabel*> scores;

    QSpacerItem *verticalSpacer;

    QLabel *zuZahlenLabel;
    std::vector<QLabel*> cashs;

    QLabel *kassenstandLabel;
    QLabel *totalCash;

    QGroupBox *statisticsBox;
    QGridLayout *gridLayout;

    QLabel *gewonnenLabel;
    QLabel *verlorenLabel;
    QLabel *anzahlSpieleLabel;
    QLabel *soloGewonnenLabel;
    QLabel *soloVerlorenLabel;
    QLabel *soloPunkteLabel;
    QLabel *groessterGewinnLabel;
    QLabel *groessterVerlustLabel;
    QLabel *ohneBockLabel;

    std::vector<QLabel*> statisticNames;
    std::vector<QLabel*> numberWons;
    std::vector<QLabel*> numberLosts;
    std::vector<QLabel*> numberPlayeds;
    std::vector<QLabel*> numberSoloWons;
    std::vector<QLabel*> numberSoloLosts;
    std::vector<QLabel*> pointsSolos;
    std::vector<QLabel*> maxSingleWins;
    std::vector<QLabel*> maxSingleLosss;
    std::vector<QLabel*> unmultipliedScores;

public:
    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 600);

        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);

        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);

        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);

        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);

        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        namesLayout = new QGridLayout();
        namesLayout->setObjectName(QString::fromUtf8("namesLayout"));
        namesLayout->setSizeConstraint(QLayout::SetMaximumSize);

        // ---- TOP MENU ----

        topMenu = new QWidget(centralwidget);
        topMenu->setObjectName(QString::fromUtf8("topMenu"));
        topMenu->setEnabled(true);
        sizePolicy1.setHeightForWidth(topMenu->sizePolicy().hasHeightForWidth());
        topMenu->setSizePolicy(sizePolicy1);
        topMenuLayout = new QGridLayout(topMenu);
        topMenuLayout->setObjectName(QString::fromUtf8("gridLayout_2"));
        topMenuLayout->setContentsMargins(6, 6, 6, 6);

        changePlayersButton = new QPushButton(topMenu);
        changePlayersButton->setObjectName(QString::fromUtf8("changePlayersButton"));

        topMenuLayout->addWidget(changePlayersButton, 0, 0, 1, 1);

        saveButton = new QPushButton(topMenu);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setSizePolicy(sizePolicy4);

        topMenuLayout->addWidget(saveButton, 0, 2, 1, 1);

        loadButton = new QPushButton(topMenu);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        topMenuLayout->addWidget(loadButton, 0, 1, 1, 1);

        mandatorySoloButton = new QPushButton(topMenu);
        mandatorySoloButton->setObjectName(QString::fromUtf8("mandatorySoloButton"));

        topMenuLayout->addWidget(mandatorySoloButton, 0, 4, 1, 1);

        topMenuSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topMenuLayout->addItem(topMenuSpacer, 0, 3, 1, 1);

        sizePolicy4.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        sizePolicy4.setHeightForWidth(changePlayersButton->sizePolicy().hasHeightForWidth());
        changePlayersButton->setSizePolicy(sizePolicy4);
        sizePolicy4.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy4);

        namesLayout->addWidget(topMenu, 0, 0, 1, 9);

        // ---- NAMES AND SCORE ENTRY SECTION ----

        namenLabel = new QLabel(centralwidget);
        namenLabel->setObjectName(QString::fromUtf8("namenLabel"));
        namenLabel->setSizePolicy(sizePolicy1);
        sizePolicy1.setHeightForWidth(namenLabel->sizePolicy().hasHeightForWidth());

        namesLayout->addWidget(namenLabel, 1, 0, 1, 1);

        letztesLabel = new QLabel(centralwidget);
        letztesLabel->setObjectName(QString::fromUtf8("letztesLabel"));
        sizePolicy1.setHeightForWidth(letztesLabel->sizePolicy().hasHeightForWidth());
        letztesLabel->setSizePolicy(sizePolicy1);

        namesLayout->addWidget(letztesLabel, 2, 0, 1, 1);

        aktuellesLabel = new QLabel(centralwidget);
        aktuellesLabel->setObjectName(QString::fromUtf8("aktuellesLabel"));

        namesLayout->addWidget(aktuellesLabel, 3, 0, 1, 1);

        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            QLabel * name = new QLabel(centralwidget);
            name->setObjectName(QString::fromUtf8("names%1").arg(i));
            namesLayout->addWidget(name, 1, i+1, 1, 1);
            names.push_back(name);

            QLabel * lastGame = new QLabel(centralwidget);
            lastGame->setObjectName(QString::fromUtf8("lastGames%1").arg(i));
            namesLayout->addWidget(lastGame, 2, i+1, 1, 1);
            lastGames.push_back(lastGame);

            QLineEdit * actual = new QLineEdit(centralwidget);
            actual->setObjectName(QString::fromUtf8("actuals%1").arg(i));
            namesLayout->addWidget(actual, 3, i+1, 1, 1);
            actuals.push_back(actual);
        }

        // ---- CONTROLS BELOW NAMES ----

        controlWidget = new QWidget(centralwidget);
        controlWidget->setObjectName(QString::fromUtf8("controlWidget"));
        horizontalLayout = new QHBoxLayout(controlWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        bockereignisseLabel = new QLabel(controlWidget);
        bockereignisseLabel->setObjectName(QString::fromUtf8("bockereignisseLabel"));
        sizePolicy2.setHeightForWidth(bockereignisseLabel->sizePolicy().hasHeightForWidth());
        bockereignisseLabel->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(bockereignisseLabel);

        spinBox = new QSpinBox(controlWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        sizePolicy3.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy3);
        spinBox->setMaximum(9);
        spinBox->setMinimum(0);

        horizontalLayout->addWidget(spinBox);

        multiplier = new QLabel(controlWidget);
        multiplier->setObjectName(QString::fromUtf8("multiplier"));

        horizontalLayout->addWidget(multiplier);

        controlSpacer0 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(controlSpacer0);

        commitButton = new QPushButton(controlWidget);
        commitButton->setObjectName(QString::fromUtf8("commitButton"));

        horizontalLayout->addWidget(commitButton);

        controlSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(controlSpacer1);

        resetButton = new QPushButton(controlWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        horizontalLayout->addWidget(resetButton);

        namesLayout->addWidget(controlWidget, 4, 0, 1, 9);

        // ---- CURRENT SCORE AND CASH SECTION ----

        spielstandLabel = new QLabel(centralwidget);
        spielstandLabel->setObjectName(QString::fromUtf8("spielstandLabel"));
        spielstandLabel->setStyleSheet(ScoreStylesheet);

        namesLayout->addWidget(spielstandLabel, 5, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        namesLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        zuZahlenLabel = new QLabel(centralwidget);
        zuZahlenLabel->setObjectName(QString::fromUtf8("zuZahlenLabel"));
        sizePolicy1.setHeightForWidth(zuZahlenLabel->sizePolicy().hasHeightForWidth());
        zuZahlenLabel->setSizePolicy(sizePolicy1);

        namesLayout->addWidget(zuZahlenLabel, 7, 0, 1, 1);

        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            QLabel * score = new QLabel(centralwidget);
            score->setObjectName(QString::fromUtf8("scores%1").arg(i));
            score->setStyleSheet(ScoreStylesheet);
            namesLayout->addWidget(score, 5, i+1, 1, 1);
            scores.push_back(score);

            QLabel * cash = new QLabel(centralwidget);
            cash->setObjectName(QString::fromUtf8("cashs%1").arg(i));
            namesLayout->addWidget(cash, 7, i+1, 1, 1);
            cashs.push_back(cash);
        }

        totalCash = new QLabel(centralwidget);
        totalCash->setObjectName(QString::fromUtf8("totalCash"));

        namesLayout->addWidget(totalCash, 8, 3, 1, 6);

        kassenstandLabel = new QLabel(centralwidget);
        kassenstandLabel->setObjectName(QString::fromUtf8("kassenstandLabel"));

        namesLayout->addWidget(kassenstandLabel, 8, 0, 1, 3);

        verticalLayout->addLayout(namesLayout);

        // ---- STATISTICS SECTION IN A BOX ----

        statisticsBox = new QGroupBox(centralwidget);
        statisticsBox->setObjectName(QString::fromUtf8("statisticsBox"));
        gridLayout = new QGridLayout(statisticsBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        gewonnenLabel = new QLabel(statisticsBox);
        gewonnenLabel->setObjectName(QString::fromUtf8("gewonnenLabel"));

        gridLayout->addWidget(gewonnenLabel, 0, 1, 1, 1);

        verlorenLabel = new QLabel(statisticsBox);
        verlorenLabel->setObjectName(QString::fromUtf8("verlorenLabel"));

        gridLayout->addWidget(verlorenLabel, 0, 2, 1, 1);

        anzahlSpieleLabel = new QLabel(statisticsBox);
        anzahlSpieleLabel->setObjectName(QString::fromUtf8("anzahlSpieleLabel"));

        gridLayout->addWidget(anzahlSpieleLabel, 0, 3, 1, 1);

        soloGewonnenLabel = new QLabel(statisticsBox);
        soloGewonnenLabel->setObjectName(QString::fromUtf8("soloGewonnenLabel"));

        gridLayout->addWidget(soloGewonnenLabel, 0, 4, 1, 1);

        soloVerlorenLabel = new QLabel(statisticsBox);
        soloVerlorenLabel->setObjectName(QString::fromUtf8("soloVerlorenLabel"));

        gridLayout->addWidget(soloVerlorenLabel, 0, 5, 1, 1);

        soloPunkteLabel = new QLabel(statisticsBox);
        soloPunkteLabel->setObjectName(QString::fromUtf8("soloPunkteLabel"));

        gridLayout->addWidget(soloPunkteLabel, 0, 6, 1, 1);

        groessterGewinnLabel = new QLabel(statisticsBox);
        groessterGewinnLabel->setObjectName(QString::fromUtf8("groessterGewinnLabel"));

        gridLayout->addWidget(groessterGewinnLabel, 0, 7, 1, 1);

        groessterVerlustLabel = new QLabel(statisticsBox);
        groessterVerlustLabel->setObjectName(QString::fromUtf8("groessterVerlustLabel"));

        gridLayout->addWidget(groessterVerlustLabel, 0, 8, 1, 1);

        ohneBockLabel = new QLabel(statisticsBox);
        ohneBockLabel->setObjectName(QString::fromUtf8("ohneBockLabel"));

        gridLayout->addWidget(ohneBockLabel, 0, 9, 1, 1);

        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            QLabel * statisticName = new QLabel(statisticsBox);
            statisticName->setObjectName(QString::fromUtf8("statisticNames%1").arg(i));
            gridLayout->addWidget(statisticName, i+1, 0, 1, 1);
            statisticNames.push_back(statisticName);

            QLabel * numberWon = new QLabel(statisticsBox);
            numberWon->setObjectName(QString::fromUtf8("numberWons%1").arg(i));
            gridLayout->addWidget(numberWon, i+1, 1, 1, 1);
            numberWons.push_back(numberWon);

            QLabel * numberLost = new QLabel(statisticsBox);
            numberLost->setObjectName(QString::fromUtf8("numberLosts%1").arg(i));
            gridLayout->addWidget(numberLost, i+1, 2, 1, 1);
            numberLosts.push_back(numberLost);

            QLabel * numberPlayed = new QLabel(statisticsBox);
            numberPlayed->setObjectName(QString::fromUtf8("numberPlayeds%1").arg(i));
            gridLayout->addWidget(numberPlayed, i+1, 3, 1, 1);
            numberPlayeds.push_back(numberPlayed);

            QLabel * numberSoloWon = new QLabel(statisticsBox);
            numberSoloWon->setObjectName(QString::fromUtf8("numberSoloWons%1").arg(i));
            gridLayout->addWidget(numberSoloWon, i+1, 4, 1, 1);
            numberSoloWons.push_back(numberSoloWon);

            QLabel * numberSoloLost = new QLabel(statisticsBox);
            numberSoloLost->setObjectName(QString::fromUtf8("numberSoloLosts%1").arg(i));
            gridLayout->addWidget(numberSoloLost, i+1, 5, 1, 1);
            numberSoloLosts.push_back(numberSoloLost);

            QLabel * pointsSolo = new QLabel(statisticsBox);
            pointsSolo->setObjectName(QString::fromUtf8("pointsSolos%1").arg(i));
            gridLayout->addWidget(pointsSolo, i+1, 6, 1, 1);
            pointsSolos.push_back(pointsSolo);

            QLabel * maxSingleWin = new QLabel(statisticsBox);
            maxSingleWin->setObjectName(QString::fromUtf8("maxSingleWins%1").arg(i));
            gridLayout->addWidget(maxSingleWin, i+1, 7, 1, 1);
            maxSingleWins.push_back(maxSingleWin);

            QLabel * maxSingleLoss = new QLabel(statisticsBox);
            maxSingleLoss->setObjectName(QString::fromUtf8("maxSingleLosss%1").arg(i));
            gridLayout->addWidget(maxSingleLoss, i+1, 8, 1, 1);
            maxSingleLosss.push_back(maxSingleLoss);

            QLabel * unmultipliedScore = new QLabel(statisticsBox);
            unmultipliedScore->setObjectName(QString::fromUtf8("unmultipliedScores%1").arg(i));
            gridLayout->addWidget(unmultipliedScore, i+1, 9, 1, 1);
            unmultipliedScores.push_back(unmultipliedScore);
        }

        verticalLayout->addWidget(statisticsBox);

        MainWindow->setCentralWidget(centralwidget);

        for(unsigned int i=0u; i < maxNumberOfPlayers - 1; ++i)
        {
            QWidget::setTabOrder(actuals[i], actuals[i+1]);
        }

        QWidget::setTabOrder(actuals[maxNumberOfPlayers - 1], spinBox);
        QWidget::setTabOrder(spinBox, commitButton);
        QWidget::setTabOrder(commitButton, resetButton);
        QWidget::setTabOrder(resetButton, changePlayersButton);
        QWidget::setTabOrder(changePlayersButton, loadButton);
        QWidget::setTabOrder(loadButton, saveButton);
        QWidget::setTabOrder(saveButton, mandatorySoloButton);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            names[i]->setText(QCoreApplication::translate("MainWindow", "!Name", nullptr));
            lastGames[i]->setText(QCoreApplication::translate("MainWindow", "!LastGame", nullptr));
            scores[i]->setText(QCoreApplication::translate("MainWindow", "!Score", nullptr));
            cashs[i]->setText(QCoreApplication::translate("MainWindow", "!Cash", nullptr));
            statisticNames[i]->setText(QCoreApplication::translate("MainWindow", "!SName", nullptr));
            numberWons[i]->setText(QCoreApplication::translate("MainWindow", "!NumberWon", nullptr));
            numberLosts[i]->setText(QCoreApplication::translate("MainWindow", "!NumberLost", nullptr));
            numberPlayeds[i]->setText(QCoreApplication::translate("MainWindow", "!NumberPlayed", nullptr));
            numberSoloWons[i]->setText(QCoreApplication::translate("MainWindow", "!NumberSoloWon", nullptr));
            numberSoloLosts[i]->setText(QCoreApplication::translate("MainWindow", "!NumberSoloLost", nullptr));
            pointsSolos[i]->setText(QCoreApplication::translate("MainWindow", "!PointsSolo", nullptr));
            maxSingleWins[i]->setText(QCoreApplication::translate("MainWindow", "!MaxSingleWin", nullptr));
            maxSingleLosss[i]->setText(QCoreApplication::translate("MainWindow", "!MaxSingleLoss", nullptr));
            unmultipliedScores[i]->setText(QCoreApplication::translate("MainWindow", "!unmultipliedScore", nullptr));
        }

        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QtDoppelKopf", nullptr));

        changePlayersButton->setText(QCoreApplication::translate("MainWindow", "Spieler \303\244ndern ...", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Laden ...", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Speichern ...", nullptr));
        mandatorySoloButton->setText(QCoreApplication::translate("MainWindow", "Pflichtsolorunde", nullptr));

        namenLabel->setText(QCoreApplication::translate("MainWindow", "Namen", nullptr));
        letztesLabel->setText(QCoreApplication::translate("MainWindow", "Letztes Spiel", nullptr));
        aktuellesLabel->setText(QCoreApplication::translate("MainWindow", "Aktuelles Spiel", nullptr));

        bockereignisseLabel->setText(QCoreApplication::translate("MainWindow", "Bockereignisse", nullptr));
        multiplier->setText(QCoreApplication::translate("MainWindow", "!multiplier", nullptr));
        commitButton->setText(QCoreApplication::translate("MainWindow", "\303\234bernehmen", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Letztes Spiel zur\303\274cksetzen", nullptr));

        spielstandLabel->setText(QCoreApplication::translate("MainWindow", "Spielstand", nullptr));
        zuZahlenLabel->setText(QCoreApplication::translate("MainWindow", "Zu Zahlen", nullptr));

        kassenstandLabel->setText(QCoreApplication::translate("MainWindow", "Aktueller Kassenstand", nullptr));
        totalCash->setText(QCoreApplication::translate("MainWindow", "!totalCash", nullptr));

        statisticsBox->setTitle(QCoreApplication::translate("MainWindow", "Statistiken", nullptr));

        gewonnenLabel->setText(QCoreApplication::translate("MainWindow", "Gewonnen", nullptr));
        verlorenLabel->setText(QCoreApplication::translate("MainWindow", "Verloren", nullptr));
        anzahlSpieleLabel->setText(QCoreApplication::translate("MainWindow", "# Spiele", nullptr));
        soloGewonnenLabel->setText(QCoreApplication::translate("MainWindow", "# +Solo", nullptr));
        soloVerlorenLabel->setText(QCoreApplication::translate("MainWindow", "# -Solo", nullptr));
        soloPunkteLabel->setText(QCoreApplication::translate("MainWindow", "Solo Punkte", nullptr));
        groessterGewinnLabel->setText(QCoreApplication::translate("MainWindow", "H\303\266chstes +", nullptr));
        groessterVerlustLabel->setText(QCoreApplication::translate("MainWindow", "H\303\266chstes -", nullptr));
        ohneBockLabel->setText(QCoreApplication::translate("MainWindow", "Ohne Bock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

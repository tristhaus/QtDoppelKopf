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
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class MainWindow;
class FrontendTest;

class Ui_MainWindow
{
    friend MainWindow;
    friend FrontendTest;

protected:
    Ui_MainWindow(const unsigned int maxPlayers)
        : maxNumberOfPlayers(maxPlayers)
    {
    }

private:
    const int experimentalWidthOfResetButton = 145;
    const unsigned int maxNumberOfPlayers;
    const QString ScoreStylesheet = "QLabel { font-weight: bold ; font-size: 12pt }";
    const QString MultiplierStylesheet = "QLabel { font-weight: bold ; font-size: 12pt }";

    QWidget *centralwidget;
    QHBoxLayout *centralLayout;

    QWidget *leftwidget;
    QVBoxLayout *leftVerticalLayout;

    QWidget *rightwidget;
    QVBoxLayout *rightVerticalLayout;

    QWidget *topMenu;
    QGridLayout *topMenuLayout;
    QPushButton *changePlayersButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *mandatorySoloButton;
    QPushButton *aboutButton;
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
    QGridLayout *statisticsGridLayout;

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

    QLabel *currentGameMultiplier;
    QWidget *multiplierPreviewWidget;
    QGridLayout *multiplierPreviewGridLayout;
    QLabel *dreifachbockLabel;
    QLabel *doppelbockLabel;
    QLabel *einfachbockLabel;
    QLabel *tripleMultiplier;
    QLabel *doubleMultiplier;
    QLabel *singleMultiplier;

    QWidget *playerHistorySelectionWidget;
    QGridLayout *playerHistoryGridLayout;
    std::vector<QHBoxLayout*> playerHistorySelectionLayouts;
    std::vector<QCheckBox*> playerHistorySelectionCheckboxes;
    std::vector<QLabel*> playerHistorySelectionLabels;
    QCustomPlot *plotPlayerHistory;

public:
    void setupUi(QMainWindow *MainWindow)
    {
        const int leftLabelsMaxWidth = 80;
        const int leftMainMaxWidth = 75;

        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 800);

        QSizePolicy sizePolicyExpExp(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicyExpExp.setHorizontalStretch(0);
        sizePolicyExpExp.setVerticalStretch(0);

        QSizePolicy sizePolicyPreFix(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicyPreFix.setHorizontalStretch(0);
        sizePolicyPreFix.setVerticalStretch(0);

        QSizePolicy sizePolicyFixPre(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicyFixPre.setHorizontalStretch(0);
        sizePolicyFixPre.setVerticalStretch(0);

        QSizePolicy sizePolicyFixFix(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicyFixFix.setHorizontalStretch(0);
        sizePolicyFixFix.setVerticalStretch(0);

        QSizePolicy sizePolicyMinMin(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicyMinMin.setHorizontalStretch(0);
        sizePolicyMinMin.setVerticalStretch(0);

        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicyExpExp.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicyExpExp);

        centralLayout = new QHBoxLayout(centralwidget);
        centralLayout->setObjectName(QString::fromUtf8("centralLayout"));

        leftwidget = new QWidget(centralwidget);
        leftwidget->setObjectName(QString::fromUtf8("leftwidget"));
        centralLayout->addWidget(leftwidget);

        leftVerticalLayout = new QVBoxLayout(leftwidget);
        leftVerticalLayout->setObjectName(QString::fromUtf8("leftVerticalLayout"));

        namesLayout = new QGridLayout();
        namesLayout->setObjectName(QString::fromUtf8("namesLayout"));
        namesLayout->setSizeConstraint(QLayout::SetMaximumSize);

        // ---- TOP MENU ----

        topMenu = new QWidget(centralwidget);
        topMenu->setObjectName(QString::fromUtf8("topMenu"));
        topMenu->setEnabled(true);
        sizePolicyPreFix.setHeightForWidth(topMenu->sizePolicy().hasHeightForWidth());
        topMenu->setSizePolicy(sizePolicyPreFix);
        topMenuLayout = new QGridLayout(topMenu);
        topMenuLayout->setObjectName(QString::fromUtf8("gridLayout_2"));
        topMenuLayout->setContentsMargins(6, 6, 6, 6);

        changePlayersButton = new QPushButton(topMenu);
        changePlayersButton->setObjectName(QString::fromUtf8("changePlayersButton"));

        topMenuLayout->addWidget(changePlayersButton, 0, 0, 1, 1);

        saveButton = new QPushButton(topMenu);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setSizePolicy(sizePolicyMinMin);

        topMenuLayout->addWidget(saveButton, 0, 2, 1, 1);

        loadButton = new QPushButton(topMenu);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        topMenuLayout->addWidget(loadButton, 0, 1, 1, 1);

        mandatorySoloButton = new QPushButton(topMenu);
        mandatorySoloButton->setObjectName(QString::fromUtf8("mandatorySoloButton"));

        topMenuLayout->addWidget(mandatorySoloButton, 0, 4, 1, 1);

        aboutButton = new QPushButton(topMenu);
        aboutButton->setObjectName(QString::fromUtf8("aboutoButton"));

        topMenuLayout->addWidget(aboutButton, 0, 5, 1, 1);

        topMenuSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topMenuLayout->addItem(topMenuSpacer, 0, 3, 1, 1);

        sizePolicyMinMin.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        sizePolicyMinMin.setHeightForWidth(changePlayersButton->sizePolicy().hasHeightForWidth());
        changePlayersButton->setSizePolicy(sizePolicyMinMin);
        sizePolicyMinMin.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicyMinMin);

        namesLayout->addWidget(topMenu, 0, 0, 1, 9);

        // ---- NAMES AND SCORE ENTRY SECTION ----

        namenLabel = new QLabel(centralwidget);
        namenLabel->setObjectName(QString::fromUtf8("namenLabel"));
        namenLabel->setSizePolicy(sizePolicyPreFix);
        sizePolicyPreFix.setHeightForWidth(namenLabel->sizePolicy().hasHeightForWidth());

        namesLayout->addWidget(namenLabel, 1, 0, 1, 1);

        letztesLabel = new QLabel(centralwidget);
        letztesLabel->setObjectName(QString::fromUtf8("letztesLabel"));
        sizePolicyPreFix.setHeightForWidth(letztesLabel->sizePolicy().hasHeightForWidth());
        letztesLabel->setSizePolicy(sizePolicyPreFix);

        namesLayout->addWidget(letztesLabel, 2, 0, 1, 1);

        aktuellesLabel = new QLabel(centralwidget);
        aktuellesLabel->setObjectName(QString::fromUtf8("aktuellesLabel"));
        aktuellesLabel->setMaximumWidth(leftLabelsMaxWidth);

        namesLayout->addWidget(aktuellesLabel, 3, 0, 1, 1);

        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            QLabel * name = new QLabel(centralwidget);
            name->setAlignment(Qt::AlignCenter);
            name->setObjectName(QString::fromUtf8("names%1").arg(i));
            namesLayout->addWidget(name, 1, i+1, 1, 1);
            names.push_back(name);

            QLabel * lastGame = new QLabel(centralwidget);
            lastGame->setAlignment(Qt::AlignCenter);
            lastGame->setObjectName(QString::fromUtf8("lastGames%1").arg(i));
            namesLayout->addWidget(lastGame, 2, i+1, 1, 1);
            lastGames.push_back(lastGame);

            QLineEdit * actual = new QLineEdit(centralwidget);
            actual->setObjectName(QString::fromUtf8("actuals%1").arg(i));
            actual->setMaximumWidth(leftMainMaxWidth);
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
        sizePolicyFixPre.setHeightForWidth(bockereignisseLabel->sizePolicy().hasHeightForWidth());
        bockereignisseLabel->setSizePolicy(sizePolicyFixPre);

        horizontalLayout->addWidget(bockereignisseLabel);

        spinBox = new QSpinBox(controlWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        sizePolicyFixFix.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicyFixFix);
        spinBox->setMaximum(9);
        spinBox->setMinimum(0);

        horizontalLayout->addWidget(spinBox);

        controlSpacer0 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(controlSpacer0);

        commitButton = new QPushButton(controlWidget);
        commitButton->setObjectName(QString::fromUtf8("commitButton"));

        horizontalLayout->addWidget(commitButton);

        controlSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(controlSpacer1);

        resetButton = new QPushButton(controlWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setFixedWidth(this->experimentalWidthOfResetButton);

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
        sizePolicyPreFix.setHeightForWidth(zuZahlenLabel->sizePolicy().hasHeightForWidth());
        zuZahlenLabel->setSizePolicy(sizePolicyPreFix);

        namesLayout->addWidget(zuZahlenLabel, 7, 0, 1, 1);

        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            QLabel * score = new QLabel(centralwidget);
            score->setAlignment(Qt::AlignCenter);
            score->setObjectName(QString::fromUtf8("scores%1").arg(i));
            score->setStyleSheet(ScoreStylesheet);
            namesLayout->addWidget(score, 5, i+1, 1, 1);
            scores.push_back(score);

            QLabel * cash = new QLabel(centralwidget);
            cash->setAlignment(Qt::AlignCenter);
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

        leftVerticalLayout->addLayout(namesLayout);

        // ---- STATISTICS SECTION IN A BOX ----

        statisticsBox = new QGroupBox(centralwidget);
        statisticsBox->setObjectName(QString::fromUtf8("statisticsBox"));
        statisticsGridLayout = new QGridLayout(statisticsBox);
        statisticsGridLayout->setObjectName(QString::fromUtf8("statisticsGridLayout"));

        gewonnenLabel = new QLabel(statisticsBox);
        gewonnenLabel->setObjectName(QString::fromUtf8("gewonnenLabel"));

        statisticsGridLayout->addWidget(gewonnenLabel, 0, 1, 1, 1);

        verlorenLabel = new QLabel(statisticsBox);
        verlorenLabel->setObjectName(QString::fromUtf8("verlorenLabel"));

        statisticsGridLayout->addWidget(verlorenLabel, 0, 2, 1, 1);

        anzahlSpieleLabel = new QLabel(statisticsBox);
        anzahlSpieleLabel->setObjectName(QString::fromUtf8("anzahlSpieleLabel"));

        statisticsGridLayout->addWidget(anzahlSpieleLabel, 0, 3, 1, 1);

        soloGewonnenLabel = new QLabel(statisticsBox);
        soloGewonnenLabel->setObjectName(QString::fromUtf8("soloGewonnenLabel"));

        statisticsGridLayout->addWidget(soloGewonnenLabel, 0, 4, 1, 1);

        soloVerlorenLabel = new QLabel(statisticsBox);
        soloVerlorenLabel->setObjectName(QString::fromUtf8("soloVerlorenLabel"));

        statisticsGridLayout->addWidget(soloVerlorenLabel, 0, 5, 1, 1);

        soloPunkteLabel = new QLabel(statisticsBox);
        soloPunkteLabel->setObjectName(QString::fromUtf8("soloPunkteLabel"));

        statisticsGridLayout->addWidget(soloPunkteLabel, 0, 6, 1, 1);

        groessterGewinnLabel = new QLabel(statisticsBox);
        groessterGewinnLabel->setObjectName(QString::fromUtf8("groessterGewinnLabel"));

        statisticsGridLayout->addWidget(groessterGewinnLabel, 0, 7, 1, 1);

        groessterVerlustLabel = new QLabel(statisticsBox);
        groessterVerlustLabel->setObjectName(QString::fromUtf8("groessterVerlustLabel"));

        statisticsGridLayout->addWidget(groessterVerlustLabel, 0, 8, 1, 1);

        ohneBockLabel = new QLabel(statisticsBox);
        ohneBockLabel->setObjectName(QString::fromUtf8("ohneBockLabel"));

        statisticsGridLayout->addWidget(ohneBockLabel, 0, 9, 1, 1);

        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            QLabel * statisticName = new QLabel(statisticsBox);
            statisticName->setObjectName(QString::fromUtf8("statisticNames%1").arg(i));
            statisticsGridLayout->addWidget(statisticName, i+1, 0, 1, 1);
            statisticNames.push_back(statisticName);

            QLabel * numberWon = new QLabel(statisticsBox);
            numberWon->setAlignment(Qt::AlignCenter);
            numberWon->setObjectName(QString::fromUtf8("numberWons%1").arg(i));
            statisticsGridLayout->addWidget(numberWon, i+1, 1, 1, 1);
            numberWons.push_back(numberWon);

            QLabel * numberLost = new QLabel(statisticsBox);
            numberLost->setAlignment(Qt::AlignCenter);
            numberLost->setObjectName(QString::fromUtf8("numberLosts%1").arg(i));
            statisticsGridLayout->addWidget(numberLost, i+1, 2, 1, 1);
            numberLosts.push_back(numberLost);

            QLabel * numberPlayed = new QLabel(statisticsBox);
            numberPlayed->setAlignment(Qt::AlignCenter);
            numberPlayed->setObjectName(QString::fromUtf8("numberPlayeds%1").arg(i));
            statisticsGridLayout->addWidget(numberPlayed, i+1, 3, 1, 1);
            numberPlayeds.push_back(numberPlayed);

            QLabel * numberSoloWon = new QLabel(statisticsBox);
            numberSoloWon->setAlignment(Qt::AlignCenter);
            numberSoloWon->setObjectName(QString::fromUtf8("numberSoloWons%1").arg(i));
            statisticsGridLayout->addWidget(numberSoloWon, i+1, 4, 1, 1);
            numberSoloWons.push_back(numberSoloWon);

            QLabel * numberSoloLost = new QLabel(statisticsBox);
            numberSoloLost->setAlignment(Qt::AlignCenter);
            numberSoloLost->setObjectName(QString::fromUtf8("numberSoloLosts%1").arg(i));
            statisticsGridLayout->addWidget(numberSoloLost, i+1, 5, 1, 1);
            numberSoloLosts.push_back(numberSoloLost);

            QLabel * pointsSolo = new QLabel(statisticsBox);
            pointsSolo->setAlignment(Qt::AlignCenter);
            pointsSolo->setObjectName(QString::fromUtf8("pointsSolos%1").arg(i));
            statisticsGridLayout->addWidget(pointsSolo, i+1, 6, 1, 1);
            pointsSolos.push_back(pointsSolo);

            QLabel * maxSingleWin = new QLabel(statisticsBox);
            maxSingleWin->setAlignment(Qt::AlignCenter);
            maxSingleWin->setObjectName(QString::fromUtf8("maxSingleWins%1").arg(i));
            statisticsGridLayout->addWidget(maxSingleWin, i+1, 7, 1, 1);
            maxSingleWins.push_back(maxSingleWin);

            QLabel * maxSingleLoss = new QLabel(statisticsBox);
            maxSingleLoss->setAlignment(Qt::AlignCenter);
            maxSingleLoss->setObjectName(QString::fromUtf8("maxSingleLosss%1").arg(i));
            statisticsGridLayout->addWidget(maxSingleLoss, i+1, 8, 1, 1);
            maxSingleLosss.push_back(maxSingleLoss);

            QLabel * unmultipliedScore = new QLabel(statisticsBox);
            unmultipliedScore->setAlignment(Qt::AlignCenter);
            unmultipliedScore->setObjectName(QString::fromUtf8("unmultipliedScores%1").arg(i));
            statisticsGridLayout->addWidget(unmultipliedScore, i+1, 9, 1, 1);
            unmultipliedScores.push_back(unmultipliedScore);
        }

        leftVerticalLayout->addWidget(statisticsBox);

        rightwidget = new QWidget(centralwidget);
        rightwidget->setObjectName(QString::fromUtf8("rightwidget"));
        centralLayout->addWidget(rightwidget);

        rightVerticalLayout = new QVBoxLayout(rightwidget);
        rightVerticalLayout->setObjectName(QString::fromUtf8("rightVerticalLayout"));

        currentGameMultiplier = new QLabel(rightwidget);
        currentGameMultiplier->setObjectName(QString::fromUtf8("currentGameMultiplier"));
        currentGameMultiplier->setStyleSheet(MultiplierStylesheet);
        rightVerticalLayout->addWidget(currentGameMultiplier);

        multiplierPreviewWidget= new QWidget(rightwidget);
        multiplierPreviewWidget->setObjectName(QString::fromUtf8("multiplierPreviewWidget"));
        multiplierPreviewGridLayout = new QGridLayout(multiplierPreviewWidget);

        dreifachbockLabel = new QLabel(rightwidget);
        dreifachbockLabel->setObjectName(QString::fromUtf8("dreifachbockLabel"));
        multiplierPreviewGridLayout->addWidget(dreifachbockLabel, 0, 0, 1, 1);

        doppelbockLabel = new QLabel(rightwidget);
        doppelbockLabel->setObjectName(QString::fromUtf8("doppelbockLabel"));
        multiplierPreviewGridLayout->addWidget(doppelbockLabel,  1, 0, 1, 1);

        einfachbockLabel = new QLabel(rightwidget);
        einfachbockLabel->setObjectName(QString::fromUtf8("einfachbockLabel"));
        multiplierPreviewGridLayout->addWidget(einfachbockLabel, 2, 0, 1, 1);

        tripleMultiplier = new QLabel(rightwidget);
        tripleMultiplier->setObjectName(QString::fromUtf8("tripleMultiplier"));
        multiplierPreviewGridLayout->addWidget(tripleMultiplier, 0, 1, 1, 1);

        doubleMultiplier = new QLabel(rightwidget);
        doubleMultiplier->setObjectName(QString::fromUtf8("doubleMultiplier"));
        multiplierPreviewGridLayout->addWidget(doubleMultiplier, 1, 1, 1, 1);

        singleMultiplier = new QLabel(rightwidget);
        singleMultiplier->setObjectName(QString::fromUtf8("singleMultiplier"));
        multiplierPreviewGridLayout->addWidget(singleMultiplier, 2, 1, 1, 1);

        rightVerticalLayout->addWidget(multiplierPreviewWidget);

        playerHistorySelectionWidget = new QWidget(rightwidget);
        playerHistorySelectionWidget->setObjectName(QString::fromUtf8("playerHistorySelectionWidget"));
        playerHistoryGridLayout = new QGridLayout(playerHistorySelectionWidget);

        unsigned int breaker = (maxNumberOfPlayers - maxNumberOfPlayers / 2);
        if(breaker < 2)
        {
            breaker = 2;
        }

        for(unsigned int i=0u; i < maxNumberOfPlayers; ++i)
        {
            int row = i < breaker ? 0 : 1;

            QHBoxLayout * layout = new QHBoxLayout(/*playerHistoryGridLayout later*/);
            layout->setObjectName(QString::fromUtf8("playerHistorySelectionLayout%1").arg(i));
            playerHistorySelectionLayouts.push_back(layout);

            QCheckBox * checkBox = new QCheckBox(playerHistorySelectionWidget);
            checkBox->setObjectName(QString::fromUtf8("playerHistorySelectionCheckbox%1").arg(i));
            checkBox->setChecked(true);
            layout->addWidget(checkBox);
            playerHistorySelectionCheckboxes.push_back(checkBox);

            QLabel * label = new QLabel(QString::fromUtf8("<b>!HTML</b>!Player"));
            label->setObjectName(QString::fromUtf8("playerHistorySelectionLabel%1").arg(i));
            layout->addWidget(label);
            playerHistorySelectionLabels.push_back(label);

            layout->addStretch(4);

            playerHistoryGridLayout->addLayout(layout, row, i%breaker, 1, 1);
        }

        rightVerticalLayout->addWidget(playerHistorySelectionWidget);

        plotPlayerHistory = new QCustomPlot(rightwidget);
        plotPlayerHistory->setObjectName(QString::fromUtf8("plotPlayerHistory"));
        plotPlayerHistory->setSizePolicy(sizePolicyExpExp);
        rightVerticalLayout->addWidget(plotPlayerHistory);

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
        QWidget::setTabOrder(saveButton, playerHistorySelectionCheckboxes[0]);

        for(unsigned int i=0u; i < maxNumberOfPlayers - 1; ++i)
        {
            QWidget::setTabOrder(playerHistorySelectionCheckboxes[i], playerHistorySelectionCheckboxes[i+1]);
        }

        QWidget::setTabOrder(playerHistorySelectionCheckboxes[maxNumberOfPlayers - 1], aboutButton);

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
        aboutButton->setText(QCoreApplication::translate("MainWindow", "Über QtDK", nullptr));

        namenLabel->setText(QCoreApplication::translate("MainWindow", "Namen", nullptr));
        letztesLabel->setText(QCoreApplication::translate("MainWindow", "Letztes Spiel", nullptr));
        aktuellesLabel->setText(QCoreApplication::translate("MainWindow", "Aktuelles Spiel", nullptr));

        bockereignisseLabel->setText(QCoreApplication::translate("MainWindow", "Bockereignisse", nullptr));
        commitButton->setText(QCoreApplication::translate("MainWindow", "\303\234bernehmen", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Zur\303\274cksetzen", nullptr));

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

        currentGameMultiplier->setText(QCoreApplication::translate("MainWindow", "Kein Bock", nullptr));
        dreifachbockLabel->setText(QCoreApplication::translate("MainWindow", "Dreifachbock Spiele", nullptr));
        doppelbockLabel->setText(QCoreApplication::translate("MainWindow", "Doppelbock Spiele", nullptr));
        einfachbockLabel->setText(QCoreApplication::translate("MainWindow", "Einfachbock Spiele", nullptr));
        tripleMultiplier->setText(QCoreApplication::translate("MainWindow", "!3bock", nullptr));
        doubleMultiplier->setText(QCoreApplication::translate("MainWindow", "!2bock", nullptr));
        singleMultiplier->setText(QCoreApplication::translate("MainWindow", "!1bock", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow
    {
    public:
        MainWindow(const unsigned int maxPlayers)
            : Ui_MainWindow(maxPlayers)
        {
        }
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

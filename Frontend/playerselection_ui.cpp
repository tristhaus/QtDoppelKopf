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

#include "playerselection_ui.h"
#include <algorithm>

Ui::PlayerSelection::PlayerSelection(unsigned int maxNumberOfPlayers,
                                     std::vector<std::pair<QString, bool>> currentPlayers,
                                     QString currentDealer,
                                     std::set<unsigned int> currentSitOutScheme,
                                     QWidget *parent)
    : QDialog(parent),
      maxNumberOfPlayers(maxNumberOfPlayers),
      initialNumberOfPlayers(std::count_if(currentPlayers.begin(), currentPlayers.end(), [&](std::pair<QString, bool> item){ return item.second; })),
      originalPlayers(currentPlayers),
      originalDealer(currentDealer),
      originalSitOutScheme(currentSitOutScheme)
{
    this->SetupUi();
    this->adjustSize();
}

void Ui::PlayerSelection::SetupUi()
{
    this->resize(500, 500);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());

    this->setSizePolicy(sizePolicy);

    verticalDialogLayout = new QVBoxLayout(this);
    verticalDialogLayout->setObjectName(QString::fromUtf8("verticaldialoglayout"));

    topLayout = new QHBoxLayout();
    topLayout->setObjectName(QString::fromUtf8("toplayout"));

    dialogAnzahlSpielerLabel = new QLabel("Anzahl Spieler", this);
    dialogAnzahlSpielerLabel->setObjectName(QString::fromUtf8("dialoganzahlspielerlabel"));
    topLayout->addWidget(dialogAnzahlSpielerLabel);

    dialogNumberOfPresentPlayers = new QSpinBox(this);
    dialogNumberOfPresentPlayers->setObjectName(QString::fromUtf8("dialognumberofpresentplayers"));
    dialogNumberOfPresentPlayers->setMaximum(maxNumberOfPlayers);
    dialogNumberOfPresentPlayers->setMinimum(4);
    dialogNumberOfPresentPlayers->setValue(initialNumberOfPlayers);
    topLayout->addWidget(dialogNumberOfPresentPlayers);

    verticalDialogLayout->addLayout(topLayout);

    playerNamesGridLayout = new QGridLayout();
    playerNamesGridLayout->setObjectName(QString::fromUtf8("playernamesgridlayout"));

    for(unsigned int index = 0; index < maxNumberOfPlayers; ++index)
    {
        dialogNames.push_back(new QLineEdit(this));
        dialogNames[index]->setObjectName(QString::fromUtf8("dialognames%1").arg(index));
        playerNamesGridLayout->addWidget(dialogNames[index], index, 1, 1, 1);
        dealerButtons.push_back(new QRadioButton(this));
        dealerButtons[index]->setObjectName(QString::fromUtf8("dealerbuttons%1").arg(index));
        playerNamesGridLayout->addWidget(dealerButtons[index], index, 0, 1, 1);

        bool needed = index < static_cast<unsigned int>(dialogNumberOfPresentPlayers->value());
        dialogNames[index]->setVisible(needed);
        dialogNames[index]->setEnabled(needed);
        dealerButtons[index]->setVisible(needed);
        dealerButtons[index]->setEnabled(needed);
    }

    verticalDialogLayout->addLayout(playerNamesGridLayout);

    dialogSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalDialogLayout->addItem(dialogSpacer);

    bottomLayout = new QVBoxLayout();
    bottomLayout->setObjectName(QString::fromUtf8("bottomLayout"));

    dialogAussitzenLabel = new QLabel("Aussitzen an Position (1 ist Geber):", this);
    dialogAussitzenLabel->setObjectName(QString::fromUtf8("dialogaussitzenlabel"));
    bottomLayout->addWidget(dialogAussitzenLabel);

    for(unsigned int index = 0; index < (maxNumberOfPlayers - 4); ++index)
    {
        dialogSittingOuts.push_back(new QSpinBox(this));
        dialogSittingOuts[index]->setObjectName(QString::fromUtf8("dialogsittingouts%1").arg(index));
        dialogSittingOuts[index]->setValue(2 * index + 1); // is one-indexed to the user

        if(index == 0)
        {
            dialogSittingOuts[index]->setEnabled(false);
        }

        bool isVisible = (dialogNumberOfPresentPlayers->value() - (4 + static_cast<int>(index))) > 0;
        dialogSittingOuts[index]->setVisible(isVisible);

        bottomLayout->addWidget(dialogSittingOuts[index]);
    }

    dialogAcceptButton = new QPushButton("OK");
    dialogAcceptButton->setObjectName(QString::fromUtf8("dialogacceptbutton"));
    bottomLayout->addWidget(dialogAcceptButton);

    verticalDialogLayout->addLayout(bottomLayout);

    this->setLayout(verticalDialogLayout);
}

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

#ifndef PLAYERSELECTION_UI_H
#define PLAYERSELECTION_UI_H

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
#include <QtWidgets/QDialog>
#include <QtWidgets/QRadioButton>

#include <utility>
#include <set>
#include <vector>

class FrontendTest;

QT_BEGIN_NAMESPACE

namespace Ui
{
    class PlayerSelection : public QDialog
    {
        Q_OBJECT

        friend FrontendTest;

    private:
        const unsigned int maxNumberOfPlayers;
        const unsigned int initialNumberOfPlayers;

        std::vector<std::pair<QString, bool>> originalPlayers;
        QString originalDealer;
        std::set<unsigned int> originalSitOutScheme;

        std::vector<QString> resultPlayers;
        QString resultDealer;
        std::set<unsigned int> resultSitOutScheme;

        QVBoxLayout * verticalDialogLayout;
        QHBoxLayout * topLayout;
        QGridLayout * playerNamesGridLayout;
        QSpinBox * dialogNumberOfPresentPlayers;
        QLabel * dialogAnzahlSpielerLabel;
        std::vector<QLineEdit*> dialogNames;
        std::vector<QRadioButton*> dealerButtons;
        QSpacerItem * dialogSpacer;
        QVBoxLayout * bottomLayout;
        QLabel * dialogAussitzenLabel;
        QPushButton * dialogAcceptButton;
        std::vector<QSpinBox*> dialogSittingOuts; // is one-indexed to the user

    public:
        /*!
         * \brief Initializes a new instance of the player selection dialog.
         * \param maxNumberOfPlayers The maximum number of configurable players.
         * \param currentPlayers Pairs representing the current players by name
         *                       and whether they are present at the table.
         * \param currentDealer The name of the current dealer.
         * \param currentSitOutScheme Collection of indices of players sitting out, if any.
         *                            Dealer is 0, implied to be sitting out, and ignored.
         * \param parent The Qt parent.
         */
        PlayerSelection(unsigned int maxNumberOfPlayers,
                        std::vector<std::pair<QString, bool>> currentPlayers,
                        QString currentDealer,
                        std::set<unsigned int> currentSitOutScheme,
                        QWidget *parent);

        /*!
         * \brief Gets the results of the configuration regarding the players at the table.
         * \return A tuple containing:
         *           all player names
         *           the name of the dealer
         *           the zero-indexed sitting out scheme, 0 is the dealer
         */
        std::tuple<std::vector<QString>, QString, std::set<unsigned int>> GetResults() const;

    private:
        void SetupUi();
        void SetOriginalPlayers();

    private slots:
        void OnOKButtonClicked();
        void OnNumberOfPresentPlayersChange();
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // PLAYERSELECTION_UI_H

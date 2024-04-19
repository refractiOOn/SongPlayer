import QtQuick
import com.refraction.PlayerController
import com.refraction.AudioSearchModel

Window {
	id: _root

	width: 960
	height: 540
	visible: true

	title: qsTr('Song Player')

    Rectangle {
        id: _topBar

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 50

        color: '#5f8575'

        SearchField {
            id: _searchField

            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: _closeSearchButton.left
                margins: 10
            }

            height: 30
            visible: !_searchPanel.hidden
            enabled: !AudioSearchModel.isSearching

            onAccepted: value => {
                AudioSearchModel.searchSong(value)
                _topBar.forceActiveFocus()
            }
        }

        ImageButton {
            id: _playlistIcon

            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 20
            }

            width: 32
            height: 32
            visible: _searchPanel.hidden

            source: 'qrc:/assets/icons/menu_icon.png'

            onClicked: {
                _playlistPanel.hidden = !_playlistPanel.hidden
            }
        }

        ImageButton {
            id: _closeSearchButton

            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 20
            }

            height: 32
            width: 32
            visible: !_searchPanel.hidden

            source: 'qrc:/assets/icons/close_icon.png'

            onClicked: {
                _searchPanel.hidden = true
            }
        }
    }

    Rectangle {
        id: _content

        anchors {
            top: _topBar.bottom
            left: parent.left
            right: parent.right
            bottom: _bottomBar.top
        }

        color: '#1e1e1e'

        AudioInfoBox {
            id: _songInfo

            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
                margins: 20
            }
        }
    }

    Rectangle {
        id: _bottomBar

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 100

        color: '#333333'

        Row {
            anchors.centerIn: parent
            spacing: 20

            ImageButton {
                id: _previousButton

                width: 64
                height: 64

                source: 'qrc:/assets/icons/previous_icon.png'

                onClicked: PlayerController.switchToPrevious()
            }

            ImageButton {
                id: _playPauseButton

                width: 64
                height: 64

                source: PlayerController.playing ?
                            'qrc:/assets/icons/pause_icon.png' :
                            'qrc:/assets/icons/play_icon.png'

                onClicked: PlayerController.playPause()
            }

            ImageButton {
                id: _nextButton

                width: 64
                height: 64

                source: 'qrc:/assets/icons/next_icon.png'

                onClicked: PlayerController.switchToNext()
            }
        }
    }

    PlaylistPanel {
        id: _playlistPanel

        anchors.top: _topBar.bottom
        x: hidden ? parent.width : parent.width - width

        onSearchRequested: {
            _searchPanel.hidden = false
        }
    }

    SearchPanel {
        id: _searchPanel

        anchors {
            left: parent.left
            right: parent.right
        }

        height: _content.height + _bottomBar.height
        y: hidden ? parent.height : _topBar.height
    }
}

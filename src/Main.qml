import QtQuick
import com.refraction.PlayerController

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

        ImageButton {
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 20
            }

            width: 32
            height: 32

            source: 'qrc:/Assets/Icons/menu_icon.png'

            onClicked: {
                _playlistPanel.hidden = !_playlistPanel.hidden
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

                source: 'qrc:/Assets/Icons/previous_icon.png'

                onClicked: PlayerController.switchToPrevious()
            }

            ImageButton {
                id: _playPauseButton

                width: 64
                height: 64

                source: PlayerController.playing ?
                            'qrc:/Assets/Icons/pause_icon.png' :
                            'qrc:/Assets/Icons/play_icon.png'

                onClicked: PlayerController.playPause()
            }

            ImageButton {
                id: _nextButton

                width: 64
                height: 64

                source: 'qrc:/Assets/Icons/next_icon.png'

                onClicked: PlayerController.switchToNext()
            }
        }
    }

    PlaylistPanel {
        id: _playlistPanel

        anchors.top: _topBar.bottom
        x: hidden ? parent.width : parent.width - width
    }
}

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
            id: _firstSong

            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
                margins: 20
            }

            infoProvider {
                songIndex: 0
                title: 'Eine Kleine Nachtmusik'
                authorName: 'Wolfgang Amadeus Mozart'
                imageSource: Qt.resolvedUrl('Assets/Images/song_1.jpg')
                audioSource: Qt.resolvedUrl('Assets/Audio/eine_kleine_nachtmusik.mp3')
            }
        }

        AudioInfoBox {
            id: _secondSong

            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
                margins: 20
            }

            infoProvider {
                songIndex: 1
                title: 'Symphony No. 5'
                authorName: 'Ludwig Van Beethoven'
                imageSource: Qt.resolvedUrl('Assets/Images/song_2.jpg')
                audioSource: Qt.resolvedUrl('Assets/Audio/symphony_no_5.mp3')
            }
        }

        AudioInfoBox {
            id: _thirdSong

            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
                margins: 20
            }

            infoProvider {
                songIndex: 2
                title: 'Air on the G String'
                authorName: 'Johann Sebastian Bach'
                imageSource: Qt.resolvedUrl('Assets/Images/song_3.jpg')
                videoSource: Qt.resolvedUrl('Assets/Videos/video_1.avi')
                audioSource: Qt.resolvedUrl('Assets/Audio/air_on_the_g_string.mp3')
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

                source: Qt.resolvedUrl('Assets/Icons/previous_icon.png')

                onClicked: PlayerController.switchToPrevious()
            }

            ImageButton {
                id: _playPauseButton

                width: 64
                height: 64

                source: PlayerController.playing ?
                            Qt.resolvedUrl('Assets/Icons/pause_icon.png') :
                            Qt.resolvedUrl('Assets/Icons/play_icon.png')

                onClicked: PlayerController.playPause()
            }

            ImageButton {
                id: _nextButton

                width: 64
                height: 64

                source: Qt.resolvedUrl('Assets/Icons/next_icon.png')

                onClicked: PlayerController.switchToNext()
            }
        }
    }
}

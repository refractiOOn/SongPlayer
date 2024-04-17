import QtQuick
import com.refraction.PlayerController

Rectangle {
	id: _root

	property bool hidden: true

	height: 400
	width: 250

	color: '#333333'

	Text {
		id: _playlistText

		anchors {
			left: parent.left
			top: parent.top
			margins: 10
		}

		text: 'Playlist'
		color: 'white'
		font {
			bold: true
			pixelSize: 20
		}
	}

    ListView {
        id: _listView

        anchors {
            top: _playlistText.bottom
            left: parent.left
            right: parent.right
            bottom: _addButton.top
            margins: 20
        }

        clip: true
        spacing: 10
        model: PlayerController

        delegate: Rectangle {
            id: _delegate

            required property string title
            required property string authorName
            required property url source
            required property url imageSource
            required property url videoSource
            required property int index

            width: _listView.width
            height: 50

            color: '#1e1e1e'

            Column {
                id: _textColumn

                anchors {
                    top: parent.top
                    left: parent.left
                    right: _trashButton.left
                    margins: 5
                }
                spacing: 5

                Text {
                    width: parent.width

                    text: _delegate.title
                    color: 'white'

                    elide: Text.ElideRight
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 10
                    font {
                        pixelSize: 14
                        bold: true
                    }
                }

                Text {
                    width: parent.width

                    text: _delegate.authorName
                    color: 'gray'

                    elide: Text.ElideRight
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 6
                    font.pixelSize: 10
                }
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    PlayerController.switchToAudio(_delegate.index)
                }
            }

            ImageButton {
                id: _trashButton

                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: 5
                }

                width: 30
                height: 30

                source: 'qrc:/Assets/Icons/trash_icon.png'

                onClicked: {
                    PlayerController.removeAudio(_delegate.index)
                }
            }
        }
    }

	ImageButton {
		id: _addButton

		anchors {
			left: parent.left
			bottom: parent.bottom
			margins: 20
		}

		width: 32
		height: 32

        source: 'qrc:/Assets/Icons/add_icon.png'

		onClicked: {
            PlayerController.addAudio('Reprezentuje biede',
                                      'Rychu Peja',
                                      'qrc:/Assets/Audio/reprezentuje_biede.mp3',
                                      'qrc:/Assets/Images/song_3.jpg')
		}
	}

	Behavior on x {
		PropertyAnimation {
			easing.type: Easing.InOutQuad
			duration: 200
		}
	}
}

import QtQuick
import com.refraction.PlayerController
import com.refraction.AudioSearchModel

Rectangle {
    id: _root

    property bool hidden: true

    color: '#333333'

    ListView {
        id: _listView

        anchors {
            fill: parent
            margins: 20
        }
        visible: !AudioSearchModel.isSearching

        spacing: 10
        clip: true
        model: AudioSearchModel

        delegate: Rectangle {
            id: _delegate

            required property string name
            required property string author
            required property url imageSource
            required property url source
            required property int index

            width: _listView.width
            height: 50

            color: '#1e1e1e'

            Image {
                id: _audioImage

                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 5
                }

                width: 32
                height: 32

                source: _delegate.imageSource
            }

            Column {
                anchors {
                    left: _audioImage.right
                    right: parent.right
                    top: parent.top
                    margins: 5
                }

                spacing: 5

                Text {
                    width: parent.width

                    text: _delegate.name
                    color: 'white'

                    fontSizeMode: Text.Fit
                    minimumPixelSize: 12
                    elide: Text.ElideRight

                    font {
                        pixelSize: 16
                        bold: true
                    }
                }

                Text {
                    width: parent.width

                    text: _delegate.author
                    color: 'gray'

                    fontSizeMode: Text.Fit
                    minimumPixelSize: 8
                    elide: Text.ElideRight

                    font.pixelSize: 12
                }
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    _root.hidden = true
                    PlayerController.addAudio(_delegate.name, _delegate.author, _delegate.source, _delegate.imageSource)
                }
            }
        }
    }

    Text {
        anchors.centerIn: parent
        visible: AudioSearchModel.isSearching || !_listView.count

        color: 'gray'
        text: AudioSearchModel.isSearching ?
                  'Searching...' :
                  (!_listView.count ?
                       'No results' :
                       '')
    }

    Behavior on y {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
            duration: 200
        }
    }
}

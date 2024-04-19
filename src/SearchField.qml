import QtQuick
import QtQuick.Controls

Rectangle {
    id: _root

    signal accepted(string value)

    color: '#1e1e1e'
    opacity: enabled ? 1 : 0.6

    border {
        width: 1
        color: _searchInput.activeFocus ? Qt.lighter('#5f8575') : 'transparent'
    }

    TextInput {
        id: _searchInput

        anchors.fill: parent

        leftPadding: 30
        font.pixelSize: 14
        color: 'white'
        verticalAlignment: TextInput.AlignVCenter

        Image {
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 5
            }

            width: 16
            height: 16

            mipmap: true
            source: 'qrc:/assets/icons/search_icon.png'
        }

        onAccepted: {
            _root.accepted(text)
        }
    }
}

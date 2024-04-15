import QtQuick

Image {
    id: _root

    signal clicked()

    opacity: _mouseArea.containsMouse ? 0.75 : 1.0
    mipmap: true

    MouseArea {
        id: _mouseArea

        anchors.fill: parent
        hoverEnabled: true

        onClicked: _root.clicked()
    }
}
